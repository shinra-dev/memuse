# memuse 

* **Version:** 2.6
* **Status:** [![Build Status](https://travis-ci.org/shinra-dev/memuse.png)](https://travis-ci.org/shinra-dev/memuse) 
* **License:** [![License](http://img.shields.io/badge/license-GPL%20%28%3E=%202%29-orange.svg?style=flat)](http://www.gnu.org/licenses/gpl-2.0.html)
* **Author:** Drew Schmidt


Originally, this package was an over-engineered solution to a mostly 
non-existent problem, as a sort of love letter to other needlessly complex 
programs like the
[Enterprise Fizzbuzz](https://github.com/Mikkeren/FizzBuzzEnterpriseEdition)

However, as of version 2.0, I'm sad to report that the package is actually
becoming quite useful.



## Package Utilities

The package comes with several classes of utilities.  I find all
of them very useful during the course of benchmarking, but 
some are certainly more useful than others.


#### Memory Lookups
With this package you can get some information about
how much memory is physically available on the host machine:

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
object.size(x)
# 762.939 MiB

rm(x);invisible(gc())

Sys.procmem()
# Size:   258.426 MiB 
# Peak:  1021.363 MiB 
```

Also, if you're working close to the metal, you may be interested
in seeing how large the CPU caches are and/or how big the cache
linesize is:

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

You can estimate memory storage requirements of a matrix without
having to divide by some annoying power of 2:

```r
howbig(10000, 500)
# 38.147 MiB

howbig(10000, 500, type="int")
# 19.073 MiB

howbig(10000, 500, representation="sparse", sparsity=.05)
# 1.907 MiB
```

Alternatively, given a (memory) size, you can also find the dimensions
of such a matrix:

```r`
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



## Installation

```r
devtools::install_github("wrathematics/memuse")
```



## Software license and disclaimer

The R package is licensed under the GNU General Public License, version
2 or greater, basically as a joke (see the vignette for details).
The C library 'meminfo' located in src/meminfo of the
memuse package source tree is additionally licensed under the 
permissive 2-clause BSD license.


## Authors

memuse is authored and maintained by:
* Drew Schmidt

With additional contributions from:
* Wei-Chen Chen
* Christian Heckendorf

We would also specially like to thank Dan Burgess for contributing
a Mac for development and testing.
