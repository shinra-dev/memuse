### utility functions for howbig.par(par="dmat")

# determine the optimal grid size (ICTXT=0)
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

# determine the local dimensions
numroc <- function(nprocs, dim, bldim, ICTXT=0)
{
  MYP <- c(0L, 0L)
  
  if (ICTXT==0){
    PROCS <- optimal.grid(nprocs)
  } else if (ICTXT==1){
    PROCS <- c(1, nprocs)
  } else if (ICTXT==2){
    PROCS <- c(nprocs, 1)
  } else {
    stop("ICTXT must be 0, 1, or 2")
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


### howbig.par
howbig.par <- function(nrow, ncol, cores, par="mpi", unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES, ..., type="double", intsize=4, ICTXT=0)
{
  par <- match.arg(tolower(par), c("dmat", "mpi"))
  type <- match.arg(tolower(type), c("double", "integer"))
  
  x <- mu(size=1, unit="b", unit.prefix=unit.prefix, unit.names=unit.names)
  
  if (type == "double")
    bytes <- 8
  else if (type == "integer")
    bytes <- intsize
  
  ### total
  x@size <- nrow*ncol*bytes # number of bytes used
  
  x <- swap.unit(x, unit)
  
  ### local
  if (par == "mpi") {
    y <- convert.to.bytes(x)
  
    y@size <- y@size / cores
    y <- swap.unit(y, unit)
    
    out <- list(total=x, local=y)
  } else if (par == "dmat") {
    ldim <- numroc(nprocs=cores, dim=c(nrow, ncol), bldim=c(4,4), ICTXT=ICTXT)
    
    z <- howbig(nrow=ldim[1], ncol=ldim[2], unit=unit, unit.prefix=unit.prefix, unit.names=unit.names, type=type, intsize=intsize)
    
    out <- list(total=x, local=z)
  } 
  
  return( out )
}

