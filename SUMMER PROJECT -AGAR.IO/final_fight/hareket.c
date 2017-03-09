#include "hareket.h"

void hareketler(void){
		
		if(sag_tus){
		haggar.yon=1;
		if(!haggar.ziplama && !haggar.dusme)
		anim_yuru();
		else if(haggar.ziplama || haggar.dusme) anim_zipla(); 
		haggar.x++;
	}
	else if(sol_tus){
		haggar.yon=0;
		if(!haggar.ziplama && !haggar.dusme)
		anim_yuru ();
		else if(haggar.ziplama || haggar.dusme) anim_zipla();
		haggar.x--;
	}
	else if(haggar.ziplama)anim_zipla();					//Y�n tu�lar� bas�lmadan z�pland�ysa z�plama animasyonunu g�ster.

	if(ust_tus && !haggar.ziplama && !haggar.dusme && haggar.y>(max_y-35)){
	anim_yuru();
	haggar.y--;	
	}
	else if(alt_tus && !haggar.ziplama && !haggar.dusme && haggar.y<(min_y-35)){
	anim_yuru();
	haggar.y++;	
	}
	
	if(!key[KEY_LEFT] && !key[KEY_RIGHT] && !key[KEY_SPACE] && !key[KEY_UP] && !key[KEY_DOWN]	//Tu�lara bas�lmad�ysa frameyi s�f�rla
	&& !haggar.dusme && !haggar.ziplama){	
	haggar.frame=0;}
	else haggar.frame++;									//Haggar frame sayac�n� art�r

	ziplama();
	mantar_frame++;											//Mantarlar�n frame sayac�n� art�r
	mantar_ekle(mantar_sayisi);								//100 adet mantar ekle

	masked_blit((BITMAP *)resimler[1].dat,buffer,haggar.frame_x,haggar.frame_y,
		haggar.x,haggar.y,28,35);
	
}

void ziplama(void){

if(space_tus && !haggar.dusme && !haggar.ziplama){			//Z�plamay� kontrol et.
haggar.frame=0;												//Frame s�f�rl�yoruz.
max_yukseklik=haggar.y-max_ziplama;							//Oyuncunun y sini buffera aktar ve ziplama
haggar.ziplama=AKTIF;										//Kontrol�n� aktifle�tir.Sonrada z�planabi
buf_y=haggar.y;												//bilecek max y�ksekli�i max_yukseklige ata.
}

if(haggar.ziplama && haggar.y>=max_yukseklik && !haggar.dusme){ 		//Yumu�ak bir z�play�� i�in �nce 2 pixel
	if(haggar.y<=(max_yukseklik+10))									// y�ksel.Max y�ksekli�e 10 kala 1 er pixel
	haggar.y-=1;														//y�ksel.B�ylece y�kselme ve yava�lama sa�
	else 																//lan�r.Daha ho� olur.
	haggar.y-=2; }

if(haggar.y==(max_yukseklik))											//E�er max y�ksekli�e eri�tiyse ziplamay�
{haggar.dusme=AKTIF;haggar.ziplama=PASIF;--haggar.y;haggar.zipladi=1;}	//durdur.Ve d��meyi aktifle�tir.

if(haggar.dusme && haggar.y<buf_y){										//dusme aktif ise ve murat.y buf_y den 
haggar.y+=2;}															//k���k ise 2 �er pixel a�a�� in.
else if(haggar.y>=buf_y){												//�ayet murat.y buf_y den b�y�k ise yada
haggar.dusme=PASIF;}													//e�it ise d��meyi durdur.

if(haggar.zipladi && !haggar.dusme){haggar.frame_y=0;					//Sadece z�plama olay� bitti�inde bir kez
if(haggar.yon) haggar.frame_x=31; else haggar.frame_x=0;				//�al���r.Yere de�di�inde normal duru�a
haggar.zipladi=0;}														//ge�ilmesi sa�lar.
} 

void mantar_ekle (short sayi){
	
	if(mantar_eklendi){													//Bu fonksiyon sadece bir kez �al��acak.
	short adet;
	short mantar_y;														// mantar y min 100 max 132
	short mantar_x;
	short buf_x=0;

	srand(time(NULL));													//de�i�ik rastgele say� �retmek i�in

	for(adet=0;adet<sayi;adet++){										

		mantar_y=(100 + rand() % 32);									// Y kordinat� 100 ila 132 aras�nda say� �retiyoruz
		mantar_x= (rand() % 10000 + haggar.x + 400);					// X kordinat� i�in say� �retiyoruz
		//buf_x=mantar_x;

		for(int i=0;i<sayi;i++)											// Mantarlara kordinatlar�n� at�yoruz.
			if( (mantar_x <= (mantar[i].x + 26)) && (mantar_x >= (mantar[i].x - 10)) ){
		     mantar_x = (mantar_x + 50);								//Mantarlar �st �ste binmesin diye yeni de�erler �retiyoruz.
			 mantar_y=(100 + rand() % 32);}

		mantar[adet].y=mantar_y;
		mantar[adet].x=mantar_x;
	}

	mantar_eklendi=0;													
	}
	

	for(short adet=0;adet<sayi;adet++){									//Animasyonlu mantar bast�rma fonksiyonu
	
	anim_mantar_yuru(adet);

	masked_blit(mantar_resim,buffer,mantar[adet].frame_x,0,
		mantar[adet].x--,mantar[adet].y ,16 ,16);

	if(haggar.dusme)													//Mantarlar�n ezilme kontrol�
	if(buf_y+35 > mantar[adet].y+10 && buf_y+35 <=mantar[adet].y+22)
		if((mantar[adet].x >= haggar.x && mantar[adet].x+16 <= haggar.x+28) || 
			(mantar[adet].x >= haggar.x && mantar[adet].x <= haggar.x+28) ||
				(mantar[adet].x+16 >= haggar.x && mantar[adet].x+16 <= haggar.x+28))
				if(haggar.y+35 >= mantar[adet].y && haggar.y+35 <= mantar[adet].y+1 && !mantar[adet].oldu) {mantar[adet].oldu=1; haggar.puan += 5;
	play_sample(ezildi, 50, 128, 1000, FALSE);}
		
	}
	
}
