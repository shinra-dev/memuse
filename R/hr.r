setClass("humanreadable", representation="VIRTUAL")



#' hr
#' 
#' Approximate size of an integer.  Very useful when dealing with potentially
#' large values, such as those from \code{howmany()}.
#' 
#' @description
#' A poor man's exponential notation.
#' 
#' @param x 
#' A number.
#' @param names 
#' "long", "short", or "comma"; determines wheter the output
#' reads like "10 million", "10m", or "10,000,000", respectively.
#' @param digits 
#' The number of decimal digits to retain.
#' 
#' @return
#' An object of class \code{humanreadable}.
#' 
#' @examples
#' \dontrun{
#' library(memuse)
#' 
#' hr(12345678)
#' hr(12345678, "long")
#' }
#' 
#' @seealso \code{\link{howmany}}
#' @export
hr <- function(x, names="comma", digits=1)
{
  #unit <- match.arg(tolower(unit), c("best"))
  unit <- "best" ### FIXME
  names <- match.arg(tolower(names), c("long", "short", "comma"))
  
  if (length(x) > 1)
  {
    ret <- sapply(x, hr)
    class(ret) <- "approx"
    
    return( ret )
  }
  
  ordmag <- log10(x)
  
  if (ordmag < 3)
  {
    printsize <- as.character(x)
    sepchar <- " "
    unit <- ""
  }
  else if (names != "comma")
  {
    index <- max(1, min(which(.numbers$exponent > ordmag)) - 1)
    
    if (names == "long")
    {
      sepchar <- " "
      unit <- .numbers$name[index]
    }
    else if (names == "short")
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
  
  ret <- paste(printsize, unit, sep=sepchar)
  ret <- gsub(ret, pattern=" $", replacement="", perl=TRUE)
  class(ret) <- "humanreadable"
  
  return(ret)
}



#' @title Print \code{humanreadable} objects
#' @description Printing for \code{hr()} 
#' @param x \code{humanreadable} object
#' @param ... unused
#' @name print-hr
#' @rdname print-hr
#' @method print humanreadable
#' @export
print.humanreadable <- function(x, ...)
{
  cat(paste(paste(x, collapse=" "), "\n"))
}
