\name{Swaps}
\alias{Swaps}
\docType{methods}

\alias{swap.unit-method}
\alias{swap.unit,memuse-method}
\alias{swap.unit}

\alias{swap.prefix-method}
\alias{swap.prefix,memuse-method}
\alias{swap.prefix}

\alias{swap.names-method}
\alias{swap.names,memuse-method}
\alias{swap.names}


\title{ Swaps }
\description{
  Methods for swapping between different memuse formats.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "memuse")}}{}
}
}
\usage{
\S4method{swap.unit}{memuse}(x, unit)
\S4method{swap.prefix}{memuse}(x)
\S4method{swap.names}{memuse}(x)
}
\arguments{
  \item{x}{memuse object}
  \item{unit}{new unit for the \code{memuse} object after the swap occurs}
}
\details{
  These methods allow simple (coherent) swaps between the different 
  \code{memuse} formats. 
  
  \code{swap.unit()} will switch an object to another, supplied unit.  If
  the unit is from another prefix, then the prefix too will change.  In this
  case, the size will change appropriately.

  \code{swap.prefix()} will change an object from one unit.prefix to the
  other. In this case, the size will change appropriately.

  \code{swap.names} will change from short to long, or long to short printing.
  The size and prefix of the object are unchanged.
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
x <- mu(1e6)

x
swap.prefix(x)
swap.names(x)
swap.unit(x, "bytes")
}
\keyword{Methods}
