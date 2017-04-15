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
