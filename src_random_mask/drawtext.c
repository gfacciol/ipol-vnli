/**
 * @file drawtext.c
 * @brief Draw text on an image
 * @author Pascal Getreuer <getreuer@gmail.com>
 * 
 * This file contains a simple implementation for drawing text onto an image.
 * Data for one 18-point sans serif font is included.
 * 
 * 
 * Copyright (c) 2012, Pascal Getreuer
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify it
 * under, at your option, the terms of the GNU General Public License as 
 * published by the Free Software Foundation, either version 3 of the 
 * License, or (at your option) any later version, or the terms of the 
 * simplified BSD license.
 *
 * You should have received a copy of these licenses along with this program.
 * If not, see <http://www.gnu.org/licenses/> and
 * <http://www.opensource.org/licenses/bsd-license.html>.
 */

#include "drawtext.h"


/** @brief Font info */
static struct fontinfo
{
    int Offset;             /**< Glyph offset in FontBitmapData       */
    unsigned char Width;    /**< Glyph width in pixels                */
    unsigned char Height;   /**< Glyph height in pixels               */
    char YShift;            /**< Vertical shift adjustment            */
    char Spacing;           /**< Horizontal spacing on the right side */
} FontInfo[] = {
    {   0,  0,  0,  0, 6},   /* space */ 
    {   0,  2, 13,  0, 1},   /* ! */
    {   4,  6,  5,  0, 1},   /* " */
    {   8, 12, 14, -1, 1},   /* # */
    {  29,  9, 17, -1, 1},   /* $ */
    {  49, 15, 13,  0, 1},   /* % */
    {  74, 12, 13,  0, 1},   /* & */
    {  94,  2,  5,  0, 1},   /* ' */
    {  96,  4, 16, -1, 1},   /* ( */
    { 104,  4, 16, -1, 1},   /* ) */
    { 112,  7,  8,  5, 1},   /* * */
    { 119, 12, 12,  1, 1},   /* + */
    { 137,  3,  4, 11, 1},   /* , */
    { 139,  5,  2,  7, 1},   /* - */
    { 141,  2,  2, 11, 1},   /* . */
    { 142,  6, 15,  0, 1},   /* / */
    { 154,  9, 13,  0, 1},   /* 0 */
    { 169,  8, 13,  0, 1},   /* 1 */
    { 182,  8, 13,  0, 1},   /* 2 */
    { 195,  9, 13,  0, 1},   /* 3 */
    { 210, 10, 13,  0, 1},   /* 4 */
    { 227,  8, 13,  0, 1},   /* 5 */
    { 240,  9, 13,  0, 1},   /* 6 */
    { 255,  8, 13,  0, 1},   /* 7 */
    { 268,  9, 13,  0, 1},   /* 8 */
    { 283,  9, 13,  0, 1},   /* 9 */
    { 298,  2,  9,  4, 2},   /* : */
    { 301,  3, 11,  4, 2},   /* ; */
    { 306, 11, 10,  3, 2},   /* < */
    { 320, 11,  6,  4, 2},   /* = */
    { 329, 11, 10,  3, 2},   /* > */
    { 343,  7, 13,  0, 1},   /* ? */
    { 355, 16, 16,  0, 1},   /* @ */
    { 387, 12, 13,  0, 1},   /* A */
    { 407,  9, 13,  0, 1},   /* B */
    { 422, 11, 13,  0, 1},   /* C */
    { 440, 11, 13,  0, 1},   /* D */
    { 458,  8, 13,  0, 1},   /* E */
    { 471,  8, 13,  0, 1},   /* F */
    { 484, 11, 13,  0, 1},   /* G */
    { 502, 10, 13,  0, 1},   /* H */
    { 519,  2, 13,  0, 1},   /* I */
    { 523,  5, 17, -4, 1},   /* J */
    { 534, 10, 13,  0, 1},   /* K */
    { 551,  8, 13,  0, 1},   /* L */
    { 564, 12, 13,  0, 1},   /* M */
    { 584, 10, 13,  0, 1},   /* N */
    { 601, 12, 13,  0, 1},   /* O */
    { 621,  8, 13,  0, 1},   /* P */
    { 634, 12, 15, -2, 1},   /* Q */
    { 657, 10, 13,  0, 1},   /* R */
    { 674,  9, 13,  0, 1},   /* S */
    { 689, 12, 13,  0, 1},   /* T */
    { 709, 10, 13,  0, 1},   /* U */
    { 726, 12, 13,  0, 1},   /* V */
    { 746, 17, 13,  0, 0},   /* W */
    { 774, 11, 13,  0, 0},   /* X */
    { 792, 12, 13,  0, 0},   /* Y */
    { 812, 11, 13,  0, 1},   /* Z */
    { 830,  4, 16, -1, 1},   /* [ */
    { 838,  6, 15, -2, 1},   /* \ */
    { 850,  4, 16, -1, 1},   /* ] */
    { 858, 11,  5,  1, 1},   /* ^ */
    { 865,  9,  2, 16, 1},   /* _ */
    { 868,  4,  3, 10, 1},   /* ` */
    { 870,  8, 10,  3, 1},   /* a */
    { 880,  9, 14, -1, 1},   /* b */
    { 896,  8, 10,  3, 1},   /* c */
    { 906,  9, 14, -1, 1},   /* d */
    { 922, 10, 10,  3, 1},   /* e */
    { 935,  7, 14, -1, 1},   /* f */
    { 948,  9, 14,  3, 1},   /* g */
    { 964,  8, 14, -1, 1},   /* h */
    { 978,  2, 14, -1, 1},   /* i */
    { 982,  4, 18, -1, 1},   /* j */
    { 991,  8, 14, -1, 1},   /* k */
    {1005,  2, 14, -1, 1},   /* l */
    {1009, 14, 10,  3, 1},   /* m */
    {1027,  8, 10,  3, 1},   /* n */
    {1037, 10, 10,  3, 1},   /* o */
    {1050,  9, 14,  3, 1},   /* p */
    {1066,  9, 14,  3, 1},   /* q */
    {1082,  6, 10,  3, 1},   /* r */
    {1090,  7, 10,  3, 1},   /* s */
    {1099,  6, 13,  0, 1},   /* t */
    {1109,  8, 10,  3, 1},   /* u */
    {1119, 10, 10,  3, 0},   /* v */
    {1132, 13, 10,  3, 1},   /* w */
    {1149, 10, 10,  3, 1},   /* x */
    {1162, 10, 14,  3, 1},   /* y */
    {1180,  8, 10,  3, 1},   /* z */
    {1190,  8, 17, -1, 1},   /* { */
    {1207,  2, 18, -1, 1},   /* | */
    {1212,  8, 17, -1, 1},   /* } */
    {1229, 11,  3,  5, 1}};  /* ~ */

    
