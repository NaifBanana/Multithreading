#include "Events.h"
namespace NB {

std::invalid_argument null_mask_error("NULL MASK NOT ALLOWED");

void NULL_FUNC() {}

NBEvent::NBEvent() {}

NBEvent::NBEvent(const uint64_t initMask, void (*initFunc)(), const char* initName) : mask{initMask}, func{initFunc}, name{initName} {
        if (mask == 0x0) {
            throw null_mask_error;
        }
}

NBEvent::NBEvent(const uint64_t initMask, const char* initName) : NBEvent(initMask, NULL_FUNC, initName) {}

NBEvent::NBEvent(NBEvent& cpy) : NBEvent(cpy.mask, cpy.func, cpy.name.c_str()) {}

NBEvent& NBEvent::operator=(NBEvent& cpy) {
    func = cpy.func;
    name = cpy.name;
    mask = cpy.mask;
    if (mask==0x0) {
        throw null_mask_error;
    }
    return *this;
}

NBEvent::~NBEvent() {}

const uint64_t NBEvent::getMask() const {
    return mask;
}

const std::string NBEvent::getName() const {
    return name;
}

void NBEvent::setFunc(void (*newFunc)()) {
    func = newFunc;
}

void NBEvent::setMask(const uint64_t newMask) {
    mask = newMask;
}

void NBEvent::setName(const char* newName) {
    name = newName;
}

const uint64_t NBEvent::check(const uint64_t refState) const{
    if ((mask!=0) && ((refState&mask)==mask)) {
        func();
        return refState&(~mask);
    }
    return refState;
}

const uint64_t NBState::check(const uint64_t refState) const {
    if ((mask!=0) && ((refState&mask)==mask)) {
        func();
    }
    return refState;
}

NBEventListener::NBEventListener(NBEvent* initEventList, uint16_t initNum, state_register* initStatePtr, const uint64_t initState) 
    : stateBuffer() {
    if (initStatePtr == nullptr) {
        state = new state_register;
    }
    
    std::atomic_store<uint64_t>(state, initState);
    numEvents = initNum;
    eventList = new NBEvent[numEvents];
    for (uint16_t i = 0; i < initNum; ++i) {
        eventList[i] = initEventList[i];
    }
}

NBEvent& NBEventListener::operator[](int ind) {
    return eventList[ind % numEvents];
}

state_register* NBEventListener::getStatePtr() const {
    return state;
}

const uint64_t NBEventListener::getState() const {
    return std::atomic_load<uint64_t>(state);
}

void NBEventListener::raiseFlags(const uint64_t newState) {
    bufferLock.lock();
    stateBuffer.push(NBStateChange{STATE_RAISE, newState});
    bufferLock.unlock();
}

void NBEventListener::raiseFlags(const NBEvent& newEvent) {
    raiseFlags(newEvent.mask);
}

void NBEventListener::dropFlags(const uint64_t dropState) {
    bufferLock.lock();
    stateBuffer.push(NBStateChange{STATE_DROP, dropState});
    bufferLock.unlock();
}

void NBEventListener::dropFlags(const NBEvent& dropEvent) {
    dropFlags(dropEvent.mask);
}

const bool NBEventListener::snoop(const uint64_t refState) const {
    return ((getState()&refState)==refState);
}

const bool NBEventListener::snoop(const NBEvent& refEvent) const {
    return snoop(refEvent.mask);
}

void NBEventListener::setState(const uint64_t newState) {
    bufferLock.lock();
    std::queue<NBStateChange>().swap(stateBuffer);
    bufferLock.unlock();
    std::atomic_store<uint64_t>(state, newState);
}

void NBEventListener::listen() {
    uint64_t oldState = getState();
    for (uint16_t i = 0; i < numEvents; ++i) {
        oldState = eventList[i].check(oldState);
    }
    NBStateChange curr;
    bufferLock.lock();
    for (; !stateBuffer.empty(); stateBuffer.pop()) {
        curr = stateBuffer.front();
        switch (curr.type) {
        case STATE_RAISE:
            oldState |= curr.mask;
            break;
        case STATE_DROP:
            oldState &= ~curr.mask;
            break;
        case STATE_SET:
            oldState = curr.mask;
            break;
        default:
            break;
        }
    }
    bufferLock.unlock();
    setState(oldState);
}

void NBEventListener::listen(const NBEvent& refEvent) {
    uint64_t oldState = getState();
    oldState = refEvent.check(oldState);
    setState(oldState);
}

};