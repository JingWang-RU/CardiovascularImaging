from PIL import Image
import os, os.path
import numpy as np
import shutil
imgs = []
imgs_dir = []

''' function:
1. find non_all_black images in './gt/', save in 'valid_images.out'
2. move non_all_black images from './gt/' to target directory subFolder
'''

path = "/CT/gt/"
valid_images = [".bmp"]
i = 0
for f in os.listdir('./gt/'):
 print('iteration %d' %i)
 i = i+1
 ext = os.path.splitext(f)[1]
 img = Image.open(os.path.join(path,f))
 img_matrix = list(np.asarray(img))
 nonzo = np.nonzero(img_matrix)[0]

 # the image is black
 if nonzo.size == 0:
   continue
 imgs_dir.append(f)

print len(imgs_dir)
np.save('valid_images.out', imgs_dir)  

imgs_dir = np.load('valid_images.out.npy')

for f in imgs_dir:
  if not os.path.isdir('./val_img/'):
     os.makedirs('./val_img/')
  subFolder = './val_img/'
  shutil.move(os.path.join(path, f), subFolder)
