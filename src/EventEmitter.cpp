//
// Created by xobtah on 07/02/17.
//

#include "EventEmitter.hpp"

namespace Emitium
{
    /*
     *  Ctor & Dtor
     */

    EventEmitter::EventEmitter() {}

    EventEmitter::~EventEmitter() {}

    /*
     *  Public member functions
     */

    EventEmitter    &EventEmitter::On(std::string event, void *(*func)(void*))
    {
        _events[event] = func;
        return (*this);
    }

    void            *EventEmitter::Emit(std::string event, void *param)
    {
        if (_events.find(event) != _events.end())
            return (_events[event](param));
        return (NULL);
    }
}