\name{Reductions}
\alias{Reductions}
\docType{methods}

\alias{sum-method}
\alias{sum,memuse-method}
\alias{sum}

\title{ memuse Arithmetic }
\description{
  Binary arithmetic operations for \code{memuse} objects.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "memuse")}}{}
}
}
\usage{
\S4method{sum}{memuse}(x, ..., na.rm=FALSE)
}
\arguments{
  \item{x}{A \code{memuse} object.}
  \item{...}{Additional arguments}
  \item{na.rm}{Whether \code{NA}'s should be ignored.}
}
\details{
  Simple arithmetic reductions.
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
\keyword{Methods}
