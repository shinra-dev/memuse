library(memuse)

n <- 9000000
x <- mu(n)

stopifnot(all.equal(swap.prefix(x), mu(n, unit.prefix="SI")))

stopifnot(all.equal(swap.names(x), mu(n, unit.names="long")))


### TODO
#y <- swap.unit(x, "kib")
#stopifnot(all.equal(y, z))
