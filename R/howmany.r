#' howmany
#' 
#' How many rows/columns of a matrix can be stored for a given memory size.
#' 
#' @details
#' This function provides the maximum dimension of an unallocated, dense,
#' in-core, numeric matrix of known byte size. For example, it will show the
#' largest possible square matrix which is 16 GiB (46340x46340).
#' 
#' If the both \code{nrow} and \code{ncol} are missing (blank inputs), then the
#' largest square matrix will be returned.  If one of \code{nrow} or
#' \code{ncol} is supplied and the other is missing, then the non-supplied
#' argument (\code{nrow} or \code{ncol}) will be determined according to the
#' supplied one.  If both arguments are supplied, an error is produced --- you
#' probably meant to use \code{howmany()}.
#' 
#' If \code{out.type="approximate"}, then a reduced representation of the
#' dimensions will be returned.  For example, the reduced representation of the
#' number 1234567890 would be "1.2b", since this number is basically 1.2
#' billion.  Not super useful, but kind of cute, and it arguably enhances
#' readability when fishing for a ballpark figure.
#' 
#' @param x 
#' The size of a matrix stored as a \code{memuse} class object.
#' @param nrow,ncol 
#' Number of (global) rows/columns of the matrix.
#' @param out.type 
#' If the full dimensions or a reduced representation should be
#' returned (see Details section below). Options are "full" and "approximate"
#' (with partial matching).
#' @param representation 
#' The kind of storage the object would be in, i.e.
#' "dense" or "sparse".
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
#' A numeric pair, the dimensions of a matrix.
#' 
#' @examples
#' \dontrun{
#' x <- mu(1, "gib")
#' 
#' # largest square matrix that's 1 GiB
#' howmany(x)
#' # same, but ballpark figure
#' howmany(mu(1, "gib"), out.type="approx")
#' }
#' 
#' @seealso \code{\link{howbig}}
#' @keywords Methods
#' @export
howmany <- function(x, nrow, ncol, out.type="full", representation="dense", ..., sparsity=0.05, type="double", intsize=4, names="short")
{
  if (!inherits(x, "memuse"))
    stop("input 'x' must be a memuse class object")
  
  # Manage input arguments
  out.type <- match.arg(arg=tolower(out.type), choices=c("full", "approximate"))
  representation <- match.arg(tolower(representation), c("dense", "sparse"))
  type <- match.arg(arg=tolower(type), choices=c("double", "integer"))
  
  bytes <- check_type(type=type, intsize=intsize)
  
  # Get the size
  size <- convert_to_bytes(x)@size
  
  if (!missing(nrow)){
    if (!is.int(nrow))
      stop("argument 'nrow' must be an integer")
    else if (!missing(ncol))
      stop("you should supply at most one of 'nrow' and 'ncol'.  Perhaps you meant to use howbig()?")
    else
      ncol <- floor(size/(nrow*bytes))
  }
  else if (!missing(ncol)){
    if (!is.int(ncol))
      stop("argument 'ncol' must be an integer")
    nrow <- floor(size/(ncol*bytes))
  }
  else
    nrow <- ncol <- floor(sqrt(size/bytes))
  
  # Return
  ret <- c(nrow, ncol)
  
  if (out.type == "approximate")
    ret <- hr(ret, names=names)
  
  ret
}
