#pragma once
#include <string>

namespace ui {

// Simple Input Field for std::string
// Returns true if the text changed
bool Input(const char *label, std::string &buffer, const char *hint = nullptr,
           float width = -1.0f);

} // namespace ui
