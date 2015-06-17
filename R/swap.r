#' Swaps
#' 
#' Methods for swapping between different memuse formats.
#' 
#' These methods allow simple (coherent) swaps between the different
#' \code{memuse} formats.
#' 
#' \code{swap.unit()} will switch an object to another, supplied unit.  If the
#' unit is from another prefix, then the prefix too will change.  In this case,
#' the size will change appropriately.
#' 
#' \code{swap.prefix()} will change an object from one unit.prefix to the
#' other. In this case, the size will change appropriately.
#' 
#' \code{swap.names} will change from short to long, or long to short printing.
#' The size and prefix of the object are unchanged.
#' 
#' @param x 
#' memuse object
#' @param unit 
#' new unit for the \code{memuse} object after the swap occurs
#' @param precedence
#' Currently does nothing.
#' 
#' @return 
#' Returns a \code{memuse} class object.
#' 
#' @examples
#' \dontrun{
#' x <- mu(1e6)
#' 
#' x
#' swap.prefix(x)
#' swap.names(x)
#' swap.unit(x, "bytes")
#' }
#' 
#' @seealso \code{ \link{Constructor} \link{memuse-class} }
#' @keywords Methods
#' @name Swaps
#' @rdname swaps
NULL



#' @rdname swaps
#' @export
setGeneric(name="swap.prefix", 
  function(x) 
    standardGeneric("swap.prefix"),
  package="memuse"
)

#' @rdname swaps
#' @export
setMethod("swap.prefix", signature(x="memuse"),
  function(x)
  {
    if (x@unit.prefix == "IEC")
      new.prefix <- "SI"
    else if (x@unit.prefix == "SI")
      new.prefix <- "IEC"
    else
      mu_error()
    
    power <- get_power(x)
    
    if (new.prefix == "IEC")
      x@size <- x@size * (1e3/1024)^power
    else
      x@size <- x@size * (1024/1e3)^power
    
    x@unit.prefix <- new.prefix
    
    x <- check.unit(x)
    
    return( x )
  }
)



#' @rdname swaps
#' @export
setGeneric(name="swap.names", 
  function(x)
    standardGeneric("swap.names"), 
  package="memuse"
)

#' @rdname swaps
#' @export
setMethod("swap.names", signature(x="memuse"),
  function(x)
  {
    if (x@unit.names == "short")
      new.names <- "long"
    else if (x@unit.names == "long")
      new.names <- "short"
    else
      mu_error()
    
    new.unit <- which(.units[[x@unit.names]][[x@unit.prefix]][["print"]] == x@unit)
    
    x@unit <- .units[[new.names]][[x@unit.prefix]][["print"]][new.unit]
    
    x@unit.names <- new.names
    
    return( x )
  }
)



#' @rdname swaps
#' @export
setGeneric(name="swap.unit", 
  function(x, unit, precedence=.PRECEDENCE)
    standardGeneric("swap.unit"), 
  package="memuse"
)

#' @rdname swaps
#' @export
setMethod("swap.unit", signature(x="memuse"),
  function(x, unit)#, precedence=.PRECEDENCE)
  {
    unit <- tolower(unit)
    
    if (unit==x@unit)
      return(x)
    
    if (unit == "best")
      x <- best.unit(x)
    else if (unit == tolower(x@unit))
      return( check.mu(x) )
    else {
      flag <- FALSE
      
      for (names in c("short", "long")){
        for (prefix in c("IEC", "SI")){
          if ( unit %in% .units[[names]][[prefix]][["check"]] ){
            flag <- TRUE
            unit.names <- names
            unit.prefix <- prefix
            break
          }
          if (flag)
            break
        }
      }
      
      if (flag){
        x <- convert_to_bytes(x)
        
        x@unit.names <- unit.names
        x@unit.prefix <- unit.prefix
        
        if (unit.prefix == "IEC")
          f <- 1024
        else
          f <- 1e3
        
        units <- .units[[x@unit.names]][[x@unit.prefix]][["check"]]
        i <- which(units == unit)
        
        x@size <- x@size/(f^(i-1))
        
        new.unit <- .units[[unit.names]][[unit.prefix]][["print"]][i]
        
        x@unit <- new.unit
      }
      else
        stop("invalid argument 'unit'.  See help('memuse')")
    }
    
    return( x )
  }
)

