#-------------------------------------------------
# TO memuse
#-------------------------------------------------

setMethod("as.memuse", signature(x="numeric"),
  function(x, ...)
  {
    ret <- internal.mu(size=x, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
    
    return( ret )
  }
)



setMethod("as.memuse", signature(x="object_size"),
  function(x, ...)
  {
    ret <- as.memuse(unclass(x))
    
    return( ret )
  }
)



#-------------------------------------------------
# FROM memuse
#-------------------------------------------------

setMethod("as.character", signature(x="memuse"),
  function(x, ..., unit=x@unit, unit.prefix=x@unit.prefix, unit.names=x@unit.names, digits=3)
  {
    ret <- utils::capture.output(print(x, unit=unit, unit.prefix=unit.prefix, unit.names=unit.names, digits=digits))
    
    return( ret )
  }
)



setMethod("as.numeric", signature(x="memuse"),
  function(x, ...)
  {
    return( convert_to_bytes(x)@size )
  }
)

