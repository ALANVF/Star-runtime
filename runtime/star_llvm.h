#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "star_dispatch.h"

typedef struct LLVM$Int1 {
	MD md;
	bool value;
} LLVM$Int1;

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

typedef struct LLVM$Int64 {
	MD md;
	int64_t value;
} LLVM$Int64;


typedef struct LLVM$UInt8 {
	MD md;
	uint8_t value;
} LLVM$UInt8;

typedef struct LLVM$UInt16 {
	MD md;
	uint16_t value;
} LLVM$UInt16;

typedef struct LLVM$UInt32 {
	MD md;
	uint32_t value;
} LLVM$UInt32;

typedef struct LLVM$UInt64 {
	MD md;
	uint64_t value;
} LLVM$UInt64;


typedef struct LLVM$Dec32 {
	MD md;
	float value;
} LLVM$Dec32;

typedef struct LLVM$Dec64 {
	MD md;
	double value;
} LLVM$Dec64;

typedef struct LLVM$Dec128 {
	MD md;
	long double value;
} LLVM$Dec128;



// Method prototypes:

/* LLVM$Int1 */
LLVM$Int1* LLVM$Int1_wrap(bool);
bool LLVM$Int1_unwrap(LLVM$Int1*);

/* LLVM$Int8 */
LLVM$Int8* LLVM$Int8_wrap(int8_t);
int8_t LLVM$Int8_unwrap(LLVM$Int8*);


/* LLVM$Int16 */
LLVM$Int16* LLVM$Int16_wrap(int16_t);
int16_t LLVM$Int16_unwrap(LLVM$Int16*);


/* LLVM$Int32 */
LLVM$Int32* LLVM$Int32_wrap(int32_t);
int32_t LLVM$Int32_unwrap(LLVM$Int32*);


/* LLVM$Int64 */
LLVM$Int64* LLVM$Int64_wrap(int64_t);
int64_t LLVM$Int64_unwrap(LLVM$Int64*);


/* LLVM$UInt8 */
LLVM$UInt8* LLVM$UInt8_wrap(uint8_t);
uint8_t LLVM$UInt8_unwrap(LLVM$UInt8*);


/* LLVM$UInt16 */
LLVM$UInt16* LLVM$UInt16_wrap(uint16_t);
uint16_t LLVM$UInt16_unwrap(LLVM$UInt16*);


/* LLVM$UInt32 */
LLVM$UInt32* LLVM$UInt32_wrap(uint32_t);
uint32_t LLVM$UInt32_unwrap(LLVM$UInt32*);


/* LLVM$UInt64 */
LLVM$UInt64* LLVM$UInt64_wrap(uint64_t);
uint64_t LLVM$UInt64_unwrap(LLVM$UInt64*);


/* LLVM$Dec32 */
LLVM$Dec32* LLVM$Dec32_wrap(float);
float LLVM$Dec32_unwrap(LLVM$Dec32*);


/* LLVM$Dec64 */
LLVM$Dec64* LLVM$Dec64_wrap(double);
double LLVM$Dec64_unwrap(LLVM$Dec64*);


/* LLVM$Dec128 */
LLVM$Dec128* LLVM$Dec128_wrap(long double);
long double LLVM$Dec128_unwrap(LLVM$Dec128*);