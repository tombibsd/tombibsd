# $NetBSD$ 

rump_quota_shutdown()
{
	for s in ${RUMP_SOCKETS_LIST}; do
		atf_check -s exit:0 env RUMP_SERVER=unix://${s} rump.halt;
	done
# check that the quota inode creation didn't corrupt the filesystem
	atf_check -s exit:0 -o "match:already clean" \
		-o "match:Phase 6 - Check Quotas" \
		fsck_ffs -nf -F ${IMG}
}
