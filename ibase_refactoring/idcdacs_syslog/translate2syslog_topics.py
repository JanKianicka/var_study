'''
Simple script to translate log messages to syslog topics
'''

import glob
from optparse import OptionParser
import os
import re

# Two parts, in the middle there will be the topic object
# Second part should match any string which could be in the printed statement


IDCDACS_LOG_PATTERN = ["(","\([\s]*printf\()([a-zA-Z0-9\s\<\>\_\(\)\"\:\%\,\-\.\;!(\)\;\#\*]*)"]
tst_pattern = '(SQL\([\s]*printf)([a-zA-Z0-9\s\<\>\_\(\)"\:\%\,\-\.\;\#\*]*)'
TRANSLATE_DICT = {"ALG":{"pattern":"", "replace":"fprintf (applog.ifo"},
                  "MSG":{"pattern":"", "replace":"fprintf (msglog.ifo"},
                  "SQL":{"pattern":"", "replace":"fprintf (sqllog.ifo"},
                  "TIME":{"pattern":"", "replace":"fprintf (tmelog.ifo"},
                  "RUN": {"pattern":"", "replace":"fprintf (runlog.ifo"}
                  }
# Looks like tme topic is not implemented - how time information shall be printed
# Will implemented as standard syslog topic, but we will miss timing information.

if __name__ == "__main__":
    print("Script translate legacy log macros to libidcstreamlog in idcdacs [c,h] files.")
    
    parser = OptionParser()
    parser.add_option("--src-directory",  dest="src_directory", help="Specify directory with C source files")
    parser.add_option("--file-pattern",  dest="file_pattern", help="Specify pattern")
    parser.add_option("--out-directory",  dest="out_directory", help="Specify output directory for output modified files")
    
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
    
    # Evaluation of patterns
    for key, diction in TRANSLATE_DICT.items():
        diction["pattern"] = "".join([IDCDACS_LOG_PATTERN[0],key,IDCDACS_LOG_PATTERN[1]])
    print TRANSLATE_DICT
    
    
    fullFilePattern = os.path.join(options.src_directory, options.file_pattern)   
    files = glob.glob(fullFilePattern)
    
    for in_file in files:
        f = open(in_file)
        f_out_path = os.path.join(options.out_directory, os.path.basename(in_file))
        f_out = open(f_out_path,"w")
        
        lines = f.readlines()
        out_lines = []
        stored = False
        replace_next_line = False
        
        for line in lines:
            if replace_next_line:
                line = line.replace(r") );"," );")
                line = line.replace(r"));"," );")
                replace_next_line = False
                
            stored = False
            for key, topic_dict in TRANSLATE_DICT.items():
                Matcher = re.search(topic_dict["pattern"], line)
                #Matcher = re.search(tst_pattern, line)
                if Matcher:
                    print line
                    #print Matcher.groups()
                    #print Matcher.group(1)
                    rest = Matcher.group(2)
                    print rest
                    line_new = re.sub(topic_dict["pattern"],"%s, %s"%(topic_dict["replace"], rest),line)
                    #print line_new
                    res = line.find(") );")
                    if (res == -1):
                        replace_next_line = True
                    line_new = line_new.replace(r") );"," );")
                    line_new = line_new.replace(r"));"," );")
                    print line_new
                    out_lines.append(line_new)
                    stored = True
                    break
            if not stored:
                out_lines.append(line)
                    
        f.close()
        f_out.writelines(out_lines)
        
