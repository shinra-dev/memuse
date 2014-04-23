approx_size <- function(x, unit="best", unit.names="long", ..., digits=1)
{
  unit <- match.arg(tolower(unit), c("best"))
  unit.names <- match.arg(tolower(unit.names), c("long", "short", "comma"))
  
  if (length(x) > 1)
  {
    ret <- sapply(x, approx_size)
    class(ret) <- "approx"
    
    return( ret )
  }
  
  ordmag <- log10(x)
  
  if (ordmag < 3)
  {
    size <- x
    printsize <- as.character(x)
  }
  else if (unit.names != "comma")
  {
    index <- max(1, min(which(.numbers$exponent > ordmag)) - 1)
    
    if (unit.names == "long")
      unit <- .numbers$name[index]
    else if (unit.names == "short")
      unit <- .numbers$shorthand[index]
    
    printsize <- as.character( round(x/(10^.numbers$exponent[index]), digits=digits) )
  }
  else if (unit == "best")
  {
    y <- x
    
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
  
  ret <- paste(printsize, unit, sep=" ")
  
  class(ret) <- "approx"
  
  return( ret )
}


