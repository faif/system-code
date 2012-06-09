#!/bin/sh

# enumerate the user database

user_f=/etc/passwd
group_f=/etc/group

while read line
do
    uname=`echo ${line} | cut -d: -f 1`
    uid=`echo ${line} | cut -d: -f 3`
    printf "groups of ${uname} (${uid})\n" 
    groups=`grep ${uname} ${group_f} | cut -d: -f 1`
    printf "${groups}\n\n"
done < ${user_f}
