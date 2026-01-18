/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#define DT_DRV_COMPAT zmk_behavior_art_control

#include <zephyr/device.h>
#include <zmk/behavior.h>
#include <zephyr/logging/log.h>

#include "art_slideshow.h"

LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

static int on_keymap_binding_pressed(const struct zmk_behavior_binding *binding,
                                     const struct zmk_behavior_binding_event event) {
    switch (binding->param1) {
    case 0: // Next
        art_slideshow_next();
        break;
    case 1: // Previous
        art_slideshow_prev();
        break;
    }
    return ZMK_BEHAVIOR_OPAQUE;
}

static int on_keymap_binding_released(const struct zmk_behavior_binding *binding,
                                      const struct zmk_behavior_binding_event event) {
    return ZMK_BEHAVIOR_OPAQUE;
}

static const struct behavior_driver_api behavior_art_control_driver_api = {
    .binding_pressed = on_keymap_binding_pressed,
    .binding_released = on_keymap_binding_released,
};

static int behavior_art_control_init(const struct device *dev) { return 0; };

struct behavior_art_control_config {};
struct behavior_art_control_data {};

BEHAVIOR_DT_INST_DEFINE(0, behavior_art_control_init, NULL, NULL, NULL, POST_KERNEL,
                        CONFIG_KERNEL_INIT_PRIORITY_DEFAULT, &behavior_art_control_driver_api);
