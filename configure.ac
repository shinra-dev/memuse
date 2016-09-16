AC_PREREQ([2.69])
AC_INIT(DESCRIPTION)

AC_PROG_CC_C99


AC_CHECK_HEADER(features.h,
  [HAS_FEATURES_H=1], # success
  [HAS_FEATURES_H=0]  # failure
)

AC_SUBST(HAS_FEATURES_H)

AC_OUTPUT(src/meminfo/src/conf.h)
