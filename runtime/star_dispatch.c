#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "star_dispatch.h"
#include "star_id.h"

size_t $NumTypes, $NumCategories;
Type* *$Types;
Category* *$Categories;



// Method definitions:

/* Method */
Method* Method_new(RawMethod method) {
	Method *out = malloc(sizeof(Method));
	out->raw = method;
	out->attrs = 0;

	return out;
}

Method* Method_newWithAttrs(RawMethod method, MethodAttr attrs) {
	if(attrs & MethodAttr$Unordered) {
		perror("Error: The method attribute `unordered` is not yet implemented!");
		exit(1);
	}

	Method *out = malloc(sizeof(Method));
	out->raw = method;
	out->attrs = attrs;

	return out;
}

void Method_cleanup(Method *method) {
	method->raw = NULL;
	free(method);
}

Value* Method_call(Method *_method, Value *value, Value* *args, size_t arity, bool isVoid) {
	RawMethod method = _method->raw;

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
#define METHOD1 void (*)(Value*, Value*)
#define METHOD2 void (*)(Value*, Value*, Value*)
#define METHOD3 void (*)(Value*, Value*, Value*, Value*)
#define METHOD4 void (*)(Value*, Value*, Value*, Value*, Value*)
#define METHOD5 void (*)(Value*, Value*, Value*, Value*, Value*, Value*)
#define METHOD6 void (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*)
#define METHOD7 void (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*)
#define METHOD8 void (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*)
#define METHOD9 void (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*)

		switch(arity) {
			case 0: method(value); break;
			case 1: ((METHOD1) method)(value, ARGS1); break;
			case 2: ((METHOD2) method)(value, ARGS2); break;
			case 3: ((METHOD3) method)(value, ARGS3); break;
			case 4: ((METHOD4) method)(value, ARGS4); break;
			case 5: ((METHOD5) method)(value, ARGS5); break;
			case 6: ((METHOD6) method)(value, ARGS6); break;
			case 7: ((METHOD7) method)(value, ARGS7); break;
			case 8: ((METHOD8) method)(value, ARGS8); break;
			case 9: ((METHOD9) method)(value, ARGS9); break;
			default:
				perror("Internal error: Methods may not take more that 9 arguments for now!");
				exit(1);
		}

#undef METHOD1
#undef METHOD2
#undef METHOD3
#undef METHOD4
#undef METHOD5
#undef METHOD6
#undef METHOD7
#undef METHOD8
#undef METHOD9
	} else {
#define METHOD0 Value* (*)(Value*)
#define METHOD1 Value* (*)(Value*, Value*)
#define METHOD2 Value* (*)(Value*, Value*, Value*)
#define METHOD3 Value* (*)(Value*, Value*, Value*, Value*)
#define METHOD4 Value* (*)(Value*, Value*, Value*, Value*, Value*)
#define METHOD5 Value* (*)(Value*, Value*, Value*, Value*, Value*, Value*)
#define METHOD6 Value* (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*)
#define METHOD7 Value* (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*)
#define METHOD8 Value* (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*)
#define METHOD9 Value* (*)(Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*, Value*)

	switch(arity) {
		case 0: return ((METHOD0) method)(value);
		case 1: return ((METHOD1) method)(value, ARGS1);
		case 2: return ((METHOD2) method)(value, ARGS2);
		case 3: return ((METHOD3) method)(value, ARGS3);
		case 4: return ((METHOD4) method)(value, ARGS4);
		case 5: return ((METHOD5) method)(value, ARGS5);
		case 6: return ((METHOD6) method)(value, ARGS6);
		case 7: return ((METHOD7) method)(value, ARGS7);
		case 8: return ((METHOD8) method)(value, ARGS8);
		case 9: return ((METHOD9) method)(value, ARGS9);
		default:
			perror("Internal error: Methods may not take more that 9 arguments for now!");
			exit(1);
	}

#undef METHOD0
#undef METHOD1
#undef METHOD2
#undef METHOD3
#undef METHOD4
#undef METHOD5
#undef METHOD6
#undef METHOD7
#undef METHOD8
#undef METHOD9
	}

	if(_method->attrs & MethodAttr$Init) {
		return value;
	} else {
		return NULL;
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


/* Sel */
Sel Sel_newSingle(const char* label, TypeID retType) {
	return (Sel) {
		.type = SelType$Single,
		.single = {
			.label = label
		},
		.retType = retType
	};
}

Sel Sel_newMulti(const char** labels, TypeID* types, size_t arity, TypeID retType) {
	Sel out = {
		.type = SelType$Multi,
		.multi = {
			.labels = malloc(sizeof(const char*) * arity),
			.types = malloc(sizeof(TypeID) * arity),
			.arity = arity
		},
		.retType = retType
	};

	for(int i = 0; i < arity; i++) {
		out.multi.labels[i] = labels[i];
		out.multi.types[i] = types[i];
	}

	return out;
}

Sel Sel_newCast(TypeID type) {
	return (Sel) {
		.type = SelType$Cast,
		.cast = {
			.type = type
		},
		.retType = type
	};
}

size_t Sel_getArity(Sel sel) {
	if(sel.type == SelType$Multi) {
		return sel.multi.arity;
	} else {
		return 0;
	}
}

char* Sel_format(Sel sel) {
	if(sel.type == SelType$Single) {
		const char* label = sel.single.label;
		char* out = malloc(3 + strlen(label));
		
		sprintf(out, "[%s]", label);
		
		return out;
	} else if(sel.type == SelType$Cast) {
		const char* name = Type_fromID(sel.retType)->name;
		char* out = malloc(3 + strlen(name));
		
		sprintf(out, "[%s]", name);

		return out;
	} else {
		size_t size = 3;
		char* out;

		for(int i = 0; i < sel.multi.arity; i++) {
			if(strlen(sel.multi.labels[i]) == 0) {
				size += 2;
			} else {
				size += strlen(sel.multi.labels[i]);
				size += 4;
			}
			
			size += strlen(Type_fromID(sel.multi.types[i])->name);
			
			if(i + 1 != sel.multi.arity) {
				size += 2;
			}
		}
		
		out = calloc(size, sizeof(char));
		out[0] = '[';

		for(int i = 0; i < sel.multi.arity; i++) {
			size_t size_ = 1;
			char* out_;
			
			if(strlen(sel.multi.labels[i]) == 0) {
				size_ += 2;
			} else {
				size_ += strlen(sel.multi.labels[i]);
				size_ += 4;
			}
			
			size_ += strlen(Type_fromID(sel.multi.types[i])->name);
			
			if(i + 1 != sel.multi.arity) {
				size_ += 2;
			}

			out_ = calloc(size_, sizeof(char));

			if(strlen(sel.multi.labels[i]) == 0) {
				strcat(out_, "(");
				strcat(out_, Type_fromID(sel.multi.types[i])->name);
				strcat(out_, ")");
			} else {
				strcat(out_, sel.multi.labels[i]);
				strcat(out_, ": (");
				strcat(out_, Type_fromID(sel.multi.types[i])->name);
				strcat(out_, ")");
			}

			if(i + 1 != sel.multi.arity) {
				strcat(out_, ", ");
			}

			strcat(out, out_);
		}

		strcat(out, "]");

		return out;
	}
}


/* SelTable */
SelTable* SelTable_new(Sel* sels, Method** methods, size_t size) {
	SelTable *out = malloc(sizeof(SelTable));
	
	out->sels = malloc(sizeof(Sel) * size);
	out->methods = malloc(sizeof(Method*) * size);
	for(int i = 0; i < size; i++) {
		out->sels[i] = sels[i];
		out->methods[i] = methods[i];
	}
	
	out->size = size;

	return out;
}

SelTable* SelTable_newEmpty(void) {
	SelTable *out = malloc(sizeof(SelTable));
	out->sels = malloc(0);
	out->methods = malloc(0);
	out->size = 0;

	return out;
}

void SelTable_cleanup(SelTable *table) {
	free(table->sels);
	table->sels = NULL;
	
	for(int i = 0; i < table->size; i++) {
		Method_cleanup(table->methods[i]);
		table->methods[i] = NULL;
	}

	free(table->methods);
	table->methods = NULL;

	free(table);
}

SelTableResults SelTable_allWithArity(SelTable *table, size_t arity) {
	SelTableResults out = {
		.indices = malloc(0),
		.size = 0
	};

	if(arity == 0) {
		for(int i = 0; i < table->size; i++) {
			if(table->sels[i].type != SelType$Multi) {
				out.indices = realloc(out.indices, ++out.size * sizeof(int));
				out.indices[out.size-1] = i;
			}
		}
	} else {
		for(int i = 0; i < table->size; i++) {
			if(table->sels[i].type == SelType$Multi && table->sels[i].multi.arity == arity) {
				out.indices = realloc(out.indices, ++out.size * sizeof(int));
				out.indices[out.size-1] = i;
			}
		}
	}

	return out;
}

Method* SelTable_getWithSelector(SelTable *table, Sel sel) {
	SelTableResults results = SelTable_allWithArity(table, Sel_getArity(sel));

	if(sel.type == SelType$Single) {
		for(int i = 0; i < results.size; i++) {
			const int idx = results.indices[i];
			Sel cSel = table->sels[idx];

			if(cSel.type == SelType$Single && !strcmp(cSel.single.label, sel.single.label)) {
				free(results.indices);
				return table->methods[idx];
			}
		}
	} else if(sel.type == SelType$Cast) {
		for(int i = 0; i < results.size; i++) {
			const int idx = results.indices[i];
			Sel cSel = table->sels[idx];

			if(cSel.type == SelType$Cast && cSel.cast.type == sel.cast.type) {
				free(results.indices);
				return table->methods[idx];
			}
		}
	} else {
		// fix comparing types maybe idk
		if(sel.multi.arity == 1) {
			for(int i = 0; i < results.size; i++) {
				const int idx = results.indices[i];
				Sel cSel = table->sels[idx];

				if(!strcmp(cSel.multi.labels[0], sel.multi.labels[0]) && cSel.multi.types[0] == sel.multi.types[0]) {
					free(results.indices);
					return table->methods[idx];
				}
			}
		} else if(sel.multi.arity == 2) {
			for(int i = 0; i < results.size; i++) {
				const int idx = results.indices[i];
				Sel cSel = table->sels[idx];

				if(!strcmp(cSel.multi.labels[0], sel.multi.labels[0]) && cSel.multi.types[0] == sel.multi.types[0]
				&& !strcmp(cSel.multi.labels[1], sel.multi.labels[1]) && cSel.multi.types[1] == sel.multi.types[1]) {
					free(results.indices);
					return table->methods[idx];
				}
			}
		} else {
			for(int i = 0; i < results.size; i++) {
				const int idx = results.indices[i];
				const Sel cSel = table->sels[idx];

				for(int j = 0; j < sel.multi.arity; j++) {
					if(strcmp(cSel.multi.labels[0], sel.multi.labels[0]) || cSel.multi.types[0] != sel.multi.types[0]) {
						goto multiNotMatched;
					}
				}

				free(results.indices);
				return table->methods[idx];

			multiNotMatched:
				continue;
			}
		}
	}

	return NULL;
}


/* TypeParents */
TypeParents* TypeParents_new(Type* *types, size_t size) {
	TypeParents *out = malloc(sizeof(TypeParents));

	out->types = malloc(sizeof(Type*) * size);
	for(int i = 0; i < size; i++) {
		out->types[i] = types[i];
	}
	
	out->size = size;

	return out;
}

void TypeParents_cleanup(TypeParents *parents) {
	for(int i = 0; i < parents->size; i++) {
		parents->types[i] = NULL;
	}

	free(parents->types);
	parents->types = NULL;

	free(parents);
}


/* TypeCategories */
TypeCategories* TypeCategories_new(void) {
	TypeCategories *out = malloc(sizeof(TypeCategories));
	out->categories = malloc(0);
	out->size = 0;

	return out;
}

void TypeCategories_cleanup(TypeCategories *categories) {
	for(int i = 0; i < categories->size; i++) {
		categories->categories[i] = NULL;
	}

	free(categories->categories);
	free(categories);
}


/* Type */
Type* Type_new(const char* name, TypeID id, TypeStructure structure, TypeParents *parents, SelTable *staticTable, SelTable *instanceTable, size_t size, Value* (*init)(void), void (*deinit)(Value*)) {
	Type *out = malloc(sizeof(Type));
	out->name = name;
	out->id = id;
	out->structure = structure;
	out->parents = parents;
	out->categories = TypeCategories_new();
	out->staticTable = staticTable;
	out->instanceTable = instanceTable;
	out->size = size;
	out->init = init;
	out->deinit = deinit;

	return out;
}

void Type_cleanup(Type *type) {
	if(Type_hasParents(type)) {
		TypeParents_cleanup(type->parents);
		type->parents = NULL;
	}

	TypeCategories_cleanup(type->categories);
	type->categories = NULL;

	SelTable_cleanup(type->staticTable);
	type->staticTable = NULL;
	
	SelTable_cleanup(type->instanceTable);
	type->instanceTable = NULL;

	free(type);
}

Type* Type_fromName(const char* name) {
	for(int i = 0; i < $NumTypes; i++) {
		if(!strcmp($Types[i]->name, name)) {
			return $Types[i];
		}
	}

	return NULL;
}

Type* Type_fromID(TypeID id) {
	for(int i = 0; i < $NumTypes; i++) {
		if($Types[i]->id == id) {
			return $Types[i];
		}
	}

	return NULL;
}

Value* Type_initDefault(Type *type) {
	Value* out = malloc(type->size);
	out->md.count = 1;
	out->md.current = type->id;
	out->md.actual = type->id;

	return out;
}

bool Type_equals(Type *type, Type *other) {
	return type->id == other->id;
}

bool Type_inherits(Type *child, Type *parent) {
	if(Type_hasParents(child)) {
		if(Type_canInherit(child)) {
			for(int i = 0; i < child->parents->size; i++) {
				Type *realParent = child->parents->types[i];
				
				if(Type_equals(realParent, parent)) {
					return true;
				} else if(Type_hasParents(realParent)) {
					if(Type_inherits(realParent, parent)) {
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool Type_hasParents(Type *type) {
	return type->parents != NULL;
}

bool Type_hasParentsBesidesValue(Type *type) {
	if(type->parents != NULL) {
		if(type->parents->size > 0) {
			if(type->parents->size == 1) {
				return type->parents->types[0]->id != TypeID$Value;
			} else {
				return true;
			}
		}
	}

	return false;
}

bool Type_canInherit(Type *type) {
	return type->structure != TypeStructure$Kind && type->structure != TypeStructure$Native;
}

Method* Type_getStaticMethodWithSelector(Type *type, Sel sel) {
	Method *out = SelTable_getWithSelector(type->staticTable, sel);

	if(out == NULL && Type_hasParents(type)) {
		for(int i = 0; i < type->parents->size; i++) {
			out = Type_getStaticMethodWithSelector(type->parents->types[i], sel);

			if(out != NULL && !(out->attrs & MethodAttr$NoInherit)) {
				return out;
			}
		}
		
		for(int i = 0; i < type->categories->size; i++) {
			out = Category_getStaticMethodForTypeWithSelector(type->categories->categories[i], type, sel);

			if(out != NULL && !(out->attrs & MethodAttr$NoInherit)) {
				return out;
			}
		}

		return NULL;
	} else {
		return out;
	}
}

Method* Type_getInstanceMethodWithSelector(Type *type, Sel sel) {
	Method *out = SelTable_getWithSelector(type->instanceTable, sel);

	if(out == NULL && Type_hasParents(type)) {
		for(int i = 0; i < type->parents->size; i++) {
			out = Type_getInstanceMethodWithSelector(type->parents->types[i], sel);
			
			if(out != NULL && !(out->attrs & MethodAttr$NoInherit)) {
				return out;
			}
		}

		for(int i = 0; i < type->categories->size; i++) {
			out = Category_getInstanceMethodForTypeWithSelector(type->categories->categories[i], type, sel);

			if(out != NULL && !(out->attrs & MethodAttr$NoInherit)) {
				return out;
			}
		}
		
		return NULL;
	} else {
		return out;
	}
}

Value* Type_dispatch(Type *type, Sel sel, Value* *args) {
	Method *method = Type_getStaticMethodWithSelector(type, sel);

	if(method == NULL) {
		fprintf(stderr, "Error: Type %s does not respond to static method %s!\n", type->name, Sel_format(sel));
		exit(1);
	} else {
		Value *res = Method_call(method, NULL, args, Sel_getArity(sel), sel.retType == TypeID$Void);
		
		if(res == NULL) {
			return res;
		} else {
			return Value_castTo(res, Type_fromID(sel.retType));
		}
	}
}

void Type_addCategory(Type *type, Category *category) {
	type->categories->categories = realloc(type->categories->categories, sizeof(Category*) * ++type->categories->size);
	type->categories->categories[type->categories->size - 1] = category;
}

bool Type_inCategory(Type *type, Category *category) {
	for(int i = 0; i < type->categories->size; i++) {
		if(category->id == type->categories->categories[i]->id) {
			return true;
		}
	}

	return false;
}


/* Category */
Category* Category_new(const char* name, CategoryID id) {
	Category *out = malloc(sizeof(Category));
	out->name = name;
	out->id = id;
	out->extensions = malloc(0);
	out->size = 0;

	return out;
}

void Category_cleanup(Category *category) {
	for(int i = 0; i < category->size; i++) {
		category->extensions[i]->type = NULL;
		SelTable_cleanup(category->extensions[i]->staticTable);
		SelTable_cleanup(category->extensions[i]->instanceTable);
		free(category->extensions[i]);
		category->extensions[i] = NULL;
	}

	free(category->extensions);
	category->extensions = NULL;

	free(category);
}

void Category_addType(Category *category, Type *type, SelTable *staticTable, SelTable *instanceTable) {
	category->extensions = realloc(category->extensions, sizeof(CategoryExt*) * ++category->size);
	category->extensions[category->size - 1] = malloc(sizeof(CategoryExt));
	category->extensions[category->size - 1]->type = type;
	category->extensions[category->size - 1]->staticTable = staticTable;
	category->extensions[category->size - 1]->instanceTable = instanceTable;
}

Method* Category_getStaticMethodForTypeWithSelector(Category *category, Type *type, Sel sel) {
	int index = -1;
	
	for(int i = 0; i < category->size; i++) {
		if(Type_equals(type, category->extensions[i]->type)) {
			index = i;
			break;
		}
	}

	if(index == -1) {
		perror("Internal error!");
		exit(1);
	} else {
		return SelTable_getWithSelector(category->extensions[index]->staticTable, sel);
	}
}

Method* Category_getInstanceMethodForTypeWithSelector(Category *category, Type *type, Sel sel) {
	int index = -1;
	
	for(int i = 0; i < category->size; i++) {
		if(Type_equals(type, category->extensions[i]->type)) {
			index = i;
			break;
		}
	}

	if(index == -1) {
		perror("Internal error!");
		exit(1);
	} else {
		return SelTable_getWithSelector(category->extensions[index]->instanceTable, sel);
	}
}


/* Value */
Value* Value_init(void) {
	Value *out = malloc(sizeof(Value));
	MD_PRELUDE(Value);

	return out;
}

void Value_deinit(Value *value) {
	free(value);
}

void Value_deinitDefault(Value *value) {
	Type *actualType = Value_actualTypeOf(value);
	
	if(actualType->deinit == NULL) {
		Type *type = Value_typeOf(value);

		if(type->deinit == NULL) {
			if(actualType->structure != TypeStructure$Native) {
				free(value);
			}
		} else {
			type->deinit(value);
		}
	} else {
		actualType->deinit(value);
	}
}

void Value_retain(Value *value) {
	value->md.count++;
}

void Value_release(Value *value) {
	if(--value->md.count == 0) {
		Value_deinitDefault(value);
	}
}

bool Value_isA(Value *value, Type *type) {
	Type *valueType = Value_typeOf(value);
	Type *actualValueType = Value_actualTypeOf(value);

	return Type_equals(valueType, type) || Type_inherits(valueType, type) || Type_equals(actualValueType, type);
}

Type* Value_typeOf(Value *value) {
	return Type_fromID(value->md.current);
}

Type* Value_actualTypeOf(Value *value) {
	return Type_fromID(value->md.actual);
}

Value* Value_castTo(Value *value, Type *type) {
	Type *valueType = Value_typeOf(value);
	Type *actualValueType = Value_actualTypeOf(value);

	// add rules for natives and kinds later
	if(type->structure == TypeStructure$Class) {
		if(value->md.actual == type->id) {
			return value;
		} else {
			if(Type_inherits(actualValueType, type)) {
				Value *out = calloc(1, type->size);
				memcpy(out, value, type->size);
				out->md.current = type->id;
				out->md.actual = type->id;
				return out;
			} else if(Type_inherits(type, actualValueType)) {
				Value *out = calloc(1, type->size);
				memcpy(out, value, actualValueType->size);
				out->md.current = type->id;
				out->md.actual = type->id;
				return out;
			} else {
				perror("error!");
				exit(1);
			}
		}
	} else if(type->structure == TypeStructure$Protocol) {
		if(Type_inherits(valueType, type)) {
			Value *out = calloc(1, valueType->size);
			memcpy(out, value, valueType->size);
			out->md.current = type->id;
			return out;
		} else if(Type_inherits(type, valueType)) {
			Value *out = calloc(1, type->size);
			memcpy(out, value, valueType->size);
			out->md.current = type->id;
			return out;
		} else {
			perror("error!");
			exit(1);
		}
	} else {
		perror("Error: Unimplemented!");
		exit(1);
	}
}

Value* Value_dispatch(Value *value, Sel sel, Value* *args) {
	Method *method = Type_getInstanceMethodWithSelector(Value_actualTypeOf(value), sel);

	if(method == NULL) {
		fprintf(stderr, "Error: Type %s does not respond to instance method %s!\n", Value_typeOf(value)->name, Sel_format(sel));
		exit(1);
	} else {
		Value *res = Method_call(method, value, args, Sel_getArity(sel), sel.retType == TypeID$Void);
		
		if(res == NULL) {
			return res;
		} else {
			return Value_castTo(res, Type_fromID(sel.retType));
		}
	}
}


/* Void */
Value* /*(never)*/ Void_init(void) {
	perror("Internal error: Type Star.Void should never be instantiated!");
	exit(1);
}