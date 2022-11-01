# memuse 

* **Version:** 4.2-2
* **License:** [BSD 2-Clause](https://opensource.org/licenses/BSD-2-Clause)
* **Project home**: https://github.com/shinra-dev/memuse
* **Bug reports**: https://github.com/shinra-dev/memuse/issues


**memuse** is an R package for memory estimation.  It has tools for estimating the size of a matrix (that doesn't exist), showing the size of an existing object in a nicer way than `object.size()`.  It also has tools for showing how much memory the current R process is consuming, how much ram is available on the system, and more.

Originally, this package was an over-engineered solution to a mostly non-existent problem, as a sort of love letter to other needlessly complex programs like the [Enterprise Fizzbuzz](https://github.com/EnterpriseQualityCoding/FizzBuzzEnterpriseEdition).  However, as of version 2.0-0, I'm sad to report that the package is actually becoming quite useful.

The package has been exhaustively tested on Linux, FreeBSD, Windows, Mac, and "other"-NIX.  That is also roughly the platforms in descending order of support for the various operations.  However, if you have a problem installing or using the package, please open an issue on the project's GitHub repository.


## Installation

To install the R package, run:

```r
install.package("memuse")
```

The development version is maintained on GitHub:

```r
remotes::install_github("shinra-dev/memuse")
```

The C internals, found in `memuse/src/meminfo/` are completely separated from the R wrapper code.  So if you prefer, you can easily build this as a standalone C shared library.



## Package Utilities

The package comes with several classes of utilities.  I find all of them very useful during the course of benchmarking, but some are certainly more useful than others.


#### Memory Lookups
With this package you can get some information about how much memory is physically available on the host machine:

```r
Sys.meminfo()
# Totalram:  15.656 GiB 
# Freeram:   10.504 GiB 

Sys.meminfo(compact.free=FALSE) ### Linux and FreeBSD only
# Totalram:   15.656 GiB 
# Freeram:     1.067 GiB 
# Bufferram:   1.332 GiB 
# Cachedram:   8.207 GiB 

Sys.swapinfo() ## same as Sys.pageinfo()
# Totalswap:    32.596 GiB 
# Freeswap:     32.595 GiB 
# Cachedswap:  444.000 KiB 
```

You can find the ram usage of the current R process:

```r
Sys.procmem()
# Size:  258.426 MiB 
# Peak:  258.426 MiB 

x <- rnorm(1e8)
memuse(x)
# 762.939 MiB

rm(x);invisible(gc())

Sys.procmem()
# Size:   258.426 MiB 
# Peak:  1021.363 MiB 
```

Also, if you're working close to the metal, you may be interested in seeing how large the CPU caches are and/or how big the cache linesize is:

```r
Sys.cachesize()
# L1I:   32.000 KiB 
# L1D:   32.000 KiB 
# L2:   256.000 KiB 
# L3:     6.000 MiB 

Sys.cachelinesize()
# Linesize:  64 B 
```



#### Estimating Memory Usage
You can estimate memory storage requirements of a matrix without having to divide by some annoying power of 2:

```r
howbig(10000, 500)
# 38.147 MiB

howbig(10000, 500, type="int")
# 19.073 MiB

howbig(10000, 500, representation="sparse", sparsity=.05)
# 1.907 MiB
```

Alternatively, given a (memory) size, you can also find the dimensions of such a matrix:

```r
howmany(mu(800, "mib"))
# [1] 10240 10240
howmany(mu(800, "mib"), ncol=500)
# [1] 209715    500
```

For more information, see the package vignette.


#### Misc
The package also has some miscellaneous helpful utilities:

```r
approx.size(12345)
# 12.3 Thousand
 
approx.size(123456789)
# 123.5 Million
 
approx.size(123456789, unit.names="short")
# 123.5m
 
approx.size(123456789, unit.names="comma")
# 123,456,789
```



## Authors

memuse is authored and maintained by:

* Drew Schmidt

With additional contributions from:

* Christian Heckendorf (FreeBSD improvements to meminfo)
* Wei-Chen Chen (Windows build fixes)
* Dan Burgess (donation of a Mac for development and testing)
