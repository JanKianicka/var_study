import re

CONF_VARS = {'INCLUDE': "%s_INCLUDES=", 'DEPS': "%s_DEPS="}

conf_f = '/home/local/kianicka/repositories/ctbto/ibase/configure.ac'
code = 'ARSIO'
#code = 'BEAM'

dep_dict = {'GDI': False, 'IDCCSS30': True, 'AESIR': False}
include_pattern = "\{([a-zA-Z0-9]*)\_[a-zA-Z0-9]*\}"

f = open(conf_f, 'r')
lines = f.readlines()
for line in lines:
    #print line
    
    incl = line.find(CONF_VARS['INCLUDE']%code)
    if incl != -1:
        print "Original:"
        print line
        
        new_include_entries = []
        for item in line.split(" "):
            Matcher = re.search(include_pattern, item.strip())
            if Matcher:
                lib_name = Matcher.group(1)
                #checking and filling matching records 
                if dep_dict.has_key(lib_name):
                    if dep_dict[lib_name]:
                        new_include_entries.append(lib_name)
                else:
                    new_include_entries.append(lib_name)
                # add possibly missing AESIR
                if (lib_name == 'AESIR'):
                    new_include_entries.append(lib_name)
                
                # filling missing true entries 
                for key, is_dep in dep_dict.items():
                    if (is_dep and (new_include_entries.count(key)<1)):
                        new_include_entries.append(key)
                
        print new_include_entries
        # print new entries
        print "New entries: \n"
        for i in new_include_entries:
            print "${%s_INCLUDES}"%(i),
        print "\n"
        
        for i in new_include_entries:
            print "${%s_LIBS}"%(i),
        print "\n"
        
    deps = line.find(CONF_VARS['DEPS']%code)
    if deps != -1:
        print "Original DEPS line: "
        print line
        #print deps
    

f.close()