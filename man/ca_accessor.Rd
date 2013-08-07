\name{Accessors}
\alias{Accessors}
\docType{methods}

\alias{size-method}
\alias{size,memuse-method}
\alias{size}

\alias{as.numeric-method}
\alias{as.numeric,memuse-method}
\alias{as.numeric}

\alias{unit-method}
\alias{unit,memuse-method}
\alias{unit}

\alias{unit.prefix-method}
\alias{unit.prefix,memuse-method}
\alias{unit.prefix}

\alias{unit.names-method}
\alias{unit.names,memuse-method}
\alias{unit.names}

\title{ Accessors }
\description{
  Accessor methods for slots of objects of class \code{memuse}.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "memuse")}}{}
}
}
\usage{
\S4method{size}{memuse}(x, as.is=TRUE)
\S4method{as.numeric}{memuse}(x, ...)
\S4method{unit}{memuse}(x)
\S4method{unit.prefix}{memuse}(x)
\S4method{unit.names}{memuse}(x)
}
\arguments{
  \item{x}{memuse object}
  \item{as.is}{logical; should the size be "as-is", or converted to bytes
  first.}
  \item{...}{Additional arguments; in this case, they are ignored.}
}
\details{
  These methods are mostly just syntactic sugar for ordinary S4 slot accessing.
  So for example, \code{size(x)} is no different semantically from calling
  \code{x@size}.
  
  There are two differences, however.  The \code{size()} method has a
  parameter \code{as.is} which controls whether the return should be 
  the raw value or the raw value converted to bytes first.  For the latter,
  you should really use \code{as.numeric} instead, which is equivalent to
  calling \code{size(x, as.is=FALSE)}.
}
\value{
  Returns a numeric value in the case of \code{size()}, and \code{as.numeric()},
  otherwise a string is returned.
}
\seealso{
  \code{
    \link{memuse-class}
    \link{Replacers}
  }
}
\examples{
x <- mu(1e6)

size(x)
as.numeric(x)
unit(x)
unit.prefix(x)
unit.names(x)
}
\keyword{Methods}
