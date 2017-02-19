#include <allegro.h>
#include <ctime>
#include <vector>
#define BLAZE_ORANGE makecol(255,102,0)

struct sprite
{
	int x;
	int y;
	int type;//0 = stormtrooper, 1 = scout trooper,2 = boba fett 3 =  darth vader, 4 = r2 (bomb)
	int velY;
	int velX;
	bool dir;//true = right, false = left
	int split;// 0 = whole, 1 = top, 2 = bottom
	int cooldown;
	sprite(int xx,int yy, int spriteType,int velocityY, int velocityX, bool direction)
	{
		x = xx;
		y = yy;
		type = spriteType;
		velY = velocityY;
		velX = velocityX;
		dir = direction;
		cooldown = 0;
		split = 0;
	}
	sprite(int xx,int yy, int spriteType,int velocityY, int velocityX, bool direction, int cool, int cut)
	{
		x = xx;
		y = yy;
		type = spriteType;
		velY = velocityY;
		velX = velocityX;
		dir = direction;
		cooldown = cool;
		split = cut;
	}
	sprite()
	{
		x = 0;
		y = 960;
		type = 0;
		velY = 0;
		velX = 0;
		dir = 0;
		cooldown = 0;
		split = 0;
	}
};

std::vector<sprite> sprites;
const int S_H = 600;
const int S_W = 800;
const int NUM_CHARACTERS = 500; //Mess around with this value, it can get pretty ridiculous
const int MAX_LIVES = 3;
const bool ENABLE_BOMB = false;
int lives = 3;
int score = 0;

void init();
void deinit();

