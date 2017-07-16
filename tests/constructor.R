library(memuse)

same = function(x, y) stopifnot(identical(x, y))

x = 1L
y = 1:2
z = matrix(1:30, 10)

same(mu.size(mu(NULL)), 0)
same(mu.size(mu()), 0)
same(mu.size(mu(x)), 1)
same(mu.size(mu(object.size(x))), unclass(object.size(x)))
same(mu.size(mu(y)), unclass(object.size(y)))
same(mu.size(mu(z)), unclass(object.size(z)))

same(mu.size(memuse(NULL)), 0)
same(mu.size(memuse()), 0)
same(mu.size(memuse(x)), 1)
same(mu.size(memuse(object.size(x))), unclass(object.size(x)))
same(mu.size(memuse(y)), unclass(object.size(y)))
same(mu.size(memuse(z)), unclass(object.size(z)))



bad = mu()
stopifnot(isTRUE(validObject(bad)))

bad@size = -1
stopifnot(inherits(try(validObject(bad), silent=TRUE), "try-error"))
bad@size = 0

bad@unit = "apple"
stopifnot(inherits(try(validObject(bad), silent=TRUE), "try-error"))
bad@unit = "b"

bad@unit.prefix = "banana"
stopifnot(inherits(try(validObject(bad), silent=TRUE), "try-error"))
bad@unit.prefix = "IEC"

bad@unit.names = "orange"
stopifnot(inherits(try(validObject(bad), silent=TRUE), "try-error"))
