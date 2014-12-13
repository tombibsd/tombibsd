# $Id$
#
# Miscellaneous variable tests.

all: unmatched_var_paren

unmatched_var_paren:
	@echo ${foo::=foo-text}
