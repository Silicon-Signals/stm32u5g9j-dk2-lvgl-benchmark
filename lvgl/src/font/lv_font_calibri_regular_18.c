/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: --bpp 1 --size 18 --no-compress --stride 1 --align 1 --font calibri-regular.ttf --range 32-127 --format lvgl -o lv_font_calibri_regular_18.c
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



#ifndef LV_FONT_CALIBRI_REGULAR_18
#define LV_FONT_CALIBRI_REGULAR_18 1
#endif

#if LV_FONT_CALIBRI_REGULAR_18

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
    0x13, 0x19, 0x8c, 0x8f, 0xf2, 0x21, 0x10, 0x89,
    0xfe, 0x26, 0x33, 0x19, 0xc, 0x80,

    /* U+0024 "$" */
    0x10, 0x21, 0xf6, 0x2c, 0x18, 0x38, 0x3c, 0x3c,
    0x1c, 0x18, 0x38, 0xcf, 0x8, 0x10, 0x0,

    /* U+0025 "%" */
    0x70, 0x51, 0x12, 0x26, 0x45, 0x88, 0xa0, 0xe8,
    0x3, 0x30, 0x49, 0x11, 0x26, 0x24, 0x84, 0xa0,
    0x60,

    /* U+0026 "&" */
    0x1f, 0x3, 0x18, 0x31, 0x83, 0x18, 0x1b, 0x1,
    0xe0, 0x1c, 0x63, 0x66, 0x63, 0x66, 0x3c, 0x61,
    0xc3, 0x1c, 0x1f, 0x30,

    /* U+0027 "'" */
    0xff, 0xc0,

    /* U+0028 "(" */
    0x32, 0x66, 0xcc, 0xcc, 0xcc, 0xcc, 0x66, 0x23,

    /* U+0029 ")" */
    0xc4, 0x66, 0x23, 0x33, 0x33, 0x33, 0x66, 0x4c,

    /* U+002A "*" */
    0x10, 0x2b, 0xf0, 0x87, 0xc2, 0x84, 0x0,

    /* U+002B "+" */
    0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18,

    /* U+002C "," */
    0x6d, 0x68,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x0, 0xc, 0x10, 0x60, 0xc1, 0x6, 0xc, 0x10,
    0x60, 0xc1, 0x6, 0xc, 0x10, 0x60, 0xc0,

    /* U+0030 "0" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0xc3, 0x66, 0x3c,

    /* U+0031 "1" */
    0x18, 0xf3, 0x60, 0xc1, 0x83, 0x6, 0xc, 0x18,
    0x30, 0x67, 0xf0,

    /* U+0032 "2" */
    0x78, 0x8e, 0x6, 0x6, 0x6, 0xe, 0xc, 0x18,
    0x30, 0x60, 0xc0, 0xff,

    /* U+0033 "3" */
    0x7d, 0x1c, 0x18, 0x30, 0xcf, 0x3, 0x3, 0x6,
    0xe, 0x37, 0xc0,

    /* U+0034 "4" */
    0xe, 0x7, 0x5, 0x82, 0xc2, 0x63, 0x31, 0x19,
    0x8c, 0xff, 0x83, 0x1, 0x80, 0xc0,

    /* U+0035 "5" */
    0x7e, 0x60, 0x60, 0x60, 0x60, 0x7e, 0x7, 0x3,
    0x3, 0x3, 0x86, 0x7c,

    /* U+0036 "6" */
    0x1e, 0x70, 0x60, 0xc0, 0xc0, 0xfe, 0xc7, 0xc3,
    0xc3, 0xc3, 0x66, 0x3c,

    /* U+0037 "7" */
    0xfe, 0xc, 0x18, 0x20, 0xc1, 0x86, 0xc, 0x10,
    0x60, 0x83, 0x0,

    /* U+0038 "8" */
    0x3e, 0xc7, 0xc3, 0xc3, 0x66, 0x3c, 0x3e, 0x67,
    0xc3, 0xc3, 0xe7, 0x7c,

    /* U+0039 "9" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xe3, 0x7f, 0x3,
    0x3, 0x6, 0xe, 0x78,

    /* U+003A ":" */
    0xf0, 0x3, 0xc0,

    /* U+003B ";" */
    0x6c, 0x0, 0x1b, 0x5a, 0x0,

    /* U+003C "<" */
    0x0, 0xc, 0x73, 0x8c, 0x1c, 0xe, 0x7, 0x2,

    /* U+003D "=" */
    0xfe, 0x0, 0x0, 0xf, 0xe0,

    /* U+003E ">" */
    0x81, 0xc0, 0xe0, 0x60, 0x21, 0xce, 0x70, 0x80,

    /* U+003F "?" */
    0x79, 0x18, 0x18, 0x30, 0x61, 0xce, 0x18, 0x30,
    0x0, 0x1, 0x83, 0x0,

    /* U+0040 "@" */
    0x1, 0xf0, 0xc, 0x38, 0x30, 0x38, 0xcf, 0x31,
    0xb2, 0x66, 0xc4, 0xcd, 0x89, 0x9b, 0x13, 0x36,
    0x6c, 0x67, 0x70, 0xc0, 0x0, 0xc0, 0x0, 0xc0,
    0x0, 0x7e, 0x0,

    /* U+0041 "A" */
    0xc, 0x3, 0x81, 0xe0, 0x68, 0x13, 0xc, 0xc3,
    0x10, 0x86, 0x7f, 0x98, 0x24, 0xf, 0x3,

    /* U+0042 "B" */
    0xfc, 0xc6, 0xc6, 0xc6, 0xcc, 0xfc, 0xc6, 0xc3,
    0xc3, 0xc3, 0xc6, 0xfc,

    /* U+0043 "C" */
    0x1f, 0x18, 0xd8, 0x18, 0xc, 0x6, 0x3, 0x1,
    0x80, 0xc0, 0x30, 0xc, 0x63, 0xe0,

    /* U+0044 "D" */
    0xfc, 0x63, 0xb0, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe1, 0xb1, 0x9f, 0x80,

    /* U+0045 "E" */
    0xff, 0x83, 0x6, 0xc, 0x1f, 0xb0, 0x60, 0xc1,
    0x83, 0x7, 0xf0,

    /* U+0046 "F" */
    0xff, 0xc, 0x30, 0xc3, 0xf, 0xf0, 0xc3, 0xc,
    0x30,

    /* U+0047 "G" */
    0x1f, 0x18, 0x58, 0x18, 0xc, 0x6, 0x3f, 0x7,
    0x83, 0xc1, 0xb0, 0xcc, 0x63, 0xe0,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xc3,

    /* U+0049 "I" */
    0xff, 0xff, 0xff,

    /* U+004A "J" */
    0x18, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc7, 0xe0,

    /* U+004B "K" */
    0xc3, 0xc6, 0xcc, 0xc8, 0xd8, 0xf0, 0xd0, 0xd8,
    0xcc, 0xc4, 0xc6, 0xc3,

    /* U+004C "L" */
    0xc3, 0xc, 0x30, 0xc3, 0xc, 0x30, 0xc3, 0xc,
    0x3f,

    /* U+004D "M" */
    0xe0, 0x3f, 0x1, 0xfc, 0x1f, 0xa0, 0xbd, 0x5,
    0xec, 0x4f, 0x22, 0x79, 0xb3, 0xc5, 0x1e, 0x28,
    0xf1, 0xc7, 0x84, 0x30,

    /* U+004E "N" */
    0xc1, 0xf0, 0xf8, 0x7a, 0x3d, 0x1e, 0x4f, 0x27,
    0x8b, 0xc5, 0xe1, 0xf0, 0xf8, 0x30,

    /* U+004F "O" */
    0x1e, 0x1c, 0x66, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xd8, 0x66, 0x38, 0x78,

    /* U+0050 "P" */
    0xf9, 0x9b, 0x1e, 0x3c, 0x79, 0xbe, 0x60, 0xc1,
    0x83, 0x6, 0x0,

    /* U+0051 "Q" */
    0x1e, 0xe, 0x31, 0x86, 0x60, 0x6c, 0xd, 0x81,
    0xb0, 0x36, 0x6, 0xc0, 0xcc, 0x31, 0x8e, 0x1f,
    0xc0, 0x6, 0x0, 0x0,

    /* U+0052 "R" */
    0xfd, 0x9f, 0x1e, 0x3c, 0xdf, 0x32, 0x66, 0xc5,
    0x8f, 0x1e, 0x10,

    /* U+0053 "S" */
    0x3c, 0x87, 0x6, 0xe, 0xf, 0xf, 0x7, 0x6,
    0xe, 0x37, 0xc0,

    /* U+0054 "T" */
    0xff, 0xc3, 0x0, 0xc0, 0x30, 0xc, 0x3, 0x0,
    0xc0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xd8, 0xc7, 0xc0,

    /* U+0056 "V" */
    0xc0, 0xd0, 0x36, 0x9, 0x86, 0x21, 0x8c, 0x43,
    0x30, 0x4c, 0x1a, 0x7, 0x80, 0xe0, 0x30,

    /* U+0057 "W" */
    0x83, 0x6, 0xc, 0x1c, 0x30, 0xf1, 0xe3, 0x45,
    0x89, 0x12, 0x26, 0x49, 0x9b, 0x36, 0x28, 0xd0,
    0xa1, 0x43, 0x87, 0x6, 0x18,

    /* U+0058 "X" */
    0x41, 0xb1, 0x88, 0xc6, 0xc1, 0xc0, 0xe0, 0x70,
    0x2c, 0x36, 0x11, 0x98, 0x48, 0x30,

    /* U+0059 "Y" */
    0x81, 0xc3, 0x42, 0x66, 0x24, 0x3c, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18,

    /* U+005A "Z" */
    0xfe, 0xc, 0x30, 0x41, 0x82, 0xc, 0x30, 0x61,
    0x82, 0x7, 0xf0,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf,

    /* U+005C "\\" */
    0xc0, 0x81, 0x3, 0x2, 0x4, 0xc, 0x8, 0x10,
    0x30, 0x20, 0x40, 0xc0, 0x81, 0x83,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f,

    /* U+005E "^" */
    0x30, 0x70, 0xa3, 0x64, 0x58, 0xf1, 0x80,

    /* U+005F "_" */
    0xff, 0x80,

    /* U+0060 "`" */
    0x62, 0x10,

    /* U+0061 "a" */
    0x7d, 0x1c, 0x18, 0x37, 0xf8, 0xf1, 0xe7, 0x7e,

    /* U+0062 "b" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xdc, 0xe6, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0xe6, 0xdc,

    /* U+0063 "c" */
    0x3c, 0xc7, 0x6, 0xc, 0x18, 0x30, 0x31, 0x3c,

    /* U+0064 "d" */
    0x3, 0x3, 0x3, 0x3, 0x3b, 0x67, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3, 0x67, 0x3b,

    /* U+0065 "e" */
    0x3c, 0x66, 0xc3, 0xc3, 0xff, 0xc0, 0xc0, 0x60,
    0x3e,

    /* U+0066 "f" */
    0x3b, 0x18, 0xcf, 0xb1, 0x8c, 0x63, 0x18, 0xc6,
    0x0,

    /* U+0067 "g" */
    0x7f, 0xe6, 0xc6, 0xc6, 0x46, 0x7c, 0xc0, 0x7e,
    0xc3, 0xc3, 0xc7, 0x7c,

    /* U+0068 "h" */
    0xc1, 0x83, 0x6, 0xd, 0xdc, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x3c, 0x60,

    /* U+0069 "i" */
    0xf3, 0xff, 0xff,

    /* U+006A "j" */
    0x33, 0x3, 0x33, 0x33, 0x33, 0x33, 0x33, 0xe0,

    /* U+006B "k" */
    0xc1, 0x83, 0x6, 0xc, 0x79, 0xb6, 0x78, 0xf1,
    0xb3, 0x36, 0x6c, 0x60,

    /* U+006C "l" */
    0xff, 0xff, 0xff, 0xc0,

    /* U+006D "m" */
    0xdc, 0xee, 0x73, 0xc6, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x30,

    /* U+006E "n" */
    0xdd, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,

    /* U+006F "o" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66,
    0x3c,

    /* U+0070 "p" */
    0xdc, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe6,
    0xdc, 0xc0, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x3b, 0x67, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x67,
    0x7b, 0x3, 0x3, 0x3,

    /* U+0072 "r" */
    0xdf, 0x31, 0x8c, 0x63, 0x18, 0xc0,

    /* U+0073 "s" */
    0x7b, 0xc, 0x38, 0x78, 0x70, 0xe3, 0xf8,

    /* U+0074 "t" */
    0x3, 0x19, 0xf6, 0x31, 0x8c, 0x63, 0x18, 0x70,

    /* U+0075 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe7, 0x76,

    /* U+0076 "v" */
    0xc3, 0x42, 0x62, 0x66, 0x24, 0x34, 0x3c, 0x18,
    0x18,

    /* U+0077 "w" */
    0x42, 0x14, 0x61, 0x67, 0x36, 0x53, 0x25, 0x22,
    0xda, 0x39, 0xe1, 0x8c, 0x18, 0xc0,

    /* U+0078 "x" */
    0x42, 0xcc, 0xb1, 0xc1, 0x87, 0x8b, 0x33, 0xc2,

    /* U+0079 "y" */
    0xc3, 0x42, 0x62, 0x66, 0x24, 0x34, 0x3c, 0x18,
    0x18, 0x18, 0x10, 0x30,

    /* U+007A "z" */
    0xf8, 0xc4, 0x62, 0x31, 0x18, 0xf8,

    /* U+007B "{" */
    0x19, 0x8c, 0x63, 0x18, 0xdc, 0x61, 0x8c, 0x63,
    0x18, 0xc3,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff,

    /* U+007D "}" */
    0xc3, 0x18, 0xc6, 0x31, 0x87, 0x33, 0x18, 0xc6,
    0x31, 0x98,

    /* U+007E "~" */
    0x71, 0x99, 0x8e
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 65, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 94, .box_w = 2, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 9, .adv_w = 143, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 23, .adv_w = 146, .box_w = 7, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 38, .adv_w = 206, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 196, .box_w = 12, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 64, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 77, .adv_w = 87, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 85, .adv_w = 87, .box_w = 4, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 93, .adv_w = 143, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 100, .adv_w = 143, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 108, .adv_w = 72, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 110, .adv_w = 88, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 111, .adv_w = 73, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 111, .box_w = 7, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 127, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 146, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 146, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 77, .box_w = 2, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 77, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 254, .adv_w = 143, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 262, .adv_w = 143, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 267, .adv_w = 143, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 275, .adv_w = 133, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 257, .box_w = 15, .box_h = 14, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 314, .adv_w = 167, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 157, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 177, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 132, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 182, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 179, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 73, .box_w = 2, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 92, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 150, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 121, .box_w = 6, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 246, .box_w = 13, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 186, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 481, .adv_w = 191, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 149, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 194, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 527, .adv_w = 156, .box_w = 7, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 132, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 549, .adv_w = 140, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 185, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 578, .adv_w = 163, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 256, .box_w = 14, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 614, .adv_w = 149, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 140, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 640, .adv_w = 135, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 88, .box_w = 4, .box_h = 16, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 659, .adv_w = 111, .box_w = 7, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 673, .adv_w = 88, .box_w = 4, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 681, .adv_w = 143, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 688, .adv_w = 143, .box_w = 9, .box_h = 1, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 690, .adv_w = 84, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 692, .adv_w = 138, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 700, .adv_w = 151, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 713, .adv_w = 122, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 151, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 734, .adv_w = 143, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 88, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 752, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 764, .adv_w = 151, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 776, .adv_w = 66, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 779, .adv_w = 69, .box_w = 4, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 787, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 799, .adv_w = 66, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 803, .adv_w = 230, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 817, .adv_w = 151, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 152, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 834, .adv_w = 151, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 846, .adv_w = 151, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 858, .adv_w = 100, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 864, .adv_w = 113, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 871, .adv_w = 96, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 879, .adv_w = 151, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 887, .adv_w = 130, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 896, .adv_w = 206, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 910, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 918, .adv_w = 130, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 930, .adv_w = 114, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 936, .adv_w = 91, .box_w = 5, .box_h = 16, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 946, .adv_w = 133, .box_w = 2, .box_h = 16, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 950, .adv_w = 91, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 960, .adv_w = 143, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 7}
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
const lv_font_t lv_font_calibri_regular_18 = {
#else
lv_font_t lv_font_calibri_regular_18 = {
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



#endif /*#if LV_FONT_CALIBRI_REGULAR_18*/
