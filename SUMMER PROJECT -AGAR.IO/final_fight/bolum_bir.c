#include "bolum_bir.h"

void tuslari_kontrol_et(void){
	if(key[KEY_LEFT]) sol_tus=1;
	else sol_tus=0;
	if(key[KEY_RIGHT]) sag_tus=1;
	else sag_tus=0;
	if(key[KEY_UP]) ust_tus=1;
	else ust_tus=0;
	if(key[KEY_DOWN]) alt_tus=1;
	else alt_tus=0;
	if(key[KEY_SPACE]) space_tus=1;
	else space_tus=0;
	
}
 
void bolum_bir (void){

//Fonu bast�r.
	draw_sprite(buffer,(BITMAP *)resimler->dat,fon_x,0);

hareketler();

textprintf_ex(buffer, font, 0,157, makecol(255,255,255), -1, "Puan = %d",haggar.puan);
textprintf_ex(buffer, font, 90,157, makecol(255,255,255), -1, "Toplam Mantar = %d    Ezik Mantar= %d ",mantar_sayisi,haggar.puan/5);

if(haggar.x > 310  && fon_x >= -283 && sag_tus) {fon_x--;haggar.x--;	//Haggar ilerliyorsa fonu geriye �ek
for(short i=1;i<mantar_sayisi;i++){										//Hagar� x ini azalt�yoruz b�ylece y�r�yormu� gibi oluyor.
		mantar[i].x--;													//Mantarlar� bir kademe daha h�zland�rd�k
		}																//Yoksa sabit duruyormu� gibi oluyorlar
	}

for(short sayac=0;sayac<mantar_sayisi;sayac++){							//En uzak mantar� buluyoruz.yani son mantar�.
	if(mantar[sayac].x > uzak_mantar)
		uzak_mantar=mantar[sayac].x;
}																		//Son mantar ekran�n d���na ��kt���nda yaz� yazd�r�yoruz.
	if(--uzak_mantar <= 0 ) {textprintf_ex(buffer, font, 75,125, makecol(255,255,255), -1, "OYUN BITTI");}
}
