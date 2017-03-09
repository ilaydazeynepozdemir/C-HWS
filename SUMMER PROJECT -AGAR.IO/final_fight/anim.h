#include <allegro.h>
#include "oyuncu.h"

#ifndef ANIM_H
#define ANIM_H

extern struct oyuncu haggar;
extern struct dusman mantar[1000];
short mantar_frame=0;

void anim_yuru (void);
void frame_artir (bool kontrol);
void anim_zipla (void);
void anim_mantar_yuru(short sayi);

#endif
