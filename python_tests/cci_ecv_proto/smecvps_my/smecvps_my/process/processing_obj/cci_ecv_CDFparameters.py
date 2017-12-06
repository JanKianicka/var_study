


def derive_CDF_parameters(in_data, scale_to, percentiles):
    '''
    Method for evaluating Cumulative Distribution Function (CDF)
    parameters to be used in scalling of the data.
    
    Parameters:
    ----------
    in_data: numpy array with "sm" input values to be scalled. 
    scale_to: reference "sm" data from the reference sensor.
    percentiles: numpy array with ordered percentiles the CDF 
                 function will be evaluated to.
    Return:
    -------
    cdf_pars: numpy array with fields: slope, intercept, 
              in_percetiles, scalled_percentiles.   
    '''
    