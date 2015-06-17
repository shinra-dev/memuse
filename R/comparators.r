#' Comparators
#' 
#' Binary comparators for \code{memuse} objects.
#' 
#' Comparisons to numeric values are done at the byte level.
#' 
#' @param e1,e2
#' \code{memuse}, \code{numeric}, or \code{object_size} objects.
#' 
#' @return Returns a \code{memuse} class object.
#' 
#' @examples
#' \dontrun{
#' x <- mu(2000)
#' y <- mu(3000)
#' 
#' x < y
#' x <= y
#' x > y
#' x >= y
#' x == y
#' x != y
#' }
#' 
#' @seealso \code{ \link{Constructor}, \link{memuse-class} }
#' @keywords Methods
#' @name Comparators
#' @rdname comparators
NULL



# --------------------------------------------------------
# mu-mu
# --------------------------------------------------------

#' @rdname comparators
#' @export
setMethod("==", signature(e1="memuse", e2="memuse"),
  function(e1, e2) 
  {
    # if unit prefices disagree, use .PREFIX
    if (e1@unit.prefix != e2@unit.prefix)
    {
      if (e1@unit.prefix != .PREFIX)
        e1 <- swap.prefix(e1)
      if (e2@unit.prefix != .PREFIX)
        e2 <- swap.prefix(e2)
    }
    
    # if names disagree, use .NAMES
    if (e1@unit.names != e2@unit.names)
    {
      if (e1@unit.names != .NAMES)
        e1 <- swap.names(e1)
    }
    
    e1 <- convert_to_bytes(e1)
    e2 <- convert_to_bytes(e2)
    
    ret <- e1@size == e2@size
    
    return( ret )
  }
)

#' @rdname comparators
#' @export
setMethod("<", signature(e1="memuse", e2="memuse"),
  function(e1, e2) 
  {
    # if unit prefices disagree, use .PREFIX
    if (e1@unit.prefix != e2@unit.prefix)
    {
      if (e1@unit.prefix != .PREFIX)
        e1 <- swap.prefix(e1)
      if (e2@unit.prefix != .PREFIX)
        e2 <- swap.prefix(e2)
    }
    
    # if names disagree, use .NAMES
    if (e1@unit.names != e2@unit.names)
    {
      if (e1@unit.names != .NAMES)
        e1 <- swap.names(e1)
    }
    
    e1 <- convert_to_bytes(e1)
    e2 <- convert_to_bytes(e2)
    
    ret <- e1@size < e2@size
    
    return( ret )
  }
)

#' @rdname comparators
#' @export
setMethod("<=", signature(e1="memuse", e2="memuse"),
  function(e1, e2) 
  {
    e1 < e2 || e1 == e2
  }
)

#' @rdname comparators
#' @export
setMethod(">", signature(e1="memuse", e2="memuse"),
  function(e1, e2) 
  {
    e2 < e1
  }
)

#' @rdname comparators
#' @export
setMethod(">=", signature(e1="memuse", e2="memuse"),
  function(e1, e2) 
  {
    e2 < e1 || e1 == e2
  }
)

#' @rdname comparators
#' @export
setMethod("!=", signature(e1="memuse", e2="memuse"),
  function(e1, e2) 
  {
    !(e1 == e2)
  }
)


# --------------------------------------------------------
# mu-numeric
# --------------------------------------------------------

#' @rdname comparators
#' @export
setMethod("==", signature(e1="memuse", e2="numeric"),
  function(e1, e2) 
  {
    e1 <- convert_to_bytes(e1)
    
    ret <- e1@size == e2
    
    return( ret )
  }
)

#' @rdname comparators
#' @export
setMethod("<", signature(e1="memuse", e2="numeric"),
  function(e1, e2) 
  {
    e1 <- convert_to_bytes(e1)
    
    ret <- e1@size < e2
    
    return( ret )
  }
)

#' @rdname comparators
#' @export
setMethod("<=", signature(e1="memuse", e2="numeric"),
  function(e1, e2) 
  {
    e1 < e2 || e1 == e2
  }
)

#' @rdname comparators
#' @export
setMethod(">", signature(e1="memuse", e2="numeric"),
  function(e1, e2) 
  {
    e2 < e1
  }
)

#' @rdname comparators
#' @export
setMethod(">=", signature(e1="memuse", e2="numeric"),
  function(e1, e2) 
  {
    e2 < e1 || e1 == e2
  }
)

#' @rdname comparators
#' @export
setMethod("!=", signature(e1="memuse", e2="numeric"),
  function(e1, e2) 
  {
    !(e1 == e2)
  }
)



# --------------------------------------------------------
# numeric-mu
# --------------------------------------------------------

#' @rdname comparators
#' @export
setMethod("==", signature(e1="numeric", e2="memuse"),
  function(e1, e2) 
  {
    e2 <- convert_to_bytes(e2)
    
    ret <- e1 == e2@size
    
    return( ret )
  }
)

#' @rdname comparators
#' @export
setMethod("<", signature(e1="numeric", e2="memuse"),
  function(e1, e2) 
  {
    e2 <- convert_to_bytes(e2)
    
    ret <- e1 < e2@size
    
    return( ret )
  }
)

#' @rdname comparators
#' @export
setMethod("<=", signature(e1="numeric", e2="memuse"),
  function(e1, e2) 
  {
    e1 < e2 || e1 == e2
  }
)

#' @rdname comparators
#' @export
setMethod(">", signature(e1="numeric", e2="memuse"),
  function(e1, e2) 
  {
    e2 < e1
  }
)

#' @rdname comparators
#' @export
setMethod(">=", signature(e1="numeric", e2="memuse"),
  function(e1, e2) 
  {
    e2 < e1 || e1 == e2
  }
)

#' @rdname comparators
#' @export
setMethod("!=", signature(e1="numeric", e2="memuse"),
  function(e1, e2) 
  {
    !(e1 == e2)
  }
)


