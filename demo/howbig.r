library(memuse, quiet=T)

# How big is a 1000x1000 matrix?
howbig(1000, 1000)


# How big is a 1000x1000 matrix if we distribute it across 16 cores?
howbig.par(1000, 1000, 16)


# How many rows/columns can a matrix have if it is 16 gib?
x <- mu(16, "gib")
howmany(x)


# Same as above, but with 500 columns?
howmany(x, ncol=500)


# Compare with object.size()
howbig(1000, 500)
object.size(matrix(runif(1000*500), 1000, 500))
