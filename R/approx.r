digits2zero <- function(str)
{
  split <- simplify2array(strsplit(x=str, split=""))
  
  if (length(split) <= 15)
    return( str )
  
  n <- length(split) - 15L
  ret <- paste(paste(split[1L:15L], collapse=""), paste(rep(0, n), collapse=""), collapse="", sep="")
  
  return( ret )
}

#digits2zero("1234567891")
#digits2zero("12345678912345678")



approx.size <- function(x, unit.names="long", ..., digits=1)
{
  #unit <- match.arg(tolower(unit), c("best"))
  unit <- "best" ### FIXME
  unit.names <- match.arg(tolower(unit.names), c("long", "short", "comma"))
  
  if (length(x) > 1)
  {
    ret <- sapply(x, approx.size)
    class(ret) <- "approx"
    
    return( ret )
  }
  
  ordmag <- log10(x)
  
  if (ordmag < 3)
  {
    size <- x
    printsize <- as.character(x)
    sepchar <- " "
    unit <- ""
  }
  else if (unit.names != "comma")
  {
    index <- max(1, min(which(.numbers$exponent > ordmag)) - 1)
    
    if (unit.names == "long")
    {
      sepchar <- " "
      unit <- .numbers$name[index]
    }
    else if (unit.names == "short")
    {
      sepchar <- ""
      unit <- .numbers$shorthand[index]
    }
    
    printsize <- as.character( round(x/(10^.numbers$exponent[index]), digits=digits) )
  }
  else if (unit == "best")
  {
    y <- digits2zero(format(x, scientific=FALSE))
    
    numbers <- unlist(strsplit(as.character(y), split="[.]"))
    if (length(numbers) == 2)
    {
      y <- numbers[1L]
      dec <- numbers[2L]
      sepchar <- "."
    }
    else
    {
      dec <- ""
      sepchar <- ""
    }
    
    # dat regex
    printsize <- gsub("(?<=\\d)(?=(\\d{3})+(?!\\d))", ",", x=y, perl=TRUE)
    printsize <- paste(printsize, dec, sep=sepchar)
    unit <- ""
  }
  
#  ret <- new("approx", size=x, printsize=printsize, unit=unit, unit.names=unit.names)
  
  ret <- paste(printsize, unit, sep=sepchar)
  
  class(ret) <- "approx"
  
  return( ret )
}


