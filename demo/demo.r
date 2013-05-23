### Basic construction and object options
library(fs, quiet=T)

linebreak <- function() cat(sprintf("\n"))

# The best unit for representation is chosen by default
fs(2000)
fs(2000, unit="kib")

linebreak()


# Construction is case insensitive; we always choose the correct case
fs(120, unit="gIb", unit.prefix="iec", unit.names="SHorT")

linebreak()


# If an incorrect unit is supplied (SI when should be IEC), then the
# assumption is the prefix is correct but the unit is being misused
# (as is commonly the case).  So passing unit="kb" with unit.prefix="IEC"
# will make the appropriate correction:
fs(2000, unit="kb")
fs(2000, unit="kb", unit.names="long")

linebreak()


# We can change the default unit.prefix and unit.names
.NAMES <- "long"
.PREFIX <- "SI"
fs(120, unit="kb")

.PREFIX <- "IEC"
fs(120, unit="kb")

.NAMES <- "short"

linebreak()

# We can easily convert between different units
x <- fs(120, unit="kib")
print(x)
swap.unit(x, "kb")
swap.unit(x, "b")
