#pragma once

#include "star.h"

namespace star {

namespace llvm {
	template<typename Repr, typename = std::enable_if_t<std::negation_v<std::is_void<Repr>>>>
	class Native: public Value {
	public:
		static TypeID id;

		Repr repr;

		Native(Repr repr): repr(repr) {
			this->md = new MD(id);
		}

		template<typename T>
		operator Native<T>() {
			return Native(reinterpret_cast<T>(this->repr));
		}

		~Native() {}
	};
	
	using Int1 = Native<bool>;
	using Int8 = Native<int8_t>;
	using Int16 = Native<int16_t>;
	using Int32 = Native<int32_t>;
	using Int64 = Native<int64_t>;
	using UInt8 = Native<uint8_t>;
	using UInt16 = Native<uint16_t>;
	using UInt32 = Native<uint32_t>;
	using UInt64 = Native<uint64_t>;
	using Dec32 = Native<float>;
	using Dec64 = Native<double>;
	using Dec128 = Native<long double>;
	using Str = Native<char*>;
	using Opaque = Native<void*>;

	void init();
}

}