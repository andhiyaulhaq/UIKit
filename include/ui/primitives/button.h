// include/ui/primitives/button.h
#pragma once

#include <imgui.h>

namespace ui {

enum class ButtonVariant { Primary, Secondary, Danger, Success };

struct ButtonStyle {
  ImVec4 bg;
  ImVec4 bg_hover;
  ImVec4 bg_active;
  ImVec4 text;
  float radius;
};

namespace theme {
ButtonStyle GetButtonStyle(ButtonVariant variant);
} // namespace theme

bool Button(const char *label, const ButtonStyle &style);
bool Button(const char *label, ButtonVariant variant);

} // namespace ui
