// include/ui/layout/stack.h
#pragma once
#include <imgui.h>

namespace ui::layout {

inline void VStackBegin(float spacing = 0.0f) { ImGui::BeginGroup(); }

inline void VStackEnd() { ImGui::EndGroup(); }

} // namespace ui::layout
