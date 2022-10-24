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

/** This 'enum' is a list of all the macros used by the Model 100's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum {
  MACRO_VERSION_INFO,
  MACRO_ANY,
};


/** The Model 100's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The PROG key is special, since it is how you indicate to the board that you
  * want to flash the firmware. However, it can be remapped to a regular key.
  * When the keyboard boots, it first looks to see whether the PROG key is held
  * down; if it is, it simply awaits further flashing instructions. If it is
  * not, it continues loading the rest of the firmware and the keyboard
  * functions normally, with whatever binding you have set to PROG. More detail
  * here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum {
  LAYER_PRIMARY,
  LAYER_SHIFT,
  LAYER_FUNCTION,
  LAYER_CONTROL,
  LAYER_SUPER,
  LAYER_ALT,
  LAYER_MOUSE
};  // layers


/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// clang-format off

KEYMAPS(

  [LAYER_PRIMARY] = KEYMAP_STACKED
  (___,                 Key_1,              Key_2,              Key_3,              Key_4,              Key_5,              Key_PrintScreen,
   ___,                 Key_B,              Key_Y,              Key_O,              Key_U,              Key_Quote,          ___,
   Key_Tab,             Key_C,              Key_I,              Key_E,              Key_A,              Key_Comma,
   Key_Escape,          Key_G,              Key_X,              Key_J,              Key_K,              Key_Minus,          ___,
   MOD_LAYER_CONTROL,                       Key_Backspace,                          ___,                                    Key_Escape,
   MOD_LAYER_SHIFT,

   ___,                 Key_6,              Key_7,              Key_8,              Key_9,              Key_0,              ___,
   ___,                 Key_DblQuote,       Key_L,              Key_D,              Key_W,              Key_V,              Key_Z,
                        Key_Period,         Key_H,              Key_T,              Key_S,              Key_N,              Key_Q,
   ___,                 Key_Question,       Key_R,              Key_M,              Key_F,              Key_P,              ___,
   MOD_LAYER_SUPER,                         Key_Enter,                              Key_Spacebar,                           MOD_LAYER_ALT,
   ShiftToLayer(LAYER_FUNCTION)),

  [LAYER_SHIFT] = KEYMAP_STACKED
  (MOVE_PRIMARY,        ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                Key_LeftParen,      ___,
   ___,                 ___,                ___,                ___,                ___,                Key_Semicolon,
   ___,                 ___,                ___,                ___,                ___,                Key_Underscore,     ___,
   MOD_LAYER_CONTROL,                       ___,                                    ___,                                    ___,
   Key_LShift,

   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 Key_RightParen,     ___,                ___,                ___,                ___,                ___,
                        Key_Colon,          ___,                ___,                ___,                ___,                ___,
   ___,                 Key_Exclamation,    ___,                ___,                ___,                ___,                ___,
   Key_LGui,                                ___,                                    ___,                                    Key_LAlt,
   XXX),

  [LAYER_FUNCTION] = KEYMAP_STACKED
  (MOVE_PRIMARY,        ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 Key_Backtick,       Key_Pound,          Key_LessThan,       Key_GreaterThan,    Key_KeypadMultiply, ___,
   ___,                 Key_Equals,         Key_At,             Key_Slash,          Key_Ampersand,      Key_KeypadAdd,
   ___,                 Key_Tilde,          Key_Percent,        Key_Backslash,      Key_Pipe,           Key_KeypadSubtract, ___,
   Key_LCtrl,                               ___,                                    ___,                                    ___,
   Key_LShift,

   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
                        ___,                Key_LeftArrow,      Key_DownArrow,      Key_UpArrow,        Key_RightArrow,     ___,
   ___,                 ___,                ___,                ___,                ___,                ___,                ___,
   Key_LGui,                                ___,                                    ___,                                    Key_LAlt,
   XXX),

  [LAYER_CONTROL] = KEYMAP_STACKED
  (MOVE_PRIMARY,        ___,                ___,                ___,                ___,                ___,                ___,
   Key_H,               Key_Q,              Key_W,              Key_E,              Key_R,              Key_T,              ___,
   Key_P,               Key_A,              Key_S,              Key_D,              Key_F,              Key_G,
   ___,                 Key_Z,              Key_X,              Key_C,              Key_V,              Key_B,              ___,
   Key_LCtrl,                               ___,                                    ___,                                    ___,
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

  // SpaceCadet can turn your shifts into parens on tap, while keeping them as
  // Shifts when held. SpaceCadetConfig lets Chrysalis configure some aspects of
  // the plugin.
  SpaceCadet,
  SpaceCadetConfig,

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

  // The macros plugin adds support for macros
  Macros,

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

  // Turns LEDs off after a configurable amount of idle time.
  IdleLEDs,
  PersistentIdleLEDs,

  // Enables dynamic, Chrysalis-editable macros.
  DynamicMacros,

  // The FirmwareVersion plugin lets Chrysalis query the version of the firmware
  // programmatically.
  FirmwareVersion,

  // The LayerNames plugin allows Chrysalis to display - and edit - custom layer
  // names, to be shown instead of the default indexes.
  LayerNames,

  // Enables setting, saving (via Chrysalis), and restoring (on boot) the
  // default LED mode.
  DefaultLEDModeConfig,

  // Enables controlling (and saving) the brightness of the LEDs via Focus.
  LEDBrightnessConfig,

  // Enables the GeminiPR Stenography protocol. Unused by default, but with the
  // plugin enabled, it becomes configurable - and then usable - via Chrysalis.
  GeminiPR);

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