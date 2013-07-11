mu_error <- function() stop("Badly formed 'memuse' object", call.=FALSE)



get.units <- function(x)
{
  return( .units[[x@unit.names]][[x@unit.prefix]][["print"]] )
}



get.power <- function(x)
{
  units <- get.units(x)
  
  power <- which(units == x@unit)
  
  if (length(power) > 0)
    return( power - 1L )
  else
    mu_error()
}



convert.to.bytes <- function(x)
{
  size <- x@size
  
  n <- which(x@unit == .units[[x@unit.names]][[x@unit.prefix]][["print"]]) - 1
  
  if (x@unit.prefix == "IEC")
    f <- 1024
  else if (x@unit.prefix == "SI")
    f <- 1e3
  else 
    mu_error()
  
#  size <- size * f^n
  size <- abc(size, f, n)
  
  x@size <- size
  x@unit <- .units[[x@unit.names]][[x@unit.prefix]][["print"]][1L]
  
  return( x )
}



best.unit <- function(x)
{
  if (x@unit.prefix == "IEC"){
    f <- 1024
    fun <- function(x) log2(abs(x))
    dgts <- 10
  } else if (x@unit.prefix == "SI"){
    f <- 1e3
    fun <- function(x) log10(abs(x))
    dgts <- 3
  } else {
    mu_error()
  }
  
  size <- convert.to.bytes(x)@size
  
  if (size == 0){
    x@unit.names <- .units[[x@unit.names]][[x@unit.prefix]][["print"]][1L]
    return( x )
  }
  
  
  num.digits <-fun(size)
    
  for (i in seq.int(9)){
    if (num.digits < dgts*i){
      unit <- .units[i]
      break
    }
  }
  
  size <- size/(f^(i-1))
  
  x@size <- size
  x@unit <- .units[[x@unit.names]][[x@unit.prefix]][["print"]][i]
  
  return( x )
}



ct.unit <- function(x)
{
  .UNIT <- tolower(.UNIT)
  
  if (.UNIT == "best")
    x <- best.unit(x)
  else {
    x <- check.mu(x)
    
    if (tolower(x@unit) != .UNIT)
      x <- swap.unit(x, .UNIT)
  }
  
  return( x )
}


# stable a*b^c with c an integer
abc <- function(a, b, c)
{
  if (c==0)
    return(a)
  p <- a
  for (i in seq.int(c)){
    p <- p*b
  }
  
  return( p )
}
