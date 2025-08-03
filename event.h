#ifndef _ext_event_h
#define _ext_event_h

#include "core.h"
#include <any>
#include <vector>
#include <string>
#include "eventresult.h"
#include <metamod_oslink.h>

EventResult TriggerEvent(std::string extension_id, std::string event, std::vector<std::any> args, std::any& eventReturn, std::string specific_plugin = "");

#endif