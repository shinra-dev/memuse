# memuse

Originally, this package was an over-engineered solution to a mostly 
non-existent problem, as a sort of love letter to other needlessly complex 
programs like the
[Enterprise Fizzbuzz](https://github.com/Mikkeren/FizzBuzzEnterpriseEdition)

However, as of version 2.0, I'm sad to report that the package is actually
becoming quite useful.  With this package you can get some information about
how much ram is physically available on the host machine:

```r
Sys.meminfo()
Sys.swapinfo() ## same as Sys.pageinfo()
```

You can find the ram usage of the current R process:

```r
Sys.procmem()
```

You can also estimate how much ram a matrix would require to store:

```r
howbig()
howmany()
```

Finally, the package is full of helpful printing utilities and replacements for
native R functionality (with better outputs):

```r
object.size()
wc.time() ## replaces system.time()
approx.size()
```

For more information, see the package vignette.



## How do I install it?

The easiest way is to use the
[devtools package](https://github.com/hadley/devtools):

```r
library(devtools)

install_github("wrathematics/RNACI") # dependency
install_github("wrathematics/memuse")
```



## Software license and disclaimer

The R package is licensed under the GNU General Public License, version
2 or greater.  The C library 'meminfo' located in src/meminfo of the
memuse package source tree is additionally licensed under the 
permissive 2-clause BSD license.
