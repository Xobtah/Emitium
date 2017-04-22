//
// Created by xobtah on 07/02/17.
//

#ifndef EMITIUM_EVENTEMITTER_HPP
#define EMITIUM_EVENTEMITTER_HPP

#include <string>
#include <functional>
#include <map>
#include <memory>
#include <list>
#include <algorithm>

namespace ium
{
    class EventEmitter
    {
    public:
        EventEmitter();
        EventEmitter(const EventEmitter&);
        EventEmitter    &operator=(const EventEmitter&);
        ~EventEmitter();

        template <typename... Args>
        EventEmitter    &AddListener(std::string, std::function<void (Args...)>);
        EventEmitter    &AddListener(std::string, std::function<void ()>);

        template<typename LambdaType>
        EventEmitter    &AddListener(std::string event_id, LambdaType lambda)
        { return (AddListener(event_id, make_function(lambda))); }

        EventEmitter    &RemoveListener(std::string);

        template <typename... Args>
        EventEmitter    &On(std::string, std::function<void (Args...)>);
        EventEmitter    &On(std::string, std::function<void ()>);

        template<typename LambdaType>
        EventEmitter    &On(std::string event_id, LambdaType lambda)
        { return On(event_id, make_function(lambda)); }

        template <typename... Args>
        EventEmitter    &Emit(std::string, Args...);

    private:
        struct ListenerBase
        {
            ListenerBase() {}
            ListenerBase(std::string i) : id(i) {}
            virtual ~ListenerBase() {}

            std::string id;
        };

        template <typename... Args>
        struct Listener : public ListenerBase
        {
            Listener() {}
            Listener(std::string i, std::function<void (Args...)> c) : ListenerBase(i), cb(c) {}

            std::function<void (Args...)> cb;
        };

        template <typename T>
        struct function_traits : public function_traits<decltype(&T::operator())> {};

        template <typename ClassType, typename ReturnType, typename... Args>
        struct function_traits<ReturnType(ClassType::*)(Args...) const>
        { typedef std::function<ReturnType (Args...)> f_type; };

        template <typename L>
        typename function_traits<L>::f_type make_function(L l)
        { return ((typename function_traits<L>::f_type)(l)); }

        std::multimap<std::string, std::shared_ptr<ListenerBase>>  _listeners;
    };

    template <typename... Args>
    EventEmitter    &EventEmitter::AddListener(std::string event_id, std::function<void (Args...)> cb)
    {
        _listeners.insert(std::make_pair(event_id, std::make_shared<Listener<Args...>>(event_id, cb)));
        return (*this);
    }

    template <typename... Args>
    EventEmitter    &EventEmitter::On(std::string event_id, std::function<void (Args...)> cb)
    { return (this->AddListener(event_id, cb)); }

    template <typename... Args>
    EventEmitter    &EventEmitter::Emit(std::string event_id, Args... args)
    {
        std::list<std::shared_ptr<Listener<Args...>>> handlers;

        {
            auto range = _listeners.equal_range(event_id);
            handlers.resize(std::distance(range.first, range.second));
            std::transform(range.first, range.second, handlers.begin(), [](std::pair<const std::string, std::shared_ptr<ListenerBase>> p)
            {
                auto l = std::dynamic_pointer_cast<Listener<Args...>>(p.second);
                if (l)
                    return (l);
                else
                    throw std::logic_error("EventEmitter::Emit: Invalid event signature.");
            });
        }
        for (auto &h : handlers)
            h->cb(args...);
        return (*this);
    }
}

#endif //EMITIUM_EVENTEMITTER_HPP
