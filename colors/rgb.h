#include "grayscale.h"
#include "hsl.h"

// [RGB]
typedef struct rgb
{
    int r;
    int g;
    int b;
} RGB;

/*
 * Definitions
 */
void rgb_constructor(RGB *self, int r, int g, int b);
int __rgb_validator(int color);

GRAYSCALE rgb_to_grayscale_average(RGB *self);
GRAYSCALE rgb_to_grayscale_luminosity(RGB *self);
GRAYSCALE rgb_to_grayscale_custom(RGB *self, float r_percent, float g_percent, float b_percent);

int _grayscale_average(int r, int g, int b);
int _grayscale_luminosity(int r, int g, int b);
int _grayscale_custom(int r, int g, int b, float r_percent, float g_percent, float b_percent);

HSL rgb_to_hsl(RGB *self);

double __rgb_max(double _r, double _g, double _b);
double __rgb_min(double _r, double _g, double _b);

double __hue_calculation_max_r(double delta, double _g, double _b);
double __hue_calculation_max_g(double delta, double _b, double _r);
double __hue_calculation_max_b(double delta, double _r, double _g);
double __saturation_calculation(double delta, double _l);
double __lightness_calculation(double c_max, double c_min);
double __module(double value);

/*
 * Implementations
 */

// constructor
void rgb_constructor(RGB *self, int r, int g, int b)
{
    self->r = __rgb_validator(r);
    self->g = __rgb_validator(g);
    self->b = __rgb_validator(b);
}

int __rgb_validator(int color)
{
    if (color < 0)
        return 0;
    else if (color > 255)
        return 255;
    else
        return color;
}

GRAYSCALE rgb_to_grayscale_average(RGB *self)
{
    GRAYSCALE grayscale;

    int gray =
        _grayscale_average(
            self->r,
            self->g,
            self->b);

    grayscale_constructor(&grayscale, gray);

    return grayscale;
}

GRAYSCALE rgb_to_grayscale_luminosity(RGB *self)
{
    GRAYSCALE grayscale;

    int gray =
        _grayscale_luminosity(
            self->r,
            self->g,
            self->b);

    grayscale_constructor(&grayscale, gray);

    return grayscale;
}

GRAYSCALE rgb_to_grayscale_custom(RGB *self,
                                  float r_percent,
                                  float g_percent,
                                  float b_percent)
{
    GRAYSCALE grayscale;

    int gray =
        _grayscale_custom(
            self->r,
            self->g,
            self->b,
            r_percent,
            g_percent,
            b_percent);

    grayscale_constructor(&grayscale, gray);

    return grayscale;
}

int _grayscale_average(int r, int g, int b)
{
    return _grayscale_custom(
        r,
        g,
        b,
        GRAY_AVEGAGE_PERCENT,
        GRAY_AVEGAGE_PERCENT,
        GRAY_AVEGAGE_PERCENT);
}

int _grayscale_luminosity(int r, int g, int b)
{
    return _grayscale_custom(
        r,
        g,
        b,
        GRAY_LUMINOSITY_RED,
        GRAY_LUMINOSITY_GREEN,
        GRAY_LUMINOSITY_BLUE);
}

int _grayscale_custom(int r,
                      int g,
                      int b,
                      float r_percent,
                      float g_percent,
                      float b_percent)
{
    return (int)(r_percent * r) +
           (int)(g_percent * g) +
           (int)(b_percent * b);
}

HSL rgb_to_hsl(RGB *self)
{
    double _r, _g, _b;
    double divider = 255.0;
    double c_max, c_min;
    double delta;
    double _h, _s, _l;
    int h, s, l;
    HSL hsl;

    _r = ((double)(self->r)) / divider;
    _g = ((double)(self->g)) / divider;
    _b = ((double)(self->b)) / divider;

    c_max = __rgb_max(_r, _g, _b);
    c_min = __rgb_min(_r, _g, _b);

    delta = c_max - c_min;

    _l = __lightness_calculation(c_max, c_min);

    if (delta == 0)
    {
        _h = 0.0;
    }
    else
    {
        if (_r == c_max)
            _h = __hue_calculation_max_r(delta, _g, _b);
        else if (_g == c_max)
            _h = __hue_calculation_max_g(delta, _b, _r);
        else
            _h = __hue_calculation_max_b(delta, _r, _g);
    }

    _s = __saturation_calculation(delta, _l);

    _s *= 100;
    _l *= 100;

    h = (int)(_h);
    s = (int)(_s);
    l = (int)(_l);

    hsl_constructor(&hsl, h, s, l);

    return hsl;
}

double __rgb_max(double _r, double _g, double _b)
{
    if (_r >= _g && _r >= _b)
        return _r;
    else if (_g >= _r && _g >= _b)
        return _g;
    else
        return _b;
}

double __rgb_min(double _r, double _g, double _b)
{
    if (_r <= _g && _r <= _b)
        return _r;
    else if (_g <= _r && _g <= _b)
        return _g;
    else
        return _b;
}

double __hue_calculation_max_r(double delta, double _g, double _b)
{
    double diff = _g - _b;
    double div = diff / delta;
    int div_int = (int)(div);
    int div_mod_6 = div_int % 6;
    int mul_60_deg = div_mod_6 * 60;
    int result = mul_60_deg % 360;
    return (double)(result);
}

double __hue_calculation_max_g(double delta, double _b, double _r)
{
    double diff = _b - _r;
    double div = diff / delta;
    double plus_2 = div + 2.0;
    double mul_60_deg = plus_2 * 60.0;
    int mul_60_deg_int = (int)(mul_60_deg);
    int result = mul_60_deg_int % 360;
    return (double)(result);
}

double __hue_calculation_max_b(double delta, double _r, double _g)
{
    double diff = _r - _g;
    double div = diff / delta;
    double plus_4 = div + 4.0;
    double mul_60_deg = plus_4 * 60.0;
    int mul_60_deg_int = (int)(mul_60_deg);
    int result = mul_60_deg_int % 360;
    return (double)(result);
}

double __saturation_calculation(double delta, double _l)
{
    return delta / (1 - __module((2.0 * _l) - 1));
}

double __lightness_calculation(double c_max, double c_min)
{
    return (c_max + c_min) / 2;
}

double __module(double value)
{
    if (value >= 0.0)
        return value;
    else
        return -value;
}