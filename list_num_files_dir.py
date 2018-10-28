# author: jiw2026@med.cornell.edu
# time: Oct 27th 2018
# function: list number of files in dir
import os
def list_dir(path,savefile):
   w = open(savefile, 'w')
   for sub in os.listdir(path):
       num = len(os.listdir(path + sub))
       if num > 500:
         w.write(sub + "\n")
         #w.write(sub + " " + str(num) + "\n")
   w.close()

if __name__ == '__main__':
   path = './paradymDICOMpng/'
   savefile = 'test_file.txt'#'./stats_paradymDICOMpng.txt'
   list_dir(path, savefile)
