#-------------------------------------------------
# TO memuse
#-------------------------------------------------

setMethod("as.memuse", signature(x="numeric"),
  function(x, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    ret <- internal.mu(size=x, unit=unit, unit.prefix=unit.prefix, unit.names=unit.names)
    
    return( ret )
  }
)



setMethod("as.memuse", signature(x="object_size"),
  function(x, unit=.UNIT, unit.prefix=.PREFIX, unit.names=.NAMES)
  {
    ret <- as.memuse(x=unclass(x), unit=unit, unit.prefix=unit.prefix, unit.names=unit.names)
    
    return( ret )
  }
)



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

setMethod("as.character", signature(x="memuse"),
  function(x, ...)
  {
    ret <- utils::capture.output(print(x))
    
    return( ret )
  }
)



setMethod("as.numeric", signature(x="memuse"),
  function(x, as.is=FALSE)
  {
    return( size(x, as.is=as.is) )
  }
)

