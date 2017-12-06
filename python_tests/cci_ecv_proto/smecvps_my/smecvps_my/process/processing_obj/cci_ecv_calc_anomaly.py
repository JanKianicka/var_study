

def calculate_anomaly(sm_series, climatology):
    '''
    Method to calculate anomaly.
    
    Parameters:
    -----------
    sm_series: pandas_Series with input sm data for anomaly evaluation.
    climatology: pandas.Series with 1-366 climatology values.
    
    Returns:
    -------
    pandas.Series with anomaly.
    '''
    