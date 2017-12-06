#!/usr/bin/python

'''
The module performs checks of the libraries and components for:
- whether there is direct dependency on idcmodel
- whether there is direct dependency on libgdi
It is using cscope tool and runs in subprocess calls.
'''

from optparse import OptionParser
import subprocess
import os
from abc import ABCMeta, abstractmethod
import re

CSOPE_FILES = "cscope.files"
FIND_COMMAND = "find %s -name \"*.c\" -o -name \"*.cpp\" -o -name \"*.h\" -o -name \"*.hpp\" > %s"
BUILD_DB = "cscope -q -R -b -i cscope.files"
CHECK_SYMBOL = "cscope -p4 -d -L -0 %s"
CHECK_INCLUDE = "cscope -p4 -d -L -6 %s"
EXP_FILES = [CSOPE_FILES, "cscope.out", "cscope.in.out", "cscope.po.out"]
INCLUDES_GREP_CMD = "grep '#include' %s/*[c,h]"
INCLUDE_PATTERN = "#include \"([a-zA-Z0-9\.]*)\""
INC_FILES_FILE = "cscope.files"


class CheckerFactory():
    
    @staticmethod
    def getChecker(check_type, module_path, include_dirs = None):
        if (check_type == "standard_test"):
            return StandardChecker(module_path)
        elif (check_type == "indirect_test"):
            return IndirectHeaderFilesChecker(module_path, include_dirs)
        else:
            print "%s not recognized as checker type."%(check_type)


class AbstractChecker():
    __metaclass__ = ABCMeta
    
    def __init__(self, module_path):
        self.module_path     = module_path
        self.collection_dict = {}
        self.check_type = "Undefined"
        
    @abstractmethod
    def setup(self):
        pass

    @abstractmethod
    def teardown(self):
        pass

    def run(self, path_to_symbols_list_file, dependency_name, check_type = "symbol"):
        
        self.check_type = check_type
        symbols2check = self._read_lookup4check(path_to_symbols_list_file)
        Out_dict = {}
    
        for symbol in symbols2check:
            
            if check_type == "symbol":
                check_command = CHECK_SYMBOL%(symbol)
            elif check_type == "include":
                check_command = CHECK_INCLUDE%(symbol)
            else:
                raise Exception("Unknown check type.")

            p = subprocess.Popen(check_command, shell=True, stdout=subprocess.PIPE)
            (stdoutdata, _) = p.communicate()
            if len(stdoutdata)>0:
                print check_command
                print stdoutdata
                Out_dict[symbol] = stdoutdata
        
        self.collection_dict[dependency_name] = Out_dict
        
    @abstractmethod 
    def printStatus(self):
        pass
    
    def get_collection_dict(self):
        return self.collection_dict

    def _read_lookup4check(self, lookup_file):
        f = open(lookup_file, "r")
        records = f.readlines()
        return records
        
class StandardChecker(AbstractChecker):
       
    def setup(self):
        find_command = FIND_COMMAND%(self.module_path, CSOPE_FILES)
        print find_command
    
        p = subprocess.Popen(find_command, shell=True, stdout=subprocess.PIPE)
        (stdoutdata, _) = p.communicate()
    
        build_db_command = BUILD_DB
        print build_db_command
 
        p = subprocess.Popen(build_db_command, shell=True, stdout=subprocess.PIPE)
        (stdoutdata, _) = p.communicate()
    
    def printStatus(self):
        print " --- Summary of direct dependencies checks --- "
        for key, out_dict in self.collection_dict.items():
                if len(out_dict.keys()) > 0:
                    print "%s has direct %s dependency on %s."%(os.path.basename(self.module_path), self.check_type, key)
                else:
                    print "%s has no direct %s dependency on %s."%(os.path.basename(self.module_path), self.check_type, key)
    
    def teardown(self):
        # Cleaning
        for csope_file in EXP_FILES:
            os.remove(csope_file)

class IndirectHeaderFilesChecker(AbstractChecker):
    
    def __init__(self, module_path, include_dirs):
        super(IndirectHeaderFilesChecker, self).__init__(module_path)
        self.include_dirs = include_dirs
        
    def setup(self):
        
        grep_cmd = INCLUDES_GREP_CMD%(self.module_path)
        
        p = subprocess.Popen(grep_cmd, shell=True, stdout=subprocess.PIPE)
        (stdoutdata, _) = p.communicate()
        print grep_cmd
    
        local_includes = []
    
        for line in stdoutdata.splitlines():
            Matcher = re.search(INCLUDE_PATTERN, line)
            if Matcher != None:
                header_file = Matcher.group(1)
                print header_file
                local_includes.append(header_file)
    
        # in order to have just unique values convert to set
        local_includes = set(local_includes)
        print local_includes
    
        h_files_to_check = []
        for h_file in local_includes:
            for include_dir in self.include_dirs:
                potential_h_file = os.path.join(include_dir,h_file).strip()
                if (os.path.isfile(potential_h_file)):
                    h_files_to_check.append(potential_h_file)
    
        print h_files_to_check
        #Check whether there are any entries for the cscope database
        if(len(h_files_to_check)<1):
            raise Exception("No include files to check matched.")
        
        f = open(INC_FILES_FILE, "w")
        for h_file in h_files_to_check:
            f.write("%s\n"%h_file)
    
        f.close()
    
        # create the database
        build_db_command = BUILD_DB
        print build_db_command
 
        p = subprocess.Popen(build_db_command, shell=True, stdout=subprocess.PIPE)
        (stdoutdata, _) = p.communicate()

    def printStatus(self):
        print " --- Summary of indirect (include header files) dependencies checks --- "
        for key, out_dict in self.collection_dict.items():
                if len(out_dict.keys()) > 0:
                    print "%s has indirect %s dependency on %s."%(os.path.basename(self.module_path), self.check_type, key)
                else:
                    print "%s has no indirect %s dependency on %s."%(os.path.basename(self.module_path), self.check_type, key)

    
    def teardown(self):
        # Cleaning
        for csope_file in EXP_FILES:
            os.remove(csope_file)

if __name__ == "__main__":
    
    parser = OptionParser()
    parser.add_option("--module-dir",  dest="module_dir", help="Specify path to the module to be checked (library or component's src)")
    parser.add_option("--astructs-lookup",  dest="astructs_lookup", help="Specify path to lookup file with arstructs type names.")
    parser.add_option("--gdi-lookup",  dest="gdi_lookup", help="Specify path to lookup file with gdi functions names.")
    
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
        
    Checker = CheckerFactory.getChecker("standard_test", options.module_dir)
    Checker.setup()
    Checker.run(options.astructs_lookup, "libidccss30")
    Checker.run(options.gdi_lookup, "libgdi")
    Checker.printStatus()
    
    Checker.teardown()
    
   
    
    
    
    
    
    
    