\name{Print}
\docType{methods}

\alias{print-method}
\alias{print,memuse-method}
\alias{print}

\alias{show-method}
\alias{show,memuse-method}
\alias{show}

\title{ Printing }
\description{
  Print and show methods for \code{memuse} class objects.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "memuse")}}{}
}
}
\usage{
  \S4method{print}{memuse}(x, ..., unit=x@unit, unit.prefix=x@unit.prefix, unit.names=x@unit.names, digits=3)
  \S4method{show}{memuse}(object)
}
\arguments{
  \item{x, object}{\code{memuse} class object}
  \item{...}{extra arguments}
  \item{unit}{the unit to be used in printing; defaults to \code{x}'s unit}
  \item{unit.prefix}{the unit prefix to be used in printing; defaults to \code{x}'s 
  unit.prefix}
  \item{unit.names}{the unit names (short or long) to be used in printing; defaults
  to \code{x}'s unit.names}
  \item{digits}{the number of decimal digits to print; default is 3}
}
\value{
  Returns a string.
}
\seealso{
  \code{\link{Constructor}, \link{memuse-class}}
}
\examples{
x <- mu(1e6)

print(x)
x # same as show(x)
}
\keyword{Methods}
