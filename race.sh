#!/bin/sh

function print_usage ()  
{
    printf "USAGE: ${@}\n" >&2
}

function print_error () 
{ 
    printf "ERROR: ${@}\n" >&2
}

if [ $# -ne 1 ] ; then
    print_usage "`basename $0` file"
    exit 0
fi

if [ ! -f "$1" ] ; then
    print_error "file $1 does not exist"
    exit 0
fi

if [ -f "$1.lock" ] ; then
    exit 0
else
    ln "$1" "$1.lock"
fi

i=0
until [ $i -eq 1000 ] ;
do
    LAST_NUM=`tail -n 1 "$1"`
    NUM=$((LAST_NUM + 1))
    echo $NUM >> $1 2>/dev/null
    i=$((i + 1))
done 

rm -f "$1.lock"
