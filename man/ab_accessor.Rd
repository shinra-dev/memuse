\name{Accessors}
\alias{Accessors}
\docType{methods}

\alias{size-method}
\alias{size,memuse-method}
\alias{size}

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
  \S4method{size}{memuse}(x)
  \S4method{unit}{memuse}(x)
  \S4method{unit.prefix}{memuse}(x)
  \S4method{unit.names}{memuse}(x)
}
\arguments{
  \item{x}{memuse object}
}
\details{
  These methods are just syntactic sugar for ordinary S4 slot accessing.
  So for example, \code{size(x)} is no different semantically from calling
  \code{x@size}.
}
\value{
  Returns a numeric element in the case of \code{size()}, otherwise a
  string is returned.
}
\seealso{
  \code{\link{Replacers}, \link{memuse-class}}
}
\examples{
x <- mu(1e6)

size(x)
unit(x)
unit.prefix(x)
unit.names(x)
}
\keyword{Methods}
