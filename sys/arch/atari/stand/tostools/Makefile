#	$NetBSD$

SUBDIR= libtos loadbsd aptck chg_pid file2swp rawwrite

.PHONY: all clean install

all:
	@for dir in ${SUBDIR}; do	\
	    ${MAKE} -C $$dir all;		\
	 done

clean:
	@for dir in ${SUBDIR}; do	\
	    ${MAKE} -C $$dir clean;	\
	 done

install:
	@for dir in ${SUBDIR}; do	\
	    ${MAKE} -C $$dir install;	\
	 done
