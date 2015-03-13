# class detection
is.memuse <- function(x) class(x)=="memuse"



### sanity checks
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
    stop("cannot construct 'memuse' object; bad 'unit.names'", call.=F)
  
  x <- check.prefix(x)
  if (is.logical(x))
    stop("cannot construct 'memuse' object; bad 'unit.prefix'", call.=F)
  
  x <- check.unit(x)
  if (is.logical(x))
    stop("cannot construct 'memuse' object; bad 'unit'", call.=F)
  
  return( x )
}



mu.nonneg <- function(x)
{
  if (x@size < 0)
    warning("memuse object contsructed with negative value")
  
  invisible()
}



### constructor
internal.memuse <- function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)#, precedence=.PRECEDENCE)
{
  if (unit == "best")
    u <- "B"
  else
    u <- unit
  
  
  # construct
  x <- new("memuse", size=size, unit=u, unit.prefix=unit.prefix, unit.names=unit.names)
  
  # sanity check
  x <- check.mu(x)
  
  mu.nonneg(x)
  
#  # convert to the correct unit
#  precedence <- match.arg(tolower(precedence), c("unit", "prefix"))
  
#  if (precedence == "unit")
  x <- swap.unit(x=x, unit="best")#, precedence=precedence)
  
  return( x )
}

internal.mu <- internal.memuse

