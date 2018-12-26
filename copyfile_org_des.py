from shutil import copyfile
import os
# author Jing
# time Dec 20 2018
# function copy files satisfying the criterion in names from src_dir to dst_dir

#src_dir = "/data/Jing/Patricia/MedisImgMask/Mask/"

src_dir = "***Images/vessels_64x64_static_3categories/"
#dst_dir = "****/rg_aug/"
dst_dir = "***/Augmentor/medis_aug/Test_IMG/"
#file = open("train_3_class_org.txt", "r").read().split('\n');
file = open("test_3_class_org.txt", "r").read().split('\n');

#dst_dir = "/mask_aug/"
#file = open("train_3_class_mask.txt", "r").read().split('\n');
#file = open("test_3_class_mask.txt", "r").read().split('\n');
for temp in file:
  filename = temp[1:-1];
  #print filename
  
  filename.split(" ")
  src = os.path.join(src_dir, filename)
  dst = os.path.join(dst_dir, filename) 
  print src
  copyfile(src, dst)
  
'''
src_dir = './MSK/'
for i, filename in enumerate(os.listdir(src_dir)):
    #print filename
    newfilename = filename
    
    newfilename.replace( "_MS.png", "_C.png" )
    print newfilename
    os.rename( src_dir + filename, src_dir + newfilename )
'''
