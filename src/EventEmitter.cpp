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

    EventEmitter    &EventEmitter::AddListener(std::string event_id, std::function<void ()> cb)
    {
        _listeners.insert(std::make_pair(event_id, std::make_shared<Listener<>>(event_id, cb)));
        return (*this);
    }

    EventEmitter    &EventEmitter::On(std::string event_id, std::function<void ()> cb)
    { return (this->AddListener(event_id, cb)); }

    EventEmitter    &EventEmitter::RemoveListener(std::string listener_id)
    {
        auto i = std::find_if(_listeners.begin(), _listeners.end(), [&] (std::pair<const std::string, std::shared_ptr<ListenerBase>> p)
        { return (p.second->id == listener_id); });
        if (i != _listeners.end())
            _listeners.erase(i);
        else
            throw std::invalid_argument("EventEmitter::remove_listener: Invalid listener id.");
        return (*this);
    }
}