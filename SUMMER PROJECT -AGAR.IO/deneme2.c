/*Allegro4 kutuphanesi kullanildi*/
/*klavyenin yon tuslariyla kontrol edilebilen bir top var.*/
/*mouse ile hareket kodlari yorum satiri icinde*/
/*yemlerin uzerine geldiginde onlari yiyerek capini buyutuyor.*/
/*bosluk tusuna basildiginda ikiye bolunuyor*/


#include <allegro.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#define W 1200
#define H 600
#define ARRAY_NUM 200
#define R 40 /*oyuncu yaricapi*/
#define DEBUG
#define BOTS_NUM 10	
#define NUM 15
#define GREEN_THINGS_NUM 5

typedef struct 
{
	double x;
	double y;
	double r;
	int col1,col2,col3;
	
} Gamer ;



typedef struct 
{
	Gamer G_1;
	Gamer G_2;
	Gamer G_3;
	Gamer G_4;
	Gamer G_5;
	Gamer G_6;
	Gamer G_7;
	Gamer G_8;
	Gamer G_9;
	Gamer G_10;
	
}Gamer_team;

typedef struct 
{
	int f_x;
	int f_y;
	int f_r;
	
} Food;

void start();
void end();
void move_circle(Gamer *gamer_1);
void foods(BITMAP *buffer,Food food_array[ARRAY_NUM]);
void eat_and_create(Food *food_1,Gamer *gamer_,int *food_count);
void play_green_things(BITMAP *buffer,Gamer *green_things,Gamer *gamer_1,int sign);
void play_circle(BITMAP *buffer,Gamer *gamer_1,Gamer *gamer_2,Gamer *gamer_3,
                int *sign,Food food_array[],int *food_count,int *great_circle,int *first,
                Gamer_team *G_team,Gamer bots[BOTS_NUM]);
void devide(BITMAP *buffer,Gamer gamer_1,Gamer *gamer_2,Gamer *gamer_3,
			int *sign,Food food_array[],int *food_count,int *first,Gamer_team *G_team);


void bot(BITMAP *buffer,Gamer *gamer_1,Gamer bots[BOTS_NUM],Food food_array[ARRAY_NUM],int *food_count_bot);

void eat_small_gamer(BITMAP *buffer,Gamer bots[BOTS_NUM],Gamer *big_or_small);

void information();

/*void play(BITMAP *buffer,Food *food_1,Gamer *gamer_,int 
*food_count,Gamer *gamer_2,Gamer *gamer_3,int *sign,Food food_array[]);*/
void push_space(int *sign,int *great_circle,int *food_count);



