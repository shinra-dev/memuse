library(memuse)

same = function(x, y) stopifnot(all.equal(x, y))

n <- 9000000
x <- mu(n)

same(swap.prefix(x), mu(n, prefix="SI"))
same(swap.names(x), mu(n, names="long"))

same(mu.size(swap.unit(x, "kib")), mu.size(x)*1024)
