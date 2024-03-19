#include "Events.h"
namespace NB {

NBEvent::NBEvent(void (*initFunc)(), const uint64_t initMask, const char* initName) {
    mask = initMask;
    func = initFunc;
    name = initName;
}

const uint64_t NBEvent::getMask() const {
    return mask;
}

const std::string NBEvent::getName() const {
    return name;
}

void NBEvent::setMask(const uint64_t newMask) {
    mask = newMask;
}
void NBEvent::setName(const char* newName) {
    name = newName;
}

void NBEvent::setFunc(void (*newFunc)()) {
    func = newFunc;
}

const uint64_t NBEvent::check(const uint64_t state) {
    if (state & mask == mask) {
        func();
    }
    return state&(~mask);
}

NBEventListener::NBEventListener(NBEvent* initEventList, uint16_t initNum, std::shared_ptr<std::atomic<uint64_t>> initStatePtr, uint64_t initState) {
    if (initStatePtr == nullptr) {
        state = std::shared_ptr<std::atomic<uint64_t>>(new std::atomic<uint64_t>);
    } else {
        state = initStatePtr;
    }

    *state = initState;
    numEvents = initNum;
    for (uint16_t i = 0; i < initNum; ++i) {
        eventList[i] = initEventList[i];
    }
}

NBEvent& NBEventListener::operator[](int ind) {
    return eventList[ind % numEvents];
}

std::shared_ptr<std::atomic<uint64_t>> NBEventListener::getStatePtr() {
    return std::shared_ptr<std::atomic<uint64_t>>(state);
}

const uint64_t NBEventListener::getState() {
    return *state;
}

const uint64_t NBEventListener::raiseState(const uint64_t newState) {
    uint64_t oldState = *state;
    uint64_t tempState = oldState | newState;
    *state = tempState;
    return tempState;
}

void NBEventListener::setState(const uint64_t newState) {
    *state = newState;
}

void NBEventListener::check() {
    uint64_t oldState = *state;
    for (uint16_t i = 0; i < numEvents; ++i) {
        oldState = eventList[i].check(oldState);
    }
    *state = oldState;
}

};