#include <allegro.h>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#define BLAZE_ORANGE makecol(255,102,0)
#define RUSSET makecol(128,70,27)
#define BLACK makecol(0,0,0)

using namespace std;

BITMAP* grabframe(BITMAP *source, int width, int height, int startx, int starty, int columns, int frame)
{
	BITMAP *temp = create_bitmap(width,height);
	int x = startx + (frame % columns) * width;
	int y = starty + (frame / columns) * height;
	blit(source,temp,x,y,0,0,width,height);
	return temp;
}

struct anim
{
    int currFrame;
    int maxFrame;
    int frameDelay;
    int frameCount;
    int x;
    int y;
    vector<BITMAP*> frames;
    anim()
    {
    	currFrame = 0;
    	frameCount = 0;
    	maxFrame = 0;
    	frameDelay = 0;
    	x = 0;
    	y = 0;
    }
    anim(int maxF,int delay, int xx, int yy, int spriteWidth, int spriteHeight, BITMAP *spritesheet)
    {
    	currFrame = 0;
    	frameCount = 0;
    	maxFrame = maxF;
    	frameDelay = delay;
    	x = xx;
    	y = yy;
    	for(int i = 0; i < maxFrame; i++)
    	{
    		frames.push_back(grabframe(spritesheet,spriteWidth,spriteHeight,0,0,maxF,i));
    	}
    }
    anim(int maxF,int delay, int xx, int yy, int spriteWidth, int spriteHeight, BITMAP *spritesheet, int q)
	{
		currFrame = 0;
		frameCount = 0;
		maxFrame = maxF;
		frameDelay = delay;
		x = xx;
		y = yy;
		for(int i = 0; i < maxFrame; i++)
		{
			frames.push_back(grabframe(spritesheet,spriteWidth,spriteHeight,0,0,1,i));
		}
	}
};

struct shape
{
    int x;//upper left
    int y;
    int radius;
    int x2;//lower right
    int y2;
    int type;//0 = rectangle, 1 = circle.

    shape(int xx1,int yy1,int xx2,int yy2)//constructor for rectangle
    {
       x = xx1;
       y = yy1;
       radius = 0;
       x2 = xx2;
       y2 = yy2;
       type = 0;
    }

    shape(int xx1,int yy1,int rad)//constructor for circle
	{
	   x = xx1;
	   y = yy1;
	   radius = rad;
	   x2 = 0;
	   y2 = 0;
	   type = 1;
	}
};

struct phrase
{
	string s;
	vector<bool> visible;

	phrase(string st)
	{
		s = st;
		for(int i = 0; i < s.length(); i++)
		{
			s[i]= tolower(s[i]);
		}
		vector<bool> temp (st.size(),false);
		visible = temp;
	}
};

void init();
void deinit();
const int S_H = 960;
const int S_W = 1280;
bool startGame = true;
BITMAP *title;
BITMAP *blank;
BITMAP *back;
BITMAP *tumble;
BITMAP *firework;
FONT *west28;
FONT *west36;
FONT *west48;
FONT *west72;
anim weed;
anim fire;
vector<phrase> phrases;
vector<string> guessed;
vector<shape> body;
int word;
int wrong = 0;
int correct = 0;
int total = 0;

void reset()
{
	guessed.clear();
	phrases.erase(phrases.begin()+word);
	wrong = 0;
	if(!phrases.size() < 1)
		word = rand() % phrases.size();

}

void createShape(shape s,int col, BITMAP *bit)
{
	if(s.type == 0)
	{
		rectfill(bit,s.x,s.y,s.x2,s.y2,col);
	}
	else
	{
		circlefill(bit,s.x,s.y,s.radius,col);
	}

}

void createShapeCenter(shape s,int col, BITMAP *bit)
{
	if(s.type == 0)
	{
		rectfill(bit,s.x+120,s.y+140,s.x2+120,s.y2+140,col);
	}
	else
	{
		circlefill(bit,s.x+120,s.y+140,s.radius,col);
	}

}

void printUlineCenter(BITMAP* bit,FONT* f,phrase* ph,int w, int h,int color )// allignment is slightly off
{
	int xPos = w-(text_length(f,ph->s.c_str())/2);
	for(int i = 0; i < ph->s.length();i++)
	{
		const char* temp = ph->s.substr(i,1).c_str();
		if(ph->visible[i])
		{
			textout_ex(bit, f, temp, xPos, h, color, -1);
		}
		if(*(temp) != ' ')
		{
			rectfill(bit,xPos, h+f->height+3, xPos+text_length(f,temp), h+f->height+6, color);
		}
		xPos+=text_length(f,temp)+10;
	}
}

void printGuessed(BITMAP* bit,FONT* f,int startX,int endX,int y,int color)
{
	int xPos = startX;
	int yPos = y;
	for(int i = 0; i < guessed.size();i++)
	{
		int charLength = text_length(f,guessed[i].c_str());
		if(xPos+charLength > endX)
		{
			xPos = startX;
			yPos += f->height+10;
		}
		textout_ex(bit, f, guessed[i].c_str(), xPos, yPos, color, -1);
		xPos+= charLength+10;
	}
}

