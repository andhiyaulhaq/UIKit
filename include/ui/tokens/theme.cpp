// include/ui/tokens/theme.cpp
#include "theme.h"
#include "../tokens/base/typography.h"
#include <imgui.h>

namespace ui::theme {

Theme current_theme;

void LoadFonts() {
  ImGuiIO &io = ImGui::GetIO();
  // Load fonts from file with different sizes
  // If font files are not found, falls back to default
  ui::tokens::base::font_small = io.Fonts->AddFontFromFileTTF(
      ui::tokens::base::font_family_regular.c_str(),
      ui::tokens::base::font_size_small);
  if (!ui::tokens::base::font_small) {
    // Fallback to default
    ImFontConfig config;
    config.SizePixels = ui::tokens::base::font_size_small;
    ui::tokens::base::font_small = io.Fonts->AddFontDefault(&config);
  }

  ui::tokens::base::font_medium = io.Fonts->AddFontFromFileTTF(
      ui::tokens::base::font_family_regular.c_str(),
      ui::tokens::base::font_size_medium);
  if (!ui::tokens::base::font_medium) {
    ImFontConfig config;
    config.SizePixels = ui::tokens::base::font_size_medium;
    ui::tokens::base::font_medium = io.Fonts->AddFontDefault(&config);
  }

  ui::tokens::base::font_large = io.Fonts->AddFontFromFileTTF(
      ui::tokens::base::font_family_regular.c_str(),
      ui::tokens::base::font_size_large);
  if (!ui::tokens::base::font_large) {
    ImFontConfig config;
    config.SizePixels = ui::tokens::base::font_size_large;
    ui::tokens::base::font_large = io.Fonts->AddFontDefault(&config);
  }
}

void LoadDefaultTheme() {
  current_theme.scale = 1.0f;
  LoadFonts();
}

} // namespace ui::theme
