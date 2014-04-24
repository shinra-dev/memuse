\name{approx.size}
\alias{approx.size}

\title{ approx.size }
\description{
  Approximate size of an integer; a poor man's exponential notation.
}
\usage{
  approx.size(x, unit="best", unit.names="long", ..., digits=1)
}
\arguments{
  \item{x}{.}
  \item{unit}{.}
  \item{unit.names}{.}
  \item{...}{Additional arguments}
  \item{digits}{.}
}
\details{
  x
}
\value{
  .
}
\seealso{
  \code{\link{howmany}}
}
\examples{
approx.size(12345678)

approx.size(12345678, unit.names="comma")
}
\keyword{Methods}
