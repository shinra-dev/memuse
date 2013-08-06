setMethod("howmany.par", signature(x="memuse"),
  function(x, nrow, ncol, out.type="full", cores=1, par="row", ..., type="double", intsize=4, ICTXT=0, bldim=c(4, 4))
  {
    out.type <- match.arg(arg=tolower(out.type), choices=c("full", "approximate"))
    
    # global
    dim <- howmany(x=x, nrow=nrow, out.type="full", type=type, intsize=intsize)
    
    # local
    par <- match.arg(tolower(par), c("row", "column", "dmat"))
    if (par == "row") {
      ldim <- c(floor(dim[1L]/cores), dim[2L])
    }
    else if (par == "column"){
      ldim <- c(dim[1L], floor(dim[2L]/cores))
    }
    else if (par == "dmat") {
      ldim <- numroc(nprocs=cores, dim=dim, bldim=bldim, ICTXT=ICTXT)
    }
    
    # re-cast return as neededS
    if (out.type == "approximate"){
      dim <- approx_size(dim)
      ldim <- approx_size(ldim)
    }
    
    out <- list(global=dim, local=ldim)
    
    return( out )
  }
)

