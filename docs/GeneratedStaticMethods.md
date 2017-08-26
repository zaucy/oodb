# OODB Class Static Methods

`T` is the class type who owns these static methods.

 * `flush(T [, T...])`

  All properties that have been changed locally are sent to the server to be written to the database. An automatic flush may occur depending on the language generated and the configuration options of your oodb instance. See [Automatic Flush](#automatic-flush) for more details.

 * `reset(T, [, T...])`

  Undoes all property changes that were made locally. This also clears any automatic flushes in queue.

 * `subscribe(T, [, T...])`

  Keeps objects in memory and all properties get updated when they are changed.

 * `unsubscribe(T, [, T...])`

  Remove any subscribed objects from memory so they are no longer updated. If an object that was supplied wasn't already subscribed to then nothing happens.


# Automatic Flush
An automatic flush is when oodb updates property changes for you. This behaviour differs between languages.

### Automatic Flush in JavaScript
An automatic flush is put into queue when any property is set. The queue fires next tick so multiple property changes happen in one request. Calling `flush()` or `reset()` will cancel the automatic flush associated with the object(s).

**Note:** next tick in a non-node.js environment uses `setTimeout()` with a 0 millisecond delay. A Node.js environment will use `process.nextTick()`.

### Automatic Flush in C++
In C++ automatic flushes occur on an object's _reference_ destruction. The objects you will mostly be manipulating are actually wrappers around the underlying property data. They behave very similarly to `std::shared_ptr` except you don't access properties and methods with the `->` operator.

When these object wrappers get destroyed they will change the property values of the underlying data and invoke a flush at that point. To prevent an automatic flush just call the static `reset()` method to return the object to it's original state.

**WARNING:** Suppose we have an oodb class named `MyClass`. Creating a new instance of `MyClass` will create a new record in the database.
```C++
// Both of these create new records in the database.
MyClass a;
MyClass* b = new MyClass();

// Try assigning from an existing object. This will _NOT_ create
// a new record. It only creates a new reference based on `a`
MyClass c = a;

// These would also _NOT_ create a new record.
MyClass d{a};
MyClass* e = new MyClass{a};
MyClass f = std::copy(a);
```

### Automatic Flush in PHP
An automatic flush occurs when the process exits.
