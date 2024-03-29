/*
 * configure stb_image about
 * the image we will support
 */
#include "stb_image.h"

#define STBI_ONLY_JPEG
#define STBI_ONLY_PNG
#define STBI_NO_HDR
#define STBI_NO_LINEAR
#define STBI_NO_GIF
#define STBI_NO_PIC



#if defined _WIN32 || defined __CYGWIN__
 #ifdef LOT_BUILD
    // #define LOT_EXPORT __declspec(dllexport)
     #define LOT_EXPORT
   #else    // #define LOT_EXPORT __declspec(dllimport)
     #define LOT_EXPORT
   #endif
#else
  #ifdef LOT_BUILD
      #define LOT_EXPORT __attribute__ ((visibility ("default")))
  #else
      #define LOT_EXPORT
  #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * exported function wrapper from the library
 */

///@DEFOLD NOT COMPILE IF UNCOMMENT. CAN'T LOAD FROM FILE SYSTEM???
LOT_EXPORT unsigned char *lottie_image_load(char const *filename, int *x,
                                            int *y, int *comp, int req_comp)
{
  //  return stbi_load(filename, x, y, comp, req_comp);
}

LOT_EXPORT unsigned char *lottie_image_load_from_data(const char *imageData,
                                                      int len, int *x, int *y,
                                                      int *comp, int req_comp)
{
    unsigned char *data = (unsigned char *)imageData;
    return stbi_load_from_memory(data, len, x, y, comp, req_comp);
}

LOT_EXPORT void lottie_image_free(unsigned char *data)
{
    stbi_image_free(data);
}

#ifdef __cplusplus
}
#endif
