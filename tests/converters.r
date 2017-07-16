library(memuse)

n = 2000
x = mu(n)

stopifnot(identical(as.memuse(n), x))
stopifnot(identical(as.numeric(x), n))
stopifnot(identical(as.character(x), "1.953 KiB"))

stopifnot(identical(as.memuse(100), as.memuse("100 b")))
