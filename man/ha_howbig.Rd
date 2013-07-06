\name{howbig}

\alias{howbig}
\alias{howbig.par}


\title{ How Big in Memory is a Matrix with Known Rows/Cols }
\description{
  Determines the memory usage for a dense, in-core, numeric matrix.
}
\usage{
  howbig(nrow, ncol, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES, 
         ..., type="double", intsize=4)
  howbig.par(nrow, ncol, cores, par="dmat", unit=.UNIT, unit.prefix=.PREFIX, 
             unit.names=.NAMES, ..., type="double", intsize=4, ICTXT=0)
}
\arguments{
  \item{nrow, ncol}{Number of (global) rows/columns of the matrix.}
  \item{cores}{The number
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
  These functions provide the memory usage of an unallocated, dense, 
  in-core, numeric matrix.  As the names suggest, \code{howbig()} simply
  returns the size (as a \code{memuse} object), while \code{howbig.par()}
  is the parallel, distributed analogue.  The latter returns the memory
  usage of a \emph{distributed}, object
}
\value{
  Returns a \code{memuse} class object.
}
\seealso{
  \code{\link{Constructor}, \link{memuse-class}}
}
\examples{
x <- mu(200)
y <- mu(100)

x+y
x-y
x*y
x/y
x^2
}
\keyword{Methods}
