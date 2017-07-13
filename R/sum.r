#' memuse Arithmetic
#' 
#' Binary arithmetic operations for \code{memuse} objects.
#' 
#' Simple arithmetic reductions.
#' 
#' @param x 
#' A \code{memuse} object.
#' @param ... 
#' Additional arguments
#' @param na.rm 
#' Whether \code{NA}'s should be ignored.
#' 
#' @return 
#' Returns a \code{memuse} class object.
#' 
#' @examples
#' \dontrun{
#' x = mu(2000)
#' y = mu(5000)
#' 
#' sum(x, y)
#' 
#' ### Mixing numeric and memuse objects will work, but the first one must be a
#' ### memuse object.
#' sum(mu(10), 10) # This will work
#' sum(10, mu(10)) # This will not
#' }
#' 
#' @seealso \code{ \link{Constructor} \link{memuse-class} }
#' @keywords Methods
#' @export
setMethod("sum", signature(x="memuse"),
  function(x, ..., na.rm=FALSE)
  {
    ret <- mu.size(x, as.is=FALSE)
    
    other <- list(...)
    
    # checking type of inputs
    typecheck <- sapply(other, sumargcheck)
    
    if (length(other) > 0)
    {
      other <- sum(sapply(other, vectorizedsum))
      ret <- ret + other
    }
    
    internal.mu(ret, unit.prefix=mu.prefix(x), unit.names=mu.names(x))
  }
)

sumargcheck = function(i)
{
  if ( !is.memuse(i) && !(is.numeric(i) && is.vector(i)) ) 
    stop("method 'sum' can only work with combinations of memuse and vector objects")
}

vectorizedsum = function(i) 
{
  if (is.memuse(i))
    mu.size(i, as.is=FALSE)
  else
    sum(i)
}
