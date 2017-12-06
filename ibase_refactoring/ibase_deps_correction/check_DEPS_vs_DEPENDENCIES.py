import re

# libaesir/  libcancomp/  libidcstream/  libidcstreamlog/  libidcsyslog/  libmseed/  libparidc/  libstdtime/    libsteim/  libtable/
cbase_list = ['AESIR','CANCOMP', 'IDCSTREAM','IDCSTREAMLOG', 'IDCSYSLOG', 'MSEED','PARIDC','STDTIME','STEIM','TABLE']

# libconvert/  libfilter/  libgeog/  libidcnumwf/  libloc/  libmagnitude/  libsigpolar/  libstanoise/
# libbeam/      libdataqc/   libfk/       libhae/   libinterp/    liblp/   libprob/       libspectra/     libwav/

sbase_list = ['CONVERT','FILTER','GEOG','IDCNUMWF','LOC','MAGNITUDE','SIGPOLAR','STANOISE',
              'BEAM','DATAQC','FK','HAE','INTERP','LP','PROB','SPECTRA','WAV']

idcmodel_list = ['IDCCSS30','IDCWFSTRUCTS', 'IDCCSS30QA']

libcd_list = ['CD']

# FLIBS should be also ignored
system_list = ['TCL','X','XAW','MOTIF','ORACLE','BLACKTIE','TUXEDO','APR','NETCDF','GMT','GSL','OPENSSL',
               'OPENLDAP','QT','PTHREAD','JAVA', 'FFTW3F']

just_symbols_list = ['DACS_IPC_INCLUDES','DACS_IPC_LIBS','DACS_IPC_DEPENDENCIES','INTERACTIVE_IPC_INCLUDES',
                     'INTERACTIVE_IPC_LIBS','INTERACTIVE_IPC_DEPENDENCIES']

DEPS_pattern = "([a-zA-Z0-9]*)\_DEPS="
DEPS_list_pattern = "\{([a-zA-Z0-9]*)\_[a-zA-Z0-9]*\}"
DEPENDENCIES_pattern = "([a-zA-Z0-9]*)\_DEPENDENCIES="
LIB_pattern = "\{LIB([a-zA-Z0-9]*)"
_DEP_pattern = "\{([a-zA-Z0-9]*)\_DEPENDENCIES"

