'''
Class to perform makefile check and modification according 
results from dependency checkers.

In order to generate makefile the following is needed.
- if gdi dependency was not detected - remove all gdi entries
- if idccss30 dependency was detected add entries in INCLUDE and LDADD
  should be extended, if/endif blocks as well
- if there is present db30qa has to be replaced with IDCCSS30QA

'''
import re

MK_INCLUDE_PATTERN  = "\@([A-Z0-9\_]*\_INCLUDES)\@"
MK_LDADD_PATTERN    = "\@([A-Z0-9\_]*\_LIBS)\@"
MK_IF_HAVE_PATTERN  = "^if (HAVE\_[A-Z0-9\_]*)$"
MK_ENDIF_HAVE_PATTERN = "^endif (HAVE\_[A-Z0-9\_]*)$"

class AppMakefileChecker():
    
    def __init__(self, make_file, make_file_out, have_idccss30 = False, have_gdi = False ):
        self.makefile_blocks = {'include_block':{'pattern':MK_INCLUDE_PATTERN, 
                                                 'idccss30_ent':"IDCCSS30_INCLUDES",
                                                 'gdi_ent':"GDI_INCLUDES",
                                                 'reverse_ord':False,
                                                 'out_string':'\t@%s@',
                                                 'have_slash':True}, 
                                'if_have_block':{'pattern':MK_IF_HAVE_PATTERN, 
                                                 'idccss30_ent':"HAVE_IDCCSS30",
                                                 'gdi_ent':"HAVE_GDI",
                                                 'reverse_ord':False,
                                                 'out_string':'if %s',
                                                 'have_slash':False},
                                'endif_have_block':{'pattern':MK_ENDIF_HAVE_PATTERN, 
                                                    'idccss30_ent':"HAVE_IDCCSS30",
                                                    'gdi_ent':"HAVE_GDI",
                                                    'reverse_ord':True,
                                                    'out_string':'endif %s',
                                                    'have_slash':False},
                                'ldadd_block':{'pattern':MK_LDADD_PATTERN, 
                                               'idccss30_ent':"IDCCSS30_LIBS",
                                               'gdi_ent':"GDI_LIBS",
                                               'reverse_ord':False,
                                               'out_string':'\t@%s@',
                                               'have_slash':True} }

        self.blocks_vars = ['temp','orig','out']
        for block_var in self.blocks_vars:
            for block_key in self.makefile_blocks.keys():
                self.makefile_blocks[block_key][block_var] = []
        
        
        self.make_file = make_file
        self.make_file_out = make_file_out
        self.lines = []
        self.whole_file_or = str
        self.have_idccss30 = have_idccss30
        self.have_gdi = have_gdi
        
    def runCheck(self):
        self._readMakefile()
        for block_key, pars in self.makefile_blocks.items():
            self._getMakefileBlocks(pars['pattern'], 
                                    pars['temp'], 
                                    pars['orig'], 
                                    self.have_idccss30, 
                                    self.have_gdi, 
                                    pars['idccss30_ent'],
                                    pars['gdi_ent'], 
                                    pars['reverse_ord'])
            self._generateTextBlocks(pars['temp'], pars['out'], pars['have_slash'], pars['out_string'])
        
        self._writeOutMakefile()
            
    def _readMakefile(self):
        make_file_f = open(self.make_file, "r")
    
        self.lines = make_file_f.readlines()
        make_file_f.seek(0)
        self.whole_file_or =  make_file_f.read()
        make_file_f.close()
        
    def _writeOutMakefile(self):
        f_out2 = open(self.make_file_out, "w")
        for block_key, pars in self.makefile_blocks.items():
            self.whole_file_or = self.whole_file_or.replace("".join(pars['orig']),  "".join(pars['out']))
            print "Original:\n"
            print "".join(pars['orig'])
            print "New:\n"
            print "".join(pars['out'])
            
        # Yet remove GDI DEP record
        if not self.have_gdi:
            self.whole_file_or = self.whole_file_or.replace("\n\t@LIBGDI@ \\\n\t@GDI_DEPENDENCIES@ \\","")
        
        #yet replace DB30QA with IDCCSS30QA
        self.whole_file_or = self.whole_file_or.replace("DB30QA","IDCCSS30QA")
                                                
        f_out2.write(self.whole_file_or)
        f_out2.close()       
    
    def _getMakefileBlocks(self, pattern, temp_block_list, orig_block_list,
                           have_idccss30, have_gdi, idccss30_ent, gdi_ent,
                           reverse_ord):
        for line in self.lines:
            Matcher = re.search(pattern, line)
             
            if Matcher:
                temp_block_list.append(Matcher.group(1))
                orig_block_list.append(line)
             
            del(Matcher)
                
        if have_idccss30 and (temp_block_list.count(idccss30_ent)<1):
            temp_block_list.append(idccss30_ent)
        
        if have_gdi and (temp_block_list.count(gdi_ent)<1):
            temp_block_list.append(gdi_ent)
        
        if not have_idccss30:
            if (temp_block_list.count(idccss30_ent)>0):
                temp_block_list.remove(idccss30_ent)
        
        if not have_gdi:
            if (temp_block_list.count(gdi_ent)>0):
                temp_block_list.remove(gdi_ent)

        temp_block_list.sort(reverse=reverse_ord)
    
    def _generateTextBlocks(self, temp_block_list, out_block_list, have_slash, string_match):
        
        i = 0
        for value in temp_block_list:
            if(i<(len(temp_block_list)-1)):
                if have_slash:
                    out_block_list.append("%s \\\n"%(string_match%(value)) )
                else:
                    out_block_list.append("%s\n"%(string_match%(value)))
            else:
                out_block_list.append("%s\n"%(string_match%(value)))
            i=i+1
