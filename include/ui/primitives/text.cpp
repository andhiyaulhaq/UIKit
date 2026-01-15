#include "text.h"
#include "../tokens/base/typography.h" // Access your font pointers

namespace ui {

void Text(const std::string &content, TextStyle style, TextColor color,
          bool wrap) {

  // --- 1. Push Font ---
  bool fontPushed = false;
  ImFont *targetFont = nullptr;

  switch (style) {
  case TextStyle::Title:
    targetFont = tokens::base::font_large;
    break;
  case TextStyle::Subtitle:
    targetFont = tokens::base::font_medium;
    break; // Or bold variant if you have it
  case TextStyle::Caption:
    targetFont = tokens::base::font_small;
    break;
  case TextStyle::Body:
  default:
    targetFont = tokens::base::font_medium;
    break;
  }

  // Only push if the font was actually loaded successfully
  if (targetFont) {
    ImGui::PushFont(targetFont);
    fontPushed = true;
  }

  // --- 2. Push Color ---
  ImVec4 targetColor;
  switch (color) {
  case TextColor::Muted:
    targetColor = ImVec4(0.6f, 0.6f, 0.6f, 1.0f);
    break; // Grey
  case TextColor::Primary:
    targetColor = ImVec4(0.2f, 0.6f, 1.0f, 1.0f);
    break; // Blue
  case TextColor::Success:
    targetColor = ImVec4(0.4f, 1.0f, 0.4f, 1.0f);
    break; // Green
  case TextColor::Danger:
    targetColor = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);
    break; // Red
  case TextColor::Normal:
  default:
    targetColor = ImGui::GetStyle().Colors[ImGuiCol_Text];
    break;
  }

  ImGui::PushStyleColor(ImGuiCol_Text, targetColor);

  // --- 3. Render ---
  if (wrap) {
    ImGui::TextWrapped("%s", content.c_str());
  } else {
    ImGui::Text("%s", content.c_str());
  }

  // --- 4. Cleanup ---
  ImGui::PopStyleColor();
  if (fontPushed) {
    ImGui::PopFont();
  }
}
} // namespace ui
