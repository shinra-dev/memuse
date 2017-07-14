library(memuse)

same = function(x, y) stopifnot(all.equal(x, y))

x = mu(5000, prefix="SI")
y = mu(4001, prefix="SI")
z = 100
class(z) = "object_size"

same(mu.size(x+y), 9.001)
same(mu.size(x+1000), 6)
same(mu.size(1000+x), 6)
same(mu.size(x+z), 5.1)
same(mu.size(z+x), 5.1)

same(mu.size(x-y), 999)
same(mu.size(x-1000), 4)
same(mu.size(10000-x), 5)
same(mu.size(x-z), 4.9)
same(mu.size(51*z - x), 100)

same(mu.size(x*y), 20.005)
same(mu.size(x*2), 10)
same(mu.size(2*x), 10)
same(mu.size(x*z), 500)
same(mu.size(z*x), 500)

same(x/y, 5/4.001)
same(mu.size(x/2), 2.5)
same(10000/x, 2)
same(x/z, 50)
same(z/x, 0.02)

same(mu.size(x^2), 25)
same(mu.size(x^x), Inf)



same(mu.size(sum(x, y, 999)), 10)
