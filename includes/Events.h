#pragma once
#ifndef _NB_EVENTS
#define _NB_EVENTS

#include <atomic>
#include <memory>
#include <functional>
#include <string>
namespace NB { 

class NBEvent {
friend class NBEventListener;
public:
    NBEvent(void (*initFunc)(), uint64_t initMask, const char* initName="");
    
    const std::string getName() const;
    const uint64_t getMask() const;
    void setMask(const uint64_t);
    void setName(const char*);
    void setFunc(void (*newFunc)());
    const uint64_t check(const uint64_t);

private:
    uint64_t mask;
    void (*func)();
    std::string name;

};

class NBEventListener {
public:
    NBEventListener(NBEvent*, uint16_t, std::shared_ptr<std::atomic<uint64_t>> initStatePtr=nullptr, uint64_t initState=0);
    NBEvent& operator[](int);

    std::shared_ptr<std::atomic<uint64_t>> getStatePtr();
    const uint64_t getState();
    const uint64_t raiseState(const uint64_t);
    void setState(const uint64_t);
    void check();

private:
    NBEvent* eventList;
    uint16_t numEvents;
    std::shared_ptr<std::atomic<uint64_t>> state;

};

};
#endif