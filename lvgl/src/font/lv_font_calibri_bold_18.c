/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: --bpp 1 --size 18 --no-compress --stride 1 --align 1 --font calibri-bold.ttf --range 32-127 --format lvgl -o lv_font_calibri_bold_18.c
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif



#ifndef LV_FONT_CALIBRI_BOLD_18
#define LV_FONT_CALIBRI_BOLD_18 1
#endif

#if LV_FONT_CALIBRI_BOLD_18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xff, 0xc3, 0xc0,

    /* U+0022 "\"" */
    0xde, 0xf7, 0xbd, 0x80,

    /* U+0023 "#" */
    0x26, 0x26, 0x66, 0xff, 0xff, 0x66, 0x64, 0xff,
    0xff, 0x4c, 0x4c, 0xcc,

    /* U+0024 "$" */
    0x18, 0x30, 0xf3, 0xec, 0x18, 0x38, 0x3c, 0x3c,
    0x1c, 0x1c, 0x3f, 0xcf, 0x8, 0x10,

    /* U+0025 "%" */
    0x70, 0x6f, 0x8c, 0xd9, 0x8d, 0xb0, 0xfb, 0x7,
    0x6e, 0xd, 0xf1, 0x9b, 0x19, 0xb3, 0x1b, 0x61,
    0xf4, 0xe,

    /* U+0026 "&" */
    0x1f, 0x1, 0xfc, 0xc, 0x60, 0x63, 0x3, 0xb8,
    0xf, 0x80, 0xf1, 0x87, 0xcc, 0x67, 0xe3, 0x1f,
    0x1c, 0x78, 0x7f, 0xe1, 0xf3, 0x0,

    /* U+0027 "'" */
    0xff, 0xc0,

    /* U+0028 "(" */
    0x36, 0x66, 0xcc, 0xcc, 0xcc, 0xcc, 0x66, 0x63,

    /* U+0029 ")" */
    0xc6, 0x66, 0x33, 0x33, 0x33, 0x33, 0x66, 0x6c,

    /* U+002A "*" */
    0x10, 0xab, 0xf9, 0x8f, 0xea, 0x84, 0x0,

    /* U+002B "+" */
    0x18, 0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18,
    0x18,

    /* U+002C "," */
    0xd, 0xbd, 0x80,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xfc,

    /* U+002F "/" */
    0x2, 0x6, 0x6, 0xe, 0xc, 0xc, 0x1c, 0x18,
    0x18, 0x38, 0x30, 0x30, 0x70, 0x60, 0x60, 0xe0,
    0xc0,

    /* U+0030 "0" */
    0x3c, 0x7e, 0x67, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3c,

    /* U+0031 "1" */
    0x33, 0xcf, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xcf,
    0xff,

    /* U+0032 "2" */
    0x3e, 0x7f, 0x47, 0x7, 0x7, 0xe, 0xe, 0x1c,
    0x38, 0x70, 0xff, 0x7f,

    /* U+0033 "3" */
    0x3c, 0x7e, 0x46, 0x6, 0xe, 0x3c, 0x3e, 0x7,
    0x3, 0x3, 0x7e, 0x7c,

    /* U+0034 "4" */
    0xe, 0x1e, 0x1e, 0x36, 0x36, 0x66, 0x66, 0xc6,
    0xff, 0xff, 0x6, 0x6,

    /* U+0035 "5" */
    0x7e, 0x7e, 0x60, 0x60, 0x7c, 0x7e, 0x7, 0x3,
    0x3, 0x7, 0xfe, 0x7c,

    /* U+0036 "6" */
    0x3e, 0x7e, 0x60, 0xc0, 0xfe, 0xff, 0xc3, 0xc3,
    0xc3, 0xe7, 0x7e, 0x3c,

    /* U+0037 "7" */
    0xff, 0xff, 0x6, 0xe, 0xe, 0xc, 0x1c, 0x18,
    0x38, 0x38, 0x30, 0x70,

    /* U+0038 "8" */
    0x3e, 0xff, 0xc3, 0xc3, 0xe6, 0x7c, 0x7e, 0xe7,
    0xc3, 0xc3, 0xff, 0x7c,

    /* U+0039 "9" */
    0x3c, 0x7e, 0xc7, 0xc3, 0xc3, 0xff, 0x7f, 0x3,
    0x3, 0x6, 0xfe, 0x78,

    /* U+003A ":" */
    0xfc, 0xf, 0xc0,

    /* U+003B ";" */
    0x6d, 0x80, 0x1b, 0x6b, 0x40,

    /* U+003C "<" */
    0x2, 0x7, 0x1e, 0x78, 0xe0, 0xf0, 0x3c, 0xe,
    0x3,

    /* U+003D "=" */
    0xff, 0xfc, 0x0, 0xf, 0xff, 0xc0,

    /* U+003E ">" */
    0x80, 0xe0, 0x78, 0x1e, 0x6, 0xe, 0x3c, 0xf0,
    0xc0,

    /* U+003F "?" */
    0xf3, 0xe1, 0xc3, 0xc, 0x77, 0x98, 0x60, 0x0,
    0x18, 0x60,

    /* U+0040 "@" */
    0x3, 0xf0, 0x1f, 0xf8, 0x70, 0x71, 0xdd, 0x33,
    0x7e, 0x6f, 0xcc, 0xdb, 0x19, 0xb6, 0x33, 0x6c,
    0xec, 0xdf, 0xf9, 0x9d, 0xe3, 0x80, 0x3, 0x80,
    0x3, 0xfc, 0x3, 0xf0, 0x0,

    /* U+0041 "A" */
    0xe, 0x1, 0xc0, 0x7c, 0xd, 0x81, 0xb0, 0x67,
    0xc, 0x61, 0xfc, 0x7f, 0xcc, 0x19, 0x83, 0x70,
    0x70,

    /* U+0042 "B" */
    0xfc, 0xfe, 0xc6, 0xc6, 0xc6, 0xfc, 0xfe, 0xc7,
    0xc3, 0xc3, 0xfe, 0xfc,

    /* U+0043 "C" */
    0x3e, 0x7f, 0x61, 0xe0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0x61, 0x7f, 0x3e,

    /* U+0044 "D" */
    0xfc, 0x7f, 0xb1, 0xd8, 0x7c, 0x1e, 0xf, 0x7,
    0x83, 0xc3, 0xe3, 0xbf, 0xdf, 0x80,

    /* U+0045 "E" */
    0xff, 0xfc, 0x30, 0xc3, 0xff, 0xf0, 0xc3, 0xf,
    0xff,

    /* U+0046 "F" */
    0xff, 0xfc, 0x30, 0xc3, 0xff, 0xf0, 0xc3, 0xc,
    0x30,

    /* U+0047 "G" */
    0x1f, 0x8f, 0xf7, 0x7, 0x80, 0xc0, 0x31, 0xfc,
    0x7f, 0x3, 0xe0, 0xdc, 0x33, 0xfc, 0x7e,

    /* U+0048 "H" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1f, 0xff, 0xff,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x30,

    /* U+0049 "I" */
    0xff, 0xff, 0xff,

    /* U+004A "J" */
    0x18, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xfe, 0xe0,

    /* U+004B "K" */
    0xc7, 0xc6, 0xce, 0xdc, 0xd8, 0xf0, 0xf8, 0xdc,
    0xcc, 0xce, 0xc6, 0xc7,

    /* U+004C "L" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xf,
    0xff,

    /* U+004D "M" */
    0xf0, 0x7f, 0x83, 0xfc, 0x1f, 0xb1, 0xbd, 0x8d,
    0xec, 0x6f, 0x36, 0x79, 0xb3, 0xcf, 0x9e, 0x38,
    0xf1, 0xc7, 0x8e, 0x30,

    /* U+004E "N" */
    0xe1, 0xf8, 0xfc, 0x7f, 0x3d, 0x9e, 0xef, 0x37,
    0x9f, 0xc7, 0xe3, 0xf0, 0xf8, 0x70,

    /* U+004F "O" */
    0x1f, 0x7, 0xf9, 0xc3, 0x70, 0x3c, 0x7, 0x80,
    0xf0, 0x1e, 0x3, 0xc0, 0xec, 0x39, 0xfe, 0xf,
    0x80,

    /* U+0050 "P" */
    0xfc, 0xfe, 0xc7, 0xc3, 0xc3, 0xc7, 0xfe, 0xfc,
    0xc0, 0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x1f, 0x3, 0xfc, 0x70, 0xce, 0x6, 0xc0, 0x6c,
    0x6, 0xc0, 0x6c, 0x6, 0xc0, 0xe6, 0x1c, 0x7f,
    0xc1, 0xfe, 0x0, 0x70, 0x3,

    /* U+0052 "R" */
    0xfe, 0x7f, 0xb0, 0xd8, 0x6c, 0x77, 0xf3, 0xf9,
    0x9c, 0xc7, 0x61, 0xb0, 0xf8, 0x70,

    /* U+0053 "S" */
    0x3d, 0xfb, 0x16, 0xe, 0xf, 0xf, 0x7, 0x7,
    0xf, 0xf3, 0xc0,

    /* U+0054 "T" */
    0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xf1, 0xdf, 0xc7, 0xc0,

    /* U+0056 "V" */
    0xe0, 0xd8, 0x36, 0xd, 0xc6, 0x71, 0x8c, 0x63,
    0x38, 0xec, 0x1b, 0x7, 0xc1, 0xe0, 0x38,

    /* U+0057 "W" */
    0xe1, 0xc3, 0x61, 0xc7, 0x63, 0xc6, 0x63, 0xc6,
    0x73, 0xc6, 0x33, 0x66, 0x36, 0x6c, 0x36, 0x6c,
    0x3e, 0x6c, 0x1e, 0x7c, 0x1e, 0x38, 0x1c, 0x38,

    /* U+0058 "X" */
    0x61, 0x9c, 0xe3, 0x30, 0xfc, 0x1e, 0x7, 0x81,
    0xe0, 0xfc, 0x37, 0x1c, 0xe6, 0x3b, 0x87,

    /* U+0059 "Y" */
    0xc3, 0xe7, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18,

    /* U+005A "Z" */
    0xff, 0xff, 0x6, 0xe, 0x1c, 0x1c, 0x38, 0x30,
    0x70, 0xe0, 0xff, 0xff,

    /* U+005B "[" */
    0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xff,

    /* U+005C "\\" */
    0xc0, 0x60, 0x60, 0x70, 0x30, 0x30, 0x38, 0x18,
    0x18, 0x1c, 0xc, 0xc, 0xe, 0x6, 0x6, 0x7,

    /* U+005D "]" */
    0xff, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xff,

    /* U+005E "^" */
    0x8, 0xe, 0xf, 0x86, 0xc3, 0x63, 0x19, 0x8d,
    0xc7,

    /* U+005F "_" */
    0xff, 0xff, 0xc0,

    /* U+0060 "`" */
    0x61, 0x84, 0x0,

    /* U+0061 "a" */
    0x7d, 0xfc, 0x1b, 0xff, 0xf8, 0xf1, 0xff, 0x76,

    /* U+0062 "b" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xdc, 0xfe, 0xe7, 0xc3,
    0xc3, 0xc3, 0xe7, 0xfe, 0xdc,

    /* U+0063 "c" */
    0x3c, 0xfb, 0x86, 0xc, 0x18, 0x39, 0x3e, 0x38,

    /* U+0064 "d" */
    0x3, 0x3, 0x3, 0x3, 0x3b, 0x7f, 0xe7, 0xc3,
    0xc3, 0xc3, 0xe7, 0x7f, 0x3b,

    /* U+0065 "e" */
    0x3c, 0x7e, 0x63, 0x7f, 0xff, 0x60, 0x60, 0x7f,
    0x3e,

    /* U+0066 "f" */
    0x3b, 0xd8, 0xcf, 0xfd, 0x8c, 0x63, 0x18, 0xc6,
    0x0,

    /* U+0067 "g" */
    0x3f, 0x7f, 0x63, 0x63, 0x3f, 0x7e, 0x60, 0x7e,
    0x7f, 0x63, 0x7f, 0x7e,

    /* U+0068 "h" */
    0xc1, 0x83, 0x6, 0xd, 0xdf, 0xf9, 0xe3, 0xc7,
    0x8f, 0x1e, 0x3c, 0x60,

    /* U+0069 "i" */
    0xf0, 0xff, 0xff, 0xc0,

    /* U+006A "j" */
    0x33, 0x0, 0x33, 0x33, 0x33, 0x33, 0x33, 0xf6,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0xc, 0xf9, 0xb6, 0x78, 0xf9,
    0xb3, 0x76, 0x7c, 0x60,

    /* U+006C "l" */
    0xff, 0xff, 0xff, 0xc0,

    /* U+006D "m" */
    0xdc, 0xef, 0xff, 0xe7, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x30,

    /* U+006E "n" */
    0xdd, 0xff, 0x9e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,

    /* U+006F "o" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e,
    0x3c,

    /* U+0070 "p" */
    0xdc, 0xfe, 0xe7, 0xc3, 0xc3, 0xc3, 0xe7, 0xfe,
    0xdc, 0xc0, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x3b, 0x7f, 0xe7, 0xc3, 0xc3, 0xc3, 0xe7, 0x7f,
    0x3b, 0x3, 0x3, 0x3,

    /* U+0072 "r" */
    0xff, 0xf9, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0073 "s" */
    0x7b, 0xfc, 0x38, 0x78, 0x78, 0xff, 0xf8,

    /* U+0074 "t" */
    0x61, 0x8f, 0xff, 0x61, 0x86, 0x18, 0x61, 0xf3,
    0xc0,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf3, 0xff, 0x76,

    /* U+0076 "v" */
    0xe3, 0xe3, 0x63, 0x66, 0x76, 0x36, 0x3e, 0x3c,
    0x1c,

    /* U+0077 "w" */
    0xe3, 0x1b, 0x38, 0xd9, 0xce, 0xcf, 0x67, 0x5b,
    0x1e, 0xd8, 0xf7, 0x87, 0x9c, 0x38, 0xe0,

    /* U+0078 "x" */
    0x63, 0x76, 0x36, 0x3c, 0x3c, 0x3c, 0x7e, 0x66,
    0xe7,

    /* U+0079 "y" */
    0xe3, 0x63, 0x67, 0x76, 0x36, 0x36, 0x3c, 0x1c,
    0x1c, 0x18, 0x18, 0x38,

    /* U+007A "z" */
    0xff, 0xf1, 0x8e, 0x31, 0xce, 0x3f, 0xfc,

    /* U+007B "{" */
    0x19, 0xcc, 0x63, 0x18, 0xdc, 0x61, 0x8c, 0x63,
    0x18, 0xe3,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff,

    /* U+007D "}" */
    0xc7, 0x18, 0xc6, 0x31, 0x87, 0x33, 0x18, 0xc6,
    0x33, 0x98,

    /* U+007E "~" */
    0x73, 0xfb, 0xdf, 0xce
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 65, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 94, .box_w = 2, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 126, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 9, .adv_w = 143, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 146, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 35, .adv_w = 210, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 203, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 67, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 77, .adv_w = 90, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 85, .adv_w = 90, .box_w = 4, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 93, .adv_w = 143, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 100, .adv_w = 143, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 109, .adv_w = 74, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 112, .adv_w = 88, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 113, .adv_w = 77, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 124, .box_w = 8, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 131, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 146, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 79, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 79, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 256, .adv_w = 143, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 265, .adv_w = 143, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 271, .adv_w = 143, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 280, .adv_w = 133, .box_w = 6, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 259, .box_w = 15, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 319, .adv_w = 175, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 161, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 152, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 360, .adv_w = 182, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 140, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 132, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 184, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 182, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 77, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 424, .adv_w = 95, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 158, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 122, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 252, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 190, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 195, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 153, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 198, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 537, .adv_w = 162, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 136, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 143, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 188, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 170, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 603, .adv_w = 261, .box_w = 16, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 627, .adv_w = 159, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 642, .adv_w = 150, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 654, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 94, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 674, .adv_w = 124, .box_w = 8, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 690, .adv_w = 94, .box_w = 4, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 698, .adv_w = 143, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 707, .adv_w = 143, .box_w = 9, .box_h = 2, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 710, .adv_w = 86, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 713, .adv_w = 142, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 155, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 734, .adv_w = 121, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 742, .adv_w = 155, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 755, .adv_w = 145, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 764, .adv_w = 91, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 773, .adv_w = 137, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 785, .adv_w = 155, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 797, .adv_w = 71, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 801, .adv_w = 74, .box_w = 4, .box_h = 16, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 809, .adv_w = 138, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 821, .adv_w = 71, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 234, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 839, .adv_w = 155, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 847, .adv_w = 155, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 856, .adv_w = 155, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 868, .adv_w = 155, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 880, .adv_w = 102, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 886, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 893, .adv_w = 100, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 902, .adv_w = 155, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 910, .adv_w = 136, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 919, .adv_w = 215, .box_w = 13, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 934, .adv_w = 132, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 943, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 955, .adv_w = 114, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 962, .adv_w = 99, .box_w = 5, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 972, .adv_w = 137, .box_w = 2, .box_h = 16, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 976, .adv_w = 99, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 986, .adv_w = 143, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 7}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t lv_font_calibri_bold_18 = {
#else
lv_font_t lv_font_calibri_bold_18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 17,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .static_bitmap = 0,
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if LV_FONT_CALIBRI_BOLD_18*/
