meminfo <- function(compact.free=TRUE, show.swap=FALSE)
{
  out <- .Call("R_meminfo", PACKAGE="memuse")
  
  if (any(unlist(out) == -1))
    stop("platform not supported at this time")
  
  out <- lapply(out, function(x) {if (x == -10) NULL else x})
  
  ret <- lapply(out, mu)
  
  if (compact.free)
  {
    ret$freeram <- ret$freeram + ret$bufferram + ret$cachedram
    ret$bufferram <- NULL
    ret$cachedram <- NULL
  }
  
  if (!show.swap)
  {
    ret$totalswap <- NULL
    ret$freeswap <- NULL
  }
  
  return( ret )
}
