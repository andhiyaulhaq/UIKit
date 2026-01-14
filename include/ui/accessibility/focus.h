// include/ui/accessibility/focus.h
#pragma once
#include <imgui.h>

namespace ui::a11y {

inline void FocusOnAppear() {
  if (ImGui::IsWindowAppearing())
    ImGui::SetKeyboardFocusHere();
}

} // namespace ui::a11y
