from pygenio import datasets
import pytesmo.time_series.anomaly as anomaly
import pytesmo.timedate.julian as julian

import pandas as pd

import matplotlib.pyplot as plt
import os

if __name__ == '__main__':
    cur_path = os.path.abspath(os.path.curdir)
    
    input_dataidx_file = os.path.join(cur_path,'data/ssmi/0673')
    
    gpi = 720360
    
    dat_obj = datasets.DatasetTs(input_dataidx_file)
    
    print dat_obj.dat_data.dtype
    print type(dat_obj.dat_data), dat_obj.dat_data.shape
    
    gpi_data = dat_obj.read_ts(gpi)
    print gpi_data.dtype, gpi_data.shape
    Ser = pd.Series(gpi_data['sm'], index=gpi_data['jd'])
    # Adjust the parameters
    climatology = anomaly.calc_climatology(Ser)
    print climatology
    climatology.plot()
    plt.show()
    
    anom = anomaly.calc_anomaly(Ser, climatology=climatology)
    
    anom.plot()
    plt.show()
    print anom
    