get.os <- function() Sys.info()[1L]


meminfo <- function(compact.free=TRUE)
{
  os <- get.os()
  
  ret <- meminfo.c()
  
  
#  if (compact.free)
#  {
#    if (os == "Linux")
#    {
#      ret$freeram <- ret$freeram + ret$bufferram + ret$cachedram
#      ret$bufferram <- ret$cachedram <- NULL
#    }
#    else if (os == "FreeBSD")
#      ret$bufferram <- ret$cachedram <- NULL
#  }
#  else
#  {
#    if (os != "Linux" && os != "FreeBSD")
#      warning(paste("compact.free=FALSE is not supported on", os))
#  }
#  
#  
#  if (!show.virtual)
#  {
#    if (os == "Linux")
#      ret$totalswap <- ret$freeswap <- ret$cachedswap <- NULL
#    else if (os == "Windows")
#      ret$totalpage <- ret$freepage <- NULL
#    else if (os == "FreeBSD")
#      ret$totalswap <- NULL
#  }
#  else
#  {
#    if (os != "Linux" && os != "Windows" && os != "Mac" && os != "FreeBSD")
#      warning(paste("show.virtual=TRUE is not supported on", os))
#  }
  
  
  return( ret )
}



meminfo.c <- function()
{
  out <- .Call("R_meminfo", PACKAGE="memuse")
  
  if (any(unlist(out) == -1))
    stop("There were errors accessing hardware info")
#  else if (any(unlist(out) == -10))
#    stop("platform not supported at this time")
  
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
#  else if (any(unlist(out) == -10))
#    stop("platform not supported at this time")
  
  ret <- lapply(out, mu)
  
  return( ret )
}



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
  
  
  ret <- list(totalram=totalram, freeram=freeram, bufferram=bufferram, cachedram=cachedram, totalswap=totalswap, freeswap=freeswap, swapcached=swapcached)
  
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


