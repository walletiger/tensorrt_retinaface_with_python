mkdir build
cd build
cmake  -DCUDA_INCLUDE_DIRS=/usr/local/cuda/include -DTENSORRT_ROOT=/usr/src/tensorrt -DCMAKE_CUDA_COMPILER=/usr/local/cuda/bin/nvcc .. 
make -j8

