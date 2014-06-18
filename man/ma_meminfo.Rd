\name{meminfo}

\alias{Sys.meminfo}
\alias{Sys.swapinfo}
\alias{Sys.pageinfo}
\alias{Sys.procmem}

\title{ meminfo }
\description{
  Platform memory information.
}
\usage{
  Sys.meminfo(compact.free=TRUE)
  Sys.swapinfo()
  Sys.pageinfo()
  Sys.procmem(gcFirst=TRUE)
}
\arguments{
  \item{compact.free}{logical; determines whether various free memory
  values should be combined into a single value. See details section
  for more information.}
  \item{gcFirst}{logical; determines if garbage collection should be
  called before getting process memory usage.}
}
\details{
  \code{Sys.meminfo()} returns some basic memory values, such as total ram, 
  free ram, and ram used for buffers/cache (when applicable).
  
  \code{Sys.swapinfo()} returns basic swap/page (virtual memory) information.
  \code{Sys.pageinfo()} is identical to \code{swapinfo()} in every way but
  name (provided for Windows users who may be more comfortable/familiar
  with the 'pagefile' naming convention).
  
  \code{Sys.procmem()} returns the total memory usage of the current R
  process, and (if supported), the maximum memory usage as well.
  
  All of the C-level source code for these methods (in src/meminfo of
  the root directory of the memuse source tree) is licensed under the
  permissive 2-Clause BSD license.
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

Sys.meminfo()

Sys.procmem()
}
}
\keyword{Methods}
