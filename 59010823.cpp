#include <stdio.h>
#include <conio.h>
#include "libconsole.cpp"
const int wide=37;
const int dis=100;
const int ResX=150;
const int ResY=100;
const int MuiTenCount=3;
const int numbw=6;
const int numh=30;
const int disbetnum=1 ; 
const int scoretop=0;

struct TPoint  
	{
		int x;
		int y;
	};

struct TMuiTen 
	{
		int x;
		int length;
	};

int bird[20][20];
int birddied[20][20];
int GameOverMsgImg[100][100];
int logo[100][100];
int BirdH,BirdW;
int BirdX=30;
int BirdY=0;
int logow,logoh;
int govmsgw,govmsgh; 
int quitgame;
int raw;
int died;
int score;
int bestscore;
int pause;
int quitall;
int number[15][15][15];
struct TMuiTen MuiTen[MuiTenCount];
int dangqua;

void GenMuiTen()
{
	int i,j;
	if (MuiTen[0].x<=0)
		{
			for ( i=0 ; i <= MuiTenCount-2 ; i++ )
				{
					MuiTen[i].x=MuiTen[i+1].x;
					MuiTen[i].length=MuiTen[i+1].length;
				}
		}
	MuiTen[MuiTenCount-1].x = MuiTen[MuiTenCount-2].x+dis;
	MuiTen[MuiTenCount-1].length = rand() % (ResY-10-wide-10+1) + 10;
}

void WelcomScreen()
{
	int i,j,t;
	
	system("MODE CON COLS=80 LINES=25");
	SetFontApp(8,16);
	clrscr(cllightblue);
	gotoxy(46,1);
		SetConsoleColor(cllightyellow, cllightblue);	
	printf("\n\n\n\n\n"); //small slant font
              printf("\t\t   ______                      ___  _______  ___ \n");
              printf("\t\t  / __/ /__ ____  ___  __ __  / _ )/  _/ _ \\/ _ \\\n");
              printf("\t\t / _// / _ `/ _ \\/ _ \\/ // / / _  \|/ // , _/ // /\n");
              printf("\t\t/_/ /_/\\_,_/ .__/ .__/\\_, / /____/___/_/|_/____/ \n");
              printf("\t\t          /_/  /_/   /___/                       \n");
	printf("\n\n\n\t\t\t:::: Press Any key TO play ::::");
		gotoxy(54,0);
		printf("PLAYFA KHEMAPHECH 59010823");
	getch();
}



void ReadBestScore( int *best )
{
	FILE *fs;
	
	int tmp;
	if((fs=fopen("data\\best.txt","rt"))==NULL)
	{
		printf("can not open file");
		getch();
		return;
	}
	fscanf(fs,"%d",best);
	fclose(fs);	
}

void WriteBestScore(int best)
{
	FILE *f;
	remove("data\\best.txt");
	if((f=fopen("data\\best.txt","w"))==NULL)
	{
		printf("can not open file");
		getch();
		fclose(f);
		return;
	}
	fprintf(f,"%d",best);
	fclose(f);	
}

