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
