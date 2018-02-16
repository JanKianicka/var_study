#!/bin/bash

WORKSPACE_LOC=/cygdrive/c/repo3/jlib
# WORKSPACE_LOC=C:/repo3/jlib
echo Copying from "$WORKSPACE_LOC"
#TARGET="10.111.3.198"
#TARGET="10.101.51.112"
#TARGET="192.168.71.58"
#TARGET="10.41.0.40"
#TARGET="192.168.140.99"
#TARGET="10.41.0.50"
#TARGET="10.111.1.21"
#TARGET="10.111.1.23"
#TARGET="10.111.1.25"
#TARGET="10.111.1.1"
#TARGET="10.111.1.5"
#TARGET="192.168.71.51"
#TARGET="10.111.1.171"
#TARGET="10.111.2.141"
#TARGET="10.111.3.180"
TARGET=10.111.2.1
rm -rf to_copy
mkdir to_copy
while IFS='' read -r PATTERN || [[ -n "$PATTERN" ]]
do
	PATTERN=$WORKSPACE_LOC$PATTERN
	if [[ "$PATTERN" =~ ^.*\..*$ ]]
	then
		FILES=`ls $PATTERN`
	else
		FILES=`ls $PATTERN\\$*.class 2>/dev/null`" "`ls $PATTERN.class`
	fi
	for FILE in $FILES 
	do
		RELATIVE_FILE=`echo $FILE | sed -r 's/^.*\/jlib\/(.*)$/\1/'`
		RELATIVE_DIR=`echo $RELATIVE_FILE | sed -r 's/^(.*)\/.*$/\1/'`
		FILE_NAME=`echo $RELATIVE_FILE | sed -r 's/^.*\/(.*)$/\1/'`
		mkdir -p "to_copy/$RELATIVE_DIR"
		cp "$FILE" "to_copy/$RELATIVE_FILE"
	done
#	cp -p $file.class to_copy/$file.class
	#cp -p $file\$*.class to_copy/$file\$*.class
done < $1;

echo
echo "Going to transfer the following files to $TARGET:"
echo
find to_copy -type f -print
echo
scp -r to_copy/{lib,lib8}/* root@$TARGET:/opt/ims/bin
scp -r to_copy/cfg/* root@$TARGET:/opt/ims/cfg
scp -r to_copy/html2/ims/* root@$TARGET:/opt/ims/tomcat/webapps/ims/html2
