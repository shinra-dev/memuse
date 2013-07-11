### Accessors
setMethod("size", signature(x="memuse"),
  function(x, as.is=TRUE)
  {
    if (as.is)
      return(x@size)
    else
      return(convert.to.bytes(x)@size)
  }
)

setMethod("unit", signature(x="memuse"),
  function(x)
    return(x@unit)
)

setMethod("unit.prefix", signature(x="memuse"),
  function(x)
    return(x@unit.prefix)
)

setMethod("unit.names", signature(x="memuse"),
  function(x)
    return(x@unit.names)
)



### Replacers
setReplaceMethod("size", signature(x="memuse"),
  function(x, value)
  {
    x@size <- value
    x <- check.mu(x)
    
#    x <- swap.unit(x=x, unit=.UNIT)
    
    return( x )
  }
)

setReplaceMethod("unit", signature(x="memuse"),
  function(x, value)
  {
    x@unit <- value
    x <- check.mu(x)
    
    return( x )
  }
)

setReplaceMethod("unit.prefix", signature(x="memuse"),
  function(x, value)
  {
    x@unit.prefix <- value
    x <- check.mu(x)
    
    return( x )
  }
)

setReplaceMethod("unit.names", signature(x="memuse"),
  function(x, value)
  {
    x@unit.names <- value
    x <- check.mu(x)
    
    return( x )
  }
)
