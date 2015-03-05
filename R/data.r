### Package control
.UNIT <- "best"
.NAMES <- "short"
.PREFIX <- "IEC"
.PRECEDENCE <- "prefix"



### mu units
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



### Misc

# From: https://en.wikipedia.org/wiki/Names_of_large_numbers
.numbers <- data.frame(
                name=c("Thousand", "Million", "Billion", "Trillion", "Quadrillion", "Quintillion", "Sextillion", "Septillion", "Octillion", "Nonillion", "Decillion", "Undecillion", "Duodecillion", "Tredecillion", "Quattuordecillion", "Quindecillion", "Sexdecillion", "Septendecillion", "Octodecillion", "Novemdecillion", "Vigintillion", "Googol", "Centillion"),
                shorthand=c("k", "m", "b", "t", "q", "qt", "sx", "sp", "ot", "n", "d", "u", "dd", "td", "qtd", "qd", "sxd", "spd", "otd", "nd", "vg", "g", "ct"),
                exponent=c(3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45, 48, 51, 54, 57, 60, 63, 100, 303),
                stringsAsFactors=F
)



.time <- list(
                 unit=c("seconds", "minutes", "hours", "days", "years", "centuries"),
                 factor=c(1.0, 60.0, 3600.0, 86400.0, 31557600, 3155760000)
)

