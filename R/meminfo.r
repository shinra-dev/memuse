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
  
  .Call("R_meminfo_retvals", as.integer(retval), PACKAGE="memuse")
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
  out <- .Call("R_meminfo", PACKAGE="memuse")
  
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
  out <- .Call("R_swapinfo", PACKAGE="memuse")
  
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
# A more boring implementation --- this actually came 
# second, believe it or not
# ---------------------------------------------------------


meminfo.linux.clean <- function(x)
{
  x <- unlist(strsplit(gsub(x=x, " +", replacement=" "), split=" "))
  
  ret <- mu(as.numeric(x[2L]), unit=x[3L])
  
  return( ret )
}



meminfo.linux <- function()
{
  mem <- readLines("/proc/meminfo")
  
  ### Ram
  ind <- grep(mem, pattern="MemTotal:")
  totalram <- meminfo.linux.clean(x=mem[ind])
  
  ind <- grep(mem, pattern="MemFree:")
  freeram <- meminfo.linux.clean(x=mem[ind])
  
  ind <- grep(mem, pattern="Buffers:")
  bufferram <- meminfo.linux.clean(x=mem[ind])
  
  ind <- grep(mem, pattern="^Cached:")
  cachedram <- meminfo.linux.clean(x=mem[ind])
  
  ### Swap
  ind <- grep(mem, pattern="SwapTotal:")
  totalswap <- meminfo.linux.clean(x=mem[ind])
  
  ind <- grep(mem, pattern="SwapFree:")
  freeswap <- meminfo.linux.clean(x=mem[ind])
  
  ind <- grep(mem, pattern="SwapCached:")
  swapcached <- meminfo.linux.clean(x=mem[ind])
  
  
  ret <- list(totalram=totalram, freeram=freeram, bufferram=bufferram, cachedram=cachedram, 
              totalswap=totalswap, freeswap=freeswap, swapcached=swapcached)
  
  return( ret )
}



meminfo.freebsd.clean <- function(str)
{
  out <- system(paste("sysctl", str), intern=TRUE)
  ret <- mu(as.numeric(sub(x=out, pattern=paste(str, ": ", sep=""), replacement="")))
  
  return( ret )
}

meminfo.freebsd <- function()
{
  str <- "hw.pagesize"
  pagesize <- meminfo.freebsd.clean(str)
  
  ### Ram
  str <- "hw.physmem"
  totalram <- meminfo.freebsd.clean(str)
  
  str <- "vm.stats.vm.v_free_count"
  freeram <- meminfo.freebsd.clean(str) * pagesize
  
  str <- "vm.stats.vm.v_active_count"
  bufferram <- meminfo.freebsd.clean(str) * pagesize
  
  str <- "vm.stats.vm.v_cache_count"
  cachedram <- meminfo.freebsd.clean(str) * pagesize
  
  ### Swap
  str <- "vm.swap_total"
  totalswap <- meminfo.freebsd.clean(str) * pagesize
  
  
  ret <- list(totalram=totalram, freeram=freeram, bufferram=bufferram, cachedram=cachedram, totalswap=totalswap)
}


# ---------------------------------------------------------
# Current R process memory usage
# ---------------------------------------------------------


meminfo.process <- function(gcFirst=TRUE)
{
  if (gcFirst)
    gc(FALSE)
  
  out <- .Call("R_memuse_process_size", PACKAGE="memuse")
  
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

cachesize <- function()
{
  levels <- 1L:3L
  
  ret <- sapply(levels, function(level) .Call("R_cachesize", level, PACKAGE="memuse"))
  
  names(ret) <- paste("l", levels, sep="")
  
  if (all(ret < 0))
  {
    if (1L %in% levels || cachesize(levels=1L)[[1L]]@size < 0)
      stop("platform not supported at this time")
    else
      stop("requested levels not available")
  }
  if (any(ret < 0))
  {
    ret <- ret[which(ret > 0)]
  }
  
  ret <- sapply(ret, mu)
  
  return( ret )
}




cachelinesize <- function()
{
  ret <- .Call("R_cachelinesize", PACKAGE="memuse")
  
  
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

