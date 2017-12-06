dnl Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(rabbit_test2, 1.0)

RABBIT_INCLUDES="-I\$(top_srcdir)/src"
AC_SUBST(RABBIT_INCLUDES)


RABBIT_LIBS="-lrabbitmq"
AC_SUBST(RABBIT_LIBS)

AC_CANONICAL_SYSTEM
AM_INIT_AUTOMAKE()

AC_PROG_CC

AC_CONFIG_FILES(Makefile src/Makefile)
AC_OUTPUT

