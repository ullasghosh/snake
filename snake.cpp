#include<iostream.h>
#include<conio.h>
#include<fstream.h>

using namespace std;

char s[101][101],playername[20];
int w,h,val[101][101],highscore,score=0,valdist[101][101],xstart,ystart,changernum=2,playerlength=0,foodcordxy[10000][3],playercord[3],countdot=0,useddot,dot[10001][10001]={};

void left(int,int);
void right(int,int);
void up(int,int);
void down(int,int);
void initial(int,int);
void getmaze();
void foodcord();
void bringfood();
void moveplayer(char);

void left(int x, int y)
{
if(y-1>=0 && valdist[x][y-1]>=0)
          if(valdist[x][y-1]==0)
          {
                            valdist[x][y-1]=valdist[x][y]+1;
                            up(x,y-1);
                            down(x,y-1);
                            left(x,y-1);
              }
          else if(valdist[x][y]+1>=valdist[x][y-1])
                                         return;
          else
          {
              valdist[x][y-1]=valdist[x][y]+1;
              up(x,y-1);
              down(x,y-1);
              left(x,y-1);
              }
else
return;
}

void right(int x, int y)
{
if(y+1<w && valdist[x][y+1]>=0)
          if(valdist[x][y+1]==0)
          {
                            valdist[x][y+1]=valdist[x][y]+1;
                            up(x,y+1);
                            down(x,y+1);
                            right(x,y+1);
              }
          else if(valdist[x][y]+1>=valdist[x][y+1])
                                         return;
          else
          {
              valdist[x][y+1]=valdist[x][y]+1;
              up(x,y+1);
              down(x,y+1);
              right(x,y+1);
              }
else
return;
}

void up(int x, int y)
{
if(x-1>=0 && valdist[x-1][y]>=0)
          if(valdist[x-1][y]==0)
          {
                            valdist[x-1][y]=valdist[x][y]+1;
                            up(x-1,y);
                            right(x-1,y);
                            left(x-1,y);
              }
          else if(valdist[x][y]+1>=valdist[x-1][y])
                                         return;
          else
          {
              valdist[x-1][y]=valdist[x][y]+1;
              up(x-1,y);
              right(x-1,y);
              left(x-1,y);
              }
else
return;
}

void down(int x, int y)
{
if(x+1<h && valdist[x+1][y]>=0)
          if(valdist[x+1][y]==0)
          {
                            valdist[x+1][y]=valdist[x][y]+1;
                            down(x+1,y);
                            right(x+1,y);
                            left(x+1,y);
              }
          else if(valdist[x][y]+1>=valdist[x+1][y])
                                         return;
          else
          {
              valdist[x+1][y]=valdist[x][y]+1;
              down(x+1,y);
              right(x+1,y);
              left(x+1,y);
              }
else
return;
}

void initial(int x, int y)
{
            up(x,y);
            valdist[x][y]=0;
            down(x,y);
            valdist[x][y]=0;
            right(x,y);
            valdist[x][y]=0;
            left(x,y);
            valdist[x][y]=0;
}

void getmaze()
{
     int i,j;
     ifstream fin;
     ifstream fsc;
     fin.open("snake.txt");
     fsc.open("snake_high_score.txt");
     fin>>w;
     fin>>h;
     fsc>>highscore;
     fsc>>playername;
     char empty[101];
     fin.getline(empty,w+1);
     for(i=0;i<h;i++)
     fin.getline(s[i],w+1);
     fin.close();
     fsc.close();
    for(i=0;i<h;i++)
    for(j=0;j<w;j++)
    {
                    if(s[i][j]=='X')
                    {
                                    val[i][j]=-1;
                                    valdist[i][j]=-1;
                    }
                    if(s[i][j]=='.')
                    {
                                    val[i][j]=0;
                                    valdist[i][j]=0;
                                    countdot++;
                                    dot[countdot][1]=i;
                                    dot[countdot][2]=j;
                    }
                    if(s[i][j]=='S')
                    {
                                    val[i][j]=0;
                                    valdist[i][j]=0;
                                    xstart=i;
                                    ystart=j;
                    }
    }
    for(i=0;i<h+1;i++)
    cout<<s[i]<<endl;
}

void foodcord()       ///generates food's point, used by bringfood
{
int rnum,i,j,dist,l,m,n,k;
srand (changernum*time(NULL));
rnum=rand()%useddot+1;
i=dot[rnum][1];
j=dot[rnum][2];
changernum*=70;
if(changernum>1000000)
    changernum=2;

    if(playercord[1]!=i || playercord[2]!=j)
    {
        if(val[i][j]==-2)
        {
            foodcord();
            return;
        }
    initial(i,j);
    dist=valdist[playercord[1]][playercord[2]];
    for(l=0;l<h;l++)
    for(m=0;m<w;m++)
    if(valdist[l][m]!=-1)
    valdist[l][m]=0;
    if(dist>10)
    {
        foodcordxy[playerlength+1][1]=i;
        foodcordxy[playerlength+1][2]=j;
        return;
    }
    else
    {
        foodcord();
        return;
    }
    }
    else
    {
        foodcord();
        return;
    }
}

void bringfood()
{
int i,j;
foodcord();
i=foodcordxy[playerlength+1][1];
j=foodcordxy[playerlength+1][2];
s[i][j]='@';
}

