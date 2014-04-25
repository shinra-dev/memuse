convert.time <- function(time, unit.in, unit.out)
{
  ind.in <- which(.time$unit == unit.in)
  ind.out <- which(.time$unit == unit.out)
  
  factor <- .time$factor[ind.in] / .time$factor[ind.out]
  
  return( time*factor )
}



readable.time <- function(time, unit.in="seconds")
{
  unit.in <- match.arg(tolower(unit.in), c("seconds", "minutes"))
  
  if (length(time) > 1L)
    return( sapply(time, readable.time) )
  
  ind <- which(.time$unit == unit.in) + 1L
  
  while (time > .time$factor[ind]  &&  ind <= length(.time$factor))
    ind <- ind + 1L
  
  ind <- ind - 1L
  
  unit.out <- .time$unit[ind]
  
  time <- convert.time(time=time, unit.in=unit.in, unit.out=unit.out)
  
#  printer <- paste(time, unit.out)
  
  class(time) <- "timing"
  attr(time, "unit") <- unit.out
  
  return( time )
}



print.timing <- function(object, digits=3)
{
  time <- round(object, digits=digits)
  unit <- attributes(object)$unit
  
  cat(paste(time, unit, "\n"))
  invisible()
}



wc.time <- function(expr, gcFirst=TRUE)
{
  time <- base::system.time(expr=expr, gcFirst=gcFirst)[3]
  attributes(time) <- NULL
  
  return( readable.time(time, unit="seconds") )
}

