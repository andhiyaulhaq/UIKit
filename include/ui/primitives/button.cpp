// include/ui/primitives/button.cpp
#include "button.h"
#include "../tokens/base/colors.h"
#include "../tokens/base/radius.h"
#include "../tokens/theme.h"
#include <imgui.h>

namespace ui {

static bool DrawButton(const char *label, const ButtonStyle &s,
                       ImVec2 override_size) {
  ImGui::PushStyleColor(ImGuiCol_Button, s.bg);
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, s.bg_hover);
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, s.bg_active);
  ImGui::PushStyleColor(ImGuiCol_Text, s.text);
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, s.radius);
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, s.padding);

  // Pass the override_size (which might be 0,0 or 150,40) to ImGui
  bool clicked = ImGui::Button(label, override_size);

  ImGui::PopStyleVar(2);
  ImGui::PopStyleColor(4);

  return clicked;
}

// Definition of the Master function
bool Button(const char *label, ButtonVariant variant, ButtonSize size_category,
            ImVec2 override_size) {
  ButtonStyle style = theme::GetButtonStyle(variant, size_category);
  return DrawButton(label, style, override_size);
}

namespace theme {

// Helper to get padding based on size
ImVec2 GetPadding(ButtonSize size, float scale) {
  switch (size) {
  case ButtonSize::Small:
    return ImVec2(8.0f * scale, 2.0f * scale);
  case ButtonSize::Medium:
    return ImVec2(16.0f * scale, 6.0f * scale); // Standard
  case ButtonSize::Large:
    return ImVec2(24.0f * scale, 12.0f * scale);
  }
  return ImVec2(16.0f * scale, 6.0f * scale);
}

ButtonStyle GetButtonStyle(ButtonVariant variant, ButtonSize size) {
  using namespace ui::tokens::base;
  float scaled_radius = md * current_theme.scale;

  // Calculate padding based on the size category
  ImVec2 padding = GetPadding(size, current_theme.scale);

  // Define colors (logic remains mostly the same, just adding .padding)
  ButtonStyle style = {};
  style.radius = scaled_radius;
  style.padding = padding;

  switch (variant) {
  case ButtonVariant::Primary:
    style.bg = blue_600;
    style.bg_hover = blue_700;
    style.bg_active = blue_700;
    style.text = neutral_200;
    break;
  case ButtonVariant::Secondary:
    style.bg = neutral_700;
    style.bg_hover = neutral_900;
    style.bg_active = neutral_900;
    style.text = neutral_200;
    break;
  case ButtonVariant::Danger:
    style.bg = red_600;
    style.bg_hover = red_700;
    style.bg_active = red_700;
    style.text = neutral_200;
    style.radius = scaled_radius;
    break;
  case ButtonVariant::Success:
    style.bg = green_600;
    style.bg_hover = green_700;
    style.bg_active = green_700;
    style.text = neutral_200;
    style.radius = scaled_radius;
    break;
  default:
    break;
  }
  return style;
}

} // namespace theme
} // namespace ui
