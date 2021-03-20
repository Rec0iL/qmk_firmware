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
                 KC_SPC,  KC_W,  KC_SPC,  KC_B,
            KC_A,  KC_S,  KC_D,  MO(2),
        KC_SPC,  KC_SPC,  KC_SPC,  MO(1)
    ),
    [1] = LAYOUT(
                 RGB_TOG,  KC_TRNS,  KC_TRNS,  RESET ,
            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
    [2] = LAYOUT(
                 KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
            KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
        KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
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
        if (encoder_flag == true) {
            rgblight_set_effect_range(0, RGBLED_NUM);
            rgblight_sethsv_noeeprom(60, 60, 60); // sets the color to teal/cyan without saving
            rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING +1);
            encoder_flag=false;
        }
        
    }
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (abs(enco_counter) >= RGBLED_NUM-1) {
        enco_counter = 0;
    }
    if (enco_counter <0 ) {
        enco_counter = RGBLED_NUM-1;
    }
    if (index == 0) { /* First encoder */
            if(IS_LAYER_ON(0)){
                if (clockwise) {
                    tap_code(KC_LEFT);
                    enco_counter=enco_counter-0.2;
                    key_timer = timer_read();
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                    rgblight_setrgb_range(80, 80, 80, 0, abs(round(enco_counter)));//turn beginning colored
                    rgblight_setrgb_at(0, 0, 0, abs(round(enco_counter)));//set current blue
                    rgblight_setrgb_range(80, 80, 80, abs(round(enco_counter)+1) , RGBLED_NUM); //turn rest colored
                    rgblight_setrgb_at(10, 10, 10, 1+abs(round(enco_counter)));//set current blue
                    rgblight_setrgb_at(10, 10, 10, (-1)+abs(round(enco_counter)));//set current blue
                    encoder_flag = true;
                    //rgblight_step();

                } else {
                    tap_code(KC_RGHT);
                    enco_counter=enco_counter+0.2;
                    key_timer = timer_read();
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                    rgblight_setrgb_range(80, 80, 80, 0, abs(round(enco_counter)));//turn beginning colored
                    rgblight_setrgb_at(0, 0, 0, abs(round(enco_counter)));//set current purple
                    rgblight_setrgb_range(80, 80, 80, abs(round(enco_counter)+1) , RGBLED_NUM); //turn rest colored
                    rgblight_setrgb_at(10, 10, 10, 1+abs(round(enco_counter)));//set current blue
                    rgblight_setrgb_at(10, 10, 10, (-1)+abs(round(enco_counter)));//set current blue
                    encoder_flag = true;
                    //rgblight_step_reverse();
                }
            }
            if(IS_LAYER_ON(2)){
                if (clockwise) {
                    tap_code(KC_PGUP);
                    enco_counter=enco_counter-0.2;
                    key_timer = timer_read();
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                    rgblight_setrgb_range(80, 80, 80, 0, abs(round(enco_counter)));//turn beginning colored
                    rgblight_setrgb_at(0, 0, 0, abs(round(enco_counter)));//set current blue
                    rgblight_setrgb_range(80, 80, 80, abs(round(enco_counter)+1) , RGBLED_NUM); //turn rest colored
                    rgblight_setrgb_at(10, 10, 10, 1+abs(round(enco_counter)));//set current blue
                    rgblight_setrgb_at(10, 10, 10, (-1)+abs(round(enco_counter)));//set current blue
                    encoder_flag = true;
                    //rgblight_step();

                } else {
                    tap_code(KC_PGDN);
                    enco_counter=enco_counter+0.2;
                    key_timer = timer_read();
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                    rgblight_setrgb_range(80, 80, 80, 0, abs(round(enco_counter)));//turn beginning colored
                    rgblight_setrgb_at(0, 0, 0, abs(round(enco_counter)));//set current purple
                    rgblight_setrgb_range(80, 80, 80, abs(round(enco_counter)+1) , RGBLED_NUM); //turn rest colored
                    rgblight_setrgb_at(10, 10, 10, 1+abs(round(enco_counter)));//set current blue
                    rgblight_setrgb_at(10, 10, 10, (-1)+abs(round(enco_counter)));//set current blue
                    encoder_flag = true;
                    //rgblight_step_reverse();
                }
            }
            if(IS_LAYER_ON(1)){
                if (clockwise) {
                    tap_code(KC_UP);
                    enco_counter=enco_counter-0.2;
                    key_timer = timer_read();
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                    rgblight_setrgb_range(80, 80, 80, 0, abs(round(enco_counter)));//turn beginning colored
                    rgblight_setrgb_at(0, 0, 0, abs(round(enco_counter)));//set current blue
                    rgblight_setrgb_range(80, 80, 80, abs(round(enco_counter)+1) , RGBLED_NUM); //turn rest colored
                    rgblight_setrgb_at(10, 10, 10, 1+abs(round(enco_counter)));//set current blue
                    rgblight_setrgb_at(10, 10, 10, (-1)+abs(round(enco_counter)));//set current blue
                    encoder_flag = true;
                    //rgblight_step();

                } else {
                    tap_code(KC_DOWN);
                    enco_counter=enco_counter+0.2;
                    key_timer = timer_read();
                    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
                    rgblight_setrgb_range(80, 80, 80, 0, abs(round(enco_counter)));//turn beginning colored
                    rgblight_setrgb_at(0, 0, 0, abs(round(enco_counter)));//set current purple
                    rgblight_setrgb_range(80, 80, 80, abs(round(enco_counter)+1) , RGBLED_NUM); //turn rest colored
                    rgblight_setrgb_at(10, 10, 10, 1+abs(round(enco_counter)));//set current blue
                    rgblight_setrgb_at(10, 10, 10, (-1)+abs(round(enco_counter)));//set current blue
                    encoder_flag = true;
                    //rgblight_step_reverse();
                }
            }
        }
    
}