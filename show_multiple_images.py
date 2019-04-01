import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import os
# author: Jing Wang
# time: Jan. 2019 
# function: show images in one figure
w=10
h=10

epoch = 200
files = os.listdir('./predicted/')
columns = 6
rows = 3
for k in range(0, len(files)):
  tmp = files[k]
  name = tmp.split('_')
  img_name = name[0]+'_'+name[1]+'_'+name[2]
  
  count = 0;
  fig = plt.figure(frameon=False,figsize=(8,8))
  
  folders = ['original', 'groundtruth', 'predicted'+str(epoch)]
  f = 0
  for i in range(1, columns*rows+1):
     if i == 0 or i == 7 or i == 13:
        count = 0
        f = f+1
     #print(img_name+'  '+str(count))
     #print(folders[f])
     img = mpimg.imread('./'+ folders[f]+'/'+tmp+'/'+img_name + '_'+str(count)+'.png')
     fig.add_subplot(rows, columns, i)
     count = count + 30;
     plt.xticks([], [])
     plt.yticks([], [])

     plt.imshow(img)
  plt.suptitle(img_name + ' ' + str(epoch))
  #plt.show()
  fig.savefig('./combined' + str(epoch) +'/'+img_name+'_combined.png')
  plt.close()
