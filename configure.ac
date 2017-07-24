AC_INIT([bp], [1.0], [bug-report@address])
AM_INIT_AUTOMAKE([subdir-objects foreign -Wall -Werror])

AC_PROG_CXX
AM_PROG_AR
AC_PROG_RANLIB
AC_CONFIG_HEADERS([config.h])

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

# Make build variables precious
AC_ARG_VAR(HOST, default value for the --host option)
AC_ARG_VAR(HOST_CC, host C compiler command)
AC_ARG_VAR(HOST_CXX, host C++ compiler command)
AC_ARG_VAR(HOST_LD, host linker command)
AC_ARG_VAR(HOST_STRIP, host strip tool)
AC_ARG_VAR(HOST_AS, host as command)
AC_ARG_VAR(HOST_AR, host archive tool)
AC_ARG_VAR(HOST_LIBTOOL, host libtool command)

AM_CONDITIONAL(DEBUG, test x"$debug" = x"true")
AM_CONDITIONAL(DARWIN_NATIVE64, test x"$HOST" = x"x86_64-apple-darwin")
AM_CONDITIONAL(LINUX_NATIVE64, test x"$HOST" = x"x86_64-linux")
AM_CONDITIONAL(LINUX_ARM, test x"$HOST" = x"arm-linux")
AM_CONDITIONAL(LINUX_X86, test x"$HOST" = x"i586-linux")

AC_CONFIG_FILES([Makefile])
AC_CONFIG_SUBDIRS([deps])

AC_OUTPUT
