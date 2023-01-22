AC_PREREQ([2.71])
AC_INIT(DESCRIPTION)
AC_CONFIG_SRCDIR([DESCRIPTION])

: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  AC_MSG_ERROR([Unable to determine RHOME])
fi
CC=`"${R_HOME}/bin/R" CMD config CC`
CFLAGS=`"${R_HOME}/bin/R" CMD config CFLAGS`
CPPFLAGS=`"${R_HOME}/bin/R" CMD config CPPFLAGS`

AC_CHECK_HEADERS(features.h,
  [HAS_FEATURES_H=1], # success
  [HAS_FEATURES_H=0]  # failure
)

AC_SUBST(HAS_FEATURES_H)
AC_CONFIG_FILES([src/meminfo/src/conf.h])
AC_OUTPUT
