### Addition
setMethod("+", signature(e1="fs", e2="fs"),
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
    
    ret <- best.unit(e1)
    
    return( ret )
  }
)



### Multiplication
setMethod("*", signature(e1="fs", e2="fs"),
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
    
    ret <- best.unit(e1)
    
    return( ret )
  }
)



### Exponentiation
setMethod("^", signature(e1="fs", e2="fs"),
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
    
    ret <- best.unit(e1)
    
    return( ret )
  }
)
