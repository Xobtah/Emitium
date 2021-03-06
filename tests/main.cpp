//
// Created by xobtah on 07/02/17.
//

#include <iostream>
#include <string>

#include "../src/EventEmitter.hpp"

int main()
{
    ium::EventEmitter   event;

    event.On("hi", []() {
        std::cout << "Hello World!" << std::endl;
    }).Emit("hi");

    event.On("twice", []() {
        std::cout << "Hello World!1" << std::endl;
    }).On("twice", []() {
        std::cout << "Hello World!2" << std::endl;
    }).Emit("twice");

    event.On("hello", [](int nb) {
        std::cout << "Hello " << nb << "!" << std::endl;
    }).Emit("hello", 42);

    ium::EventEmitter   event2 = event;

    event2.Emit("hello", 24)/*.On("ref", [](ium::EventEmitter &e) { e.Emit("hello"); })
            .Emit("ref", event2)*/;
    return (0);
}