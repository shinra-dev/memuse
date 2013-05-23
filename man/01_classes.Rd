\name{ddmatrix-class}
\docType{class}

\alias{fs}
\alias{fs-class}

\title{Class fs}
\description{ Distributed matrix class. }

\section{Creating Objects}{
  \code{ new('ddmatrix', Data = ..., dim = ..., ldim = ...,
  bldim = ..., ICTXT = ...)}
}

\section{Slots}{
\describe{
\item{\code{Data}:}{LOCAL: Object of class \code{matrix}}
\item{\code{dim}:}{GLOBAL: Object of class \code{numeric}}
\item{\code{ldim}:}{LOCAL: Object of class \code{numeric}}
\item{\code{bldim}:}{GLOBAL: Object of class \code{numeric}}
\item{\code{ICTXT}:}{GLOBAL: Object of class \code{numeric}}
}
}
\section{Prototype}{
\describe{
\item{matrix Data}{matrix(0.0)}
\item{numeric dim}{c(1,1)}
\item{numeric ldim}{c(1,1)}
\item{numeric bldim}{c(1,1)}
\item{numeric ICTXT}{0}
}
}
\section{Details}{
  \code{ddmatrix} is the container for ScaLAPACK-friendly parallel
  block-cyclically distributed matrices. The class object is
  instantiated in SPMD fashion, whereby each process owns a piece
  of the "whole" matrix (which no single R process need ever own in
  its entirety), and each process stores its piece of the whole into a
  container with a name common to all processes.
}
\seealso{
  \code{\link{InitGrid}, \link{SlotAccessors}}
}
\keyword{Classes}
