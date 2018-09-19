import h5py
import sys
import os
import matplotlib.pyplot as plt
import scipy.misc
# author: Jing jiw2026@med.cornell.edu
# time: Sept. 17th 2018
# function: read h5 file with two keys and save each data to png
# example: read_h5_to_img.py 18-1 D2
def read_h5_img(pid, anas):
  # design the name input pid should be like ***-***
  splitpid = pid.rsplit('-', 1)
  spid = splitpid[0].rjust(10,'0')# fill in with 0
  timestep = 'T' + splitpid[1]
  save_img = timestep + '_' + spid + '_'+anas
  f = h5py.File('./paradigm_paired/' + pid +'/Analysis' + anas + '/cmpr.h5', 'r')
  ''' 
  d = [n for n in f.keys()]
  for n in d:
   print d
  '''
  screenshot = f['screenshot'].value
  cmpr = f['cmpr'].value
  f.close()
  print("%d screenshot with size (%d,%d)" % (len(screenshot), len(screenshot[1,:,1]), len(screenshot[1,1,:])))
  print("%d cmpr with size (%d,%d)" % (len(cmpr), len(cmpr[1,:,1]), len(cmpr[1,1,:])))
  
  savepath = './Jingread/' + pid + '/' + anas + '/'
  if not os.path.exists(savepath+'screen/'):
    os.makedirs(savepath+'screen/')
  if not os.path.exists(savepath+'cmpr/'):
    os.makedirs(savepath+'cmpr/')
  for i in range(len(screenshot)):
    s = screenshot[i,:,:]
    c = cmpr[i,:,:]
    #plt.figure(i+1)
    #plt.imshow(c)
    #plt.show()
    #plt.savefig(savepath+str(i)+'s.png')
    #plt.imshow(c)#,cmap='gray')
    #plt.axis('off')
    #plt.savefig(savepath+str(i)+'c.png',bbox_inches='tight',dpi=500)
    scipy.misc.imsave(savepath+'cmpr/'+save_img + '_' + str(i).rjust(3,'0')+'_C.png',c)
    scipy.misc.imsave(savepath+'screen/'+save_img + '_' + str(i).rjust(3,'0')+'_S.png',s)
 
  
if __name__ == "__main__":
   read_h5_img(sys.argv[1], sys.argv[2])
  
