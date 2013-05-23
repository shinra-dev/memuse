valid.fs <- function(object)
{
  if (!class(object) == "fs")
    return( "Not a class 'fs' object" )
  
  object@unit.names <- tolower(object@unit.names)
  if ( !(object@unit.names %in% c("short", "long")) )
    return( "invalid slot 'unit.names'.  See help('fs')" )
  
  object@unit.prefix <- toupper(object@unit.prefix)
  if ( !(object@unit.prefix %in% c("IEC", "SI")) )
    return( "invalid slot 'unit.prefix'.  See help('fs')" )
  
  unit <- tolower(object@unit)
  if ( !(unit %in% .units[["short"]][["IEC"]][["check"]]) &&
       !(unit %in% .units[["short"]][["SI"]][["check"]]) &&
       !(unit %in% .units[["long"]][["IEC"]][["check"]]) &&
       !(unit %in% .units[["long"]][["SI"]][["check"]]) )
    return( "invalid slot 'unit'.  See help('fs')" )
}

### filesize (fs) class
# slots are:  
   # size --- the actual size in some filesize units
   # unit --- the filesize unit (e.g., byte, kilobyte, etc.)
   # unit.prefix --- IEC or SI units
   # unit.names --- short (e.g., kb) or long (e.g., kilobyte)
setClass("fs", 
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
          validity=valid.fs
)