int main() {
	
	start();

	/*BITMAP *background=load_bitmap("b1.bmp",NULL);*/
	
	BITMAP *buffer=create_bitmap(W,H);/*!!!! onemli*/
	
	int sign=0;
	Gamer gamer_1,gamer_2,gamer_3;
	Gamer_team G_team;

	Gamer green_things1,green_things2;
	Gamer green_things_arr[GREEN_THINGS_NUM];
	Food food_1;
	int counter = 0,food_count=0,great_circle;
	int food_count_bot=0;
	
	int timer=0;
	int i,j;


	Gamer bots[BOTS_NUM];

	int first=0;	/*devide fonksiyonunda gamer_3'e gamer_1'in koordinatlarini sadece */
					/*bir kere vermek icin yolladim*/
					/*if icine sadece bir kere girsin diye*/
	Food food_array[ARRAY_NUM];
	
	srand(time(NULL));
		/*ilk konumlar*/

	gamer_1.x=rand()%(W);   
	
	gamer_1.y=rand()%(H);   
	
	gamer_1.r=R; 


	srand(time(NULL));
	for(i=0;i<GREEN_THINGS_NUM;++i){
		green_things_arr[i].x=rand()%(W/2)+10;
		green_things_arr[i].y=rand()%(W-50);
		green_things_arr[i].r=50;
	} 

	/*green_things1.x=rand()%(W/2)+10;		green_things1.y=rand()%(W-50);		green_things1.r=50;
	green_things2.x=rand()%(H/5)+10;		green_things2.y=rand()%(H-50);		green_things2.r=50;
	*/

	srand(time(NULL));
	/*food_array'i doldurur*/
	for(i=0;i<ARRAY_NUM;++i){

		food_array[i].f_x = rand()%(W-10);
		food_array[i].f_y = rand()%(H-10);
		food_array[i].f_r = 5;
	}

	srand(time(NULL));
	for(i=0;i<BOTS_NUM;++i){
		bots[i].x = rand()%(W-50);
		bots[i].y = rand()%(H-50);
		bots[i].r = rand()%10+20;
		bots[i].col1 = rand()%250;
		bots[i].col2 = rand()%250;
		bots[i].col2 = rand()%250;
	}



	/*bu dongu icindekiler ekranda gorunur*/
	while (!key[KEY_ESC]  ) {

		show_mouse(buffer);

		if(mouse_b && 1 ){/*fareye tıklanmadığı sürece*/
	       printf("BASTI %d %d \n",mouse_x,mouse_y);
	      
  		}

		++timer;
		/*printf("%d\n", timer);*/
		/*blit(background,buffer,0,0,0,0,W,H);*/
		
        push_space(&sign,&great_circle,&food_count);
       
	    foods(buffer,food_array);
		bot(buffer,&gamer_1,bots,food_array,&food_count_bot);
		play_circle(buffer,&gamer_1,&gamer_2,&gamer_3,&sign,food_array,
		            &food_count,&great_circle,&first,&G_team,bots);

		
	    /*devide(buffer,&gamer_1,&gamer_2,&gamer_3,&sign,food_array,&food_count,&first);*/

		for(i=0;i<GREEN_THINGS_NUM;++i){
			play_green_things(buffer,&green_things_arr[i],&gamer_1,sign);
			for(j=0;j<BOTS_NUM;++j){
				play_green_things(buffer,&green_things_arr[i],&bots[j],sign);
			}
		}
		

	/*	

		if( (sign > 0 ) /*&& (gamer_1->r >= 20) ){

	/*		play_green_things(buffer,&green_things1,&gamer_2,sign);
			play_green_things(buffer,&green_things1,&gamer_3,sign);

		}*/
		
		if(sign == 0 || sign == 7000){

			great_circle = food_count ;
		}

		/*OYUN BITTI KISMI YANLIS DUZELTT!*/

		if(gamer_1.r == 0){
			
			textout_justify_ex(buffer, font, "OYUN BITTI", 100,100, 
		                    150, 200, makecol(255, 225, 0), makecol(0,0,0));
		}

		textout_justify_ex(buffer, font, "YARICAP UZUNLUGU", 500, 70, 
		                    10, 20, makecol(255, 225, 100), makecol(0,0,0));
		textprintf_ex(buffer,font,500,25,makecol(225,225,255),makecol(0,0,0),
		              "%.1f",gamer_1.r);
		textout_justify_ex(buffer, font, "YENILEN YEM SAYISI", 500, 70, 
		                   40, 20, makecol(255, 255, 255), makecol(0,0,0));
		textprintf_ex(buffer,font,500,55,makecol(225,225,225),makecol(0,0,0),
		              "%-10d",food_count);	

	    rest(50);
		blit(buffer,screen,0,0,0,0,W,H);/*bufferdan ekrana*/
		clear_bitmap(buffer);
	}
	end();
return 0;
}
END_OF_MAIN()


/*iki tane daire olusturur*/
/*bolunme esnasinda cagirilmali*/
void devide(BITMAP *buffer,Gamer gamer_1,Gamer *gamer_2,Gamer *gamer_3,
			int *sign,Food food_array[],int *food_count,int *first,Gamer_team *G_team){
	
	int i;
    /*ilk basmada*/
	if((*first) == 0){
		++(*first);

	/*	gamer_2->x=gamer_1.x ;
		gamer_2->y=gamer_1.y ;
		gamer_2->r=gamer_1.r / 2 ;

		gamer_3->x=gamer_1.x  ;
		gamer_3->y=gamer_1.y + 50 ;
		gamer_3->r=gamer_1.r / 2 ;	*/
	}

 	circlefill(buffer,gamer_2->x,gamer_2->y,gamer_2->r,makecol(200,0,250));
    circlefill(buffer,gamer_3->x,gamer_3->y,gamer_3->r,makecol(0,0,250));      
   
    move_circle(gamer_2);
	for(i=0;i<ARRAY_NUM;++i){
		eat_and_create(&food_array[i],gamer_2,food_count);
	}
	
	move_circle(gamer_3);
	for(i=0;i<ARRAY_NUM;++i){
		eat_and_create(&food_array[i],gamer_3,food_count);
	}

	/*ayrilan parca her dongude yarim birim geri geliyor.*/
	if(gamer_3->x > gamer_2->x){
		
		gamer_3->x = gamer_2->x - (1.0/2) ;
	}
	
}

