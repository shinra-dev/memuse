\name{memuse-class}
\docType{class}

\alias{memuse-class}

\title{Class memuse}
\description{ Memory usage class object. }

\section{Creating Objects}{
  \code{new('memuse', size = ..., unit = ..., unit.prefix = ..., unit.names = ...)}
  
  \code{memuse(size = ..., unit = ..., unit.prefix = ..., unit.names = ...)}

  \code{mu(size = ..., unit = ..., unit.prefix = ..., unit.names = ...)}
}

\section{Slots}{
\describe{
\item{\code{size}:}{Object of class \code{numeric}}
\item{\code{unit}:}{Object of class \code{character}}
\item{\code{unit.prefix}:}{Object of class \code{character}}
\item{\code{unit.names}:}{Object of class \code{character}}
}
}
\section{Prototype}{
\describe{
\item{numeric size}{0}
\item{character unit}{"B"}
\item{character unit.prefix}{"IEC"}
\item{character unit.names}{"short"}
}
}
\section{Details}{
  \code{memuse} is the container for memory usage data for an unallocated,
  dense, in-core R object.  The \code{size} slot contains the memory 
  usage in some unit of bytes.  The \code{unit} slot contains the 
  unit of bytes that \code{size} is stored in (e.g., kb, mb, gb, ...).
  The \code{unit.prefix} slot contains the unit prefix, either IEC or
  SI.  The \code{unit.names} slot contains the unit names, either short
  (e.g., kb) or long (e.g., kilobyte).
  
  There is almost certainly no compelling reason to work with this class
  directly.  Instead, you should use the host of methods for this class.
}
\seealso{
  \code{
    \link{Control}
    \link{Constructor}
  }
}
\keyword{Classes}
