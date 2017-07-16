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
#' mu.unit(x)
#' mu.prefix(x)
#' mu.names(x)
#' }
#' 
#' @seealso \code{ \link{memuse-class} }
#' @keywords Methods
#' @name Accessors
#' @rdname accessors
NULL

#' @rdname accessors
#' @export
setGeneric(name="mu.size", 
  function(x, as.is=TRUE)
    standardGeneric("mu.size"), 
  package="memuse"
)

#' @rdname accessors
#' @export
setGeneric(name="mu.unit", 
  function(x)
    standardGeneric("mu.unit"), 
  package="memuse"
)

#' @rdname accessors
#' @export
setGeneric(name="mu.prefix", 
  function(x)
    standardGeneric("mu.prefix"), 
  package="memuse"
)

#' @rdname accessors
#' @export
setGeneric(name="mu.names", 
  function(x)
    standardGeneric("mu.names"), 
  package="memuse"
)



#' @rdname accessors
#' @export
setMethod("mu.size", signature(x="memuse"),
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
setMethod("mu.unit", signature(x="memuse"),
  function(x)
    return(x@unit)
)

#' @rdname accessors
#' @export
setMethod("mu.prefix", signature(x="memuse"),
  function(x)
    return(x@unit.prefix)
)

#' @rdname accessors
#' @export
setMethod("mu.names", signature(x="memuse"),
  function(x)
    return(x@unit.names)
)
