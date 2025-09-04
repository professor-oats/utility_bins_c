// THANKS Kaan Alpar

#include <stdio.h>
#include <string.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

int main(int argc, char *argv[]) {
    //  _.:-=+*#%@ this one
    // -.,)+'/ъьийлуэяоаеюсжчкхвнцгдшмпбфрт
    //  .,:-гпрдэхбфйж
    // .,:-гпрдэх%фйж
    // `^\",:;Il!i~+_-?][}{1)(|\\/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$
    char Chars[] =" .:-=+*#%@"; // бвгджзклмнпрстфхцчшщаеёиоуыэюяйъь)-+./,";  // Have this as Density
    int CharsLen = strlen(Chars);
    int Width, Height, PixelSize;
    unsigned char *ImageData = stbi_load(argv[1], &Width, &Height, &PixelSize, 0);

    if (ImageData) {
        unsigned char *Pixels = ImageData;
        for (int RowIndex = 0; RowIndex < Height; RowIndex++) {
            for (int ColumnIndex = 0; ColumnIndex < Width; ColumnIndex++) {
                unsigned char R = *Pixels++;
                unsigned char G = *Pixels++;
                unsigned char B = *Pixels++;
                if (PixelSize >=4) {
                    unsigned char A = *Pixels++;
                }

                //float Avg = (R + G + B) / 3.0;
                float Avg = (R * 0.3 + G * 0.30 + B * 0.6);
                int CharIndex = (int)(CharsLen * (Avg/255.0));
                putchar(Chars[CharIndex]);

            }
            putchar('\n');
        }
    }

    else {
        printf("Failed to load image %s.\n", argv[1]);
    }

    return 0;

}
