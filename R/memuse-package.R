#' Core memuse Classes and Methods
#' 
#' Originally an amusing fancy printing system, this package contains that, as
#' well as some functionality for showing.  As of version 2.0, the package
#' contains some helpful utilities for accessing hardware ram information, ram
#' usage of the current R process, as well as some other niceties.
#' 
#' If you do a lot of benchmarking, this is the package you've been waiting
#' for.  Maybe.  I mean, I don't want to be too pushy about it.
#' 
#' @import methods
#' 
#' @useDynLib memuse,
#'   R_meminfo_retvals, R_meminfo_raminfo, R_meminfo_swapinfo,
#'   R_meminfo_procinfo, R_meminfo_cacheinfo_size, R_meminfo_cacheinfo_linesize,
#'   R_meminfo_filesize
#' 
#' @name memuse-package
#' @docType package
#' @author Drew Schmidt
#' @references Project home page: \url{https://shinra-dev.github.io}
#' @keywords Package
NULL
