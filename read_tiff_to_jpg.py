import tifffile as tiff
import matplotlib.pyplot as plt
from PIL import Image
import scipy.misc
import os

# function : read the tif file and save each slice to jpg
# created : Aug 24 2018
# author : Jing

#dir = './d2/'
dir = './lcx/'
file = 'volume.tif'
#file = 'cmpr.tif'
a = tiff.imread( dir+file )
 
print a.shape # (243,512,512)

print a.dtype # dtype('uint16')

folder = file[:-4] +'Tif/';# /volumTif/
#im = Image.fromarray(a[1,:,:])

if not os.path.exists( dir + folder ):
   os.makedirs( dir + folder )

for i in range(0, a.shape[0]):
   scipy.misc.imsave( dir + folder + 'S%06d.jpg'%i, a[i,:,:])

'''
fig = plt.figure(1)#figsize = (9,7) )
#plt.imshow(a[1,:,:], cmap='Greys_r')
#plt.show()

'''
