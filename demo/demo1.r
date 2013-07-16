library(memuse, quiet=T)

iprint <- function(str)
{
  cat(sprintf(paste("> ", str, "\n", sep="")))
  eval(parse(text=str))
}

linebreak <- function(n=1) cat(sprintf(paste(rep("\n", n))))


# ------------------------------------------------------

cat(sprintf("### Basic construction and object options\n\n\n"))

cat(sprintf("# The best unit for representation is chosen by default\n"))
iprint("mu(2000)")
iprint("mu(2000, unit=\"kib\")")


cat(sprintf("
# Construction is case insensitive; we always choose the correct 
case.\n"))
iprint("mu(120, unit=\"gIb\", unit.prefix=\"iec\", unit.names=\"SHorT\")")


cat(sprintf("
# If an incorrect unit is supplied (SI when should be IEC), then 
the assumption is the prefix is correct but the unit is being 
misused (as is typically the case).  So passing unit='kb' with 
unit.prefix='IEC' will make the appropriate correction:\n"))
iprint("mu(2000, unit=\"kb\")")
iprint("mu(2000, unit=\"kb\", unit.names=\"long\")")
iprint("mu(2000, unit=\"kb\", unit.prefix=\"SI\")")

linebreak()


cat(sprintf("# We can change the default unit.prefix and unit.names\n"))
cat(sprintf("> .NAMES <- \"long\"\n"))
.NAMES <- "long"
cat(sprintf("> .PREFIX <- \"SI\"\n"))
.PREFIX <- "SI"
iprint("mu(120, unit=\"kb\")")

cat(sprintf(".PREFIX <- \"IEC\"\n"))
iprint("mu(120, unit=\"kb\")")

cat(sprintf("> .NAMES <- \"short\""))
.NAMES <- "short"

linebreak(2)

cat(sprintf("# We can easily convert between different units\n"))
iprint("> x <- mu(120, unit=\"kib\")")
x <- mu(120, unit="kib")
iprint("print(x)")
iprint("swap.unit(x, \"kb\")")
iprint("swap.unit(x, \"b\")")
