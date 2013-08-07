### Sum method - can handle mixed memuse/numeric
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



# sum((mu(10)+mu(4)+mu(2)+mu(2)+mu(5)+mu(5))*c(1,0,7,0,0,7,11,8,0,10,0,8,0,14,15,10,4,15,8,12,16))

