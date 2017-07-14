library(memuse)

# Only run the test on platforms that are definitely supported.
# However, we can't possibly know the return values without knowing what machine
# is running this. So we settle for ensuring evaluation without error.
iswin <- function() tolower(.Platform$OS.type) == "windows"
ismac <- function() tolower(as.character(Sys.info()["sysname"])) == "darwin"
islin <- function() tolower(as.character(Sys.info()["sysname"])) == "linux"
supported = function() iswin() || ismac() || islin()

if (supported()){
  Sys.meminfo()
  Sys.swapinfo()
  Sys.procmem()
  Sys.cachesize()
  Sys.cachelinesize()
}
