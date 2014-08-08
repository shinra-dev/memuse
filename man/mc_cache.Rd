\name{cache}
\alias{cache}

\alias{Sys.cachesize}
\alias{Sys.cachelinesize}

\title{Cache Sizes and Linesize}
\description{
  Shows the amount of cache available as well as the linesize.
}
\usage{
Sys.cachesize()
Sys.cachelinesize()
}
\details{
  \code{Sys.cachesize()} will check the various levels of cache and
  return all available cache information in a list.  If you don't have
  some kind of level-1 cache, then it will return an error.  If you
  have some kind of future space computer with more than 3 levels of
  cache, levels higher than 3 will not be displayed.
  
  \code{Sys.cachelinesize()} will return the cache linesize.  It's
  almostly certainly 32 or 64 bytes.
}
\value{
  Returns a list, whose values are platform dependent.
}
\seealso{
  \code{\link{meminfo}}
}
\examples{
\dontrun{
library(memuse)

Sys.cachesize()
Sys.cachelinesize()
}
}
\keyword{Methods}