int GameOverMsg(int score,int best)
{
	int i,j,c;
	int temp,scoretmp,num[100],index,scorew,scoreh,scoreleft,k,lastx;
	char keypr;
	
	gotoxy(40,0);
		printf("Game Flappy Bird C++  - PLAYFA KHEMAPHET");
	for(j=0;j<=govmsgh;j++)
		{
			gotoxy((ResX-70)/2,(ResY-16)/2+j);
			for(i=0;i<=govmsgw;i++)
			{		
				c=GameOverMsgImg[i][j];
				switch(c)
				{
					case 'B':
						{
							SetConsoleColor(clgreen,clgray);
							printf("%c",219);
							break;
						}
					case '#':
						{
							SetConsoleColor(clblue,clblack);
							printf("%c",219);
							break;
						}
					case 'X':
						{
							SetConsoleColor(cllightred,clblack);
							printf("%c",219);
							break;
						}
					default :
						{
							SetConsoleColor(cllightwhite,clgray);
							printf("%c",176);
							break;
						}
				}
			}	
		}
	index=-1;	
	temp=best;
	do
	{
		index++;
		num[index]=temp%10;
		temp=temp/10;		
	}
	while (temp!=0);
	scoreh=numh;
	scorew=numbw*index+(index-1)*disbetnum;
	scoreleft=(ResX-scorew)/2;
	lastx=(ResX-70)/2+35;
	SetConsoleColor(cllightyellow,clblack);	
	
	for(i=index;i>=0;i--)
		{
			gotoxy(lastx,(ResY-16)/2+3);
			for(j=0;j<=5;j++)
				{
					gotoxy(lastx,(ResY-16)/2+2+j);
					for(k=0;k<=2;k++)
						if(number[num[i]][k][j]==78)
							printf("%c",219);
						else printf(" ");					
				}
			lastx=lastx+numbw+disbetnum;			
		}	
	
	temp=0;
	scoretmp=-1;
	index=-1;
	do
	{
		scoretmp++;
		temp=scoretmp;
		index=-1;
		do
		{
			index++;
			num[index]=temp%10;
			temp=temp/10;		
		}
		while (temp!=0);
		

		scoreh=numh;
		scorew=numbw*index+(index-1)*disbetnum;
		scoreleft=(ResX-scorew)/2;
		lastx=(ResX-70)/2+35;
		SetConsoleColor(cllightwhite,clgray);
		

		for(j=(ResY-16)/2+9;j<=(ResY-16)/2+16-1;j++)
		{
			gotoxy(lastx,j);
			for(i=lastx;i<=(ResX-70)/2+70-3;i++)		
			{
				printf("%c",176);
			}
		}
		SetConsoleColor(cllightyellow,clblack);	
		

		for(i=index;i>=0;i--)
		{
			gotoxy(lastx,(ResY-16)/2+9);
			for(j=0;j<=5;j++)
				{
					gotoxy(lastx,(ResY-16)/2+9+j);
					for(k=0;k<=2;k++)
						if(number[num[i]][k][j]==78)
							printf("%c",219);
						else printf(" ");					
				}
			lastx=lastx+numbw+disbetnum;			
		}	
		Sleep(500/((score==0)?1:score));
	}	
	while (scoretmp!=score);
	
	
		keypr='2';
		do
		{
			if (GetAsyncKeyState(VK_RETURN)) keypr=VK_RETURN;
		}
		while(keypr=='2');
	if (score>best) bestscore=score;
		return ((keypr==VK_RETURN)?1:0);
		
}

