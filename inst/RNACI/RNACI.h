// Copyright (c) 2014-2016, Drew Schmidt
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


/* Changelog:
  Version 0.3-0:
    * Fixed warnings visible with -Wall -pedantic.
    * Use strnlen() over strlen(); shorten string checks in allocator.
    * Simplify initializer in allocator using memset().
  
  Version 0.2-0:
    * Converted to header only.
  
  Version 0.1-0:
    * Initial release.
*/

#ifndef __RNACI_H__
#define __RNACI_H__

#define RNACI_VERSION 0.3.0

#include <R.h>
#include <Rinternals.h>

#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>


#define RNACIMAX(m,n) m<n?n:m
#define RNULL R_NilValue


// R data accessors
#define IGNORED -1

#define __RNACI_INT(x,y,...) INTEGER(x)[y]
#define INT(...) __RNACI_INT(__VA_ARGS__,0,IGNORED)

#define __RNACI_DBL(x,y,...) REAL(x)[y]
#define DBL(...) __RNACI_DBL(__VA_ARGS__,0,IGNORED)

#define __RNACI_STR(x,y,...) ((char*)CHAR(STRING_ELT(x,y)))
#define STR(...) __RNACI_STR(__VA_ARGS__,0,IGNORED)


#define MatINT(x,i,j) (INTEGER(x)[i+nrows(x)*j])
#define MatDBL(x,i,j) (REAL(x)[i+nrows(x)*j])

#define INTP(x) (INTEGER(x))
#define DBLP(x) (REAL(x))



#define newRptr(ptr,Rptr,fin) PROTECT(Rptr = R_MakeExternalPtr(ptr, R_NilValue, R_NilValue));R_RegisterCFinalizerEx(Rptr, fin, TRUE)
#define getRptr(ptr) R_ExternalPtrAddr(ptr);

#define newRfreeptrfun(FNAME,TYPE,FREEFUN) \
static void FNAME(SEXP ptr) \
{ \
  if (NULL == R_ExternalPtrAddr(ptr)) return; \
  TYPE *tmp = (TYPE *) R_ExternalPtrAddr(ptr); \
  FREEFUN(tmp); \
  R_ClearExternalPtr(ptr); \
}




// GC stuff
#define R_INIT int __RNACI_SEXP_protect_counter=0
#define PT(x) PROTECT((x)); (__RNACI_SEXP_protect_counter)++
#define R_END (UNPROTECT(__RNACI_SEXP_protect_counter))


// Allocations
#define OPTIONALARG1(a,b,c,...) (a),(b),(c)

#define newRlist(x,n) PT(x=__Rvecalloc(n, "vec", false))
// #define newRvec(x,n,type) PT(x=__Rvecalloc(n, type,false))
#define newRvec(x,...) PT(x=__Rvecalloc(OPTIONALARG1(__VA_ARGS__,false,IGNORED)))
// #define newRmat(x,m,n,type) PT(x=__Rmatalloc(m,n,type,false))
#define newRmat(x,m,...) PT(x=__Rmatalloc(m,OPTIONALARG1(__VA_ARGS__,false,IGNORED)))


/* Misc stuff */
#define nonzero(x) (x?x:1)

#define is_null(x) (x==NULL)

#if __STDC_VERSION__ >= 199901L
#define dbstart printf("DEBUGGING in %s Started\n", __func__);int __RNACI_debug_printing_counter=0
#define dbstop printf("DEBUGGING in %s Ended\n", __func__)
#else
#define dbstart int __RNACI_debug_printing_counter=0
#endif

#define dbshow printf("%d\n", __RNACI_debug_printing_counter);__RNACI_debug_printing_counter++;



/***************************************************
 * Definitions *
 ***************************************************/


// alloc.c
static inline SEXP __Rvecalloc(int n, char *type, int init)
{
  SEXP RET;
  
  if (strncmp(type, "vec", 1) == 0)
    PROTECT(RET = allocVector(VECSXP, n));
  else if (strncmp(type, "int", 1) == 0)
  {
    PROTECT(RET = allocVector(INTSXP, n));
    
    if (init)
      memset(INTP(RET), 0, n*sizeof(int));
  }
  else if (strncmp(type, "double", 1) == 0)
  {
    PROTECT(RET = allocVector(REALSXP, n));
    
    if (init)
      memset(DBLP(RET), 0, n*sizeof(double));
  }
  else if (strncmp(type, "str", 1) == 0 || strncmp(type, "char*", 1) == 0)
    PROTECT(RET = allocVector(STRSXP, n));
  else
    return NULL;
  
  UNPROTECT(1);
  return RET;
}

