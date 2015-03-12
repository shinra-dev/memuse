### validObject check
valid.mu <- function(object)
{
  if (!class(object) == "memuse")
    return( "Not a class 'memuse' object" )
  
  object@unit.names <- tolower(object@unit.names)
  if ( !(object@unit.names %in% c("short", "long")) )
    return( "invalid slot 'unit.names'.  See help('memuse')" )
  
  object@unit.prefix <- toupper(object@unit.prefix)
  if ( !(object@unit.prefix %in% c("IEC", "SI")) )
    return( "invalid slot 'unit.prefix'.  See help('memuse')" )
  
  unit <- tolower(object@unit)
  if ( !(unit %in% .units[["short"]][["IEC"]][["check"]]) &&
       !(unit %in% .units[["short"]][["SI"]][["check"]]) &&
       !(unit %in% .units[["long"]][["IEC"]][["check"]]) &&
       !(unit %in% .units[["long"]][["SI"]][["check"]]) )
    return( "invalid slot 'unit'.  See help('memuse')" )
}


### memory usage (memuse) class
# slots are:  
   # size --- the actual size in some memuse units
   # unit --- the memuse unit (e.g., byte, kilobyte, etc.)
   # unit.prefix --- IEC or SI units
   # unit.names --- short (e.g., kb) or long (e.g., kilobyte)
#' Class memuse
#' 
#' Memory usage class object.
#' 
#' 
#' @name memuse-class
#' @docType class
#' @section Creating Objects: \code{new('memuse', size = ..., unit = ...,
#' unit.prefix = ..., unit.names = ...)}
#' 
#' @slot size
#' TODO
#' @slot unit
#' TODO
#' @slot unit.prefix
#' TODO
#' @slot unit.names
#' TODO
#' 
#' \code{memuse(size = ..., unit = ..., unit.prefix = ..., unit.names = ...)}
#' 
#' \code{mu(size = ..., unit = ..., unit.prefix = ..., unit.names = ...)}
#' @seealso \code{ \link{Control} \link{Constructor} }
#' @keywords Classes
setClass("memuse", 
  representation(
    size="numeric",
    unit="character",
    unit.prefix="character",
    unit.names="character"
  ),
  prototype(
    size=0,
    unit="B",
    unit.prefix="IEC",
    unit.names="short"
  ), 
  validity=valid.mu
)


### Virtual classes

# to prevent R whining during package installation
setClass("object_size") 

# for nice printing
setClass("approx", representation="VIRTUAL")

