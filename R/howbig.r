howbig <- function(nrow, ncol, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES, ..., type="double", intsize=4)
{
  type <- match.arg(type, c("double", "integer"))
  
  x <- mu(size=1, unit="b", unit.prefix=unit.prefix, unit.names=unit.names)
  
  if (type == "double")
    bytes <- 8
  else if (type == "integer")
    bytes <- intsize
  
  x@size <- nrow*ncol*bytes # number of bytes used
  
  x <- swap.unit(x, unit)
  
  return( x )
}



howbig.par <- function(nrow, ncol, cores, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES, ..., type="double", intsize=4)
{
  type <- match.arg(type, c("double", "integer"))
  
  x <- mu(size=1, unit="b", unit.prefix=unit.prefix, unit.names=unit.names)
  
  if (type == "double")
    bytes <- 8
  else if (type == "integer")
    bytes <- intsize
  
  ### total
  x@size <- nrow*ncol*bytes # number of bytes used
  
  x <- swap.unit(x, unit)
  
  ### local
  y <- convert.to.bytes(x)
  
  y@size <- y@size / cores
  y <- swap.unit(y, unit)
  
  ldim <- numroc(nprocs=cores, dim=c(nrow, ncol), bldim=c(4,4), ICTXT=0)
  
  z <- howbig(m=ldim[1], n=ldim[2], unit=unit, unit.prefix=unit.prefix, unit.names=unit.names, type=type, intsize=intsize)
  
  out <- list(total=x, block=y, block.cyclic=z)
  
  return( out )
}



# needed for block-cyclic return
optimal.grid <- function(nprocs)
{
  n <- floor(sqrt(nprocs))
  
  for (i in 0:(n-1)){
    ncols <- n-i
    nrows <- floor(nprocs %% ncols)
    
    if (nrows == 0)
      break
  }
  
  nrows <- nprocs / ncols
  
  return(c(nrows, ncols))
}

numroc <- function(nprocs, dim, bldim, ICTXT=0)
{
  MYP <- c(0L, 0L)
  
  if (ICTXT==0){
    PROCS <- optimal.grid(nprocs)
  }
  else if (ICTXT==1){
    PROCS <- c(1, nprocs)
  }
  else {
    PROCS <- c(nprocs, 1)
  }
  
  ISRCPROC <- 0
  
  ldim <- numeric(2)
  for (i in 1:2){
    MYDIST <- (PROCS[i] + MYP[i] - ISRCPROC) %% PROCS[i]
    NBLOCKS <- floor(dim[i] / bldim[i])
    ldim[i] <- floor(NBLOCKS / PROCS[i]) * bldim[i]
    EXTRABLKS <- NBLOCKS %% PROCS[i]
    
    if (is.na(EXTRABLKS))
      EXTRABLKS <- 0
    
    if (MYDIST < EXTRABLKS)
      ldim[i] <- ldim[i] + bldim[i]
    else if (MYDIST == EXTRABLKS)
      ldim[i] <- ldim[i] + dim[i] %% bldim[i]
  }
  
  if (any(is.na(ldim)))
    ldim[which(is.na(ldim))] <- 0L
  if (any(ldim<1)) ldim <- c(0L, 0L)
  
  return(ldim)
}
