# tensorrt_retinaface_with_python
just add python bindings for tensorrt_retinaface detect frame works (support onnx to tensorRT modules)

# TensorRT ONNX with python bindings 

clone from https://github.com/wuchaodzxx/tensorrt_retinaface

I add python bindings for python3 support for tensortRT ONNX (+  opencv4)

#how to run:
1 ./build_all.sh 
2 cp build/libtensorrt_engine_lib.so  /usr/local/lib/
3 cd python && python3 setup.py install 
# you must have cuda , tensorRT , opencv4.x , python-boost installed 
4 convert onnx models to tensorRT
onnx2trt models/retinaface_mbv2_sim.onnx -o models/retinaface.trt
5 test 
cd python &&  python3 test.py 


details:
tensorRT wrapper : tensorrt_engine_wrap.cc
python Modules   : python/trt_engine_retinaface_module.cpp python/setup.py 

python Modules   :
references : 
https://github.com/PierreFritsch/OpenCV-Python-C-Module-for-Image-Processing/
https://github.com/Algomorph/pyboostcvconverter

OpenCV-Python-C-Module-for-Image-Processing project is simple but does not work for my opencv4 env . 
pyboostcvconverter is a little complicated.

i extract pyboost_cv4_converter.cpp from pyboostcvconverter , and combine it to OpenCV-Python-C-Module-for-Image-Processing 


