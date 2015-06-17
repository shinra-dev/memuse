### Package control

#' Control Variables for the memuse Package.
#' 
#' A set of controls which provides (changeable) default values for many
#' functions in this package.
#' 
#' Currently, there are 4 control data objects: \itemize{ \item \code{.UNIT}
#' defaults to "best".  The default choice will scale \code{size} values to the
#' nearest (by scaling factor --- 1024 or 1000 depending on unit prefix).
#' Other acceptable choices are, for example, "kb" or "kib".  If the user
#' requests the wrong unit by prefix (e.g., "kb" instead of "kib" when the unit
#' prefix is IEC), then the correct one will be chosen for the user.
#' 
#' \item \code{.PREFIX} defaults to "IEC".  Acceptable values are "IEC" and
#' "SI".
#' 
#' \item \code{.NAMES} defaults to "short".  Acceptable values are "short" and
#' "long".
#' 
#' \item \code{.PRECEDENCE} defaults to "prefix".  Acceptable values are "unit"
#' and "prefix".
#' 
#' }
#' 
#' All values are case insensitive, in that the correct case will be determined
#' for the user if the incorrect case is supplied.  For example, if the user
#' sets \code{.PREFIX <- "si"}, then the correct case ("SI") will be determined
#' as needed.
#' 
#' For a "human readable" explanation of what these values do, see the package
#' vignette.
#' 
#' @examples
#' \dontrun{
#' mu(2000)
#' .PREFIX <- "SI"
#' mu(2000)
#' }
#' 
#' @name Control Variables
#' @aliases Control .UNIT .PREFIX .NAMES .PRECEDENCE
#' @docType data
#' @seealso \code{ \link{memuse-class} \link{Constructor} }
#' @rdname control
#' @keywords Data
.UNIT <- "best"
#' @rdname control
.NAMES <- "short"
#' @rdname control
.PREFIX <- "IEC"
#' @rdname control
.PRECEDENCE <- "prefix"



.units <- list(
  short=list(
    IEC=list(
      print = c("B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB", "ZiB", "YiB"),
      check = c("b", "kib", "mib", "gib", "tib", "pib", "eib", "zib", "yib")
    ), 
    SI=list(
      print = c("B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"),
      check = c("b", "kb", "mb", "gb", "tb", "pb", "eb", "zb", "yb")
    )
  ), 
  long=list(
    IEC=list(
      print = c("bytes", "kibibytes", "mebibytes", "gibibytes", "tebibytes", "pebibytes", "exbibytes", "zebibytes", "yobibytes"),
      check = c("bytes", "kibibytes", "mebibytes", "gibibytes", "tebibytes", "pebibytes", "exbibytes", "zebibytes", "yobibytes")
    ),
    SI=list(
      print = c("bytes", "kilobytes", "megabytes", "gigabytes", "terabytes", "petabytes", "exabytes", "zettabytes", "yottabytes"),
      check = c("bytes", "kilobytes", "megabytes", "gigabytes", "terabytes", "petabytes", "exabytes", "zettabytes", "yottabytes")
    )
  )
)



.units_bits <- list(
  short=list(
    IEC=list(
      print = c("b", "Kib", "Mib", "Gib", "Tib", "Pib", "Eib", "Zib", "Yib"),
      check = c("b", "kib", "mib", "gib", "tib", "pib", "eib", "zib", "yib")
    ), 
    SI=list(
      print = c("b", "Kb", "Mb", "Gb", "Tb", "Pb", "Eb", "Zb", "Yb"),
      check = c("b", "kb", "mb", "gb", "tb", "pb", "eb", "zb", "yb")
    )
  ), 
  long=list(
    IEC=list(
      print = c("bits", "kibibits", "mebibits", "gibibits", "tebibits", "pebibits", "exbibits", "zebibits", "yobibits"),
      check = c("bits", "kibibits", "mebibits", "gibibits", "tebibits", "pebibits", "exbibits", "zebibits", "yobibits")
    ),
    SI=list(
      print = c("bits", "kilobits", "megabits", "gigabits", "terabits", "petabits", "exabits", "zettabits", "yottabits"),
      check = c("bits", "kilobits", "megabits", "gigabits", "terabits", "petabits", "exabits", "zettabits", "yottabits")
    )
  )
)


