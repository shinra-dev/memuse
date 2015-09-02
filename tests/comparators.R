library(memuse)


f <- function(x, y)
{
  stopifnot(x<y)
  stopifnot(x<=y)
  stopifnot(!(x>y))
  stopifnot(!(x>=y))
  stopifnot(!(x==y))
  stopifnot(x!=y)
}


x <- mu(2000)
y <- mu(3000)
f(x, y)

x <- mu(2000)
y <- mu(3000, unit.prefix="SI")
f(x, y)

x <- mu(2000)
y <- 3000
f(x, y)
