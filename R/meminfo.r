get.os <- function() Sys.info()[1L]


meminfo <- function(compact.free=TRUE, show.virtual=FALSE)
{
  out <- .Call("R_meminfo", PACKAGE="memuse")
  
  os <- get.os()
  
  if (any(unlist(out) == -1))
    stop("platform not supported at this time")
  
#  out <- lapply(out, function(x) {if (x == -10) NULL else x})
  
  ret <- lapply(out, mu)
  
  if (os == "Linux" && compact.free)
  {
    ret$freeram <- ret$freeram + ret$bufferram + ret$cachedram
    ret$bufferram <- NULL
    ret$cachedram <- NULL
  }
  
  if (!show.virtual)
  {
    if (os == "Linux")
    {
      ret$totalswap <- NULL
      ret$freeswap <- NULL
    }
    else if (os == "Windows")
    {
      ret$totalpage <- NULL
      ret$freepage <- NULL
    }
  }
  
  return( ret )
}
