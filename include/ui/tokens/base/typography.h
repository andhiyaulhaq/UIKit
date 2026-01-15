// include/ui/tokens/base/typography.h
#pragma once
#include <imgui.h>
#include <string>

namespace ui::tokens::base {

// Relative path from the executable to the font file
inline std::string font_family_regular = "assets/fonts/Inter-Regular.ttf";
inline std::string font_family_bold = "assets/fonts/Inter-SemiBold.ttf";

// Font config sizes
inline float font_size_small = 14.0f;
inline float font_size_medium = 18.0f; // Standard UI size
inline float font_size_large = 24.0f;

// Pointers (Initialized in theme.cpp)
inline ImFont *font_small = nullptr;
inline ImFont *font_medium = nullptr;
inline ImFont *font_large = nullptr;

} // namespace ui::tokens::base
