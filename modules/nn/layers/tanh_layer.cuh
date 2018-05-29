#include <device_launch_parameters.h>

namespace alchemy {

template <typename T>
__global__ void tanh_kernel(const size_t size, const T* A, T* B)
{
    for (int i = blockIdx.x * blockDim.x + threadIdx.x; i < size; i += blockDim.x * gridDim.x) {
        B[i] = std::tanh(A[i]);
    }
}
template <typename Device, typename T>
void TanhLayer<Device, T>::ForwardGPU(const vector<container *> &input,
                              const vector<container *> &output)
{
    const auto count = input[0]->size();
    const auto input_data = input[0]->data_gptr();
    auto output_data = output[0]->mutable_data_gptr();

    tanh_kernel<<<CUDA_BLOCK_NUM(count), CUDA_THREAD_NUM>>>(count, input_data, output_data);
}

template <typename T>
__global__ void dtanh_kernel(const size_t size, const T* OutputData, const T* OutputDiff, T* InputDiff)
{
    for (int i = blockIdx.x * blockDim.x + threadIdx.x; i < size; i += blockDim.x * gridDim.x) {
        auto tx = OutputData[i];
        InputDiff[i] = OutputDiff[i] *(1 - tx * tx);
    }
}
template <typename Device, typename T>
void TanhLayer<Device, T>::BackwardGPU(const vector<container *> &input,
                               const vector<container *> &output)
{
    auto count = input[0]->size();
    auto output_data = output[0]->data_gptr();
    auto output_diff = output[0]->diff_gptr();
    auto input_diff = input[0]->mutable_diff_gptr();

    dtanh_kernel<<<CUDA_BLOCK_NUM(count), CUDA_THREAD_NUM>>>(count, output_data, output_diff, input_diff);
}

}