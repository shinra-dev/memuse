/* Automatically generated. Do not edit by hand. */

#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <stdlib.h>

extern SEXP R_meminfo_cacheinfo_linesize();
extern SEXP R_meminfo_cacheinfo_size(SEXP level);
extern SEXP R_meminfo_filesize(SEXP filename);
extern SEXP R_meminfo_procinfo();
extern SEXP R_meminfo_raminfo();
extern SEXP R_meminfo_retvals(SEXP retval);
extern SEXP R_meminfo_swapinfo();

static const R_CallMethodDef CallEntries[] = {
  {"R_meminfo_cacheinfo_linesize", (DL_FUNC) &R_meminfo_cacheinfo_linesize, 0},
  {"R_meminfo_cacheinfo_size", (DL_FUNC) &R_meminfo_cacheinfo_size, 1},
  {"R_meminfo_filesize", (DL_FUNC) &R_meminfo_filesize, 1},
  {"R_meminfo_procinfo", (DL_FUNC) &R_meminfo_procinfo, 0},
  {"R_meminfo_raminfo", (DL_FUNC) &R_meminfo_raminfo, 0},
  {"R_meminfo_retvals", (DL_FUNC) &R_meminfo_retvals, 1},
  {"R_meminfo_swapinfo", (DL_FUNC) &R_meminfo_swapinfo, 0},
  {NULL, NULL, 0}
};

void R_init_memuse(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);
}
