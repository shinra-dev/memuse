\name{howmany}

\alias{howmany-method}
\alias{howmany,memuse-method}
\alias{howmany}

\alias{howmany.par-method}
\alias{howmany.par,memuse-method}
\alias{howmany.par}

\title{ howmany }
\description{
  How many rows/columns of a matrix can be stored for a given memory size.
}
\section{Methods}{
\describe{
\item{\code{signature(x = "memuse")}}{}
}
}
\usage{
\S4method{howmany}{memuse}(x, nrow, ncol, out.type="full", 
            representation="dense", ..., sparsity=0.05, type="double", 
            intsize=4, unit.names="short")
\S4method{howmany.par}{memuse}(x, nrow, ncol, out.type="full", cores=1, 
            par="row", ..., type="double", intsize=4, ICTXT=0, bldim=c(4, 4))
}
\arguments{
  \item{x}{The size of a matrix stored as a \code{memuse} class object.}
  \item{nrow, ncol}{Number of (global) rows/columns of the matrix.}
  \item{out.type}{If the full dimensions or a reduced representation
  should be returned (see Details section below). Options are "full"
  and "approximate" (with partial matching).}
  \item{representation}{The kind of storage the object would be in, 
  i.e. "dense" or "sparse".}
  \item{cores}{The number of cores/processors}
  \item{par}{Type of data distribution. Choices are "row", "column", and 
  "dmat".  The first is for row-contiguous (distribyted by row) distributions,
  such as the "GBD" format (see the pbdDEMO package vignette).  Next, "column"
  is for the transpose, column-contiguous distributions.  Finally, "dmat"
  is for \pkg{pbdDMAT} objects.}
  \item{unit.names}{string; control for whether the unit names should 
  be printed out or their abbreviation should be used.  Options are 
  "long" and "short", respectively.  Case is ignored.}
  \item{...}{Additional arguments.}
  \item{sparsity}{The proportion of sparsity of the matrix if
  \code{representation="sparse"}}
  \item{type}{"double" or "int"; the storage type of the data matrix.
  If you don't know the type, it is probably stored as a double, so 
  the default value will suffice.}
  \item{intsize}{The size (in bytes) of an integer.  Default is 4, but
  this is platform dependent.}
  \item{ICTXT}{BLACS context number; only used with \code{howbig.par()}
   with \code{par="dmat"}.}
  \item{bldim}{Blocking factor for block-cyclically decomposed (dmat) data.}

}
\details{
  This function provides the maximum dimension of an unallocated, dense, 
  in-core, numeric matrix of known byte size. For example, it will show
  the largest possible square matrix which is 16 GiB (46340x46340).
  
  If the both \code{nrow} and \code{ncol} are missing (blank inputs), then
  the largest square matrix will be returned.  If one of \code{nrow} or 
  \code{ncol} is supplied and the other is missing, then the non-supplied
  argument (\code{nrow} or \code{ncol}) will be determined according to the
  supplied one.  If both arguments are supplied, an error is produced ---
  you probably meant to use \code{howmany()}.

  If \code{out.type="approximate"}, then a reduced representation of the
  dimensions will be returned.  For example, the reduced representation of
  the number 1234567890 would be "1.2b", since this number is basically 
  1.2 billion.  Not super useful, but kind of cute, and it arguably 
  enhances readability when fishing for a ballpark figure.
}
\value{
  \code{howmany()} returns a numeric pair, the dimensions of a matrix.

  \code{howmany.par()} returns a list (the global and local dimensions),
  each of which is a numeric pair.
}
\seealso{
  \code{\link{howbig}}
}
\examples{
\dontrun{
x <- mu(1, "gib")

# largest square matrix that's 1 GiB
howmany(x)
# same, but ballpark figure
howmany(mu(1, "gib"), out.type="approx")
}
}
\keyword{Methods}
