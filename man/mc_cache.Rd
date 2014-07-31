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
  TODO
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
