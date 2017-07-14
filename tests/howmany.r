library(memuse)

same <- function(a, b) stopifnot(all.equal(a, b))

x <- mu(1000000)
hm <- howmany(x)
same(hm, c(353, 353))