/*yardimci fonksiyon. bosluk tusuna basilmdiginda kontrol amacli*/
/*bu fonksiyon olmadiginda bosluk tusuna basilinca saniyelere */
/*gore algiladigi icin yanlis calisiyor*/
void push_space(int *sign,int *great_circle,int *food_count)
{
    if (key[KEY_SPACE]){
	  	(*sign)++;
	  	
	 	if((*sign) >= 5 && (*sign)!=7000 ){
	  		(*sign) = 2000;
/*bir kere basilmis ve sonrasinda birlesme olmamis*/
/*tekrar basilmis*/
	  		
	 	}

	 	if((*sign) >= 5 && (*sign)==7000 ){
	 		(*sign) = 4 ;

	 	/*birlesme olmus ve tekrar basilmis. yani ikiye bolunme olmali*/
	 	}/*??????????????*/

	  	/*printf("%d\n",(*sign) );*/	

	/*  	if((*sign) == 1000 && key[KEY_SPACE]){
	  		/*ucuncu basma*/
	  	/*	(*sign) = 1000;
	  		
	  			
	  	}*/
    }
	  
}


/*bosluk tusuna basildiginda ikiye ayriliyor.sonra birlesiyor. */
/*oyunun diger hareketleri de bu fonsiyon icinde kullanildi*/	 
void play_circle(BITMAP *buffer,Gamer *gamer_1,Gamer *gamer_2,Gamer *gamer_3,
                int *sign,Food food_array[],int *food_count,int *great_circle,int *first,
                Gamer_team *G_team,Gamer bots[BOTS_NUM]){

    int i;


	    /*ikinci basmada*/
	if((*sign) == 2000 && (*first == 1) ){
		G_team->G_1.x = gamer_2->x + 50;
		G_team->G_1.y = gamer_2->y ;
		G_team->G_1.r = gamer_1->r / 4;
		
		gamer_2->r = gamer_1->r/4;

		G_team->G_2.x = gamer_2->x + 50;
		G_team->G_2.y = gamer_2->y +50 ;
		G_team->G_2.r = gamer_1->r / 4;
		
		gamer_3->r = gamer_1->r/4;
		++(*first);
	}




    /*bosluga basilmadigi ve tekrar birlesme zamaninda*/
    if(*sign == 0 || *sign == 7000 ){
    	circlefill(buffer,gamer_1->x,gamer_1->y,gamer_1->r,makecol(200,0,250));
		move_circle(gamer_1);
		for(i=0;i<ARRAY_NUM;++i){
			eat_and_create(&food_array[i],gamer_1,food_count);
		}
		eat_small_gamer(buffer,bots,gamer_1);

		gamer_2->x = gamer_1->x + 50;
		gamer_2->y = gamer_1->y + 50;

		gamer_3->x = gamer_1->x ;
		gamer_3->y = gamer_1->y ;

		gamer_2->r = gamer_1->r / 2;
		gamer_3->r = gamer_1->r / 2;

    }

    /*bosluk tusuna basildigi zamanlarda*/
    else if( (*sign > 0 ) /*&& (gamer_1->r >= 20)*/ ){
    	

    	devide(buffer,*gamer_1,gamer_2,gamer_3,sign,food_array,food_count,first,G_team);/*ilk*/
    	gamer_1->r = gamer_2->r + gamer_3->r;
		gamer_1->x = (gamer_2->x + gamer_3->x)/2;
		gamer_1->y = (gamer_2->y + gamer_3->y)/2;

		eat_small_gamer(buffer,bots,gamer_2);
		eat_small_gamer(buffer,bots,gamer_3);
	

		

    	if(*sign == 2000 && *first == 2){
    		
    		devide(buffer,*gamer_1,&G_team->G_1,&G_team->G_2,sign,food_array,
    				food_count,first,G_team);
    		

    		gamer_1->r = gamer_2->r + gamer_3->r + G_team->G_1.r + G_team->G_2.r;
			gamer_1->x = (gamer_2->x + gamer_3->x)/2;
			gamer_1->y = (gamer_2->y + gamer_3->y)/2;
    	}
 
   	}

/*bosluga basildiginda ama yaricapi bolunmeye müsait olmadiginda*/
/*(*sign != 1000) kosulu yaricap 20 altina dustugunde ve oyuncu iki parca oldugunda */
/*bir parca yesil sey tarafindan yenirse diger parca yok olmasin diye*/
   	
   	else if( (*sign > 0 ) && (gamer_1->r < 20) && (*sign != 1000) ){
   	    circlefill(buffer,gamer_1->x,gamer_1->y,gamer_1->r,makecol(200,0,250));
		move_circle(gamer_1);
		for(i=0;i<ARRAY_NUM;++i){
			eat_and_create(&food_array[i],gamer_1,food_count);
		}
		gamer_2->x = gamer_1->x ;
		gamer_2->y = gamer_1->y ;
                                                                               
		gamer_3->x = gamer_1->x + (gamer_1->r+50);
		gamer_3->y = gamer_1->y + (gamer_1->r);

		gamer_2->r=gamer_1->r/2;      
       	gamer_3->r=gamer_1->r/2;

        *sign = 0;

   	}

	if(*food_count - *great_circle >= 10){
		*sign = 7000;
	} /*birlesme komutu gibi*/
		/*EKSIKLERI VAR!!!!!!!!!! SADECE ILK BOLUNMEDE GECERLI.DUZELT!!!*/


}

