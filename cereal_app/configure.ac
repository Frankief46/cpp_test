AC_INIT([generic_microservice], [1.0], [bug-report@address])
AM_INIT_AUTOMAKE([subdir-objects foreign -Wall -Werror])

AC_PROG_CXX
AM_PROG_AR
AC_PROG_RANLIB

# Enable C and C++
AC_LANG([C])
AC_LANG([C++])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([string])
AC_CHECK_HEADERS([iostream])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

AC_ARG_ENABLE(debug,
AS_HELP_STRING([--enable-debug],
               [enable debugging, default: no]),
[case "${enableval}" in
             yes) debug=true ;;
             no)  debug=false ;;
             *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
esac],
[debug=false])

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

