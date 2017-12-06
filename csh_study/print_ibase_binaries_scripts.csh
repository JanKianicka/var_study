#!/bin/csh
# set path_to_bins = "${CTBTO_INSTALL}/ibase/bin"
set path_to_bins = "${CTBTO_INSTALL}/idcdacs/bin"
foreach f (`ls $path_to_bins/*`)
set name = `file $f| awk '{print $2}'`
set f_basename = `basename $f`
if ($name == "ELF") then
# for printing out binaries, uncomment this
#echo $f_basename
else
# for printing out scripts, uncomment this
# echo "Script: $f"
echo $f_basename
endif
end
