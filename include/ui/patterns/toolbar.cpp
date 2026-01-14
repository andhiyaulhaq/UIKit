// include/ui/patterns/toolbar.cpp
#include "ui/patterns/toolbar.h"
#include "ui/primitives/button.h"
#include <imgui.h>

namespace ui::patterns {

void Toolbar() {
  if (ui::primitives::Button("New")) {
  }
  ImGui::SameLine();
  if (ui::primitives::Button("Save")) {
  }
}

} // namespace ui::patterns
