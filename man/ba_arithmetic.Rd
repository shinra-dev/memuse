\name{Arithmetic}
\alias{Arithmetic}
\docType{methods}

\alias{+-method}
\alias{+,memuse,memuse-method}
\alias{+}

\alias{*-method}
\alias{*,memuse,memuse-method}
\alias{*,memuse,numeric-method}
\alias{*,numeric,memuse-method}
\alias{*}

\alias{^-method}
\alias{^,memuse,memuse-method}
\alias{^,memuse,numeric-method}
\alias{^}


\title{ MemUse Arithmetic }
\description{
  Binary arithmetic operations for \code{memuse} objects.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "memuse", y = "memuse")}}{}
\item{\code{signature(x = "numeric", y = "memuse")}}{}
\item{\code{signature(x = "memuse", y = "numeric")}}{}
}
}
\usage{
  x + y
  x * y
  x ^ y
}
\arguments{
  \item{x, y}{\code{memuse} class objects}
}
\details{
  deets
}
\value{
  Returns a \code{memuse} class object.
}
\seealso{
  \code{\link{Constructor}, \link{memuse-class}}
}
\examples{
x <- mu(100)
y <- mu(200)

x+y
x*y
x^2
}
\keyword{Methods}
