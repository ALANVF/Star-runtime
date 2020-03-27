# Initialization functions

`void star_initStar(void);`
Used to initialize the core types `Star.Value` and `Star.Void`.
You should always call this before doing stuff.

`void star_initLLVM(void);`
Used to initialize native types. These include:
- int1 (`bool`)
- int8
- int16
- int32
- int64
- uint8
- uint16
- uint32
- uint64
- float
- double
- long double
- string (`char*`)
Other native types such as pointers will be defined in Star since they are generic types.

`void star_deinitStar(void);`
Cleans up everything that Star has allocated. This includes types and categories.

# Type functions

`size_t star_getNumTypes(void);`
Returns the current number of registered types.

`Type** star_getTypes(void);`
Returns an array of all registered types. This does not need to be freed.

`void star_registerType(Type*);`
Register a new type. This type will be freed automatically when `star_deinitStar` is called.


# Category functions

`size_t star_getNumCategories(void);`
Returns the current number of registered categories.

`Category** star_getCategories(void);`
Returns an array of all registered categories. This does not need to be freed.

`void star_registerCategory(Category*);`
Register a new category. This category will be freed automatically when `star_deinitStar` is called.


# Helper functions

`Type* star_getValueType(void);`
Returns the core type `Star.Value`. This will error if `star_initStar` has not been called.

`Type* star_getVoidType(void);`
Returns the core type `Star.Void`. This will error if `star_initStar` has not been called.