#include <allegro.h>
#define MY_COLOR makecol(100,0,255)
#define BLAZE_ORANGE makecol(255,102,0)
#define BLUE makecol(0,0,255)

void init();
void deinit();
struct shape
{
    int x;//upper left
    int y;
    int length;
    int x2;//lower right
    int y2;

    shape(int xx, int yy, int myLength)
    {
       x = xx;
       y = yy;
       length = myLength;
       x2 = xx+20;
       y2 = yy+myLength;
    }
};

bool startGame = true;
const int INITIAL_SPEED = 6;
const int PLAYER_SPEED = 2;
int gameSpeed = 1;
int round = 0;
const int roundInterval = 2;
shape p1 = shape(5,180,120);
shape p2 = shape(615,180,120);
shape ball = shape(310,230,20);
const int winningScore = 11;
int p1score = 0;
int p2score = 0;
bool up = true;
bool left = true;

void updateShape(shape &pad, int type)
{
   if(type == 1)
   {
      pad = shape(pad.x,pad.y,pad.length);
   }
   else
   {
      pad = shape(pad.x,pad.y,20);
   }
}

void reset(int winner)
{
	if(winner == 1)
	{
		left = true;
		p1score++;
	}
	if(winner == 2)
	{
		left = false;
		p2score++;
	}
	p1 = shape(5,180,120);
	updateShape(p1,1);
	p2 = shape(615,180,120);
	updateShape(p1,1);
	ball = shape(310,230,20);
	updateShape(ball,2);
	round = 0;
	gameSpeed = 1;
}
void createRect(shape pad,int col, BITMAP *bit)
{
     int x2 = pad.x + 20;
     int y2 = pad.y + pad.length;
     rectfill(bit,pad.x,pad.y,x2,y2,col);
}

bool collision(shape ball, shape pad)
{
     return (((ball.x>=pad.x&&ball.x<=pad.x2)&&(ball.y>=pad.y&&ball.y<=pad.y2))||((ball.x>=pad.x&&ball.x<=pad.x2)&&(ball.y2>=pad.y&&ball.y2<=pad.y2))||((ball.x2>=pad.x&&ball.x2<=pad.x2)&&(ball.y2>=pad.y&&ball.y2<=pad.y2))||((ball.x2>=pad.x&&ball.x2<=pad.x2)&&(ball.y>=pad.y&&ball.y <=pad.y2)));
}



int main() {
	init();
	BITMAP *blank = create_bitmap(640,480);
	BITMAP *title = create_bitmap(640,480);
	BITMAP *end = create_bitmap(640,480);
	while (!key[KEY_ESC])
    {
          while(!key[KEY_Y] && startGame && !key[KEY_ESC])
          {
              clear_bitmap(title);
              textout_centre_ex(title,font,"Hello, and welcome to pong, by Eric Hoffmann!",320,100,BLAZE_ORANGE,-1);
              textout_centre_ex(title,font,"The rules are simple. Bounce the ball past your opponent's paddle ",320,120,BLAZE_ORANGE,-1);
              textout_centre_ex(title,font,"while stopping them from bouncing it past yours.",320,140,BLAZE_ORANGE,-1);
              textout_centre_ex(title,font,"Player 1 moves the paddle up and down with the w and s keys.",320,160,BLAZE_ORANGE,-1);
              textout_centre_ex(title,font,"Player 2 controls the paddle with the up and down arrow keys.",320,180,BLAZE_ORANGE,-1);
              textout_centre_ex(title,font,"Press y to continue to the game!",320,200,BLAZE_ORANGE,-1);
  		      blit(title,screen,0,0,0,0,title->w, title->h);
		      rest(5);
          }
          startGame = false;
          clear_bitmap(blank);

        if(key[KEY_W]&&(p1.y >= PLAYER_SPEED))
        {
          p1.y-=PLAYER_SPEED;
          updateShape(p1,1);
        }
        if(key[KEY_S]&&(p1.y2 <= 480-PLAYER_SPEED))
        {
          p1.y+=PLAYER_SPEED;
          updateShape(p1,1);
        }

        if(key[KEY_UP]&&(p2.y >= PLAYER_SPEED))
        {
          p2.y-=PLAYER_SPEED;
          updateShape(p2,1);
        }
        if(key[KEY_DOWN]&&(p2.y2 <= 480-PLAYER_SPEED))
        {
          p2.y+=PLAYER_SPEED;
          updateShape(p2,1);
        }

		if(ball.y<=1|| ball.y2 >= 479)
		{
           up = !up;
        }
	    if(up)
		{
            ball.y++;
            updateShape(ball,2);
        }
        else
        {
            ball.y--;
            updateShape(ball,2);
        }

        if(left==true&&collision(ball,p1))
        {
           round++;
           left = false;
        }
        if(left==false&&collision(ball,p2))
        {
           round++;
           left = true;
        }
        if(round == roundInterval && gameSpeed <=(INITIAL_SPEED-1))
        {
              round = 0;
              gameSpeed+=1;
        }
		if(left)
		{
            ball.x--;
            updateShape(ball,2);
        }
        else
        {
            ball.x++;
            updateShape(ball,2);
        }
		if(ball.x2<0)
		{
			reset(2);
			textprintf_ex(blank,font,100,100,BLAZE_ORANGE,-1,"Player 1 Score: %d",p1score);
			textprintf_ex(blank,font,420,100,BLAZE_ORANGE,-1,"Player 2 Score: %d",p2score);
			createRect(p1,BLUE,blank);
			createRect(p2,BLUE,blank);
			createRect(ball,MY_COLOR,blank);
			blit(blank,screen,0,0,0,0,blank->w, blank->h);
			rest(500);
		}

		if(ball.x>640)
		{
			reset(1);
			textprintf_ex(blank,font,100,100,BLAZE_ORANGE,-1,"Player 1 Score: %d",p1score);
			textprintf_ex(blank,font,420,100,BLAZE_ORANGE,-1,"Player 2 Score: %d",p2score);
			createRect(p1,BLUE,blank);
			createRect(p2,BLUE,blank);
			createRect(ball,MY_COLOR,blank);
			blit(blank,screen,0,0,0,0,blank->w, blank->h);
			rest(500);
		}
		textprintf_ex(blank,font,100,100,BLAZE_ORANGE,-1,"Player 1 Score: %d",p1score);
		textprintf_ex(blank,font,420,100,BLAZE_ORANGE,-1,"Player 2 Score: %d",p2score);
        createRect(p1,BLUE,blank);
        createRect(p2,BLUE,blank);
        createRect(ball,MY_COLOR,blank);
		blit(blank,screen,0,0,0,0,blank->w, blank->h);
		while((p1score >=11 || p2score >= 11)&&!key[KEY_ESC])
		 {
		     clear_bitmap(end);
		     textout_centre_ex(end,font,"Game Over!",320,100,BLAZE_ORANGE,-1);
		     if(p1score >= 11)
		     {
		    	 textout_centre_ex(end,font,"Player 1 wins!",320,120,BLAZE_ORANGE,-1);
		     }
		     else
		     {
		    	 textout_centre_ex(end,font,"Player 2 wins!",320,120,BLAZE_ORANGE,-1);
		     }
			 textout_centre_ex(end,font,"Press y to start a new game",320,140,BLAZE_ORANGE,-1);
			 if(key[KEY_Y])
			 {
				 p1score = 0;
				 p2score = 0;
				 reset(3);
				 break;
			 }
			 blit(end,screen,0,0,0,0,title->w, title->h);
			 rest(5);
		 }
		rest(INITIAL_SPEED-gameSpeed);

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
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
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
