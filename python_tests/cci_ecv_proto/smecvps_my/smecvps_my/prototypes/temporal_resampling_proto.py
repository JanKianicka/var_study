
from pygenio import datasets
import pytesmo.temporal_matching as tm
import pytesmo.timedate.julian as julian

import pandas as pd

import matplotlib.pyplot as plt
import os

def temp_resam(df, startdate, enddate, freq):
    ref_dr = pd.date_range(startdate, enddate, freq=freq)
    ref_df = pd.DataFrame(index=ref_dr)
    
    matched_df = tm.df_match(ref_df, df)
    return matched_df
    
    


if __name__ == '__main__':
    
    cur_path = os.path.abspath(os.path.curdir)
    input_dataidx_file = os.path.join(cur_path,'data/ascatssf/0673')
    
    gpi = 720360
    
    dat_obj = datasets.DatasetTs(input_dataidx_file)
    
    print dat_obj.dat_data.dtype
    print type(dat_obj.dat_data), dat_obj.dat_data.shape
    
    gpi_data = dat_obj.read_ts(gpi)
    print gpi_data.dtype, gpi_data.shape
    
    ref_dr = pd.date_range('1970-01-01 12:00:00', '2016-01-01 12:00:00', freq='D')
    ref_df = pd.DataFrame(index=ref_dr)
    
    ascat_dr = julian.julian2datetimeindex(gpi_data['jd'])
    ascat_df = pd.DataFrame(gpi_data, index=ascat_dr)
    matched_df = tm.df_match(ref_df, ascat_df)
    
    matched_df.plot()
    plt.show()
    pass
    