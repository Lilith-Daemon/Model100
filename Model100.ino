/* -*- mode: c++ -*-
 * Keyboardio Model100 Custom Firmware
 * Copyright (C) 2022 Lilith Daemon
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */

// Kaleidoscope
#include "Kaleidoscope.h"

// Kaleidoscope plugins
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-LED-ActiveLayerColor.h"
#include "Kaleidoscope-LED-Palette-Theme.h"
#include "Kaleidoscope-Colormap.h"

#include "Kaleidoscope-MouseKeys.h"

#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-DynamicMacros.h"

#include "Kaleidoscope-MagicCombo.h"
#include "Kaleidoscope-HardwareTestMode.h"
#include "Kaleidoscope-USB-Quirks.h"

#include "Kaleidoscope-HostPowerManagement.h"
#include "Kaleidoscope-IdleLEDs.h"


// My plugins
#include "Lilith-CharShift.h"
#include "Lilith-LED-Manager.h"

// Constant values for my sketch
#include "headers/const.h"

// Custom aliases for my sketches
#include "headers/custom_alias.h"

// Magic combos
#include "headers/magic_combos.h"

// Power management
#include "headers/power_management.h"



// Layers
enum {
  // Firmware layers
  LAYER_PRIMARY,
  LAYER_FUNCTION,
  LAYER_CONTROL,
  LAYER_SUPER,
  LAYER_ALT,
  LAYER_MOUSE,
  LAYER_HUB,

  // Pseudo layer
  FIRMWARE_LAYER_COUNT,

  // EEPROM layers
  EEPROM_LAYER_01 = FIRMWARE_LAYER_COUNT,
  EEPROM_LAYER_02,
  EEPROM_LAYER_03,
  EEPROM_LAYER_04,
  EEPROM_LAYER_05,
  EEPROM_LAYER_06,
  EEPROM_LAYER_07,
  EEPROM_LAYER_08,
  EEPROM_LAYER_09,
  EEPROM_LAYER_10,
  EEPROM_LAYER_11,
  EEPROM_LAYER_12,
  EEPROM_LAYER_13,
  EEPROM_LAYER_14,
  EEPROM_LAYER_15,
  EEPROM_LAYER_16,
  EEPROM_LAYER_17,
  EEPROM_LAYER_18,
  EEPROM_LAYER_19,
  EEPROM_LAYER_20,

  // Pseudo layer
  EEPROM_LAYER_END_MARKER,

  // Layer Aliases
  LAYER_RPG_MAKER_REBORN = EEPROM_LAYER_01
};  // layers

#define TOTAL_LAYERS FIRMWARE_LAYER_COUNT + EEPROM_LAYER_COUNT


// Disable clang formatter for NCS, KEYMAPS, and ColorMap
// clang-format off


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
  (KEY_0_F10,         Key_0,                Key_F10),
  (KEY_ESC_HUB,       Key_Escape,           ShiftToLayer(LAYER_HUB))
)

