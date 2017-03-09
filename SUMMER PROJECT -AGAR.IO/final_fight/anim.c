#include "anim.h"

void anim_yuru (void){
	if(haggar.yon) haggar.frame_y=72;
	else haggar.frame_y=36;	

    if(haggar.frame<7)
		haggar.frame_x=0;					
	else if(haggar.frame>=7 && haggar.frame<14)
		haggar.frame_x=30;					
	else if(haggar.frame>=14 && haggar.frame<21)
		haggar.frame_x=60;						
	
	else if(haggar.frame>=21)	
		haggar.frame=0;		
}

void anim_zipla (void){
	if(haggar.yon) haggar.frame_y=143;	
	else haggar.frame_y=107;

	if(haggar.frame<23)
		haggar.frame_x=0;					
	else if(haggar.frame>=23 && haggar.frame<25)
		haggar.frame_x=32;					
	else if(haggar.frame>=28 && haggar.frame<49)
		haggar.frame_x=63;						
	
	else if(haggar.frame>=49){	
	haggar.frame_x=63;}		
}

void anim_mantar_yuru(short sayi){

	if(mantar_frame<=14)
		mantar[sayi].frame_x=0;
	else if(mantar_frame>14 && mantar_frame<=28)
		mantar[sayi].frame_x=22;
	else if(mantar_frame>28){
		mantar_frame=0;
		mantar[sayi].frame_x=0;}
	
	if(mantar[sayi].oldu)
		mantar[sayi].frame_x=42;
}
