\name{approx.size}
\alias{approx.size}

\title{ approx.size }
\description{
  Approximate size of an integer; a poor man's exponential notation.
}
\usage{
  approx.size(x, unit.names="long", ..., digits=1)
}
\arguments{
  \item{x}{A number.}
  \item{unit.names}{"long", "short", or "comma"; determines wheter the output 
  reads like "10 million", "10m", or "10,000,000", respectively.}
  \item{...}{Additional arguments}
  \item{digits}{The number of decimal digits to retain.}
}
\details{
  A simple printing system to make numbers readable.
}
\seealso{
  \code{\link{howmany}}
}
\examples{
\dontrun{
library(memuse)

approx.size(12345678)
approx.size(12345678, unit.names="comma")
}
}
