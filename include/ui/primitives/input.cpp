#include "input.h"

// Include ImGui/Internal headers only here
#include "imgui.h"
// #include "imgui_internal.h" // Optional, if you need deep customization
// #include "../tokens/theme.h" // Your theme colors

namespace ui {

// -------------------------------------------------------------------------
// INTERNAL HELPER (Hidden from the header)
// -------------------------------------------------------------------------
struct InputTextCallback_UserData {
  std::string *Str;
};

static int InputTextCallback(ImGuiInputTextCallbackData *data) {
  if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
    auto *user_data = (InputTextCallback_UserData *)data->UserData;
    // Resize string to accommodate new text
    user_data->Str->resize(data->BufTextLen);
    data->Buf = (char *)user_data->Str->c_str();
  }
  return 0;
}

// -------------------------------------------------------------------------
// PUBLIC COMPONENT
// -------------------------------------------------------------------------
bool Input(const char *label, std::string &buffer, const char *hint,
           float width) {

  // 1. Layout
  if (width != 0.0f) {
    float w = (width < 0.0f) ? ImGui::GetContentRegionAvail().x : width;
    ImGui::SetNextItemWidth(w);
  }

  // 2. Styling
  ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 10));
  ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 4.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);

  // Colors (You could also pull these from your theme.h)
  ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
  ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.3f, 0.3f, 0.3f, 0.5f));
  ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0, 0, 0, 0));

  // 3. Render
  InputTextCallback_UserData user_data;
  user_data.Str = &buffer;

  // We use the ID "##" to hide the label text but keep the ID unique
  // If you want a visible label, remove the "##" logic below
  std::string id_label = "##" + std::string(label);

  bool changed = ImGui::InputTextWithHint(
      id_label.c_str(), hint ? hint : "", (char *)buffer.c_str(),
      buffer.capacity() + 1, ImGuiInputTextFlags_CallbackResize,
      InputTextCallback, &user_data);

  // 4. Cleanup
  ImGui::PopStyleColor(4);
  ImGui::PopStyleVar(3);

  return changed;
}
} // namespace ui
