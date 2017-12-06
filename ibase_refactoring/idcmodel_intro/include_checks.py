#!/usr/bin/python

'''
Procedures for indirect checks
'''
from checks import CheckerFactory
from optparse import OptionParser


if __name__ == "__main__":
    
    parser = OptionParser()
    parser.add_option("--module-dir",  dest="module_dir", help="Specify path to the module to be checked (library or component's src)")
    parser.add_option("--idcmodel-h-files-lookup",  dest="idcmodel_h_files_lookup", help="Specify path to lookup file with all idcmodel header files.")
    parser.add_option("--gdi-h-files-lookup",  dest="gdi_h_files_lookup", help="Specify path to lookup file with gdi header files.")
    parser.add_option("--include-dirs",  dest="include_dirs", help="Specify list of include dirs comma separated.")
    
    (options, dummy) = parser.parse_args()
    
    if options.module_dir == None:
        print("Path to the module not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    if options.idcmodel_h_files_lookup == None:
        print("Path to the idcmodel-h-files lookup not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    if options.gdi_h_files_lookup == None:
        print("Path to the gdi-h-files-lookup lookup not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    if options.include_dirs == None:
        print("Comma separated list of include dirs of indirect header files.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    include_dirs = options.include_dirs.split(",")
    print include_dirs
    Checker = CheckerFactory.getChecker("standard_test", options.module_dir)
    Checker.setup()
    Checker.run(options.idcmodel_h_files_lookup, "libidccss30", check_type="include")
    Checker.run(options.gdi_h_files_lookup, "libgdi", check_type="include")
    Checker.printStatus()
     
    Checker.teardown()
    
    IncludeChecker = CheckerFactory.getChecker("indirect_test", options.module_dir, include_dirs)
    IncludeChecker.setup()
    IncludeChecker.run(options.idcmodel_h_files_lookup, "libidccss30", check_type="include")
    IncludeChecker.run(options.gdi_h_files_lookup, "libgdi", check_type="include")
    IncludeChecker.printStatus()
    IncludeChecker.teardown()
    
    