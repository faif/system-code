#!/bin/sh

#    network information about a host
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

domain=`hostname -f` || exit 1
ip=`ip add | grep inet | grep brd | tr -s " " | cut -d" " -f3` || exit 1
iface=`lspci | grep Net | cut -d: -f3 | sed 's/^ *//'` || exit 1

printf "hostname\t${domain}\n"
printf "ip address\t${ip}\t\n"
printf "net. adapter\t${iface}\t\n"
