lib_LTLIBRARIES = mapChange.la

mapChange_la_SOURCES = mapChange.cpp
mapChange_la_CXXFLAGS= -I$(top_srcdir)/include -I$(top_srcdir)/plugins/plugin_utils
mapChange_la_LDFLAGS = -module -avoid-version -shared
mapChange_la_LIBADD = $(top_builddir)/plugins/plugin_utils/libplugin_utils.la

AM_CPPFLAGS = $(CONF_CPPFLAGS)
AM_CFLAGS = $(CONF_CFLAGS)
AM_CXXFLAGS = $(CONF_CXXFLAGS)

EXTRA_DIST = \
	README.txt \
	mapChange.def \
	mapChange.sln \
	mapChange.vcxproj

MAINTAINERCLEANFILES =	\
	Makefile.in
