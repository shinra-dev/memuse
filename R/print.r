#' Printing
#' 
#' Print and show methods for \code{memuse} class objects.
#' 
#' @param x,object 
#' \code{memuse} class object
#' @param ... extra arguments
#' @param unit 
#' the unit to be used in printing; defaults to \code{x}'s unit
#' @param unit.prefix 
#' the unit prefix to be used in printing; defaults to
#' \code{x}'s unit.prefix
#' @param unit.names 
#' the unit names (short or long) to be used in printing;
#' defaults to \code{x}'s unit.names
#' @param digits 
#' the number of decimal digits to print; default is 3
#' 
#' @return 
#' Returns a string.
#' 
#' @examples
#' \dontrun{
#' x <- mu(1e6)
#' 
#' print(x)
#' x # same as show(x)
#' }
#' 
#' @seealso \code{\ link{Constructor} \link{memuse-class} }
#' @keywords Methods
#' @name Print
#' @rdname print
NULL

#' @rdname print
#' @export
setMethod("print", signature(x="memuse"),
  function(x, ..., unit=x@unit, unit.prefix=x@unit.prefix, unit.names=x@unit.names, digits=3)
  {
    if (unit.names != x@unit.names)
      x <- swap.names(x=x)
    if (unit.prefix != x@unit.prefix)
      x <- swap.prefix(x=x)
    if (unit != x@unit)
      x <- swap.unit(x=x, unit=unit, )
    
    unit <- tolower(x@unit)
    if (unit == "b" || unit == "bytes")
      digits <- 0
    
    if (x@size > 1e22)
      format <- "e"
    else
      format <- "f"
    
    cat(sprintf(paste("%.", digits, format, " ", x@unit, "\n", sep=""), x@size))
  }
)

#' @rdname print
#' @export
setMethod("show", signature(object="memuse"),
  function(object) 
    print(object, unit=object@unit, unit.prefix=object@unit.prefix, unit.names=object@unit.names, digits=3)
)