int keyPressed()//only works for a-z,1-9 and only one key at a time. returns -1 if no keys are pressed
{
	for(int i = 1; i < 37; i++)
		if(key[i])
			return scancode_to_ascii(i);
	return -1;
}

void checkChar(int input,phrase* ph)
{
	char in = input;
	if(ph->s.find(in) != string::npos)
	{
		for(int i = 0; i < ph->s.length();i++)
		{
			if(ph->s.substr(i,1).compare(string(1,in))==0)
			{
				ph->visible[i] = true;
			}
		}
	}
	else
	{
		bool found = false;
		for(int i = 0; i < guessed.size();i++)
		{
			if(guessed[i].compare(string(1,in)) == 0)
			{
				found = true;
				break;
			}
		}
		if(!found)
		{
			guessed.push_back(string(1,in));
			wrong++;
		}
	}
}

void printUline(BITMAP* bit,FONT* f,phrase* ph,int w, int h,int color )
{
	int xPos = w;
	for(int i = 0; i < ph->s.length();i++)
	{
		const char* temp = ph->s.substr(i,1).c_str();
		if(ph->visible[i])
		{
			textout_ex(bit, f, temp, xPos, h, color, -1);
		}
		if(*(temp) != ' ')
		{
			rectfill(bit,xPos, h+f->height+3, xPos+text_length(f,temp), h+f->height+6, color);
		}
		else
		{
			ph->visible[i] = true;
		}
		xPos+=text_length(f,temp)+10;
	}
}

bool wordSolved()
{
	for(int i = 0; i < phrases[word].visible.size();i++)
	{
		const char* temp = phrases[word].s.substr(i,1).c_str();
		if(!phrases[word].visible[i] && *(temp) != ' ')
		{
			return false;
		}
	}
	return true;
}

void hangedScreen()
{
	for(int i = 0; i < phrases[word].visible.size();i++)
	{
		phrases[word].visible[i] = true;
	}
	while(!key[KEY_ENTER] && !key[KEY_ESC])
	{
	  clear_bitmap(title);
	  blit(back,title,0,0,0,0,screen->w, screen->h);
	  textout_centre_ex(title,west72,"Oh No!",S_W/2,100,RUSSET,-1);
	  textout_centre_ex(title,west36,"you were hanged!",S_W/2,200,RUSSET,-1);
	  textout_centre_ex(title,west36,"If you want to continue guessing,",S_W/2,250,RUSSET,-1);
	  textout_centre_ex(title,west36,"please press Enter.",S_W/2,300,RUSSET,-1);
	  textout_centre_ex(title,west36,"Otherwise, press the escape key",S_W/2,350,RUSSET,-1);
	  textout_centre_ex(title,west36,"to exit the game.",S_W/2,400,RUSSET,-1);
	  printUlineCenter(title,west72,&phrases[word],S_W/2,S_H-(S_H/4), RUSSET);
	  for(int i = 0; i < wrong; i++)
	  {
		  createShapeCenter(body[i],BLACK,title);
	  }
	  blit(title,screen,0,0,0,0,title->w, title->h);
	}
}

void pauseScreen()
{
	while(!key[KEY_ENTER] && !key[KEY_ESC])
	{
	  clear_bitmap(title);
	  blit(back,title,0,0,0,0,screen->w, screen->h);
	  textout_centre_ex(title,west72,"Congratulations!",S_W/2,100,RUSSET,-1);
	  textout_centre_ex(title,west36,"you solved the puzzle!",S_W/2,200,RUSSET,-1);
	  textout_centre_ex(title,west36,"If you want to continue guessing,",S_W/2,250,RUSSET,-1);
	  textout_centre_ex(title,west36,"please press Enter.",S_W/2,300,RUSSET,-1);
	  textout_centre_ex(title,west36,"Otherwise, press the escape key",S_W/2,350,RUSSET,-1);
	  textout_centre_ex(title,west36,"to exit the game.",S_W/2,400,RUSSET,-1);
	  printUlineCenter(title,west72,&phrases[word],S_W/2,S_H-(S_H/4), RUSSET);
	  blit(title,screen,0,0,0,0,title->w, title->h);
	}
}


void endScreen()
{
	while(!key[KEY_ENTER] && !key[KEY_ESC])
	{
	  clear_bitmap(title);
	  blit(back,title,0,0,0,0,screen->w, screen->h);
	  textout_centre_ex(title,west72,"Game Over!",S_W/2,100,RUSSET,-1);
	  textout_centre_ex(title,west36,"Thanks for playing!",S_W/2,250,RUSSET,-1);
	  textprintf_centre_ex(title,west36,S_W/2,200,RUSSET,-1,"You solved %i of %i correctly!",correct,total);
	  textout_centre_ex(title,west36,"please press Enter",S_W/2,300,RUSSET,-1);
	  textout_centre_ex(title,west36,"or the escape key",S_W/2,350,RUSSET,-1);
	  textout_centre_ex(title,west36,"to exit the game.",S_W/2,400,RUSSET,-1);
	  if (++fire.frameCount > fire.frameDelay)
	  {
		fire.frameCount=0;
		if (++fire.currFrame == fire.maxFrame)
			fire.currFrame=0;
	  }
	  draw_sprite(title,fire.frames[fire.currFrame],fire.x,fire.y);
	  blit(title,screen,0,0,0,0,title->w, title->h);
	}
}

