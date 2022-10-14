#include <stdio.h>
#include "colors/rgb.h"

int main()
{
    RGB rgb;
    GRAYSCALE grayscale;
    HSL hsl;

    // DEGAULT RGB
    rgb_constructor(&rgb, 100, 200, 220);
    printf("rgb : %i, %i, %i\n", rgb.r, rgb.g, rgb.b);
    // rgb : 100, 200, 255

    // RGB VALIDATION
    rgb_constructor(&rgb, -100, 300, 999);
    printf("rgb : %i, %i, %i\n", rgb.r, rgb.g, rgb.b);
    // rgb : 0, 255, 255

    // RGB -> GRAYSCALE (AVERAGE)
    rgb_constructor(&rgb, 100, 200, 300);
    grayscale = rgb_to_grayscale_average(&rgb);
    printf("gray (average)    : %i\n", grayscale.gray);
    // gray (average)    : 183

    // RGB -> GRAYSCALE (LUMINOSITY)
    rgb_constructor(&rgb, 108, 140, 88);
    grayscale = rgb_to_grayscale_luminosity(&rgb);
    printf("gray (luminosity) : %i\n", grayscale.gray);
    // gray (luminosity) : 123

    // RGB -> GRAYSCALE (CUSTOM)
    rgb_constructor(&rgb, 96, 69, 99);
    grayscale = rgb_to_grayscale_custom(&rgb, 0.1, 0.2, 0.7);
    printf("gray (custom)     : %i\n", grayscale.gray);
    // gray (custom)     : 91

    // RGB -> HSL
    rgb_constructor(&rgb, 0, 100, 200);
    hsl = rgb_to_hsl(&rgb);
    printf("hsl : %i, %i, %i\n", hsl.h, hsl.s, hsl.l);
    // hsl : 0, 89, 41

    return 0;
}