#include "star_llvm.h"

namespace star {

#define ADD_NATIVE(type)\
	registerType(\
		new Type(\
			"Star.LLVM." #type,\
			Type::newID(),\
			Structure::Native,\
			{},\
			new SelTable(),\
			new SelTable(),\
			sizeof(type),\
			nullptr,\
			nullptr\
		)\
	)

namespace llvm {
	template<> TypeID Int1::id = 2;
	template<> TypeID Int8::id = 3;
	template<> TypeID Int16::id = 4;
	template<> TypeID Int32::id = 5;
	template<> TypeID Int64::id = 6;
	template<> TypeID UInt8::id = 7;
	template<> TypeID UInt16::id = 8;
	template<> TypeID UInt32::id = 9;
	template<> TypeID UInt64::id = 10;
	template<> TypeID Dec32::id = 11;
	template<> TypeID Dec64::id = 12;
	template<> TypeID Dec128::id = 13;
	template<> TypeID Str::id = 14;
	template<> TypeID Opaque::id = 15;

	void init() {
		ADD_NATIVE(Int1);
		ADD_NATIVE(Int8);
		ADD_NATIVE(Int16);
		ADD_NATIVE(Int32);
		ADD_NATIVE(Int64);
		ADD_NATIVE(UInt8);
		ADD_NATIVE(UInt16);
		ADD_NATIVE(UInt32);
		ADD_NATIVE(UInt64);
		ADD_NATIVE(Dec32);
		ADD_NATIVE(Dec64);
		ADD_NATIVE(Dec128);

		// do Str and Opaque

		/*registerType(
			new Type(
				"Star.LLVM.Int1",
				Type::newID(),
				Structure::Native,
				{},
				new SelTable(),
				new SelTable(),
				sizeof(Int1),
				nullptr,
				nullptr
			)
		);*/
	}

#undef ADD_NATIVE
}

}