int main()
{
	init();
	srand(time(NULL));
	show_mouse(screen);
	enable_hardware_cursor();
	select_mouse_cursor(MOUSE_CURSOR_ARROW);
	phrases.push_back(phrase("cowboy"));
	phrases.push_back(phrase("outlaws"));
	phrases.push_back(phrase("sheriff"));
	phrases.push_back(phrase("ranch hand"));
	phrases.push_back(phrase("cattle rustler"));

	total = phrases.size();
	word = rand() % phrases.size();

	body.push_back(shape(550,350,40));
	body.push_back(shape(530,360,570,480));
	body.push_back(shape(460,400,535,420));
	body.push_back(shape(570,400,640,420));
	body.push_back(shape(530,480,545,570));
	body.push_back(shape(555,480,570,570));
	west28 = load_font("shelldrake_28.pcx",NULL,NULL);
	west36 = load_font("shelldrake_36.pcx",NULL,NULL);
	west48 = load_font("shelldrake_48.pcx",NULL,NULL);
	west72 = load_font("shelldrake_72.pcx",NULL,NULL);
	title = create_bitmap(S_W,S_H);
	back = load_bitmap("background.bmp",NULL);
	blank = create_bitmap(S_W,S_H);
	tumble = load_bitmap("tumbleweedsprite.bmp",NULL);
	firework = load_bitmap("fireworks.bmp",NULL);
	weed = anim(8,10,150,650,100,100,tumble);
	fire = anim(6,20,448,512,384,128,firework,1);
	int keyDown;
	while (!key[KEY_ESC])
	{
		while(!key[KEY_ENTER] && startGame && !key[KEY_ESC])
		{
		  clear_bitmap(title);
		  blit(back,title,0,0,0,0,screen->w, screen->h);
		  textout_centre_ex(title,west48,"Welcome to Wild West Hangman!",S_W/2,100,RUSSET,-1);
		  textout_centre_ex(title,west36,"The Rules:",S_W/2,200,RUSSET,-1);
		  textout_centre_ex(title,west36,"Use the keyboard to guess the letters",S_W/2,250,RUSSET,-1);
		  textout_centre_ex(title,west36,"in the word or set of words.",S_W/2,300,RUSSET,-1);
		  textout_centre_ex(title,west36,"You only have 6 wrong guesses, so choose carefully.",S_W/2,350,RUSSET,-1);
		  textout_centre_ex(title,west36,"Run out of guesses, and you'll be hanged!",S_W/2,400,RUSSET,-1);
		  textout_centre_ex(title,west36,"When you correctly guess a word or phrase,",S_W/2,450,RUSSET,-1);
		  textout_centre_ex(title,west36,"you will be given the next word to solve.",S_W/2,500,RUSSET,-1);
		  textout_centre_ex(title,west36,"Press Enter to continue. Good Luck!",S_W/2,550,RUSSET,-1);
		  if (++weed.frameCount > weed.frameDelay)
		  {
			if(weed.x >=1280)
			{
				weed.x=-100;
			}
			else
			{
				weed.x+=10;
			}
			weed.frameCount=0;
			if (++weed.currFrame == weed.maxFrame)
			weed.currFrame=0;
		  }
		  draw_sprite(title,weed.frames[weed.currFrame],weed.x,weed.y);
		  //stretch_sprite(title,weed.frames[weed.currFrame],weed.x,weed.y,150,150);
		  blit(title,screen,0,0,0,0,title->w, title->h);
		}
		startGame = false;
		clear_bitmap(blank);
		blit(back,blank,0,0,0,0,screen->w, screen->h);
		keyDown = keyPressed();
		if(keyDown != -1)
		{
			checkChar(keyDown,&phrases[word]);
		}

		for(int i = 0; i < wrong; i++)
		{
				createShapeCenter(body[i],BLACK,blank);
		}
		printGuessed(blank,west36,870,1170,100,RUSSET);
		printUlineCenter(blank,west72,&phrases[word],S_W/2,S_H-(S_H/4), RUSSET);
		if(wordSolved())
		{
			correct++;
			if(phrases.size() <2)
			{
				endScreen();
				break;
			}
			else
			{
				pauseScreen();
			}
			reset();
		}
		if(wrong >= 6)
		{
			if(phrases.size() <2)
			{
				endScreen();
				break;
			}
			else
			{
				hangedScreen();
			}
			reset();
		}
		blit(blank,screen,0,0,0,0,title->w, title->h);

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
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 960, 720, 0, 0);
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
