#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "star_llvm.h"
#include "star_dispatch.h"
#include "star_id.h"
#include "star.h"

void star_initLLVM(void) {
	star_registerType(
		Type_new(
			"LLVM.Int1",
			TypeID$LLVM$Int1,
			TypeStructure$Native,
			NULL,
			SelTable_newEmpty(),
			SelTable_newEmpty(),
			sizeof(LLVM$Int1),
			NULL,
			Value_deinit
		)
	);

	star_registerType(
		Type_new(
			"LLVM.Int8",
			TypeID$LLVM$Int8,
			TypeStructure$Native,
			NULL,
			SelTable_newEmpty(),
			SelTable_newEmpty(),
			sizeof(LLVM$Int8),
			NULL,
			Value_deinit
		)
	);

	star_registerType(
		Type_new(
			"LLVM.Int16",
			TypeID$LLVM$Int16,
			TypeStructure$Native,
			NULL,
			SelTable_newEmpty(),
			SelTable_newEmpty(),
			sizeof(LLVM$Int16),
			NULL,
			Value_deinit
		)
	);

	star_registerType(
		Type_new(
			"LLVM.Int32",
			TypeID$LLVM$Int32,
			TypeStructure$Native,
			NULL,
			SelTable_newEmpty(),
			SelTable_newEmpty(),
			sizeof(LLVM$Int32),
			NULL,
			Value_deinit
		)
	);

	star_registerType(
		Type_new(
			"LLVM.Int64",
			TypeID$LLVM$Int64,
			TypeStructure$Native,
			NULL,
			SelTable_newEmpty(),
			SelTable_newEmpty(),
			sizeof(LLVM$Int64),
			NULL,
			Value_deinit
		)
	);

	star_registerType(
		Type_new(
			"LLVM.UInt8",
			TypeID$LLVM$UInt8,
			TypeStructure$Native,
			NULL,
			SelTable_newEmpty(),
			SelTable_newEmpty(),
			sizeof(LLVM$UInt8),
			NULL,
			Value_deinit
		)
	);

	star_registerType(
		Type_new(
			"LLVM.UInt16",
			TypeID$LLVM$UInt16,
			TypeStructure$Native,
			NULL,
			SelTable_newEmpty(),
			SelTable_newEmpty(),
			sizeof(LLVM$UInt16),
			NULL,
			Value_deinit
		)
	);

	star_registerType(
		Type_new(
			"LLVM.UInt32",
			TypeID$LLVM$UInt32,
			TypeStructure$Native,
			NULL,
			SelTable_newEmpty(),
			SelTable_newEmpty(),
			sizeof(LLVM$UInt32),
			NULL,
			Value_deinit
		)
	);

	star_registerType(
		Type_new(
			"LLVM.UInt64",
			TypeID$LLVM$UInt64,
			TypeStructure$Native,
			NULL,
			SelTable_newEmpty(),
			SelTable_newEmpty(),
			sizeof(LLVM$UInt64),
			NULL,
			Value_deinit
		)
	);

	star_registerType(
		Type_new(
			"LLVM.Dec32",
			TypeID$LLVM$Dec32,
			TypeStructure$Native,
			NULL,
			SelTable_newEmpty(),
			SelTable_newEmpty(),
			sizeof(LLVM$Dec32),
			NULL,
			Value_deinit
		)
	);
	
	star_registerType(
		Type_new(
			"LLVM.Dec64",
			TypeID$LLVM$Dec64,
			TypeStructure$Native,
			NULL,
			SelTable_newEmpty(),
			SelTable_newEmpty(),
			sizeof(LLVM$Dec64),
			NULL,
			Value_deinit
		)
	);

	star_registerType(
		Type_new(
			"LLVM.Dec128",
			TypeID$LLVM$Dec128,
			TypeStructure$Native,
			NULL,
			SelTable_newEmpty(),
			SelTable_newEmpty(),
			sizeof(LLVM$Dec128),
			NULL,
			Value_deinit
		)
	);

	star_registerType(
		Type_new(
			"LLVM.Str",
			TypeID$LLVM$Str,
			TypeStructure$Native,
			NULL,
			SelTable_new(
				(Sel[]) {
					Sel_newMulti(
						(const char*[]) {"newWithLength"},
						(TypeID[])      {TypeID$LLVM$UInt64},
						1,
						TypeID$LLVM$Str
					)
				},
				(Method*[]) {
					Method_new((RawMethod) LLVM$Str__newWithLength_LLVM$UInt64)
				},
				1
			),
			SelTable_new(
				(Sel[]) {
					Sel_newSingle("length", TypeID$LLVM$UInt64),
					Sel_newMulti(
						(const char*[]) {"at"},
						(TypeID[])    {TypeID$LLVM$UInt64},
						1,
						TypeID$LLVM$UInt8
					),
					Sel_newMulti(
						(const char*[]) {"at", "set"},
						(TypeID[])    {TypeID$LLVM$UInt64, TypeID$LLVM$UInt8},
						2,
						TypeID$LLVM$UInt8
					),
					Sel_newSingle("free", TypeID$Void)
				},
				(Method*[]) {
					Method_new((RawMethod) LLVM$Str__length),
					Method_new((RawMethod) LLVM$Str__at_LLVM$UInt64),
					Method_new((RawMethod) LLVM$Str__at_LLVM$UInt64_set_LLVM$UInt8),
					Method_new((RawMethod) LLVM$Str__free)
				},
				4
			),
			sizeof(LLVM$Str),
			NULL,
			Value_deinit
		)
	);
}