void LoadNumber()
{
	int i,j,c;
	FILE *f;
	
	if ((f=fopen("data\\0.txt","r"))!=NULL)
	{
		i=-1;
		j=0;
		do
		{
			c=getc(f);
			if(c=='\n') 
			{
				i=-1;
				j++;
				
			}
			else
			{
				i++;
				number[0][i][j]=c;
				
			}
		}
		while (c!=EOF);
	}
	else 
	{
		printf("can not open file");
		return;
	}
	fclose(f);
	
	if ((f=fopen("data\\1.txt","r"))!=NULL)
	{
		i=-1;
		j=0;
		do
		{
			
			c=getc(f);
			if(c=='\n') 
			{
				i=-1;
				j++;
				
			}
			else
			{
				i++;
				number[1][i][j]=c;
				
			}
		}
		while (c!=EOF);
	}
	else 
	{
		printf("can not open file");
		return;
	}
	fclose(f);
	
	if ((f=fopen("data\\2.txt","r"))!=NULL)
	{
		i=-1;
		j=0;
		do
		{
			c=getc(f);
			if(c=='\n') 
			{
				i=-1;
				j++;
				
			}
			else
			{
				i++;
				number[2][i][j]=c;
				
			}
		}
		while (c!=EOF);
	}
	else 
	{
		printf("can not open file");
		return;
	}
	fclose(f);
	
	if ((f=fopen("data\\3.txt","r"))!=NULL)
	{
		i=-1;
		j=0;
		do
		{
			c=getc(f);
			if(c=='\n') 
			{
				i=-1;
				j++;
				
			}
			else
			{
				i++;
				number[3][i][j]=c;
				
			}
		}
		while (c!=EOF);
	}
	else 
	{
	printf("can not open file");
		return;
	}
	fclose(f);
	
	if ((f=fopen("data\\4.txt","r"))!=NULL)
	{
		i=-1;
		j=0;
		do
		{
			c=getc(f);
			if(c=='\n') 
			{
				i=-1;
				j++;
				
			}
			else
			{
				i++;
				number[4][i][j]=c;
				
			}
		}
		while (c!=EOF);
	}
	else 
	{
		printf("can not open file");
		return;
	}
	fclose(f);
	if ((f=fopen("data\\5.txt","r"))!=NULL)
	{
		i=-1;
		j=0;
		do
		{
			c=getc(f);
			if(c=='\n') 
			{
				i=-1;
				j++;
				
			}
			else
			{
				i++;
				number[5][i][j]=c;
				
			}
		}
		while (c!=EOF);
	}
	else 
	{
		printf("can not open file");
		return;
	}
	fclose(f);
	if ((f=fopen("data\\6.txt","r"))!=NULL)
	{
		i=-1;
		j=0;
		do
		{
			c=getc(f);
			if(c=='\n') 
			{
				i=-1;
				j++;
				
			}
			else
			{
				i++;
				number[6][i][j]=c;
				
			}
		}
		while (c!=EOF);
	}
	else 
	{
		printf("can not open file");
		return;
	}
	fclose(f);
	if ((f=fopen("data\\7.txt","r"))!=NULL)
	{
		i=-1;
		j=0;
		do
		{
			c=getc(f);
			if(c=='\n') 
			{
				i=-1;
				j++;
				
			}
			else
			{
				i++;
				number[7][i][j]=c;
				
			}
		}
		while (c!=EOF);
	}
	else 
	{
		printf("can not open file");
		return;
	}
	fclose(f);
	if ((f=fopen("data\\8.txt","r"))!=NULL)
	{
		i=-1;
		j=0;
		do
		{
			c=getc(f);
			if(c=='\n') 
			{
				i=-1;
				j++;
				
			}
			else
			{
				i++;
				number[8][i][j]=c;
				
			}
		}
		while (c!=EOF);
	}
	else 
	{
		printf("can not open file");
		return;
	}
	fclose(f);
	if ((f=fopen("data\\9.txt","r"))!=NULL)
	{
		i=-1;
		j=0;
		do
		{
			c=getc(f);
			if(c=='\n') 
			{
				i=-1;
				j++;
				
			}
			else
			{
				i++;
				number[9][i][j]=c;
				
			}
		}
		while (c!=EOF);
	}
	else 
	{
		printf("can not open file");
		return;
	}
	fclose(f);
	
}

void step()
{
	int i;
	for(i=0;i<=MuiTenCount-1;i++)
		MuiTen[i].x=MuiTen[i].x-3;
}


void DrawM(int x,int l)
{
	int i;
	
	if(x<ResX-1)
	{		
		for(i=l;i>=0;i--)
		{
			SetConsoleColor(((i%2==0)?cllightwhite:cllightred),clblack);
			gotoxy(x,i);
			printf("%c%c%c",177,219,177);
		}
	
		for(i=0;i<=ResY-l-wide;i++)
		{
			SetConsoleColor(((i%2==0)?cllightwhite:cllightred),clblack);
			gotoxy(x,ResY-1-i);
			printf("%c%c%c",177,219,177);
		}
	}	
}

