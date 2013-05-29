# print method
setMethod("print", signature(x="memuse"),
  function(x, ..., unit=x@unit, unit.prefix=x@unit.prefix, unit.names=x@unit.names, digits=3)
  {
    if (unit.names != x@unit.names)
      x <- swap.names(x)
    if (unit.prefix != x@unit.prefix)
      x <- swap.prefix(x)
    if (unit != x@unit)
      x <- swap.unit(x, unit)
    
    unit <- tolower(x@unit)
    if (unit == "b" || unit == "bytes")
      digits <- 0
    
    if (x@size > 1e22)
      format <- "e"
    else
      format <- "f"
    
    cat(sprintf(paste("%.", digits, format, " ", x@unit, "\n", sep=""), x@size))
  }
)

# show method
setMethod("show", signature(object="memuse"),
  function(object) 
    print(object, unit=object@unit, unit.prefix=object@unit.prefix, unit.names=object@unit.names, digits=3)
)

