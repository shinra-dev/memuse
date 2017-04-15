#' memuse Constructor
#' 
#' Constructor for objects of class \code{memuse}.
#' 
#' For numeric objects, if the length is 1, then its value is used
#' as the number of bytes.  Otherwise, the object's memory usage
#' in R is taken for the size parameter.
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
#' ### The value passed as 'size' is the number of bytes
#' x <- memuse(100, unit="kb")
#' x
#' 
#' y <- memuse(100, unit="kb", unit.prefix="SI")
#' y
#' 
#' ### Use the memory usage of object 'size'
#' memuse(rnorm(1e4))
#' }
#' 
#' @importFrom utils object.size
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
setMethod("mu", signature(size="ANY"),
  function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
    mu(utils::object.size(size), unit=unit, unit.prefix=unit.prefix, unit.names=unit.names)
)

#' @rdname constructor
#' @export
setMethod("mu", signature(size="NULL"),
  function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    memuse(0, unit=unit, unit.prefix=unit.prefix, unit.names=unit.names)
  }
)

#' @rdname constructor
#' @export
setMethod("mu", signature(size="numeric"),
  function(size, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    if (NROW(size) == 1 && NCOL(size) == 1)
      internal.mu(size=size, unit=unit, unit.prefix=unit.prefix, unit.names=unit.names)
    else
      mu(utils::object.size(size), unit=unit, unit.prefix=unit.prefix, unit.names=unit.names)
  }
)

#' @rdname constructor
#' @export
setMethod("mu", signature(size="object_size"),
  function(size, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    internal.mu(size=unclass(size), unit=unit, unit.prefix=unit.prefix, unit.names=unit.names)
  }
)

#' @rdname constructor
#' @export
setMethod("mu", signature(size="missing"),
  function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    memuse(0, unit=unit, unit.prefix=unit.prefix, unit.names=unit.names)
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
setMethod("memuse", signature(size="ANY"),
  function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
    mu(utils::object.size(size), unit=unit, unit.prefix=unit.prefix, unit.names=unit.names)
)

#' @rdname constructor
#' @export
setMethod("memuse", signature(size="NULL"),
  function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
    mu(size, unit, unit.prefix, unit.names)
)

#' @rdname constructor
#' @export
setMethod("memuse", signature(size="missing"),
  function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
    mu(size, unit, unit.prefix, unit.names)
)

#' @rdname constructor
#' @export
setMethod("memuse", signature(size="numeric"),
  function(size=size, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
    mu(size, unit, unit.prefix, unit.names)
)

#' @rdname constructor
#' @export
setMethod("memuse", signature(size="object_size"),
  function(size, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
    mu(size, unit, unit.prefix, unit.names)
)
