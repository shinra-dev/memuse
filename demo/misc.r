library(memuse)

# system.time() with human-readable outputs
wc.time(Sys.sleep(1.234))

### Making numbers more readable
approx.size(1e6)
approx.size(1e7, unit.names="short")
approx.size(1e7, unit.names="comma")
