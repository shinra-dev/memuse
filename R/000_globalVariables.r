### This file should be loaded before all other *.r files.
### 
### This is to avoid the fale positive messages from R CMD check.
###   "no visible binding for global variable"
### Suggested by Prof Brian Ripley
### ?globalVariables

utils::globalVariables(c(".units", ".units_bits", ".numbers", ".time"))
