#pragma once

#include "star.h"

#ifdef __cplusplus
extern "C" {
#endif

/* dispatch */
typedef star::RawMethod  star_RawMethod;
typedef star::TypeID     star_TypeID;
typedef star::CategoryID star_CategoryID;

enum star_Structure {
	star_Structure_Class,
	star_Structure_Protocol,
	star_Structure_Kind,
	star_Structure_Native
};

enum star_MethodAttr {
	star_MethodAttr_Init      = 1 << 1,
	star_MethodAttr_NoInherit = 1 << 3,
	star_MethodAttr_Unordered = 1 << 5
};

typedef void* star_Method;
typedef void* star_Sel;
typedef void* star_SelTable;
typedef void* star_Type;
typedef void* star_Category;
typedef void* star_MD;
typedef void* star_Value;

star_Method star_Method_new(star_RawMethod);
star_Method star_Method_newWithAttrs(star_RawMethod, star_MethodAttr);
void        star_Method_cleanup(star_Method);
star_Value  star_Method_call(star_Method, star_Value*, star_Value*, size_t, bool);

star_Sel star_Sel_newSingle(const char*, star_TypeID);
star_Sel star_Sel_newMulti(const char**, star_TypeID*, size_t, star_TypeID);
star_Sel star_Sel_newCast(star_TypeID);
size_t   star_Sel_getArity(star_Sel);
char*    star_Sel_format(star_Sel);

star_SelTable star_SelTable_new(star_Sel*, star_Method*, size_t);
star_SelTable star_SelTable_newEmpty();
void          star_SelTable_cleanup(star_SelTable);
size_t*       star_SelTable_allWithArity(star_SelTable, size_t, size_t*);
star_Method   star_SelTable_getWithSelector(star_SelTable, star_Sel);

star_Type    star_Type_new(const char*, star_TypeID, star_Structure, star_Type*, size_t, star_SelTable, star_SelTable, size_t, star_Value (*)(), void (*)(star_Value));
star_Type    star_Type_fromName(const char*);
star_Type    star_Type_fromID(star_TypeID);
star_TypeID  star_Type_newID();
void         star_Type_cleanup(star_Type);
star_Value   star_Type_initDefault(star_Type);
bool         star_Type_equals(star_Type, star_Type);
bool         star_Type_inherits(star_Type, star_Type);
bool         star_Type_hasParents(star_Type);
bool         star_Type_hasParentsBesidesValue(star_Type);
bool         star_Type_canInherit(star_Type);
star_Method  star_Type_getStaticMethodWithSelector(star_Type, star_Sel);
star_Method  star_Type_getInstanceMethodWithSelector(star_Type, star_Sel);
star_Value   star_Type_dispatch(star_Type, star_Sel, star_Value*);
void         star_Type_addCategory(star_Type, star_Category);
bool         star_Type_inCategory(star_Type, star_Category);

star_Category   star_Category_new(const char*, star_CategoryID);
star_CategoryID star_Category_newID();
void            star_Category_cleanup(star_Category);
void            star_Category_addType(star_Category, star_Type, star_SelTable, star_SelTable);
star_Method     star_Category_getStaticMethodForTypeWithSelector(star_Category, star_Type, star_Sel);
star_Method     star_Category_getInstanceMethodForTypeWithSelector(star_Category, star_Type, star_Sel);

star_Value star_Value_init();
void       star_Value_deinit(star_Value);
void       star_Value_deinitDefault(star_Value);
void       star_Value_retain(star_Value);
void       star_Value_release(star_Value);
bool       star_Value_isA(star_Value, star_Type);
star_Type  star_Value_typeOf(star_Value);
star_Type  star_Value_actualTypeOf(star_Value);
star_Value star_Value_castTo(star_Value, star_Type);
star_Value star_Value_dispatch(star_Value, star_Sel, star_Value*);


/* star */
void star_init();
void star_deinit();

size_t star_getNumTypes();
star_Type* star_getTypes();
void star_registerType(star_Type);

size_t star_getNumCategories();
star_Category* star_getCategories();
void star_registerCategory(star_Category);

star_Type star_getValueType();
star_Type star_getVoidType();


/* llvm */
void star_llvm_init();

#define STAR_LLVM_WRAP(type, base)\
	star_Value star_llvm_##type##_wrap(base);\
	base        star_llvm_##type##_unwrap(star_Value);

STAR_LLVM_WRAP(Int1,   bool)
STAR_LLVM_WRAP(Int8,   int8_t)
STAR_LLVM_WRAP(Int16,  int16_t)
STAR_LLVM_WRAP(Int32,  int32_t)
STAR_LLVM_WRAP(Int64,  int64_t)
STAR_LLVM_WRAP(UInt8,  uint8_t)
STAR_LLVM_WRAP(UInt16, uint16_t)
STAR_LLVM_WRAP(UInt32, uint32_t)
STAR_LLVM_WRAP(UInt64, uint64_t)
STAR_LLVM_WRAP(Dec32,  float)
STAR_LLVM_WRAP(Dec64,  double)
STAR_LLVM_WRAP(Dec128, long double)
STAR_LLVM_WRAP(Str,    char*)
STAR_LLVM_WRAP(Opaque, void*)

#undef STAR_LLVM_WRAP

#ifdef __cplusplus
}
#endif