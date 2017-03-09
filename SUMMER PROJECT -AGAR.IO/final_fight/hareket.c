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
	else if(haggar.ziplama)anim_zipla();					//Yön tuþlarý basýlmadan zýplandýysa zýplama animasyonunu göster.

	if(ust_tus && !haggar.ziplama && !haggar.dusme && haggar.y>(max_y-35)){
	anim_yuru();
	haggar.y--;	
	}
	else if(alt_tus && !haggar.ziplama && !haggar.dusme && haggar.y<(min_y-35)){
	anim_yuru();
	haggar.y++;	
	}
	
	if(!key[KEY_LEFT] && !key[KEY_RIGHT] && !key[KEY_SPACE] && !key[KEY_UP] && !key[KEY_DOWN]	//Tuþlara basýlmadýysa frameyi sýfýrla
	&& !haggar.dusme && !haggar.ziplama){	
	haggar.frame=0;}
	else haggar.frame++;									//Haggar frame sayacýný artýr

	ziplama();
	mantar_frame++;											//Mantarlarýn frame sayacýný artýr
	mantar_ekle(mantar_sayisi);								//100 adet mantar ekle

	masked_blit((BITMAP *)resimler[1].dat,buffer,haggar.frame_x,haggar.frame_y,
		haggar.x,haggar.y,28,35);
	
}

void ziplama(void){

if(space_tus && !haggar.dusme && !haggar.ziplama){			//Zýplamayý kontrol et.
haggar.frame=0;												//Frame sýfýrlýyoruz.
max_yukseklik=haggar.y-max_ziplama;							//Oyuncunun y sini buffera aktar ve ziplama
haggar.ziplama=AKTIF;										//Kontrolünü aktifleþtir.Sonrada zýplanabi
buf_y=haggar.y;												//bilecek max yüksekliði max_yukseklige ata.
}

if(haggar.ziplama && haggar.y>=max_yukseklik && !haggar.dusme){ 		//Yumuþak bir zýplayýþ için önce 2 pixel
	if(haggar.y<=(max_yukseklik+10))									// yüksel.Max yüksekliðe 10 kala 1 er pixel
	haggar.y-=1;														//yüksel.Böylece yükselme ve yavaþlama sað
	else 																//lanýr.Daha hoþ olur.
	haggar.y-=2; }

if(haggar.y==(max_yukseklik))											//Eðer max yüksekliðe eriþtiyse ziplamayý
{haggar.dusme=AKTIF;haggar.ziplama=PASIF;--haggar.y;haggar.zipladi=1;}	//durdur.Ve düþmeyi aktifleþtir.

if(haggar.dusme && haggar.y<buf_y){										//dusme aktif ise ve murat.y buf_y den 
haggar.y+=2;}															//küçük ise 2 þer pixel aþaðý in.
else if(haggar.y>=buf_y){												//Þayet murat.y buf_y den büyük ise yada
haggar.dusme=PASIF;}													//eþit ise düþmeyi durdur.

if(haggar.zipladi && !haggar.dusme){haggar.frame_y=0;					//Sadece zýplama olayý bittiðinde bir kez
if(haggar.yon) haggar.frame_x=31; else haggar.frame_x=0;				//Çalýþýr.Yere deðdiðinde normal duruþa
haggar.zipladi=0;}														//geçilmesi saðlar.
} 

void mantar_ekle (short sayi){
	
	if(mantar_eklendi){													//Bu fonksiyon sadece bir kez çalýþacak.
	short adet;
	short mantar_y;														// mantar y min 100 max 132
	short mantar_x;
	short buf_x=0;

	srand(time(NULL));													//deðiþik rastgele sayý üretmek için

	for(adet=0;adet<sayi;adet++){										

		mantar_y=(100 + rand() % 32);									// Y kordinatý 100 ila 132 arasýnda sayý üretiyoruz
		mantar_x= (rand() % 10000 + haggar.x + 400);					// X kordinatý için sayý üretiyoruz
		//buf_x=mantar_x;

		for(int i=0;i<sayi;i++)											// Mantarlara kordinatlarýný atýyoruz.
			if( (mantar_x <= (mantar[i].x + 26)) && (mantar_x >= (mantar[i].x - 10)) ){
		     mantar_x = (mantar_x + 50);								//Mantarlar üst üste binmesin diye yeni deðerler üretiyoruz.
			 mantar_y=(100 + rand() % 32);}

		mantar[adet].y=mantar_y;
		mantar[adet].x=mantar_x;
	}

	mantar_eklendi=0;													
	}
	

	for(short adet=0;adet<sayi;adet++){									//Animasyonlu mantar bastýrma fonksiyonu
	
	anim_mantar_yuru(adet);

	masked_blit(mantar_resim,buffer,mantar[adet].frame_x,0,
		mantar[adet].x--,mantar[adet].y ,16 ,16);

	if(haggar.dusme)													//Mantarlarýn ezilme kontrolü
	if(buf_y+35 > mantar[adet].y+10 && buf_y+35 <=mantar[adet].y+22)
		if((mantar[adet].x >= haggar.x && mantar[adet].x+16 <= haggar.x+28) || 
			(mantar[adet].x >= haggar.x && mantar[adet].x <= haggar.x+28) ||
				(mantar[adet].x+16 >= haggar.x && mantar[adet].x+16 <= haggar.x+28))
				if(haggar.y+35 >= mantar[adet].y && haggar.y+35 <= mantar[adet].y+1 && !mantar[adet].oldu) {mantar[adet].oldu=1; haggar.puan += 5;
	play_sample(ezildi, 50, 128, 1000, FALSE);}
		
	}
	
}
