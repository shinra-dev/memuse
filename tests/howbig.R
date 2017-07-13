library(memuse)

same <- function(a, b) stopifnot(all.equal(a, b))

m = 1000
n = 500

hb <- howbig(m, n)
same(as.numeric(hb), 4e6)
same(mu.size(hb), 4e6/1024/1024)
