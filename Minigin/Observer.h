#pragma once

#include "GameEvent.h"

class Observer {
public:
	virtual ~Observer() = default;
	virtual void UpdateObsever(GameEvent event) = 0;
};