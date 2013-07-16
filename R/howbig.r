howbig <- function(nrow, ncol, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES, ..., type="double", intsize=4)
{
  type <- match.arg(tolower(type), c("double", "integer"))
  
  x <- internal.mu(size=1, unit="b", unit.prefix=unit.prefix, unit.names=unit.names)
  
  if (type == "double")
    bytes <- 8
  else if (type == "integer")
    bytes <- intsize
  
  x@size <- nrow*ncol*bytes # number of bytes used
  
  x <- swap.unit(x, unit)
  
  return( x )
}

