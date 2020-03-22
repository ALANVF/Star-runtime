#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>

#include "star_llvm.h"
#include "star_dispatch.h"
#include "star_id.h"
#include "star.h"

void star_initLLVM(void) {
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
}



// Method definitions:

/* LLVM$Int8 */
LLVM$Int8* LLVM$Int8_wrap(int8_t value) {
	LLVM$Int8 *out = malloc(sizeof(LLVM$Int8));
	MD_PRELUDE(LLVM$Int8);

	out->value = value;

	return out;
}

int8_t LLVM$Int8_unwrap(LLVM$Int8 *this) {
	return this->value;
}


/* LLVM$Int16 */
LLVM$Int16* LLVM$Int16_wrap(int16_t value) {
	LLVM$Int16 *out = malloc(sizeof(LLVM$Int16));
	MD_PRELUDE(LLVM$Int16);

	out->value = value;

	return out;
}

int16_t LLVM$Int16_unwrap(LLVM$Int16 *this) {
	return this->value;
}


/* LLVM$Int32 */
LLVM$Int32* LLVM$Int32_wrap(int32_t value) {
	LLVM$Int32 *out = malloc(sizeof(LLVM$Int32));
	MD_PRELUDE(LLVM$Int32);

	out->value = value;

	return out;
}

int32_t LLVM$Int32_unwrap(LLVM$Int32 *this) {
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