if __name__ == "__main__":
    print("Started check of configure.as DEPS vs. DEPENDENCY variables.")
    # Fir we read confgure file
    configure_file = "/home/local/kianicka/repositories/prj_2016_ctbto_autoshi_sbase_impl2/ibase/configure.ac"
    configure_file_out = "/home/local/kianicka/repositories/prj_2016_ctbto_autoshi_sbase_impl2/ibase/configure.ac_out"
    
    in_f = open(configure_file,"r")
    out_f = open(configure_file_out, "w")
    
    in_lines = in_f.readlines()
    libkeys_dict = {}
    
    for line in in_lines:
        lib_DEPS_libraries = []
        DEPENDENCIES_LIB_libraries = []
        DEPENDENCIES_DEP_libraries = []
        
        Matcher = re.search(DEPS_pattern, line.strip())
        if Matcher:
            #print line
            libkeys_dict[Matcher.group(1)] = {}
            for item in line.split(" "):
                Matcher2 = re.search(DEPS_list_pattern, item.strip())
                if Matcher2:
                    #print Matcher2.group(0).split("_")[0][1:]
                    lib_name = Matcher2.group(1)
                    lib_DEPS_libraries.append(lib_name)
            
            #print "_DEPS= ",lib_DEPS_libraries
            libkeys_dict[Matcher.group(1)]["_DEPS="] = lib_DEPS_libraries 
    
        Matcher3 = re.search(DEPENDENCIES_pattern, line.strip())
        if Matcher3:
            #print line
            #print Matcher3.group(1) 
            for item in line.split(" "):
                Matcher4 = re.search(LIB_pattern, item.strip())
                if Matcher4:
                    #print "DEPS - groups:",Matcher4.groups()
                    lib_name = Matcher4.group(1)
                    DEPENDENCIES_LIB_libraries.append(lib_name)
            libkeys_dict[Matcher3.group(1)]["DEPENDENCIES_LIB"] = DEPENDENCIES_LIB_libraries
            
            for item in line.split("=")[1].split(" "):
                Matcher5 = re.search(_DEP_pattern, item.strip())
                if Matcher5:
                    #print "_DEPS - groups:",Matcher5.groups()
                    lib_name = Matcher5.group(1)
                    DEPENDENCIES_DEP_libraries.append(lib_name)
            libkeys_dict[Matcher3.group(1)]["DEPENDENCIES_DEP"] = DEPENDENCIES_DEP_libraries
            
            #print("_DEPENDENCIES LIB*: ",DEPENDENCIES_LIB_libraries)
            #print("_DEPENDENCIES *_DEPS: ",DEPENDENCIES_DEP_libraries)
            
            for exp_library in libkeys_dict[Matcher3.group(1)]["_DEPS="]:
                #print exp_library
                if DEPENDENCIES_LIB_libraries.count(exp_library) == 0 and system_list.count(exp_library)<1 \
                and cbase_list.count(exp_library) <1 and sbase_list.count(exp_library)<1 \
                and idcmodel_list.count(exp_library)<1 and libcd_list.count(exp_library)<1 \
                and DEPENDENCIES_LIB_libraries.count(Matcher3.group(1))<1 and DEPENDENCIES_DEP_libraries.count(Matcher3.group(1))<1:
                    print Matcher3.group(1)
                    missing_value = "${LIB%s}"%(exp_library)
                    print "Missing DEPENDENCY: %s"%missing_value
                    #print "_DEPS= ",lib_DEPS_libraries
                    #print("_DEPENDENCIES LIB*: ",DEPENDENCIES_LIB_libraries)
                    #print("_DEPENDENCIES *_DEPS: ",DEPENDENCIES_DEP_libraries)
                    print line
                
                if DEPENDENCIES_DEP_libraries.count(exp_library) == 0 and system_list.count(exp_library)<1 \
                and cbase_list.count(exp_library) <1 and sbase_list.count(exp_library)<1 \
                and idcmodel_list.count(exp_library)<1 and libcd_list.count(exp_library)<1 \
                and DEPENDENCIES_LIB_libraries.count(Matcher3.group(1))<1 and DEPENDENCIES_DEP_libraries.count(Matcher3.group(1))<1:
                    print Matcher3.group(1)
                    missing_value = "${%s_DEPENDENCIES}"%(exp_library)
                    print "Missing DEPENDENCY: %s"%missing_value
                    #print "_DEPS= ",lib_DEPS_libraries
                    #print("_DEPENDENCIES LIB*: ",DEPENDENCIES_LIB_libraries)
                    #print("_DEPENDENCIES *_DEPS: ",DEPENDENCIES_DEP_libraries)
                    print line
                    
            # Remove obsolete cbase variables
            for cbase_lib in cbase_list:
                if line.find(cbase_lib)>0:
                    print "Found obsolete cbase DEPENDENCY:",cbase_lib
                    print "Beeing removed."
                    print line
                    line = line.replace("${LIB%s} "%cbase_lib,"")
                    line = line.replace("${%s_DEPENDENCIES} "%cbase_lib,"")
                    line = line.replace(" ${%s_DEPENDENCIES}"%cbase_lib,"")
                    print line
              
            # Remove obsolete sbase variables
            for sbase_lib in sbase_list:
                if line.find("LIB%s"%sbase_lib)>0 or line.find("%s_DEPENDENCIES"%sbase_lib)>0:
                    print "Found obsolete sbase DEPENDENCY:", sbase_lib
                    print "Beeing removed."
                    print line
                    line = line.replace("${LIB%s} "%sbase_lib,"")
                    line = line.replace("${%s_DEPENDENCIES} "%sbase_lib,"")
                    line = line.replace(" ${%s_DEPENDENCIES}"%sbase_lib,"")
                    line = line.replace("${%s_DEPENDENCIES}"%sbase_lib,"")
                    print line

        out_f.write(line)

    in_f.close()
    out_f.close()
    
    
    