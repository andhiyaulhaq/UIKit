// include/ui/primitives/button.cpp
#include "button.h"
#include <imgui.h>

namespace ui {

static bool DrawButton(const char *label, const theme::ButtonStyle &s) {
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

bool Button(const char *label, const theme::ButtonStyle &style) {
  return DrawButton(label, style);
}

} // namespace ui
