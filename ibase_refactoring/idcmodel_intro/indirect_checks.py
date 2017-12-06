#!/usr/bin/python

'''
Procedures for indirect checks
'''
from checks import CheckerFactory
from optparse import OptionParser


if __name__ == "__main__":
    
    parser = OptionParser()
    parser.add_option("--module-dir",  dest="module_dir", help="Specify path to the module to be checked (library or component's src)")
    parser.add_option("--astructs-lookup",  dest="astructs_lookup", help="Specify path to lookup file with arstructs type names.")
    parser.add_option("--gdi-lookup",  dest="gdi_lookup", help="Specify path to lookup file with gdi functions names.")
    parser.add_option("--include-dirs",  dest="include_dirs", help="Specify list of include dirs comma separated.")
    
    
    (options, dummy) = parser.parse_args()
    
    if options.module_dir == None:
        print("Path to the module not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    if options.astructs_lookup == None:
        print("Path to the astructs lookup not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    if options.gdi_lookup == None:
        print("Path to the gdi functions lookup not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    if options.include_dirs == None:
        print("Comma separated list of include dirs of indirect header files.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    include_dirs = options.include_dirs.split(",")
    print include_dirs
    IncludeChecker = CheckerFactory.getChecker("indirect_test", options.module_dir, include_dirs)
    IncludeChecker.setup()
    IncludeChecker.run(options.astructs_lookup, "libidccss30")
    IncludeChecker.run(options.gdi_lookup, "libgdi")
    IncludeChecker.printStatus()
    IncludeChecker.teardown()
    
    # Comments:
     
    # Now we will generate the database and perform two tests:
    # - standard test of symbols per module (idcmodel and libgdi) - done
    # - test of include tangling includes of libidccss30 h files or libgdi h files - this will be implemented in different script as optional when there is no dependency, just to verify 
    # even if no symbol is used.
    # - this test will be executed also for inside library testing - this will be one more test type
    # Yet has to extended to check of local array_structs with the same name and same header file name. - manual, but put echo about it
    # and for aesir abstract header files check yet - also optional - implemented in the separate script
    
    
    
    
    
    
    