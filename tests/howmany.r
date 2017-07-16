library(memuse)

same <- function(a, b) stopifnot(all.equal(a, b))

x = mu(1000000)
hm = howmany(x)
same(hm, c(353, 353))

hm = howmany(x, 1000)
same(hm, c(1000, 125))

hm = howmany(x, ncol=1000)
same(hm, c(125, 1000))
