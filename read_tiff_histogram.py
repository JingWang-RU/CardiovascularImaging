# author: Jing jiw2026@med.cornell.edu
# time: Nov. 14 2018
# function: find hounsfield unit from volume image
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
import sys

def image_hist(tif_path, name, save_png):
    #print(tif_path)
    im = Image.open(tif_path)
    imarray = np.array(im)
     
    plt.hist(imarray.ravel(), bins='auto')
    plt.title(name)
    plt.savefig(save_png)
    plt.show()    

def main(argv):
   image_hist(sys.argv[1], sys.argv[2], sys.argv[3])

if __name__ == "__main__":
   main(sys.argv[1:])
      
