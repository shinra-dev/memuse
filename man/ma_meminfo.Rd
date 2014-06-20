\name{meminfo}
\alias{meminfo}

\alias{Sys.meminfo}
\alias{Sys.swapinfo}
\alias{Sys.pageinfo}

\title{meminfo}
\description{
  Platform memory information.
}
\usage{
Sys.meminfo(compact.free=TRUE)

Sys.swapinfo()

Sys.pageinfo()
}
\arguments{
  \item{compact.free}{logical; determines whether various free memory
  values should be combined into a single value. See details section
  for more information.}
}
\details{
  \code{Sys.meminfo()} returns some basic memory values, such as total ram, 
  free ram, and ram used for buffers/cache (when applicable).
  
  \code{Sys.swapinfo()} returns basic swap/page (virtual memory) information.
  \code{Sys.pageinfo()} is identical to \code{swapinfo()} in every way but
  name (provided for Windows users who may be more comfortable/familiar
  with the 'pagefile' naming convention).
  
  All of the C-level source code for these methods (in src/meminfo of
  the root directory of the memuse source tree) is licensed under the
  permissive 2-Clause BSD license.
}
\value{
  Returns a list, whose values are platform dependent in addition to being
  modified by input arguments.
}
\seealso{
  \code{\link{procmem}}
}
\examples{
\dontrun{
library(memuse)

Sys.meminfo()

Sys.procmem()
}
}
\keyword{Methods}
