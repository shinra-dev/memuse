\name{meminfo}

\alias{meminfo}
\alias{swapinfo}
\alias{pageinfo}

\title{ meminfo }
\description{
  Platform memory information.
}
\usage{
  meminfo(compact.free=TRUE)
  swapinfo()
  pageinfo()
}
\arguments{
  \item{compact.free}{logical; determines whether various free memory
  values should be combined into a single value. See details section
  for more information.}
}
\details{
  \code{meminfo()} returns some basic memory values, such as total ram, 
  free ram, and ram used for buffers/cache (when applicable).
  
  \code{swapinfo()} returns basic swap/page (virtual memory) information.
  \code{pageinfo()} is identical to \code{swapinfo()} in every way but
  name (provided for Windows users who may be more comfortable/familiar
  with the 'pagefile' naming convention).
}
\value{
  Returns a list, whose values are platform dependent in addition to being
  modified by input arguments.
}
\seealso{
  \code{\link{howmany}}
}
\examples{
\dontrun{
library(memuse)

meminfo()
}
}
\keyword{Methods}
