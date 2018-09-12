import tifffile as tiff
import matplotlib.pyplot as plt
from PIL import Image
import scipy.misc
import glob, os
# function: read tif and generate image 
# author: Jing jiw2026@med.cornell.edu
# time: August24, 2018
#file = 'DCM_10150799_20130205.tif'   
#dir = './d2/'
#dir = './lcx/'
#dir = './rpda/'
#dir = './lad/'
dir = './18-1/tree/'
for file in glob.glob(dir+"*.tif"):
  #file = 'volume.tif'
  #file = 'cmpr.tif'
  a = tiff.imread( file )
   
  print a.shape # (243,512,512)
  
  print a.dtype # dtype('uint16')
  
  folder = file[:-4] +'Tif/';
  #im = Image.fromarray(a[1,:,:])
  
  if not os.path.exists( folder ):
     os.makedirs( folder )
  
  for i in range(0, a.shape[0]):
     scipy.misc.imsave( folder + 'S%06d.jpg'%i, a[i,:,:])
  
'''
fig = plt.figure(1)#figsize = (9,7) )
#plt.imshow(a[1,:,:], cmap='Greys_r')
#plt.show()

#ax1 = fig.add_subplot( 1, 2, 1 )
plt.imshow( a[1,:,:] )#, cmap = 'Greys_r' )
fig.show()

gig = plt.figure(2)
#ax2 = fig.add_subplot( 1, 2, 2 )
#ax2.imshow( a[200,:,:] )#, cmap = 'Greys_r' )
plt.imshow( a[200,:,:] )
gig.show()
'''
