#!/bin/sh

FILEROOT=/sys
CLASSNAME=Linux_SysfsAttribute

OUTFILE=$CLASSNAME".instance"
rm -f $OUTFILE
if [[ $1 = "-rm" ]]; then exit 0; fi

# Find all the appropriate /sys files
find $FILEROOT -noleaf -type f | while read; do
   FILE="$REPLY"

   # SettingID
   echo "$FILE"

   # Value
   if [[ `stat -c "%A" "$FILE"` = ?r* ]]; then
      VALUE=`cat "$FILE" 2>/dev/null | sed -e 's/[	]/ /g'`
   else
      VALUE="NULL"
   fi
   echo $VALUE

   #  Writeable
   if [[ `stat -c "%A" "$FILE"` = ??w* ]]; then echo TRUE; else echo FALSE; fi

   echo 
done > $OUTFILE 

