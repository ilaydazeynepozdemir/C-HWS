#include <stdbool.h>

extern  bool sol_tus;
extern  bool sag_tus;
extern  bool ust_tus;
extern  bool alt_tus;
extern  bool space_tus;

extern BITMAP *mantar_resim;

struct oyuncu{

	short x;
	short y;
	short frame_x;
	short frame_y;
	short frame;
	short puan;
	bool ziplama;
	bool dusme;
	bool yon;
	bool zipladi;
};

struct dusman{

	short x;
	short y;
	short frame_x;
	short frame_y;
	short frame;
	bool oldu;

};

