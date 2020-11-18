#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <Python.h>
#include <time.h>
#include <sys/time.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "tensorrt_engine_wrap.h"
#include "pyboostcvconverter/pyboostcvconverter.hpp"
#include <boost/python.hpp>

using namespace cv;
using namespace boost::python;

static unsigned int time_now_ms()
{
    struct timespec t_now;
    int i_sec, i_ms;

    clock_gettime(CLOCK_MONOTONIC, &t_now);

    i_sec = (int)(t_now.tv_sec);
    i_ms  = (int)(t_now.tv_nsec/1000000);

    return (unsigned int)(1000*i_sec + i_ms);
}


static PyObject * mpyCreate(PyObject *self, PyObject *args)
{
    char *engine_name = NULL;
    int w, h;
    void *ctx = NULL;
    unsigned int t0, t1;
    
    if (!PyArg_ParseTuple(args, "s", &engine_name))
        return NULL;

    printf("create engine , trt name = %s \n", engine_name );
    t0 = time_now_ms();
    ctx = trt_engine_retinaface_create(engine_name);
    t1 = time_now_ms();
    printf("engine create  = %lu, cost %d ms\n", (unsigned long long)ctx, t1 - t0);
    return Py_BuildValue("K", (unsigned long long)ctx);

}

static PyObject *mpyDetect(PyObject *self, PyObject *args)
{
    void *engine = NULL;
    PyObject *ndArray = NULL;
    const char *ret = NULL;
    unsigned long long v; 
    unsigned int t0, t1, t2;

    if (!PyArg_ParseTuple(args, "KO", &v, &ndArray))
        return NULL;

    t0 = time_now_ms();
    Mat mat = pbcvt::fromNDArrayToMat(ndArray);
    t1 = time_now_ms();
    
    engine = (void *)v;
    ret = trt_engine_retinaface_detect(engine, mat);
    t2 = time_now_ms();

    printf("engine do detect , load numpy array to mat cost %d ms, detect cost %d ms \n", t1 - t0, t2 - t1);
    return Py_BuildValue("s", ret);
}

static PyObject * mPyDestroy(PyObject *self, PyObject *args)
{
    void *engine = NULL;
    unsigned long long v; 
    if (!PyArg_ParseTuple(args, "K", &v))
        return NULL;

    printf(" destroy engine , engine = %lu\n", v);
    engine = (void *)v;
    trt_engine_retinaface_destroy(engine);

    return NULL;

}

static PyMethodDef TRTRetinaFaceMeThods[] = {
    {"create", mpyCreate, METH_VARARGS, "Create the engine."},
    {"detect", mpyDetect, METH_VARARGS, "use the engine to detect image"},    
    {"destroy", mPyDestroy, METH_VARARGS, "destroy the engine"},        
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef TRTRetinaFaceModule = {
    PyModuleDef_HEAD_INIT,
    "TRTRetinaFace",     /* name of module */
    "",          /* module documentation, may be NULL */
    -1,          /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    TRTRetinaFaceMeThods
};

PyMODINIT_FUNC PyInit_TRTRetinaFace(void) {
    printf("init module ... \n");

    return PyModule_Create(&TRTRetinaFaceModule);
}



