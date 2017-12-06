#!/usr/bin/python

'''
Script potting together all checks and to check also 
particular entries in configure.ac
'''
import os
import re
from optparse import OptionParser
from checks import CheckerFactory

from makefile_checker import AppMakefileChecker

DEP_KEYS = {'GDI':'libgdi', 
            'IDCCSS30':'libidccss30',
            'AESIR':None
            }
CONF_VARS = {'INCLUDE': "%s_INCLUDES=", 'DEPS': "%s_DEPS="}
include_pattern = "\{([a-zA-Z0-9\_]*)\_[a-zA-Z0-9]*\}"


class Evaluator():
    
    def __init__(self, module_dir, astructs_lookup, gdi_lookup, include_dirs,
                  idcmodel_h_files_lookup, gdi_h_files_lookup, aesir_struct_lookup, 
                  aesir_h_files_lookup):
        self.Dep_dict = {}
        for key in DEP_KEYS.keys():
            self.Dep_dict[key] = False
            
        self.module_dir = module_dir
        self.astructs_lookup = astructs_lookup
        self.gdi_lookup = gdi_lookup
        self.include_dirs = include_dirs
        self.idcmodel_h_files_lookup = idcmodel_h_files_lookup
        self.gdi_h_files_lookup = gdi_h_files_lookup
        self.aesir_struct_lookup = aesir_struct_lookup 
        self.aesir_h_files_lookup = aesir_h_files_lookup 
            
    def evaluateRetDict(self):
        for f in (self._standardChecks, self._indirectChecks, self._includeDirectChecks, self._includeIndirectChecks):
            try:
                ret_dict = f()
            except:
                print "No header files for indirect check or other error, proceeding ..."
                continue
            
            for lib_key, lib_name in DEP_KEYS.items():
                if (ret_dict.has_key(lib_name)):
                    if not self.Dep_dict[lib_key]:
                        self.Dep_dict[lib_key] = (False if len(ret_dict[lib_name])<1 else True)
        
        # AESIR evaluate separately due to 1-2 key-value
        Aesir_direct_check = self._aesirDirectChecks()
         
        self.Dep_dict['AESIR'] = (False if len(Aesir_direct_check["libaesir_structs"])<1 else True)
        if not self.Dep_dict['AESIR']:
            self.Dep_dict['AESIR'] = (False if len(Aesir_direct_check["libaesir_h_files"])<1 else True)
    
    def _standardChecks(self):
        Checker = CheckerFactory.getChecker("standard_test", self.module_dir)
        Checker.setup()
        Checker.run(self.astructs_lookup, "libidccss30")
        Checker.run(self.gdi_lookup, "libgdi")
        Checker.printStatus()
        Checker.teardown()
        
        return Checker.get_collection_dict()
    
    def _indirectChecks(self):
        include_dirs = self.include_dirs.split(",")
        print include_dirs
        IncludeChecker = CheckerFactory.getChecker("indirect_test", self.module_dir, include_dirs)
        IncludeChecker.setup()
        IncludeChecker.run(self.astructs_lookup, "libidccss30")
        IncludeChecker.run(self.gdi_lookup, "libgdi")
        IncludeChecker.printStatus()
        IncludeChecker.teardown()
    
        return IncludeChecker.get_collection_dict()
    
    def _includeDirectChecks(self):
        include_dirs = self.include_dirs.split(",")
        print include_dirs
        Checker = CheckerFactory.getChecker("standard_test", self.module_dir)
        Checker.setup()
        Checker.run(self.idcmodel_h_files_lookup, "libidccss30", check_type="include")
        Checker.run(self.gdi_h_files_lookup, "libgdi", check_type="include")
        Checker.printStatus()
        Checker.teardown()
    
        return Checker.get_collection_dict()
    
    def _includeIndirectChecks(self):    
        IncludeChecker = CheckerFactory.getChecker("indirect_test", self.module_dir, self.include_dirs)
        IncludeChecker.setup()
        IncludeChecker.run(self.idcmodel_h_files_lookup, "libidccss30", check_type="include")
        IncludeChecker.run(self.gdi_h_files_lookup, "libgdi", check_type="include")
        IncludeChecker.printStatus()
        IncludeChecker.teardown()
        
        return IncludeChecker.get_collection_dict()
    
    def _aesirDirectChecks(self):
        # Direct check for types(structures)
        Checker = CheckerFactory.getChecker("standard_test", self.module_dir)
        Checker.setup()
        Checker.run(self.aesir_struct_lookup, "libaesir_structs")
        Checker.run(self.aesir_h_files_lookup, "libaesir_h_files", check_type="include")
        Checker.printStatus()
        Checker.teardown()
    
        return Checker.get_collection_dict()
    
    def getDepDict(self):
        return self.Dep_dict

