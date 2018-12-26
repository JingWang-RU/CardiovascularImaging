import Augmentor as aug


#date: Dec 20th 2019
#author: jing wang
#function: input directory of orginal and mask images, file with the same name
#          output the processed images in org/output/

img_dir = "./MSK/"#"./org/"
mask_dir = "./IMG/"#"./mask/"
p = aug.Pipeline( img_dir )
p.ground_truth ( mask_dir )

# Add operations to the pipeline as normal:

n = 4299*2 # 
'''
for x in xrange(0,1):
 #p.rotate_without_crop( probability = 1, max_left_rotation= x, max_right_rotation=0, expand=False )
 p.rotate90( probability = 1 ) 
 #p.rotate180( probability = 1 )
 #p.rotate270( probability = 1 )
 #p.rotate(probability=1, max_left_rotation=5, max_right_rotation=5)
 p.flip_left_right(probability=0.5)
 
 p.zoom(probability=1, min_factor=0.9, max_factor=1.5)
 p.flip_top_bottom(probability=0.5)
 
 p.sample( n )

for x in xrange(0,1):
 p.rotate180( probability = 1 )
 #p.rotate270( probability = 1 )
 #p.rotate(probability=1, max_left_rotation=5, max_right_rotation=5)
 p.flip_left_right(probability=0.5)
 
 p.zoom(probability=1, min_factor=0.9, max_factor=1.5)
 p.flip_top_bottom(probability=0.5)
 
 p.sample( n )
'''
for x in xrange(0,1):
 #p.rotate180( probability = 1 )
 p.rotate270( probability = 1 )
 p.flip_left_right(probability=0.5)
 
 p.zoom(probability=1, min_factor=0.9, max_factor=1.5)
 p.flip_top_bottom(probability=0.5)
 
 p.sample( n )


