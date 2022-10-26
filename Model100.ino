// -*- mode: c++ -*-
// Copyright 2016-2022 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 100's firmware
 */

// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for storing the keymap in EEPROM
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"

// Support for communicating with the host via a simple Serial protocol
#include "Kaleidoscope-FocusSerial.h"

// Support for querying the firmware version via Focus
#include "Kaleidoscope-FirmwareVersion.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for LED modes that set all LEDs to a single color
#include "Kaleidoscope-LED-ActiveLayerColor.h"

// Support for shared palettes for other plugins, like Colormap below
#include "Kaleidoscope-LED-Palette-Theme.h"

// Support for an LED mode that lets one configure per-layer color maps
#include "Kaleidoscope-Colormap.h"

// Support for turning the LEDs off after a certain amount of time
#include "Kaleidoscope-IdleLEDs.h"

// Support for setting and saving the default LED mode
#include "Kaleidoscope-DefaultLEDModeConfig.h"

// Support for changing the brightness of the LEDs
#include "Kaleidoscope-LEDBrightnessConfig.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-HardwareTestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for magic combos (key chords that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"

// Support for secondary actions on keys
#include "Kaleidoscope-Qukeys.h"

// Support for one-shot modifiers and layer keys
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"

// Support for dynamic, Chrysalis-editable macros
#include "Kaleidoscope-DynamicMacros.h"

// Support for SpaceCadet keys
#include "Kaleidoscope-SpaceCadet.h"

// Support for editable layer names
#include "Kaleidoscope-LayerNames.h"

// Support for the GeminiPR Stenography protocol
#include "Kaleidoscope-Steno.h"

// Custom aliases for my sketches
#include "custom_alias.h"
#include "const.h"
#include "Lilith-CharShift.h"

/* NamedCharShift setup
 */
NCS_KEYS(
  (P_L_1_5,           Key_Quote,            Key_LeftParen),
  (P_L_2_5,           Key_Comma,            Key_Semicolon),
  (P_L_3_5,           Key_Minus,            Key_Underscore),
  (P_R_1_5,           Key_DblQuote,         Key_RightParen),
  (P_R_2_5,           Key_Period,           Key_Colon),
  (P_R_3_5,           Key_Question,         Key_Exclamation),
  (KEY_1_F1,          Key_1,                Key_F1),
  (KEY_2_F2,          Key_2,                Key_F2),
  (KEY_3_F3,          Key_3,                Key_F3),
  (KEY_4_F4,          Key_4,                Key_F4),
  (KEY_5_F5,          Key_5,                Key_F5),
  (KEY_6_F6,          Key_6,                Key_F6),
  (KEY_7_F7,          Key_7,                Key_F7),
  (KEY_8_F8,          Key_8,                Key_F8),
  (KEY_9_F9,          Key_9,                Key_F9),
  (KEY_0_F10,         Key_0,                Key_F10)
)



/* Macros
 */
enum {
  MACRO_VERSION_INFO,
  MACRO_ANY,
};

/* Layers
 */
enum {
  LAYER_PRIMARY,
  LAYER_FUNCTION,
  LAYER_CONTROL,
  LAYER_SUPER,
  LAYER_ALT,
  LAYER_MOUSE,
  LAYER_HUB,

  // Pseudo layer
  FIRMWARE_LAYER_COUNT
};  // layers


/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// clang-format off

