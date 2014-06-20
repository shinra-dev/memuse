library(memuse, quiet=T)


# 100 + 200
mu(100) + mu(200)
# (100 * 200)/1024
mu(100) * mu(200)



.NAMES <- "long"
mu(10, unit.names="long") + mu(1111, unit.names="short")
.NAMES <- "short"
mu(10, unit.names="long") + mu(1111, unit.names="short")


