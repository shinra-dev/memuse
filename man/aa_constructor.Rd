\name{Constructor}
\alias{Constructor}
\docType{methods}

\alias{memuse}
\alias{memuse-method}
\alias{memuse,numeric-method}
\alias{memuse,object_size-method}

\alias{mu}
\alias{mu-method}
\alias{mu,numeric-method}
\alias{mu,object_size-method}

\title{ memuse Constructor }
\description{
  Constructor for objects of class \code{memuse}.
}
\usage{
\S4method{memuse}{numeric}(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
\S4method{mu}{numeric}(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
}
\arguments{
  \item{size}{\code{numeric}; indicates the unit-multiple number of bytes used
  by the object.}
  \item{unit}{\code{string}; the unit of storage, such as "MiB" or "MB", 
  depending on prefix.  Case is ignored.}
  \item{unit.prefix}{\code{string}; the unit prefix, namely IEC or SI.  Case 
  is ignored.}
  \item{unit.names}{\code{string}; control for whether the unit names should 
  be printed out or their abbreviation should be used.  Options are 
  "long" and "short", respectively.  Case is ignored.}
}
\details{
  Simple constructor for \code{memuse} objects.
}
\value{
  Returns a \code{memuse} class object.
}
\seealso{
  \code{
    \link{memuse-class}
    \link{Accessors}
    \link{Converters}
  }
}
\examples{
x <- mu(100, unit="kb")
x

y <- mu(100, unit="kb", unit.prefix="SI")
y
}
\keyword{Methods}
