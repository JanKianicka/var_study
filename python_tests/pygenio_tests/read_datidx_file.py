'''
Simple test script for reading dat, idx file created by ECV processor prototype of TU Wien.
'''

from pygenio import datasets
import matplotlib.pyplot as plt

if __name__ == '__main__':
    #input_dataidx_file = '/home/local/kianicka/projects/CCI/ECV_FILES/011_resampledTemporal/ascat/0673'
    input_dataidx_file = '/home/local/kianicka/projects/CCI/ECV_FILES/010_resampledSpatial/ascatssf/0673'
    #input_dataidx_file = '/home/local/kianicka/projects/CCI/ECV_FILES/060_monthlyAverage/combinedProd/0673'
    gpi = 720360
    
    
    print "Content of datasets: %s"%(dir(datasets))
    dat_obj = datasets.DatasetTs(input_dataidx_file)
    print "Content of DatasetTs object: %s"%(dir(dat_obj))

    print "Direct access to data:"
    print dat_obj.dat_data
    print "of type: %s"%(type(dat_obj.dat_data))
    print "of dtype: %s"%(dat_obj.dat_data.dtype)
    print "And what about number of GPIs: %s"%(dat_obj.idx_number_of_gpis)
    
    print "To get the data using function we need to know GPI number explicitely: %d"%(gpi)
    gpi_data = dat_obj.read_ts(gpi)
    
    sm = gpi_data[:]['sm']
    print "Got sm variable of dtype, shape: %s, %s"%(sm.dtype, sm.shape)
    
    print "And plot sm variable."
    wh = sm < -10
    sm[wh] = 0
    plt.plot(sm)
    plt.show()

    
    
    