is.memuse <- function(x) class(x)=="memuse"



check.unit <- function(x)
{
  # Essentially correct unit (up to case)
  unit <- tolower(x@unit)
  check <- .units[[x@unit.names]][[x@unit.prefix]][["check"]]
  
  print <- .units[[x@unit.names]][[x@unit.prefix]][["print"]]
  
  if (unit %in% check){
    x@unit <- print[which(check==unit)]
    
    return( x )
  }
  
  # Unit does not match unit.prefix --- assume they meant the given unit.prefix and fix unit
  check <- .units[[x@unit.names]]
  check[[x@unit.prefix]] <- NULL
  
  if (unit %in% check[[1L]][["check"]]){
    x@unit <- print[which(check[[1L]][["check"]] == unit)]
    
    return( x )
  }
  
  # Unit does not match unit.names --- assume they meant the given unit.names and fix unit
  other.names <- if (x@unit.names == "short") "long" else "short"
  
  check <- .units[[other.names]]
#  check[[x@unit.prefix]] <- NULL
  
  if (unit %in% check[[x@unit.prefix]][["check"]]){
    x@unit <- print[which(check[[x@unit.prefix]][["check"]] == unit)]
    
    return( x )
  }
  
  check[[x@unit.prefix]] <- NULL
  
  if (unit %in% check[[1L]][["check"]]){
    x@unit <- print[which(check[[1L]][["check"]] == unit)]
    
    return( x )
  }
  
  # failed
  return( FALSE )
}



check.prefix <- function(x)
{
  prefix <- toupper(x@unit.prefix)
  check <- c("SI", "IEC")
  
  if (prefix %in% check){
    x@unit.prefix <- prefix
    
    return( x )
  }
  else
    FALSE
}



check.names <- function(x)
{
  prefix <- tolower(x@unit.names)
  check <- c("short", "long")
  
  if (prefix %in% check){
    x@unit.names <- tolower(prefix)
    
    return( x )
  }
  else
    FALSE
}



check.mu <- function(x)
{
  x <- check.names(x)
  if (is.logical(x))
    stop("cannot construct 'memuse' object; bad 'unit.names'", call.=FALSE)
  
  x <- check.prefix(x)
  if (is.logical(x))
    stop("cannot construct 'memuse' object; bad 'unit.prefix'", call.=FALSE)
  
  x <- check.unit(x)
  if (is.logical(x))
    stop("cannot construct 'memuse' object; bad 'unit'", call.=FALSE)
  
  return( x )
}



mu.nonneg <- function(x)
{
  if (x@size < 0)
    warning("memuse object contsructed with negative value")
  
  invisible()
}



internal.mu <- function(size=0, unit="best", unit.prefix="IEC", unit.names="short")
{
  if (unit == "best")
    u <- "B"
  else
    u <- unit
  
  
  x <- new("memuse", size=size, unit=u, unit.prefix=unit.prefix, unit.names=unit.names)
  x <- check.mu(x)
  
  mu.nonneg(x)
  
  if (size > 0)
    x <- swap.unit(x=x, unit=unit)
  
  x
}
