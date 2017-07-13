library(memuse)

same = function(x, y) stopifnot(identical(x, y))

x = 1000
y = x*10
z = y*10

same(as.character(hr(999)), "999")
same(as.character(hr(x)), "1,000")
same(as.character(hr(y)), "10,000")
same(as.character(hr(z)), "100,000")
same(as.character(hr(z*10)), "1,000,000")

same(as.character(hr(999, names="long")), "999")
same(as.character(hr(x, names="long")), "1 Thousand")
same(as.character(hr(y, names="long")), "10 Thousand")
same(as.character(hr(z, names="long")), "100 Thousand")
same(as.character(hr(z*10, names="long")), "1 Million")

same(as.character(hr(999, names="short")), "999")
same(as.character(hr(x, names="short")), "1k")
same(as.character(hr(y, names="short")), "10k")
same(as.character(hr(z, names="short")), "100k")
same(as.character(hr(z*10, names="short")), "1m")
