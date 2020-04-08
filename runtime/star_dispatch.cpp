#include "star_dispatch.h"

namespace star {

// Method:
std::optional<Value*> Method::call(Value *value, std::vector<Value*> args, bool isVoid) {
	RawMethod method = this->raw;

#define ARGS1 args[0]
#define ARGS2 args[0], args[1]
#define ARGS3 args[0], args[1], args[2]
#define ARGS4 args[0], args[1], args[2], args[3]
#define ARGS5 args[0], args[1], args[2], args[3], args[4]
#define ARGS6 args[0], args[1], args[2], args[3], args[4], args[5]
#define ARGS7 args[0], args[1], args[2], args[3], args[4], args[5], args[6]
#define ARGS8 args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]
#define ARGS9 args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]
	
	if(isVoid) {
		using Method1 = void (*)(Value*, Value*);
		using Method2 = void (*)(Value*, Value*, Value*);
		using Method3 = void (*)(Value*, Value*, Value*, Value*);
		using Method4 = void (*)(Value*, Value*, Value*, Value*, Value*);
		using Method5 = void (*)(Value*, Value*, Value*, Value*, Value*, Value*);
		using Method6 = void (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*);
		using Method7 = void (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*);
		using Method8 = void (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*);
		using Method9 = void (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*);

		switch(args.size()) {
			case 0: method(value); break;
			case 1: ((Method1) method)(value, ARGS1); break;
			case 2: ((Method2) method)(value, ARGS2); break;
			case 3: ((Method3) method)(value, ARGS3); break;
			case 4: ((Method4) method)(value, ARGS4); break;
			case 5: ((Method5) method)(value, ARGS5); break;
			case 6: ((Method6) method)(value, ARGS6); break;
			case 7: ((Method7) method)(value, ARGS7); break;
			case 8: ((Method8) method)(value, ARGS8); break;
			case 9: ((Method9) method)(value, ARGS9); break;
			default:
				throw std::runtime_error("Internal error: Methods may not take more that 9 arguments for now!");
		}
	} else {
		using Method0 = Value* (*)(Value*);
		using Method1 = Value* (*)(Value*, Value*);
		using Method2 = Value* (*)(Value*, Value*, Value*);
		using Method3 = Value* (*)(Value*, Value*, Value*, Value*);
		using Method4 = Value* (*)(Value*, Value*, Value*, Value*, Value*);
		using Method5 = Value* (*)(Value*, Value*, Value*, Value*, Value*, Value*);
		using Method6 = Value* (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*);
		using Method7 = Value* (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*);
		using Method8 = Value* (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*);
		using Method9 = Value* (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*);

		switch(args.size()) {
			case 0: return ((Method0) method)(value);
			case 1: return ((Method1) method)(value, ARGS1);
			case 2: return ((Method2) method)(value, ARGS2);
			case 3: return ((Method3) method)(value, ARGS3);
			case 4: return ((Method4) method)(value, ARGS4);
			case 5: return ((Method5) method)(value, ARGS5);
			case 6: return ((Method6) method)(value, ARGS6);
			case 7: return ((Method7) method)(value, ARGS7);
			case 8: return ((Method8) method)(value, ARGS8);
			case 9: return ((Method9) method)(value, ARGS9);
			default:
				throw std::runtime_error("Internal error: Methods may not take more that 9 arguments for now!");
		}
	}

	if(this->attrs & Method::Attr::Init) {
		return value;
	} else {
		return {};
	}

#undef ARGS1
#undef ARGS2
#undef ARGS3
#undef ARGS4
#undef ARGS5
#undef ARGS6
#undef ARGS7
#undef ARGS8
#undef ARGS9
}


// Sel:
bool Sel::isSingle() {
	return this->type == SelType::Single;
}

bool Sel::isMulti() {
	return this->type == SelType::Multi;
}

bool Sel::isCast() {
	return this->type == SelType::Cast;
}

std::string Sel::format() {
	if(this->isSingle()) {
		return ((Sel::Single*) this)->format();
	} else if(this->isCast()) {
		return ((Sel::Cast*) this)->format();
	} else {
		return ((Sel::Multi*) this)->format();
	}
}


// Sel::Single:
Sel::Single::Single(std::string label, TypeID retType) {
	this->type = Sel::SelType::Single;
	this->arity = 0;
	this->label = label;
	this->retType = retType;
}

std::string Sel::Single::format() {
	return "[" + this->label + "]";
}


// Sel::Multi:
Sel::Multi::Multi(std::vector<std::string> labels, std::vector<TypeID> types, TypeID retType) {
	if(labels.size() != types.size()) throw std::runtime_error("Error: Labels and argument types must be the same length!");
	if(labels.size() == 0) throw std::runtime_error("Error: A method must take at least one label!");
	
	this->type = Sel::SelType::Multi;
	this->arity = labels.size();
	this->labels = labels;
	this->types = types;
	this->retType = retType;
}

std::string Sel::Multi::format() {
	std::string out = "[";

	for(int i = 0; i < this->arity; i++) {
		if(!this->labels[i].empty()) {
			out += this->labels[i];
			out += ": ";
		}

		out += "(";
		out += Type::fromID(this->types[i])->name;
		out += ")";

		if(i + 1 != this->arity) {
			out += ", ";
		}
	}

	return out + "]";
}


// Sel::Cast:
Sel::Cast::Cast(TypeID retType) {
	this->type = Sel::SelType::Cast;
	this->arity = 0;
	this->retType = retType;
}

std::string Sel::Cast::format() {
	return "[" + Type::fromID(this->retType)->name + "]";
}


// SelTable:
SelTable::SelTable() {
	this->sels = {};
	this->methods = {};
	this->size = 0;
}
SelTable::SelTable(std::vector<Sel*> sels, std::vector<Method*> methods) {
	if(sels.size() != methods.size()) throw std::runtime_error("Error: Must have the same amount of selectors and methods");

	this->sels = sels;
	this->methods = methods;
	this->size = sels.size();
}

std::vector<size_t> SelTable::allWithArity(size_t arity) {
	std::vector<size_t> out = {};

	for(int i = 0; i < this->size; i++) {
		if(this->sels[i]->arity == arity) {
			out.push_back(i);
		}
	}

	return out;
}

std::optional<Method*> SelTable::getWithSelector(Sel *sel) {
	for(int idx : this->allWithArity(sel->arity)) {
		Sel *csel = this->sels[idx];
		
		if(csel->type == sel->type) {
			if(sel->isSingle()) {
				if(((Sel::Single*) csel)->label == ((Sel::Single*) sel)->label) {
					return this->methods[idx];
				}
			} else if(sel->isCast()) {
				if(csel->type == sel->type) {
					return this->methods[idx];
				}
			} else {
				Sel::Multi *_csel = (Sel::Multi*) csel;
				Sel::Multi *_sel = (Sel::Multi*) sel;

				if(_csel->labels == _sel->labels && _csel->types == _sel->types) {
					return this->methods[idx];
				}
			}
		}
	}

	return {};
}

SelTable::~SelTable() {
	for(Sel *sel : this->sels) {
		delete sel;
	}
	
	for(Method *method : this->methods) {
		delete method;
	}
}


// Type:
size_t Type::maxID = 0;
std::vector<Type*> Type::types = {};

Type::Type(std::string name, TypeID id, Structure structure, std::vector<Type*> parents, SelTable *staticTable, SelTable *instanceTable, size_t size, Value* (*init)(), void (*deinit)(Value*)) {
	this->name = name;
	this->id = id;
	this->structure = structure;
	this->parents = parents;
	this->categories = {};
	this->staticTable = staticTable;
	this->instanceTable = instanceTable;
	this->size = size;
	this->init = init;
	this->deinit = deinit;
}

Type* Type::fromName(std::string name) {
	for(Type *type : Type::types) {
		if(type->name == name) {
			return type;
		}
	}

	throw std::runtime_error("error!");
}

Type* Type::fromID(TypeID id) {
	for(Type *type : Type::types) {
		if(type->id == id) {
			return type;
		}
	}

	throw std::runtime_error("error!");
}

TypeID Type::newID() {
	return Type::maxID++;
}

Value* Type::initDefault() {
	if(this->structure != Structure::Class) throw std::runtime_error("Error: Can only create an instance of a class type!");
	
	Value *out = (Value*) operator new(this->size);
	out->md = new MD(this->id);

	return out;
}

bool Type::equals(Type *type) {
	return this->id == type->id;
}

bool Type::inherits(Type *type) {
	if(this->hasParents()) {
		for(Type *parent : this->parents) {
			if(parent->equals(type) || parent->inherits(type)) {
				return true;
			}
		}
	}

	return false;
}

bool Type::hasParents() {
	return !this->parents.empty();
}

bool Type::hasParentsBesidesValue() {
	if(this->hasParents()) {
		if(this->parents.size() == 1) {
			return this->parents[0]->id == 0;
		} else {
			return true;
		}
	} else {
		return false;
	}
}

bool Type::canInherit() {
	return this->structure != Structure::Kind && this->structure != Structure::Native;
}

std::optional<Method*> Type::getStaticMethodWithSelector(Sel *sel) {
	if(auto method = this->staticTable->getWithSelector(sel)) {
		return method;
	}
	
	if(this->hasParents()) {
		for(Type *parent : this->parents) {
			if(auto method = parent->getStaticMethodWithSelector(sel)) {
				return method;
			}
		}
	}

	for(Category *category : this->categories) {
		if(auto method = category->getStaticMethodForTypeWithSelector(this, sel)) {
			return method;
		}
	}

	return {};
}

std::optional<Method*> Type::getInstanceMethodWithSelector(Sel *sel) {
	if(auto method = this->instanceTable->getWithSelector(sel)) {
		return method;
	}
	
	if(this->hasParents()) {
		for(Type *parent : this->parents) {
			if(auto method = parent->getInstanceMethodWithSelector(sel)) {
				return method;
			}
		}
	}

	for(Category *category : this->categories) {
		if(auto method = category->getInstanceMethodForTypeWithSelector(this, sel)) {
			return method;
		}
	}

	return {};
}

std::optional<Value*> Type::dispatch(Sel *sel, std::vector<Value*> args) {
	if(auto method = this->getStaticMethodWithSelector(sel)) {
		if(auto result = (*method)->call(nullptr, args, sel->retType == 1)) {
			return (*result)->castTo(Type::fromID(sel->retType));
		} else {
			return {};
		}
	} else {
		throw std::runtime_error(("Error: Type " + this->name + " does not respond to static method " + sel->format() + "!").c_str());
	}
}

void Type::addCategory(Category *category) {
	this->categories.push_back(category);
}

bool Type::inCategory(Category *category) {
	for(Category *cat : this->categories) {
		if(cat->id == category->id) {
			return true;
		}
	}

	return false;
}

Type::~Type() {
	delete this->staticTable;
	delete this->instanceTable;
}


// Category::Ext:
Category::Ext::Ext(Type *type, SelTable *staticTable, SelTable *instanceTable) {
	this->type = type;
	this->staticTable = staticTable;
	this->instanceTable = instanceTable;
}

Category::Ext::~Ext() {
	delete this->staticTable;
	delete this->instanceTable;
}


// Category:
size_t Category::maxID = 0;
std::vector<Category*> Category::categories = {};

Category::Category(std::string name, CategoryID id) {
	this->name = name;
	this->id = id;
	this->extensions = {};
}

CategoryID Category::newID() {
	return Category::maxID++;
}

void Category::addType(Type *type, SelTable *staticTable, SelTable *instanceTable) {
	this->extensions.push_back(new Category::Ext(type, staticTable, instanceTable));
}

std::optional<Method*> Category::getStaticMethodForTypeWithSelector(Type *type, Sel *sel) {
	for(auto ext : this->extensions) {
		if(ext->type->equals(type)) {
			return ext->staticTable->getWithSelector(sel);
		}
	}

	return {};
}

std::optional<Method*> Category::getInstanceMethodForTypeWithSelector(Type *type, Sel *sel) {
	for(auto ext : this->extensions) {
		if(ext->type->equals(type)) {
			return ext->instanceTable->getWithSelector(sel);
		}
	}

	return {};
}

Category::~Category() {
	for(auto ext : this->extensions) {
		delete ext;
	}
}


// MD:
MD::MD(TypeID id) {
	this->current = id;
	this->actual = id;
	this->count = 1;
}
MD::MD(TypeID current, TypeID actual) {
	this->current = current;
	this->actual = actual;
	this->count = 1;
}

std::string MD::format() {
	return (
		"Current: " + Type::fromID(this->current)->name + ", "
		"Actual: " + Type::fromID(this->actual)->name + ", "
		"Count: " + std::to_string(this->count)
	);
}


// Value:
Value::Value() {
	this->md = new MD(0);
}

Value* Value::init() {
	return new Value();
}

void Value::deinit() {
	//delete this->md;
	//this->md = nullptr;

	operator delete(this, this->actualTypeOf()->size);
}

void Value::deinitDefault() {
	Type *actualType = this->actualTypeOf();
	
	if(actualType->deinit == nullptr) {
		Type *type = this->typeOf();
		
		if(type->deinit != nullptr) {
			type->deinit(this);
		}
	} else {
		actualType->deinit(this);
	}
}

void Value::retain() {
	this->md->count++;
}

void Value::release() {
	if(--this->md->count == 0) {
		Type *actualType = this->actualTypeOf();

		this->deinitDefault();
		delete this->md;

		if(actualType->structure == Structure::Native) {
			operator delete(this, sizeof(this));
		} else {
			operator delete(this, actualType->size);
		}
	}
}

bool Value::isA(Type *type) {
	Type *current = this->typeOf();
	Type *actual = this->actualTypeOf();

	return current->equals(type) || current->inherits(type) || actual->equals(type);
}

Type* Value::typeOf() {
	return Type::fromID(this->md->current);
}

Type* Value::actualTypeOf() {
	return Type::fromID(this->md->actual);
}

Value* Value::castTo(Type *type) {
	Type *current = this->typeOf();
	Type *actual = this->actualTypeOf();

	if(type->structure == Structure::Class) {
		if(this->md->actual == type->id) {
			return this;
		} else if(actual->inherits(type)) {
			Value *out = (Value*) operator new(type->size);
			std::memcpy(out, this, type->size);
			out->md->current = type->id;
			out->md->actual = type->id;
			return out;
		} else if(type->inherits(actual)) {
			Value *out = (Value*) operator new(type->size);
			std::memcpy(out, this, actual->size);
			out->md->current = type->id;
			out->md->actual = type->id;
			return out;
		} else {
			throw std::runtime_error("error!");
		}
	} else if(type->structure == Structure::Protocol) {
		if(current->inherits(type)) {
			Value *out = (Value*) operator new(current->size);
			std::memcpy(out, this, current->size);
			out->md->current = type->id;
			return out;
		} else if(type->inherits(current)) {
			Value *out = (Value*) operator new(type->size);
			std::memcpy(out, this, current->size);
			out->md->current = type->id;
			return out;
		} else {
			throw std::runtime_error("error!");
		}
	} else {
		throw std::runtime_error("Error: Unimplemented!");
	}
}

std::optional<Value*> Value::dispatch(Sel *sel, std::vector<Value*> args) {
	Type *type = this->actualTypeOf();
	
	if(auto method = type->getInstanceMethodWithSelector(sel)) {
		if(auto result = (*method)->call(this, args, sel->retType == 1)) {
			if((*method)->attrs & Method::Attr::Init) {
				return this;
			} else {
				return (*result)->castTo(Type::fromID(sel->retType));
			}
		} else {
			return {};
		}
	} else {
		throw std::runtime_error(("Error: Type " + type->name + " does not respond to static method " + sel->format() + "!").c_str());
	}
}
	
Value::~Value() {}

}