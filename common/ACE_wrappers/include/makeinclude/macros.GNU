#-*- Makefile -*-

#----------------------------------------------------------------------------
#	$Id: macros.GNU 80826 2008-03-04 14:51:23Z wotte $
#
#	Local and nested target definitions
#----------------------------------------------------------------------------

TARGETS_LOCAL  = \
	all.local \
	debug.local \
	profile.local \
	optimize.local \
	install.local \
	deinstall.local \
	clean_binaries.local \
	clean_idl_stubs.local \
	clean.local \
	realclean.local \
	clobber.local \
	depend.local \
	rcs_info.local \
	idl_stubs.local \
	svnignore.local

TARGETS_NESTED   = \
	$(TARGETS_LOCAL:.local=.nested)

