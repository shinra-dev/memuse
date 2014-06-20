\name{Control Variables}

\alias{Control}
\alias{.UNIT}
\alias{.PREFIX}
\alias{.NAMES}
\alias{.PRECEDENCE}


\docType{data}
\title{Control Variables for the memuse Package.}
\description{
  A set of controls which provides (changeable) default values for many 
  functions in this package.
}
\details{
  Currently, there are 4 control data objects:
  \itemize{
  \item  \code{.UNIT} defaults to "best".  The default choice will scale \code{size}
  values to the nearest (by scaling factor --- 1024 or 1000 depending on
  unit prefix).  Other acceptable choices are, for example, "kb" or "kib".
  If the user requests the wrong unit by prefix (e.g., "kb" instead of
  "kib" when the unit prefix is IEC), then the correct one will be 
  chosen for the user.
  
  \item \code{.PREFIX} defaults to "IEC".  Acceptable values are "IEC" and "SI".
  
  \item \code{.NAMES} defaults to "short".  Acceptable values are "short" and
  "long".
  
  \item \code{.PRECEDENCE} defaults to "prefix".  Acceptable values are "unit"
  and "prefix".

  }

  All values are case insensitive, in that the correct case will be determined
  for the user if the incorrect case is supplied.  For example, if the user
  sets \code{.PREFIX <- "si"}, then the correct case ("SI") will be determined
  as needed.
  
  For a "human readable" explanation of what these values do, see the package 
  vignette.
}
\seealso{
  \code{
    \link{memuse-class}
    \link{Constructor}
  }
}
\keyword{Data}
