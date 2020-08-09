setClass("humanreadable", representation="VIRTUAL")


hr_make_humanreadable = function(printsize, unit, sepchar)
{
  ret = paste(printsize, unit, sep=sepchar)
  ret = gsub(ret, pattern=" $", replacement="", perl=TRUE)
  class(ret) = "humanreadable"
  ret
}



hr_trivial = function(x, digits)
{
  printsize = as.character(round(x, digits=digits))
  sepchar = " "
  unit = ""
  
  hr_make_humanreadable(printsize, unit, sepchar)
}



hr_names = function(x, digits, ordmag, names)
{
  index = max(1, min(which(.numbers$exponent >= ordmag)) - 1)
  
  if (names == "long")
  {
    sepchar = " "
    unit = .numbers$name[index]
  }
  else if (names == "short")
  {
    sepchar = ""
    unit = .numbers$shorthand[index]
  }
  
  printsize = round(round(x, 0)/(10^.numbers$exponent[index]), digits=digits)
  
  hr_make_humanreadable(printsize, unit, sepchar)
}



hr_comma = function(x, digits)
{
  sgn = sign(x)
  dec = round(abs(x) - floor(abs(x)), digits) * 10^digits
  x = floor(abs(x))
  
  y = digits2zero(format(x, scientific=FALSE))
  
  if (dec > 0)
    sepchar = "."
  else
  {
    dec = ""
    sepchar = ""
  }
  
  if (sgn < 0)
    sgnchar = "-"
  else
    sgnchar = ""
  
  # dat regex
  printsize = gsub("(?<=\\d)(?=(\\d{3})+(?!\\d))", ",", x=y, perl=TRUE)
  printsize = paste0(paste0(sgnchar, printsize), sepchar, dec)
  unit = ""
  
  hr_make_humanreadable(printsize, unit, "")
}



#' hr
#' 
#' Approximate size of an integer.  Very useful when dealing with potentially
#' large values, such as those from \code{howmany()}.
#' 
#' @description
#' A rich man's exponential notation.
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
hr = function(x, names="comma", digits=2)
{
  names = match.arg(tolower(names), c("long", "short", "comma"))
  
  if (length(x) > 1)
  {
    ret = sapply(x, hr)
    class(ret) = "approx"
    
    return(ret)
  }
  
  ordmag = floor(log10(x)) + 1
  
  if (ordmag < 4)
    hr_trivial(x, digits)
  else if (names != "comma")
    hr_names(x, digits, ordmag, names)
  else
    hr_comma(x, digits)
}



#' @title Print \code{humanreadable} objects
#' @description Printing for \code{hr()} 
#' @param x \code{humanreadable} object
#' @param ... unused
#' @name print-hr
#' @rdname print-hr
#' @method print humanreadable
#' @export
print.humanreadable = function(x, ...)
{
  cat(paste(paste(x, collapse=" "), "\n"))
}