#define INT_DEF(bits)\
	LLVM$Int##bits* LLVM$Int##bits##_wrap(int##bits##_t value) {\
		LLVM$Int##bits *out = malloc(sizeof(LLVM$Int##bits));\
		MD_PRELUDE(LLVM$Int##bits);\
		out->value = value;\
		return out;\
	}\
	\
	int##bits##_t LLVM$Int##bits##_unwrap(LLVM$Int##bits *this) {\
		return this->value;\
	}

#define UINT_DEF(bits)\
	LLVM$UInt##bits* LLVM$UInt##bits##_wrap(uint##bits##_t value) {\
		LLVM$UInt##bits *out = malloc(sizeof(LLVM$UInt##bits));\
		MD_PRELUDE(LLVM$UInt##bits);\
		out->value = value;\
		return out;\
	}\
	\
	uint##bits##_t LLVM$UInt##bits##_unwrap(LLVM$UInt##bits *this) {\
		return this->value;\
	}



// Method definitions:

/* LLVM$Int1 */
LLVM$Int1* LLVM$Int1_wrap(bool value) {
	LLVM$Int1 *out = malloc(sizeof(LLVM$Int1));
	MD_PRELUDE(LLVM$Int1);

	out->value = value;

	return out;
}

bool LLVM$Int1_unwrap(LLVM$Int1 *this) {
	return this->value;
}


/* LLVM$Int8 */
INT_DEF(8)


/* LLVM$Int16 */
INT_DEF(16)


/* LLVM$Int32 */
INT_DEF(32)


/* LLVM$Int64 */
INT_DEF(64)


/* LLVM$UInt8 */
UINT_DEF(8)


/* LLVM$UInt16 */
UINT_DEF(16)


/* LLVM$UInt32 */
UINT_DEF(32)


/* LLVM$UInt64 */
UINT_DEF(64)


/* LLVM$Dec32 */
LLVM$Dec32* LLVM$Dec32_wrap(float value) {
	LLVM$Dec32 *out = malloc(sizeof(LLVM$Dec32));
	MD_PRELUDE(LLVM$Dec32);

	out->value = value;

	return out;
}

float LLVM$Dec32_unwrap(LLVM$Dec32 *this) {
	return this->value;
}


/* LLVM$Dec64 */
LLVM$Dec64* LLVM$Dec64_wrap(double value) {
	LLVM$Dec64 *out = malloc(sizeof(LLVM$Dec64));
	MD_PRELUDE(LLVM$Dec64);

	out->value = value;

	return out;
}

double LLVM$Dec64_unwrap(LLVM$Dec64 *this) {
	return this->value;
}

/* LLVM$Dec128 */
LLVM$Dec128* LLVM$Dec128_wrap(long double value) {
	LLVM$Dec128 *out = malloc(sizeof(LLVM$Dec128));
	MD_PRELUDE(LLVM$Dec128);

	out->value = value;

	return out;
}

long double LLVM$Dec128_unwrap(LLVM$Dec128 *this) {
	return this->value;
}


/* LLVM$Str */
LLVM$Str* LLVM$Str_wrap(char* str) {
	LLVM$Str *out = malloc(sizeof(LLVM$Str));
	MD_PRELUDE(LLVM$Str);

	out->value = str;

	return out;
}

char* LLVM$Str_unwrap(LLVM$Str *this) {
	return this->value;
}

// static
Value* /*(LLVM$Str*)*/ LLVM$Str__newWithLength_LLVM$UInt64(Value *_this /*(LLVM$Str*)*/, Value *_length /*(LLVM$UInt64*)*/) {
	LLVM$UInt64 *length = (LLVM$UInt64*) _length;

	LLVM$Str *out = malloc(sizeof(LLVM$Str));
	MD_PRELUDE(LLVM$Str);

	out->value = calloc(length->value, sizeof(char));

	return (Value*) out;
}

// instance
Value* /*(LLVM$UInt64*)*/ LLVM$Str__length(Value *_this /*(LLVM$Str*)*/) {
	LLVM$Str *this = (LLVM$Str*) _this;

	return (Value*) LLVM$UInt64_wrap(strlen(this->value));
}

Value* /*(LLVM$UInt8*)*/ LLVM$Str__at_LLVM$UInt64(Value *_this /*(LLVM$Str*)*/, Value *_index /*(LLVM$UInt64*)*/) {
	LLVM$Str *this = (LLVM$Str*) _this;
	LLVM$UInt64 *index = (LLVM$UInt64*) _index;

	if(LLVM$UInt64_unwrap(index) > strlen(this->value)) {
		perror("Error: Index out of range!");
		exit(1);
	} else {
		return (Value*) LLVM$UInt8_wrap(this->value[LLVM$UInt64_unwrap(index)]);
	}
}

Value* /*(LLVM$UInt8*)*/ LLVM$Str__at_LLVM$UInt64_set_LLVM$UInt8(Value *_this /*(LLVM$Str*)*/, Value *_index /*(LLVM$UInt64*)*/, Value *_value /*(LLVM$UInt8*)*/) {
	LLVM$Str *this = (LLVM$Str*) _this;
	LLVM$UInt64 *index = (LLVM$UInt64*) _index;
	LLVM$UInt8 *value = (LLVM$UInt8*) _value;

	if(LLVM$UInt64_unwrap(index) > strlen(this->value)) {
		perror("Error: Index out of range!");
		exit(1);
	} else {
		return (Value*) LLVM$UInt8_wrap(this->value[LLVM$UInt64_unwrap(index)] = LLVM$UInt8_unwrap(value));
	}
}

void LLVM$Str__free(Value *_this /*(LLVM$Str*)*/) {
	LLVM$Str *this = (LLVM$Str*) _this;

	free(this->value);
}



#undef INT_DEF
#undef UINT_DEF