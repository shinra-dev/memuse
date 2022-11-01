valid.mu <- function(object)
{
  if (!inherits(object, "memuse"))
    return( "Not a class 'memuse' object" )
  
  if (object@size < 0)
    return("invalid slot 'size'; must be >= 0")

  object@unit.names <- tolower(object@unit.names)
  if ( !(object@unit.names %in% c("short", "long")) )
    return( "invalid slot 'unit.names'.  See ?memuse" )
  
  object@unit.prefix <- toupper(object@unit.prefix)
  if ( !(object@unit.prefix %in% c("IEC", "SI")) )
    return( "invalid slot 'unit.prefix'.  See ?memuse" )
  
  unit <- tolower(object@unit)
  if ( !(unit %in% .units[["short"]][["IEC"]][["check"]]) &&
       !(unit %in% .units[["short"]][["SI"]][["check"]]) &&
       !(unit %in% .units[["long"]][["IEC"]][["check"]]) &&
       !(unit %in% .units[["long"]][["SI"]][["check"]]) )
    return( "invalid slot 'unit'.  See ?memuse" )
}



#' Class memuse
#' 
#' Memory usage class object.
#' 
#' @slot size
#' The actual size in some memuse units.
#' @slot unit
#' The mem unit (e.g., byte, kilobyte, etc.)
#' @slot unit.prefix
#' IEC or SI units
#' @slot unit.names
#' short (e.g., kb) or long (e.g., kilobyte)
#' 
#' @seealso \code{ \link{Control} \link{Constructor} }
#' @keywords Classes
#' @name memuse-class
#' @docType class
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



# to prevent R whining during package installation
setClass("object_size") 
