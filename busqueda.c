#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int width;
    int height;
    int max_value;
    unsigned char **pixels;
} Image;

// ------------------------- Funciones base -------------------------

// Leer imagen PGM (formato P2)
Image *leerPGM(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Error: no se pudo abrir %s\n", filename);
        return NULL;
    }

    char type[3];
    fscanf(f, "%2s", type);
    if (strcmp(type, "P2") != 0) {
        printf("Error: formato no soportado (solo P2)\n");
        fclose(f);
        return NULL;
    }

    Image *img = (Image *)malloc(sizeof(Image));

    // Leer ancho, alto y valor máximo
    fscanf(f, "%d %d", &img->width, &img->height);
    fscanf(f, "%d", &img->max_value);

    img->pixels = (unsigned char **)malloc(img->height * sizeof(unsigned char *));
    for (int i = 0; i < img->height; i++) {
        img->pixels[i] = (unsigned char *)malloc(img->width * sizeof(unsigned char));
        for (int j = 0; j < img->width; j++) {
            int val;
            fscanf(f, "%d", &val);
            img->pixels[i][j] = (unsigned char)val;
        }
    }

    fclose(f);
    return img;
}

void liberarImagen(Image *img) {
    for (int i = 0; i < img->height; i++)
        free(img->pixels[i]);
    free(img->pixels);
    free(img);
}

// ------------------------- Búsqueda de patrón -------------------------

#define PATRON_SIZE 4

// Verifica si el patrón se encuentra en (x, y)
int compararPatron(Image *img, unsigned char patron[PATRON_SIZE][PATRON_SIZE], int x, int y) {
    for (int i = 0; i < PATRON_SIZE; i++) {
        for (int j = 0; j < PATRON_SIZE; j++) {
            if (y + i >= img->height || x + j >= img->width)
                return 0; // fuera de rango
            if (img->pixels[y + i][x + j] != patron[i][j])
                return 0; // no coincide
        }
    }
    return 1;
}

// Estrategia 1: Búsqueda exhaustiva (fuerza bruta)
void buscarPatronFuerzaBruta(Image *img, unsigned char patron[PATRON_SIZE][PATRON_SIZE]) {
    printf("Buscando patrón (fuerza bruta)...\n");
    for (int y = 0; y < img->height - PATRON_SIZE; y++) {
        for (int x = 0; x < img->width - PATRON_SIZE; x++) {
            if (compararPatron(img, patron, x, y)) {
                printf("Patrón encontrado en (%d, %d)\n", x, y);
                return;
            }
        }
    }
    printf("Patrón no encontrado.\n");
}

// Estrategia 2: Optimizada (solo ejemplo de estructura)
void buscarPatronOptimizada(Image *img, unsigned char patron[PATRON_SIZE][PATRON_SIZE]) {
    printf("Buscando patrón (versión optimizada)...\n");
    // TODO: implementar búsqueda reduciendo comparaciones innecesarias
    // Sugerencias:
    // - Usar una primera comparación con el valor promedio del patrón.
    // - Saltar posiciones si el primer pixel no coincide.
    printf("(Implementar esta función)\n");
}

// ------------------------- Programa principal -------------------------

int main() {
    char filename[100];
    printf("Ingrese el nombre del archivo PGM: ");
    scanf("%s", filename);

    Image *img = leerPGM(filename);
    if (!img) return 1;

    printf("Imagen cargada: %dx%d\n", img->width, img->height);

    // Definición de un patrón 4x4 (ejemplo simple)
    unsigned char patron[PATRON_SIZE][PATRON_SIZE] = {
        {0, 0, 0, 0},
        {0, 255, 255, 0},
        {0, 255, 255, 0},
        {0, 0, 0, 0}
    };

    buscarPatronFuerzaBruta(img, patron);
    buscarPatronOptimizada(img, patron);

    liberarImagen(img);
    return 0;
}
