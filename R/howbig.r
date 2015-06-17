#' howbig
#' 
#' Determines the memory usage for a dense, in-core, numeric matrix of
#' specified rows/columns.
#' 
#' These functions provide the memory usage of an unallocated, dense, in-core,
#' numeric matrix.  As the names suggest, \code{howbig()} simply returns the
#' size (as a \code{memuse} object), while \code{howbig.par()} is the parallel,
#' distributed analogue.  The latter returns the memory usage of a
#' \emph{distributed}, object
#' 
#' @param nrow,ncol 
#' Number of (global) rows/columns of the matrix.
#' @param representation 
#' The kind of storage the object would be in, i.e. "dense" or "sparse".
#' @param cores 
#' The number of cores/processors
#' @param par 
#' Type of data distribution. Choices are "dmat" or "balanced". The
#' former is for \pkg{pbdDMAT} objects, the latter is the simple, locally
#' load-balanced block partitioning.
#' @param unit 
#' string; the unit of storage, such as "MiB" or "MB", depending on
#' prefix.  Case is ignored.
#' @param unit.prefix 
#' string; the unit prefix, namely IEC or SI.  Case is ignored.
#' @param unit.names 
#' string; control for whether the unit names should be
#' printed out or their abbreviation should be used.  Options are "long" and
#' "short", respectively.  Case is ignored.
#' @param ... 
#' Additional arguments.
#' @param sparsity 
#' The proportion of sparsity of the matrix if
#' \code{representation="sparse"}
#' @param type 
#' "double" or "int"; the storage type of the data matrix.  If you
#' don't know the type, it is probably stored as a double, so the default value
#' will suffice.
#' @param intsize 
#' The size (in bytes) of an integer.  Default is 4, but this is
#' platform dependent.
#' @param ICTXT 
#' BLACS context number; only used with \code{howbig.par()} with
#' \code{par="dmat"}.
#' @param bldim 
#' Blocking factor for block-cyclically decomposed (dmat) data.
#' @return \code{howbig()} 
#' returns a \code{memuse} class object.
#' 
#' \code{howbig.par()} returns a list of 2 elements, each of class
#' \code{memuse}.  One is the total memory usage, the other is the local memory
#' usage.
#' 
#' @examples
#' \dontrun{
#' # size of a 1000x1000 matrix
#' howbig(1000, 1000)
#' }
#' 
#' @seealso \code{\link{howmany}}
#' @keywords Methods
#' @name howbig
#' @rdname howbig
#' @export howbig
howbig <- function(nrow, ncol, representation="dense", unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES, ..., sparsity=0.05, type="double", intsize=4)
{
  type <- match.arg(tolower(type), c("double", "integer"))
  
  x <- internal.mu(size=1, unit="b", unit.prefix=unit.prefix, unit.names=unit.names)
  
  bytes <- check_type(type=type, intsize=intsize)
  
  x@size <- nrow*ncol*bytes # number of bytes used
  
  representation <- match.arg(tolower(representation), c("dense", "sparse"))
  
  if (representation == "sparse")
  {
    if (sparsity < 0 || sparsity > 1)
      stop("argument 'sparsity' should be between 0 and 1")
    else
      x <- sparsity * x
  }
  
  x <- swap.unit(x, unit)
  
  return( x )
}



#' @rdname howbig
#' @export
howbig.par <- function(nrow, ncol, cores=1, par="balanced", unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES, ..., type="double", intsize=4, ICTXT=0, bldim=c(4, 4))
{
  par <- match.arg(arg=tolower(par), choices=c("dmat", "balanced"))
  
  x <- howbig(nrow=nrow, ncol=ncol, unit=unit, unit.prefix=unit.prefix, unit.names=unit.names, type=type, intsize=intsize)
  
  # local
  if (par == "balanced") {
    y <- convert_to_bytes(x)
  
    y@size <- y@size / cores
    y <- swap.unit(y, unit)
    
    out <- list(total=x, local=y)
  }
  else if (par == "dmat") {
    ldim <- numroc(nprocs=cores, dim=c(nrow, ncol), bldim=bldim, ICTXT=ICTXT)
    
    z <- howbig(nrow=ldim[1L], ncol=ldim[2L], unit=unit, unit.prefix=unit.prefix, unit.names=unit.names, type=type, intsize=intsize)
    
    out <- list(total=x, local=z)
  } 
  
  return( out )
}

