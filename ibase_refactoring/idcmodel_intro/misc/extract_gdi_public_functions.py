'''
Simple script to extract set of function names to be tested.
'''
from optparse import OptionParser
import subprocess
import os
import re

public_function_pattern = ' T ([a-zA-Z0-9_]*)$'

if __name__ == "__main__":
    print("Script retrieve list of public functions from *.a library file using 'nm'")
    
    parser = OptionParser()
    parser.add_option("--library_file",  dest="library_file", help="Specify path to the library *.a file")
    parser.add_option("--out_directory",  dest="out_directory", help="Specify output directory for list output ")
    
    (options, dummy) = parser.parse_args()
    
    if options.library_file == None:
        print("Input library file not specified")
        print("For usage information type <scriptname.py> -h")
        exit()

    if options.out_directory == None:
        print("out_directory not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()

    cmd = "nm --defined-only %s"%(options.library_file)
    print cmd
    p = subprocess.Popen(["nm", "--defined-only", options.library_file], stdout=subprocess.PIPE)
    (stdoutdata, _) = p.communicate()

    f_out = open(os.path.join(options.out_directory, "libgdi_pubfun_list"), "w")

    for line in stdoutdata.splitlines():
        print line
        Matcher = re.search(public_function_pattern, line)
        if Matcher != None:
            pub_function = Matcher.group(1)
            print pub_function
            f_out.write("%s\n"%pub_function)
    
    f_out.close()
            
            
            
            
            
        