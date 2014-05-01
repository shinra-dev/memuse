get.os <- function() Sys.info()[1L]


meminfo <- function(compact.free=TRUE, show.virtual=FALSE)
{
  out <- .Call("R_meminfo", PACKAGE="memuse")
  
  os <- get.os()
  
  if (any(unlist(out) == -1))
    stop("There were errors accessing hardware info")
  else if (any(unlist(out) == -10))
    stop("platform not supported at this time")
  
  ret <- lapply(out, mu)
  
  if (os == "Linux" && compact.free)
  {
    ret$freeram <- ret$freeram + ret$bufferram + ret$cachedram
    ret$bufferram <- ret$cachedram <- NULL
  }
  
  if (!show.virtual)
  {
    if (os == "Linux")
      ret$totalswap <- ret$freeswap <- ret$swapcached <- NULL
    else if (os == "Windows")
      ret$totalpage <- ret$freepage <- NULL
    else if (os == "FreeBSD")
      ret$totalswap <- NULL
  }
  else
  {
    if (os != "Linux" && os != "Windows" && os != "Mac")
      warning("show.virtual=TRUE is unsupported for this platform")
  }
  
  return( ret )
}