/*yer sonra diger yemin koordinatlarini belirler*/
void eat_and_create(Food *food_1,Gamer *gamer_,int *food_count){
 
    if( sqrt( pow(( (double)(gamer_->y) - (food_1->f_y)) , 2) + 
              pow(( (double)(gamer_->x) - (food_1->f_x)) , 2) ) <= 
              (gamer_->r)-(food_1->f_r) ){
		/*kucuk daire buyuk daire icine geldiginde aralarindaki mesafeyi*/
		/*bu sekilde bulup sinirlandirdim*/
        (gamer_->r) = (gamer_->r) + (1.0/2);
        
		++(*food_count);


		srand(time(NULL));
		if((*food_count)%2 == 0)
			(food_1->f_x) = rand()%(W-10);
		else if((*food_count)%3 == 0)
			(food_1->f_x) = rand()%(W-10);
		else if((*food_count)%4 == 0)
			(food_1->f_x) = rand()%(W-10);
		else if((*food_count)%5 == 0)
			(food_1->f_x) = rand()%(W-10);
		else if((*food_count)%7 == 0)
			(food_1->f_x) = rand()%(W-10);
		else 
			(food_1->f_x) = rand()%(W-10);

		srand(time(NULL));
		if((*food_count)%2 == 0)
			(food_1->f_y) = rand()%(H-10);
		else if((*food_count)%3 == 0)
			(food_1->f_y) = rand()%(H-10);
		else if((*food_count)%4 == 0)
			(food_1->f_y) = rand()%(H-10);
		else if((*food_count)%5 == 0)
			(food_1->f_y) =	rand()%(H-10);
		else if((*food_count)%7 == 0)
			(food_1->f_y) = rand()%(H-10);
		else 
			(food_1->f_y) = rand()%(H-10);

		/*eger rand() a cozum bulamazsan ilk sayiya yeni koordinatlari ata*/
		/*sonra bi sonraki dongude karsilastir eger ayniysa kendin farkli bir
		 yontemle atamaya basla*/
		    /*olmuyor*/
			
	}

	
}

void foods(BITMAP *buffer,Food food_array[20]){

	int i;
	for(i=0;i<ARRAY_NUM;++i){
		circlefill(buffer,(food_array[i].f_x),(food_array[i].f_y),
		(food_array[i].f_r),makecol(rand()%225,rand()%225,rand()%225));
		/*yiyecekler her dongude farkli renk aliyor*/
		
	}
}

	/*hareket etmesini saglar*/
