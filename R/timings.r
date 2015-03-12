convert.time <- function(time, unit.in, unit.out)
{
  ind.in <- which(.time$unit == unit.in)
  ind.out <- which(.time$unit == unit.out)
  
  factor <- .time$factor[ind.in] / .time$factor[ind.out]
  
  return( time*factor )
}



#' Print times in a readable way.
#' 
#' @param time
#' A time count.
#' @param unit
#' The unit of time (e.g. "seconds").
#' 
#' @examples
#' \dontrun{
#' library(memuse)
#' 
#' readable.time(10000, unit="seconds")
#' readable.time(10000, unit="minutes")
#' }
#' 
#' @export
readable.time <- function(time, unit="seconds")
{
  unit <- match.arg(tolower(unit), c("seconds", "minutes"))
  
  if (length(time) > 1L)
    return( sapply(time, readable.time) )
  
  ind <- which(.time$unit == unit) + 1L
  
  while (time > .time$factor[ind]  &&  ind <= length(.time$factor))
    ind <- ind + 1L
  
  ind <- ind - 1L
  
  unit.out <- .time$unit[ind]
  
  time <- convert.time(time=time, unit.in=unit, unit.out=unit.out)
  
#  printer <- paste(time, unit.out)
  
  class(time) <- "readabletime"
  attr(time, "unit") <- unit.out
  
  return( time )
}



#' @title Print readabletime objects.
#' 
#' @param x 
#' An readabletime object.
#' @param ... 
#' Additional arguments (ignored).
#' @param digits
#' The (max) number of digits to display.
#' 
#' @name print-readabletime
#' @rdname print-readabletime
#' @method print readabletime
#' @export
print.readabletime <- function(x, ..., digits=3)
{
  time <- round(x, digits=digits)
  unit <- attributes(x)$unit
  
  cat(paste(time, unit, "\n"))
  invisible()
}



#' Readable Timings
#' 
#' Printing timings in their "native" unit.  For example, "10000" seconds
#' becomes "2.778 hours".
#' 
#' The wall-clock timer, \code{wc.time()}, is a simple wrapper around R's
#' \code{system.time()} using these readable units.
#' 
#' This uses S3 methods for simplicity, though this makes some higher
#' abstractions impossible.  Future versions will likely use S4.
#' 
#' @param expr 
#' A valid R expression to be timed.
#' @param gcFirst 
#' logical; determines if garbage collection should be called
#' before getting process memory usage.
#' 
#' @return
#' Returns a \code{timing} object, which dispalys readable times.
#' 
#' @keywords Methods
#' 
#' @examples
#' \dontrun{
#' library(memuse)
#' 
#' wc.time(rnorm(1e6))
#' }
#' 
#' @export
wc.time <- function(expr, gcFirst=TRUE)
{
  time <- base::system.time(expr=expr, gcFirst=gcFirst)[3]
  attributes(time) <- NULL
  
  return( readable.time(time, unit="seconds") )
}

