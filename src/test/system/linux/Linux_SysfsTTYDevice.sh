#!/bin/sh

FILEROOT=/sys/class/tty
CLASSNAME=Linux_SysfsTTYDevice

OUTFILE=$CLASSNAME".instance"
rm -f $OUTFILE
if [[ $1 = "-rm" ]]; then exit 0; fi

# Find all the appropriate /proc files
FILES=$( find $FILEROOT -maxdepth 1 -mindepth 1 -type d );
for FILE in $FILES; do
   # Name
   echo $FILE

   echo 
done > $OUTFILE 
