bin_PROGRAMS = mbvelocitytool

AM_CFLAGS = ${libnetcdf_CFLAGS}

AM_CPPFLAGS = -I${top_srcdir}/src/mbio \
	      -I${top_srcdir}/src/mbaux \
	      -I${top_srcdir}/src/gsf \
	      ${libnetcdf_CPPFLAGS} \
	      ${libmotif_CPPFLAGS}

AM_LDFLAGS = 

LIBS = ${top_builddir}/src/mbio/libmbio.la \
       ${top_builddir}/src/mbaux/libmbaux.la \
       ${top_builddir}/src/mbaux/libmbxgr.la \
       ${libgmt_LIBS} ${libnetcdf_LIBS} ${libproj_LIBS} \
       ${libmotif_LIBS} \
       $(LIBM)

mbvelocitytool_SOURCES = mbvelocity_bxutils.c mbvelocity.c mbvelocity_callbacks.c \
        mbvelocity_creation.c mbvelocity_prog.c mbvelocity_creation.h mbvelocity.h
