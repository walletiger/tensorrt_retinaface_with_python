import cv2 
import TRTRetinaFace as t

engine = t.create('../retinaface.trt')

for i in range(1, 6):
    img = cv2.imread('/home/walle/x%d.jpg' % i)
    b = t.detect(engine, img)
    print(b)

