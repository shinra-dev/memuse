\name{meminfo}

\alias{meminfo}

\title{ meminfo }
\description{
  Platform memory information.
}
\usage{
  meminfo(compact.free=TRUE, show.virtual=FALSE)
}
\arguments{
  \item{compact.free}{logical; determines whether various free memory
  values should be combined into a single value. See details section
  for more information.}
  \item{show.virtual}{logical; determines if virtual memory/swap/pagefile
  values should be shown. See details section for more information.}
}
\details{
  x
}
\value{
  Returns a list, whose values are platform dependent in addition to being
  modified by input arguments.
}
\seealso{
  \code{\link{howmany}}
}
\examples{
meminfo()
}
\keyword{Methods}
