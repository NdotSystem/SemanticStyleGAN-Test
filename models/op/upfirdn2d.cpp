// Copyright (c) 2019, NVIDIA Corporation. All rights reserved.
//
// This work is made available under the Nvidia Source Code License-NC.
// To view a copy of this license, visit
// https://nvlabs.github.io/stylegan2/license.html

#include <ATen/ATen.h>
#include <torch/extension.h>

torch::Tensor upfirdn2d_op(const torch::Tensor &input,
                           const torch::Tensor &kernel, int up_x, int up_y,
                           int down_x, int down_y, int pad_x0, int pad_x1,
                           int pad_y0, int pad_y1);

#define CHECK_CUDA(x)                                                          \
  TORCH_CHECK(x.type().is_cuda(), #x " must be a CUDA tensor")
#define CHECK_CONTIGUOUS(x)                                                    \
  TORCH_CHECK(x.is_contiguous(), #x " must be contiguous")
#define CHECK_INPUT(x)                                                         \
  CHECK_CUDA(x);                                                               \
  CHECK_CONTIGUOUS(x)

torch::Tensor upfirdn2d(const torch::Tensor &input, const torch::Tensor &kernel,
                        int up_x, int up_y, int down_x, int down_y, int pad_x0,
                        int pad_x1, int pad_y0, int pad_y1) {
  CHECK_INPUT(input);
  CHECK_INPUT(kernel);

  at::DeviceGuard guard(input.device());

  return upfirdn2d_op(input, kernel, up_x, up_y, down_x, down_y, pad_x0, pad_x1,
                      pad_y0, pad_y1);
}

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
  m.def("upfirdn2d", &upfirdn2d, "upfirdn2d (CUDA)");
}