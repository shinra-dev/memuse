meminfo_retvals <- function(retval)
{
  if (length(retval) > 1)
    return(sapply(retval, meminfo_retvals))
  
  .Call(R_meminfo_retvals, as.integer(retval))
}



#' meminfo
#' 
#' Platform memory information.
#' 
#' \code{Sys.meminfo()} returns some basic memory values, such as total ram,
#' free ram, and ram used for buffers/cache (when applicable).
#' 
#' All of the C-level source code for these methods (in src/meminfo of the root
#' directory of the memuse source tree) is licensed under the permissive
#' 2-Clause BSD license.
#' 
#' @param compact.free 
#' logical; determines whether various free memory values
#' should be combined into a single value. See details section for more
#' information.
#' 
#' @return 
#' Returns a list, whose values are platform dependent in addition to
#' being modified by input arguments.
#' 
#' @examples
#' \dontrun{
#' library(memuse)
#' 
#' Sys.meminfo()
#' }
#' 
#' @seealso \code{\link{procmem}}
#' @name meminfo
#' @rdname meminfo
#' @export
Sys.meminfo <- function(compact.free=TRUE)
{
  out <- .Call(R_meminfo_raminfo)
  
  if (any(unlist(out) == -1))
    stop("There were errors accessing hardware info")
  
  if (all(unlist(out) == -10))
    stop("platform not supported at this time")
  
  tmp <- -which(out == -10)
  if (length(tmp) > 0)
    out <- out[tmp]
  
  ret <- lapply(out, mu)
  
  
  
  if (compact.free)
  {
    ret$freeram <- val_or_zero(ret$freeram) + val_or_zero(ret$bufferram) + val_or_zero(ret$cachedram)
    ret$bufferram <- ret$cachedram <- NULL
  }
  
  class(ret) <- "sysinfo"
  
  return( ret )
}



#' swapinfo
#' 
#' Platform swap information.
#' 
#' \code{Sys.swapinfo()} returns basic swap/page (virtual memory) information.
#' \code{Sys.pageinfo()} is identical to \code{swapinfo()} in every way but
#' name (provided for Windows users who may be more comfortable/familiar with
#' the 'pagefile' naming convention).
#' 
#' All of the C-level source code for these methods (in src/meminfo of the root
#' directory of the memuse source tree) is licensed under the permissive
#' 2-Clause BSD license.
#' 
#' @return 
#' Returns a list, whose values are platform dependent in addition to
#' being modified by input arguments.
#' 
#' @examples
#' \dontrun{
#' library(memuse)
#' 
#' Sys.swapinfo()
#' }
#' 
#' @seealso \code{\link{procmem}}
#' @name swapinfo
#' @rdname swapinfo
#' @export
Sys.swapinfo <- function()
{
  out <- .Call(R_meminfo_swapinfo)
  
  if (any(unlist(out) == -1))
    stop("There were errors accessing hardware info")
  
  if (all(unlist(out) == -10))
    stop("platform not supported at this time")
  
  tmp <- -which(out == -10)
  if (length(tmp) > 0)
    out <- out[tmp]
  
  ret <- lapply(out, mu)
  class(ret) <- "sysinfo"
  
  return( ret )
}

#' @rdname swapinfo
#' @export
Sys.pageinfo <- Sys.swapinfo



# ---------------------------------------------------------
# Current R process memory usage
# ---------------------------------------------------------

#' procmem
#' 
#' Shows the amount of ram used by the current R process.
#' 
#' \code{Sys.procmem()} returns the total memory usage of the current R
#' process, and (if supported), the maximum memory usage as well.
#' 
#' All of the C-level source code for these methods (in src/meminfo of the root
#' directory of the memuse source tree) is licensed under the permissive
#' 2-Clause BSD license.
#' 
#' @param gcFirst 
#' logical; determines if garbage collection should be called
#' before getting process memory usage.
#' 
#' @return 
#' Returns a list, whose values are platform dependent in addition to
#' being modified by input arguments.
#' 
#' @examples
#' \dontrun{
#' library(memuse)
#' 
#' ### How much is being used?
#' Sys.procmem()
#' 
#' ### Use more.
#' x <- rnorm(1e7)
#' Sys.procmem()
#' 
#' ### Use less.
#' rm(x)
#' gc(FALSE)
#' Sys.procmem()
#' }
#' 
#' @seealso \code{\link{meminfo}}
#' @name procmem
#' @rdname procmem
#' @export
Sys.procmem <- function(gcFirst=TRUE)
{
  if (gcFirst)
    gc(FALSE)
  
  out <- .Call(R_meminfo_procinfo)
  
  if (any(unlist(out) == -1))
    stop("There were errors accessing process info")
  
  if (all(unlist(out) == -10))
    stop("platform not supported at this time")
  
  tmp <- -which(out == -10)
  if (length(tmp) > 0)
    out <- out[tmp]
  
  ret <- lapply(out, mu)
  
  class(ret) <- "sysinfo"
  
  return( ret )
}



