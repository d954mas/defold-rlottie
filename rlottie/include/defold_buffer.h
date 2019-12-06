#pragma once
#include <dmsdk/sdk.h>
#include <math.h>

#define min(a,b)             (((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a,b)             (((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi,ma)      min(max(a,mi),ma)         // clamp: Clamp value into set range.

struct Buffer {
	int width;
	int height;
	int channels;
	uint8_t* stream;
};

Buffer BufferCreate(int, int,int, dmScript::LuaHBuffer*);
void BufferClear(Buffer &buffer);

static inline void BufferDrawPixel(Buffer &b,int x, int y, uint32_t color){
	uint8_t red = (color & 0xFF000000) >> 24;
	uint8_t green = (color & 0x00FF0000) >> 16;
	uint8_t blue = (color & 0x0000FF00) >> 8;
    int start = ((b.height - y - 1) * b.width + x)*4;
    b.stream[start] = red;
    b.stream[start+1] = green;
    b.stream[start+2] = blue;
    b.stream[start+3] = 256;
}

static inline void BufferDrawRect(Buffer &b,int x, int y,int w, int h, uint32_t color){
    for (int yi = 0; yi< h; yi++){
        for (int xi = 0; xi< w; xi++){
            BufferDrawPixel(b,x + xi,y + yi,color);
        }
    }
}
