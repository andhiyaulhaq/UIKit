# UI Kit Restructuring Plan for Modularity and Scalability

## Analysis of Current Code

The original code had some modularity:

- Design tokens separated in `base/` (colors, radius).
- Theme aggregates tokens into component styles.
- Primitives use the global theme.

However, it was not as modular and scalable as shadcn/ui because:

- Tight coupling: Button directly accesses global `current_theme`.
- Limited variants: Only Primary and Secondary.
- No easy customization per component instance.
- Global state makes it hard to have multiple themes or scoped theming.

Shadcn/ui is modular through:

- Composable components with props for variants and custom styles.
- Design tokens as CSS variables for easy theming.
- No global dependencies; themes applied via context or props.

## Goal: Decouple Components from Global Theme

To make it properly structured and decoupled:

- Components should not depend on global state.
- Styles passed as parameters, allowing flexibility.
- Theme provides default styles via helper functions.

## Changes Made

### 1. Enhanced Design Tokens

- Added more colors: red_600/700, green_600/700 for danger and success variants.
- Kept existing neutral and blue colors.

### 2. Expanded Theme System

- Added `ButtonVariant` enum with Primary, Secondary, Danger, Success.
- Added `button_danger` and `button_success` styles to `Theme` struct.
- Updated `LoadDefaultTheme()` to initialize new styles.
- Added `GetButtonStyle(ButtonVariant)` function to retrieve styles by variant.

### 3. Decoupled Button Component

- Changed `Button` signature from `bool Button(const char *label, ButtonVariant variant)` to `bool Button(const char *label, const ButtonStyle &style)`.
- Removed direct access to `current_theme` in `button.cpp`.
- Removed `ButtonVariant` from `button.h` (moved to `theme.h`).
- `button.cpp` no longer includes `theme.h` directly (only through `button.h`).

### 4. Updated Usage

- In `main.cpp`, changed calls to `ui::Button("Primary", ui::theme::GetButtonStyle(ui::theme::ButtonVariant::Primary))`.
- This decouples the component from the theme, as the caller provides the style.

## Benefits Achieved

- **Modularity**: Components are self-contained, styles injected via parameters.
- **Scalability**: Easy to add more variants, sizes, or custom styles.
- **Decoupling**: Button doesn't know about theme globals; can be used with any style.
- **Flexibility**: Callers can override styles or use custom themes.
- **Similarity to shadcn**: Components take style props, themes provide defaults.

## Future Improvements

- Add size variants (small, medium, large) with different padding/radius.
- Implement a ThemeProvider for scoped theming.
- Add more components (Input, Text, etc.) following the same pattern.
- Support for custom themes beyond defaults.