void InScore(int score)
{
	int temp,num[100],index,scorew,scoreh,i,scoreleft,j,k,lastx;
	temp=score;
	index=-1;
	

	do
	{
		index++;
		num[index]=temp%10;
		temp=temp/10;		
	}
	while (temp!=0);
	

	scoreh=numh;
	scorew=numbw*index+(index-1)*disbetnum;
	scoreleft=(ResX-scorew)/2;
	lastx=scoreleft;
	SetConsoleColor(cllightyellow,clblack);
			
	for(i=index;i>=0;i--)
		{
			for(j=0;j<=5;j++)
				{
					gotoxy(lastx,scoretop+j);
					for(k=0;k<=2;k++)
						if(number[num[i]][k][j]==78)
							printf("%c",219);
						else printf(" ");					
				}
			lastx=lastx+numbw+disbetnum;			
		}		
}

void DrawMu()
{
	int i;
	for(i=0;i<MuiTenCount;i++)
		DrawM(MuiTen[i].x,MuiTen[i].length);
}



void DrawBird(int x,int y)
{
	int i,j,c,t;
	
	gotoxy(x,y);
	for(j=0;j<=BirdH;j++)
	{
		for(i=0;i<=BirdW;i++)
			{
				c=bird[i][j];
				switch (c)
					{
						case 'B':
							{
								SetConsoleColor(clblack,clwhite);
								t=219 ; break;
							}
						case 'R':
							{
								SetConsoleColor(cllightred,clwhite);
								t=219; break;
							}
						case 'Y':
							{
								SetConsoleColor(cllightyellow,cllightblue);
								t=219; break;
							}
						case 'W':
							{
								SetConsoleColor(cllightwhite,clwhite);
								t=219; break;
							}
						case 'O':
							{
								SetConsoleColor(cllightgreen,clblue);
								t=219; break;
							}
						default: 
							{
								t=c;
								SetConsoleColor(cllightblue,cllightblue);
							}
					}
				printf("%c",t);
			}
		gotoxy(x,y+j+1);
				 
	}
}

void DrawBirdDown(int x,int y)
{
	int i,j,c,t;
	
	gotoxy(x,y);
	for(j=0;j<=BirdW;j++)
	{

		for(i=BirdH;i>=0;i--)
			{
				c=bird[j][i];
				switch (c)
					{
						case 'B':
							{
								SetConsoleColor(clblack,clwhite);
								t=219 ; break;
							}
						case 'R':
							{
								SetConsoleColor(clred,clwhite);
								t=219; break;
							}
						case 'Y':
							{
								SetConsoleColor(cllightyellow,cllightblue);
								t=219; break;
							}
						case 'W':
							{
								SetConsoleColor(cllightwhite,clwhite);
								t=219; break;
							}
						case 'O':
							{
								SetConsoleColor(cllightgreen,clblue);
								t=219; break;
							}
						default: 
							{
								t=c;
								SetConsoleColor(cllightblue,cllightblue);
							}
					}
				 printf("%c",t);
				}
				 gotoxy(x,y+j+1);
			}

}



void loadgameoverimg(int *maxx,int *maxy)
{
	FILE *fs;
	int i,j,c;
	if((fs=fopen("data\\GameOverImg.txt","r"))==NULL)
		{
			printf(" ");
			getch();
			return;
		}
	i=-1;j=0;		
	do
	{
		c=getc(fs);
		if (c=='\n') 
		{
			j++;
			i=-1;
			continue;
		}
		
		if (c!=EOF)
		{
			i++;
			GameOverMsgImg[i][j]=c;
		}	
	}
	while (c!=EOF);
	*maxx=i;
	*maxy=j;

	fclose(fs);
}

int LoadBirdImage(int *maxx,int *maxy)
{
	FILE *fs;
	int c,t,i,j;
	if((fs=fopen("data\\flappybird.txt","r"))==NULL)
		{
			return 0;
		}
	i=-1;j=0;		
	do
	{
		c=getc(fs);
		if (c=='\n') 
		{
			j++;
			i=-1;
			continue;
		}
		
		if (c!=EOF)
		{
			i++;
			bird[i][j]=c;
		}	
	}
	while (c!=EOF);
	*maxx=i;
	*maxy=j;
	fclose(fs);
}


