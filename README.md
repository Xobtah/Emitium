# Emitium
This is an implementation of NodeJS's EventEmitter object, in C++. This class enables your objects to behave on defined events.

### What's the point?
The EventEmitter class adds two main functions to your class:
```markdown
template <typename LambdaType>
EventEmitter	&On(std::string, LambdaType);
template <typename ...Args>
EventEmitter	&Emit(std::string, Args...);
```
* The first function takes a string and a lambda function in parameter. The lambda can take as many parameter as you want. It sets the lambda function to be executed on a call to the string key you give. You can give multiple functions to the same string key, the functions will be added and, on runtime, will be executed one after the other (FIFO).
* The second function takes a string and a set of arguments in parameter. Once it is called, if a listener is set for the string key, it calls the lambda function passing the set of arguments. Make sure you give the arguments the lambda takes, otherwise your program will fail.

This class gives an event based way of programming in C++. For example, if you need to handle the keyboard events of a graphical program (using SDL for example), you can set a listener for each event, and then when you get the event, just call the corresponding function.

### How to use it?
You have an example of use in the tests/ folder.

Make sure you compile the .cpp file, include the .hpp one, and get your class inherit from the EventEmitter class.
```markdown
class   MyObject : public Emitium::EventEmitter
{
public:
	MyObject();
	~MyObject();
};
```
Now you can use it.
```markdown
MyObject obj;
obj.On("my event", []() { std::cout << "Hello World!" << std::endl; });
obj.Emit("my event");
```
You can also chain the functions:
```markdown
obj.On(...).On(...).Emit(...).On(...);
```

### To Do
- Being able to pass function pointers as a callback
- Being able to pass references as callback parameter
