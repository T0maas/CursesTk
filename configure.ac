#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([cursestk], [0.1], [BUG-REPORT-ADDRESS])
AC_CONFIG_HEADERS([config.h])
AC_ENABLE_SHARED
AM_INIT_AUTOMAKE
# Checks for programs.
AC_PROG_CXX
LT_INIT
# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.
PKG_CHECK_MODULES([ncurses],[ncurses > 5.0])
# Checks for library functions.
#AC_CHECK_FUNCS([pow sqrt])


AC_CONFIG_FILES([Makefile src/Makefile cursestk.pc])
AC_OUTPUT
