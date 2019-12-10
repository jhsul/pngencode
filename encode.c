#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <math.h>
#include <png.h>

int encode(char *source, char *dest, char verbose)
{
    FILE *src;
    FILE *dst;

    uint32_t size;
    uint32_t dim;

    uint8_t **row_pointers;

    png_structp png;
    png_infop info;

    /* Open source and dest files */

    if(verbose)
        printf("Attempting to open %s... ", source);

    src = fopen(source, "rb");
    if (!src)
    {
        printf("Error opening %s\n", source);
        return 1;
    }
    if(verbose)
        printf("Success!\n");

    if(verbose)
        printf("Attempting to open %s... ", dest);

    dst = fopen(dest, "wb");
    if (!dst)
    {
        printf("Error opening %s\n", dest);
        return 1;
    }
    if(verbose)
        printf("Success!\n");

    png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    info = png_create_info_struct(png);

    if (setjmp(png_jmpbuf(png)))
    {
        printf("Error running setjmp\n");
        return 1;
    }

    // Get the size of the file in bytes
    fseek(src, 0L, SEEK_END);
    size = ftell(src);
    rewind(src);

    dim = (uint32_t)ceil(sqrt(ceil((double)size / 3)));

    if(verbose)
    {
        printf("Size of %s: %d bytes\n", source, size);
        printf("Writing %s (%dx%d)...\n", dest, dim, dim);
    }
    row_pointers = (uint8_t **)malloc(sizeof(uint8_t *) * dim);
    for (int i = 0; i < dim; ++i)
        row_pointers[i] = (uint8_t *)calloc(3*dim, sizeof(uint8_t));

    for (int i = 0; i < dim; ++i)
    {
        // each row haS dim*3 bytes
        fread(row_pointers[i], 3*dim, 1, src);
    }

    png_init_io(png, dst);

    png_set_IHDR(
        png,
        info,
        dim, dim,
        8,
        PNG_COLOR_TYPE_RGB,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png, info);
    png_write_image(png, row_pointers);
    png_write_end(png, NULL);

    png_destroy_write_struct(&png, &info);
    fclose(src);
    fclose(dst);
    for (int i = 0; i < dim; ++i)
        free(row_pointers[i]);
    free(row_pointers);

    return 0;
}