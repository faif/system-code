#!/bin/bash

#    page_size.sh Calculate the mean and median of the executable sizes
#    Copyright (C) 2011 Sakis Kasampalis <faif at dtek period gr>

#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.

#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.

#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.

function print_error () 
{ 
    printf "ERROR: ${@}\n" >&2
}

function print_usage ()  
{
    printf "USAGE: ${@}\n" >&2
}

if [ $# -lt 1 ] ; then 
    print_error "Insufficient Arguments."
    print_usage "`basename $0` [directory1] [directory2] ..."
    exit 1
fi

tot_size=0
tot_cnt=0 
median=0
n_dirs=0

for i in "$@"
do
    # TODO: add privilege control (if the dir can be read, etc.)
    if [ -d "$i" ] ; then
	    cnt=`find $i -executable | wc -l`
	    size=`find $i -executable | xargs du -s | awk '{ print $1 }' | head -n 1`
	    results=`find $i -executable | xargs du -s | awk '{ print $1 }' | wc -l`
	    med_pos=`echo "$results / 2" | bc`
	    med_pos=`echo "+$med_pos"` # to be tail-compatible
	    cur_median=`find $i -executable | xargs du -s | awk '{ print $1 }' \
	        | sort -n | tail -n $med_pos | head -n 1`
	    median=`echo "$median + $cur_median" | bc`
	    tot_size=`echo "$tot_size + $size" | bc`
	    tot_cnt=`echo "$tot_cnt + $cnt" | bc`
	    n_dirs=`echo "$n_dirs + 1" | bc`
    else
        print_error "$i: Invalid directory"
    fi
done

mean=`echo "$tot_size / $tot_cnt" | bc`
median=`echo "$median / $n_dirs" | bc`

if [ $tot_size -gt 0 ] ; then
    echo "total files: $tot_cnt"
    echo "total size: $tot_size bytes"
    echo "mean size: $mean bytes"
    echo "median size: $median bytes"
fi
