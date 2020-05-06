#include "star_llvm.h"

namespace star {

#define ADD_NATIVE(type)\
	registerType(\
		new Type(\
			"Star.LLVM." #type,\
			type::id,\
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
	template<> TypeID Int1::id = 0;
	template<> TypeID Int8::id = 0;
	template<> TypeID Int16::id = 0;
	template<> TypeID Int32::id = 0;
	template<> TypeID Int64::id = 0;
	template<> TypeID UInt8::id = 0;
	template<> TypeID UInt16::id = 0;
	template<> TypeID UInt32::id = 0;
	template<> TypeID UInt64::id = 0;
	template<> TypeID Dec32::id = 0;
	template<> TypeID Dec64::id = 0;
	template<> TypeID Dec128::id = 0;
	template<> TypeID Str::id = 0;
	template<> TypeID Opaque::id = 0;

	void init() {
		Int1::id = Type::newID();
		Int8::id = Type::newID();
		Int16::id = Type::newID();
		Int32::id = Type::newID();
		Int64::id = Type::newID();
		UInt8::id = Type::newID();
		UInt16::id = Type::newID();
		UInt32::id = Type::newID();
		UInt64::id = Type::newID();
		Dec32::id = Type::newID();
		Dec64::id = Type::newID();
		Dec128::id = Type::newID();
		Str::id = Type::newID();
		Opaque::id = Type::newID();

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