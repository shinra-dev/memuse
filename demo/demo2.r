### Arithmetic
library(fs, quiet=T)

linebreak <- function() cat(sprintf("\n"))


fs(100) + fs(200)
fs(100) * fs(200) # = 20000/1024


#fs(10, unit.names="long") + fs(1111)