KEYMAPS(

  [LAYER_PRIMARY] = KEYMAP_STACKED
  (___,                 NCS(KEY_1_F1),      NCS(KEY_2_F2),      NCS(KEY_3_F3),      NCS(KEY_4_F4),      NCS(KEY_5_F5),      Key_PrintScreen,
   ___,                 Key_B,              Key_Y,              Key_O,              Key_U,              NCS(P_L_1_5),       ___,
   Key_Tab,             Key_C,              Key_I,              Key_E,              Key_A,              NCS(P_L_2_5),
   Key_Escape,          Key_G,              Key_X,              Key_J,              Key_K,              NCS(P_L_3_5),       ___,
   MOD_LAYER_CONTROL,                       Key_Backspace,                          LockLayer(LAYER_MOUSE),                 NCS(KEY_ESC_HUB),
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
  (MOVE_PRIMARY,        XXX,                XXX,                XXX,                XXX,                XXX,                XXX,
   XXX,                 XXX,                Key_mouseUpL,       Key_mouseUp,        Key_mouseUpR,       XXX,                XXX,
   XXX,                 MOVE_PRIMARY,       Key_mouseL,         Key_mouseDn,        Key_mouseR,         XXX,
   XXX,                 XXX,                Key_mouseDnL,       Key_mouseDn,        Key_mouseDnR,       XXX,                XXX,
   MOD_LAYER_CONTROL,                       Key_mouseBtnL,                          Key_mouseBtnR,                          Key_mouseBtnM,
   Key_LShift,

   XXX,                 XXX,                XXX,                XXX,                XXX,                XXX,                XXX,
   XXX,                 XXX,                Key_mouseWarpNW,    Key_mouseWarpN,     Key_mouseWarpNE,    Key_mouseWarpEnd,   XXX,
                        XXX,                Key_mouseWarpW,     Key_mouseWarpIn,    Key_mouseWarpE,     Key_mouseWarpEnd,   XXX,
   XXX,                 XXX,                Key_mouseWarpSW,    Key_mouseWarpS,     Key_mouseWarpSE,    Key_mouseWarpEnd,   XXX,
   Key_mouseScrollL,                        Key_mouseScrollUp,                      Key_mouseScrollDn,                      Key_mouseScrollR,
   Key_LCtrl),

  [LAYER_HUB] = KEYMAP_STACKED
  (MOVE_PRIMARY,        LOCK_TO_EEPROM(13), LOCK_TO_EEPROM(14), LOCK_TO_EEPROM(15), LOCK_TO_EEPROM(16), LOCK_TO_EEPROM(17), XXX,
   XXX,                 LOCK_TO_EEPROM(01), LOCK_TO_EEPROM(02), LOCK_TO_EEPROM(03), LOCK_TO_EEPROM(04), LOCK_TO_EEPROM(18), XXX,
   XXX,                 LOCK_TO_EEPROM(05), LOCK_TO_EEPROM(06), LOCK_TO_EEPROM(07), LOCK_TO_EEPROM(08), LOCK_TO_EEPROM(19),
   XXX,                 LOCK_TO_EEPROM(09), LOCK_TO_EEPROM(10), LOCK_TO_EEPROM(11), LOCK_TO_EEPROM(12), LOCK_TO_EEPROM(20), XXX,
   XXX,                                     XXX,                                    XXX,                                    XXX,
   XXX,

   XXX,                 XXX,                XXX,                XXX,                XXX,                XXX,                XXX,
   XXX,                 XXX,                XXX,                XXX,                XXX,                XXX,                XXX,
                        XXX,                XXX,                XXX,                XXX,                XXX,                XXX,
   XXX,                 XXX,                XXX,                XXX,                XXX,                XXX,                XXX,
   XXX,                                     XXX,                                    XXX,                                    XXX,
   XXX),

  [LAYER_RPG_MAKER_REBORN] = KEYMAP_STACKED
   (MOVE_PRIMARY,       XXX,                XXX,                XXX,                XXX,                XXX,                Key_F12,
   XXX,                 XXX,                Key_Q,              Key_UpArrow,        Key_W,              XXX,                XXX,
   XXX,                 Key_X,              Key_LArrow,         Key_DnArrow,        Key_RArrow,         XXX,
   XXX,                 XXX,                XXX,                XXX,                XXX,                XXX,                XXX,
   Key_D,                                   Key_Enter,                              Key_S,                                  Key_A,
   Key_LShift,
   XXX,                 XXX,                XXX,                XXX,                XXX,                XXX,                XXX,
   XXX,                 XXX,                XXX,                XXX,                XXX,                XXX,                XXX,
                        XXX,                XXX,                XXX,                XXX,                XXX,                XXX,
   XXX,                 XXX,                XXX,                XXX,                XXX,                XXX,                XXX,
   XXX,                                     XXX,                                    XXX,                                    XXX,
   XXX),

  [EEPROM_LAYER_02] = LAYER_BLANK,
  [EEPROM_LAYER_03] = LAYER_BLANK,
  [EEPROM_LAYER_04] = LAYER_BLANK,
  [EEPROM_LAYER_05] = LAYER_BLANK,
  [EEPROM_LAYER_06] = LAYER_BLANK,
  [EEPROM_LAYER_07] = LAYER_BLANK,
  [EEPROM_LAYER_08] = LAYER_BLANK,
  [EEPROM_LAYER_09] = LAYER_BLANK,
  [EEPROM_LAYER_10] = LAYER_BLANK,
  [EEPROM_LAYER_11] = LAYER_BLANK,
  [EEPROM_LAYER_12] = LAYER_BLANK,
  [EEPROM_LAYER_13] = LAYER_BLANK,
  [EEPROM_LAYER_14] = LAYER_BLANK,
  [EEPROM_LAYER_15] = LAYER_BLANK,
  [EEPROM_LAYER_16] = LAYER_BLANK,
  [EEPROM_LAYER_17] = LAYER_BLANK,
  [EEPROM_LAYER_18] = LAYER_BLANK,
  [EEPROM_LAYER_19] = LAYER_BLANK,
  [EEPROM_LAYER_20] = LAYER_BLANK

) // KEYMAPS(

// Enable clang formatter again
// clang-format on

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  switch (macro_id) {
  }
  return MACRO_NONE;
}


KALEIDOSCOPE_INIT_PLUGINS(
  // Support for managing the keymap via EEPROM
  EEPROMSettings, EEPROMKeymap,

  // Focus plugins
  Focus, FocusSettingsCommand, FocusEEPROMCommand,

  // LED plugins
  LEDControl, LEDActiveLayerColorEffect, LEDPaletteTheme, ColormapEffect, LEDManager,

  // Support for macros
  Macros, DynamicMacros,

  // Named charshift support
  CharShift,

  // Mousekeys
  MouseKeys, MouseKeysConfig,

  // Disable LEDs when idle
  HostPowerManagement, IdleLEDs,

  // Magic combos for debug utilities
  MagicCombo, HardwareTestMode, USBQuirks);

void setup() {
  // Setup the layer colors
  static const cRGB layerColormap[] PROGMEM = {
    HRGB(0xc41ef3), // Primary
    HRGB(0x51b56f), // Function
    HRGB(0x0300FF), // Control
    HRGB(0x1aadbc), // Super
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
  EEPROMKeymap.setup(TOTAL_LAYERS);

  // We need to tell the Colormap plugin how many layers we want to have custom
  // maps for. To make things simple, we set it to eight layers, which is how
  // many editable layers we have (see above).
  ColormapEffect.max_layers(TOTAL_LAYERS);

  // For Dynamic Macros, we need to reserve storage space for the editable
  // macros. A kilobyte is a reasonable default.
  DynamicMacros.reserve_storage(1024);

  // Set the action key the test mode should listen for to Left Fn
  HardwareTestMode.setActionKey(R3C6);

  MouseKeys.setWarpGridSize(MOUSE_WARP_GRID_3X3);

  LEDActiveLayerColorEffect.setColormap(layerColormap);

  Layer.move(LAYER_PRIMARY);
}

// Defer to Kaleidoscope.loop()
void loop() {
  Kaleidoscope.loop();
}