static inline SEXP __Rmatalloc(int m, int n, char *type, int init)
{
  SEXP RET;
  
  if (strncmp(type, "vec", 1) == 0)
    PROTECT(RET = allocMatrix(VECSXP, m, n));
  else if (strncmp(type, "int", 1) == 0)
  {
    PROTECT(RET = allocMatrix(INTSXP, m, n));
    
    if (init)
      memset(INTP(RET), 0, m*n*sizeof(int));
  }
  else if (strncmp(type, "double", 1) == 0)
  {
    PROTECT(RET = allocMatrix(REALSXP, m, n));
    
    if (init)
      memset(DBLP(RET), 0, m*n*sizeof(double));
  }
  else if (strncmp(type, "str", 1) == 0 || strncmp(type, "char*", 1) == 0)
    PROTECT(RET = allocMatrix(STRSXP, m, n));
  else
    return NULL;
  
  UNPROTECT(1);
  return RET;
}


// floats.c

static inline int fis_zerof(float x)
{
  const float abs_epsf = 1.1f * FLT_EPSILON;
  if (fabsf(x) < abs_epsf*FLT_MIN)
    return true;
  else
    return false;
}

static inline int fis_zero(double x)
{
  const double abs_eps = 1.1 * DBL_EPSILON;
  if (fabs(x) < abs_eps*DBL_MIN)
    return true;
  else
    return false;
}

static inline int fequalsf(float x, float y)
{
  const float abs_epsf = 1.1f * FLT_EPSILON;
  const double diff = fabsf(x - y);
  
  if (x == y)
    return true;
  else if (x == 0.0f || y == 0.0f || diff < FLT_MIN)
    return diff < (abs_epsf*FLT_MIN);
  else
    return diff/(fabsf(x) + fabsf(y)) < abs_epsf;
}

static inline int fequals(double x, double y)
{
  const double abs_eps = 1.1 * DBL_EPSILON;
  const double diff = fabs(x - y);
  
  if (x == y)
    return true;
  else if (x == 0.0 || y == 0.0 || diff < DBL_MIN)
    return diff < (abs_eps*DBL_MIN);
  else
    return diff/(fabs(x) + fabs(y)) < abs_eps;
}



// misc.c
static inline int is_Rnull(SEXP x)
{
  R_INIT;
  SEXP basePackage;
  SEXP tmp;
  
  PT( basePackage = eval( lang2( install("getNamespace"), ScalarString(mkChar("base")) ), R_GlobalEnv ) );
  
  tmp = eval( lang2( install("is.null"), x), basePackage);
  
  R_END;
  return INT(tmp,0);
}

static inline int is_Rnan(SEXP x)
{
  R_INIT;
  SEXP basePackage;
  SEXP tmp;

  PT( basePackage = eval( lang2( install("getNamespace"), ScalarString(mkChar("base")) ), R_GlobalEnv ) );

  tmp = eval( lang2( install("is.nan"), x), basePackage);

  R_END;
  return INT(tmp,0);
}

static inline int is_Rna(SEXP x)
{
  R_INIT;
  SEXP basePackage;
  SEXP tmp;
  
  PT( basePackage = eval( lang2( install("getNamespace"), ScalarString(mkChar("base")) ), R_GlobalEnv ) );
  
  tmp = eval( lang2( install("is.na"), x), basePackage);
  
  R_END;
  return INT(tmp,0);
}

static inline int is_double(SEXP x)
{
  R_INIT;
  SEXP basePackage;
  SEXP tmp;
  
  PT( basePackage = eval( lang2( install("getNamespace"), ScalarString(mkChar("base")) ), R_GlobalEnv ) );
  
  tmp = eval( lang2( install("is.double"), x), basePackage);
  
  R_END;
  return INT(tmp,0);
}

static inline int is_integer(SEXP x)
{
  R_INIT;
  SEXP basePackage;
  SEXP tmp;
  
  PT( basePackage = eval( lang2( install("getNamespace"), ScalarString(mkChar("base")) ), R_GlobalEnv ) );
  
  tmp = eval( lang2( install("is.integer"), x), basePackage);
  
  R_END;
  return INT(tmp,0);
}



