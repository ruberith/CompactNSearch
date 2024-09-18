#pragma once

namespace CompactNSearch
{
#ifdef USE_DOUBLE
	using Real = double;
#else
	using Real = float;
#endif
}

#define INITIAL_NUMBER_OF_INDICES   50
#define INITIAL_NUMBER_OF_NEIGHBORS 50

#ifdef _MSC_VER
	#include <ppl.h>
#elif defined(__APPLE__) && defined(__clang__)
	#include <dispatch/dispatch.h>
	#include <iterator>

	namespace dispatch
	{
		template <typename _Iterator, typename _Function>
		void parallel_for_each(_Iterator first, _Iterator last, const _Function& _Func)
		{
			dispatch_apply(
				std::distance(first, last),
				DISPATCH_APPLY_AUTO,
				^(size_t i) {
					_Func(*std::next(first, i));
				}
			);
		}
	}
#else
	#include <parallel/algorithm>
#endif
