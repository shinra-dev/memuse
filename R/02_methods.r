### Method declarations
setGeneric(name="print", useAsDefault=base::print, package="fs")

setGeneric(name="swap.unit", 
  function(x, unit)
    standardGeneric("swap.unit"), 
  package="fs"
)

setGeneric(name="swap.prefix", 
  function(x) 
    standardGeneric("swap.prefix"),
  package="fs"
)

setGeneric(name="swap.names", 
  function(x)
    standardGeneric("swap.names"), 
  package="fs"
)

setGeneric(name="howmany", 
  function(x, ...)
    standardGeneric("howmany"), 
  package="fs"
)