class LibConfigEntryChecker():
    
    def __init__(self, module_dir, configure_ac, dep_dict):
        self.module_dir = module_dir
        self.configure_ac = configure_ac
        self.dep_dict = dep_dict
        self.module_code = None
        self.config_lines = []
    
    def runCheck(self):
        self._getModuleCode()
        self._getConfigLines()
        for line in self.config_lines:
            incl = line.find(CONF_VARS['INCLUDE']%self.module_code)
            if incl != -1:
                print "Original INCLUDE line:"
                print line
                print "New entries: \n"
                for i in self._getNewVars(line):
                    print "${%s_INCLUDES}"%(i),
                print "\n"
            
            deps = line.find(CONF_VARS['DEPS']%self.module_code)
            if deps != -1:
                print "Original DEPS line: "
                print line
                print "New entries: \n"
                for i in self._getNewVars(line):
                    print "${%s_LIBS}"%(i),
                print "\n"
            
    def _getModuleCode(self):     
        self.module_code = os.path.basename(self.module_dir.replace('lib','')).upper()
        print self.module_code
    
    def _getConfigLines(self):
        # Checking configure.ac
        configure_f = open(self.configure_ac, "r")
        self.config_lines = configure_f.readlines()       
        configure_f.close()
    
    def _getNewVars(self, line):
                
        new_include_entries = []
        for item in line.split(" "):
            Matcher = re.search(include_pattern, item.strip())
            if Matcher:
                lib_name = Matcher.group(1)
                #checking and filling matching records 
                if self.dep_dict.has_key(lib_name):
                    if self.dep_dict[lib_name]:
                        new_include_entries.append(lib_name)
                else:
                    new_include_entries.append(lib_name)
                # add possibly missing AESIR
                if (lib_name == 'AESIR'):
                    new_include_entries.append(lib_name)
                
                # filling missing true entries 
                for key, is_dep in Dep_dict.items():
                    if (is_dep and (new_include_entries.count(key)<1)):
                        new_include_entries.append(key)
                
        #print new_include_entries
        new_include_entries_set = set(new_include_entries)
        new_include_entries = list(new_include_entries_set)
        new_include_entries.sort()
        print new_include_entries
        return new_include_entries
    

if __name__ == "__main__":
    
    parser = OptionParser()
    parser.add_option("--module-dir",  dest="module_dir", help="Specify path to the module to be checked (library or component's src)")
    parser.add_option("--astructs-lookup",  dest="astructs_lookup", help="Specify path to lookup file with arstructs type names.")
    parser.add_option("--gdi-lookup",  dest="gdi_lookup", help="Specify path to lookup file with gdi functions names.")
    parser.add_option("--idcmodel-h-files-lookup",  dest="idcmodel_h_files_lookup", help="Specify path to lookup file with all idcmodel header files.")
    parser.add_option("--gdi-h-files-lookup",  dest="gdi_h_files_lookup", help="Specify path to lookup file with gdi header files.")
    parser.add_option("--aesir-struct-lookup",  dest="aesir_struct_lookup", help="Specify path to lookup file with all tested aesir types.")
    parser.add_option("--aesir-h-files-lookup",  dest="aesir_h_files_lookup", help="Specify path to lookup file with tested aesir header files.")
    parser.add_option("--include-dirs",  dest="include_dirs", help="Specify list of include dirs comma separated.")
    parser.add_option("--configure-ac",  dest="configure_ac", help="Specify path to configure.ac with entries.")
    parser.add_option("--lib-app",  dest="lib_app", help="Specify \'lib\' for library, 'app' for application respectively.")
    
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
        print("Path to the gdi functions lookup not specified - this will not be performed.")
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
    
    if options.aesir_struct_lookup == None:
        print("Path to the aesir_struct_lookup lookup not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    if options.aesir_h_files_lookup == None:
        print("Path to the aesir_h_files_lookup lookup not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    if options.configure_ac == None:
        print("Path to configure.ac not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()

    if (options.lib_app == None or options.lib_app not in ('lib', 'app')) :
        print("Lib/App switch not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()

    Evaluator = Evaluator(options.module_dir, options.astructs_lookup, options.gdi_lookup, options.include_dirs, 
                          options.idcmodel_h_files_lookup, options.gdi_h_files_lookup, 
                          options.aesir_struct_lookup, options.aesir_h_files_lookup)
    Evaluator.evaluateRetDict()
    Dep_dict = Evaluator.getDepDict()
    
    print Dep_dict
    
    if (options.lib_app == 'lib'):
        LibConfigCheckerInst = LibConfigEntryChecker(options.module_dir, options.configure_ac, Dep_dict)
        LibConfigCheckerInst.runCheck()
    
    if (options.lib_app == "app"):
        make_file = os.path.join(options.module_dir, "Makefile.am")
        make_file_out = "%s_out"%make_file
        
        MkFileChecker = AppMakefileChecker(make_file, make_file_out, have_idccss30=Dep_dict['IDCCSS30'], have_gdi=Dep_dict['GDI'])
        MkFileChecker.runCheck()
    
    
    