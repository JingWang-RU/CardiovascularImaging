from __future__ import print_function
import cv2
import numpy as np
import os
from matplotlib import pyplot as plt
from os import listdir
# function: detect the edge of echo images with "canny edge" provided by Opencv
imgpath = '../dataset/A4C/'
included_extensions = ['jpg']
files = [fn for fn in os.listdir(imgpath) if any(fn.endswith(ext) for ext in included_extensions)]#[f for f in listdir(imgpath) if os.path.isfile(''.join(imgpath, f))]
for imgname in files:
  imgid = imgname.split(".")[0]
  print('file name %s ' % imgid, end='')
  img = cv2.imread(imgpath+imgname,0)
  figpath = './figures/'+ imgid+'/'
  if not os.path.isdir(figpath):
     os.makedirs(figpath)
  for thred1 in range(10,200,50):
   print ("thred 1: %d " % thred1, end = "")
   for thred2 in range(10,200,50):
      print("thred 2: %d " % thred2)
      edges = cv2.Canny(img,thred1,thred2,3,L2gradient=False)
      plt.subplot(121),plt.imshow(img,cmap = 'gray')
      plt.title('Original Image'), plt.xticks([]), plt.yticks([])
      plt.subplot(122),plt.imshow(edges,cmap = 'gray')
      plt.title('Edge Image '+str(thred1)+":"+str(thred2)), plt.xticks([]), plt.yticks([])
   
      filename = figpath+"imid_"+imgid+"_th_"+str(thred1) +"_"+str(thred2)+".png"
      plt.savefig(filename, format='png')
      
      #plt.show()
      plt.close()
