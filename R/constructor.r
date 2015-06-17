#' memuse Constructor
#' 
#' Constructor for objects of class \code{memuse}.
#' 
#' Simple constructor for \code{memuse} objects.
#' 
#' @param size 
#' \code{numeric}; indicates the unit-multiple number of bytes used
#' by the object.
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
#' @return 
#' Returns a \code{memuse} class object.
#' 
#' @examples
#' \dontrun{
#' x <- mu(100, unit="kb")
#' x
#' 
#' y <- mu(100, unit="kb", unit.prefix="SI")
#' y
#' }
#' 
#' @seealso \code{ \link{memuse-class} \link{Accessors} \link{Converters} }
#' @keywords Methods
#' @name Constructor
#' @rdname constructor
NULL

#' @rdname constructor
#' @export
setGeneric(name="mu", 
  function(size, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
    standardGeneric("mu"), 
  package="memuse"
)

#' @rdname constructor
#' @export
setMethod("mu", signature(size="NULL"),
  function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    return( NULL )
  }
)

#' @rdname constructor
#' @export
setMethod("mu", signature(size="numeric"),
  function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    return( internal.mu(size=size, unit=unit, unit.prefix=unit.prefix, unit.names=unit.names) )
  }
)

#' @rdname constructor
#' @export
setMethod("mu", signature(size="object_size"),
  function(size, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    return( internal.mu(size=unclass(size), unit=unit, unit.prefix=unit.prefix, unit.names=unit.names) )
  }
)

#' @rdname constructor
#' @export
setMethod("mu", signature(size="missing"),
  function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    return( memuse(0, unit=unit, unit.prefix=unit.prefix, unit.names=unit.names) )
  }
)



#' @rdname constructor
#' @export
setGeneric(name="memuse", 
  function(size, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
    standardGeneric("memuse"), 
  package="memuse"
)

#' @rdname constructor
#' @export
setMethod("memuse", signature(size="NULL"),
  function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    return( NULL )
  }
)

#' @rdname constructor
#' @export
setMethod("memuse", signature(size="missing"),
  function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    return( mu(0, unit=unit, unit.prefix=unit.prefix, unit.names=unit.names) )
  }
)

#' @rdname constructor
#' @export
setMethod("memuse", signature(size="numeric"),
  function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    return( internal.mu(size=size, unit=unit, unit.prefix=unit.prefix, unit.names=unit.names) )
  }
)

#' @rdname constructor
#' @export
setMethod("memuse", signature(size="object_size"),
  function(size, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    return( internal.mu(size=unclass(size), unit=unit, unit.prefix=unit.prefix, unit.names=unit.names) )
  }
)



#' object.size
#' 
#' @param x
#' An R object.
#' 
#' @name object.size
#' @rdname object.size
#' @export
object.size <- function(x)
{
  return( mu(utils::object.size(x)) )
}


