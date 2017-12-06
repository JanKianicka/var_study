
from pygenio import datasets
import matplotlib.pyplot as plt
import numpy as np
import os

if __name__ == "__main__":
    
    cur_path = os.path.abspath(os.path.curdir)
    
    blending_map_datafile = os.path.join(cur_path,'data/blending_map/0673_BlMap')
    rmpa_data_file        = os.path.join(cur_path,'data/rmap/0673_RMap')
    
    gpi =720378
    dat_obj = datasets.DatasetMp(blending_map_datafile)
    print dat_obj.dat_data.shape
    print dat_obj.dat_data.dtype
    print dat_obj.read(gpi, is_gpi=True)
    print dat_obj.dat_data
    
    #Rmape 
    dat_obj_Rmap = datasets.DatasetMp(rmpa_data_file)
    print dat_obj_Rmap.dat_data.shape
    print dat_obj_Rmap.dat_data.dtype
    print dat_obj_Rmap.read(gpi, is_gpi=True)
    print dat_obj_Rmap.dat_data
    
    reshaped_data = np.reshape(dat_obj.dat_data['prod_id'][:,3], [20,20])
    plt.imshow(reshaped_data)
    plt.show()