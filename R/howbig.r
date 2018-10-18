#' howbig
#' 
#' Determines the memory usage for a dense, in-core, numeric matrix of
#' specified rows/columns.
#' 
#' @details
#' These functions provide the memory usage of an unallocated, dense, in-core,
#' numeric matrix.  As the name suggests, \code{howbig()} simply returns the
#' size (as a \code{memuse} object).
#' 
#' @param nrow,ncol 
#' Number of (global) rows/columns of the matrix.
#' @param representation 
#' The kind of storage the object would be in, i.e. "dense" or "sparse".
#' @param unit 
#' string; the unit of storage, such as "MiB" or "MB", depending on
#' prefix.  Case is ignored.
#' @param prefix 
#' string; the unit prefix, namely IEC or SI.  Case is ignored.
#' @param names 
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
#' 
#' @return
#' returns a \code{memuse} class object.
#' 
#' @examples
#' \dontrun{
#' # size of a 1000x1000 matrix
#' howbig(1000, 1000)
#' }
#' 
#' @seealso \code{\link{howmany}}
#' @export
howbig <- function(nrow=1, ncol=1, representation="dense", unit="best", prefix="IEC", names="short", ..., sparsity=0.05, type="double", intsize=4)
{
  type <- match.arg(tolower(type), c("double", "integer"))
  
  x <- internal.mu(size=1, unit="b", unit.prefix=prefix, unit.names=names)
  
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
  
  swap.unit(x, unit)
}
