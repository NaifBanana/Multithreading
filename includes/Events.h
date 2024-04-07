#pragma once
#ifndef _NB_EVENTS
#define _NB_EVENTS

#include <atomic>
#include <stdexcept>
#include <queue>
#include <array>
#include <memory>
#include <mutex>
#include <string>

using state_register = std::atomic<uint64_t>;

namespace NB { 

void NULL_FUNC();

class NBEvent {
friend class NBEventListener;
public:
    NBEvent();
    NBEvent(const uint64_t, void (*initFunc)() = NULL_FUNC, const char* initName="");
    NBEvent(const uint64_t, const char* initName="");
    NBEvent(NBEvent&);
    NBEvent& operator=(NBEvent& cpy);
    ~NBEvent();

    const std::string getName() const;
    const uint64_t getMask() const;
    void setMask(const uint64_t);
    void setName(const char*);
    void setFunc(void (*newFunc)());
    virtual const uint64_t check(const uint64_t) const;

protected:
    uint64_t mask = 0x0;
    void (*func)() = nullptr;
    std::string name = "";

};

class NBState : public NBEvent {
friend class NBEventListener;
public:
    using NBEvent::NBEvent;

    const uint64_t check(const uint64_t) const override;

};

enum NBStateChangeType : uint8_t {
    STATE_RAISE, STATE_DROP, STATE_SET
};
 
struct NBStateChange {
    uint8_t type;
    uint64_t mask;
};

class NBEventListener {
public:
    NBEventListener(NBEvent*, uint16_t, state_register* initStatePtr=nullptr, const uint64_t initState=(uint64_t)0x0);
    template<size_t SIZE>
    NBEventListener(std::array<NBEvent, SIZE> eventArray, state_register* initStatePtr=nullptr, const uint64_t initState=(uint64_t)0x0)
        : NBEventListener(eventArray.data(), eventArray.size(), initStatePtr, initState) {}
    NBEvent& operator[](int);

    state_register* getStatePtr() const;
    const uint64_t getState() const;
    void raiseFlags(const uint64_t);
    void raiseFlags(const NBEvent&);
    void dropFlags(const uint64_t);
    void dropFlags(const NBEvent&);
    const bool snoop(const uint64_t) const;
    const bool snoop(const NBEvent&) const;
    void setState(const uint64_t);
    void listen();
    void listen(const NBEvent&);

protected:
    NBEvent* eventList;
    uint16_t numEvents;
    state_register* state;
    std::mutex bufferLock;
    std::queue<NBStateChange> stateBuffer;

};

};
#endif