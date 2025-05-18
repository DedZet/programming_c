// Найти все области, статистику глифов:
// размеры глифа, количество пикселей, плотность, связность, диаметр, периметр
// найти похожие глифы путем сравнения глифов одинакового размера.
// Похожие глифы должны содержать не более 10% раличающихся пикселей.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <math.h>

#define ISBIT(n,x) (((01<<(n))&(x))?1:0)
#define MAX_GLYPHS 50000
#define SIMILARITY_THRESHOLD 0.9 // 90% similarity (10% difference)

typedef struct img { //  структура глифа - картинки
   int w; int h;     // ширина и высота в пикслелях
   int dx;           // расстояние до следующего глифа (если буква)
   int count;        // черных пикселей всего
   int id;           // иднтификатор - "номер" глифа
   int bytes;        // количество байтов в битовой карте
   double density;   // плотность черных пикселей
   int diam;         // диаметр в манхеттенской метрике
   int perim;        // периметр глифа
   int conn;         // связность
   unsigned char *data;  //  битовая карта (неупакованная)
} IMG;

IMG *G[MAX_GLYPHS];
int N = 0;

void calculate_stats(IMG *img);
void find_similar_glyphs();
void print_glyph_stats(IMG *img);
int compare_glyphs(IMG *a, IMG *b);
void flood_fill(IMG *img, int x, int y, int *area, int *perimeter, int visited[][img->h]);

void outbyte(char byte) { // Вывод байта в двоичном виде
    int i;
    for (i = 7; i > -1; i--)
        putchar(ISBIT((i), byte) ? '*' : ' ');
    fflush(stdout);
}

void outbytes(int n, char *byte) { // Вывод массива байтов в двоичном виде
    int i;
    for (i = 0; i < n; i++)
        outbyte(byte[i]);
    putchar('\n');
}

int popcnt8(unsigned char i) {
    int count = 0;
    while (i) {
        ++count;
        i = (i - 1) & i;
    }
    return count;
}

int popcnt64(unsigned long long w) {
    w -= (w >> 1) & 0x5555555555555555ULL;
    w = (w & 0x3333333333333333ULL) + ((w >> 2) & 0x3333333333333333ULL);
    w = (w + (w >> 4)) & 0x0f0f0f0f0f0f0f0fULL;
    return (int)((w * 0x0101010101010101ULL) >> 56);
}

IMG *init_img(int id, int w, int h) { // создание пустого (чистого) глифа с заданными размерами
    IMG *t = (IMG *)malloc(sizeof(IMG));
    t->w = w;
    t->h = h;
    t->dx = 0;
    t->count = 0;
    t->id = id;
    t->bytes = (((w + 7) / 8) * h);
    t->data = (unsigned char *)calloc(t->bytes, 1);
    return t;
}

IMG *load_img(int id, char *File) {
    FILE *F; // считывание из файла глифа с номером id
    IMG *I = (IMG *)malloc(sizeof(IMG));
    F = fopen(File, "rb");
    if (!F) {
        perror("Error opening file");
        return NULL;
    }

    fread(&(I->w), sizeof(int), 1, F);
    fread(&(I->h), sizeof(int), 1, F);
    fread(&(I->dx), sizeof(int), 1, F);
    fread(&(I->count), sizeof(int), 1, F);
    fread(&(I->id), sizeof(int), 1, F);
    fread(&(I->bytes), sizeof(int), 1, F);
    I->data = (unsigned char *)calloc(I->bytes, 1);
    fread(I->data, 1, I->bytes, F);
    fclose(F);

    calculate_stats(I);
    return I;
}

void calculate_stats(IMG *img) {

    if (img->count == 0) {
        long int c = 0;
        unsigned long long *t = (unsigned long long *)img->data;
        unsigned char *s = (unsigned char *)img->data;
        int len = img->bytes;
		
		int i;
        for (i = 0; i < len / 8; i++)
            c += popcnt64(t[i]);

        for (i = (len / 8) * 8; i < len; i++)
            c += popcnt8(s[i]);

        img->count = c;
    }

    img->density = (double)img->count / (img->w * img->h);

    int min_x = img->w, max_x = 0;
    int min_y = img->h, max_y = 0;
    int found_pixel = 0;
	
	int y,x;
    for (y = 0; y < img->h; y++) {
        for (x = 0; x < img->w; x++) {
            int byte_index = x * (img->bytes / img->h) + y / 8;
            if (ISBIT((7 - y % 8), img->data[byte_index])) {
                found_pixel = 1;
                if (x < min_x) min_x = x;
                if (x > max_x) max_x = x;
                if (y < min_y) min_y = y;
                if (y > max_y) max_y = y;
            }
        }
    }

    if (found_pixel) {
        img->diam = (max_x - min_x) + (max_y - min_y);
    } else {
        img->diam = 0;
    }

    int visited[img->w][img->h];
    memset(visited, 0, sizeof(visited));
    int total_perimeter = 0;
    int regions = 0;
	

    for (y = 0; y < img->h; y++) {
        for (x = 0; x < img->w; x++) {
            int byte_index = x * (img->bytes / img->h) + y / 8;
            if (ISBIT((7 - y % 8), img->data[byte_index]) && !visited[x][y]) {
                int area = 0, perimeter = 0;
                flood_fill(img, x, y, &area, &perimeter, visited);
                total_perimeter += perimeter;
                regions++;
            }
        }
    }

    img->perim = total_perimeter;
    img->conn = regions;
}

