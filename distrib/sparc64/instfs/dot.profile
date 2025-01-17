# $NetBSD$
#
# Copyright (c) 1997 Perry E. Metzger
# Copyright (c) 1994 Christopher G. Demetriou
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. All advertising materials mentioning features or use of this software
#    must display the following acknowledgement:
#          This product includes software developed for the
#          NetBSD Project.  See http://www.NetBSD.org/ for
#          information about NetBSD.
# 4. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# 
# <<Id: LICENSE,v 1.2 2000/06/14 15:57:33 cgd Exp>>

PATH=/sbin:/bin:/usr/bin:/usr/sbin:/
export PATH

# Check if we are on a framebuffer or on serial console and default
# the terminal type accordingly.
# There is no /var/db/dev.cdb, so sysctl might not map the devicename properly;
# ttyE0 is 90,0 -> 0x5a00
case $(sysctl -nx kern.consdev) in
 0000000000005a0*)
   TERM=wsvt25
   ;;
 *)
   TERM=vt220
   ;;
esac

export TERM
HOME=/
export HOME
BLOCKSIZE=1k
export BLOCKSIZE
EDITOR=ed
export EDITOR
SHELL=/bin/sh
export SHELL

umask 022

if [ "X${DONEPROFILE}" = "X" ]; then
	DONEPROFILE=YES
	export DONEPROFILE

	# set up some sane defaults
	echo 'erase ^?, werase ^W, kill ^U, intr ^C'
	stty newcrt werase ^W intr ^C kill ^U erase ^? 9600
	echo ''

	if [ $TERM != "wsvt25" ]; then
		cat << "EOM"
You are using a serial console, we do not know your terminal emulation.
Please select one, typical values are:

	vt100
	ansi
	xterm

EOM
		echo -n "Terminal type (just hit ENTER for '$TERM'): "
		read ans
		if [ -n "$ans" ];then
		    TERM=$ans
		fi
	fi

	# mount the kern_fs so that we can find the root device, and also
	# examine the dmesg state
	mount -t kernfs /kern /kern

	# hack to get around bugs in kernfs's rootdev/rrootdev lookup.
	ls -l /dev/* > /dev/null 2>&1

	# mount the ramdisk read write
	mount -t ffs -u /kern/rootdev /

	# run the installation or upgrade script.
	sysinst
	if [ $? = 4 ]; then
		echo "Oops, something went wrong - we will try again"
		exit
	fi
	echo
	echo "To return to the installer, quit this shell by typing 'exit'" \
		"or ^D."
fi
