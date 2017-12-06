'''
Short script to collect binaries and libraries by comparison
of install repository and installed artifacts in DVL runtime.
1. Read all files into lists
2. Go through entries in /dvl 'bin' and 'lib' directories and find them in the install repo
3. If found add it to the dictionary with keyword representing repository (root directory).
4. If not found add it to the list of not found items.
5. Print out the output.
'''
import os

if __name__ == "__main__":
    print "Starting processing of files."
    
    install_repo_file   = "/home/local/kianicka/projects/SHI_Support/ICRRelease16.9.1/install_devlan_clean.filelist.txt"
    dvl_bin_file        = "/home/local/kianicka/projects/SHI_Support/ICRRelease16.9.1/dvl_rel_fileslist.txt"
    dvl_lib_file        = "/home/local/kianicka/projects/SHI_Support/ICRRelease16.9.1/dvl_lib_filelist.txt"
    out_file            = "/home/local/kianicka/projects/SHI_Support/ICRRelease16.9.1/IDCRelease16.9.1_rel_inputs.txt"
    
    f_install = open(install_repo_file)
    install_repo_files_list = f_install.readlines()
    f_install.seek(0,0)
    install_repo_string = f_install.read()
    
        
    f_bin = open(dvl_bin_file)
    bin_files_list = f_bin.readlines()
    
    f_lib = open(dvl_lib_file)
    lib_files_list = f_lib.readlines()
    
    f_install.close()
    f_bin.close()
    f_lib.close()
    
    print "install_repo_files_list len:",len(install_repo_files_list)
    
    #for line in install_repo_files_list:
    #    print line
    print "bin_files_list len:",len(bin_files_list)
    print "lib_files_list len:",len(lib_files_list)
    
    dvl_super_list = bin_files_list + lib_files_list 
           
    print "dvl_super_list len:", len(dvl_super_list)
    
    #prepare dictionay of install repo entries
    install_repo_dict = {}
    for entry in install_repo_files_list:
        split_entry = os.path.dirname(entry).split('/')
        if len(split_entry) > 1:
            install_repo_dict[split_entry[1]] = []
    
    for entry in install_repo_files_list:
        split_entry = os.path.dirname(entry).split('/')
        if len(split_entry) > 1:
            install_repo_dict[split_entry[1]].append(os.path.basename(entry).strip())
    for key, item in install_repo_dict.items():
        # print key
        # print item
        pass
    
    not_found_list = []
    output_found_dict = {}
    # Fill the output with keys
    for repo in install_repo_dict.keys():
        output_found_dict[repo] = dict()
        output_found_dict[repo]['basename'] = dict()
        output_found_dict[repo]['fullname'] = dict()
        output_found_dict[repo]['basename']['libs'] = []
        output_found_dict[repo]['basename']['exec'] = []
        output_found_dict[repo]['fullname']['libs'] = []
        output_found_dict[repo]['fullname']['exec'] = []
        
    for bin_lib in dvl_super_list:
        base_name = os.path.basename(bin_lib).strip()
        if base_name in install_repo_string:
            # Here implement index in the list and if raised excetion, continue to the next one
            # if not raised add it to the list of installed items
            for repo, install_bin_lib_list in install_repo_dict.items():
                try:
                    install_bin_lib_list.index(base_name)
                    if 'lib' == base_name[:3]: 
                        output_found_dict[repo]['basename']['libs'].append(base_name)
                        output_found_dict[repo]['fullname']['libs'].append(bin_lib)
                    else:
                        output_found_dict[repo]['basename']['exec'].append(base_name)
                        output_found_dict[repo]['fullname']['exec'].append(bin_lib)
                        #print base_name
                except:
                    # print "Not found."
                    pass
        else:
            not_found_list.append(bin_lib)
    
    # Remove duplicates and sort them alphabetically 
    for repo, subdict in output_found_dict.items():
        subdict['basename']['libs'] = list(set(subdict['basename']['libs']))
        subdict['basename']['exec'] = list(set(subdict['basename']['exec']))
        subdict['basename']['libs'].sort()
        subdict['basename']['exec'].sort()
        
        subdict['fullname']['libs'].sort()
        subdict['fullname']['exec'].sort()
    
    print "Content of /dvl/software/shi/bin, /dvl/software/shi/lib: "
    
    repos = output_found_dict.keys()
    repos.sort()
    
    # opening and wrting also to the output file
    f_out = open(out_file,"w")
    
    for repo in repos:
        if repo not in ['.git','X11','rnaux','rnpicker','rnpipeline','staapp'] and (len(output_found_dict[repo]['basename']['libs'])>0 or len(output_found_dict[repo]['basename']['exec'])>0) :
            print "%s"%(repo)
            print "-" * len(repo)
            f_out.write("%s\n"%(repo))
            f_out.write("-" * len(repo))
            f_out.write("\n")
            
            if len(output_found_dict[repo]['basename']['exec']) > 0:
                print " executables:"
                f_out.write(" executables:\n")
                for bin_lib in output_found_dict[repo]['basename']['exec']:
                    print "  %s"%(bin_lib)
                    f_out.write("  %s\n"%(bin_lib))
                f_out.write("\n")
                
            if len(output_found_dict[repo]['basename']['libs']) > 0:
                print " libraries:"
                f_out.write(" libraries:\n")
                for bin_lib in output_found_dict[repo]['basename']['libs']:
                    print "  %s"%(bin_lib)
                    f_out.write("  %s\n"%(bin_lib))
            
            f_out.write("\n")
            
                
    print "Not found bins/libs in install repository:"
    print "-----------------------------------------"
    f_out.write("Not found bins/libs in install repository:\n")
    f_out.write("-----------------------------------------\n")
    
    for bin_lib in not_found_list:
        print bin_lib
        f_out.write(bin_lib)
    
    f_out.close()
    
    
    