// printing.c
static inline void PRINT(SEXP x)
{
  R_INIT;
  SEXP basePackage;
  
  PT( basePackage = eval( lang2( install("getNamespace"), ScalarString(mkChar("base")) ), R_GlobalEnv ) );
  
  eval( lang2( install("print"), x), basePackage);
  
  R_END;
}



// structures_misc.c
static inline void set_list_names(SEXP R_list, SEXP R_names)
{
  setAttrib(R_list, R_NamesSymbol, R_names);
}

static inline void set_df_rownames(SEXP R_df, SEXP R_rownames)
{
  setAttrib(R_df, R_RowNamesSymbol, R_rownames);
}

static inline void set_df_colnames(SEXP R_df, SEXP R_colnames)
{
  set_list_names(R_df, R_colnames);
}

static inline void set_list_as_df(SEXP R_list)
{
  setAttrib(R_list, R_ClassSymbol, mkString("data.frame"));
}



// structures_dataframes.c
static inline SEXP make_dataframe_default_colnames(const int n)
{
  R_INIT;
  int i;
  int buflen;
  SEXP ret;
  
  buflen = (int) (ceil(log10((double)n)) + 1.);
  char *buf = malloc(buflen * sizeof(*buf));
  buf[0] = 'X';
  
  newRlist(ret, n);
  
  for (i=0; i<n; i++)
  {
    sprintf(buf+1, "%d", i+1);
    buflen = (int) (ceil(log10((double)i+2)) + 1.);
    buflen = RNACIMAX(buflen, 2);
    SET_VECTOR_ELT(ret, i, mkCharLen(buf, buflen));
  }
  
  free(buf);
  
  R_END;
  return ret;
}

static inline SEXP make_dataframe_default_rownames(int n)
{
  R_INIT;
  int i;
  SEXP ret_names;
  
  newRvec(ret_names, n, "int");
  
  for(i=0; i<n; i++)
    INT(ret_names,i) = i + 1;
  
  R_END;
  return ret_names;
}

static inline SEXP make_dataframe(SEXP R_rownames, SEXP R_colnames, int n, ...)
{
  R_INIT;
  int i;
  SEXP R_df;
  SEXP R_default_rownames;
  SEXP R_default_colnames;
  SEXP tmp;
  va_list listPointer;
  
  // Construct list
  newRlist(R_df, n);
  
  va_start(listPointer, n);
  
  for(i=0; i<n; i++)
  {
    tmp = va_arg(listPointer, SEXP);
    
    SET_VECTOR_ELT(R_df, i, tmp);
  }
  
  va_end(listPointer);
  
  // Set names
  set_list_as_df(R_df);
  
  if (is_Rnull(R_rownames))
  {
    R_default_rownames = make_dataframe_default_rownames(n);
    set_df_rownames(R_df, R_default_rownames);
  }
  else
    set_df_rownames(R_df, R_rownames);
  
  if (is_Rnull(R_colnames))
  {
    R_default_colnames = make_dataframe_default_colnames(n);
    set_df_colnames(R_df, R_default_colnames);
  }
  else
    set_df_colnames(R_df, R_colnames);
  
  
  R_END;
  return R_df;
}



// structures_lists.c
static inline SEXP make_list_names(int n, ...)
{
  R_INIT;
  int i;
  char *tmp;
  SEXP R_list_names;
  va_list listPointer;
  
  newRvec(R_list_names, n, "str");
  
  va_start(listPointer, n);
  
  for(i=0; i<n; i++)
  {
    tmp = va_arg(listPointer, char *);
  
    SET_STRING_ELT(R_list_names, i, mkChar(tmp));
  }
  
  va_end(listPointer);
  
  R_END;
  return R_list_names;
}

static inline SEXP make_list(SEXP R_list_names, const int n, ...)
{
  R_INIT;
  int i;
/*  const int n = LENGTH(R_list_names);*/
  SEXP tmp, R_list;
  va_list listPointer;
  
  newRlist(R_list, n);
  
  va_start(listPointer, n);
  
  for(i=0; i<n; i++)
  {
    tmp = va_arg(listPointer, SEXP);
  
    SET_VECTOR_ELT(R_list, i, tmp);
  }
  
  va_end(listPointer);
  
/*  setAttrib(R_list, R_NamesSymbol, R_list_names);*/
  if (!is_Rnull(R_list_names))
    set_list_names(R_list, R_list_names);
  
  R_END;
  return R_list;
}


#endif
