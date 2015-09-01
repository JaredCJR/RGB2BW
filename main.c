#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include "bmp.h"

int main(int argc, char *argv[]) {
    char openfile[] = "./pictures/ex.bmp";
    char savefile[] = "./pictures/ex_after.bmp";
    BMP *bmp = (BMP*) malloc(sizeof(BMP));

    uint64_t start = 0;
    uint64_t end = 0;
    uint64_t elapsed = 0;
    uint64_t avg = 0;
    struct timespec t_start, t_end;
    int loop = 100;
    int i;

    /* Load the image and print the infomation */
    bmpLoad(bmp, openfile);
    long stride = bmp->width * 4;
    //bmpPrint(bmp);

    /* RGBA to BW */
    printf("RGBA to BW is in progress....\n");
    #if defined(ORIGIN)
        printf("\n\n\n[Original version]\n");       
        system("./flush_cache.sh");
        elapsed = 0;
        avg = 0;
        for(i = 0; i < loop; i++){
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            rgbaToBw(bmp, bmp->width, bmp->height, stride);
            clock_gettime(CLOCK_MONOTONIC, &t_end);
            start = ((uint64_t)(t_start.tv_sec) * 1000000000LL + t_start.tv_nsec);
            end = (uint64_t)(t_end.tv_sec) * 1000000000LL + t_end.tv_nsec;
            elapsed += (end-start);
        }
        avg = elapsed/loop;
    #endif


    #if defined(VERSION1)
        printf("\n\n\n[Version 1 : using RGB table]\n");
        system("./flush_cache.sh");
        generateRGBTable();
        elapsed = 0;
        avg = 0;
        for(i = 0; i < loop; i++){
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            rgbaToBw_v1(bmp, bmp->width, bmp->height, stride);
            clock_gettime(CLOCK_MONOTONIC, &t_end);
            start = ((uint64_t)(t_start.tv_sec) * 1000000000LL + t_start.tv_nsec);
            end = (uint64_t)(t_end.tv_sec) * 1000000000LL + t_end.tv_nsec;
            elapsed += (end-start);
        }
        avg = elapsed/loop;
    #endif

    #if defined(VERSION2)
        printf("\n\n\n[Version 2 : using pointer]\n");
        system("./flush_cache.sh");
        elapsed = 0;
        avg = 0;
        for(i = 0; i < loop; i++){
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            rgbaToBw_v2(bmp, bmp->width, bmp->height, stride);
            clock_gettime(CLOCK_MONOTONIC, &t_end);
            start = ((uint64_t)(t_start.tv_sec) * 1000000000LL + t_start.tv_nsec);
            end = (uint64_t)(t_end.tv_sec) * 1000000000LL + t_end.tv_nsec;
            elapsed += (end-start);
        }
        avg = elapsed/loop;
    #endif

    #if defined(VERSION3)
        printf("\n\n\n[Version 3] : versoin1 + versoin2\n");
        system("./flush_cache.sh");
        generateRGBTable();
        elapsed = 0;
        avg = 0;
        for(i = 0; i < loop; i++){
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            rgbaToBw_v3(bmp, bmp->width, bmp->height, stride);
            clock_gettime(CLOCK_MONOTONIC, &t_end);
            start = ((uint64_t)(t_start.tv_sec) * 1000000000LL + t_start.tv_nsec);
            end = (uint64_t)(t_end.tv_sec) * 1000000000LL + t_end.tv_nsec;
            elapsed += (end-start);
        }
        avg = elapsed/loop;
    #endif

    #if 1
        printf("\n\n\n[Version 4] : NEON\n");
        system("./flush_cache.sh");
        generateRGBTable();
        elapsed = 0;
        avg = 0;
        for(i = 0; i < loop; i++){
            clock_gettime(CLOCK_MONOTONIC, &t_start);
            rgbaToBw_v4(bmp->data, bmp->width, bmp->height, stride);
            clock_gettime(CLOCK_MONOTONIC, &t_end);
            start = ((uint64_t)(t_start.tv_sec) * 1000000000LL + t_start.tv_nsec);
            end = (uint64_t)(t_end.tv_sec) * 1000000000LL + t_end.tv_nsec;
            elapsed += (end-start);
        }
        avg = elapsed/loop;
    #endif

    printf("Execution time of rgbaToBw() : %" PRIu64 " \n", avg);
    bmpSave(bmp, savefile);

    return 0;
}
