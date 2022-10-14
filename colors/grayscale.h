
#define GRAY_AVEGAGE_PERCENT 0.33

#define GRAY_LUMINOSITY_RED 0.30
#define GRAY_LUMINOSITY_GREEN 0.59
#define GRAY_LUMINOSITY_BLUE 0.11

// [GRAYSCALE]
typedef struct
{
    int gray;
} GRAYSCALE;

void grayscale_constructor(GRAYSCALE *self, int gray);
void grayscale_gray(GRAYSCALE *self, int gray);

void grayscale_constructor(GRAYSCALE *self, int gray)
{
    grayscale_gray(self, gray);
}

void grayscale_gray(GRAYSCALE *self, int gray)
{
    if (gray > 255)
        self->gray = 255;
    else if (gray < 0)
        self->gray = 0;
    else
        self->gray = gray;
}
