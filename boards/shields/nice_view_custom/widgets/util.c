/*
 *
 * Copyright (c) 2023 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 *
 */

#include <zephyr/kernel.h>
#include "util.h"

LV_IMG_DECLARE(bolt);

void rotate_canvas(lv_obj_t *canvas, lv_color_t cbuf[]) {
    static lv_color_t cbuf_tmp[CANVAS_SIZE * CANVAS_SIZE];
    memcpy(cbuf_tmp, cbuf, sizeof(cbuf_tmp));
    lv_img_dsc_t img;
    img.data = (void *)cbuf_tmp;
    img.header.cf = LV_COLOR_FORMAT_NATIVE;
    img.header.w = CANVAS_SIZE;
    img.header.h = CANVAS_SIZE;

    lv_canvas_fill_bg(canvas, LVGL_BACKGROUND, LV_OPA_COVER);
    
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);
    
    lv_draw_image_dsc_t img_dsc;
    lv_draw_image_dsc_init(&img_dsc);
    img_dsc.src = &img;
    img_dsc.rotation = 900; // 90 degrees (0.1 degree resolution)
    img_dsc.pivot.x = CANVAS_SIZE / 2;
    img_dsc.pivot.y = CANVAS_SIZE / 2;
    
    lv_area_t area;
    area.x1 = 0;
    area.y1 = 0;
    area.x2 = CANVAS_SIZE - 1;
    area.y2 = CANVAS_SIZE - 1;
    lv_draw_image(&layer, &img_dsc, &area);
    
    lv_canvas_finish_layer(canvas, &layer);
}

void draw_battery(lv_obj_t *canvas, const struct status_state *state) {
    lv_layer_t layer;
    lv_canvas_init_layer(canvas, &layer);

    lv_draw_rect_dsc_t rect_black_dsc;
    init_rect_dsc(&rect_black_dsc, LVGL_BACKGROUND);
    lv_draw_rect_dsc_t rect_white_dsc;
    init_rect_dsc(&rect_white_dsc, LVGL_FOREGROUND);

    lv_area_t area;
    area.x1 = 0;
    area.y1 = 2;
    area.x2 = 29;
    area.y2 = 12;
    lv_draw_rect(&layer, &rect_white_dsc, &area);

    area.x1 = 1;
    area.y1 = 3;
    area.x2 = 27;
    area.y2 = 10;
    lv_draw_rect(&layer, &rect_black_dsc, &area);

    area.x1 = 2;
    area.y1 = 4;
    area.x2 = 2 + (state->battery + 2) / 4;
    area.y2 = 8;
    lv_draw_rect(&layer, &rect_white_dsc, &area);

    area.x1 = 30;
    area.y1 = 5;
    area.x2 = 33;
    area.y2 = 11;
    lv_draw_rect(&layer, &rect_white_dsc, &area);

    area.x1 = 31;
    area.y1 = 6;
    area.x2 = 32;
    area.y2 = 10;
    lv_draw_rect(&layer, &rect_black_dsc, &area);

    if (state->charging) {
        lv_draw_image_dsc_t img_dsc;
        lv_draw_image_dsc_init(&img_dsc);
        img_dsc.src = &bolt;
        area.x1 = 9;
        area.y1 = -1;
        area.x2 = 9 + 11;
        area.y2 = -1 + 18;
        lv_draw_image(&layer, &img_dsc, &area);
    }

    lv_canvas_finish_layer(canvas, &layer);
}

void init_label_dsc(lv_draw_label_dsc_t *label_dsc, lv_color_t color, const lv_font_t *font,
                    lv_text_align_t align) {
    lv_draw_label_dsc_init(label_dsc);
    label_dsc->color = color;
    label_dsc->font = font;
    label_dsc->align = align;
}

void init_rect_dsc(lv_draw_rect_dsc_t *rect_dsc, lv_color_t bg_color) {
    lv_draw_rect_dsc_init(rect_dsc);
    rect_dsc->bg_color = bg_color;
}

void init_line_dsc(lv_draw_line_dsc_t *line_dsc, lv_color_t color, uint8_t width) {
    lv_draw_line_dsc_init(line_dsc);
    line_dsc->color = color;
    line_dsc->width = width;
}

void init_arc_dsc(lv_draw_arc_dsc_t *arc_dsc, lv_color_t color, uint8_t width) {
    lv_draw_arc_dsc_init(arc_dsc);
    arc_dsc->color = color;
    arc_dsc->width = width;
}
