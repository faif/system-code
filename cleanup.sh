#!/bin/bash

# cleanup the configuration files of the removed packages 

if [ "${UID}" -ne 0 ] ; then
    echo "you need root privileges!"
    exit 1
else
    COLUMNS=1000 dpkg --list | grep ^rc | awk '{print $2}' | xargs dpkg -P
    #dpkg-query --show --showformat='${Status}\t${Package}\n'| grep ^deinstall | cut -f2	| xargs dpkg -P
fi
