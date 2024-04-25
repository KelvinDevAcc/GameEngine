#include "sound_system.h"

#include "servicelocator.h"
std::unique_ptr<sound_system> servicelocator::_ss_instance{ nullptr };
