'''
In order to generate makefile the following is needed.
- if gdi dependency was not detected - remove all gdi entries
- if idccss30 dependency was detected add entries in INCLUDE and LDADD
  should be extended, if/endif blocks as well
- if there is present db30qa has to be replaced with IDCCSS30QA

'''
from makefile_checker import AppMakefileChecker    

if __name__ == "__main__":

    make_file = '/home/local/kianicka/repositories/ctbto/ibase/src/fpstacap/Makefile.am'
    make_file_out2 = '/home/local/kianicka/repositories/ctbto/ibase/src/fpstacap/Makefile.am_out'
    idccss30 = True
    gdi = True
    
    MkFileChecker = AppMakefileChecker(make_file, make_file_out2, have_idccss30=idccss30, have_gdi=gdi)
    MkFileChecker.runCheck()
 
