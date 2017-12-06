

def scale_sm_noise(sm_in, sm_noise_in, sm_scale_to):
    '''
    Method to scale sm_noise.
    
    Parameters:
    -----------
    sm_in: numpy.array with sm values adjacent to the
           sm_noise to be scaled.
    sm_noise_in: noise of sm to be scaled.
    sm_scale_to: sm values of the reference
    
    Return:
    ------
    numpy.array with scaled sm noise.
    '''