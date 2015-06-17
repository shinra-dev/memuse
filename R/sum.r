#' memuse Arithmetic
#' 
#' Binary arithmetic operations for \code{memuse} objects.
#' 
#' Simple arithmetic reductions.
#' 
#' @name Reductions
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
#' ### This will work
#' sum(mu(10), 10)
#' 
#' ### This will not
#' sum(10, mu(10))
#' }
#' 
#' @seealso \code{ \link{Constructor} \link{memuse-class} }
#' @keywords Methods
#' @rdname sum
NULL

#' @rdname sum
#' @export
setMethod("sum", signature(x="memuse"),
  function(x, ..., na.rm=FALSE)
  {
    ret <- size(x, as.is=F)
    
    other <- list(...)
    
    # checking type of inputs
    typecheck <- sapply(other, function(i)
    {
      if ( !is.memuse(i) && !(is.numeric(i) && is.vector(i))) 
        stop("method 'sum' can only work with combinations of memuse and vector objects")
    })
    
    if (length(other) > 0){
      other <- sum(sapply(other, function(i) 
      {
        if (is.memuse(i))
          size(i, as.is=F)
        else
          sum(i)
      }))
      
      ret <- ret + other
    }
    
    ret <- mu(ret)
    
    return( ret )
  }
)

