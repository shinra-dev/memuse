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
  
  if (ICTXT==0)
    PROCS <- optimal.grid(nprocs)
  else if (ICTXT==1)
    PROCS <- c(1, nprocs)
  else if (ICTXT==2)
    PROCS <- c(nprocs, 1)
  else 
    stop("ICTXT must be 0, 1, or 2")
  
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

