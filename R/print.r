#' Printing
#' 
#' Print and show methods for \code{memuse} class objects.
#' 
#' @param x,object 
#' \code{memuse} class object
#' @param ... extra arguments
#' @param unit 
#' the unit to be used in printing; defaults to \code{x}'s unit
#' @param prefix 
#' the unit prefix to be used in printing; defaults to
#' \code{x}'s prefix
#' @param names 
#' the unit names (short or long) to be used in printing;
#' defaults to \code{x}'s names
#' @param digits 
#' the number of decimal digits to print; default is 3
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
#' @name print-memuse
#' @rdname print-memuse
NULL



#' @rdname print-memuse
#' @export
setMethod("print", signature(x="memuse"),
  function(x, ..., unit=mu.unit(x), prefix=mu.prefix(x), names=mu.names(x), digits=3)
  {
    if (names != x@unit.names)
      x <- swap.names(x=x)
    if (prefix != x@unit.prefix)
      x <- swap.prefix(x=x)
    if (unit != x@unit)
      x <- swap.unit(x=x, unit=unit)
    
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



#' @rdname print-memuse
#' @export
setMethod("show", signature(object="memuse"),
  function(object) 
    print(object, unit=mu.unit(object), prefix=mu.prefix(object), names=mu.names(object), digits=3)
)
