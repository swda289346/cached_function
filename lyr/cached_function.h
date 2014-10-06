#include <map>
#include <tuple>
#include <functional>

namespace lyr
{
	template<class R, class... Args> class cached_function
	{
		private:
			std::map<std::tuple<Args...>, R> cache;
			std::function<R(cached_function &, Args...)> function;
			
		public:
			cached_function(std::function<R(cached_function &, Args...)> &function) : function(function)
			{
				
			}
			
			cached_function(R(*function)(cached_function &, Args...))
			{
				this->function = function;
			}
			
			R operator()(Args... args)
			{
				typename std::map<std::tuple<Args...>, R>::iterator i = cache.find(std::make_tuple(args...));
				if (i!=cache.end())
					return i->second;
				return cache[std::make_tuple(args...)] = function(*this, args...);
			}
	};
}

