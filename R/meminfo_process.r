meminfo.process <- function()
{
  out <- .Call("R_memuse_process_size")
  
  ret <- mu(out)
  
  return( ret )
}
