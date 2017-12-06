
def temporal_resampling(df, startdate, enddate, freq):
    '''
    Method for temporal resampling of CCI data in the ECV processor.
    
    Parameters:
    -----------
    df: Input data frame - sparial resampled CCI data.
        Expected following fields:
        [('jd', '<f8'), ('sm', '<f4'), ('sm_noise', '<f4'), 
        ('dir', 'i1'), ('pdb', 'i1'), ('ssf', 'i1'), 
        ('flag', 'i1'), ('nmeas', 'i1')]
    startdate: (datetime) start date
    enddate: (datetime) end date
    freq: frequency of time grid as input into pandas date_range.
    
    Returns:
    --------
    Temporally resampled Data Frame of the same structure as input.
    '''
    
    
    