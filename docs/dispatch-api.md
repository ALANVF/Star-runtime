# Types

`typedef void (*RawMethod)(Value*);`

Base type of Star methods. Should only be used when calling `Method_new` or `Method_newWithAttrs`.

`typedef size_t TypeID;`

Unique identifier for types.

`typedef size_t CategoryID;`

Unique identifier for categories.

```c
typedef enum {
	TypeStructure$Class,
	TypeStructure$Protocol,
	TypeStructure$Kind,
	TypeStructure$Native
} TypeStructure;
```
Determines how a type should be treated.

```c
typedef enum {
	SelType$Single,
	SelType$Multi,
	SelType$Cast
} SelType;
```
A tag type for `Sel`.

```c
typedef enum {
	MethodAttr$Init      = 1 << 1,
	MethodAttr$NoInherit = 1 << 3,
	MethodAttr$Unordered = 1 << 5
} MethodAttr;
```
Method attribute flags.

```c
typedef struct Method {
	RawMethod raw;
	MethodAttr attrs;
} Method;
```
Star method type. Should not be created directly.

```c
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
```
Selector type. Should not be created directly.

```c
typedef struct SelTable {
	Sel* sels;
	Method** methods;
	size_t size;
} SelTable;
```
Represents a dispatch table. Should not be created directly.

```c
typedef struct TypeParents {
	Type* *types;
	size_t size;
} TypeParents;
```
Represents types that a type inherits from. Should not be created directly.

```c
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
```
Represents a Star type. Should not be created directly.

```c
typedef struct CategoryExt {
	Type *type;
	SelTable *staticTable;
	SelTable *instanceTable;
} CategoryExt;
```
Represents a single category for a type. Should not be created directly.

```c
typedef struct Category {
	const char* name;
	CategoryID id;
	CategoryExt* *extensions;
	size_t size;
} Category;
```
Represents a Star category. Should not be created directly.

```c
typedef struct MD {
	TypeID current;
	TypeID actual;
	size_t count;
} MD;
```
Metadata used for Star values. Can be created directly, but it's generally already initialized.

```c
typedef struct Void {
	MD md;
} Void;
```
Represents the native structure of the core type `Star.Void`. Should not be created directly.

```c
typedef struct Value {
	MD md;
} Value;
```
Represents the native structure of the core type `Star.Void`. Should not be created directly.


# Method functions

`Method* Method_new(RawMethod method);`

Creates a new method.

`Method* Method_newWithAttrs(RawMethod method, MethodAttr attrs);`

Creates a new method with attributes.


# Selector functions

`Sel Sel_newSingle(const char* name, TypeID returnType);`

Creates a single selector (looks like `this[label]` in Star).

`Sel Sel_newMulti(const char* *labels, TypeID *types, size_t arity, TypeID returnType);`

Creates a multi selector (looks like `this[label1: arg1 label: arg2]` in Star).

`Sel Sel_newCast(TypeID returnType);`

Creates a cast selector (looks like `this[MyType]` in Star).

`size_t Sel_getArity(Sel);`

Returns the arity of a selector.

`char* Sel_format(Sel);`

Formats a selector. The returned char pointer needs to be freed by the user.


# SelTable functions

`SelTable* SelTable_new(Sel* selectors, Method* *methods, size_t numSelectors);`

Creates a selector table. `selectors` and `methods` act as parellel arrays. The returned value does not need to be freed.

`SelTable* SelTable_newEmpty(void);`

Creates an empty selector table. The returned value does not need to be freed.


# TypeParents functions

`TypeParents* TypeParents_new(Type* *parents, size_t numParents);`

Creates a TypeParents object. This should only be used when calling `Type_new`. The returned value does not need to be freed.


# Type functions

```c
Type* Type_new(
	const char* name,
	TypeID id,
	TypeStructure structure,
	TypeParents *parents,
	SelTable *staticTable,
	SelTable *instanceTable,
	size_t nativeSize,
	Value* (*init)(void),
	void (*deinit)(Value*)
);
```
Creates a new type. `parents`, `init`, and `deinit` may be ommited with `NULL`. The returned value does not need to be freed.

