#include <allegro.h>
#include "oyuncu.h"

#ifndef MAIN_H
#define MAIN_H

BITMAP *buffer;
BITMAP *mantar_resim;
BITMAP *son;
DATAFILE *resimler;
SAMPLE *ezildi;

struct oyuncu haggar;
struct dusman mantar[1000];

void bolum_bir (void);
void tuslari_kontrol_et(void);

#endif