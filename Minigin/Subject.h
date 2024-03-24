#pragma once

#include "GameEvent.h"
#include "Observer.h"

class Subject {
public:
    virtual void Attach(Observer* observer, GameEvent event) = 0;
    virtual void Detach(Observer* observer, GameEvent event) = 0;
    virtual void Notify(GameEvent event) = 0;
};