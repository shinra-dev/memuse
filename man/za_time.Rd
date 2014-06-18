\name{time}

\alias{wc.time}
\alias{print.timing}


\title{ Readable Timings }
\description{
  Printing timings in their "native" unit.  For example, "10000"
  seconds becomes "2.778 hours".  
  
  The wall-clock timer, \code{wc.time()}, is a simple wrapper 
  around R's \code{system.time()} using these readable units.
}
\usage{
  wc.time(expr, gcFirst=TRUE)
  \S3method{print}{timing}(x, digits=3, ...)
}
\arguments{
  \item{expr}{A valid R expression to be timed.}
  \item{gcFirst}{logical; determines if garbage collection should be
  called before getting process memory usage.}
  \item{x}{A count, in seconds, to be printed.}
  \item{digits}{The number of decimal digits to print.}
  \item{...}{Extra arguments (currently ignored).}
}
\details{
  This uses S3 methods for simplicity, though this makes some 
  higher abstractions impossible.  Future versions will likely 
  use S4.
}
\examples{
\dontrun{
library(memuse)

wc.time(rnorm(1e6))
}
}
\keyword{Methods}
