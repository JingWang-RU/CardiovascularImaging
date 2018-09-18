import h5py
import sys
import os
import matplotlib.pyplot as plt
# author: Jing jiw2026@med.cornell.edu
# time: Sept. 17th 2018
# function: read h5 file with two keys and save the data to png
anas = 'D2'#'LCX'
f=h5py.File('./paradigm_paired/***/Analysis'+anas+'/cmpr.h5', 'r')

d = [n for n in f.keys()]
for n in d:
 print d

screenshot= f['screenshot'].value
cmprs = f['cmpr'].value
#print len(screenshot) #325
#print len(cmprs) #325
#print sys.getsizeof(screenshot)#5476919
#print sys.getsizeof(cmprs)
#print len(screenshot[1,:,1]) #237
#print len(screenshot[1,1,:]) #237
#print len(cmprs[1,:,1])      #64
#print len(cmprs[1,1,:])      #64
savepath = './Jingread/***/'+anas+'/'
if not os.path.exists(savepath):
  os.makedirs(savepath)
for i in range(len(screenshot)):
  s = screenshot[i,:,:]
  c = cmprs[i,:,:]
  #plt.figure(i)
  plt.imshow(s) 
  #plt.figure(i+1)
  #plt.imshow(c)
  #plt.show()
  plt.savefig(savepath+str(i)+'screen.png')
  plt.imshow(c)
  plt.savefig(savepath+str(i)+'cmp.png')
f.close()
