% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/sysinfo.r
\name{procmem}
\alias{procmem}
\alias{Sys.procmem}
\title{procmem}
\usage{
Sys.procmem(gcFirst = TRUE)
}
\arguments{
\item{gcFirst}{logical; determines if garbage collection should be called
before getting process memory usage.}
}
\value{
Returns a list, whose values are platform dependent in addition to
being modified by input arguments.
}
\description{
Shows the amount of ram used by the current R process.
}
\details{
\code{Sys.procmem()} returns the total memory usage of the current R
process, and (if supported), the maximum memory usage as well.

All of the C-level source code for these methods (in src/meminfo of the root
directory of the memuse source tree) is licensed under the permissive
2-Clause BSD license.
}
\examples{
\dontrun{
library(memuse)

### How much is being used?
Sys.procmem()

### Use more.
x <- rnorm(1e7)
Sys.procmem()

### Use less.
rm(x)
gc(FALSE)
Sys.procmem()
}

}
\seealso{
\code{\link{meminfo}}
}