# ---------------------------------------------------------
# Cache sizes
# ---------------------------------------------------------

getcache <- function(level) .Call(R_meminfo_cacheinfo_size, level)


#' Cache Sizes
#' 
#' Shows the sizes of the CPU caches.
#' 
#' \code{Sys.cachesize()} will check the various levels of cache and return all
#' available cache information in a list.  If you don't have some kind of
#' level-1 cache, then it will return an error.  If you have some kind of
#' future space computer with more than 3 levels of cache, levels higher than 3
#' will not be displayed.
#' 
#' @return 
#' Returns a list, whose values are platform dependent.
#' 
#' @examples
#' \dontrun{
#' library(memuse)
#' 
#' Sys.cachesize()
#' }
#' 
#' @seealso \code{\link{meminfo}}
#' @name cachesize
#' @rdname cachesize
#' @export
Sys.cachesize <- function()
{
  levels <- 0L:4L
  
  ret <- sapply(levels, getcache)
  
  names(ret) <- c("L1I", "L1D", "L2", "L3", "L4")
  
  if (all(ret < 0))
    stop("platform not supported at this time")
  else if (any(ret < 0))
    ret <- ret[which(ret > 0)]
  
  ret <- sapply(ret, mu)
  
  class(ret) <- "sysinfo"
  
  return( ret )
}



#' Cache Sizes and Linesize
#' 
#' Shows the size of the cache line.
#' 
#' \code{Sys.cachelinesize()} will return the cache linesize.  It's almost
#' certainly 32 or 64 bytes.
#' 
#' @return 
#' Returns a list, whose values are platform dependent.
#' 
#' @examples
#' \dontrun{
#' library(memuse)
#' 
#' Sys.cachelinesize()
#' }
#' 
#' @seealso \code{\link{meminfo}}
#' @name cachelinesize
#' @rdname cachelinesize
#' @export
Sys.cachelinesize <- function()
{
  ret <- .Call(R_meminfo_cacheinfo_linesize)
  
  
  if (ret < 0)
    stop("platform not supported at this time")
  
  ret <- list(Linesize=mu(ret))
  
  class(ret) <- "sysinfo"
  
  return( ret )
}



# ---------------------------------------------------------
# File sizes
# ---------------------------------------------------------

#' filesize
#' 
#' Returns size of a file as reported by the file system (the
#' file is not scanned).
#' 
#' All of the C-level source code for these methods (in src/meminfo of the root
#' directory of the memuse source tree) is licensed under the permissive
#' 2-Clause BSD license.
#' 
#' @param filename
#' Location of the file (as a string).
#' 
#' @return 
#' A memuse class object.
#' 
#' @examples
#' \dontrun{
#' library(memuse)
#' 
#' x <- rnorm(1e5)
#' object.size(x) ### size in ram
#' 
#' tmp <- tempfile()
#' saveRDS(x, file=tmp)
#' Sys.filesize(tmp) ### size on disk
#' unlink(tmp)
#' }
#' 
#' @name filesize
#' @rdname filesize
#' @export
Sys.filesize <- function(filename)
{
  filename <- tools::file_path_as_absolute(filename)
  ret <- .Call(R_meminfo_filesize, filename)
  
  ret <- mu(ret)
  
  return( ret )
}



# ---------------------------------------------------------
# Print handling
# ---------------------------------------------------------

title_case <- function(x) gsub(x, pattern="(^|[[:space:]])([[:alpha:]])", replacement="\\1\\U\\2", perl=TRUE)


#' @title Print sysinfo objects.
#' 
#' @param x 
#' An sysinfo object.
#' @param ... Additional arguments (ignored).
#' 
#' @name print-sysinfo
#' @rdname print-sysinfo
#' @method print sysinfo
#' @export
print.sysinfo <- function(x, ...)
{
  # So ugly it's beautiful
  maxlen <- max(sapply(names(x), nchar))
  names <- gsub(names(x), pattern="_", replacement=" ")
  names <- title_case(x=names)
  spacenames <- simplify2array(lapply(names, function(str) paste0(str, ":", paste0(rep(" ", maxlen-nchar(str)), collapse=""))))
  
  maxlen <- max(sapply(x, function(y) nchar(paste(y))))
  prespaces <- simplify2array(lapply(x, function(y) paste0(rep(" ", maxlen-nchar(paste(y))), collapse="")))
  
  lapply(1:length(x), function(i) cat(paste(spacenames[i], prespaces[i], x[[i]], sep=" ", collapse="\n"), "\n"))
#  cat("\n")
  
  invisible()
}



#' @export
"[.sysinfo" <- function(x, i)
{
  class(x) <- NULL
  ret <- x[i]
  if (length(ret) > 0)
    class(ret) <- "sysinfo"
  else
    return(numeric(0))
  
  return(ret)
}

