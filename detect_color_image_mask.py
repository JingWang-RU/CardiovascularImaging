import numpy as np
import cv2
import matplotlib.pyplot as plt
from scipy.misc import imsave
import sys
# function: read an image and extract yellow save in png
# author : Jing jiw2026@med.cornell.edu
# time: Sept. 20th 2018

def show(title, img, color = True):
   if color:
       plt.imshow(img[:,:,::-1]), plt.title(title), plt.show()
   else:
       plt.imshow(img, cmap='gray'), plt.title(title), plt.show()

def save_mask(path, mask_path):
   img = cv2.imread(path)
   #show('original', img)

   #yellow
   mask = cv2.inRange(img,(25,146,190),(62,174,250))
   #show('mask', mask, False)
   imsave(mask_path, mask)

#res=255-cv2.cvtColor(mask,cv2.COLOR_GRAY2BGR)
#show('result', res, False)
if __name__ == "__main__":
   save_mask(sys.argv[1], sys.argv[2])