void move_circle(Gamer *gamer_1){
	
/*	if((gamer_1->x >= mouse_x) && (gamer_1->x != mouse_x))
		gamer_1->x -= 1.5 ;
	if((gamer_1->y >= mouse_y) && (gamer_1->y != mouse_y))
		gamer_1->y -= 1.5 ;
	if((mouse_x >= gamer_1->x) && (gamer_1->x != mouse_x))
		gamer_1->x += 1.5 ;
	if((mouse_y >= gamer_1->y) && (gamer_1->y != mouse_y))
		gamer_1->y += 1.5;
*/
	
	
	if(key[KEY_UP])
		(gamer_1->y) -= 2;
	else if(key[KEY_DOWN])
		(gamer_1->y) += 2;
	if(key[KEY_LEFT])
		(gamer_1->x) -= 2;
	else if(key[KEY_RIGHT])
		(gamer_1->x) += 2;




}

/*yesil top oyuncu yanina geldiginde onun capini azaltir*/
/*kendine ceker*/
void play_green_things(BITMAP *buffer,Gamer *green_things,Gamer *gamer_,
				int sign){
	 circlefill(buffer,green_things->x,green_things->y,green_things->r,makecol(0,150,0));
	 if( sqrt( pow(( (double)(green_things->y) - (gamer_->y)) , 2) + 
              pow(( (double)(green_things->x) - (gamer_->x)) , 2) ) <= 
              (green_things->r)){
	 	
	 	if(sign == 0 || sign == 7000)
	 		gamer_->r =  gamer_->r - 0.1;
	/*yesil sey oyuncuyu kendine ceker*/
	 	if((green_things->x > gamer_->x )&& (gamer_->x < ((green_things->x + gamer_->x)/2)))
	 		gamer_->x += 10;
	 	if((green_things->y > gamer_->y )&& (gamer_->y < ((green_things->y + gamer_->y)/2)))
	 		gamer_->y += 10;
	 	
	 	if((green_things->x > gamer_->x )&& (gamer_->x > ((green_things->x + gamer_->x)/2)))
	 		gamer_->x -= 10;
	 	if((green_things->y > gamer_->y )&& (gamer_->y > ((green_things->y + gamer_->y)/2)))
	 		gamer_->y -= 10;
	 	if( sqrt( pow(( (double)(green_things->y) - (gamer_->y)) , 2) + 
              pow(( (double)(green_things->x) - (gamer_->x)) , 2) ) <= 
              (green_things->r) - gamer_->r){
	 		gamer_->r = 0;
		}


	}

}

