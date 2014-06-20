library(memuse, quiet=T)


# The best unit for representation is chosen by default
mu(2000)
mu(2000, unit="kib")

# Construction is case insensitive; we always choose the correct case.
mu(120, unit="gIb", unit.prefix="iec", unit.names="SHorT")

# If an incorrect unit is supplied (SI when should be IEC), then 
# the assumption is the prefix is correct but the unit is being 
# misused (as is typically the case).  So passing unit='kb' with 
# unit.prefix='IEC' will make the appropriate correction:
mu(2000, unit="kb")
mu(2000, unit="kb", unit.names="long")
mu(2000, unit="kb", unit.prefix="SI")


# We can change the default unit.prefix and unit.names
.NAMES <- "long"
.PREFIX <- "SI"
mu(120, unit="kb")

.PREFIX <- "IEC"
mu(120, unit="kb")

.NAMES <- "short"


# We can easily convert between different units
x <- mu(120, unit="kib")
print(x)
swap.unit(x, "kb")
swap.unit(x, "b")

