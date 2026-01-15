// include/ui/tokens/theme.h
#pragma once
#include <imgui.h>

namespace ui::theme {

struct Theme {
  float scale = 1.0f; // Global scale factor for scalability
  // Component styles are computed on-demand via Get<Component>Style functions
};

extern Theme current_theme;

// lifecycle
void LoadDefaultTheme();
void LoadFonts();

} // namespace ui::theme
