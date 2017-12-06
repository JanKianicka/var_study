

def scale_data(in_data, cdf_pars):
    '''
    Method to scale data using CDF parameters.
    
    Parameters:
    ----------
    in_data: numpy.arary, input sm data
    cdf_pars: CDF parameters, numpy.array with fields
              slope and intercept corresponding to 
              required percentiles.
    
    Returns:
    -------
    Numpy array with scalled "sm" data.
    
    '''
    