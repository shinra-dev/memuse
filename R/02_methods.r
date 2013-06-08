### Method declarations
#setGeneric(name="print", 
#  useAsDefault=base::print, 
#  package="MemUse"
#)

### Accessors
setGeneric(name="size", 
  function(x)
    standardGeneric("size"), 
  package="MemUse"
)

setGeneric(name="unit", 
  function(x)
    standardGeneric("unit"), 
  package="MemUse"
)

setGeneric(name="unit.prefix", 
  function(x)
    standardGeneric("unit.prefix"), 
  package="MemUse"
)

setGeneric(name="unit.names", 
  function(x)
    standardGeneric("unit.names"), 
  package="MemUse"
)


### Replacers
setGeneric(name="size<-", 
  function(x, value)
    standardGeneric("size<-"), 
  package="MemUse"
)

setGeneric(name="unit<-", 
  function(x, value)
    standardGeneric("unit<-"), 
  package="MemUse"
)

setGeneric(name="unit.prefix<-", 
  function(x, value)
    standardGeneric("unit.prefix<-"), 
  package="MemUse"
)

setGeneric(name="unit.names<-", 
  function(x, value)
    standardGeneric("unit.names<-"), 
  package="MemUse"
)


### Swaps
setGeneric(name="swap.unit", 
  function(x, unit)
    standardGeneric("swap.unit"), 
  package="MemUse"
)

setGeneric(name="swap.prefix", 
  function(x) 
    standardGeneric("swap.prefix"),
  package="MemUse"
)

setGeneric(name="swap.names", 
  function(x)
    standardGeneric("swap.names"), 
  package="MemUse"
)


### Other
setGeneric(name="howmany", 
  function(x, ...)
    standardGeneric("howmany"), 
  package="MemUse"
)
