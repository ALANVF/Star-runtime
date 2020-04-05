#pragma once

#include <string>
#include <vector>
#include <optional>
#include <stdexcept>
#include <cstring>

namespace star {

class Type;
class Value;
class Category;

typedef void (*RawMethod)(Value*);
typedef size_t TypeID;
typedef size_t CategoryID;

enum class Structure {
	Class,
	Protocol,
	Kind,
	Native
};

class Method {
public:
	enum Attr {
		None      = 0,
		Init      = 1 << 1,
		NoInherit = 1 << 3,
		Unordered = 1 << 5
	};
	
	RawMethod raw;
	Attr attrs;

	Method(RawMethod raw, Attr attrs = None): raw(raw), attrs(attrs) {}

	std::optional<Value*> call(Value*, std::vector<Value*>, bool);

	~Method() {}
};

class Sel {
public:
	enum class SelType {
		Single,
		Multi,
		Cast
	};
	
	SelType type;
	TypeID retType;
	size_t arity;

	class Single;
	class Multi;
	class Cast;

	bool isSingle();
	
	bool isMulti();
	
	bool isCast();

	virtual std::string format();

	virtual ~Sel() {}
};

class Sel::Single : public Sel {
public:
	std::string label;

	Single(std::string, TypeID);

	virtual std::string format();

	~Single() {}
};

class Sel::Multi : public Sel {
public:
	std::vector<std::string> labels;
	std::vector<TypeID> types;

	Multi(std::vector<std::string>, std::vector<TypeID>, TypeID);

	virtual std::string format();

	~Multi() {}
};

class Sel::Cast : public Sel {
public:
	Cast(TypeID);

	virtual std::string format();

	~Cast() {}
};

class SelTable {
public:
	std::vector<Sel*> sels;
	std::vector<Method*> methods;
	size_t size;

	SelTable();
	SelTable(std::vector<Sel*>, std::vector<Method*>);

	std::vector<size_t> allWithArity(size_t);

	std::optional<Method*> getWithSelector(Sel*);

	~SelTable();
};

class Type {
public:
	static std::vector<Type*> types;
	static TypeID maxID;

	std::string name;
	TypeID id;
	Structure structure;
	std::vector<Type*> parents;
	std::vector<Category*> categories;
	SelTable *staticTable;
	SelTable *instanceTable;
	size_t size;
	Value* (*init)();
	void (*deinit)(Value*);
	
	Type(std::string, TypeID, Structure, std::vector<Type*>, SelTable*, SelTable*, size_t, Value* (*)(), void (*)(Value*));

	static Type* fromName(std::string);
	
	static Type* fromID(TypeID);

	static TypeID newID();

	Value* initDefault();

	bool equals(Type*);

	bool inherits(Type*);

	bool hasParents();

	bool hasParentsBesidesValue();

	bool canInherit();

	std::optional<Method*> getStaticMethodWithSelector(Sel*);

	std::optional<Method*> getInstanceMethodWithSelector(Sel*);

	std::optional<Value*> dispatch(Sel*, std::vector<Value*>);

	void addCategory(Category*);

	bool inCategory(Category*);

	~Type();
};

class Category {
private:
	class Ext {
	public:
		Type *type;
		SelTable *staticTable;
		SelTable *instanceTable;

		Ext(Type*, SelTable*, SelTable*);

		~Ext();
	};

public:
	static std::vector<Category*> categories;
	static CategoryID maxID;

	std::string name;
	CategoryID id;
	std::vector<Ext*> extensions;

	Category(std::string, CategoryID);

	static CategoryID newID();

	void addType(Type*, SelTable*, SelTable*);

	std::optional<Method*> getStaticMethodForTypeWithSelector(Type*, Sel*);

	std::optional<Method*> getInstanceMethodForTypeWithSelector(Type*, Sel*);

	~Category();
};

class MD {
public:
	TypeID current;
	TypeID actual;
	size_t count;

	MD(TypeID);
	MD(TypeID, TypeID);

	~MD() {}
};

class Value {
public:
	MD *md;

	Value();

	static Value* init();

	void deinit();

	void deinitDefault();

	void retain();

	void release();

	bool isA(Type*);

	Type* typeOf();

	Type* actualTypeOf();

	Value* castTo(Type*);

	std::optional<Value*> dispatch(Sel*, std::vector<Value*>);

	~Value();
};

class Void : public Value {
public:
	Void() {
		throw std::runtime_error("Internal error: Type Star.Void should never be instantiated!");
	}
};

}