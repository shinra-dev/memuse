library(memuse)

same <- function(a, b) stopifnot(all.equal(a, b))

m = 1000
n = 500

hb <- howbig(m, n)
same(as.numeric(hb), 4e6)
same(mu.size(hb), 4e6/1024/1024)



test = howbig(50, 50, representation="sparse", sparsity=.01)
truth = mu(200)
same(test, truth)
