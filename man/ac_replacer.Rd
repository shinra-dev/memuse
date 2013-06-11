\name{Replacers}
\alias{Replacers}
\docType{methods}

\alias{size<--method}
\alias{size<-,memuse-method}
\alias{size<-}

\alias{unit<--method}
\alias{unit<-,memuse-method}
\alias{unit<-}

\alias{unit.prefix<--method}
\alias{unit.prefix<-,memuse-method}
\alias{unit.prefix<-}

\alias{unit.names<--method}
\alias{unit.names<-,memuse-method}
\alias{unit.names<-}

\title{ Replacers }
\description{
  Replacement methods for slots of objects of class \code{memuse}.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "memuse")}}{}
}
}
\usage{
  size(x) <- value
  unit(x) <- value
  unit.prefix(x) <- value
  unit.names(x) <- value
}
\arguments{
  \item{x}{memuse object}
  \item{value}{replacement value}
}
\details{
  These methods are syntactic sugar for assignment using ordinary S4
  accessors.  So for example, \code{size(x) <- 10} is semantically no 
  different from calling \code{x@size <- 10}
  
  These methods are strict replacement methods; if you need to swap the
  units of a \code{memuse} class object, you should probably be using the
  \code{\link{Swaps}} methods.  See example below for further details.
}
\value{
  Returns a numeric element in the case of \code{size()}, otherwise a
  string is returned.
}
\seealso{
  \code{\link{Accessors}, \link{memuse-class}}
}
\examples{
x <- mu(2000, unit="bytes")
x

size(x) <- 1000
x
}
\keyword{Methods}
