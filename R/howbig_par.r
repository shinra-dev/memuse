howbig.par <- function(nrow, ncol, cores, par="balanced", unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES, ..., type="double", intsize=4, ICTXT=0)
{
  par <- match.arg(arg=tolower(par), choices=c("dmat", "balanced"))
  type <- match.arg(arg=tolower(type), choices=c("double", "integer"))
  
  x <- internal.mu(size=1, unit="b", unit.prefix=unit.prefix, unit.names=unit.names)
  
  if (type == "double")
    bytes <- 8
  else if (type == "integer")
    bytes <- intsize
  
  # total
  x@size <- nrow*ncol*bytes # number of bytes used
  
  x <- swap.unit(x, unit)
  
  # local
  if (par == "balanced") {
    y <- conver_to_bytes(x)
  
    y@size <- y@size / cores
    y <- swap.unit(y, unit)
    
    out <- list(total=x, local=y)
  }
  else if (par == "dmat") {
    ldim <- numroc(nprocs=cores, dim=c(nrow, ncol), bldim=c(4,4), ICTXT=ICTXT)
    
    z <- howbig(nrow=ldim[1], ncol=ldim[2], unit=unit, unit.prefix=unit.prefix, unit.names=unit.names, type=type, intsize=intsize)
    
    out <- list(total=x, local=z)
  } 
  
  return( out )
}