void flood_fill(IMG *img, int x, int y, int *area, int *perimeter, int visited[][img->h]) {
    if (x < 0 || x >= img->w || y < 0 || y >= img->h || visited[x][y]) {
        return;
    }

    int byte_index = x * (img->bytes / img->h) + y / 8;
    if (!ISBIT((7 - y % 8), img->data[byte_index])) {
        return;
    }

    visited[x][y] = 1;
    (*area)++;

    int neighbors = 0;
    if (x > 0) {
        int n_byte_index = (x-1) * (img->bytes / img->h) + y / 8;
        if (ISBIT((7 - y % 8), img->data[n_byte_index])) neighbors++;
    }
    if (x < img->w-1) {
        int n_byte_index = (x+1) * (img->bytes / img->h) + y / 8;
        if (ISBIT((7 - y % 8), img->data[n_byte_index])) neighbors++;
    }
    if (y > 0) {
        int n_byte_index = x * (img->bytes / img->h) + (y-1) / 8;
        if (ISBIT((7 - (y-1) % 8), img->data[n_byte_index])) neighbors++;
    }
    if (y < img->h-1) {
        int n_byte_index = x * (img->bytes / img->h) + (y+1) / 8;
        if (ISBIT((7 - (y+1) % 8), img->data[n_byte_index])) neighbors++;
    }

    *perimeter += (4 - neighbors);

    flood_fill(img, x+1, y, area, perimeter, visited);
    flood_fill(img, x-1, y, area, perimeter, visited);
    flood_fill(img, x, y+1, area, perimeter, visited);
    flood_fill(img, x, y-1, area, perimeter, visited);
}

void print_glyph_stats(IMG *img) {
    printf("ID: %d\n", img->id);
    printf("Dimensions: %d x %d pixels\n", img->w, img->h);
    printf("Black pixels: %d\n", img->count);
    printf("Density: %.2f%%\n", img->density * 100);
    printf("Diameter (Manhattan): %d\n", img->diam);
    printf("Perimeter: %d\n", img->perim);
    printf("Connectivity (regions): %d\n", img->conn);
    printf("\n");
}

int compare_glyphs(IMG *a, IMG *b) {
    if (a->w != b->w || a->h != b->h) {
        return 0;
    }

    int total_pixels = a->w * a->h;
    int different_pixels = 0;

	int y,x;
    for (y = 0; y < a->h; y++) {
        for (x = 0; x < a->w; x++) {
            int a_byte_index = x * (a->bytes / a->h) + y / 8;
            int b_byte_index = x * (b->bytes / b->h) + y / 8;
            
            int a_bit = ISBIT((7 - y % 8), a->data[a_byte_index]);
            int b_bit = ISBIT((7 - y % 8), b->data[b_byte_index]);
            
            if (a_bit != b_bit) {
                different_pixels++;
            }
        }
    }

    double similarity = 1.0 - (double)different_pixels / total_pixels;
    return (similarity >= SIMILARITY_THRESHOLD);
}

void find_similar_glyphs() {
    printf("\nFinding similar glyphs...\n");
    
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = i + 1; j < N; j++) {
            if (compare_glyphs(G[i], G[j])) {
                printf("Glyph %d and %d are similar (size: %dx%d)\n", 
                       G[i]->id, G[j]->id, G[i]->w, G[i]->h);
            }
        }
    }
}

void process_directory(const char *path) {
    DIR *dir;
    struct dirent *entry;
    char filename[256];

    dir = opendir(path);
    if (!dir) {
        perror("Error opening directory");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strstr(entry->d_name, "glif_") == entry->d_name) {
            snprintf(filename, sizeof(filename), "%s/%s", path, entry->d_name);
            G[N] = load_img(N, filename);
            if (G[N]) {
                printf("Loaded %s\n", filename);
                print_glyph_stats(G[N]);
                N++;
                if (N >= MAX_GLYPHS) break;
            }
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <directory_with_glyphs>\n", argv[0]);
        return 1;
    }

    process_directory(argv[1]);
    find_similar_glyphs();

    int i;
    for (i = 0; i < N; i++) {
        free(G[i]->data);
        free(G[i]);
    }

    return 0;
}
