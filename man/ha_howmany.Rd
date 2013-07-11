\name{howmany}

\alias{howmany-method}
\alias{howmany,memuse-method}
\alias{howmany}

\title{ How Many Rows/Cols of a Matrix for a Memory Size }
\description{
  Binary arithmetic operations for \code{memuse} objects.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "memuse", y = "memuse")}}{}
\item{\code{signature(x = "numeric", y = "memuse")}}{}
\item{\code{signature(x = "memuse", y = "numeric")}}{}
}
}
\usage{
  \S4method{howmany}{memuse}(x, nrow, ncol, unit=.UNIT, unit.prefix=.PREFIX,
  unit.names=.NAMES, ..., type="double", intsize=4)
}
\arguments{
  \item{x}{The size of a matrix stored as a \code{memuse} class object.}
  \item{nrow, ncol}{Number of (global) rows/columns of the matrix.}
  \item{unit}{string; the unit of storage, such as "MiB" or "MB", 
  depending on prefix.  Case is ignored.}
  \item{unit.prefix}{string; the unit prefix, namely IEC or SI.  Case 
  is ignored.}
  \item{unit.names}{string; control for whether the unit names should 
  be printed out or their abbreviation should be used.  Options are 
  "long" and "short", respectively.  Case is ignored.}
  \item{...}{Additional arguments.}
  \item{type}{"double" or "int"; the storage type of the data matrix.
  If you don't know the type, it is probably stored as a double, so 
  the default value will suffice.}
  \item{intsize}{The size (in bytes) of an integer.  Default is 4, but
  this is platform dependent.}
}
\details{
  This function provides the maximum dimension of an unallocated, dense, 
  in-core, numeric matrix of known byte size. For example, it will show
  the largest possible square matrix which is 16 GiB (46340x46340).
  
  If the both \code{nrow} and \code{ncol} are missing (blank inputs), then
  the largest square matrix will be returned.  If one of \code{nrow} or 
  \code{ncol} is supplied and the other is missing, then the non-supplied
  argument (\code{nrow} or \code{ncol}) will be determined according to the
  supplied one.  If both arguments are supplied, an error is produced ---
  you probably meant to use \code{howmany()}.
}
\value{
  Returns a numeric pair, the dimensions of a matrix.
}
\seealso{
  \code{\link{howbig}}
}
\examples{
x <- mu(1, "gib")

# largest square matrix that's 1 GiB
howmany(x)
}
\keyword{Methods}
