#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([milter-blockdomain], [1.05], [takao_abe@xurb.jp])
AC_DEFINE([PACKAGE_DATE], ["2022-04-24"], [Define to the release date of this package.])
AM_INIT_AUTOMAKE([foreign])
AC_CONFIG_SRCDIR([src/milter-blockdomain.c])
AC_CONFIG_HEADERS([config.h])

timestamp=$(date '+%F %H:%M %Z')
AC_DEFINE_UNQUOTED([BUILD_TIMESTAMP], "$timestamp", [Define to the current timestamp])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdio.h stdlib.h stdarg.h string.h sysexits.h syslog.h unistd.h])
AC_CHECK_HEADERS([sys/time.h sys/types.h sys/stat.h ctype.h errno.h getopt.h pwd.h])
AC_CHECK_HEADERS([arpa/inet.h netinet/in.h libmilter/mfapi.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_PID_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_CHOWN
AC_FUNC_MALLOC
AC_CHECK_FUNCS([gettimeofday memset strchr strdup])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
