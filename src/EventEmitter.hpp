//
// Created by xobtah on 07/02/17.
//

#ifndef EMITIUM_EVENTEMITTER_HPP
#define EMITIUM_EVENTEMITTER_HPP

#include <string>
#include <map>

namespace Emitium
{
    class   EventEmitter
    {
    public:
        EventEmitter();
        ~EventEmitter();

        EventEmitter    &On(std::string, void *(*)(void*));

        void            *Emit(std::string, void *param = NULL);

    protected:
        std::map<std::string, void *(*)(void*)> _events;
    };
}

#endif //EMITIUM_EVENTEMITTER_HPP
