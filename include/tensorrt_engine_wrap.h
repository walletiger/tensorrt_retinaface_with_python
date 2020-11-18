#pragma once 

#ifdef __cplusplus
extern "C"
{
#endif 

void * trt_engine_retinaface_create(const char * engine_path);
const char * trt_engine_retinaface_detect(void *h_engine, cv::Mat &img);
void trt_engine_retinaface_destroy(void *h_engine);

#ifdef __cplusplus
}
#endif 
