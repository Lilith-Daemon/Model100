/* -*- mode: c++ -*-
 * Kaleidoscope-NamedCharShift -- Independently assign shifted and unshifted symbols
 * Copyright (C) 2021  Keyboard.io, Inc
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

#include "kaleidoscope/plugin/NamedCharShift.h"

#include <Arduino.h>                   // for F, __FlashStringHelper
#include <Kaleidoscope-FocusSerial.h>  // for Focus, FocusSerial
#include <Kaleidoscope-Ranges.h>       // for CS_FIRST, CS_LAST

#include "kaleidoscope/KeyAddrMap.h"                      // for KeyAddrMap<>::Iterator, KeyAddrMap
#include "kaleidoscope/KeyEvent.h"                        // for KeyEvent
#include "kaleidoscope/KeyMap.h"                          // for KeyMap
#include "kaleidoscope/LiveKeys.h"                        // for LiveKeys, live_keys
#include "kaleidoscope/Runtime.h"                         // for Runtime, Runtime_
#include "kaleidoscope/device/device.h"                   // for Base<>::HID, VirtualProps::HID
#include "kaleidoscope/driver/hid/keyboardio/Keyboard.h"  // for Keyboard
#include "kaleidoscope/key_defs.h"                        // for Key, Key_NoKey, Key_LeftShift
#include "kaleidoscope/keyswitch_state.h"                 // for keyToggledOff
#include "kaleidoscope/progmem_helpers.h"                 // for cloneFromProgmem

namespace kaleidoscope {
namespace plugins {

// =============================================================================
// Event handlers

// -----------------------------------------------------------------------------
EventHandlerResult NamedCharShift::onSetup() {
  lilith_gen_named_char_shift::setup();
  return EventHandlerResult::OK;
}

// -----------------------------------------------------------------------------
EventHandlerResult NamedCharShift::onNameQuery() {
  return ::Focus.sendName(F("NamedCharShift"));
}

// -----------------------------------------------------------------------------
EventHandlerResult NamedCharShift::onKeyEvent(KeyEvent &event) {
  // If the event is for anything other than an NamedCharShift key, we ignore it.
  if (!isCharShiftKey(event.key)) {
    // If this event is for a Keyboard key, we need to stop
    // `beforeReportingState()` from suppressing `shift` keys.
    if (event.key.isKeyboardKey())
      reverse_shift_state_ = false;
    return EventHandlerResult::OK;
  }

  // Default to not suppressing `shift` modifiers.
  reverse_shift_state_ = false;

  // It shouldn't be possible for an NamedCharShift key to toggle off, because it
  // will get replaced by on of its `KeyPair` values when it toggles on, but just
  // in case, we exit early if that happens.
  if (keyToggledOff(event.state))
    return EventHandlerResult::OK;

  // Next, we get the `KeyPair` values corresponding to the event key.
  KeyPair keypair = decodeCharShiftKey(event.key);

  // Determine if a shift key is being held.
  bool shift_held = false;
  for (Key key : live_keys.all()) {
    if (key.isKeyboardShift()) {
      shift_held = true;
      break;
    }
  }

  if (!shift_held) {
    // No shift key is held; just use the base value of the `KeyPair`.
    event.key = keypair.lower;
  } else {
    // At least one shift key is held; use the shifted value.
    event.key = keypair.upper;
    // Check for a shift modifier flag.
    if (event.key.isKeyboardKey() &&
        (event.key.getFlags() & SHIFT_HELD) == 0) {
      // The upper key doesn't have the `shift` modifier flag; we need to
      // suppress `shift` in `beforeReportingState()`.
      reverse_shift_state_ = true;
    }
  }

  return EventHandlerResult::OK;
}

// -----------------------------------------------------------------------------
EventHandlerResult NamedCharShift::beforeReportingState(const KeyEvent &event) {
  // If `onKeyEvent()` has signalled that `shift` should be suppressed, this is
  // the time to do it.  We can't do it in `onKeyEvent()`, because the new
  // Keyboard HID report hasn't been prepared yet there.
  if (reverse_shift_state_) {
    Runtime.hid().keyboard().releaseKey(Key_LeftShift);
    Runtime.hid().keyboard().releaseKey(Key_RightShift);
  }
  return EventHandlerResult::OK;
}

// =============================================================================
// Support functions

bool NamedCharShift::isCharShiftKey(Key key) {
  return (key >= ranges::CS_FIRST && key <= ranges::CS_LAST);
}

NamedCharShift::KeyPair NamedCharShift::decodeCharShiftKey(Key key) {
  uint8_t i = key.getRaw() - ranges::CS_FIRST;
  if (i < numKeyPairs()) {
    return readKeyPair(i);
  }
  return {Key_NoKey, Key_NoKey};
}

// This should be overridden if the KeyPairs array is stored in EEPROM
__attribute__((weak))
uint8_t
NamedCharShift::numKeyPairs() {
  return numProgmemKeyPairs();
}

// This should be overridden if the KeyPairs array is stored in EEPROM
__attribute__((weak))
NamedCharShift::KeyPair
NamedCharShift::readKeyPair(uint8_t n) {
  return readKeyPairFromProgmem(n);
}

uint8_t NamedCharShift::numProgmemKeyPairs() {
  return num_keypairs_;
}

NamedCharShift::KeyPair NamedCharShift::readKeyPairFromProgmem(uint8_t n) {
  return cloneFromProgmem(progmem_keypairs_[n]);
}

}  // namespace plugins
}  // namespace kaleidoscope

kaleidoscope::plugins::NamedCharShift NamedCharShift;
