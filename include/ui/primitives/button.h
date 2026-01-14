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

bool Button(const char *label, ButtonVariant variant);

} // namespace ui

const ui::ButtonVariant Primary = ui::ButtonVariant::Primary;
const ui::ButtonVariant Secondary = ui::ButtonVariant::Secondary;
