// include/ui/primitives/button.h
#pragma once
#include <imgui.h>

namespace ui {

enum class ButtonVariant { Primary, Secondary, Danger, Success };
enum class ButtonSize { Small, Medium, Large };

struct ButtonStyle {
  ImVec4 bg;
  ImVec4 bg_hover;
  ImVec4 bg_active;
  ImVec4 text;
  float radius;
  ImVec2 padding;
  ImFont *font;
};

namespace theme {
ButtonStyle GetButtonStyle(ButtonVariant variant, ButtonSize size);
} // namespace theme

// -----------------------------------------------------------------------------
// 1. The Master Function
// This handles the logic. We set defaults here for the "Standard" case.
// Usage: ui::Button("Label") -> Defaults to Primary, Medium
// -----------------------------------------------------------------------------
bool Button(const char *label, ButtonVariant variant = ButtonVariant::Primary,
            ButtonSize size_category = ButtonSize::Medium,
            ImVec2 override_size = ImVec2(0, 0));

// -----------------------------------------------------------------------------
// 2. The Convenience Overload
// This catches the specific case: ui::Button("Label", ImVec2(100, 50));
// We implement it inline here to redirect to the Master function.
// -----------------------------------------------------------------------------
inline bool Button(const char *label, ImVec2 override_size) {
  // We hardcode Primary and Medium here as your requested defaults
  return Button(label, ButtonVariant::Primary, ButtonSize::Medium,
                override_size);
}

} // namespace ui