int main() {
	init();
	BITMAP* blank = create_bitmap(S_W,S_H);
	BITMAP* title = create_bitmap(S_W,S_H);
	BITMAP* lsab = load_bitmap("lightsaber.bmp",NULL);
	BITMAP* boba = load_bitmap("boba.bmp",NULL);
	BITMAP* r2 = load_bitmap("r2.bmp",NULL);
	BITMAP* scout = load_bitmap("ScoutTrooper.bmp",NULL);
	BITMAP* vader = load_bitmap("DarthVader.bmp",NULL);
	BITMAP* storm = load_bitmap("stormtrooper.bmp",NULL);
	BITMAP* back = load_bitmap("space_background.bmp",NULL);
	bool startGame = true;
	for(int i = 0; i < NUM_CHARACTERS; i++)
	{
		int tx = rand() % S_W;
		int ty = rand() % 5;//type, not y position
		int tvx = ((rand() % 10) + 10);
		int tvy = ((rand() % 20)+30);
		int cd = ((rand()%30)+1);
		bool td;
		if(tx < S_W/2)
		{
			td = true;
		}
		else
		{
			td = false;
		}
		sprites.insert(sprites.begin()+i,sprite(tx,S_H,ty,tvy,tvx,td,cd,0));
	}

	while (!key[KEY_ESC])
	{
		while(!key[KEY_Y] && startGame && !key[KEY_ESC])
		{
		  clear_bitmap(title);
		  blit(back,title,0,0,0,0,blank->w, blank->h);
		  textout_centre_ex(title,font,"Hello, and welcome to Star Wars Ninja, by Eric Hoffmann!",S_W/2,200,BLAZE_ORANGE,-1);
		  textout_centre_ex(title,font,"The rules are simple. Use your mouse to wield a lightsaber and cut down your enemies! ",S_W/2,220,BLAZE_ORANGE,-1);
		  textout_centre_ex(title,font,"These are your enemies:",S_W/2,240,BLAZE_ORANGE,-1);
		  draw_sprite(title,boba,S_W/2-boba->w/2-20,340-boba->h/2);
		  draw_sprite(title,vader,S_W/2+vader->w/2+20,340-vader->h/2);
		  draw_sprite(title,scout,S_W/2-scout->w/2-120,340-scout->h/2);
		  draw_sprite(title,storm,S_W/2+vader->w/2+120,340-storm->h/2);
		  textout_centre_ex(title,font,"Be careful not to hit r2-d2 though. You'll lose a life! (represented by the lightsabers in the upper left corner)",S_W/2,420,BLAZE_ORANGE,-1);
		  textout_centre_ex(title,font,"Don't hit this:",S_W/2,440,BLAZE_ORANGE,-1);
		  draw_sprite(title,r2,S_W/2-r2->w/2,S_H/2);
		  textout_centre_ex(title,font,"Press y to continue to the game!",S_W/2,S_H/2+100,BLAZE_ORANGE,-1);
		  blit(title,screen,0,0,0,0,title->w, title->h);
		  rest(5);
		}
		startGame = false;

		clear_bitmap(blank);
		blit(back,blank,0,0,0,0,blank->w, blank->h);
		for(int i=0; i < sprites.size();i++)
		{
			sprite* temp = &sprites.at(i);
			BITMAP* t;
			switch(temp->type)
			{
				case 0:
					t=storm;
					break;
				case 1:
					t=scout;
					break;
				case 2:
					t = boba;
					break;
				case 3:
					t=vader;
					break;
				default:
					t=r2;
			}
			if(temp->split == 1)
			{
				masked_blit(t,blank,0,0,temp->x,temp->y,t->w,t->h/2);
			}
			else if (temp->split == 2)
			{
				masked_blit(t,blank,0,t->h/2,temp->x,temp->y,t->w,t->h/2);
			}
			else
			{
				draw_sprite(blank,t,temp->x,temp->y);
			}

			if(temp->cooldown <= 0)
			{
				temp->y-=temp->velY;
				temp->velY--;
			}
			temp->cooldown--;
			if(temp->dir == true)
			{
				temp->x+=temp->velX;
			}
			else
			{
				temp->x-=temp->velX;

			}
			if(temp->split == 0)
			{
				if(mouse_x > temp->x && mouse_x < temp->x+76 && mouse_y > temp->y && mouse_y < temp->y+t->h)
				{
					if(temp->type < 4)
					{
						score++;
					}
					else
					{
						if(ENABLE_BOMB)
						{
							lives--;
						}
					}
					int tx = temp->x;
					int ty = temp->y;
					int ttype = temp->type;
					int tvy = temp->velY;
					int tvx = temp->velX;
					bool td = temp->dir;

					sprites.erase(sprites.begin()+i);
					sprites.insert(sprites.begin()+i,sprite(tx,ty,ttype,tvy+5,tvx,td,0,1));

					sprites.push_back(sprite(tx,ty+t->h/2,ttype,tvy,tvx,td,0,2));
				}
			}

			if(temp->y > S_H)
			{
				if(temp->split <2)
				{
					sprites.erase(sprites.begin()+i);
					int tx = rand() % S_W;
					int ty = rand() % 5;//type, not y position
					int tvx = ((rand() % 10) + 10);
					int tvy = ((rand() % 20)+30);
					int cd = ((rand()%30)+1);
					bool td;
					if(tx < S_W/2)
					{
						td = true;
					}
					else
					{
						td = false;
					}
					sprites.insert(sprites.begin()+i,sprite(tx,S_H,ty,tvy,tvx,td,cd,0));
				}
				else
				{
					sprites.erase(sprites.begin()+i);
					i--;
				}

			}
		}
		if(lives <= 0)
		{
			while(!key[KEY_ESC])
			{
			  clear_bitmap(title);
			  blit(back,title,0,0,0,0,blank->w, blank->h);
			  textout_centre_ex(title,font,"Game Over!",S_W/2,200,BLAZE_ORANGE,-1);
			  textprintf_centre_ex(title,font,S_W/2,220,BLAZE_ORANGE,-1,"You killed %d enemies!",score);
			  textout_centre_ex(title,font,"Press y to play again! Otherwise, press escape to exit.",S_W/2,240,BLAZE_ORANGE,-1);
			  if(key[KEY_Y])
			  {

				  lives = MAX_LIVES;
				  score = 0;
				  for(int i=0; i < sprites.size();i++)
				  {
					  sprites.erase(sprites.begin()+i);
					  sprites.insert(sprites.begin()+i,sprite());
				  }
				  break;
			  }
			  blit(title,screen,0,0,0,0,title->w, title->h);
			  rest(5);
			}
		}
		textprintf_ex(blank,font,10,10,BLAZE_ORANGE,-1,"Lives:");
		for(int i = 0; i < lives; i++)
		{
			draw_sprite(blank,lsab,10+i*50,20);
		}
		textprintf_ex(blank,font,mouse_x+10,mouse_y,BLAZE_ORANGE,-1,"Score: %d",score);
		textprintf_ex(blank,font,mouse_x-80,mouse_y,BLAZE_ORANGE,-1,"Lives: %d",lives);
		draw_sprite(blank,lsab,mouse_x-lsab->w/2,mouse_y-lsab->h/2);
		blit(blank,screen,0,0,0,0,blank->w, blank->h);
		rest(50);
	}

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED,S_W, S_H, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}
