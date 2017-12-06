'''
Simple script to translate different log messages of idcdacs.
- "fprintf(stderr|stdout,"
- "printf("
- "printlog"

There will be used replacing by pattern matching and testing occurrence of words in the message body.
1. topic will be set by provided files subselection
2. severity by evaluation of key words tailored for particular library. 

'''
import glob
from optparse import OptionParser
import os
import re


fprintf_pattern = '(fprintf\([\s]*stderr,|fprintf\([\s]*stdout,)([a-zA-Z0-9\s\n\<\>\_\(\)\"\:\%\,\-\.\;\#\*\?\=\&\\\]*)'
# printf_pattern  = '( printf\()([a-zA-Z0-9\s\n\<\>\_\(\)\"\:\%\,\-\.\;\#\*\?\=\&]*)' - used for remnants for print statements
printf_pattern  = '(\tprintf\()([a-zA-Z0-9\s\n\<\>\_\(\)\"\:\%\,\-\.\;\#\*\?\=\&]*)'
printlog_pattern_all = '(printlog\(ALLP,)([a-zA-Z0-9\s\n\<\>\_\(\)"\:\%\,\-\.\;\#\*\?\=\&]*)'
printlog_pattern_debug = '(printlog\(DEBUGP,)([a-zA-Z0-9\s\n\<\>\_\(\)"\:\%\,\-\.\;\#\*\?\=\&]*)'
printlog_pattern_norm = '(printlog\(NORMP,)([a-zA-Z0-9\s\n\<\>\_\(\)"\:\%\,\-\.\;\#\*\?\=\&]*)'

Error_keywords   = ['Error','error','abnormal','exception', 'ERROR']
Warning_keywords = ['Warning','warning','Warn','warn']
Debug_keywords   = ['trace','debug']

'''
"trace" -> trclog topic, trnaslated to dg1
"debug" -> severity db1
'''
TEST_CASES = {1:{"re_pattern":fprintf_pattern,"contains": Error_keywords, "replace": "fprintf (%s.err"},
              2:{"re_pattern":fprintf_pattern,"contains": Warning_keywords, "replace": "fprintf (%s.wrn"},
              3:{"re_pattern":fprintf_pattern,"contains": Debug_keywords,  "replace": "fprintf (%s.db1"},
              4:{"re_pattern":fprintf_pattern,"contains": None,  "replace": "fprintf (%s.ifo"},
              5:{"re_pattern":printf_pattern,"contains":  Error_keywords, "replace": "        fprintf (%s.err"},
              6:{"re_pattern":printf_pattern,"contains":  Warning_keywords, "replace":"        fprintf (%s.wrn"},
              7:{"re_pattern":printf_pattern,"contains":  Debug_keywords,  "replace":"        fprintf (%s.db1"},
              8:{"re_pattern":printf_pattern,"contains":  None,  "replace":"        fprintf (%s.ifo"},
              # valid for idcdacs only - 9:{"re_pattern":printlog_pattern,"contains":  None, "replace":"fprintf (%s.wrn"} #this is because printlog statements in libidcdacs are only of type of warning
              9:{"re_pattern":printlog_pattern_all,"contains":  None, "replace":"fprintf (%s.ifo"},
              10:{"re_pattern":printlog_pattern_debug,"contains":  None, "replace":"fprintf (%s.dg1"},
              11:{"re_pattern":printlog_pattern_norm,"contains":  None, "replace":"fprintf (%s.ifo"},
              }

if __name__ == "__main__":

    parser = OptionParser()
    parser.add_option("--src-directory",  dest="src_directory", help="Specify directory with C source files")
    parser.add_option("--file-pattern",  dest="file_pattern", help="Specify pattern")
    parser.add_option("--out-directory",  dest="out_directory", help="Specify output directory for output modified files")
    parser.add_option("--syslog-topic",  dest="syslog_topic", help="Specify syslog topic which should match with file pattern.")
    
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
        
    if options.syslog_topic == None:
        print("syslog_topic not specified.")
        print("For usage information type <scriptname.py> -h")
        exit()
    
    print("Ran translate_other_statements.py with:")
    print("src_directory: %s"%(options.src_directory))
    print("file_pattern: %s"%(options.file_pattern))
    print("out_directory: %s"%(options.out_directory))
    print("syslog_topic: %s"%(options.syslog_topic))
    
    fullFilePattern = os.path.join(options.src_directory, options.file_pattern)   
    files = glob.glob(fullFilePattern)
    
    for in_file in files:
        print in_file
        f = open(in_file)
        f_out_path = os.path.join(options.out_directory, os.path.basename(in_file))
        f_out = open(f_out_path,"w")
        
        lines = f.readlines()
        out_lines = []
        line_counter = 0
        
        for line in lines:
            #print line
            line_new = line
            b = False
            was_matcher = False
            for case, case_dict in TEST_CASES.items():
                Matcher = re.search(case_dict["re_pattern"], line)
                if Matcher:
                    was_matcher = True
#                     print line
                    print Matcher.groups(), len(Matcher.groups())
                    rest = Matcher.group(2)
#                   print repr(rest)
                    line_new = re.sub(case_dict["re_pattern"],"%s, %s"%(case_dict["replace"]%(options.syslog_topic), repr(rest)[1:-1] ),line)
                    if case_dict["contains"] != None:
                        for word2test in case_dict["contains"]:
                            # check second and third line
                            if ((line_counter+2) < len(lines)):
                                line_second = lines[line_counter+1]
                                line_third  = lines[line_counter+2]
                                if (line.strip()[-2:] != ");"):
                                    if ((line_second.find(word2test) != -1) or (line_third.find(word2test) != -1)):
                                        line_new = re.sub(case_dict["re_pattern"],"%s, %s"%(case_dict["replace"]%(options.syslog_topic), repr(rest)[1:-1] ),line)
                                        b = True
                                        break
                            if rest.find(word2test) != -1:
                                line_new = re.sub(case_dict["re_pattern"],"%s, %s"%(case_dict["replace"]%(options.syslog_topic), repr(rest)[1:-1]),line)
                                b = True
                                break
                    if b:
                        break
            if (b or was_matcher):
                print line
                print line_new
            
            out_lines.append(line_new)
            line_counter += 1
                        
        f.close()
        f_out.writelines(out_lines)
        f_out.close()
    
    
    