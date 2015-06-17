#' Accessors
#' 
#' Accessor methods for slots of objects of class \code{memuse}.
#' 
#' These methods are mostly just syntactic sugar for ordinary S4 slot
#' accessing.  So for example, \code{size(x)} is no different semantically from
#' calling \code{x@@size}.
#' 
#' There are two differences, however.  The \code{size()} method has a
#' parameter \code{as.is} which controls whether the return should be the raw
#' value or the raw value converted to bytes first.  For the latter, you should
#' really use \code{as.numeric} instead, which is equivalent to calling
#' \code{size(x, as.is=FALSE)}.
#' 
#' 
#' @param x 
#' memuse object
#' @param as.is 
#' logical; should the size be "as-is", or converted to bytes first.
#' @param ... 
#' Additional arguments; in this case, they are ignored.
#' 
#' @return Returns a numeric value in the case of \code{size()}, and
#' \code{as.numeric()}, otherwise a string is returned.
#' 
#' @examples
#' \dontrun{
#' x <- mu(1e6)
#' 
#' size(x)
#' as.numeric(x)
#' unit(x)
#' unit.prefix(x)
#' unit.names(x)
#' }
#' 
#' @seealso \code{ \link{memuse-class} \link{Replacers} }
#' @keywords Methods
#' @name Accessors
#' @rdname accessors
NULL

#' @rdname accessors
#' @export
setGeneric(name="size", 
  function(x, as.is=TRUE)
    standardGeneric("size"), 
  package="memuse"
)

#' @rdname accessors
#' @export
setGeneric(name="unit", 
  function(x)
    standardGeneric("unit"), 
  package="memuse"
)

#' @rdname accessors
#' @export
setGeneric(name="unit.prefix", 
  function(x)
    standardGeneric("unit.prefix"), 
  package="memuse"
)

#' @rdname accessors
#' @export
setGeneric(name="unit.names", 
  function(x)
    standardGeneric("unit.names"), 
  package="memuse"
)



#' @rdname accessors
#' @export
setMethod("size", signature(x="memuse"),
  function(x, as.is=TRUE)
  {
    if (as.is)
      return(x@size)
    else
      return(convert_to_bytes(x)@size)
  }
)

#' @rdname accessors
#' @export
setMethod("unit", signature(x="memuse"),
  function(x)
    return(x@unit)
)

#' @rdname accessors
#' @export
setMethod("unit.prefix", signature(x="memuse"),
  function(x)
    return(x@unit.prefix)
)

#' @rdname accessors
#' @export
setMethod("unit.names", signature(x="memuse"),
  function(x)
    return(x@unit.names)
)



#' Replacers
#' 
#' Replacement methods for slots of objects of class \code{memuse}.
#' 
#' These methods are syntactic sugar for assignment using ordinary S4
#' accessors.  So for example, \code{size(x) <- 10} is semantically no
#' different from calling \code{x@@size <- 10}
#' 
#' These methods are strict replacement methods; if you need to swap the units
#' of a \code{memuse} class object, you should probably be using the
#' \code{\link{Swaps}} methods.  See example below for further details.
#' 
#' @name Replacers
#' 
#' @param x 
#' memuse object
#' @param value 
#' replacement value
#' 
#' @return Returns a numeric element in the case of \code{size()}, otherwise a
#' string is returned.
#' 
#' @examples
#' \dontrun{
#' x <- mu(2000, unit="bytes")
#' x
#' 
#' size(x) <- 1000
#' x
#' }
#' 
#' @seealso \code{ \link{Accessors} \link{memuse-class} }
#' @keywords Methods
#' @rdname replacers
NULL

#' @rdname replacers
#' @export
setGeneric(name="size<-", 
  function(x, value)
    standardGeneric("size<-"), 
  package="memuse"
)

#' @rdname replacers
#' @export
setGeneric(name="unit<-", 
  function(x, value)
    standardGeneric("unit<-"), 
  package="memuse"
)

#' @rdname replacers
#' @export
setGeneric(name="unit.prefix<-", 
  function(x, value)
    standardGeneric("unit.prefix<-"), 
  package="memuse"
)

#' @rdname replacers
#' @export
setGeneric(name="unit.names<-", 
  function(x, value)
    standardGeneric("unit.names<-"), 
  package="memuse"
)



#' @rdname replacers
#' @export
setReplaceMethod("size", signature(x="memuse"),
  function(x, value)
  {
    x@size <- value
    x <- check.mu(x)
    
#    x <- swap.unit(x=x, unit=.UNIT)
    
    return( x )
  }
)

#' @rdname replacers
#' @export
setReplaceMethod("unit", signature(x="memuse"),
  function(x, value)
  {
    x@unit <- value
    x <- check.mu(x)
    
    return( x )
  }
)

#' @rdname replacers
#' @export
setReplaceMethod("unit.prefix", signature(x="memuse"),
  function(x, value)
  {
    x@unit.prefix <- value
    x <- check.mu(x)
    
    return( x )
  }
)

#' @rdname replacers
#' @export
setReplaceMethod("unit.names", signature(x="memuse"),
  function(x, value)
  {
    x@unit.names <- value
    x <- check.mu(x)
    
    return( x )
  }
)
