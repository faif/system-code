#!/bin/sh

# find all SUID/SGID programs
printf "searching for SUID/SGID programs...\n"
find / -type f \( -perm -04000 -o -perm -02000 \) \-exec ls -lg {} \; 2>/dev/null

# locate all group & world-writable files
printf "\nsearching for group/world writable files...\n"
find / -type f \( -perm -2 -o -perm -20 \) -exec ls -lg {} \; 2>/dev/null

# locate all group & world-writable directories
printf "\nsearching for group/world writable directories...\n"
find / -type d \( -perm -2 -o -perm -20 \) -exec ls -ldg {} \; 2>/dev/null

# locate files on your system that do not have an owner
printf "\nsearching for files without owner...\n"
find / -nouser -o -nogroup 2>/dev/null
