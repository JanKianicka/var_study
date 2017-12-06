#!/usr/bin/python

'''
Procedures for libaesir checks - for ArrayStructures abstract types.
'''
from checks import CheckerFactory
from optparse import OptionParser


if __name__ == "__main__":
    
    parser = OptionParser()
    parser.add_option("--module-dir",  dest="module_dir", help="Specify path to the module to be checked (library or component's src)")
    parser.add_option("--aesir-struct-lookup",  dest="aesir_struct_lookup", help="Specify path to lookup file with all tested aesir types.")
    parser.add_option("--aesir-h-files-lookup",  dest="aesir_h_files_lookup", help="Specify path to lookup file with tested aesir header files.")
    parser.add_option("--include-dirs",  dest="include_dirs", help="Specify list of include dirs comma separated.")
    
    (options, dummy) = parser.parse_args()
    if options.module_dir == None:
        print("Path to the module not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    if options.aesir_struct_lookup == None:
        print("Path to the aesir_struct_lookup lookup not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    if options.aesir_h_files_lookup == None:
        print("Path to the aesir_h_files_lookup lookup not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    if options.include_dirs == None:
        print("Comma separated list of include dirs of indirect header files.")
        print("For usage information type <scriptname.py> -h")
        exit()
    

    include_dirs = options.include_dirs.split(",")
    print include_dirs

    # Direct check for types(structures)
    Checker = CheckerFactory.getChecker("standard_test", options.module_dir)
    Checker.setup()
    Checker.run(options.aesir_struct_lookup, "libaesir_structs")
    Checker.run(options.aesir_h_files_lookup, "libaesir_h_files", check_type="include")
    Checker.printStatus()
    Checker.teardown()
    
    #Indirect checks for include files
    IncludeChecker = CheckerFactory.getChecker("indirect_test", options.module_dir, include_dirs)
    IncludeChecker.setup()
    IncludeChecker.run(options.aesir_struct_lookup, "libaesir_structs")
    IncludeChecker.run(options.aesir_h_files_lookup, "libaesir_h_files", check_type="include")
    IncludeChecker.printStatus()
    IncludeChecker.teardown()
    
        
     
    
    
    