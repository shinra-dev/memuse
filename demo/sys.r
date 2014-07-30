library(memuse)

### How much ram do you have/have free?
Sys.meminfo()

### How much swap space?
Sys.swapinfo()

### How much ram is the current R process using?
Sys.procmem()

### How big are the processor caches?
Sys.cacheinfo()
