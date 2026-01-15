// =====================================================
// ImGui + GLFW + OpenGL headers
// =====================================================
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>

// GLAD must be included BEFORE GLFW to initialize OpenGL function pointers
// correctly
#include <glad/gl.h>

#include <GLFW/glfw3.h>

#ifdef _WIN32
#include <windows.h>
#endif

// Custom UI Headers (Your component library)
#include "ui/primitives/button.h"
#include "ui/primitives/input.h"
#include "ui/tokens/theme.h"

// =====================================================
// VIEWMODEL
// =====================================================
struct KitViewModel {
  // This struct is intended to hold the application state (variables, flags,
  // data). Keeping state separate from the rendering logic (KitApp) follows the
  // MVVM pattern.
  std::string username;
  std::string email;
  std::string outputMessage;
};

// =====================================================
// APPLICATION CLASS
// =====================================================
class KitApp {
public:
  KitApp(int width, int height, const char *title) {
    initWindow(width, height, title);
    initImGui();
  }

  // Destructor: Handles the cleanup of ImGui, OpenGL, and GLFW resources
  // ensuring no memory leaks when the app closes.
  ~KitApp() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    if (window)
      glfwDestroyWindow(window);
    glfwTerminate();
  }

  // Main Application Loop
  void Run() {
    if (!window)
      return;

    // Standard Game/App Loop
    while (!glfwWindowShouldClose(window)) {
      // Poll and process events (keyboard, mouse, window resize, etc.)
      glfwPollEvents();

      // We call Draw() explicitly here.
      // This is separated into its own function so it can ALSO be called
      // from the window_refresh_callback during resizing.
      Draw();
    }
  }

