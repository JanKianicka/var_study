'''
Simple script to extract DB30 macros from libgdi array structs.
Ad-hoc implemented code manipulation utility. 

Date: 22.9.2015, Jan Kianicka
'''

import glob
from optparse import OptionParser
import os


START_TEXT_2_REMOVE = "#ifdef USE_DB30_MACROS"
END_TEXT_2_REMOVE   = "#endif /* USE_DB30_MACROS */"
ADD_REMOVE = "\"db30\" macros to convert libdb30 calls to libgdi calls"
MACROS_H_FILE = "db30_macros.h"

if __name__ == "__main__":
    print("Script to parse out macros from Array Structure header files.")
    
    parser = OptionParser()
    parser.add_option("--src_directory",  dest="src_directory", help="Specify directory with Array Struct header files")
    parser.add_option("--file_pattern",  dest="file_pattern", help="Specify pattern to extract header files")
    parser.add_option("--out_directory",  dest="out_directory", help="Specify output directory for output header files")
    
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
    
    f_macros_file = open(os.path.join(options.out_directory,MACROS_H_FILE), "a")
    f_macros_file.write(START_TEXT_2_REMOVE)
    
    for in_file in files:
        f = open(in_file)
        file_str = f.read()
    
        
        rmstr1 = file_str.find(START_TEXT_2_REMOVE)
        rmstr2 = file_str.find(END_TEXT_2_REMOVE)
        rmstr3 = file_str.find(ADD_REMOVE)
        print("Block to be removed: %d, %d, %d"%(rmstr1, rmstr2, rmstr3))    
            
        to_remove  = file_str[rmstr1:rmstr2+(len(END_TEXT_2_REMOVE))]
        to_remove2 = file_str[rmstr3-10:(rmstr3+len(ADD_REMOVE)+5)]

        file_str_out = file_str.replace(to_remove,"")
        file_str_out = file_str_out.replace(to_remove2,"")
        out_file = os.path.join(options.out_directory, os.path.basename(in_file))
        f_out = open(out_file,"w")
        f_out.write(file_str_out)
        print("Output written into: %s"%(out_file))
        
        
        # output to macros header file
        out_just_macros = to_remove.replace(START_TEXT_2_REMOVE, "\n")
        out_just_macros = out_just_macros.replace(END_TEXT_2_REMOVE, "\n")
        f_macros_file.write(out_just_macros)
    
    
    f_macros_file.write(END_TEXT_2_REMOVE)
    f.close()
    f_out.close()
    f_macros_file.close()
    
    
    
        
    