`Type* Type_fromName(const char* name);`

Lookup a type by name. The returned value does not need to be freed.

`Type* Type_fromID(TypeID id);`

Lookup a type by ID. The returned value does not need to be freed.

`bool Type_equals(Type *type1, Type *type2);`

Check if `type1` represents the same type as `type2`.

`bool Type_inherits(Type *child, Type *parent);`

Check if `child` inherits from `parent`.

`bool Type_hasParents(Type *type);`

Check if `type` inherits from anything.

`bool Type_hasParentsBesidesValue(Type *type);`

Check if `type` inherits from anything besides `Star.Value`.

`bool Type_canInherit(Type *type);`

Check if `type` is able to inherit from anything.

`Method* Type_getStaticMethodWithSelector(Type *type, Sel selector);`

Look up a static method of `type`. Returns `NULL` if it doesn't exist. The returned value does not need to be freed.

`Method* Type_getInstanceMethodWithSelector(Type *type, Sel selector);`

Look up an instance method of `type`. Returns `NULL` if it doesn't exist. The returned value does not need to be freed.

`Value* Type_dispatch(Type *type, Sel selector, Value* *args);`

Call static method of `type` with `args`. `selector` may not be a cast selector. If `selector` is a single selector, `args` can be `NULL`. The returned needs to either be freed by the user or managed using ARC.

`bool Type_inCategory(Type *type, Category *category);`

Check if `type` is in the category `category`.


# Category functions

`Category* Category_new(const char* name, CategoryID id);`

Creates a new Star category. The returned value does not need to be freed.

`void Category_addType(Category *category, Type *type, SelTable *staticTable, SelTable *instanceTable);`

Register a type to a category.

`Method* Category_getStaticMethodForTypeWithSelector(Category *category, Type *type, Sel selector);`

Self-explanatory. The returned value does not need to be freed.

`Method* Category_getInstanceMethodForTypeWithSelector(Category *category, Type *type, Sel selector);`

Self-explanatory. The returned value does not need to be freed.


# Value functions

`void Value_deinitDefault(Value *value);`

Frees any Star value. If the value's type provides a custom deinitializer, that is used instead.

`void Value_retain(Value *value);`

Increases the reference count of `value`.

`void Value_release(Value *value);`

Decreases the reference count of `value`. If the reference count becomes `0`, then `value` is deinitialized.

`bool Value_isA(Value *value, Type *type);`

Check if `value` is an instance of `type` or derived from `type`.

`Type* Value_typeOf(Value *value);`

Returns the current type of `value`. The returned value does not need to be freed.

`Type* Value_actualTypeOf(Value *value);`

Returns the actual type of `value`. The returned value does not need to be freed.

`Value* Value_castTo(Value *value, Type *type);`

Return a new value representing `value` casted to type `type`. The returned value either needs to be freed by the user or managed using ARC.

`Value* Value_dispatch(Value *value, Sel selector, Value* *args);`

Same deal as `Type_dispatch` except that it uses the type's instance table rather than the type's static table. The returned value either needs to be freed by the user or managed using ARC.


# Macros

`#define RETAIN(value)`

Shortcut for `Value_retain`

`#define RELEASE(value)`

Shortcut for `Value_release`

`#define ISA(value, type)`

Shortcut for `Value_isA`

`#define TYPE_DISPATCH_SINGLE(type, label, ret)`

Self-explanatory.

`#define TYPE_DISPATCH_MULTI(type, labels, types, size, ret, args)`

Self-explanatory.

`#define DISPATCH_SINGLE(value, label, ret)`

Self-explanatory.

`#define DISPATCH_MULTI(value, labels, types, size, ret, args)`

Self-explanatory.

`#define DISPATCH_CAST(value, type)`

Self-explanatory.