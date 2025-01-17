# $NetBSD$
#
# Copyright (c) 2013 The NetBSD Foundation, Inc.
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

# TEST RFC 4182
# Setup four routers connected like this: R1---R2---R3---R4--
# Goal is to be able to ping from R1 the outermost interface of R4
# Disable net.inet.ip.forwarding, enable net.mpls.forwarding
# Add route on R1 in order to encapsulate into MPLS the IP packets with
#     destination equal to R4 right hand side interface. Use two labels here:
#     25 and IPv6 Explicit NULL
# Add a double tagged MPLS route on R2 in order to forward frames belonging to
#     that FEC to R3, with IPv4 NULL being the most outermost one
# Add MPLS "POP" route on R3 for that FEC, pointing to R4
# Do the same for the reverse direction (R4 to R1)
# ping from R1 to R4 right hand side interface


RUMP_SERVER1=unix://./r1
RUMP_SERVER2=unix://./r2
RUMP_SERVER3=unix://./r3
RUMP_SERVER4=unix://./r4

RUMP_FLAGS=\
"-lrumpnet -lrumpnet_net -lrumpnet_netmpls -lrumpnet_netinet -lrumpnet_shmif"

atf_test_case rfc4182 cleanup
rfc4182_head()
{

	atf_set "descr" "RFC 4182 conformance test"
	atf_set "require.progs" "rump_server"
}

startservers()
{

	ulimit -r 300
	atf_check -s exit:0 rump_server ${RUMP_FLAGS} ${RUMP_SERVER1}
	atf_check -s exit:0 rump_server ${RUMP_FLAGS} ${RUMP_SERVER2}
	atf_check -s exit:0 rump_server ${RUMP_FLAGS} ${RUMP_SERVER3}
	atf_check -s exit:0 rump_server ${RUMP_FLAGS} ${RUMP_SERVER4}
}

configservers()
{

	# Setup the first server
	export RUMP_SERVER=${RUMP_SERVER1}
	atf_check -s exit:0 rump.ifconfig shmif0 create
	atf_check -s exit:0 rump.ifconfig shmif0 linkstr ./shdom1
	atf_check -s exit:0 rump.ifconfig shmif0 10.0.1.1/24
	atf_check -s exit:0 rump.ifconfig mpls0 create up
	atf_check -s exit:0 rump.sysctl -q -w net.mpls.accept=1
	atf_check -s exit:0 rump.sysctl -q -w net.inet.ip.forwarding=0
	atf_check -s exit:0 rump.route -q add 10.0.4.0/24 -ifa 10.0.1.1 \
	    -ifp mpls0 -tag 25,2 -inet 10.0.1.2

	# Setup the second server
	export RUMP_SERVER=${RUMP_SERVER2}
	atf_check -s exit:0 rump.ifconfig shmif0 create
	atf_check -s exit:0 rump.ifconfig shmif0 linkstr ./shdom1
	atf_check -s exit:0 rump.ifconfig shmif0 10.0.1.2/24
	atf_check -s exit:0 rump.ifconfig shmif1 create
	atf_check -s exit:0 rump.ifconfig shmif1 linkstr ./shdom2
	atf_check -s exit:0 rump.ifconfig shmif1 10.0.2.1/24
	atf_check -s exit:0 rump.ifconfig mpls0 create up
	atf_check -s exit:0 rump.sysctl -q -w net.mpls.accept=1
	atf_check -s exit:0 rump.sysctl -q -w net.mpls.forwarding=1
	atf_check -s exit:0 rump.sysctl -q -w net.inet.ip.forwarding=0
	atf_check -s exit:0 rump.route -q add -mpls 25 -tag 30,0 -inet 10.0.2.2
	atf_check -s exit:0 rump.route -q add -mpls 27 -tag 3 -inet 10.0.1.1

	# Setup the third server
	export RUMP_SERVER=${RUMP_SERVER3}
	atf_check -s exit:0 rump.ifconfig shmif0 create
	atf_check -s exit:0 rump.ifconfig shmif0 linkstr ./shdom2
	atf_check -s exit:0 rump.ifconfig shmif0 10.0.2.2/24
	atf_check -s exit:0 rump.ifconfig shmif1 create
	atf_check -s exit:0 rump.ifconfig shmif1 linkstr ./shdom3
	atf_check -s exit:0 rump.ifconfig shmif1 10.0.3.1/24
	atf_check -s exit:0 rump.ifconfig mpls0 create up
	atf_check -s exit:0 rump.sysctl -q -w net.mpls.accept=1
	atf_check -s exit:0 rump.sysctl -q -w net.mpls.forwarding=1
	atf_check -s exit:0 rump.sysctl -q -w net.inet.ip.forwarding=0
	atf_check -s exit:0 rump.route -q add -mpls 30 -tag 3 -inet 10.0.3.2
	atf_check -s exit:0 rump.route -q add -mpls 26 -tag 27,0 -inet 10.0.2.1

	# Setup the fourth server
	export RUMP_SERVER=${RUMP_SERVER4}
	atf_check -s exit:0 rump.ifconfig shmif0 create
	atf_check -s exit:0 rump.ifconfig shmif0 linkstr ./shdom3
	atf_check -s exit:0 rump.ifconfig shmif0 10.0.3.2/24
	atf_check -s exit:0 rump.ifconfig shmif1 create
	atf_check -s exit:0 rump.ifconfig shmif1 linkstr ./shdom4
	atf_check -s exit:0 rump.ifconfig shmif1 10.0.4.1/24
	atf_check -s exit:0 rump.ifconfig mpls0 create up
	atf_check -s exit:0 rump.sysctl -q -w net.mpls.accept=1
	atf_check -s exit:0 rump.sysctl -q -w net.inet.ip.forwarding=0
	atf_check -s exit:0 rump.route -q add 10.0.1.0/24 -ifa 10.0.3.2 \
	    -ifp mpls0 -tag 26 -inet 10.0.3.1

	unset RUMP_SERVER
}

doping()
{

	export RUMP_SERVER=${RUMP_SERVER1}
	atf_check -s exit:0 -o match:"64 bytes from 10.0.4.1: icmp_seq=" \
	    rump.ping -n -o -w 5 10.0.4.1
	unset RUMP_SERVER
}

docleanup()
{

	RUMP_SERVER=${RUMP_SERVER1} rump.halt
	RUMP_SERVER=${RUMP_SERVER2} rump.halt
	RUMP_SERVER=${RUMP_SERVER3} rump.halt
	RUMP_SERVER=${RUMP_SERVER4} rump.halt
}

rfc4182_body()
{

	startservers
	configservers
	doping
}

rfc4182_cleanup()
{

	docleanup
}

atf_init_test_cases()
{ 

	atf_add_test_case rfc4182
} 
