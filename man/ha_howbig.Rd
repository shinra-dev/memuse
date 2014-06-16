\name{howbig}

\alias{howbig}
\alias{howbig.par}


\title{ howbig }
\description{
  Determines the memory usage for a dense, in-core, numeric matrix of
  specified rows/columns.
}
\usage{
  howbig(nrow, ncol, representation="dense", unit=.UNIT, unit.prefix=.PREFIX, 
  unit.names=.NAMES, ..., sparsity=0.05, type="double", intsize=4)
  howbig.par(nrow, ncol, cores=1, par="balanced", unit=.UNIT, 
			 unit.prefix=.PREFIX, unit.names=.NAMES, ..., type="double", 
			 intsize=4, ICTXT=0, bldim=c(4, 4))
}
\arguments{
  \item{nrow, ncol}{Number of (global) rows/columns of the matrix.}
  \item{representation}{The kind of storage the object would be in, 
  i.e. "dense" or "sparse".}
  \item{cores}{The number of cores/processors}
  \item{par}{Type of data distribution. Choices are "dmat" or "balanced". The
  former is for \pkg{pbdDMAT} objects, the latter is the simple, locally
  load-balanced block partitioning.}
  \item{unit}{string; the unit of storage, such as "MiB" or "MB", 
  depending on prefix.  Case is ignored.}
  \item{unit.prefix}{string; the unit prefix, namely IEC or SI.  Case 
  is ignored.}
  \item{unit.names}{string; control for whether the unit names should 
  be printed out or their abbreviation should be used.  Options are 
  "long" and "short", respectively.  Case is ignored.}
  \item{...}{Additional arguments.}
  \item{sparsity}{The proportion of sparsity of the matrix if
  \code{representation="sparse"}}
  \item{type}{"double" or "int"; the storage type of the data matrix.
  If you don't know the type, it is probably stored as a double, so 
  the default value will suffice.}
  \item{intsize}{The size (in bytes) of an integer.  Default is 4, but
  this is platform dependent.}
  \item{ICTXT}{BLACS context number; only used with \code{howbig.par()}
  with \code{par="dmat"}.}
  \item{bldim}{Blocking factor for block-cyclically decomposed (dmat) data.}
}
\details{
  These functions provide the memory usage of an unallocated, dense, 
  in-core, numeric matrix.  As the names suggest, \code{howbig()} simply
  returns the size (as a \code{memuse} object), while \code{howbig.par()}
  is the parallel, distributed analogue.  The latter returns the memory
  usage of a \emph{distributed}, object
}
\value{
  \code{howbig()} returns a \code{memuse} class object.
  
  \code{howbig.par()} returns a list of 2 elements, each of class
  \code{memuse}.  One is the total memory usage, the other is the 
  local memory usage.
}
\seealso{
  \code{\link{howmany}}
}
\examples{
# size of a 1000x1000 matrix
howbig(1000, 1000)
}
\keyword{Methods}