/*bootlarin food countu isimize yaramiyor o nedenle pointer olarak yollanmadi fonksiyona*/
void bot(BITMAP *buffer,Gamer *gamer_1,Gamer bots[BOTS_NUM],Food food_array[ARRAY_NUM],int *food_count_bot){

		int i,j,k;
		int arr[14]={2,3,5,7,11,13,17,19,23,29,31,37,41,47};
		

	for(i=0;i<BOTS_NUM;++i){
		circlefill(buffer,(bots[i].x),(bots[i].y),
		(bots[i].r),makecol(bots[i].col1,bots[i].col2,bots[i].col3));
		
		for(j=0;j<ARRAY_NUM;++j){
			eat_and_create(&food_array[j],&bots[i],food_count_bot);
		}

	eat_small_gamer(buffer,bots,&bots[i]);
		
		bots[i].x -= 0.3;
		for(j=0;j<13;++j) {
		
/*burayi duzenle!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
			/*ilk i 0 a eşit diye*/
			if((i+1)%arr[j] == 0){
				switch(j){
					case 1 : bots[i].x += 0.5 ;
							 bots[i].y -= 0.5; break ;
					
					case 2 : bots[i].x -= 0.5 ;
							 bots[i].y += 0.5; break ;
					
					case 3 : bots[i].x += 0.5 ; break ;

					case 4 : bots[i].x -= 0.5 ; break ;
					
					case 5 :  bots[i].y += 0.5; break;
					
					case 6 : bots[i].y -= 0.5; break;
					
					case 7 : if(*food_count_bot > 2)
								bots[i].x -= 0.5;
							 bots[i].y ++; break;
					
					case 8 : bots[i].x -= 0.5;
							 if(*food_count_bot > 5)
							 	bots[i].y += 0.5; break;
					
					case 9 : bots[i].x += 0.5;
							 if(*food_count_bot > 7)
							 	bots[i].y -= 0.5; break;
					
					case 10 :if(*food_count_bot > 8) 
								bots[i].x += 0.5;
							 bots[i].y -= 0.5; break;
					
					case 11 :if(*food_count_bot > 10) 
							 	bots[i].x -= 0.7;
							 bots[i].y += 0.5; break;
					
					case 12 : bots[i].x -= 0.5;
							 if(*food_count_bot > 10)
							 	bots[i].y -= 0.9; break;
					
					case 13 : bots[i].x += 0.5;
							 bots[i].y += 0.5; break;	

				}

			}
		}
			for(k=0;k<BOTS_NUM;++k){
				
				if(i != k){
				if( sqrt( pow(( (double)(bots[i].y) - (bots[k].y)) , 2) + 
           	 		pow(( (double)(bots[i].x) - (bots[k].x)) , 2) ) <=
           	 		(bots[i].r)+(bots[k].r) ){
					
					if(bots[i].x >= bots[k].x && bots[i].r >= bots[k].r){
						bots[k].x --;
					}
					else if(bots[k].x >= bots[i].x && bots[k].r >= bots[i].r){
						bots[i].x --;
					}

					if(bots[i].y >= bots[k].y && bots[i].r >= bots[k].r){
						bots[k].y --;
					}
					else if(bots[k].y >= bots[i].y && bots[k].r >= bots[i].r){
						bots[i].y --;
					}

				}
				}

				if( sqrt( pow(( (double)(gamer_1->y) - (bots[k].y)) , 2) + 
           	 		pow(( (double)(gamer_1->x) - (bots[k].x)) , 2) ) <=
           	 		(gamer_1->r)+(bots[k].r) ){

					if(gamer_1->x >= bots[k].x && gamer_1->r >= bots[k].r){
						bots[k].x -= 0.1;
					}
					if(bots[k].x >= gamer_1->x && bots[k].r >= gamer_1->r){
						gamer_1->x -= 0.1;
					}
					if(bots[k].x >= gamer_1->x && gamer_1->r >= bots[k].r){
						bots[k].x += 0.1;
					}


					if(gamer_1->y >= bots[k].y && gamer_1->r >= bots[k].r){
						bots[k].y -= 0.1;
					}
					if(bots[k].y >= gamer_1->y && bots[k].r >= gamer_1->r){
						gamer_1->y -= 0.1;
					}
					if(bots[k].y >= gamer_1->y && gamer_1->r >= bots[k].r){
						bots[k].y += 0.1;
					}

				}
			}


		/*!!!!!!!!!!!!!!*/
		

	}



}


void eat_small_gamer(BITMAP *buffer,Gamer bots[BOTS_NUM],Gamer *big_or_small){

	int i,k;
	for(k=0;k<BOTS_NUM;++k){



		if(big_or_small->r > bots[k].r){
			if( sqrt( pow(( (double)(big_or_small->y) - (bots[k].y)) , 2) + 
           	 pow(( (double)(big_or_small->x) - (bots[k].x)) , 2) ) <= 
           	 (big_or_small->r)-(bots[k].r) ){

           	 	big_or_small->r = big_or_small->r + bots[k].r;
           	 srand(time(NULL));
           	 	bots[k].x = rand()%(W-50);
           	 	bots[k].y = rand()%(H+50);
           	 	bots[k].r = rand()%20+10;
           	 	bots[k].col1 = rand()%250;


			}

		}

		else if(bots[k].r > big_or_small->r){
			if( sqrt( pow(( (double)(bots[k].y) - (big_or_small->y)) , 2) + 
           	 pow(( (double)(bots[k].x) - (big_or_small->x)) , 2) ) <= 
           	 (bots[k].r)-(big_or_small->r) ){
           	 	
           	 	bots[k].r = bots[k].r + big_or_small->r;
           	 srand(time(NULL));
           	 	big_or_small->x = rand()%(W-50);
           	 	big_or_small->y = rand()%(H+50);
           	 	big_or_small->r = rand()%20+10;
           	 	big_or_small->col1 = rand()%250;
			}
		}
	

	}
}

void start() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) 
		depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED,W,H,0,0);
	  
	/*if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}*/
	install_timer();
	install_keyboard();
	install_mouse();
 
}
void end() {
	clear_keybuf();
 
}
