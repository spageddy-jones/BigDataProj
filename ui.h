#pragma once

#include <functional>
#include <string>

// functions with bool return values will return true on success
// and will print the error to stderr on failure

bool uiRegisterCommand(const std::string name, std::function<std::string(const std::string &)> fn);

bool uiRegisterValue(const std::string &name);
bool uiSetValue(const std::string &name, const std::string &value);

// all registrations must be made before calling uiListen()
void uiListen();
