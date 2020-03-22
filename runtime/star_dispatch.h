#pragma once

#include <stdbool.h>

// Type prototypes:

typedef struct Type Type;
typedef struct Value Value;
typedef struct Category Category;



// Type definitions:

typedef void (*Method)(Value*);
typedef size_t TypeID;
typedef size_t CategoryID;

typedef enum {
	TypeStructure$Class,
	TypeStructure$Protocol,
	TypeStructure$Kind,
	TypeStructure$Native
} TypeStructure;

typedef enum {
	SelType$Single,
	SelType$Multi,
	SelType$Cast
} SelType;

typedef struct Sel {
	SelType type;
	union {
		struct {
			const char* label;
		} single;
		
		struct {
			const char** labels;
			TypeID* types;
			size_t arity;
		} multi;
		
		struct {
			TypeID type;
		} cast;
	};
	TypeID retType;
} Sel;

typedef struct SelTable {
	Sel* sels;
	Method* methods;
	size_t size;
} SelTable;

typedef struct TypeParents {
	Type* *types;
	size_t size;
} TypeParents;

typedef struct TypeCategories {
	Category* *categories;
	size_t size;
} TypeCategories;

typedef struct Type {
	const char* name;
	TypeID id;
	TypeStructure structure;
	TypeParents *parents;
	TypeCategories *categories;
	SelTable *staticTable;
	SelTable *instanceTable;
	size_t size;
	Value* (*init)(void);
	void (*deinit)(Value*);
} Type;

typedef struct CategoryExt {
	Type *type;
	SelTable *staticTable;
	SelTable *instanceTable;
} CategoryExt;

typedef struct Category {
	const char* name;
	CategoryID id;
	CategoryExt* *extensions;
	size_t size;
} Category;

typedef struct MD {
	TypeID current;
	TypeID actual;
	size_t count;
} MD;


typedef struct Void {
	MD md;
} Void;

typedef struct Value {
	MD md;
} Value;


typedef struct SelTableResults {
	int* indices;
	int size;
} SelTableResults;



// Global constants:
extern size_t $NumTypes, $NumCategories;
extern Type *$Value, *$Void, *$LLVM$Int32, *$LLVM$Dec64;
extern Type* **$Types;
extern Category* **$Categories;



// Method prototypes:

/* Method */
Value* Method_call(Method, Value*, Value**, size_t, bool);


/* Sel */
Sel Sel_newSingle(const char*, TypeID);
Sel Sel_newMulti(const char**, TypeID*, size_t, TypeID);
Sel Sel_newCast(TypeID);
size_t Sel_getArity(Sel);
char* Sel_format(Sel);


/* SelTable */
SelTable* SelTable_new(Sel*, Method*, size_t);
SelTable* SelTable_newEmpty(void);
void SelTable_cleanup(SelTable*);
SelTableResults SelTable_allWithArity(SelTable*, size_t);
Method SelTable_getWithSelector(SelTable*, Sel);


/* TypeParents */
TypeParents* TypeParents_new(Type**, size_t);
void TypeParents_cleanup(TypeParents*);


/* TypeCategories */
TypeCategories* TypeCategories_new(void);
void TypeCategories_cleanup(TypeCategories*);


/* Type */
Type* Type_new(const char*, TypeID, TypeStructure, TypeParents*, SelTable*, SelTable*, size_t, Value* (*)(void), void (*)(Value*));
void Type_cleanup(Type*);
Type* Type_fromName(const char*);
Type* Type_fromID(TypeID);
Value* Type_initDefault(Type*);
bool Type_equals(Type*, Type*);
bool Type_inherits(Type*, Type*);
bool Type_hasParents(Type*);
bool Type_hasParentsBesidesValue(Type*);
bool Type_canInherit(Type*);
Method Type_getStaticMethodWithSelector(Type*, Sel);
Method Type_getInstanceMethodWithSelector(Type*, Sel);
void Type_addCategory(Type*, Category*);
bool Type_inCategory(Type*, Category*);


/* Category */
Category* Category_new(const char*, CategoryID);
void Category_cleanup(Category*);
void Category_addType(Category*, Type*, SelTable*, SelTable*);


/* Value */
Value* Value_init(void);
void Value_deinit(Value*);
void Value_deinitDefault(Value*);
void Value_retain(Value*);
void Value_release(Value*);
bool Value_isA(Value*, Type*);
Type* Value_typeOf(Value*);
Type* Value_actualTypeOf(Value*);
Value* Value_castTo(Value*, Type*);
Value* Value_dispatch(Value*, Sel, Value**);


/* Void */
Value* /*(never)*/ Void_init(void) __attribute__((noreturn));



// Macros:

#define MD_PRELUDE(type)\
	out->md.count = 1;\
	out->md.current = TypeID$##type;\
	out->md.actual = TypeID$##type

#define RETAIN(value) Value_retain((Value*) value)
#define RELEASE(value) Value_release((Value*) value)
#define ISA(value, type) Value_isA((Value*) value, type)

#define DISPATCH_SINGLE(value, label, ret)\
	Value_dispatch(\
		(Value*) value,\
		Sel_newSingle(label, ret),\
		NULL\
	)

#define DISPATCH_MULTI(value, labels, types, size, ret, args)\
	Value_dispatch(\
		(Value*) value,\
		Sel_newMulti(\
			(const char*[]) labels,\
			(TypeID[]) types,\
			size,\
			ret\
		),\
		(Value*[]) args\
	)

#define DISPATCH_CAST(value, type)\
	Value_dispatch(\
		(Value*) value,\
		Sel_newCast(type),\
		NULL\
	)