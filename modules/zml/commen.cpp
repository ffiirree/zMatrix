#ifdef USE_CUDA
#include <cublas_v2.h>
#endif
#include <glog/logging.h>
#include "commen.hpp"

namespace z {

Global* Global::instance_ = nullptr;

Global& Global::Instance() {
    if (instance_ == nullptr) {
        instance_ = new Global();
    }
    return *instance_;
}

Global::Global()
{
#ifdef USE_CUDA
    if(cublasCreate(&cublas_handle_) != CUBLAS_STATUS_SUCCESS) {
        LOG(INFO) << "Create Cublas handle failed!";
    }
#endif
}

Global::~Global()
{
#ifdef USE_CUDA
    if(cublas_handle_) cublasDestroy(cublas_handle_);
#endif
}

std::ostream& operator << (std::ostream& os, const vector<int>& vec)
{
    auto size = vec.size();
    os << "[";
    for(size_t i = 0; i < size; ++i) {
        os << vec[i] << (i == (size - 1) ? "" : ", ");
    }
    os << "]";
    return os;
}

}