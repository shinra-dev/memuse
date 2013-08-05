### Constructor methods
setMethod("mu", signature(size="numeric"),
  function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    return( internal.mu(size=size, unit=unit, unit.prefix=unit.prefix, unit.names=unit.names) )
  }
)


setMethod("mu", signature(size="object_size"),
  function(size, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    return( internal.mu(size=unclass(size), unit=unit, unit.prefix=unit.prefix, unit.names=unit.names) )
  }
)


setMethod("memuse", signature(size="numeric"),
  function(size=0, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    return( internal.mu(size=size, unit=unit, unit.prefix=unit.prefix, unit.names=unit.names) )
  }
)


setMethod("memuse", signature(size="object_size"),
  function(size, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    return( internal.mu(size=unclass(size), unit=unit, unit.prefix=unit.prefix, unit.names=unit.names) )
  }
)


setMethod("object.size", signature(x="ANY"),
  function(x)
  {
    return( mu(utils::object.size(x)) )
  }
)


### Recasting methods
setMethod("as.numeric", signature(x="memuse"),
  function(x, ...)
  {
    return( convert_to_bytes(x)@size )
  }
)


setMethod("as.memuse", signature(x="numeric"),
  function(x, ...)
  {
    return( internal.mu(size=x, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES) )
  }
)


setMethod("as.memuse", signature(x="object_size"),
  function(x, ...)
  {
    return( as.memuse(unclass(x)) )
  }
)

