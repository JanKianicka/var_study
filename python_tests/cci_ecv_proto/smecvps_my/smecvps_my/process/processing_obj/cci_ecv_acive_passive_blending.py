


def blend_active_passive(active_data, passive_data,
                         rmap, vodmap, amiwscoverage,
                         porositymap):
    '''
    Method to perform final blending of acive and passive product.
    
    Parameters:
    acive_data: numpy.array with all required fields in dimensions
                [gpi, time] can contain block of GPIs.
    passive_date: numpy.array of the same structure and dimensions 
                  as active_data.
    rmap: numpy.array with active/passive reference correlation.
    vodmap: Vegetation Optical Depth map - numpy.array.
    amiwscoverige: auxiliary map of ami_ws coverage
    porositymap: numpy.array with porosity values.
    
    Return:
    numpy.array with combined product
    numpy.array with active product
    numpy.array with passive product
    numpy.array with output rmap
    numpy.array with output blanding map
    '''
    