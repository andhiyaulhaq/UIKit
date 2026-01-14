// include/ui/core/id.h
#pragma once
#include <imgui.h>

namespace ui::core {

struct ScopedID {
  ScopedID(const void *ptr) { ImGui::PushID(ptr); }
  ~ScopedID() { ImGui::PopID(); }
};

} // namespace ui::core
