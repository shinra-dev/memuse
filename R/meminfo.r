get.os <- function() Sys.info()[1L]


val_or_zero <- function(x)
{
  if (is.null(x))
    return(0)
  else
    return(x)
}



meminfo_retvals <- function(retval)
{
  if (length(retval) > 1)
    return(sapply(retval, meminfo_retvals))
  
  .Call(R_meminfo_retvals, as.integer(retval))
}



meminfo <- function(compact.free=TRUE)
{
  os <- get.os()
  
  ret <- meminfo.c()
  
  
  if (compact.free)
  {
    ret$freeram <- val_or_zero(ret$freeram) + val_or_zero(ret$bufferram) + val_or_zero(ret$cachedram)
    ret$bufferram <- ret$cachedram <- NULL
  }
  
  
  return( ret )
}




meminfo.c <- function()
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
  
  return( ret )
}




swapinfo <- function()
{
  os <- get.os()
  
  ret <- swapinfo.c()
  
  return( ret )
}


swapinfo.c <- function()
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
  
  return( ret )
}


pageinfo <- swapinfo



# ---------------------------------------------------------
# Current R process memory usage
# ---------------------------------------------------------


meminfo.process <- function(gcFirst=TRUE)
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
  
  return( ret )
}



# ---------------------------------------------------------
# Cache sizes
# ---------------------------------------------------------

getcache <- function(level) .Call(R_meminfo_cacheinfo_size, level)

cachesize <- function()
{
  levels <- 0L:3L
  
  ret <- sapply(levels, getcache)
  
  names(ret) <- c("L1I", "L1D", "L2", "L3")
  
  if (all(ret < 0))
    stop("platform not supported at this time")
  else if (any(ret < 0))
    ret <- ret[which(ret > 0)]
  
  ret <- sapply(ret, mu)
  
  return( ret )
}



cachelinesize <- function()
{
  ret <- .Call(R_meminfo_cacheinfo_linesize)
  
  
  if (ret < 0)
    stop("platform not supported at this time")
  
  ret <- mu(ret)
  
  return( ret )
}


# ---------------------------------------------------------
# Exported names
# ---------------------------------------------------------

Sys.meminfo <- meminfo
Sys.swapinfo <- swapinfo
Sys.pageinfo <- swapinfo
Sys.procmem <- meminfo.process
Sys.cachesize <- cachesize
Sys.cachelinesize <- cachelinesize

