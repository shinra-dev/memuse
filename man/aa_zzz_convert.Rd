\name{Converters}
\alias{Converters}
\docType{methods}

\alias{as.memuse}
\alias{as.memuse-method}
\alias{as.memuse,numeric-method}
\alias{as.memuse,object_size-method}

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
  \S4method{as.memuse}{numeric}(x, ...)
  \S4method{as.memuse}{object_size}(x, ...)
}
\arguments{
  \item{x}{Numeric or object_size data.}
  \item{...}{Additional arguments; currently ignored.}
}
\details{
  These methods convert numeric or \code{object_size} objects into \code{memuse}
  objects.
}
\value{
  Returns a \code{memuse} object.
}
\seealso{
  \code{\link{Accessors}, \link{memuse-class}}
}
\examples{
as.memuse(10)
}
\keyword{Methods}
