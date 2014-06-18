\name{Converters}
\alias{Converters}
\docType{methods}

\alias{as.memuse}
\alias{as.memuse-method}
\alias{as.memuse,numeric-method}
\alias{as.memuse,object_size-method}
\alias{as.memuse,character-method}

\title{ Converters }
\description{
  Converter methods.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "memuse")}}{}
}
}
\usage{
\S4method{as.memuse}{numeric}(x, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
\S4method{as.memuse}{object_size}(x, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
\S4method{as.memuse}{character}(x, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
}
\arguments{
  \item{x}{Numeric value, object_size data, or appropriate string
  (see details section for more information).}
  \item{unit}{\code{string}; the unit of storage, such as "MiB" or "MB", 
  depending on prefix.  Case is ignored.}
  \item{unit.prefix}{\code{string}; the unit prefix, namely IEC or SI.  Case 
  is ignored.}
  \item{unit.names}{\code{string}; control for whether the unit names should 
  be printed out or their abbreviation should be used.  Options are 
  "long" and "short", respectively.  Case is ignored.}
}
\details{
  These methods convert numeric, \code{object_size}, and string 
  (character) objects into \code{memuse} objects.
  
  Strings must be of the same form as the printed output of a 
  a memuse object.  For example, "100 KiB" is valid, but 
  "100 (KiB)" is not.  As always, case of the unit is ignored, and
  so "100 kib" would be valid as well.
}
\value{
  Returns a \code{memuse} object.
}
\seealso{
  \code{
    \link{memuse-class}
    \link{Accessors}
  }
}
\examples{
as.memuse(10)
}
\keyword{Methods}
