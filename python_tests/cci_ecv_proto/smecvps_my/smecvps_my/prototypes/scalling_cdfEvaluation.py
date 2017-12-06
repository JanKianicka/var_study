from pygenio import datasets
import numpy as np
import scipy.interpolate as sc_int
from pytesmo import scaling
import matplotlib.pyplot as plt
import pandas as pd
import os

if __name__ == '__main__':
    cur_path = os.path.abspath(os.path.curdir)
    
    amsre_datfile = os.path.join(cur_path,"data/amsre/0673")
    tmi_datfile   = os.path.join(cur_path,"data/tmi/0673")
        
    print amsre_datfile
    
    gpi = 720360
    
    amsre_dat_obj = datasets.DatasetTs(amsre_datfile)
    amsre_gpi_data = amsre_dat_obj.read_ts(gpi)
    
    tmi_dat_obj = datasets.DatasetTs(tmi_datfile)
    tmi_gpi_data = tmi_dat_obj.read_ts(gpi)
    
    print amsre_gpi_data.dtype, amsre_gpi_data.shape
    print tmi_gpi_data.dtype, tmi_gpi_data.shape
    
    # In CDF evaluation should be only values without Nan
    wh = amsre_gpi_data['sm'] > -100;
    amsre_gpi_data['sm'][wh]
    wh2 =  tmi_gpi_data['sm'] > -100;
    tmi_gpi_data
    scalled_data = scaling.lin_cdf_match(tmi_gpi_data['sm'][wh2], amsre_gpi_data['sm'][wh])
    print tmi_gpi_data['sm'].shape
    print scalled_data.shape
    
    # Estimating the parameters
    in_data = tmi_gpi_data['sm'][wh2]
    scale_to = amsre_gpi_data['sm'][wh]
    print "In data:",in_data
    print "Scale to data:",scale_to
    
    percentiles = [0, 5, 10, 30, 50, 70, 90, 95, 100]

    in_data_pctl = np.array(np.percentile(in_data, percentiles))
    scale_to_pctl = np.array(np.percentile(scale_to, percentiles))
    
    uniq_ind = np.unique(in_data_pctl, return_index=True)[1]
    in_data_pctl = in_data_pctl[uniq_ind]
    scale_to_pctl = scale_to_pctl[uniq_ind]

    uniq_ind = np.unique(scale_to_pctl, return_index=True)[1]
    in_data_pctl = in_data_pctl[uniq_ind]
    scale_to_pctl = scale_to_pctl[uniq_ind]

    f = sc_int.interp1d(in_data_pctl, scale_to_pctl)
    print dir(f)
    print "Input percentiles:",in_data_pctl
    print "Scale to percentiles:", scale_to_pctl
    # Here should be evaluated slope and intercept of the existing funciton
    
    plt.plot(scalled_data)
    plt.plot(tmi_gpi_data['sm'][wh2])
     
    plt.show()
    
    
    # How this CDF function works?
    x_test = np.arange(2.0, 40.0)
    y_test = f(x_test)
    print x_test
    print y_test
    plt.plot(in_data_pctl, scale_to_pctl, "o", x_test, y_test, "-")
    plt.show()
    
    # Evaluation of second subinterval 
    # x1 ... y1
    # x2 ... y2
    # s = (y2 -y1)/(x2 - x1)
    # y1 = i + s*x1
    # i = (y1 - s*x1)
    x1 = in_data_pctl[1]
    x2 = in_data_pctl[2]
    
    y1 = scale_to_pctl[1]
    y2 = scale_to_pctl[2]
    slope = (y2 - y1)/(x2 - x1)
    x_test_1 = np.arange(10.0, 86.0)
    i = (y1 - slope*x1)
    print "slope, itercept 1:",slope,i 
    y_test_sl_int2 = i + slope*x_test_1
    print "Evaluated values for the first block second time:", y_test_sl_int2
    plt.plot(in_data_pctl, scale_to_pctl, "o", x_test_1, y_test_sl_int2, "-")
    plt.show()
    
    # Evaluation of slopes and intercepts for whole block
    slopes = (np.roll(scale_to_pctl,-1)[:-1] - scale_to_pctl[:-1])/(np.roll(in_data_pctl,-1)[:-1] - in_data_pctl[:-1])
    print "Block slopes:",slopes, slopes.shape
    intercepts = (scale_to_pctl[:-1] - slopes*in_data_pctl[:-1])
    print "Block intercepts:",intercepts, intercepts.shape
    
    # Using CDF function using intercepts and slopes
    x_test_1_pd = pd.DataFrame(x_test_1)
    y_test_sl_pd = x_test_1_pd.copy()
    
    for index, perc_intervals in enumerate(zip(in_data_pctl,np.roll(in_data_pctl,-1))[:-1]):
        print index, perc_intervals
        rule1 = x_test_1_pd >= perc_intervals[0]
        rule2 = x_test_1_pd <= perc_intervals[1]
        y_test_sl_pd[rule1 & rule2] = intercepts[index] + slopes[index]*x_test_1_pd[rule1 & rule2]
    
    plt.plot(in_data_pctl, scale_to_pctl, "o", x_test_1, y_test_sl_pd, "-")
    plt.show()
    
    # Here prototype evaluation of whole data span iterating over intervals
    tmi_in_data4test = tmi_gpi_data['sm'][wh2].copy()
    tmi_in_data4test_df = pd.DataFrame(tmi_in_data4test)
    scalled_data_2_df = tmi_in_data4test_df.copy()
    print tmi_in_data4test_df.describe()
    
    # The same algorithm as above - will be put to the function
    for index, perc_intervals in enumerate(zip(in_data_pctl,np.roll(in_data_pctl,-1))[:-1]):
        print index, perc_intervals
        rule1 = tmi_in_data4test_df >= perc_intervals[0]
        rule2 = tmi_in_data4test_df <= perc_intervals[1]
        scalled_data_2_df[rule1 & rule2] = intercepts[index] + slopes[index]*tmi_in_data4test_df[rule1 & rule2]
    
    # See it is exactly same graph 
    plt.plot(scalled_data_2_df)
    plt.plot(scalled_data)
    plt.show()
    
    
    
    