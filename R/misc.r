setMethod("as.numeric", signature(x="memuse"),
  function(x, ...)
  {
    return( convert.to.bytes(x)@size )
  }
)

