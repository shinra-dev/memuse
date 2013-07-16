library(memuse, quiet=T)

iprint <- function(str)
{
  cat(sprintf(paste("> ", str, "\n", sep="")))
  eval(parse(text=str))
}

linebreak <- function(n=1) cat(sprintf(paste(rep("\n", n))))


# ------------------------------------------------------

cat(sprintf("### Arithmetic\n\n"))

cat(sprintf("# 100 + 200\n"))
iprint("mu(100) + mu(200)")
cat(sprintf("# (100 * 200)/1024\n"))
iprint("mu(100) * mu(200)")

linebreak()

cat(sprintf("> .NAMES <- \"long\"\n"))
.NAMES <- "long"
mu(10, unit.names="long") + mu(1111, unit.names="short")
cat(sprintf("> .NAMES <- \"short\"\n"))
.NAMES <- "short"
mu(10, unit.names="long") + mu(1111, unit.names="short")

