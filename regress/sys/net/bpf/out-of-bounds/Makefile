#	$NetBSD$

.ifdef REGRESS_LOG
regress:
	@echo sys/net/bpf/out-of-bounds out-of-bounds \
	`./out-of-bounds.sh` | tee ${REGRESS_LOG} ; true
.else
regress:
	@echo sys/net/bpf/out-of-bounds out-of-bounds \
	`./out-of-bounds.sh`; true 
.endif

.include <bsd.prog.mk>
