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
