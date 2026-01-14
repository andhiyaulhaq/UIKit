// include/ui/primitives/button.cpp
#include "button.h"
#include "../tokens/base/colors.h"
#include "../tokens/base/radius.h"
#include "../tokens/theme.h"
#include <imgui.h>

namespace ui {

static bool DrawButton(const char *label, const ButtonStyle &s) {
  ImGui::PushStyleColor(ImGuiCol_Button, s.bg);
  ImGui::PushStyleColor(ImGuiCol_ButtonHovered, s.bg_hover);
  ImGui::PushStyleColor(ImGuiCol_ButtonActive, s.bg_active);
  ImGui::PushStyleColor(ImGuiCol_Text, s.text);
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, s.radius);

  bool clicked = ImGui::Button(label);

  ImGui::PopStyleVar();
  ImGui::PopStyleColor(4);

  return clicked;
}

bool Button(const char *label, ButtonVariant variant) {
  ButtonStyle style = theme::GetButtonStyle(variant);
  return DrawButton(label, style);
}

namespace theme {

ButtonStyle GetButtonStyle(ButtonVariant variant) {
  using namespace ui::tokens::base;
  float scaled_radius = md * current_theme.scale;
  switch (variant) {
  case ButtonVariant::Primary:
    return {.bg = blue_600,
            .bg_hover = blue_700,
            .bg_active = blue_700,
            .text = neutral_200,
            .radius = scaled_radius};
  case ButtonVariant::Secondary:
    return {.bg = neutral_700,
            .bg_hover = neutral_900,
            .bg_active = neutral_900,
            .text = neutral_200,
            .radius = scaled_radius};
  case ButtonVariant::Danger:
    return {.bg = red_600,
            .bg_hover = red_700,
            .bg_active = red_700,
            .text = neutral_200,
            .radius = scaled_radius};
  case ButtonVariant::Success:
    return {.bg = green_600,
            .bg_hover = green_700,
            .bg_active = green_700,
            .text = neutral_200,
            .radius = scaled_radius};
  }
  return {}; // Default
}

} // namespace theme

} // namespace ui
