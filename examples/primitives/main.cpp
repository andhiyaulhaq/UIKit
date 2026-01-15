// =====================================================
// ImGui + GLFW + OpenGL headers
// =====================================================
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Include glad before GLFW
#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <stdio.h>
// #include <iostream>
// #include <string>

#ifdef _WIN32
#include <windows.h>
#endif

// Custom UI Headers (Preserved)
#include "ui/primitives/button.h"
#include "ui/tokens/theme.h"

// =====================================================
// VIEWMODEL
// =====================================================
struct KitViewModel {
  // The original code was stateless (just UI rendering),
  // but we keep this struct to adhere to the requested architecture.
  // If you add dynamic data (input fields, counters) later,
  // their state would go here.
};

// =====================================================
// APPLICATION CLASS (The Wrapper)
// =====================================================
class KitApp {
public:
  KitApp(int width, int height, const char *title) {
    initWindow(width, height, title);
    initImGui();
  }

  ~KitApp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    if (window)
      glfwDestroyWindow(window);
    glfwTerminate();
  }

  // Main Run Loop
  void Run() {
    if (!window)
      return;

    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();

      // Update Logic (None for this specific example)
      // vm.update();

      // Render
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();

      renderUI(); // Render the UI

      ImGui::Render();

      int w, h;
      glfwGetFramebufferSize(window, &w, &h);
      glViewport(0, 0, w, h);

      // Matches original clear color
      glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      glfwSwapBuffers(window);
    }
  }

private:
  GLFWwindow *window = nullptr;
  KitViewModel vm;

  // Static error callback needed for GLFW
  static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
  }

  void initWindow(int w, int h, const char *title) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
      return;

    // No version hints were in original code, but standardizing on GL 3.0+ is
    // safe If your original code relied on legacy GL, remove these hints.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //
    // Optional depending on platform

    window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (!window) {
      glfwTerminate();
      return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable VSync

    if (!gladLoadGL(glfwGetProcAddress)) {
      fprintf(stderr, "Failed to initialize GLAD\n");
    }
  }

  void initImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // -- Load Custom Theme (Preserved feature) --
    ui::theme::LoadDefaultTheme();

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
  }

  // This contains the logic from the original ShowButtons() function
  // This contains the logic from the original ShowButtons() function
  void renderUI() {
    // 1. Setup the window to fill the entire viewport
    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    // 2. Add flags to remove decorations (title bar, resize handle) and
    // movement
    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    // Optional: Remove window rounding to ensure it fits the corners perfectly
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

    // 3. Begin the window with the flags
    ImGui::Begin("Minimal Example", nullptr, window_flags);

    // --- Content (Buttons) ---

    // 1. No extra args
    ui::Button("Save");

    // 2. Passing ImVec2
    ui::Button("Submit", ImVec2(150, 40));
    ui::Button("Full Width", ImVec2(-1.0f, 40));

    // 3. Passing Variant
    ui::Button("Primary", Primary);
    ImGui::SameLine();
    ui::Button("Secondary", Secondary);

    // Get the available width of the window/container
    float avail_width = ImGui::GetContentRegionAvail().x;
    float spacing = ImGui::GetStyle().ItemSpacing.x;
    float half_width = (avail_width - spacing) / 2.0f;

    ui::Button("Test1", ImVec2(half_width, 30));
    ImGui::SameLine();
    ui::Button("Test2", ImVec2(half_width, 30));

    // 4. Passing Variant + Size Category
    ui::Button("Delete", Danger, Small);

    ImGui::End();

    // Pop the style var we pushed earlier
    ImGui::PopStyleVar();
  }
};

// =====================================================
// ENTRY POINT
// =====================================================

int main(int argc, char **argv) {
  // 1. Create App
  KitApp app(800, 600, "UI Kit - Minimal");

  // 2. Run App
  app.Run();

  // 3. Cleanup happens automatically when 'app' goes out of scope
  return 0;
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
  return main(__argc, __argv);
}
#endif
