#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Include glad before glfw
#include <glad/gl.h>

#include <GLFW/glfw3.h>

#include <stdio.h>

#include "ui/primitives/button.h"
#include "ui/tokens/theme.h"

void ShowButtons() {

  // 1. No extra args
  // Matches Master function. Uses defaults: Primary, Medium, {0,0}
  ui::Button("Save");

  // 2. Passing ImVec2
  // Matches the Inline Overload. Redirects to Master with: Primary, Medium,
  // {150,40}
  ui::Button("Submit", ImVec2(150, 40));
  ui::Button("Full Width", ImVec2(-1.0f, 40));

  // 3. Passing Variant
  // Matches Master function. Uses defaults for rest: Variant, Medium, {0,0}
  ui::Button("Primary", Primary);
  ImGui::SameLine();
  ui::Button("Secondary", Secondary);

  // Get the available width of the window/container
  float avail_width = ImGui::GetContentRegionAvail().x;

  // Get the standard spacing ImGui uses between items (usually 8px)
  float spacing = ImGui::GetStyle().ItemSpacing.x;

  // Calculate half width: (Total - Spacing) / 2
  float half_width = (avail_width - spacing) / 2.0f;

  ui::Button("Test1", ImVec2(half_width, 30));
  ImGui::SameLine();
  ui::Button("Test2", ImVec2(half_width, 30));

  // 4. Passing Variant + Size Category
  // Matches Master function.
  ui::Button("Delete", Danger, Small);
}

static void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main() {
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return 1;

  GLFWwindow *window =
      glfwCreateWindow(800, 600, "UI Kit - Minimal", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);

  if (!gladLoadGL(glfwGetProcAddress)) {
    fprintf(stderr, "Failed to initialize GLAD\n");
    return 1;
  }

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  ui::theme::LoadDefaultTheme();

  ImGui::StyleColorsDark();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 130");

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Minimal Example");

    ShowButtons();

    ImGui::End();

    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
