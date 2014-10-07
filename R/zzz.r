.onUnload <- function(libpath)
{
  library.dynam.unload("memuse", libpath)

  invisible()
}