KEYMAPS(

  [LAYER_PRIMARY] = KEYMAP_STACKED
  (___,                 NCS(KEY_1_F1),      NCS(KEY_2_F2),      NCS(KEY_3_F3),      NCS(KEY_4_F4),      NCS(KEY_5_F5),      Key_PrintScreen,
   ___,                 Key_B,              Key_Y,              Key_O,              Key_U,              NCS(P_L_1_5),       ___,
   Key_Tab,             Key_C,              Key_I,              Key_E,              Key_A,              NCS(P_L_2_5),
   Key_Escape,          Key_G,              Key_X,              Key_J,              Key_K,              NCS(P_L_3_5),       ___,
   MOD_LAYER_CONTROL,                       Key_Backspace,                          ___,                                    Key_Escape,
   Key_LShift,

   ___,                 NCS(KEY_6_F6),      NCS(KEY_7_F7),      NCS(KEY_8_F8),      NCS(KEY_9_F9),      NCS(KEY_0_F10),     ___,
   ___,                 NCS(P_R_1_5),       Key_L,              Key_D,              Key_W,              Key_V,              Key_Z,
                        NCS(P_R_2_5),       Key_H,              Key_T,              Key_S,              Key_N,              Key_Q,
   ___,                 NCS(P_R_3_5),       Key_R,              Key_M,              Key_F,              Key_P,              ___,
   MOD_LAYER_SUPER,                         Key_Enter,                              Key_Spacebar,                           MOD_LAYER_ALT,
   ShiftToLayer(LAYER_FUNCTION)),

  [LAYER_FUNCTION] = KEYMAP_STACKED
  (MOVE_PRIMARY,        ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 Key_Backtick,       Key_Pound,          Key_Carat,          Key_Dollar,         Key_KeypadMultiply, ___,
   ___,                 Key_Equals,         Key_At,             Key_Slash,          Key_Ampersand,      Key_KeypadAdd,
   ___,                 Key_Tilde,          Key_Percent,        Key_Backslash,      Key_Pipe,           Key_KeypadSubtract, ___,
   Key_LCtrl,                               ___,                                    ___,                                    ___,
   Key_LShift,

   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                Key_LSquareBracket, Key_RSquareBracket, ___,                ___,                ___,
                        ___,                Key_LeftArrow,      Key_DownArrow,      Key_UpArrow,        Key_RightArrow,     ___,
   ___,                 ___,                Key_LCurlyBracket,  Key_RCurlyBracket,  Key_LessThan,       Key_GreaterThan,    ___,
   Key_LGui,                                ___,                                    ___,                                    Key_LAlt,
   XXX),

  [LAYER_CONTROL] = KEYMAP_STACKED
  (MOVE_PRIMARY,        ___,                ___,                ___,                ___,                ___,                ___,
   Key_H,               Key_Q,              Key_W,              Key_E,              Key_R,              Key_T,              ___,
   Key_P,               Key_A,              Key_S,              Key_D,              Key_F,              Key_G,
   ___,                 Key_Z,              Key_X,              Key_C,              Key_V,              Key_B,              ___,
   MOD_LAYER_CONTROL,                       ___,                                    ___,                                    ___,
   Key_LShift,

   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
                        ___,                Key_LeftArrow,      Key_DownArrow,      Key_UpArrow,        Key_RightArrow,     ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   Key_LGui,                                ___,                                    ___,                                    Key_LAlt,
   XXX),

  [LAYER_SUPER] = KEYMAP_STACKED
  (MOVE_PRIMARY,        ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   Key_LCtrl,                               ___,                                    ___,                                    ___,
   Key_LShift,

   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
                        ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   Key_LGui,                                ___,                                    ___,                                    Key_LAlt,
   XXX),

  [LAYER_ALT] = KEYMAP_STACKED
  (MOVE_PRIMARY,        ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   Key_LCtrl,                               ___,                                    ___,                                    ___,
   Key_LShift,

   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
                        ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   Key_LGui,                                ___,                                    ___,                                    Key_LAlt,
   XXX),

  [LAYER_MOUSE] = KEYMAP_STACKED
  (MOVE_PRIMARY,        ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   Key_LCtrl,                               ___,                                    ___,                                    ___,
   Key_LShift,

   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
                        ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   Key_LGui,                                ___,                                    ___,                                    Key_LAlt,
   XXX),

) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// clang-format on

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t key_state) {
  if (keyToggledOn(key_state)) {
    Macros.type(PSTR("Keyboardio Model 100 - Firmware version "));
    Macros.type(PSTR(KALEIDOSCOPE_FIRMWARE_VERSION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    event.key.setKeyCode(Key_A.getKeyCode() + (uint8_t)(millis() % 36));
    event.key.setFlags(0);
  }
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  switch (macro_id) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(event.state);
    break;

  case MACRO_ANY:
    anyKeyMacro(event);
    break;
  }
  return MACRO_NONE;
}

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    LEDControl.disable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.enable();
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/** This 'enum' is a list of all the magic combos used by the Model 100's
 * firmware The names aren't particularly important. What is important is that
 * each is unique.
 *
 * These are the names of your magic combos. They will be used by the
 * `USE_MAGIC_COMBOS` call below.
 */
enum {
  // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
  // mode.
  COMBO_TOGGLE_NKRO_MODE,
  // Enter test mode
  COMBO_ENTER_TEST_MODE
};

/** Wrappers, to be used by MagicCombo. **/

/**
 * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
 * a function with an unused argument, to match what MagicCombo expects.
 */
static void toggleKeyboardProtocol(uint8_t combo_index) {
  USBQuirks.toggleKeyboardProtocol();
}

/**
 * Toggles between using the built-in keymap, and the EEPROM-stored one.
 */
static void toggleKeymapSource(uint8_t combo_index) {
  if (Layer.getKey == Layer.getKeyFromPROGMEM) {
    Layer.getKey = EEPROMKeymap.getKey;
  } else {
    Layer.getKey = Layer.getKeyFromPROGMEM;
  }
}

/**
 *  This enters the hardware test mode
 */
static void enterHardwareTestMode(uint8_t combo_index) {
  HardwareTestMode.runTests();
}


/** Magic combo list, a list of key combo and action pairs the firmware should
 * recognise.
 */
USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
                  // Left Fn + Esc + Shift
                  .keys = {R3C6, R2C6, R3C7}},
                 {.action = enterHardwareTestMode,
                  // Left Fn + Prog + LED
                  .keys = {R3C6, R0C0, R0C6}},
                 {.action = toggleKeymapSource,
                  // Left Fn + Prog + Shift
                  .keys = {R3C6, R0C0, R3C7}});

