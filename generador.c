#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para una imagen en escala de grises
typedef struct {
    int width;
    int height;
    int max_value;
    unsigned char **pixels;
} Image;

// Función para crear una imagen vacía (color base)
Image *crearImagen(int width, int height, int color_base) {
    Image *img = (Image *)malloc(sizeof(Image));
    img->width = width;
    img->height = height;
    img->max_value = 255;

    img->pixels = (unsigned char **)malloc(height * sizeof(unsigned char *));
    for (int i = 0; i < height; i++) {
        img->pixels[i] = (unsigned char *)malloc(width * sizeof(unsigned char));
        for (int j = 0; j < width; j++)
            img->pixels[i][j] = (unsigned char)color_base;
    }

    return img;
}

// Dibuja un cuadrado sólido de cierto tamaño e intensidad
void dibujarCuadro(Image *img, int x, int y, int size, unsigned char color) {
    for (int i = y; i < y + size && i < img->height; i++) {
        for (int j = x; j < x + size && j < img->width; j++) {
            img->pixels[i][j] = color;
        }
    }
}

// Dibuja una cruz centrada en (x, y)
void dibujarCruz(Image *img, int x, int y, int size, unsigned char color) {
    int half = size / 2;
    for (int i = -half; i <= half; i++) {
        if (y + i >= 0 && y + i < img->height)
            img->pixels[y + i][x] = color;
        if (x + i >= 0 && x + i < img->width)
            img->pixels[y][x + i] = color;
    }
}

// Guarda la imagen en formato PGM (P2: ASCII)
void guardarPGM(Image *img, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Error: No se pudo crear el archivo %s\n", filename);
        return;
    }

    fprintf(f, "P2\n%d %d\n%d\n", img->width, img->height, img->max_value);
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            fprintf(f, "%d ", img->pixels[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Imagen guardada en %s\n", filename);
}

// Libera la memoria usada
void liberarImagen(Image *img) {
    for (int i = 0; i < img->height; i++)
        free(img->pixels[i]);
    free(img->pixels);
    free(img);
}

int main() {
    int width = 200, height = 300;
    Image *img = crearImagen(width, height, 200); // fondo gris claro

    printf("=== Generador de imagen PGM ===\n");
    printf("Dimensiones: %dx%d\n", width, height);

    int opcion;
    while (1) {
        printf("\n1. Dibujar cuadrado\n2. Dibujar cruz\n3. Guardar y salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        if (opcion == 3) break;

        int x, y, size;
        unsigned char color;
        printf("Ingrese posición (x y): ");
        scanf("%d %d", &x, &y);
        printf("Ingrese tamaño: ");
        scanf("%d", &size);
        printf("Ingrese intensidad (0-255): ");
        scanf("%hhu", &color);

        if (opcion == 1)
            dibujarCuadro(img, x, y, size, color);
        else if (opcion == 2)
            dibujarCruz(img, x, y, size, color);
        else
            printf("Opción inválida.\n");
    }

    guardarPGM(img, "imagen_generada.pgm");
    liberarImagen(img);
    return 0;
}
