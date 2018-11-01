import h5py
import sys
import os
import matplotlib.pyplot as plt
import scipy.misc


# author: Jing jiw2026@med.cornell.edu
# time: Nov. 1st 2018
# function: read ID/vessel/h5 file with two keys and save each data to png
def read_h5_file_img(h5_path, savepath, save_img):
    # design the name input pid should be like ***-***

    f = h5py.File(h5_path, 'r')
    screenshot = f['screenshot'].value
    cmpr = f['cmpr'].value
    f.close()
    print("%d screenshot with size (%d,%d)" % (len(screenshot), len(screenshot[1, :, 1]), len(screenshot[1, 1, :])))
    print("%d cmpr with size (%d,%d)" % (len(cmpr), len(cmpr[1, :, 1]), len(cmpr[1, 1, :])))

    if not os.path.exists(savepath + 'screen/'):
        os.makedirs(savepath + 'screen/')
    if not os.path.exists(savepath + 'cmpr/'):
        os.makedirs(savepath + 'cmpr/')
    for i in range(len(screenshot)):
        s = screenshot[i, :, :]
        c = cmpr[i, :, :]
        # plt.figure(i+1)
        # plt.imshow(c)
        # plt.show()
        # plt.savefig(savepath+str(i)+'s.png')
        # plt.imshow(c)#,cmap='gray')
        # plt.axis('off')
        # plt.savefig(savepath+str(i)+'c.png',bbox_inches='tight',dpi=500)
        scipy.misc.imsave(savepath + 'cmpr/' + save_img + '_' + str(i).rjust(3, '0') + '_C.png', c)
        scipy.misc.imsave(savepath + 'screen/' + save_img + '_' + str(i).rjust(3, '0') + '_S.png', s)

def vessel_per_id(path, dest_path):
    for id_path in os.listdir(path):
        splitpid = id_path.rsplit('-', 1)
        spid = splitpid[0].rjust(10, '0')  # fill in with 0
        timestep = 'T' + splitpid[1]
        for vessel_path in os.listdir(path+'/'+id_path):
            if '_' in vessel_path:
               vessel_name = vessel_path.rsplit('_')[1]
            else:
               vessel_name = vessel_path[8:] # AnalalysisLCD or Analysis_LCD
            vessel_file = path + id_path + '/' + vessel_path + '/cmpr.h5'
            save_path = dest_path + id_path + '/' + vessel_name + '/'
            save_img = timestep + '_' + spid + '_' + vessel_name
            read_h5_file_img(vessel_file, save_path, save_img)

if __name__ == "__main__":
    path = '/data/DATASETS/PARADIGM/cleerly/paradigm_paired/';
    dest_path = '../images/';
    vessel_per_id(path, dest_path)
    #read_h5_img(sys.argv[1], sys.argv[2])