// First, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the
  // left Fn button at the same time.
  HardwareTestMode,

  // LEDControl provides support for other LED modes
  LEDControl,

  // LEDActiveLayerColorEffect sets the color based on the active layer
  LEDActiveLayerColorEffect,

  // The LED Palette Theme plugin provides a shared palette for other plugins,
  // like Colormap below
  LEDPaletteTheme,

  // The Colormap effect makes it possible to set up per-layer colormaps
  ColormapEffect,

  // Turns LEDs off after a configurable amount of idle time.
  IdleLEDs,

  // The macros plugin adds support for macros
  Macros,

  // SpaceCadet can turn your shifts into parens on tap, while keeping them as
  // Shifts when held. SpaceCadetConfig lets Chrysalis configure some aspects of
  // the plugin.
  SpaceCadet,
  SpaceCadetConfig,

  // Char shift
  CharShift,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  // The MouseKeysConfig plugin lets Chrysalis configure some aspects of the
  // plugin.
  MouseKeys,
  MouseKeysConfig,

  // The HostPowerManagement plugin allows us to turn LEDs off when then host
  // goes to sleep, and resume them when it wakes up.
  HostPowerManagement,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo,

  // The USBQuirks plugin lets you do some things with USB that we aren't
  // comfortable - or able - to do automatically, but can be useful
  // nevertheless. Such as toggling the key report protocol between Boot (used
  // by BIOSes) and Report (NKRO).
  USBQuirks,

  // The Qukeys plugin enables the "Secondary action" functionality in
  // Chrysalis. Keys with secondary actions will have their primary action
  // performed when tapped, but the secondary action when held.
  Qukeys,

  // Enables the "Sticky" behavior for modifiers, and the "Layer shift when
  // held" functionality for layer keys.
  OneShot,
  OneShotConfig,
  EscapeOneShot,
  EscapeOneShotConfig,

  // The FirmwareVersion plugin lets Chrysalis query the version of the firmware
  // programmatically.
  FirmwareVersion);

/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  // Setup the layer colors
  static const cRGB layerColormap[] PROGMEM = {
    HRGB(0xBD05F2), // Primary
    HRGB(0x540695), // Shift
    HRGB(0x069531), // Function
    HRGB(0x0300FF), // Control
    HRGB(0x00A4B5), // Super
    HRGB(0x76462A), // Alt
    HRGB(0xAAA6CA), // Mouse
    };

  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // To make the keymap editable without flashing new firmware, we store
  // additional layers in EEPROM. For now, we reserve space for eight layers. If
  // one wants to use these layers, just set the default layer to one in EEPROM,
  // by using the `settings.defaultLayer` Focus command, or by using the
  // `keymap.onlyCustom` command to use EEPROM layers only.
  // EEPROMKeymap.setup(16);

  // We need to tell the Colormap plugin how many layers we want to have custom
  // maps for. To make things simple, we set it to eight layers, which is how
  // many editable layers we have (see above).
  // ColormapEffect.max_layers(16 + FIRMWARE_LAYER_COUNT);

  // Set the action key the test mode should listen for to Left Fn
  HardwareTestMode.setActionKey(R3C6);

  // To avoid any surprises, SpaceCadet is turned off by default. However, it
  // can be permanently enabled via Chrysalis, so we should only disable it if
  // no configuration exists.
  SpaceCadetConfig.disableSpaceCadetIfUnconfigured();

  LEDActiveLayerColorEffect.setColormap(layerColormap);

  Layer.move(LAYER_PRIMARY);
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
