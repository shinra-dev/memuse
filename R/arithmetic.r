# -------------------------------------------------
# Addition
# -------------------------------------------------

#' Binary Arithmetic
#' 
#' Binary arithmetic operations for \code{memuse} objects.
#' 
#' Simple binary arithmetic for \code{memuse} objects.  Options include any
#' combination of \code{memuse}, \code{object_size} (output from the
#' \code{object.size()} function), and \code{numeric} objects.
#' 
#' @param e1,e2
#' \code{memuse}, \code{numeric}, or \code{object_size} objects.
#' 
#' @return Returns a \code{memuse} class object.
#' 
#' @examples
#' \dontrun{
#' x <- mu(200)
#' y <- mu(100)
#' 
#' x+y
#' x-y
#' x*y
#' x/y
#' x^2
#' }
#' 
#' @seealso \code{ \link{Constructor}, \link{memuse-class} }
#' @keywords Methods
#' @name Arithmetic
#' @rdname arithmetic
NULL

#' @rdname arithmetic
#' @export
setMethod("+", signature(e1="memuse", e2="memuse"),
  function(e1, e2) 
  {
    # if unit prefices disagree, use .PREFIX
    if (e1@unit.prefix != e2@unit.prefix){
      if (e1@unit.prefix != .PREFIX)
        e1 <- swap.prefix(e1)
      if (e2@unit.prefix != .PREFIX)
        e2 <- swap.prefix(e2)
    }
    
    # if names disagree, use .NAMES
    if (e1@unit.names != e2@unit.names){
      if (e1@unit.names != .NAMES)
        e1 <- swap.names(e1)
    }
    
    e1 <- convert_to_bytes(e1)
    e2 <- convert_to_bytes(e2)
    
    e1@size <- e1@size + e2@size
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



#' @rdname arithmetic
#' @export
setMethod("+", signature(e1="memuse", e2="numeric"),
  function(e1, e2) 
  {
    if (length(e2) != 1)
      stop("memuse + numeric : vector must be of length 1")
    
    e1 <- convert_to_bytes(e1)
    
    e1@size <- e1@size + e2
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



#' @rdname arithmetic
#' @export
setMethod("+", signature(e1="numeric", e2="memuse"),
  function(e1, e2)
  {
    if (length(e1) != 1)
      stop("numeric + memuse : vector must be of length 1")
    else
      return( e2+e1 )
  }
)



#' @rdname arithmetic
#' @export
setMethod("+", signature(e1="memuse", e2="object_size"),
  function(e1, e2) 
  {
    e1 <- convert_to_bytes(e1)
    
    e1@size <- e1@size + unclass(e2)
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



#' @rdname arithmetic
#' @export
setMethod("+", signature(e1="object_size", e2="memuse"),
  function(e1, e2)
    return( e2+e1 )
)



# -------------------------------------------------
# Subtraction
# -------------------------------------------------


#' @rdname arithmetic
#' @export
setMethod("-", signature(e1="memuse", e2="memuse"),
  function(e1, e2)
  {
    ret <- e1+(-1*e2)
    mu.nonneg(ret)
    
    return( ret )
  }
)



#' @rdname arithmetic
#' @export
setMethod("-", signature(e1="memuse", e2="numeric"),
  function(e1, e2)
  {
    if (length(e2) != 1)
      stop("memuse - numeric : vector must be of length 1")
    
    ret <- e1+(-1*e2)
    mu.nonneg(ret)
    
    return( ret )
  }
)



#' @rdname arithmetic
#' @export
setMethod("-", signature(e1="numeric", e2="memuse"),
  function(e1, e2)
  {
    if (length(e1) != 1)
      stop("vector - numeric : vector must be of length 1")
    
    ret <- e1+(-1*e2)
    mu.nonneg(ret)
    
    return( ret )
  }
)



#' @rdname arithmetic
#' @export
setMethod("-", signature(e1="memuse", e2="missing"),
  function(e1, e2)
    return( -1*e1 )
)



#' @rdname arithmetic
#' @export
setMethod("-", signature(e1="memuse", e2="object_size"),
  function(e1, e2) 
  {
    e1 <- convert_to_bytes(e1)
    
    e1@size <- e1@size - unclass(e2)
    
    ret <- swap.unit(e1, .UNIT)
    mu.nonneg(ret)
    
    return( ret )
  }
)



#' @rdname arithmetic
#' @export
setMethod("-", signature(e1="object_size", e2="memuse"),
  function(e1, e2) 
  {
    e2 <- convert_to_bytes(e2)
    
    e2@size <- unclass(e1) - e2@size
    
    ret <- swap.unit(e2, .UNIT)
    mu.nonneg(ret)
    
    return( ret )
  }
)


# -------------------------------------------------
# Multiplication
# -------------------------------------------------

#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="memuse", e2="memuse"),
  function(e1, e2) 
  {
    # if unit prefices disagree, use .PREFIX
    if (e1@unit.prefix != e2@unit.prefix){
      if (e1@unit.prefix != .PREFIX)
        e1 <- swap.prefix(e1)
      if (e2@unit.prefix != .PREFIX)
        e2 <- swap.prefix(e2)
    }
    
    # if names disagree, use .NAMES
    if (e1@unit.names != e2@unit.names){
      if (e1@unit.names != .NAMES)
        e1 <- swap.names(e1)
    }
    
    e1 <- convert_to_bytes(e1)
    e2 <- convert_to_bytes(e2)
    
    e1@size <- e1@size * e2@size
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="memuse", e2="numeric"),
  function(e1, e2) 
  {
#    if (length(e2) != 1)
#      stop("memuse * numeric : vector must be of length 1")
    
    e1 <- convert_to_bytes(e1)
    
    e1@size <- e1@size * e2
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="numeric", e2="memuse"),
  function(e1, e2)
  {
    if (length(e1) != 1)
      stop("numeric * memuse : vector must be of length 1")
    else
      return( e2*e1 )
  }
)



#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="memuse", e2="object_size"),
  function(e1, e2) 
  {
    e1 <- convert_to_bytes(e1)
    
    e1@size <- e1@size * unclass(e2)
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



#' @rdname arithmetic
#' @export
setMethod("*", signature(e1="object_size", e2="memuse"),
  function(e1, e2)
    return( e2*e1 )
)




# -------------------------------------------------
# Division
# -------------------------------------------------

#' @rdname arithmetic
#' @export
setMethod("/", signature(e1="memuse", e2="memuse"),
  function(e1, e2) 
  {
    # if unit prefices disagree, use .PREFIX
    if (e1@unit.prefix != e2@unit.prefix){
      if (e1@unit.prefix != .PREFIX)
        e1 <- swap.prefix(e1)
      if (e2@unit.prefix != .PREFIX)
        e2 <- swap.prefix(e2)
    }
    
    # if names disagree, use .NAMES
    if (e1@unit.names != e2@unit.names){
      if (e1@unit.names != .NAMES)
        e1 <- swap.names(e1)
    }
    
    e1 <- convert_to_bytes(e1)
    e2 <- convert_to_bytes(e2)
    
    e1@size <- e1@size / e2@size
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



#' @rdname arithmetic
#' @export
setMethod("/", signature(e1="memuse", e2="numeric"),
  function(e1, e2) 
  {
    if (length(e2) != 1)
      stop("memuse * numeric : vector must be of length 1")
    
    e1 <- convert_to_bytes(e1)
    
    e1@size <- e1@size / e2
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



#' @rdname arithmetic
#' @export
setMethod("/", signature(e1="numeric", e2="memuse"),
  function(e1, e2)
  {
    if (length(e1) != 1)
      stop("vector * numeric : vector must be of length 1")
    else
      return( e2/e1 )
  }
)



#' @rdname arithmetic
#' @export
setMethod("/", signature(e1="memuse", e2="object_size"),
  function(e1, e2) 
  {
    e1 <- convert_to_bytes(e1)
    
    e1@size <- e1@size / unclass(e2)
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



#' @rdname arithmetic
#' @export
setMethod("/", signature(e1="object_size", e2="memuse"),
  function(e1, e2) 
  {
    e2 <- convert_to_bytes(e2)
    
    e2@size <- unclass(e1) / e2@size
    
    ret <- swap.unit(e2, .UNIT)
    
    return( ret )
  }
)



# -------------------------------------------------
# Exponentiation
# -------------------------------------------------

#' @rdname arithmetic
#' @export
setMethod("^", signature(e1="memuse", e2="memuse"),
  function(e1, e2) 
  {
    # if unit prefices disagree, use .PREFIX
    if (e1@unit.prefix != e2@unit.prefix){
      if (e1@unit.prefix != .PREFIX)
        e1 <- swap.prefix(e1)
      if (e2@unit.prefix != .PREFIX)
        e2 <- swap.prefix(e2)
    }
    
    # if names disagree, use .NAMES
    if (e1@unit.names != e2@unit.names){
      if (e1@unit.names != .NAMES)
        e1 <- swap.names(e1)
    }
    
    e1 <- convert_to_bytes(e1)
    e2 <- convert_to_bytes(e2)
    
    e1@size <- e1@size ^ e2@size
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)



#' @rdname arithmetic
#' @export
setMethod("^", signature(e1="memuse", e2="numeric"),
  function(e1, e2) 
  {
    if (length(e2) != 1)
      stop("memuse ^ vector : vector must be of length 1")
    
    e1 <- convert_to_bytes(e1)
    
    e1@size <- e1@size ^ e2
    
    ret <- swap.unit(e1, .UNIT)
    
    return( ret )
  }
)

