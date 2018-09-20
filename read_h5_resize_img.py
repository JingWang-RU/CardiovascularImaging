import h5py
import sys
import os
import matplotlib.pyplot as plt
from scipy.misc import imresize 
from scipy.misc import imsave
# author: Jing jiw2026@med.cornell.edu
# time: Sept. 20th 2018
# function: read h5 file with two keys, resize and save to png
# example: read_h5_resize_img.py *** D2 64
def read_h5_resize_img(pid, anas, resize):
  # design the name input pid should be like ***-***
  splitpid = pid.rsplit('-', 1)
  spid = splitpid[0].rjust(10,'0')# fill in with 0
  timestep = 'T' + splitpid[1]
  save_img = timestep + '_' + spid + '_' + anas
  f = h5py.File('./paradigm_paired/' + pid +'/Analysis' + anas + '/cmpr.h5', 'r')
  screenshot = f['screenshot'].value
  f.close()
  
  savepath = './Jingread/' + pid + '/' + anas + '/screen' + str(resize) + '/'
  if not os.path.exists(savepath):
    os.makedirs(savepath)
  for i in range(len(screenshot)):
    s = screenshot[i,:,:]
    re = imresize(s,(64,64))    
    imsave(savepath+save_img + '_' + str(i).rjust(3,'0')+'_'+str(resize)+'S.png', re)
 
  
if __name__ == "__main__":
   read_h5_resize_img(sys.argv[1], sys.argv[2], sys.argv[3])
  
