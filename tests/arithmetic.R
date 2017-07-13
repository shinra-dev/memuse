library(memuse)

same = function(x, y) stopifnot(all.equal(x, y))

x = mu(5000, prefix="SI")
y = mu(4001, prefix="SI")
z = object.size(x)

same(mu.size(x+y), 9.001)
same(mu.size(x+1000), 6)
same(mu.size(1000+x), 6)
same(mu.size(x+z), 6.256)
same(mu.size(z+x), 6.256)

same(mu.size(x-y), 999)
same(mu.size(x-1000), 4)
same(mu.size(10000-x), 5)
same(mu.size(x-z), 3.744)
same(mu.size((4*z)-x), 24)

same(mu.size(x*y), 20.005)
same(mu.size(x*2), 10)
same(mu.size(2*x), 10)
same(mu.size(x*z), 6.28)
same(mu.size(z*x), 6.28)

same(x/y, 5/4.001)
same(mu.size(x/2), 2.5)
same(10000/x, 2)
same(x/z, 5000/as.numeric(z))
same(z/x, as.numeric(z)/5000)

same(mu.size(x^2), 25)
same(mu.size(x^x), Inf)



same(mu.size(sum(x, y, 999)), 10)
