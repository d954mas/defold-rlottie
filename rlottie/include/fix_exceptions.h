#pragma once
#if __cpp_exceptions
# define __try      try
# define __catch(X) catch(X)
# define __throw_exception_again throw
# define __throw throw
#else
# define __try      if (true)
# define __catch(X) if (false)
# define __throw
#endif