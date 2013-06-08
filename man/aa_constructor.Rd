\name{Constructor}
\alias{Constructor}

\alias{memuse}
\alias{mu}


\title{ MemUse Constructor }
\description{
  Constructor for objects of class \code{memuse}.
}
\usage{
  memuse(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  mu(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
}
\arguments{
  \item{size}{numeric; indicates the unit-multiple number of bytes used
  by the object.}
  \item{unit}{string; the unit of storage, such as "MiB" or "MB", 
  depending on prefix.  Case is ignored.}
  \item{unit.prefix}{string; the unit prefix, namely IEC or SI.  Case 
  is ignored.}
  \item{unit.names}{string; control for whether the unit names should 
  be printed out or their abbreviation should be used.  Options are 
  "long" and "short", respectively.  Case is ignored.}
}
\details{
  deets
}
\value{
  Returns a memuse class object.
}
\seealso{
  \code{\link{Constructor}, \link{memuse-class}}
}
\examples{
x <- mu(100, unit="kb")
x

y <- mu(100, unit="kb", unit.prefix="SI")
y
}
\keyword{Methods}
