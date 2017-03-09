#include "main.h"

volatile long speed_counter=0;			

void increment_speed_counter(){
speed_counter++;
}END_OF_FUNCTION(increment_speed_counter);

int main(int argc,char *argv[]){

allegro_init();
install_keyboard();
install_timer();
install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);

LOCK_VARIABLE(speed_counter);
LOCK_FUNCTION(increment_speed_counter);
install_int_ex(increment_speed_counter,BPS_TO_TIMER(115));

int depth;
depth=desktop_color_depth();
set_color_depth(depth);

//GFX_AUTODETECT_WINDOWED		//GDI kullanan pencere.
//GFX_DIRECTX_WIN				//DIRECTX kullanan pencere.

set_gfx_mode(GFX_AUTODETECT_WINDOWED, 400, 165, 0, 0);	
set_window_title("Allegro-Final Fight - Mrti14");

buffer=create_bitmap(400,165);

mantar_resim=load_bitmap("mantar.bmp",NULL);		// baz� resimleri ��endi�im i�in datafile i�ine koymad�m.
son=load_bitmap("son.bmp",NULL);
resimler=load_datafile("final_fight.dat");
ezildi = load_sample("ezildi.wav");


haggar.y=105;										//Hagar�n Y kordinat�na ilk de�eri at�yoruz.

while(!key[KEY_ESC]){
	
	while(speed_counter>0){							//Fps i�in say�c�
		 tuslari_kontrol_et();						//Tu�lar� kontrol edip tamponlara at�yor.Direk tu�lar� kullanm�yoruz
		 bolum_bir();								//Birinci b�l�m
		 draw_sprite(screen,buffer,0,0);			//Buffer� bast�r�yoruz
		 clear_bitmap(buffer);						//Ekranda iz kalmamas� i�in  temizliyoruz
	speed_counter --;								//Say�c�y� azalt�yoruz
	}
	//rest(1);										//��lemci kullan�m�n� k�s�tl�yor.Ayr�nt�l� bil i�in allegro manuale bak�n
}	

clear_bitmap(screen);								//Ekran� temizle
while(!key[KEY_Q]){
draw_sprite(screen,son,0,0);						//Mrti14 ekran�n� bast�r
textprintf_ex(screen, font, 0,157, makecol(255,255,255), -1, "Cikmak icin Q ya basin...");
}

destroy_bitmap(buffer);								//B�t�n grafikerli siliyoruz.
destroy_bitmap(mantar_resim);
destroy_bitmap(son);
destroy_sample(ezildi);
unload_datafile(resimler);
return 0;

}
