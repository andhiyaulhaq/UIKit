# Theme Scalability Plan

## Current Issues

The current theme system in `theme.cpp` and `theme.h` is not scalable for adding new components:

- The `Theme` struct contains hardcoded fields for each button variant (e.g., `button_primary`, `button_secondary`).
- `LoadDefaultTheme()` precomputes and sets these styles.
- `GetButtonStyle()` simply returns the precomputed style based on variant.
- To add a new component (e.g., Input), you must:
  - Define a new `InputStyle` struct.
  - Add `input_*` fields to the `Theme` struct.
  - Update `LoadDefaultTheme()` to initialize them.
  - Add a `GetInputStyle()` function with a switch statement.
- This approach violates the Open-Closed Principle: the `Theme` struct and related functions must be modified for each new component.

## Proposed Scalable Structure

To make the theme system scalable:

### 1. Simplify the Theme Struct

- Reduce `Theme` to only global settings that affect all components, e.g.:
  ```cpp
  struct Theme {
    float scale = 1.0f; // Global scale factor
  };
  ```
- Remove component-specific fields like `button_primary`, etc.

### 2. Compute Styles On-Demand

- Modify `GetButtonStyle(ButtonVariant variant)` to compute the style dynamically:
  ```cpp
  ButtonStyle GetButtonStyle(ButtonVariant variant) {
    using namespace ui::tokens::base;
    float scaled_radius = md * current_theme.scale;
    switch (variant) {
      case ButtonVariant::Primary:
        return {.bg = blue_600, .bg_hover = blue_700, .bg_active = blue_700, .text = neutral_200, .radius = scaled_radius};
      // ... other cases
    }
  }
  ```
- This eliminates the need to store precomputed styles in `Theme`.

### 3. Update LoadDefaultTheme()

- Simplify to only set global properties:
  ```cpp
  void LoadDefaultTheme() {
    current_theme.scale = 1.0f;
  }
  ```

### 4. Adding New Components

- For a new component (e.g., Input):
  - Define `InputStyle` struct and `InputVariant` enum in `theme.h` or a component-specific header.
  - Add `GetInputStyle(InputVariant variant)` function that computes the style similarly.
- No changes needed to `Theme` struct or `LoadDefaultTheme()`.

## Benefits

- **Scalability**: Adding new components doesn't require modifying core theme files.
- **Maintainability**: Styles are computed in one place per component.
- **Flexibility**: Easy to customize styles per variant without global state changes.
- **Performance**: Minimal impact since styles are simple structs.

## Implementation Steps

1. Modify `theme.h`: Update `Theme` struct, keep `ButtonStyle` and `ButtonVariant`.
2. Modify `theme.cpp`: Update `LoadDefaultTheme()` and `GetButtonStyle()`.
3. Test existing button functionality.
4. (Future) Add new components following the pattern.

## Mermaid Diagram

```mermaid
graph TD
    A[Theme] --> B[scale]
    C[ButtonStyle] --> D[GetButtonStyle(variant)]
    E[InputStyle] --> F[GetInputStyle(variant)]
    D --> B
    F --> B
    B --> G[Scaled Radius]
    H[Base Tokens] --> D
    H --> F
```
