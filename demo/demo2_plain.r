### Arithmetic
library(memuse, quiet=T)

linebreak <- function(n=1) cat(sprintf(paste(rep("\n", n))))

# 100 + 200
mu(100) + mu(200)
# (100 * 200)/1024
mu(100) * mu(200)


linebreak()


.NAMES <- "long"
mu(10, unit.names="long") + mu(1111, unit.names="short")
.NAMES <- "short"
mu(10, unit.names="long") + mu(1111, unit.names="short")

