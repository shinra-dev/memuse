### Addition
setMethod("+", signature(e1="memuse", e2="memuse"),
  function(e1, e2) 
  {
    # if unit prefices disagree, use .PREFIX
    if (e1@unit.prefix != e2@unit.prefix){
      if (e1@unit.prefix != .PREFIX)
        e1 <- swap.prefix(e1)
      if (e2@unit.prefix != .PREFIX)
        e2 <- swap.prefix(e2)
    }
    
    # if names disagree, use .NAMES
    if (e1@unit.names != e2@unit.names){
      if (e1@unit.names != .NAMES)
        e1 <- swap.names(e1)
    }
    
    e1 <- convert.to.bytes(e1)
    e2 <- convert.to.bytes(e2)
    
    e1@size <- e1@size + e2@size
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



setMethod("+", signature(e1="memuse", e2="numeric"),
  function(e1, e2) 
  {
    if (length(e2) != 1)
      stop("memuse * vector : vector must be of length 1")
    
    e1 <- convert.to.bytes(e1)
    
    e1@size <- e1@size + e2
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



setMethod("+", signature(e1="numeric", e2="memuse"),
  function(e1, e2)
  {
    if (length(e1) != 1)
      stop("vector * memuse : vector must be of length 1")
    else
      return( e2+e1 )
  }
)



### Subtraction
setMethod("-", signature(e1="memuse", e2="memuse"),
  function(e1, e2)
    return( e1+(-1*e2) )
)


setMethod("-", signature(e1="memuse", e2="numeric"),
  function(e1, e2)
  {
    if (length(e2) != 1)
      stop("vector * memuse : vector must be of length 1")
    else
      return( e1+(-1*e2) )
  }
)


setMethod("-", signature(e1="numeric", e2="memuse"),
  function(e1, e2)
  {
    if (length(e1) != 1)
      stop("vector * memuse : vector must be of length 1")
    else
      return( e1+(-1*e2) )
  }
)


setMethod("-", signature(e1="memuse", e2="missing"),
  function(e1, e2)
    return( -1*e1 )
)



### Multiplication
setMethod("*", signature(e1="memuse", e2="memuse"),
  function(e1, e2) 
  {
    # if unit prefices disagree, use .PREFIX
    if (e1@unit.prefix != e2@unit.prefix){
      if (e1@unit.prefix != .PREFIX)
        e1 <- swap.prefix(e1)
      if (e2@unit.prefix != .PREFIX)
        e2 <- swap.prefix(e2)
    }
    
    # if names disagree, use .NAMES
    if (e1@unit.names != e2@unit.names){
      if (e1@unit.names != .NAMES)
        e1 <- swap.names(e1)
    }
    
    e1 <- convert.to.bytes(e1)
    e2 <- convert.to.bytes(e2)
    
    e1@size <- e1@size * e2@size
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



setMethod("*", signature(e1="memuse", e2="numeric"),
  function(e1, e2) 
  {
    if (length(e2) != 1)
      stop("memuse * vector : vector must be of length 1")
    
    e1 <- convert.to.bytes(e1)
    
    e1@size <- e1@size * e2
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



setMethod("*", signature(e1="numeric", e2="memuse"),
  function(e1, e2)
  {
    if (length(e1) != 1)
      stop("vector * memuse : vector must be of length 1")
    else
      return( e2*e1 )
  }
)


### Division
setMethod("/", signature(e1="memuse", e2="memuse"),
  function(e1, e2) 
  {
    # if unit prefices disagree, use .PREFIX
    if (e1@unit.prefix != e2@unit.prefix){
      if (e1@unit.prefix != .PREFIX)
        e1 <- swap.prefix(e1)
      if (e2@unit.prefix != .PREFIX)
        e2 <- swap.prefix(e2)
    }
    
    # if names disagree, use .NAMES
    if (e1@unit.names != e2@unit.names){
      if (e1@unit.names != .NAMES)
        e1 <- swap.names(e1)
    }
    
    e1 <- convert.to.bytes(e1)
    e2 <- convert.to.bytes(e2)
    
    e1@size <- e1@size / e2@size
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



setMethod("/", signature(e1="memuse", e2="numeric"),
  function(e1, e2) 
  {
    if (length(e2) != 1)
      stop("memuse * vector : vector must be of length 1")
    
    e1 <- convert.to.bytes(e1)
    
    e1@size <- e1@size / e2
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



setMethod("/", signature(e1="numeric", e2="memuse"),
  function(e1, e2)
  {
    if (length(e1) != 1)
      stop("vector * memuse : vector must be of length 1")
    else
      return( e2/e1 )
  }
)



### Exponentiation
setMethod("^", signature(e1="memuse", e2="memuse"),
  function(e1, e2) 
  {
    # if unit prefices disagree, use .PREFIX
    if (e1@unit.prefix != e2@unit.prefix){
      if (e1@unit.prefix != .PREFIX)
        e1 <- swap.prefix(e1)
      if (e2@unit.prefix != .PREFIX)
        e2 <- swap.prefix(e2)
    }
    
    # if names disagree, use .NAMES
    if (e1@unit.names != e2@unit.names){
      if (e1@unit.names != .NAMES)
        e1 <- swap.names(e1)
    }
    
    e1 <- convert.to.bytes(e1)
    e2 <- convert.to.bytes(e2)
    
    e1@size <- e1@size ^ e2@size
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



setMethod("^", signature(e1="memuse", e2="numeric"),
  function(e1, e2) 
  {
    if (length(e2) != 1)
      stop("memuse ^ vector : vector must be of length 1")
    
    e1 <- convert.to.bytes(e1)
    
    e1@size <- e1@size ^ e2
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)
