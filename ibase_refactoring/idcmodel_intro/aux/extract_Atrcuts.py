'''
Small utility to create lists of all array structs. 
'''
import glob
from optparse import OptionParser
import os
import re

structure_name_pattern = '\}([a-zA-Z0-9_]*);'

if __name__ == "__main__":
    print("Script to parse out macros Array Structure types and create list in the lookup file.")
    
    parser = OptionParser()
    parser.add_option("--src_directory",  dest="src_directory", help="Specify directory with Array Struct header files ")
    parser.add_option("--file_pattern",   dest="file_pattern",  help="Specify pattern to extract structure names ")
    parser.add_option("--out_directory",  dest="out_directory", help="Specify output directory for list output ")
    
    (options, dummy) = parser.parse_args()
    
    if options.src_directory == None:
        print("src_directory not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
        
    if options.file_pattern == None:
        print("file_pattern not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()

    if options.out_directory == None:
        print("out_directory not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    fullFilePattern = os.path.join(options.src_directory, options.file_pattern)   
    files = glob.glob(fullFilePattern)
    files.sort()
    
    f_out = open(os.path.join(options.out_directory, "ArrayStructures_list"), "w")
    # Here comes listing through files and extracting structure name
    # using regular expression.
    
    for header_file in files:
        print header_file
        f = open(header_file, "r")
        file_str = f.read()
        Matcher = re.search(structure_name_pattern,file_str)
        Arrastr_name = Matcher.group(1)
        print Arrastr_name
        f_out.write("%s\n"%Arrastr_name)
    
    f_out.close()
    
    
    
