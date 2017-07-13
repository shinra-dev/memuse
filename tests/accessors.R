library(memuse)

same = function(x, y) stopifnot(identical(x, y))

x = mu(1024*3)

same(mu.size(x), 3)
same(mu.names(x), "short")
same(mu.prefix(x), "IEC")
same(mu.unit(x), "KiB")



x_si = swap.prefix(x)

same(mu.size(x_si), 3.072)
same(mu.names(x_si), "short")
same(mu.prefix(x_si), "SI")
same(mu.unit(x_si), "KB")



x_long = swap.names(x)

same(mu.size(x_long), 3)
same(mu.names(x_long), "long")
same(mu.prefix(x_long), "IEC")
same(mu.unit(x_long), "kibibytes")
