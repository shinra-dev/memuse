library(memuse)

n = 2000
x = mu(n)

stopifnot(identical(as.memuse(n), x))
stopifnot(identical(as.numeric(x), n))
stopifnot(identical(as.character(x), "1.953 KiB"))
