\name{Arithmetic}
\alias{Arithmetic}
\docType{methods}

\alias{+-method}
\alias{+,memuse,memuse-method}
\alias{+,memuse,numeric-method}
\alias{+,numeric,memuse-method}
\alias{+,memuse,object_size-method}
\alias{+,object_size,memuse-method}
\alias{+}

\alias{--method}
\alias{-,memuse,memuse-method}
\alias{-,memuse,numeric-method}
\alias{-,numeric,memuse-method}
\alias{-,memuse,missing-method}
\alias{-,memuse,object_size-method}
\alias{-,object_size,memuse-method}
\alias{-}

\alias{*-method}
\alias{*,memuse,memuse-method}
\alias{*,memuse,numeric-method}
\alias{*,numeric,memuse-method}
\alias{*,memuse,object_size-method}
\alias{*,object_size,memuse-method}
\alias{*}

\alias{/-method}
\alias{/,memuse,memuse-method}
\alias{/,memuse,numeric-method}
\alias{/,numeric,memuse-method}
\alias{/,memuse,object_size-method}
\alias{/,object_size,memuse-method}
\alias{/}

\alias{^-method}
\alias{^,memuse,memuse-method}
\alias{^,memuse,numeric-method}
\alias{^}


\title{ memuse Arithmetic }
\description{
  Binary arithmetic operations for \code{memuse} objects.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "memuse", y = "memuse")}}{}
\item{\code{signature(x = "numeric", y = "memuse")}}{}
\item{\code{signature(x = "memuse", y = "numeric")}}{}
\item{\code{signature(x = "object_size", y = "memuse")}}{}
\item{\code{signature(x = "memuse", y = "object_size")}}{}
}
}
\usage{
  x + y
  x - y
  x * y
  x / y
  x ^ y
}
\arguments{
  \item{x, y}{\code{memuse}, \code{numeric}, or \code{object_size} objects.}
}
\details{
  Simple binary arithmetic for \code{memuse} objects.  Options include
  any combination of \code{memuse}, \code{object_size} (output from the
  \code{object.size()} function), and \code{numeric} objects.
}
\value{
  Returns a \code{memuse} class object.
}
\seealso{
  \code{
    \link{Constructor}
    \link{memuse-class}
  }
}
\examples{
x <- mu(200)
y <- mu(100)

x+y
x-y
x*y
x/y
x^2
}
\keyword{Methods}