void moveplayer(char c)
{
    int flag,xprev,yprev,xpos,ypos,i,temp[100];
    flag=0;
    xprev=playercord[1];
    yprev=playercord[2];
    xpos=playercord[1];
    ypos=playercord[2];
    if(c==75)
    {
        ypos=ypos-1;
        if(ypos<0)
        {
            ypos=w-1;
            if((val[xpos][ypos]!=0))
            {
                score=-1;
                ypos=yprev;
            }
        }
        else if((val[xpos][ypos]!=0))
            score=-1;
        else
            flag=1;
    }
    if(c==77)
    {
        ypos=ypos+1;
        if(ypos>=w)
        {
            ypos=0;
            if(val[xpos][ypos]!=0)
            {
                score=-1;
                ypos=yprev;
            }
        }
        else if(val[xpos][ypos]!=0)
            score=-1;
        else
            flag=1;
    }
    if(c==72)
    {
        xpos=xpos-1;
        if(xpos<0)
        {
            xpos=h-1;
            if(val[xpos][ypos]!=0)
            {
                score=-1;
                xpos=xprev;
            }
        }
        else if(val[xpos][ypos]!=0)
            score=-1;
        else
            flag=1;
    }
    if(c==80)
    {
        xpos=xpos+1;
        if(xpos>=h)
        {
            xpos=0;
            if(val[xpos][ypos]!=0)
            {
                score=-1;
                xpos=xprev;
            }
        }
        else if(val[xpos][ypos]!=0)
            score=-1;
        else
            flag=1;
    }
    s[xpos][ypos]='o';
    playercord[1]=xpos;
    playercord[2]=ypos;

        if(playerlength==0)
        {
            s[xprev][yprev]='.';
            val[xprev][yprev]=0;
        }
        else
        {
        s[foodcordxy[playerlength][1]][foodcordxy[playerlength][2]]='.';
        val[foodcordxy[playerlength][1]][foodcordxy[playerlength][2]]=0;
        }

        for(i=playerlength;i>=2;i--)
        {
            foodcordxy[i][1]=foodcordxy[i-1][1];
            foodcordxy[i][2]=foodcordxy[i-1][2];
            s[foodcordxy[i][1]][foodcordxy[i][2]]='O';
            val[foodcordxy[i][1]][foodcordxy[i][2]]=-2;
        }
        if(playerlength>0)
        {
        foodcordxy[1][1]=xprev;
        foodcordxy[1][2]=yprev;
        s[foodcordxy[1][1]][foodcordxy[1][2]]='O';
        val[foodcordxy[1][1]][foodcordxy[1][2]]=-2;
        }
}

int main()
{
system("mode 650");
RESTART:
score=0;
playerlength=0;
countdot=0;
int i,j,xpos,ypos,xprev,yprev,flag,count=1,tough;
char c='z',a='z',tempchar;
getmaze();
useddot=countdot;
cout<<"\nObjective: Feed snake '@' and snake will start from 'S' \n\nAvoid collision with itself and 'X'\n\nDirection control by arrow keys\n\n";

while(a!='s' && a!='m' && a!='f')
{
cout<<"Press speed of snake ('s'-slow,'m'-moderate,'f'-fast): ";
while(a!='s' && a!='m' && a!='f')
a=_getch();
cout<<a;
}

switch(a)
{
case 's':
    tough=10000;
    break;
case 'm':
    tough=8000;
    break;
case 'f':
    tough=3000;
    break;
}

cout<<"\nTo play press any direction key";
while(c!=72 && c!=75 && c!=77 && c!=80)
c=_getch();
system("cls");
s[xstart][ystart]='o';
playercord[1]=xstart;
playercord[2]=ystart;
bringfood();

for(i=0;i<h+1;i++)
        cout<<s[i]<<endl;

while(score==0)
{
    if(playercord[1]==foodcordxy[playerlength+1][1] && playercord[2]==foodcordxy[playerlength+1][2])
    {
        playerlength++;
        bringfood();
        system("cls");
    for(i=0;i<h+1;i++)
        cout<<s[i]<<endl;
    }

      if(kbhit())
    {
        getch();
        c=getch();
    }

if(count%tough==0)
 {
    if(c==72 || c==75 || c==77 || c==80)
    moveplayer(c);///move one step if c not equal to NULL
    if(score!=-1)
    {
        system("cls");
        for(i=0;i<h+1;i++)
            cout<<s[i]<<endl;
    }
    count=2;
 }
    count++;
}
if(score==-1)
{
    cout<<"\aSnake is dead!\n\nYour score: "<<playerlength<<"\n\nPrevious high score "<<highscore<<" by "<<playername;
    if(playerlength>highscore)
    {
        cout<<"\nEnter your name: ";
        cin.getline(playername,20);
        ofstream fsc("snake_high_score.txt");
        fsc<<playerlength;
        fsc<<playername;
        fsc.close();
    }
}

cout<<"\n\nTo play again press 'r', to quit press 'q', press 'c' for credit";
AGAIN:
while(c!='r' && c!='q' && c!='c')
c=_getch();
if(c=='r')
{
    system("cls");
    goto RESTART;
}
if(c=='c')
{
    system("cls");
    cout<<"\n\nDeveloped by Ullas\n\n\n";
    cout<<"\nTo play again press 'r', to quit press 'q'";
    c='z';
    goto AGAIN;
}
}
