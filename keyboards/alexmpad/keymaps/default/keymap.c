/* Copyright 2021 AlexF
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
float enco_counter = 0;
bool encoder_flag = false;
// Defines names for use in layer keycodes and the keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                 KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,
            KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,
        KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC
    ),
    [1] = LAYOUT(
                 KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,
            KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,
        KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC
    ),
    [2] = LAYOUT(
                 KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,
            KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,
        KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC
    ),

};

void keyboard_post_init_user(void) {
  // Call the post init code.
  rgblight_enable_noeeprom(); // enables Rgb, without saving settings
  rgblight_sethsv_noeeprom(60, 60, 60); // sets the color to teal/cyan without saving
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 1); // sets mode to Fast breathing without saving
}

static uint16_t key_timer;
void matrix_scan_user(void) {
    if (timer_elapsed(key_timer) > 1000) {
        rgblight_set_effect_range(0, 17);
        rgblight_sethsv_noeeprom(60, 60, 60); // sets the color to teal/cyan without saving
        if (encoder_flag == true) {
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING +1);
            encoder_flag=false;
        }
        
    }
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (abs(enco_counter) >= 17) {
        enco_counter = 0;
    }
    if (enco_counter <0 ) {
        enco_counter = 17;
    }
    if (index == 0) { /* First encoder */
        if (clockwise) {
            enco_counter=enco_counter-0.2;
            key_timer = timer_read();
            tap_code(KC_LEFT);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_setrgb_range(40, 0, 40, 0, abs(round(enco_counter)));
            rgblight_setrgb_range(40, 40, 40, abs(round(enco_counter)) , 17);
            encoder_flag = true;
            //rgblight_step();

        } else {
            enco_counter=enco_counter+0.2;
            key_timer = timer_read();
            tap_code(KC_RGHT);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            rgblight_setrgb_range(0, 40, 40, 0, abs(round(enco_counter)));
            rgblight_setrgb_range(40, 40, 40, abs(round(enco_counter)) , 17);
            encoder_flag = true;
            //rgblight_step_reverse();
        }
    }
};
