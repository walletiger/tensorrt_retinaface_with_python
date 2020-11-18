from setuptools import setup, Extension, find_packages
import distutils.command.clean
from torch.utils.cpp_extension import BuildExtension

setup(
    name='TRTRetinaFace',
    version='1.0',
    author="hugo",
    url="",
    description='Python Package with Hello World C++ Extension',

    # Package info
    packages=find_packages(exclude=('test',)),
    zip_safe=False,

    ext_modules=[
        Extension(
            'TRTRetinaFace',
            sources=['pyboostcvconverter/pyboost_cv4_converter.cpp', 'trt_engine_retinaface_module.cpp'],
            include_dirs=['/usr/local/lib/python3.6/dist-packages/numpy/core/include/numpy/',
                          '/usr/local/cuda/include/', '/workspace/face_detect/tensorrt_retinaface/include', 
                          '../include'
                         ],
            library_dirs=['../build'],
            libraries=['gstvideo-1.0', 'opencv_features2d', 'opencv_flann',  'opencv_imgcodecs', 'opencv_imgproc', 'opencv_core', 'opencv_highgui', 'opencv_videoio', 'tensorrt_engine_lib',  "thor", "boost_python3"],
            py_limited_api=True)
    ],
    #data_files=[('./', ['libtensorrt_engine_lib.so'])],
    #cmdclass={
    #    'build_ext': BuildExtension.with_options(no_python_abi_suffix=True),
    #}


)


#        ${CUDA_LIBRARIES}
#        ${CUDNN_LIBRARY}
#        ${TENSORRT_LIBRARY}
#        tensorrt_engine_lib
#        ${OpenCV_LIBS}
#        thor
