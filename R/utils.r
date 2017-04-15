# Constructor error message
mu_error <- function() stop("Badly formed 'memuse' object", call.=FALSE)



check_type <- function(type, intsize)
{
  if (type == "double")
    bytes <- 8
  else if (type == "integer")
    bytes <- intsize
  
  return( bytes )
}



# Function to grab the printable units from the convoluted .units data structure
get_units <- function(x)
{
  return( .units[[x@unit.names]][[x@unit.prefix]][["print"]] )
}



# Get the correct power for the factor that determines which unit is to be used
get_power <- function(x)
{
  units <- get_units(x)
  
  power <- which(units == x@unit)
  
  if (length(power) > 0)
    return( power - 1L )
  else
    mu_error()
}



# Convert a memuse object to one stored in bytes
convert_to_bytes <- function(x)
{
  size <- x@size
  
  n <- which(x@unit == .units[[x@unit.names]][[x@unit.prefix]][["print"]]) - 1
  
  if (x@unit.prefix == "IEC")
    f <- 1024
  else if (x@unit.prefix == "SI")
    f <- 1e3
  else 
    mu_error()
  
#  size <- size * f^n
  size <- abc(size, f, n)
  
  x@size <- size
  x@unit <- .units[[x@unit.names]][[x@unit.prefix]][["print"]][1L]
  
  return( x )
}



# Find the best unit representation for an object
best.unit <- function(x)
{
  if (x@unit.prefix == "IEC"){
    f <- 1024
    fun <- function(x) log2(abs(x))
    dgts <- 10
  } else if (x@unit.prefix == "SI"){
    f <- 1e3
    fun <- function(x) log10(abs(x))
    dgts <- 3
  } else {
    mu_error()
  }
  
  size <- convert_to_bytes(x)@size
  
  if (size == 0){
    x@unit.names <- .units[[x@unit.names]][[x@unit.prefix]][["print"]][1L]
    return( x )
  }
  
  
  num.digits <-fun(size)
    
  for (i in seq.int(9)){
    if (num.digits < dgts*i){
      unit <- .units[i]
      break
    }
  }
  
  size <- size/(f^(i-1))
  
  x@size <- size
  x@unit <- .units[[x@unit.names]][[x@unit.prefix]][["print"]][i]
  
  return( x )
}



# stable a*b^c with c an integer
abc <- function(a, b, c)
{
  if (c==0)
    return(a)
  p <- a
  for (i in seq.int(c)){
    p <- p*b
  }
  
  return( p )
}



# whole number checker
is.int <- function(x)
{
  # IEEE arithmetic gives 52 bit mantissa, so instead of doing that
  # weird shit R suggests in help('is.integer'), we will just use
  # machine epsilon for the tolerance.  Deal with it, nerd.
  # With this tolerance, this is probably equivalent to just doing
  # x==floor(x), but for some reason this makes me less nervous.
  tol <- 2^(-53)
  
  if (!is.numeric(x))
    return( FALSE )
  else
    return( abs(x - floor(x)) < tol )
}



# return the value or 0 if NULL
val_or_zero <- function(x)
{
  if (is.null(x))
    return(0)
  else
    return(x)
}



# Zero's digits of a string after the first 15 digits
digits2zero <- function(str)
{
  if (nchar(str) <= 15)
    return( str )
  
  split <- simplify2array(strsplit(x=str, split=""))
  
  n <- length(split) - 15L
  ret <- paste(paste(split[1L:15L], collapse=""), paste(rep(0, n), collapse=""), collapse="", sep="")
  
  return( ret )
}



# ------------------------------------------------------------------------------
# Parallel utilities
# ------------------------------------------------------------------------------

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
