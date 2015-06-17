#' Converters
#' 
#' Converter methods.
#' 
#' These methods convert numeric, \code{object_size}, and string (character)
#' objects into \code{memuse} objects.
#' 
#' Strings must be of the same form as the printed output of a a memuse object.
#' For example, "100 KiB" is valid, but "100 (KiB)" is not.  As always, case of
#' the unit is ignored, and so "100 kib" would be valid as well.
#' 
#' @param x 
#' Numeric value, object_size data, or appropriate string (see details
#' section for more information).
#' @param ...
#' Additional arguments.
#' 
#' @return 
#' Returns a \code{memuse} object.
#' 
#' @examples
#' \dontrun{
#' as.memuse(10)
#' }
#' 
#' @seealso \code{ \link{memuse-class} \link{Accessors} }
#' @keywords Methods
#' @name Converters
#' @rdname converters
NULL

#' @rdname converters
#' @export
setGeneric(name="as.memuse", 
  function(x, ...)
    standardGeneric("as.memuse"), 
  package="memuse"
)



#-------------------------------------------------
# TO memuse
#-------------------------------------------------

#' @param unit 
#' \code{string}; the unit of storage, such as "MiB" or "MB",
#' depending on prefix.  Case is ignored.
#' @param unit.prefix 
#' \code{string}; the unit prefix, namely IEC or SI.  Case
#' is ignored.
#' @param unit.names 
#' \code{string}; control for whether the unit names should
#' be printed out or their abbreviation should be used.  Options are "long" and
#' "short", respectively.  Case is ignored.
#' 
#' @rdname converters
#' @export
setMethod("as.memuse", signature(x="numeric"),
  function(x, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    ret <- internal.mu(size=x, unit=unit, unit.prefix=unit.prefix, unit.names=unit.names)
    
    return( ret )
  }
)



#' @rdname converters
#' @export
setMethod("as.memuse", signature(x="object_size"),
  function(x, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    ret <- as.memuse(x=unclass(x), unit=unit, unit.prefix=unit.prefix, unit.names=unit.names)
    
    return( ret )
  }
)



#' @rdname converters
#' @export
setMethod("as.memuse", signature(x="character"),
  function(x, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    y <- unlist(strsplit(x=x, split=" "))
    
    if (length(y) != 2)
      stop("malformed string; can not convert to a memuse object")
    
    size <- as.numeric(y[1L])
    unit <- y[2L]
    
    ret <- mu(size=size, unit=unit, unit.prefix=unit.prefix, unit.names=unit.names)
    
    return( ret )
  }
)



#-------------------------------------------------
# FROM memuse
#-------------------------------------------------

#' @rdname converters
#' @export
setMethod("as.character", signature(x="memuse"),
  function(x, ...)
  {
    ret <- utils::capture.output(print(x))
    
    return( ret )
  }
)



#' @param as.is 
#' logical; should the size be "as-is", or converted to bytes first.
#' 
#' @rdname converters
#' @export
setMethod("as.numeric", signature(x="memuse"),
  function(x, as.is=FALSE)
  {
    return( size(x, as.is=as.is) )
  }
)

