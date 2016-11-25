#include "acllib.h"
#include <stdlib.h>
#include <stdio.h>
#define TITLEX 200
#define TITLEY 20
#define ONE 20
#define framelength 700
#define framewidth 560
#define AA 65
#define DD 68
#define WW 87
#define SS 83
#define MOVEA (head2=add(head2,head2->x-ONE,head2->y))
#define MOVED (head2=add(head2,head2->x+ONE,head2->y))
#define MOVEW (head2=add(head2,head2->x,head2->y-ONE))
#define MOVES (head2=add(head2,head2->x,head2->y+ONE))

typedef struct snake* snk;
struct snake{
	int x;
	int y;
	snk next;
};


void loadImage(const char *pImageFileName,ACL_Image *pImage);
void putImage(ACL_Image *pImage,int x,int y);
void loadSound(const char *fileName, ACL_Sound *pSound);
void playSound(ACL_Sound soundID,int repeat);
typedef void (*MouseEventCallback) (int x,int y,int button,int event);
void registerMouseEvent(MouseEventCallback callback);
void registerTimerEvent(TimerEventCallback callback);
void paintText(int x,int y,const char *pStr);
void setTextColor(ACL_Color color);
void setTextBkColor(ACL_Color color);
void setTextSize(int size);
void rectangle(int nLeftRect,int nTopRect,int nRightRect, int nBottomRect);
void mapframe(void);
void registerKeyboardEvent(KeyboardEventCallback callback);
void keylistener (int key,int event);

void drawsnake(snk head,int []);
snk add(snk head,int x,int y);
snk initsnake();
snk move(snk head2,int key,int food[]);


const int rectanglex1=40,rectangley1=100,rectanglex2=framewidth-40,rectangley2=framelength-20;
const int snakex0=220,snakey0=280;
char grade[100][5]={"0","0","0","0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15","16","17",
					"18","19","20","21","22","23","24","25","26","27"};
int life=3;//生命初始值
int food[2]={220,480};
snk head;
int key=WW;int lastkey=84;//用来保存蛇之前的运动方向 
int lifeflag=0;//标志是否吃到食物
int song11=0;

void keylistener (int key0,int event)
{
	key=key0;
}

void timerlistener(int ID)
{ 
	ACL_Sound song1,song2,song3,song4,song5,song6,song7,song8,song9,song10;
	clearDevice();
	registerKeyboardEvent(keylistener);	

	if (life==4&&lifeflag)
	{
		loadSound("first.mp3",&song1);
		playSound(song1,0);		
	
	}		
	else if(life==5&&lifeflag)
	{
		loadSound("double.mp3",&song2);
		playSound(song2,0);
	}
	else if(life==6&&lifeflag)
	{
		loadSound("dominating.mp3",&song3);
		playSound(song3,0);
	}
	else if(life==7&&lifeflag)
	{
		loadSound("megakill.mp3",&song4);
		playSound(song4,0);
	}
	else if(life==8&&lifeflag)
	{
		loadSound("whickedsick.mp3",&song5);
		playSound(song5,0);
	}
	else if(life==9&&lifeflag)
	{
		loadSound("unstopable.mp3",&song6);
		playSound(song6,0);
	}
	else if(life==10&&lifeflag)
	{
		loadSound("rampage.mp3",&song7);
		playSound(song7,0);
	}
	else if(life==11&&lifeflag)
	{
		loadSound("godlike.mp3",&song8);
		playSound(song8,0);
	}
	else if(life==12&&lifeflag)
	{
		loadSound("ownage.mp3",&song9);
		playSound(song9,0);
	}
	else if (life>12&&lifeflag) 
	{
		loadSound("holyshit.mp3",&song10);
		playSound(song10,0);
	}

	mapframe();	
	beginPaint();
	setTextSize(20);
	setTextColor(RED);	
	paintText(TITLEX+85,TITLEY+33,grade[life]);
	endPaint();
	head=move(head,key,food);	
	if (head==NULL)
	{
		beginPaint();
		setTextSize(28);
		setTextColor(RED);
		setTextBkColor(EMPTY);
		paintText(TITLEX,TITLEY+15*ONE,"游戏结束了");
		endPaint();	
		cancelTimer(1);	
	}
	else
		drawsnake(head,food);
	if (lifeflag==1)
	{
		cancelTimer(1);
		registerTimerEvent(timerlistener);
		startTimer(1,350-20*life);
	}
}

