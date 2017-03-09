#include <allegro.h>
#include "oyuncu.h"

#ifndef HAREKET_H
#define HAREKET_H

#define AKTIF 1
#define PASIF 0
#define max_y 116
#define min_y 148
#define max_ziplama 55			//En fazla kaç pixel yukarý zýplayabileceði.

short max_yukseklik=0;
short buf_y=0;					//Sadece bir kere çalýþacak bir fonksiyon içerisinde murat.y'ye eþitlenecek.
short mantar_sayisi=100;
extern short mantar_frame;
extern short uzak_mantar;
bool mantar_eklendi=1;
extern BITMAP *buffer;
extern BITMAP *son;
extern BITMAP *buffer2;
extern SAMPLE *ezildi;
extern DATAFILE *resimler;
extern struct oyuncu haggar;
extern struct dusman mantar[1000];

void anim_yuru (void);			//Fonksiyon prototipleri.
void anim_zipla (void);
void frame_artir (bool kontrol);
void hareketler(void);
void ziplama(void);
void mantar_ekle (short sayi);
void anim_mantar_yuru(short sayi);


#endif
