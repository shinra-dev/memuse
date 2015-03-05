library(memuse)

### How much ram do you have/have free?
Sys.meminfo()
cat("\n")

### How much swap space?
Sys.swapinfo()
cat("\n")

### How much ram is the current R process using?
Sys.procmem()
cat("\n")

### How big are the processor caches?
Sys.cachesize()
cat("\n")

### How big is the cache line?
Sys.cachelinesize()
cat("\n")

### How long has your system been up (seconds since boot)?
Sys.uptime()
cat("\n")

### How long has this R session been running?
Sys.procuptime()
cat("\n")