void mapframe(void)//画地图 
{
	ACL_Image bk;
	beginPaint();
	loadImage("background.jpg",&bk);
	putImageScale(&bk,0,0,560,700);
	
	setTextSize(28);
	setTextColor(RED);
	setTextBkColor(EMPTY);
	paintText(TITLEX,TITLEY,"贪 吃 婷");
	setTextSize(20);
	paintText(TITLEX+30,TITLEY+33,"好吃:");
	setTextSize(18);
	paintText(TITLEX-160,TITLEY+20,"上:W");	
	paintText(TITLEX-160,TITLEY+40,"下:S");
	paintText(TITLEX-100,TITLEY+20,"左:A");
	paintText(TITLEX-100,TITLEY+40,"右:D");	
	setPenWidth(5);
	setPenColor(EMPTY);
	setBrushColor(RGB(83,83,83));
	rectangle(rectanglex1-ONE,rectangley1-ONE,rectanglex1,rectangley2);
	rectangle(rectanglex1-ONE,rectangley1-ONE,rectanglex2,rectangley1);
	rectangle(rectanglex2,rectangley1-ONE,rectanglex2+ONE,rectangley2+ONE);
	rectangle(rectanglex1-ONE,rectangley2,rectanglex2+ONE,rectangley2+ONE);
	endPaint();
}



void drawsnake(snk head,int food[])//画蛇和食物 
{
	snk p;p=head;
	ACL_Image img,lip;
	beginPaint();
	loadImage("shiting.jpg",&img);
	loadImage("lipstick.jpg",&lip);

	while(p)
	{			
		putImageScale(&img,p->x,p->y,ONE,ONE);
		p=p->next;
	}
	setPenColor(BLUE);
	setPenWidth(3);
	putImageScale(&lip,food[0],food[1],ONE,ONE);
	endPaint();	
}

snk add(snk head1,int x,int y)//给蛇添加头 
{
	snk temp;
	temp=(snk)malloc(sizeof(struct snake));
	temp->x=x;
	temp->y=y;
	temp->next=head1;
	return temp;	
}


snk initsnake()//初始化蛇的身体 
{
	snk head0;
	int i;
	head0=(snk)malloc(sizeof(struct snake));
	head0->x=snakex0;
	head0->y=snakey0;
	head0->next=NULL;
	for(i=1;i<life;++i)
		head0=add(head0,head0->x+ONE,head0->y);
	return head0;
}

snk move(snk head2,int key,int food[])
{
	snk temp,p;
	switch (key){//根据输入的按键改变蛇的运动方向 
		case WW:lastkey!=SS?MOVEW:MOVES;	break;
		case AA:lastkey!=DD?MOVEA:MOVED;	break;
		case SS:lastkey!=WW?MOVES:MOVEW;	break;
		case DD:lastkey!=AA?MOVED:MOVEA;	break;
		default:
				{
					switch (lastkey){
						case WW:MOVEW;break;
						case SS:MOVES;break;
						case AA:MOVEA;break;
						case DD:MOVED;break;
						default:break;
					}
				}
				break;
	}
	if((key==AA&&lastkey!=DD)||(key==SS&&lastkey!=WW)||(key==WW&&lastkey!=SS)||(key==DD&&lastkey!=AA))
	lastkey=key;//将当前运动方向保存下来 
	p=head2;
	if (p->x<rectanglex1||p->x>rectanglex2-ONE||p->y<rectangley1||p->y>rectangley2-ONE)
	   	life=0;
	else
	{
		p=p->next;
		while(p)
		{
			if(p->x==head2->x&&p->y==head2->y)
			{
				life=0;
				break;
			}
			p=p->next;
		}
	}
	
	if (life==0)
	{
		head2=NULL;lifeflag=0;
	}	
	else
	{
		p=head2;
		if(abs(head2->x-food[0])>10||abs(head2->y-food[1])>10)
		{
			while(p->next->next)
				p=p->next;
			temp=p->next;
			p->next=NULL;
			free(temp);
			lifeflag=0;
		}
		else
		{
			food[0]=(rand()%23)*ONE+rectanglex1;
			food[1]=(rand()%28)*ONE+rectangley1;
			++life;
			lifeflag=1;	
		}					
	}	
	return head2;
}

void timer1(int ID)
{
	if (key==DD)
	{
		if(song11==0)
		{
			ACL_Sound song11;
			loadSound("meat.mp3",&song11);
			playSound(song11,0);
			song11=1;
		}
		cancelTimer(0);	
		registerTimerEvent(timerlistener);
		startTimer(1,350-20*life);
	}

}
int Setup()
{
	initWindow ("test",400,0,560,700);
	ACL_Sound song;
	
	head=initsnake();			
	mapframe();
	beginPaint();
	setTextSize(28);
	setTextColor(RED);
	setTextBkColor(EMPTY);
	paintText(TITLEX,TITLEY+15*ONE,"按D开始游戏");	
	endPaint();
	loadSound("Nightelf.mp3",&song);
	playSound(song,1);
	registerTimerEvent(timer1);
	registerKeyboardEvent(keylistener);	
	startTimer(0,50);

	return 0;
}
