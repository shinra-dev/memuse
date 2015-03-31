library(memuse)

test <- function(a, b) stopifnot(all.equal(a, b))

hb <- howbig(1000, 500)
test(as.numeric(hb), 4e6)
test(as.numeric(hb, as.is=TRUE), 4e6/1024/1024)


x <- mu(1000000)
hm <- howmany(x)
test(hm, c(353, 353))
