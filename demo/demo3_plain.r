### howbig() and howmany()
library(memuse, quiet=T)

linebreak <- function(n=1) cat(sprintf(paste(rep("\n", n))))

# How big is a 1000x1000 matrix?
howbig(1000, 1000)

linebreak()

# How big is a 1000x1000 matrix if we distribute it across 16 cores?
howbig.par(1000, 1000, 16)

linebreak()

# How many rows/columns can a matrix have if it is 16 gib?
x <- mu(16, "gib")
howmany(x)

linebreak(1)

# Same as above, but with 500 columns?
howmany(x, ncol=500)
