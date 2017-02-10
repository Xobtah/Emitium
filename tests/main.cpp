//
// Created by xobtah on 07/02/17.
//

#include <iostream>
#include <string>

#include "../src/EventEmitter.hpp"

int main()
{
    Emitium::EventEmitter   event;
    //char                    string[] = "World";

    /*event.On("hi", [](void *param) -> void*
    {
        std::cout << "Hello " << reinterpret_cast<char*>(param) << "!" << std::endl;
        return (NULL);
    }).Emit("hi", string);
    event.On("hello", []()
    {
        std::cout << "Hello!" << std::endl;
    }).Emit("hello");*/
    event.On("hi", []() {
        std::cout << "Hello World!" << std::endl;
    }).Emit("hi");
    return (0);
}