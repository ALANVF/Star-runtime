#pragma once

#include <stdint.h>

#include "star_dispatch.h"

typedef struct LLVM$Int8 {
	MD md;
	int8_t value;
} LLVM$Int8;

typedef struct LLVM$Int16 {
	MD md;
	int16_t value;
} LLVM$Int16;

typedef struct LLVM$Int32 {
	MD md;
	int32_t value;
} LLVM$Int32;

typedef struct LLVM$Dec64 {
	MD md;
	double value;
} LLVM$Dec64;



// Method prototypes:

/* LLVM$Int8 */
LLVM$Int8* LLVM$Int8_wrap(int8_t);
int8_t LLVM$Int8_unwrap(LLVM$Int8*);


/* LLVM$Int16 */
LLVM$Int16* LLVM$Int16_wrap(int16_t);
int16_t LLVM$Int16_unwrap(LLVM$Int16*);


/* LLVM$Int32 */
LLVM$Int32* LLVM$Int32_wrap(int32_t);
int32_t LLVM$Int32_unwrap(LLVM$Int32*);


/* LLVM$Dec64 */
LLVM$Dec64* LLVM$Dec64_wrap(double);
double LLVM$Dec64_unwrap(LLVM$Dec64*);