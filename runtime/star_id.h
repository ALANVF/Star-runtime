#pragma once

enum {
	TypeID$Value,
	TypeID$Void,



	TypeID$LLVM$Int1,
	TypeID$LLVM$Int8,
	TypeID$LLVM$Int16,
	TypeID$LLVM$Int32,
	TypeID$LLVM$Int64,
	TypeID$LLVM$Int128,

	TypeID$LLVM$UInt8,
	TypeID$LLVM$UInt16,
	TypeID$LLVM$UInt32,
	TypeID$LLVM$UInt64,
	TypeID$LLVM$UInt128,

	TypeID$LLVM$Dec16,
	TypeID$LLVM$Dec32,
	TypeID$LLVM$Dec64,
	TypeID$LLVM$Dec128,

	TypeID$LLVM$Ptr,
	TypeID$LLVM$Array,

	TypeID$LLVM$Struct,
	TypeID$LLVM$PackedStruct,

	TypeID$LLVM$Func
};