void Render()
{
	clrscr(cllightblue);
	if (died) 
		DrawBirdDown(BirdX,BirdY);
	else
		DrawBird(BirdX,BirdY);
	InScore(score);	
	DrawMu();	
}

void setdefaultsetting()
{
	system("MODE CON COLS=150 LINES=100");
	SetFontApp(4,6);
	MaximizeWindow();
}

void init()
{
	int i;
	
	dangqua=FALSE;
	raw=0;
	score=0;
	quitgame=false;
	quitall=false;
	pause=false;
	died=FALSE;
	BirdY=0;
	
	for(i=0;i<3;i++)
	{
		MuiTen[i].x=149+i*dis;
		MuiTen[i].length=rand() % (ResY-10-wide-10+1) + 10;;
	}
}



int checkdied()
{
	int i,died;
	struct TPoint TopOfTop,DownOfTop,TopOfDown,DownOfDown;
	struct TPoint Bird1,Bird2;
	died=false;
	Bird1.x=BirdX;
	Bird1.y=BirdY;
	Bird2.x=BirdX+BirdW;
	Bird2.y=BirdY+BirdH;

	
	
	if((BirdY+BirdH)>=ResY) return 1;
	
	for(i=0;i<MuiTenCount;i++)
		{

				TopOfTop.x=MuiTen[i].x;
				TopOfTop.y=0;
				DownOfTop.x=MuiTen[i].x;
				DownOfTop.y=0+MuiTen[i].length;
				
				TopOfDown.x=MuiTen[i].x;
				TopOfDown.y=0+MuiTen[i].length+wide;
				DownOfDown.x=MuiTen[i].x;
				DownOfDown.y=ResY-1;
				
				if((Bird2.x>=TopOfTop.x )&& (Bird1.x<TopOfTop.x))
					dangqua=i;
				if ((i==dangqua)&&(TopOfTop.x<Bird1.x))
					
					{
						score++;
						dangqua=-1;	
					}
				died=(Bird1.x<DownOfTop.x)&&(DownOfTop.x<Bird2.x)&&((DownOfTop.y>Bird1.y)||(TopOfDown.y<Bird2.y));
				if (died==TRUE) break;		
		}
		return died;
}

void GameOver()
{
	int i;
	for(i=600;i<=6000;i=i+50)
		Beep(i,60);
}

