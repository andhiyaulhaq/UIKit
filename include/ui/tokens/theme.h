// include/ui/tokens/theme.h
#pragma once
#include <imgui.h>

namespace ui::theme {

enum class ButtonVariant { Primary, Secondary, Danger, Success };

struct ButtonStyle {
  ImVec4 bg;
  ImVec4 bg_hover;
  ImVec4 bg_active;
  ImVec4 text;
  float radius;
};

struct Theme {
  float scale = 1.0f; // Global scale factor for scalability
  // Component styles are computed on-demand via Get<Component>Style functions
};

extern Theme current_theme;

// lifecycle
void LoadDefaultTheme();

// Get style for variant
ButtonStyle GetButtonStyle(ButtonVariant variant);

} // namespace ui::theme