/** @brief Font bitmap data */
static unsigned char FontBitmapData[] =
    {255, 255, 195, 192, 207, 60, 243, 204, 4, 64, 68, 12, 192, 200, 127, 
    247, 255, 9, 129, 144, 255, 239, 254, 19, 3, 48, 50, 2, 32, 8, 4, 15, 
    143, 238, 150, 67, 224, 252, 31, 4, 194, 113, 127, 243, 240, 32, 16, 8, 
    0, 120, 17, 152, 67, 49, 134, 98, 12, 200, 25, 144, 30, 79, 1, 51, 2, 
    102, 8, 204, 49, 152, 67, 49, 3, 192, 15, 1, 248, 48, 131, 0, 56, 3, 192, 
    110, 108, 118, 195, 204, 24, 225, 199, 254, 62, 112, 255, 192, 50, 102, 
    76, 204, 204, 196, 102, 35, 196, 102, 35, 51, 51, 50, 102, 76, 17, 37, 
    81, 195, 138, 164, 136, 6, 0, 96, 6, 0, 96, 6, 15, 255, 255, 240, 96, 6, 
    0, 96, 6, 0, 96, 109, 64, 255, 192, 240, 12, 49, 134, 24, 227, 12, 49, 
    198, 24, 99, 12, 0, 62, 63, 152, 216, 60, 30, 15, 7, 131, 193, 224, 216, 
    207, 227, 224, 56, 248, 216, 24, 24, 24, 24, 24, 24, 24, 24, 255, 255, 
    124, 254, 135, 3, 3, 7, 6, 12, 24, 48, 96, 255, 255, 126, 127, 160, 224, 
    48, 57, 248, 252, 7, 1, 128, 224, 255, 231, 224, 7, 1, 192, 176, 108, 19, 
    8, 198, 49, 12, 255, 255, 240, 48, 12, 3, 0, 126, 126, 96, 96, 124, 126, 
    71, 3, 3, 3, 135, 254, 124, 30, 31, 156, 92, 12, 6, 243, 253, 199, 193, 
    224, 216, 239, 227, 224, 255, 255, 6, 6, 6, 14, 12, 12, 28, 24, 24, 56, 
    48, 62, 63, 184, 248, 62, 59, 249, 253, 199, 193, 224, 248, 239, 227, 
    224, 62, 63, 184, 216, 60, 31, 29, 254, 123, 1, 129, 209, 207, 195, 192, 
    240, 3, 192, 108, 0, 3, 106, 0, 0, 32, 60, 31, 31, 15, 129, 240, 15, 128, 
    62, 1, 224, 4, 255, 255, 252, 0, 0, 15, 255, 255, 192, 128, 30, 1, 240, 
    7, 192, 62, 7, 195, 227, 224, 240, 16, 0, 121, 254, 24, 48, 97, 134, 24, 
    48, 96, 1, 131, 0, 7, 224, 31, 248, 60, 28, 112, 6, 96, 3, 227, 99, 199, 
    227, 198, 99, 198, 102, 199, 252, 227, 112, 96, 0, 112, 0, 56, 16, 31, 
    240, 7, 192, 6, 0, 96, 15, 0, 240, 25, 129, 152, 25, 131, 12, 63, 199, 
    254, 96, 102, 6, 192, 48, 254, 127, 176, 216, 108, 55, 243, 249, 134, 
    193, 224, 240, 255, 239, 224, 15, 199, 253, 192, 176, 12, 1, 128, 48, 6, 
    0, 192, 12, 1, 192, 159, 240, 252, 254, 31, 243, 7, 96, 124, 7, 128, 240, 
    30, 3, 192, 120, 31, 7, 127, 207, 224, 255, 255, 192, 192, 192, 255, 255, 
    192, 192, 192, 192, 255, 255, 255, 255, 192, 192, 192, 254, 254, 192, 
    192, 192, 192, 192, 192, 15, 199, 253, 192, 176, 12, 1, 135, 240, 254, 3, 
    192, 108, 13, 193, 159, 225, 248, 192, 240, 60, 15, 3, 192, 255, 255, 
    255, 3, 192, 240, 60, 15, 3, 192, 192, 255, 255, 255, 192, 24, 198, 49, 
    140, 99, 24, 198, 49, 140, 254, 224, 193, 176, 204, 99, 48, 216, 60, 15, 
    3, 96, 204, 49, 140, 51, 6, 192, 192, 192, 192, 192, 192, 192, 192, 192, 
    192, 192, 192, 192, 255, 255, 224, 127, 15, 240, 253, 139, 217, 189, 155, 
    207, 60, 243, 198, 60, 99, 192, 60, 3, 192, 48, 224, 248, 63, 15, 195, 
    216, 246, 60, 207, 27, 198, 240, 252, 63, 7, 193, 192, 31, 131, 252, 112, 
    230, 6, 192, 60, 3, 192, 60, 3, 192, 54, 6, 112, 227, 252, 31, 128, 252, 
    254, 199, 195, 195, 199, 254, 252, 192, 192, 192, 192, 192, 31, 131, 252, 
    112, 230, 6, 192, 60, 3, 192, 60, 3, 192, 54, 6, 112, 227, 252, 31, 128, 
    24, 0, 192, 252, 63, 140, 115, 12, 195, 49, 207, 227, 240, 198, 48, 204, 
    51, 6, 193, 192, 62, 63, 184, 88, 12, 3, 224, 252, 7, 1, 128, 224, 255, 
    231, 224, 255, 255, 255, 6, 0, 96, 6, 0, 96, 6, 0, 96, 6, 0, 96, 6, 0, 
    96, 6, 0, 192, 240, 60, 15, 3, 192, 240, 60, 15, 3, 192, 240, 54, 25, 
    254, 63, 0, 192, 54, 6, 96, 102, 6, 48, 195, 12, 25, 129, 152, 25, 128, 
    240, 15, 0, 96, 6, 0, 193, 193, 224, 224, 216, 216, 204, 108, 102, 54, 
    51, 27, 24, 216, 216, 108, 108, 54, 54, 27, 27, 7, 7, 3, 131, 129, 193, 
    192, 112, 230, 24, 230, 13, 192, 240, 28, 3, 128, 120, 27, 7, 48, 199, 
    48, 110, 14, 224, 118, 6, 48, 193, 152, 25, 128, 240, 6, 0, 96, 6, 0, 96, 
    6, 0, 96, 6, 0, 255, 255, 252, 7, 1, 192, 48, 14, 3, 128, 224, 24, 6, 1, 
    192, 127, 255, 254, 255, 204, 204, 204, 204, 204, 204, 255, 195, 6, 24, 
    97, 195, 12, 48, 225, 134, 24, 48, 192, 255, 51, 51, 51, 51, 51, 51, 255, 
    14, 3, 96, 198, 48, 108, 6, 255, 255, 192, 198, 48, 60, 126, 71, 3, 63, 
    255, 195, 199, 255, 123, 192, 96, 48, 24, 13, 231, 251, 143, 131, 193, 
    224, 240, 124, 127, 246, 240, 30, 127, 97, 192, 192, 192, 192, 97, 127, 
    30, 1, 128, 192, 96, 51, 219, 255, 143, 131, 193, 224, 240, 124, 119, 
    249, 236, 31, 31, 230, 31, 3, 255, 255, 252, 1, 129, 127, 199, 224, 30, 
    124, 193, 143, 255, 204, 24, 48, 96, 193, 131, 6, 0, 61, 191, 248, 248, 
    60, 30, 15, 7, 199, 127, 158, 192, 104, 103, 241, 240, 192, 192, 192, 
    192, 222, 254, 231, 195, 195, 195, 195, 195, 195, 195, 240, 255, 255, 
    240, 51, 0, 51, 51, 51, 51, 51, 51, 254, 192, 192, 192, 192, 195, 198, 
    204, 216, 240, 240, 216, 204, 198, 195, 255, 255, 255, 240, 222, 123, 
    251, 238, 56, 240, 195, 195, 15, 12, 60, 48, 240, 195, 195, 15, 12, 48, 
    222, 254, 231, 195, 195, 195, 195, 195, 195, 195, 30, 31, 230, 27, 3, 
    192, 240, 60, 13, 134, 127, 135, 128, 222, 127, 184, 248, 60, 30, 15, 7, 
    199, 255, 111, 48, 24, 12, 6, 0, 61, 191, 248, 248, 60, 30, 15, 7, 199, 
    127, 158, 192, 96, 48, 24, 12, 223, 254, 48, 195, 12, 48, 195, 0, 125, 
    255, 15, 7, 195, 193, 195, 254, 248, 97, 134, 63, 253, 134, 24, 97, 134, 
    31, 60, 195, 195, 195, 195, 195, 195, 195, 231, 127, 123, 192, 240, 54, 
    25, 134, 51, 12, 195, 48, 120, 30, 3, 0, 199, 30, 56, 241, 70, 219, 102, 
    219, 54, 217, 162, 199, 28, 56, 225, 199, 0, 225, 216, 99, 48, 204, 30, 
    7, 131, 48, 204, 97, 184, 112, 192, 240, 54, 25, 134, 51, 12, 193, 224, 
    120, 12, 3, 0, 192, 96, 120, 28, 0, 255, 255, 6, 12, 28, 56, 48, 112, 
    255, 255, 15, 31, 24, 24, 24, 24, 24, 240, 240, 56, 24, 24, 24, 24, 24, 
    31, 15, 255, 255, 255, 255, 240, 240, 248, 24, 24, 24, 24, 24, 15, 15, 
    28, 24, 24, 24, 24, 24, 248, 240, 124, 63, 254, 31, 0};