int gamemenu()
{
	int i,play;
	system("MODE CON COLS=80 LINES=25");
	SetFontApp(8,16);
	clrscr(cllightblue);
	DrawBird(2,4);
	SetConsoleColor(cllightyellow, cllightblue);	
	i=6;			
		gotoxy(20, i);              printf("   ______                      ___  _______  ___ \n");
        gotoxy(20, i+1);      printf("  / __/ /__ ____  ___  __ __  / _ )/  _/ _ \\/ _ \\ \n");
        gotoxy(20, i+2);      printf(" / _// / _ `/ _ \\/ _ \\/ // / / _  \|/ // , _/ // /\n");
        gotoxy(20, i+3);      printf("/_/ /_/\\_,_/ .__/ .__/\\_, / /____/___/_/|_/____/ \n");
        	gotoxy(20, i+4);      printf("          /_/  /_/   /___/                       \n");
	gotoxy(30,13);
	SetConsoleColor(cllightyellow,cllightblue);
	printf("HIGHSCORE : %d",bestscore);
	gotoxy(36,23);
	SetConsoleColor(cllightgreen,cllightblue);
	printf("PLAYFA KHEMAPECH");
	SetConsoleColor(cllightred,clblue);
	play=-1;
	do
	{
		gotoxy(20,14);
		printf(" SPACE bar to play , ESC to exit");
		Sleep(200);
		gotoxy(20,14);
		printf("                                        ");
		Sleep(200);
		if(GetAsyncKeyState(VK_SPACE))
			{
								Beep(700,50);
				play=1;
			}
		if(GetAsyncKeyState(VK_ESCAPE))
			{
								Beep(700,50);
				play=0;
			}
		
	}
	while(play==-1);
	return play;
}
void help()
{
	char sel;
	system("MODE CON COLS=80 LINES=25");
	SetFontApp(8,16);
	clrscr(cllightblue);
	DrawBird(2,4);
	SetConsoleColor(cllightyellow, cllightblue);
    system("cls");
    while(true)
    {
    printf("\n\n                   Controls: Press space bar to fly up. P to pause         \n");
    printf("             Goal: Fly through the holes between the pipes.   	  \n");
    printf("             When you pass through the hole,you get 1 point.   	  \n");
    printf("                    Try to pass as much as you can.   	  \n");
    printf("            But be careful, don't hit the pipes or the ground!   	  \n");
    printf("                          Are you ready? ?   Press y to go  : :	");
    scanf("%c",&sel);
    if(sel=='y') return;
    else system("cls");
    }
}
main()
{	
	int giatocroi=0;
	int menuselection;
	char name[20];	
	hidecursor();
	initlibrary();
	LoadBirdImage(&BirdW,&BirdH);
	loadgameoverimg(&govmsgw,&govmsgh);
	LoadNumber();
	ReadBestScore(&bestscore);
	WelcomScreen();
					Beep(700,50);
	do
	{
		init();
	
		menuselection=gamemenu();					Beep(700,50);  help();
		if(menuselection==0) 
		{
			quitall=true; 
		}
		setdefaultsetting();
		clrscr(cllightblue);
		do
			{	
				
				Render();
				died=checkdied();
				if (died)
					{

						giatocroi=0;
						do
							{
								BirdY=BirdY+1.5*giatocroi;
								if(BirdY+BirdW>ResY) 
									BirdY=ResY-BirdW-1;
													Beep(700,50);
								Render();
								giatocroi=giatocroi+1;
							}
						while (BirdY!=ResY-BirdW-1);
						if(GameOverMsg(score,bestscore)!=1) 
						{
							quitall=true;
						}
					}
				else
				{
					step();
				GenMuiTen();
				if(raw>0)
					BirdY= BirdY-raw;
				else
					BirdY=BirdY+4;
				if (raw>0) 
					raw=raw-1;
				if(raw<5) raw=0;
				if (BirdY<0) 
					BirdY=0;
				if (GetAsyncKeyState(VK_SPACE))
				{raw=7;
				}
							
				if ((GetAsyncKeyState('P')||GetAsyncKeyState('p'))&&(!quitgame))
					pause=true;
				Sleep(10);
				if (GetAsyncKeyState(VK_ESCAPE))
				{
					system("cls");
					system("MODE CON COLS=80 LINES=25");
	SetFontApp(8,16);
	clrscr(cllightblue);
	gotoxy(46,1);
		SetConsoleColor(cllightyellow, cllightblue);
					printf("\n\n\n\n\n\n\n\t\t   ________   __  _______   ____ _   _________\n");
                    printf("\t\t  / ___/ _ | /  |/  / __/  / __ \\ | / / __/ _ \\ \n");
                    printf("\t\t / (_ / __ |/ /|_/ / _/   / /_/ / |/ / _// , _/ \n");
                    printf("\t\t \\___/_/ |_/_/  /_/___/  \\____/|___/___/_/|_| \n");
                    
					return 0;
				}
				if(pause)
					{
								printf("  tab SPACE bar continue to play ,  ESC to exit");
						do
							{
								pause=!GetAsyncKeyState(VK_SPACE);
								if(GetAsyncKeyState(VK_ESCAPE))
								{
													Beep(700,50);
									died=1;
									pause=0;
								}
								
							}
						while(pause==true);
						SetConsoleTitle("game pause");
					}
				}		
			}
		while (((!died)&&(!quitall)));
		SetConsoleColor(cllightwhite,clblack);
	}
	while (!quitall);
	WriteBestScore(bestscore);
}
