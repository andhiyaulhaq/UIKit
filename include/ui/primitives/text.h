#pragma once
#include <string>

namespace ui {

// 1. Hierarchy Levels (Maps to your typography.h fonts)
enum class TextStyle {
  Title,    // Large Font (24pt)
  Subtitle, // Medium Font (18pt)
  Body,     // Regular Font (18pt or 14pt)
  Caption   // Small Font (12pt/14pt)
};

// 2. Semantic Colors
enum class TextColor {
  Normal,  // Standard White/Light Grey
  Muted,   // Greyed out (Secondary info)
  Primary, // Brand Color (Blue)
  Success, // Green
  Danger   // Red
};

// 3. The Component
// 'wrap': If true, text will wrap to the next line at the window edge.
void Text(const std::string &content, TextStyle style = TextStyle::Body,
          TextColor color = TextColor::Normal, bool wrap = true);

} // namespace ui
