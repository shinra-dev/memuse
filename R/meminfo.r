val_or_zero <- function(x)
{
  if (is.null(x))
    return(0)
  else
    return(x)
}



meminfo_retvals <- function(retval)
{
  if (length(retval) > 1)
    return(sapply(retval, meminfo_retvals))
  
  .Call(R_meminfo_retvals, as.integer(retval))
}



Sys.meminfo <- function(compact.free=TRUE)
{
  out <- .Call(R_meminfo_raminfo)
  
  if (any(unlist(out) == -1))
    stop("There were errors accessing hardware info")
  
  if (all(unlist(out) == -10))
    stop("platform not supported at this time")
  
  tmp <- -which(out == -10)
  if (length(tmp) > 0)
    out <- out[tmp]
  
  ret <- lapply(out, mu)
  
  
  
  if (compact.free)
  {
    ret$freeram <- val_or_zero(ret$freeram) + val_or_zero(ret$bufferram) + val_or_zero(ret$cachedram)
    ret$bufferram <- ret$cachedram <- NULL
  }
  
  class(ret) <- "sysinfo"
  
  return( ret )
}



Sys.swapinfo <- function()
{
  out <- .Call(R_meminfo_swapinfo)
  
  if (any(unlist(out) == -1))
    stop("There were errors accessing hardware info")
  
  if (all(unlist(out) == -10))
    stop("platform not supported at this time")
  
  tmp <- -which(out == -10)
  if (length(tmp) > 0)
    out <- out[tmp]
  
  ret <- lapply(out, mu)
  class(ret) <- "sysinfo"
  
  return( ret )
}


Sys.pageinfo <- Sys.swapinfo



# ---------------------------------------------------------
# Current R process memory usage
# ---------------------------------------------------------


Sys.procmem <- function(gcFirst=TRUE)
{
  if (gcFirst)
    gc(FALSE)
  
  out <- .Call(R_meminfo_procinfo)
  
  if (any(unlist(out) == -1))
    stop("There were errors accessing process info")
  
  if (all(unlist(out) == -10))
    stop("platform not supported at this time")
  
  tmp <- -which(out == -10)
  if (length(tmp) > 0)
    out <- out[tmp]
  
  ret <- lapply(out, mu)
  
  class(ret) <- "sysinfo"
  
  return( ret )
}



# ---------------------------------------------------------
# Cache sizes
# ---------------------------------------------------------

getcache <- function(level) .Call(R_meminfo_cacheinfo_size, level)

Sys.cachesize <- function()
{
  levels <- 0L:3L
  
  ret <- sapply(levels, getcache)
  
  names(ret) <- c("L1I", "L1D", "L2", "L3")
  
  if (all(ret < 0))
    stop("platform not supported at this time")
  else if (any(ret < 0))
    ret <- ret[which(ret > 0)]
  
  ret <- sapply(ret, mu)
  
  class(ret) <- "sysinfo"
  
  return( ret )
}



Sys.cachelinesize <- function()
{
  ret <- .Call(R_meminfo_cacheinfo_linesize)
  
  
  if (ret < 0)
    stop("platform not supported at this time")
  
  ret <- list(Linesize=mu(ret))
  
  class(ret) <- "sysinfo"
  
  return( ret )
}



# ---------------------------------------------------------
# File sizes
# ---------------------------------------------------------

Sys.filesize <- function(filename)
{
  filename <- tools::file_path_as_absolute(filename)
  ret <- .Call(R_meminfo_filesize, filename)
  
  ret <- mu(ret)
  
  return( ret )
}



# ---------------------------------------------------------
# Uptimes
# ---------------------------------------------------------

Sys.uptime <- function()
{
  ret <- .Call(R_meminfo_system_uptime)
  
  if (ret < 0)
    stop("platform not supported at this time")
  
  ret <- readable.time(ret)
  
  return( ret )
}



Sys.utiltime <- function()
{
  ret <- .Call(R_meminfo_process_utiltime)
  
  if (any(ret < 0))
    stop("platform not supported at this time")
  
  ret <- lapply(ret, function(i) capture.output(print(readable.time(i))))
  names(ret) <- c("usr", "sys")
  class(ret) <- "sysinfo"
  
  return( ret )
}



Sys.runtime <- function()
{
  ret <- .Call(R_meminfo_process_runtime)
  
  if (ret < 0)
    stop("platform not supported at this time")
  
  ret <- readable.time(ret)
  
  return( ret )
}



post.system.time <- function()
{
  usrsys <- .Call(R_meminfo_process_utiltime)
  if (any(usrsys < 0))
    stop("platform not supported at this time")
  
  elapsed <- .Call(R_meminfo_process_runtime)
  if (elapsed < 0)
    stop("platform not supported at this time")
  
  ret <- c(usrsys, elapsed)
  names(ret) <- c("user.self", "sys.self", "elapsed")
  class(ret) <- "proc_time"
  
  return(ret)
}



# ---------------------------------------------------------
# Print handling
# ---------------------------------------------------------

title_case <- function(x) gsub(x, pattern="(^|[[:space:]])([[:alpha:]])", replacement="\\1\\U\\2", perl=TRUE)


### So ugly it's beautiful
print.sysinfo <- function(x)
{
  maxlen <- max(sapply(names(x), nchar))
  names <- gsub(names(x), pattern="_", replacement=" ")
  names <- title_case(x=names)
  spacenames <- simplify2array(lapply(names, function(str) paste0(str, ":", paste0(rep(" ", maxlen-nchar(str)), collapse=""))))
  
  maxlen <- max(sapply(x, function(y) nchar(paste(y))))
  prespaces <- simplify2array(lapply(x, function(y) paste0(rep(" ", maxlen-nchar(paste(y))), collapse="")))
  
  lapply(1:length(x), function(i) cat(paste(spacenames[i], prespaces[i], x[[i]], sep=" ", collapse="\n"), "\n"))
#  cat("\n")
  
  invisible()
}



"[.sysinfo" <- function(x, i)
{
  class(x) <- NULL
  ret <- x[i]
  if (length(ret) > 0)
    class(ret) <- "sysinfo"
  else
    return(numeric(0))
  
  return(ret)
}

