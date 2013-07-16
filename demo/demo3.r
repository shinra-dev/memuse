library(memuse, quiet=T)

iprint <- function(str)
{
  cat(sprintf(paste("> ", str, "\n", sep="")))
  eval(parse(text=str))
}

linebreak <- function(n=1) cat(sprintf(paste(rep("\n", n))))


# ------------------------------------------------------

cat(sprintf("### howbig() and howmany()\n\n"))

cat(sprintf("# How big is a 1000x1000 matrix?\n"))
iprint("howbig(1000, 1000)")

linebreak(2)
cat(sprintf("# How big is a 1000x1000 matrix if we distribute it across 16 cores?\n"))
iprint("howbig.par(1000, 1000, 16)")

linebreak()

cat(sprintf("# How many rows/columns can a matrix have if it is 16 gib?\n"))
cat(sprintf("> x <- mu(16, \"gib\")\n"))
x <- mu(16, "gib")
iprint("howmany(x)")

linebreak(2)

cat(sprintf("# Same as above, but with 500 columns?\n"))
iprint("howmany(x, ncol=500)")
