import numpy as np
import cv2

# function: load the image and put text on it

img = cv2.imread('cre.bmp'); 
'''
# Draw a diagonal blue line with thickness of 5 px
cv2.line(img,(0,0),(511,511),(255,0,0),5)

cv2.rectangle(img,(384,0),(510,128),(0,255,0),3)

cv2.circle(img,(447,63), 63, (0,0,255), -1)

cv2.ellipse(img,(256,256),(100,50),0,0,180,255,-1)
'''
font = cv2.FONT_HERSHEY_SIMPLEX
# (0,255,0) is the scalar color
cv2.putText(img,'ID',(10,500), 1, 2,(0,255,0),2, lineType=8)
cv2.putText(img,'# Slide',(200,500), 1, 2,(0,255,0),2, lineType=8)

cv2.imshow("Display image", img);

cv2.waitKey(0)

cv2.destroyAllWindows()
