/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/random/random.h>
#include <lvgl.h>

#include "art_slideshow.h"

#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM1)
LV_IMG_DECLARE(hammerbeam1);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_CHILL)
LV_IMG_DECLARE(chill);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM2)
LV_IMG_DECLARE(hammerbeam2);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM3)
LV_IMG_DECLARE(hammerbeam3);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM4)
LV_IMG_DECLARE(hammerbeam4);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM5)
LV_IMG_DECLARE(hammerbeam5);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM6)
LV_IMG_DECLARE(hammerbeam6);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM7)
LV_IMG_DECLARE(hammerbeam7);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM8)
LV_IMG_DECLARE(hammerbeam8);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM9)
LV_IMG_DECLARE(hammerbeam9);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM10)
LV_IMG_DECLARE(hammerbeam10);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM11)
LV_IMG_DECLARE(hammerbeam11);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM12)
LV_IMG_DECLARE(hammerbeam12);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM13)
LV_IMG_DECLARE(hammerbeam13);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM14)
LV_IMG_DECLARE(hammerbeam14);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM15)
LV_IMG_DECLARE(hammerbeam15);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM16)
LV_IMG_DECLARE(hammerbeam16);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM17)
LV_IMG_DECLARE(hammerbeam17);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM18)
LV_IMG_DECLARE(hammerbeam18);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM19)
LV_IMG_DECLARE(hammerbeam19);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM20)
LV_IMG_DECLARE(hammerbeam20);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM21)
LV_IMG_DECLARE(hammerbeam21);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM22)
LV_IMG_DECLARE(hammerbeam22);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM23)
LV_IMG_DECLARE(hammerbeam23);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM24)
LV_IMG_DECLARE(hammerbeam24);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM25)
LV_IMG_DECLARE(hammerbeam25);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM26)
LV_IMG_DECLARE(hammerbeam26);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM27)
LV_IMG_DECLARE(hammerbeam27);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM28)
LV_IMG_DECLARE(hammerbeam28);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM29)
LV_IMG_DECLARE(hammerbeam29);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM30)
LV_IMG_DECLARE(hammerbeam30);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_VIM)
LV_IMG_DECLARE(vim);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_CPP)
LV_IMG_DECLARE(cpp);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_LGTM)
LV_IMG_DECLARE(lgtm);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_SHIP_IT)
LV_IMG_DECLARE(ship_it);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_VIBE_CODING)
LV_IMG_DECLARE(vibe_coding);
#endif

static const lv_img_dsc_t *art_images[] = {
#if IS_ENABLED(CONFIG_CUSTOM_ART_VIBE_CODING)
    &vibe_coding,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_SHIP_IT)
    &ship_it,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_LGTM)
    &lgtm,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_CPP)
    &cpp,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_VIM)
    &vim,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_CHILL)
    &chill,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM1)
    &hammerbeam1,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM2)
    &hammerbeam2,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM3)
    &hammerbeam3,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM4)
    &hammerbeam4,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM5)
    &hammerbeam5,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM6)
    &hammerbeam6,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM7)
    &hammerbeam7,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM8)
    &hammerbeam8,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM9)
    &hammerbeam9,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM10)
    &hammerbeam10,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM11)
    &hammerbeam11,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM12)
    &hammerbeam12,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM13)
    &hammerbeam13,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM14)
    &hammerbeam14,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM15)
    &hammerbeam15,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM16)
    &hammerbeam16,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM17)
    &hammerbeam17,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM18)
    &hammerbeam18,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM19)
    &hammerbeam19,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM20)
    &hammerbeam20,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM21)
    &hammerbeam21,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM22)
    &hammerbeam22,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM23)
    &hammerbeam23,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM24)
    &hammerbeam24,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM25)
    &hammerbeam25,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM26)
    &hammerbeam26,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM27)
    &hammerbeam27,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM28)
    &hammerbeam28,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM29)
    &hammerbeam29,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM30)
    &hammerbeam30,
#endif
};

static lv_obj_t *img_widget;
static lv_timer_t *slideshow_timer;
static uint8_t current_art_index = 0;
static const uint8_t art_count = sizeof(art_images) / sizeof(art_images[0]);

static void slideshow_task(lv_timer_t *timer) { art_slideshow_next(); }

void art_slideshow_init(lv_obj_t *parent) {
    if (art_count == 0) {
        return;
    }

    current_art_index = sys_rand32_get() % art_count;

    img_widget = lv_img_create(parent);
    lv_img_set_src(img_widget, art_images[current_art_index]);
    lv_obj_center(img_widget);
    lv_obj_align(img_widget, LV_ALIGN_TOP_LEFT, 0, 0);

    slideshow_timer = lv_timer_create(slideshow_task, CONFIG_CUSTOM_ANIMATION_SPEED, NULL);
}

void art_slideshow_next(void) {
    if (art_count == 0) {
        return;
    }

    current_art_index = (current_art_index + 1) % art_count;
    lv_img_set_src(img_widget, art_images[current_art_index]);
    lv_timer_reset(slideshow_timer);
}

void art_slideshow_prev(void) {
    if (art_count == 0) {
        return;
    }

    current_art_index = (current_art_index + art_count - 1) % art_count;
    lv_img_set_src(img_widget, art_images[current_art_index]);
    lv_timer_reset(slideshow_timer);
}
