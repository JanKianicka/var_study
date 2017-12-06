from pygenio import datasets

if __name__ == '__main__':
    #input_dataidx_file = '/home/local/kianicka/projects/CCI/ECV_FILES/020_CDFParameterMerging/ers12/0673CDFPara'
    input_dataidx_file = '/home/local/kianicka/projects/CCI/ECV_FILES/040_CDFParameterBlending/active/0673CDFPara'
    
    #dat_obj = datasets.DatasetTs(input_dataidx_file)
    dat_obj = datasets.DatasetMp(input_dataidx_file)
    print dir(dat_obj)
    print dat_obj.dat_data, dat_obj.dat_filename, dat_obj.dat_maj_ver
    print dat_obj.meta_data
    print "of type: %s"%(type(dat_obj.dat_data))
    print "of dtype: %s"%(dat_obj.dat_data.dtype)
    
    data = dat_obj.read(0)
    print type(data), data.shape, data.dtype
    print data
    print dir(data)
    
    print "GPI:", data[2]
    print data.itemsize
    print data.item(0)
    
    print dat_obj.dat_data.dtype
    #Now it works, for return type of the read function it does not work.
    print dat_obj.dat_data[:]['gpi']
    print dat_obj.dat_data[:]['interc']
    print dat_obj.dat_data[:]['slope']
    print dat_obj.dat_data[:]['perc_src']
    #print dat_obj.dat_data[:]['somehting'] - not found
    
    # The questions are how to check over keys and how to distinguish dat file to be expected?
    # Is this type feasible as input to our computational objects?
    