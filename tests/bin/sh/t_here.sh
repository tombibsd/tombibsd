# $NetBSD$
#
# Copyright (c) 2007 The NetBSD Foundation, Inc.
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
#
# THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
# ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
# TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
# BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

nl='
'

check()
{
	SVIFS="$IFS"
	result="$(eval $1)"
	# Remove newlines
	oifs="$IFS"
	IFS="$nl"
	result="$(echo $result)"
	IFS="$oifs"
	if [ "$2" != "$result" ]
	then
		atf_fail "expected [$2], found [$result]"
	fi
	IFS="$SVIFS"
}

atf_test_case all
all_head() {
	atf_set "descr" "Basic tests for here documents"
}
all_body() {
	y=x

	IFS=
	check 'x=`cat <<EOF'$nl'text'${nl}EOF$nl'`; echo $x' 'text'
	check 'x=`cat <<\EOF'$nl'text'${nl}EOF$nl'`; echo $x' 'text'

	check 'x=`cat <<EOF'$nl'te${y}t'${nl}EOF$nl'`; echo $x' 'text'
	check 'x=`cat <<\EOF'$nl'te${y}t'${nl}EOF$nl'`; echo $x' 'te${y}t'
	check 'x=`cat <<"EOF"'$nl'te${y}t'${nl}EOF$nl'`; echo $x' 'te${y}t'
	check 'x=`cat <<'"'EOF'"$nl'te${y}t'${nl}EOF$nl'`; echo $x' 'te${y}t'

	check 'x=`cat <<EOF'$nl'te'"'"'xt'${nl}EOF$nl'`; echo $x' 'te'"'"'xt'
	check 'x=`cat <<\EOF'$nl'te'"'"'xt'${nl}EOF$nl'`; echo $x' 'te'"'"'xt'
	check 'x=`cat <<"EOF"'$nl'te'"'"'xt'${nl}EOF$nl'`; echo $x' 'te'"'"'xt'

	check 'x=`cat <<EOF'$nl'te'"'"'${y}t'${nl}EOF$nl'`; echo $x' 'te'"'"'xt'
	check 'x=`cat <<EOF'$nl'te'"''"'${y}t'${nl}EOF$nl'`; echo $x' 'te'"''"'xt'
}

atf_init_test_cases() {
	atf_add_test_case all
}
