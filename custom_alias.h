/* Kaleidoscope - Firmware for computer input devices
 * Copyright (C) 2022  Lilith Daemon
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

#pragma once

// Shifted keys
#define Key_Colon             LSHIFT(Key_Semicolon)
#define Key_DblQuote          LSHIFT(Key_Quote)
#define Key_GreaterThan       LSHIFT(Key_Period)
#define Key_LessThan          LSHIFT(Key_Comma)
#define Key_Pipe              LSHIFT(Key_Backslash)
#define Key_Question          LSHIFT(Key_Slash)
#define Key_Tilde             LSHIFT(Key_Backtick)
#define Key_Underscore        LSHIFT(Key_Minus)
#define Key_Exclamation       LSHIFT(Key_1)
#define Key_At                LSHIFT(Key_2)
#define Key_Pound             LSHIFT(Key_3)
#define Key_Dollar            LSHIFT(Key_4)
#define Key_Percent           LSHIFT(Key_5)
#define Key_Carat             LSHIFT(Key_6)
#define Key_Ampersand         LSHIFT(Key_7)
#define Key_Asterisk          LSHIFT(Key_8)

// Move layers
#define MOVE_PRIMARY          MoveToLayer(LAYER_PRIMARY)

// Mod layers
#define MOD_LAYER_CONTROL     modLayerKey(Key_LCtrl,  LAYER_CONTROL)
#define MOD_LAYER_SUPER       modLayerKey(Key_LGui,   LAYER_SUPER)
#define MOD_LAYER_ALT         modLayerKey(Key_LAlt,   LAYER_ALT)

// Colors
#define HRGB(h)               CRGB((h & 0xFF0000)>>16, (h & 0x00FF00)>>8, h & 0x0000FF)

// Me being lazy
#define YYY                   XXX

// Rename to fit 18 char
#define Key_LCurlyBracket     LSHIFT(Key_LeftBracket)
#define Key_RCurlyBracket     LSHIFT(Key_RightBracket)
