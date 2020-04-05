#include <functional>

#include "star_c.h"

template<typename In, typename Out>
static std::vector<Out> wrapCArray(In* arr, size_t length, std::function<Out(In)> fn) {
	std::vector<Out> out = {};

	for(int i = 0; i < length; i++) {
		out.push_back(fn(arr[i]));
	}

	return out;
}

template<
	typename To,
	typename From,
	typename = std::enable_if_t<
			(
				(std::is_pointer_v<To> && std::is_class_v<std::remove_pointer_t<To>>) ||
				(std::is_pointer_v<From> && std::is_class_v<std::remove_pointer_t<From>>)
			) && sizeof(From) == sizeof(To)
	>
>
To unsafeCast(From value) {
	return *((To*) &value);
}

template<typename T>
T* unwrap(void* value) {
	return (T*) value;
}

extern "C" {

/* dispatch */
star_Method star_Method_new(star_RawMethod raw) {
	return new star::Method(raw);
}

star_Method star_Method_newWithAttrs(star_RawMethod raw, star_MethodAttr attrs) {
	return new star::Method(raw, (star::Method::Attr) attrs);
}

void star_Method_cleanup(star_Method method) {
	delete unwrap<star::Method>(method);
}

star_Value star_Method_call(star_Method method, star_Value *value, star_Value* args, size_t numArgs, bool isVoid) {
	auto _value = value == NULL ? nullptr : unwrap<star::Value>(value);
	auto _args = wrapCArray<star_Value, star::Value*>(args, numArgs, unwrap<star::Value>);
	
	if(auto result = unwrap<star::Method>(method)->call(_value, _args, isVoid)) {
		return *result;
	} else {
		return NULL;
	}
}

star_Sel star_Sel_newSingle(const char* label, star_TypeID retType) {
	return new star::Sel::Single(label, retType);
}

star_Sel star_Sel_newMulti(const char** labels, star_TypeID* types, size_t arity, star_TypeID retType) {
	auto _labels = wrapCArray<const char*, std::string>(labels, arity, [](auto str) {return str;});
	auto _types = wrapCArray<star_TypeID, star::TypeID>(types, arity, [](auto id) {return id;});

	return new star::Sel::Multi(_labels, _types, retType);
}

star_Sel star_Sel_newCast(star_TypeID retType) {
	return new star::Sel::Cast(retType);
}

size_t star_Sel_getArity(star_Sel sel) {
	return unwrap<star::Sel>(sel)->arity;
}

char* star_Sel_format(star_Sel sel) {
	return _strdup(unwrap<star::Sel>(sel)->format().data());
}

star_SelTable star_SelTable_new(star_Sel* sels, star_Method* methods, size_t numMethods) {
	auto _sels = wrapCArray<star_Sel, star::Sel*>(sels, numMethods, unwrap<star::Sel>);
	auto _methods = wrapCArray<star_Method, star::Method*>(methods, numMethods, unwrap<star::Method>);

	return new star::SelTable(_sels, _methods);
}

star_SelTable star_SelTable_newEmpty() {
	return new star::SelTable();
}

void star_SelTable_cleanup(star_SelTable table) {
	delete unwrap<star::SelTable>(table);
}

size_t* star_SelTable_allWithArity(star_SelTable table, size_t arity, size_t *length) {
	auto indexes = unwrap<star::SelTable>(table)->allWithArity(arity);
	auto out = (size_t*) calloc(indexes.size(), sizeof(size_t));
	
	memcpy_s(out, sizeof(size_t) * indexes.size(), indexes.data(), sizeof(size_t) * indexes.size());
	*length = indexes.size();

	return out;
}

star_Method star_SelTable_getWithSelector(star_SelTable table, star_Sel sel) {
	if(auto result = unwrap<star::SelTable>(table)->getWithSelector(unwrap<star::Sel>(sel))) {
		return *result;
	} else {
		return NULL;
	}
}

star_Type star_Type_new(
	const char* name,
	star_TypeID id,
	star_Structure structure,
	star_Type* parents, size_t numParents,
	star_SelTable staticTable,
	star_SelTable instanceTable,
	size_t size,
	star_Value (*init)(),
	void (*deinit)(star_Value)
) {
	return new star::Type(
		name,
		id,
		star::Structure(structure),
		numParents == 0
			? std::vector<star::Type*> {}
			: wrapCArray<star_Type, star::Type*>(parents, numParents, unwrap<star::Type>),
		unwrap<star::SelTable>(staticTable),
		unwrap<star::SelTable>(instanceTable),
		size,
		init == NULL ? nullptr : (star::Value* (*)()) init,
		deinit == NULL ? nullptr : (void (*)(star::Value*)) deinit
	);
}

star_Type star_Type_fromName(const char* name) {
	return star::Type::fromName(name);
}

star_Type star_Type_fromID(star_TypeID id) {
	return star::Type::fromID(id);
}

star_TypeID star_Type_newID() {
	return star::Type::newID();
}

void star_Type_cleanup(star_Type type) {
	delete unwrap<star::Type>(type);
}

star_Value star_Type_initDefault(star_Type type) {
	return unwrap<star::Type>(type)->initDefault();
}

bool star_Type_equals(star_Type type1, star_Type type2) {
	return unwrap<star::Type>(type1)->equals(unwrap<star::Type>(type2));
}

bool star_Type_inherits(star_Type child, star_Type parent) {
	return unwrap<star::Type>(child)->inherits(unwrap<star::Type>(parent));
}

bool star_Type_hasParents(star_Type type) {
	return unwrap<star::Type>(type)->hasParents();
}

bool star_Type_hasParentsBesidesValue(star_Type type) {
	return unwrap<star::Type>(type)->hasParentsBesidesValue();
}

bool star_Type_canInherit(star_Type type) {
	return unwrap<star::Type>(type)->canInherit();
}

star_Method star_Type_getStaticMethodWithSelector(star_Type type, star_Sel sel) {
	if(auto result = unwrap<star::Type>(type)->getStaticMethodWithSelector(unwrap<star::Sel>(sel))) {
		return *result;
	} else {
		return NULL;
	}
}

star_Method star_Type_getInstanceMethodWithSelector(star_Type type, star_Sel sel) {
	if(auto result = unwrap<star::Type>(type)->getInstanceMethodWithSelector(unwrap<star::Sel>(sel))) {
		return *result;
	} else {
		return NULL;
	}
}

star_Value star_Type_dispatch(star_Type type, star_Sel sel, star_Value* args) {
	auto _args = wrapCArray<star_Value, star::Value*>(args, unwrap<star::Sel>(sel)->arity, unsafeCast<star::Value*, star_Value>);

	if(auto result = unwrap<star::Type>(type)->dispatch(unwrap<star::Sel>(sel), _args)) {
		return *result;
	} else {
		return NULL;
	}
}

void star_Type_addCategory(star_Type type, star_Category category) {
	unwrap<star::Type>(type)->addCategory(unwrap<star::Category>(category));
}

bool star_Type_inCategory(star_Type type, star_Category category) {
	return unwrap<star::Type>(type)->inCategory(unwrap<star::Category>(category));
}

star_Category star_Category_new(const char* name, star_CategoryID id) {
	return new star::Category(name, id);
}

star_CategoryID star_Category_newID() {
	return star::Category::newID();
}

void star_Category_cleanup(star_Category category) {
	delete unwrap<star::Category>(category);
}

void star_Category_addType(star_Category category, star_Type type, star_SelTable staticTable, star_SelTable instanceTable) {
	unwrap<star::Category>(category)->addType(unwrap<star::Type>(type), unwrap<star::SelTable>(staticTable), unwrap<star::SelTable>(instanceTable));
}

star_Method star_Category_getStaticMethodForTypeWithSelector(star_Category category, star_Type type, star_Sel sel) {
	if(auto result = unwrap<star::Category>(category)->getStaticMethodForTypeWithSelector(unwrap<star::Type>(type), unwrap<star::Sel>(sel))) {
		return *result;
	} else {
		return NULL;
	}
}

star_Method star_Category_getInstanceMethodForTypeWithSelector(star_Category category, star_Type type, star_Sel sel) {
	if(auto result = unwrap<star::Category>(category)->getInstanceMethodForTypeWithSelector(unwrap<star::Type>(type), unwrap<star::Sel>(sel))) {
		return *result;
	} else {
		return NULL;
	}
}

star_Value star_Value_init() {
	return star::Value::init();
}

void star_Value_deinit(star_Value value) {
	unwrap<star::Value>(value)->deinit();
}

void star_Value_deinitDefault(star_Value value) {
	unwrap<star::Value>(value)->deinitDefault();
}

void star_Value_retain(star_Value value) {
	unwrap<star::Value>(value)->retain();
}

void star_Value_release(star_Value value) {
	unwrap<star::Value>(value)->release();
}

bool star_Value_isA(star_Value value, star_Type type) {
	return unwrap<star::Value>(value)->isA(unwrap<star::Type>(type));
}

star_Type star_Value_typeOf(star_Value value) {
	return unwrap<star::Value>(value)->typeOf();
}

star_Type star_Value_actualTypeOf(star_Value value) {
	return unwrap<star::Value>(value)->actualTypeOf();
}

star_Value star_Value_castTo(star_Value value, star_Type type) {
	return unwrap<star::Value>(value)->castTo(unwrap<star::Type>(type));
}

star_Value star_Value_dispatch(star_Value value, star_Sel sel, star_Value* args) {
	auto _args = wrapCArray<star_Value, star::Value*>(args, unwrap<star::Sel>(sel)->arity, unsafeCast<star::Value*, star_Value>);

	if(auto result = unwrap<star::Value>(value)->dispatch(unwrap<star::Sel>(sel), _args)) {
		return *result;
	} else {
		return NULL;
	}
}


/* star */
void star_init() {
	star::init();
}

void star_deinit() {
	star::deinit();
}

size_t star_getNumTypes() {
	return star::numTypes();
}

star_Type* star_getTypes() {
	return (star_Type*) star::types().data();
}

void star_registerType(star_Type type) {
	star::registerType(unwrap<star::Type>(type));
}

size_t star_getNumCategories() {
	return star::numCategories();
}

star_Category* star_getCategories() {
	return (star_Category*) star::categories().data();
}

void star_registerCategory(star_Category category) {
	star::registerCategory(unwrap<star::Category>(category));
}

star_Type star_getValueType() {
	return star::valueType();
}

star_Type star_getVoidType() {
	return star::voidType();
}


/* llvm */
void star_llvm_init() {
	star::llvm::init();
}

#define STAR_LLVM_WRAP(type, base)\
	star_Value star_llvm_##type##_wrap(base value) {\
		return new star::llvm::type(value);\
	}\
	\
	base star_llvm_##type##_unwrap(star_Value value) {\
		return unwrap<star::llvm::type>(value)->repr;\
	}
	
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

}