private:
  GLFWwindow *window = nullptr;
  KitViewModel vm;

  // Standard GLFW error handling
  static void glfw_error_callback(int error, const char *description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
  }

  // ---------------------------------------------------------
  // RESIZE HANDLING EXPLANATION:
  // On Windows, the operating system blocks the main thread while the user
  // is resizing or dragging the window (the modal loop). This pauses the
  // 'Run()' loop above, causing the UI to freeze until the mouse is released.
  //
  // To fix this, we hook into the 'WindowRefreshCallback', which fires
  // continuously *during* the resize event, allowing us to force a redraw.
  // ---------------------------------------------------------
  static void window_refresh_callback(GLFWwindow *window) {
    // We cannot access non-static member functions (like app->Draw()) directly
    // from a static C-style callback.
    // We retrieve the "User Pointer" (which we stored in initWindow) to get
    // the specific instance of our KitApp class.
    KitApp *app = reinterpret_cast<KitApp *>(glfwGetWindowUserPointer(window));

    if (app) {
      app->Draw(); // Force a render frame immediately
    }
  }

  void initWindow(int w, int h, const char *title) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
      return;

    // Set OpenGL version to 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (!window) {
      glfwTerminate();
      return;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable V-Sync to prevent screen tearing

    if (!gladLoadGL(glfwGetProcAddress)) {
      fprintf(stderr, "Failed to initialize GLAD\n");
    }

    // ---------------------------------------------------------
    // LINKING C++ CLASS TO C CALLBACKS
    // ---------------------------------------------------------
    // 1. Store the 'this' pointer inside the GLFW window structure.
    //    This allows us to retrieve the class instance in static callbacks.
    glfwSetWindowUserPointer(window, this);

    // 2. Register the refresh callback to handle smoother resizing on Windows.
    glfwSetWindowRefreshCallback(window, window_refresh_callback);
  }

  void initImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // Load custom fonts and colors
    ui::theme::LoadDefaultTheme();
    ImGui::StyleColorsDark();

    // Initialize platform and renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
  }

  // ---------------------------------------------------------
  // THE RENDERING PIPELINE
  // ---------------------------------------------------------
  void Draw() {
    // 1. Start the ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 2. Define the UI layout (windows, buttons, text)
    renderUI();

    // 3. Finalize ImGui draw data
    ImGui::Render();

    // 4. Clear the OpenGL buffer (Background Color)
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    glViewport(0, 0, w, h);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark grey background
    glClear(GL_COLOR_BUFFER_BIT);

    // 5. Render ImGui draw data over the OpenGL background
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // 6. Swap the back buffer to the front (display the frame)
    glfwSwapBuffers(window);
  }

  // ---------------------------------------------------------
  // UI LAYOUT DEFINITION
  // ---------------------------------------------------------
  void renderUI() {
    // To make the UI "Responsive" and fill the whole window like a web app:
    // We grab the main viewport (the OS window dimensions).
    const ImGuiViewport *viewport = ImGui::GetMainViewport();

    // Force the ImGui window to match the position and size of the OS window.
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    // Configure flags to remove standard window chrome:
    // - NoDecoration: Hides Title bar, close button, collapse button.
    // - NoMove: User cannot drag the window contents (it's fixed to the frame).
    // - NoResize: User cannot resize the internal ImGui window (it matches OS
    // window).
    ImGuiWindowFlags window_flags =
        ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoBringToFrontOnFocus;

    // Remove window rounding so the UI fits perfectly into the corners.
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

    ImGui::Begin("Minimal Example", nullptr, window_flags);

    // --- Content Rendering ---

    // Example 1: Standard Button
    ui::Button("Save");

    // Example 2: Sized Buttons
    ui::Button("Submit", ImVec2(150, 40));
    ui::Button("Full Width",
               ImVec2(-1.0f, 40)); // -1.0f width means "Span available width"

    // Example 3: Themed Buttons (Primary/Secondary)
    ui::Button("Primary", Primary);
    ImGui::SameLine(); // Places the next element on the same horizontal line
    ui::Button("Secondary", Secondary);

    // Example 4: Responsive Grid Calculation
    float avail_width = ImGui::GetContentRegionAvail().x;
    float spacing = ImGui::GetStyle().ItemSpacing.x;
    // Calculate 50% width minus half the spacing for a perfect 2-column split
    float half_width = (avail_width - spacing) / 2.0f;

    ui::Button("Test1", ImVec2(half_width, 30));
    ImGui::SameLine();
    ui::Button("Test2", ImVec2(half_width, 30));

    // Example 5: Variant + Size
    ui::Button("Delete", Danger, Small);

    // --- TITLE ---
    ImGui::SetWindowFontScale(1.5f);
    ImGui::Text("User Registration");
    ImGui::SetWindowFontScale(1.0f);
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();

    // --- INPUTS ---
    // Using our new C++ friendly wrapper
    ui::Input("##User", vm.username, "Enter Username...");
    ImGui::Spacing();

    ui::Input("##Email", vm.email, "Enter Email Address...");
    ImGui::Spacing();

    // --- ACTIONS ---
    const char *btnLabel = "Create Account";

    // 1. Calculate a "comfortable" width dynamically
    // We use the text size plus standard FramePadding (multiplied by 4 for a
    // nice wide look)
    ImVec2 textSize = ImGui::CalcTextSize(btnLabel);
    ImGuiStyle &style = ImGui::GetStyle();

    // Using style.FramePadding.x ensures consistency with other buttons.
    // * 40.0f gives it "breathing room" on both sides.
    float dynamicBtnWidth = textSize.x + (style.FramePadding.x * 40.0f);

    // 2. Calculate proper Right Alignment
    // GetContentRegionAvail().x gives us the total width available on this
    // line. We simply add it to the current cursor X, then subtract our button
    // width.
    float alignX = ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x -
                   dynamicBtnWidth;

    // 3. Apply position
    if (alignX > ImGui::GetCursorPosX()) {
      ImGui::SetCursorPosX(alignX);
    }

    // 4. Draw Button
    // We pass the exact calculated width so the button renders exactly where we
    // planned
    if (ui::Button(btnLabel, ImVec2(dynamicBtnWidth, 0))) {
      vm.outputMessage = "Created user: " + vm.username;
    }

    // --- FEEDBACK ---
    if (!vm.outputMessage.empty()) {
      ImGui::Spacing();
      ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s",
                         vm.outputMessage.c_str());
    }

    ImGui::End();

    // Always pop style variables to avoid affecting other windows/frames
    ImGui::PopStyleVar();
  }
};

int main(int argc, char **argv) {
  // Initialize the App
  KitApp app(800, 600, "UI Kit - Minimal");

  // Enter the infinite loop
  app.Run();

  return 0;
}

#ifdef _WIN32
// Standard Windows entry point
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
  return main(__argc, __argv);
}
#endif