/** @brief Draw a pixel on an image */
static void PutPixel(float *Image, int Width, int Height, 
    int x, int y)
{
    if(0 <= x && x < Width && 0 <= y && y < Height){
        Image[x + Width*y] = 255;
        Image[x + Width*y + Height*Width] = 255;
        Image[x + Width*y + 2*Height*Width] = 255;
	}
}
    

/** 
 * @brief Draw a packed binary glyph on an image 
 * @param Image the destination image
 * @param Width, Height the image dimensions
 * @param Glyph the packed binary glyph data
 * @param GlyphWidth, GlyphHeight the glyph dimensions in pixels
 * @param x0, y0 the upper-left corner of the glyph
 * @param Value the grayscale value of the drawn glyph
 */
static void DrawGlyph(float *Image, int Width, int Height, 
    const unsigned char *Glyph, int GlyphWidth, int GlyphHeight, 
    int x0, int y0)
{
    unsigned int Packed, Mask;
    int x = 0, y = 0;
    
    if(GlyphWidth)
        while(1)
        {
            /* Unpack each byte in the glyph data into eight pixels */
            for(Mask = 0x80, Packed = *Glyph; Mask; Mask >>= 1)
            {
                if((Packed & Mask))
                    PutPixel(Image, Width, Height, x0 + x, y0 + y);
                
                if(++x >= GlyphWidth)
                {
                    x = 0;
                    
                    if(++y >= GlyphHeight)
                        return;
                }
            }
            
            Glyph++;
        }    
}    
 

 /** @brief Compute the width of text in pixels */
int TextWidth(const char *Text)
{
    int c, Width = 0;
    
    if(!Text || !*Text)
        return 0;
    
    while((c = *(Text++)))
    {
        if(!(32 <= c && c <= 126))
            c = 63;
        
        c -= 32;        
        Width += FontInfo[c].Width + FontInfo[c].Spacing;
    }
    
    Width -= FontInfo[c].Spacing;
    return Width;
}


/** 
 * @brief Draw text on an image 
 * @param Image the destination image
 * @param Width, Height the image dimensions
 * @param x0, y0 the upper-left corner of the text
 * @param Value the grayscale value of the drawn text
 * @param Text the text to be drawn
 */
void DrawText(float *Image, int Width, int Height,
    int x0, int y0, const char *Text)
{
    int c;
    
    if(!Text || !*Text)
        return;
    
    while((c = *(Text++)))
    {
        if(!(32 <= c && c <= 126))
            c = 63;
        
        c -= 32;
        DrawGlyph(Image, Width, Height, 
            FontBitmapData + FontInfo[c].Offset,
            FontInfo[c].Width, FontInfo[c].Height,
            x0, y0 + FontInfo[c].YShift);
        
        x0 += FontInfo[c].Width + FontInfo[c].Spacing;
    }
}
