// include/ui/tokens/theme.cpp
#include "theme.h"
#include "base/colors.h"
#include "base/radius.h"

namespace ui::theme {

Theme current_theme;

void LoadDefaultTheme() { current_theme.scale = 1.0f; }

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

} // namespace ui::theme
