#include <device_launch_parameters.h>

namespace alchemy {

template <typename T>
__global__ void relu_kernel(const size_t size, const T* InputData, double alpha, T* OutputData)
{
    for (int i = blockIdx.x * blockDim.x + threadIdx.x; i < size; i += blockDim.x * gridDim.x) {
        OutputData[i] = InputData[i] > (T)0.0 ? InputData[i] : alpha * InputData[i];
    }
}

template <typename Device, typename T>
void ReLuLayer<Device, T>::ForwardGPU(const vector<container *> &input,
                              const vector<container *> &output)
{
    auto count = input[0]->size();
    auto input_data = input[0]->data_gptr();
    auto output_data = output[0]->mutable_data_gptr();

    relu_kernel<<<CUDA_BLOCK_NUM(count), CUDA_THREAD_NUM>>>(count, input_data, relu_param_.alpha(), output_data);
}


template <typename T>
__global__ void drelu_kernel(const size_t size, const T* InputData, const T* OutputDiff, double alpha, T* InputDiff)
{
    for (int i = blockIdx.x * blockDim.x + threadIdx.x; i < size; i += blockDim.x * gridDim.x) {
        InputDiff[i] = OutputDiff[i] * ((InputData[i] > 0) ? 1 : alpha);
    }
}

template<typename Device, typename T>
void ReLuLayer<Device, T>::BackwardGPU(const vector<container *> &input,
                               const vector<container *> &output)
{
    auto count = input[0]->size();
    auto input_data = input[0]->data_gptr();
    auto output_diff = output[0]->diff_gptr();
    auto input_diff = input[0]->mutable_diff_gptr();

    drelu_kernel<<<CUDA_BLOCK_NUM(count), CUDA_THREAD_NUM>>>(count, input_data, output_diff, relu_param_.alpha(), input_diff);
}
}