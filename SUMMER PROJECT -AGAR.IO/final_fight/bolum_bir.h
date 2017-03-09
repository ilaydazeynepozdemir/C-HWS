#include <allegro.h>
#include "oyuncu.h"

#ifndef BOLUM_BIR_H
#define BOLUM_BIR_H

bool sol_tus=0;							// Tuþlarý direk kullanmayýp önce bu deðerlere aktarýcaz.
bool sag_tus=0;
bool ust_tus=0;
bool alt_tus=0;
bool space_tus=0;

extern BITMAP *buffer;
extern DATAFILE *resimler;
extern BITMAP *son;
extern struct oyuncu haggar;
extern struct dusman mantar[1000];
extern short mantar_sayisi;
short fon_x=0;
short uzak_mantar=0;

extern short mantar_sayisi;
extern struct dusman mantar[1000];

void tuslari_kontrol_et(void);
void bolum_bir (void);
void frame_artir (bool kontrol);
void hareketler(void);
void mantar_ekle (short sayi);

#endif
