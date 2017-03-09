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

//Fonu bastýr.
	draw_sprite(buffer,(BITMAP *)resimler->dat,fon_x,0);

hareketler();

textprintf_ex(buffer, font, 0,157, makecol(255,255,255), -1, "Puan = %d",haggar.puan);
textprintf_ex(buffer, font, 90,157, makecol(255,255,255), -1, "Toplam Mantar = %d    Ezik Mantar= %d ",mantar_sayisi,haggar.puan/5);

if(haggar.x > 310  && fon_x >= -283 && sag_tus) {fon_x--;haggar.x--;	//Haggar ilerliyorsa fonu geriye çek
for(short i=1;i<mantar_sayisi;i++){										//Hagarý x ini azaltýyoruz böylece yürüyormuþ gibi oluyor.
		mantar[i].x--;													//Mantarlarý bir kademe daha hýzlandýrdýk
		}																//Yoksa sabit duruyormuþ gibi oluyorlar
	}

for(short sayac=0;sayac<mantar_sayisi;sayac++){							//En uzak mantarý buluyoruz.yani son mantarý.
	if(mantar[sayac].x > uzak_mantar)
		uzak_mantar=mantar[sayac].x;
}																		//Son mantar ekranýn dýþýna çýktýðýnda yazý yazdýrýyoruz.
	if(--uzak_mantar <= 0 ) {textprintf_ex(buffer, font, 75,125, makecol(255,255,255), -1, "OYUN BITTI");}
}
