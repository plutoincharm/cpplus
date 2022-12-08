//#include"headerfile.h"
//#include"variables.h"
//#include"class.h"
//#include"mouse.h"
#include<iostream.h>
#include<string.h>
#include<iomanip.h>
#include<graphics.h>
#include<math.h>
#include<time.h>
#include<bios.h>
#include<fstream.h>
#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<process.h>
#include<stdlib.h>
int	g=7,l1=2,c=0,c2=0,tracecount=0;
int	mine=0,s1=0,m=0;
int	r[8][5];
int screen_counter=0;
int turn=1,tcount=0,mk=0,ele=0,element_row=0,element_column=0,moves=1,user_array[6][6],pos[6][6],hg=0,sec=1,seven=1;
int user_controler =0;
float time_count;
int solved_array[6][6],b[3],secret[6][8],sub_array[3],drop_7_mode=1,number[6],half_solved_array[3];
int s=0,l=0,sc=0,drop_7_array[7][7];
int sudoku_screen_changer=1,drop_7_screen_show=1,sde=0;
int menupage=0;
class graphics
{
     public:
	     void disc(int p, int x, int y ,int num =0);
	     void disp(int m[7][7]);
	     void box(int a);
	     void box_drop();
	     void mainpage();
	     void selection(int a);
	     void bk();
	     void bk_drop();
	     void mainpage_drop();
	     void selection_drop();
	     void dispcontent(int m[6][6]);
};
class sudoku:public graphics
{
	public:
		sudoku()              // constructor
		{
			for(int i=0;i<6;i++)
			{
				for(int j=0;j<6;j++)
				{
					 user_array[i][j]=0;
				}
			}
		}
		~sudoku()        //destructor
		{
			for(int i=0;i<6;i++)
			{
				for(int j=0;j<6;j++)
				{
					 solved_array[i][j]=0;

				}
			}
		}
		void start();
		void solve();
		void interchange();
		void startup();
		void option();
		int  check();
		//int input();
		void usercontrol(int m);
		void selective_assign();

};
class drop_7  :public graphics
{
  public:
		drop_7()                //constructor
		{
			for(int i=0;i<7;i++)
			{
				for(int j=0;j<7;j++)
				{
					 drop_7_array[i][j]=0;

				}
			}
		}
		~drop_7()         //   destructor
		{
			for(int i=0;i<7;i++)
			{
				for(int j=0;j<7;j++)
				{
					 drop_7_array[i][j]=0;

				}
			}
		}
		int generate(int m, int n, int p=0);
		void startup();
		void count(int m ,int n);
		void secret_check(int m, int n,int  a[4]);// make it reference
		int gameover();
		void drop(int m, int n);
		void push_down();
		void option_drop();
		void rules_drop();
		void start();
		void controls_drop();
		//void zero(int m[7][7]);
		void push_down(int m, int n);
};
class Trace_2048 :public graphics
{
   public:    void disp(int a[4][4]);
	      int ins(int a[4][4]);
	      int up(int a[4][4]);
	      int down(int a[4][4]);
	      int left(int a[4][4]);
	      int right(int a[4][4]);
	      void control(int a[4][4]);
	      int option(int a[4][4]);
	      int source(int m[4][4]);
	      void initial(int a[4][4]);
	      void initialx(int a[4][4]);
	      void start_2048(int a[4][4]);
	      void create();
	      void disp(int a[8][5]);
	      void disp1(int a[8][5]);
	      int source(int a[8][5]);
	      int ins(int a[8][5]);
	      void initialp(int a[8][5]);
	      int trace();
	      int gameover();
};

class game : public sudoku,public drop_7,public Trace_2048
{
	public: void end_game();
		void start_game();

}game;
void game::end_game()
{
	cleardevice();
	for(int i=0,j=1;j<=15;i++,j++)
	{
		sound(222.5+i*20);
		setbkcolor(j);
		delay(100)  ;
	}
	nosound();
	sound(261.114);
	setbkcolor(15);
	setcolor(12);
	settextstyle(6,0,6);
	outtextxy(190,210,"Thanks For Playing");
	nosound();
	delay(1000);
	exit(0);
}
void pointer_based_intialisation(int a)
{
	switch(a)
	{
	   case 1:
		  {
			sudoku *p;
			break;
		  }
	     case 2:
		{
			drop_7 *p;
			break;
		}
	     case 3:
		{
			Trace_2048 *p;
			break;
		}
	     default: break;


	}
}
int cx=0,cy=0,q=0;
class mouse
{
	REGS regs;
	int no_buttons;
	public:	void show_mouse();
		void get_status();
		void hide_mouse();
		mouse()
		{
			regs.x.ax=0;
			int86(0x33,&regs,&regs);
			if(regs.x.cx==0xfff)no_buttons=regs.x.bx;
		}
}ob;
void mouse::hide_mouse()
{
		regs.x.ax=0x02;
		int86(0x33,&regs,&regs);
}
void mouse::get_status()
{

	q=0;
	regs.x.ax=0x03;
	int86(0x33,&regs,&regs);
	while(q!=1)
	{
		regs.x.ax=0x03;
		int86(0x33,&regs,&regs);
		q=regs.x.bx;
		cx=regs.x.cx;
		cy=regs.x.dx;
	}
}
void mouse::show_mouse()
{
	regs.x.ax=0x01;
	int86(0x33,&regs,&regs);

}

void sudoku::interchange()
{
	for(int i=0;i<=5;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(i%2==0)
			{
				solved_array[i+1][j+3]=solved_array[i][j];
			}
			else if(i%2!=0)
			{
				solved_array[i-1][j+3]=solved_array[i][j];
			}
		}
	}
}
void sudoku::solve()
{

       int p,r,q,t,ct,flag=0;
       randomize();
       p=random(6)+1;
       do
       {
	    q=random(6)+1;

       }while(q==p);
       do
       {
		r=random(6)+1;

       }while((r==p)||(r==q));
       b[0]=p;solved_array[0][0]=p;
       b[1]=q;solved_array[0][1]=q;
       b[2]=r;solved_array[0][2]=r;
       solved_array[2][0]=q;
       for(int f=0,g=1;f<6;f++,g++)
       {
		number[f]=g;
       }
       for(int h=0;h<6;h++)
       {
		if((number[h]==b[0])||(number[h]==b[1])||(number[h]==b[2]))	  //similar in num to be made  zero
		{
			number[h]=0;
		}
       }
       int z=0;
       for(h=0;h<6;h++)
       {
		if(number[h]!=0)
		{
			sub_array[z]=number[h];
			z++;
		}
       }
       for( g=0;g<3;g++)
       {
		solved_array[1][g]=sub_array[g];
       }
       for(int count=0;count<=1;count++)
       {
		if(count==1)
		{
			for(int z=0;z<3;z++)
			{
				half_solved_array[z]=sub_array[z];
			}
		}
		else
		{
			for(int z=0;z<3;z++)
			{
				half_solved_array[z]=b[z];
			}
		}
		for(int j=0;j<=2;j++)
		{
			for(int i=2;((i<6)&&(count==0));i+=2)
			{
				if((i==2)&&(j==0))
				{
					do
					{
						//	randomize();

						t=random(3);
					}while((half_solved_array[t]==solved_array[i-2][j]));
					solved_array[i][j]=half_solved_array[t];
					i+=2;
				}
				if(i==4)
				{
					ct=1;
					for(int p=0;((p<3)&&(ct==1));p++)
					{
						if((j==0)&&(half_solved_array[p]!=solved_array[0][j])&&(half_solved_array[p]!=solved_array[2][j]))
						{
							solved_array[i][j]=half_solved_array[p]; ct=0;
						}
						else if((j==1)&&(half_solved_array[p]!=solved_array[i][j-1])&&(half_solved_array[p]!=solved_array[2][j])&&(half_solved_array[p]!=solved_array[0][j]))
						{
							solved_array[i][j]=half_solved_array[p];   ct=0;
						}
						else if((j==2)&&(half_solved_array[p]!=solved_array[i][j-1])&&(half_solved_array[p]!=solved_array[i][j-2]))
						{
							solved_array[i][2]=half_solved_array[p];    ct=0;
						}
					}
				}
				if((i==2)&&(j>0))
				{
					flag=0;
					for(int n=j-1;((n>=0)&&(flag==0));n--)
					{
						// flag=0;
						for(int p=0;p<3;p++)
						{
							if((j==1)&&(b[p]!=solved_array[i][n])&&(b[p]!=solved_array[0][j]))
							{
								solved_array[i][j]=half_solved_array[p];
								flag=1;
							}
							else if((j==2)&&(half_solved_array[p]!=solved_array[i][n])&&(half_solved_array[p]!=solved_array[i][n-1]))
							{
								solved_array[i][j]=half_solved_array[p];
								flag=1;
							}
						}

					}
				}
			}

			for( i=3;((i<6)&&(count==1));i+=2)
			{
				if((i==3)&&(j==0))
				{
					do
					{
						//	randomize();
						t=random(3);
					}while((half_solved_array[t]==solved_array[i-2][j]));
					solved_array[i][j]=half_solved_array[t];
					i+=2;
				}
				if(i==5)     //no else if please
				{
					ct=1;
					for(int p=0;((p<3)&&(ct==1));p++)
					{
						if((j==0)&&(half_solved_array[p]!=solved_array[1][j])&&(half_solved_array[p]!=solved_array[3][j]))
						{
							solved_array[i][j]=half_solved_array[p]; ct=0;
						}
						else if((j==1)&&(half_solved_array[p]!=solved_array[i][j-1])&&(half_solved_array[p]!=solved_array[3][j])&&(half_solved_array[p]!=solved_array[1][j]))
						{
							solved_array[i][j]=half_solved_array[p];   ct=0;
						}
						else if((j==2)&&(half_solved_array[p]!=solved_array[i][j-1])&&(half_solved_array[p]!=solved_array[i][j-2]))
						{
							solved_array[i][2]=half_solved_array[p];    ct=0;
						}
					}
				}
				if((i==3)&&(j>0))
				{
					flag=0;
					for(int n=j-1;((n>=0)&&(flag==0));n--)
					{
						// flag=0;
						for(int p=0;p<3;p++)
						{
							if((j==1)&&(half_solved_array[p]!=solved_array[i][n])&&(half_solved_array[p]!=solved_array[1][j]))
							{
								solved_array[i][j]=half_solved_array[p];
								flag=1;
							}
							else if((j==2)&&(half_solved_array[p]!=solved_array[i][n])&&(half_solved_array[p]!=solved_array[i][n-1]))
							{
								solved_array[i][j]=half_solved_array[p];
								flag=1;
							}
						 }
					}
				}
			}
		}
       }
}
void graphics::bk()
{
	 setbkcolor(4);
	 setcolor(6);

	 int i=0;
	 for(int g=0;g<=639;g+=100,i++)
	 {
		sound(222.5+i*20);
		line(g,0,(g+139),479);
		delay(300);
	 }
	 for(g=639; g>=0;g-=100,i++)
	 {
		sound(222.5+i*20);
		line(0,g,g,0);
		delay(300);
	 }
	 g=250;
	 for(int h=90;g<=639;g+=100,h+=100,i++)
	 {
		 sound(222.5+i*20);
		 line(g,479,639,h);
		 delay(300);
	 }
	 nosound();
	 settextstyle(10,0,5);
	 setcolor(14);
	 outtextxy(180,190,"SUDOKU");
	 delay(2000);
}
void graphics::mainpage()
{
	 cleardevice();
	 if(sudoku_screen_changer==1)
	 {
	   // cleardevice();
	    setbkcolor(4);
	    settextstyle(10,0,4);
	    setcolor(14);
	    outtextxy(220,3,"SUDOKU");
	    delay(500);
	    settextstyle(10,0,1);
	    outtextxy(150,192,"*");
	    outtextxy(200,195,"New Game");
	    outtextxy(150,247,"*");
	    outtextxy(200,250,"Exit");
	    delay(1000);
	 }
	 else if(sudoku_screen_changer==2)
	 {
	      //	cleardevice();
	    setbkcolor(4);
	    settextstyle(10,0,4);
	    setcolor(14);
	    outtextxy(220,3,"SUDOKU");
	    delay(500);
	    settextstyle(10,0,1);
	    outtextxy(150,172,"*");
	    outtextxy(200,175,"Continue");
	    outtextxy(150,222,"*");
	    outtextxy(200,225,"Solution");
	    outtextxy(150,272,"*");
	    outtextxy(200,275,"New Game");
	    delay(400);
	    outtextxy(150,323,"*");
	    outtextxy(200,325,"Exit");
	    delay(1000);
	  }


}
void graphics::box(int a)
{
	char s[20];
	if(a==1)
	{
	    cleardevice();
	    settextstyle(10,0,4);
	    setcolor(14);
	    outtextxy(210,3,"SUDOKU");
	    setbkcolor(4)  ;
	    setcolor(2);
	    rectangle(150,90,456,396);
	    floodfill(160,100,2);
	    for(int i=201;i<=456;i=i+51)
	    {
		line(i,90,i,396);
	    }
	    for(int j=141;j<=396;j=j+51)
	    {
		line(150,j,456,j);
	    }
	    delay(1000);
	}
	else if(a==2)
	{
		cleardevice();
		settextstyle(10,0,4);
		setcolor(14);
		outtextxy(210,3,"SUDOKU");
		setbkcolor(4);
		setcolor(2);
		int ct=1,cd=1;
	  for(int i=201;i<=456;i=i+51)
	  {
		if((ct==1)||(ct==2)||(ct==5)||(ct==4))
		{
		  line(i,90,i,396);
		}
		ct++;
	  }
	  for(int j=141;j<=396;j=j+51)
	  {
		if((cd==1)||(cd==3)||(cd==5))line(150,j,456,j);
		cd++;
	  }
	  ct=cd=1;
	  for(i=201;i<=456;i=i+51)
	  {
		   if((ct==3))
		   {
			setlinestyle(SOLID_LINE,2,3);
			line(i,90,i,396);
		   }
		   ct++;
	  }
	  for(j=141;j<=396;j=j+51)
	  {
		if((cd==2)||(cd==4))
		{
			setlinestyle(SOLID_LINE,2,3);
			line(150,j,456,j);

		}
		cd++;
	  }
	  setlinestyle(SOLID_LINE,2,3);
	  rectangle(150,90,456,396);
	  setlinestyle(SOLID_LINE,1,1);
       }
}
void graphics::selection(int a)
{
		setcolor(14);
		settextstyle(8,0,3);
		outtextxy(490,237,"*");
		outtextxy(510,240,"Check");
		outtextxy(490,297,"*");
		outtextxy(510,300,"Back");

}
inline int mouseloop(int x1,int x2,int y1,int y2)//put end point in screen)
{
		int flag=0 ;
	    if((cx>=x1)&&(cx<=x2)&&(cy>=y1)&&(cy<=y2))
	    {
	       return 1;
	    }
	    else return 3;
}
void sudoku::selective_assign()
{
	     int p;
	     p=random(2)+1;
	     if(p==1)
	     {
	       pos[0][0]= user_array[0][0]=solved_array[0][0];
	       pos[1][0]=user_array[1][0]=solved_array[1][0];
	       pos[1][3]=user_array[1][3]=solved_array[1][3];
	       pos[1][4]=user_array[1][4]=solved_array[1][4];
	       pos[2][3]=user_array[2][3]=solved_array[2][3];
	       pos[3][0]=  user_array[3][0]=solved_array[3][0];
	       pos[3][1]= user_array[3][1]=solved_array[3][1];
	       pos[3][3]=	user_array[3][3]=solved_array[3][3];
	       pos[4][5]=user_array[4][5]=solved_array[4][5];
	       pos[5][1]= user_array[5][1]=solved_array[5][1];
	       pos[5][5]= user_array[5][5]=solved_array[5][5];
	     }
	     else if(p==2)
	     {
		   pos[0][0]=user_array[0][0]=solved_array[0][0];
		   pos[1][0]=user_array[1][0]=solved_array[1][0];
		   pos[0][1]= user_array[0][1]=solved_array[0][1];
		   pos[0][5]=  user_array[0][5]=solved_array[0][5];
		   pos[1][3]=  user_array[1][3]=solved_array[1][3];
		   pos[2][3]=user_array[2][3]=solved_array[2][3];
		   pos[2][2]=  user_array[2][2]=solved_array[2][2];
		   pos[3][5]=   user_array[3][5]=solved_array[3][5];
		   pos[5][3]=   user_array[5][3]=solved_array[5][3];
		   pos[4][0]=user_array[4][0]=solved_array[4][0];
		   pos[4][1]=user_array[4][1]=solved_array[4][1];
		   pos[4][5]=user_array[4][5]=solved_array[4][5];
		}


}


void graphics::dispcontent(int m[6][6])
{
	  char s[20];
	  int flag=0;
	  for(int y=90,i=0;y<396&&flag==0;y+=51)
	  {
	       for(int x=150,j=0;x<456&&flag==0;x+=51)
	       {
		    if(m[i][j]!=0)
		    {                             //change flickering
		       setcolor(14);
		       itoa(m[i][j],s,10);
		       setfillstyle(1,4);
		       floodfill(x+6,y+6,2);
		       settextstyle(6,0,1);
		       outtextxy(x+19,y+15,s);

		      //	flag=1;
		    }
		    j++;
		}
		i++;

	  }
}
void sudoku::usercontrol(int m)
{
       int ret=0;
       user_controler=0;
      char s[20];

    if(m!=1)
    {

      cleardevice();

	     if(m==2)     //check
	     {

		cleardevice();
		game.sudoku::box(1);
		game.sudoku::dispcontent(user_array);

		int i=0;
		for(int y=90;y<396;y+=51)
		{
			for(int x=150,j=0;x<456;x+=51)
			{
				if((solved_array[i][j]!=user_array[i][j])||(user_array[i][j]==0))  // to color empyt spaces
				{

					setfillstyle(1,13);
					floodfill(x+6,y+6,2);//x+50,y+50)
					if(user_array[i][j]!=0)
					{
						setfillstyle(1,5);
						floodfill(x+6,y+6,2);
						setcolor(15);
						itoa(user_array[i][j],s,10);
						settextstyle(6,0,1);
						outtextxy(x+19,y+15,s);
						//	ob.show_mouse();
					}
				}
				j++;
			}
			i++;
		}
		user_controler=1;
		ret =1;
		setcolor(15);
		settextstyle(2,0,8);
		outtextxy(30,440,"Press Esc To Go Back");
		sound(2000);
		delay(30);
		nosound();
		//  delay(200);
	}
	else if(m==3)//solution
	{
			cleardevice();
			setbkcolor(4);
			mk=1;
			game.sudoku::box(1);
			game.sudoku::dispcontent(solved_array);
			setcolor(1);
			settextstyle(2,0,8);
			outtextxy(30,440,"Press Esc To Go Back");
			ret =1;
			user_controler=1;
		}while(bioskey(0)!=283);
		sound(2000);
		delay(30);
		nosound();
	}
}
int sudoku::check()
{
	int comp=36,flag=1;
	for(int i=0;i<6;i++)
	   for(int j=0;j<6;j++)
		 if(solved_array[i][j]!=user_array[i][j])
		 {
			flag=0;
			comp--;
		 }
		 if(flag==1)
		 {
			sudoku_screen_changer=1;
			cleardevice();
			setbkcolor(15);
			setcolor(12);
			settextstyle(5,0,3);
			delay(1000);
			outtextxy(350,250,"Sudoku Solved Successfully");
			delay(200);
			for(int i=0;i<7;i++)
			{
				for(int j=0;j<7;j++)
				{
					solved_array[i][j]=0;
				}
			}
			cleardevice();
			pointer_based_intialisation(1);
			sudoku_screen_changer=1;
		}
		return comp;

}
void sudoku::start()
{

	int 	m=0,flag=0,ret=0,opt,ct=0;
	char 	s[50];
		sudoku_screen_changer =2;
		int repeat=0;
		int comp=0;


			do
			{
				hg=comp+moves/100;
				if(repeat==0)
				{
					game.sudoku::box(2);
					game.sudoku::selection(1);
				  //	if(user_controler==1)
				  game.sudoku::dispcontent(user_array);
				}
				ob.show_mouse();
				ob.get_status();
				if(mouseloop(150,450,90,396)==1)           //divide conditions towards sudoku
				{
						int 	val=0; char d;
						ob.hide_mouse();
						gotoxy(2,2);
						d=getch();
						sound(3000);
						delay(50);
						nosound();
						setcolor(4);
						rectangle(0,0,15,400);
						setfillstyle(1,4);
						floodfill(7,20,4);
						val=int(d);
						val=val-48;
						while((val<1)||(val>6))
						{

						      setcolor(15);
							settextstyle(2,0,8);
							outtextxy(70,415,"Only 1 To 6 Allowed");
							{
								delay(100);
								val=0;



						    d=getch();
						    sound(3000);
						    delay(50);
						    nosound();
						     val=int(d);
						    val=val-48;
						    setcolor(4);
						    rectangle(20,400,600,600);
						    setfillstyle(0,4);
						    floodfill(40,420,4);
						 }

						 }

						 flag=0;repeat=1;
						 for(int y=90,i=0;y<396&&flag==0;y+=51,i++)    //check it
						 {
							   //	i++;
							for(int x=150,j=0;x<456&&flag==0;x+=51,j++)
							{
								if(mouseloop(x,x+51,y,y+51)==1)//input
								{

									if((pos[i][j]==0))
									{
									user_array[i][j]=val;
									moves++;
									if(user_array[i][j]!=0)
									 {
									   flag=1;

									//	ob.show_mouse();
									  setfillstyle(0,4);
									 floodfill(x+19,y+15,2);
								       itoa(user_array[i][j],s,10);
								      settextstyle(6,0,1);
								      setcolor(14);
								      outtextxy(x+19,y+15,s);
									  }
								      }
							else if(pos[i][j]!=0)     ;
						 }
						 //	 j++;
					 }
					  // i++;
				}
					ob.show_mouse();
					ob.get_status();
			}
			else if(mouseloop(480,590,180,350)==1)      //center line ordinatrs
			{
				if(mouseloop(510,560,190,210)==1)   //hint
				{
					sound(2000);
					m =1;
					ob.hide_mouse();
					delay(30);
					nosound();
					game.sudoku::usercontrol(m);
					repeat=0;
				}
				else if(mouseloop(510,580,250,270)==1)  //check         //check it
				{      sound(2000);
					m=2;
					ob.hide_mouse();  delay(30);
						nosound();
				       game.sudoku::usercontrol(m);
				       repeat=0;
				}
			       else if(mouseloop(510,570,310,330)==1)  //back
			       {
					     //	return startup();
				     m=6;   ct=1;
				     sound(2000);
				     ob.hide_mouse();
				     delay(30);
				     nosound();
				     ret =1;
				     repeat=0;
				}
			}
		}while((ct==0)&&(game.sudoku::check()));

}
void sudoku::startup()
{      int ct =0,flag=0,opt=6,ret=6;

	       game.sudoku::bk();
	       flag=0;  ct=0;
	       cleardevice();
	       int p=0;
		ret=0;

	   do
	   {

		     if(p==0)game.sudoku::mainpage();
		     p=0;
		     ct=0;
		    ob.show_mouse();
		    ob.get_status();
		    delay(100);
		    if(sudoku_screen_changer==1)
		    {
			if(mouseloop(200,359,205,232)==1) //new game
			{
				sound(2000);
				ob.hide_mouse();
				delay(30);
				nosound();
				cleardevice();
				setbkcolor(4);
				setcolor(14);
				delay(300);
				outtextxy(200,200,"Please Wait !");
				delay(1000);
				pointer_based_intialisation(1);
				game.sudoku::solve();
				game.sudoku::interchange();
				game.sudoku::selective_assign();
				start();

			  }
			   else if(mouseloop(200,260,260,287)==1)       //exit
			   {
				sound(2000);
				ob.hide_mouse();
				delay(30);
				nosound();
				ct=1;
				ret=1;

			   }
			    else p=1;
		 }
		 else if(sudoku_screen_changer==2)
		 {

			   if((mouseloop(200,317,189,214)==1)&&(sudoku_screen_changer==2))//continue
			   {
				sound(2000);
				ob.hide_mouse();
				delay(30);
				nosound();
				time_count =0;
				game.sudoku::start();

			   }
			   else if((mouseloop(200,310,239,263)==1)&&(sudoku_screen_changer==2))//solution
			   {
				sound(2000);
				ob.hide_mouse();
				delay(30);
				nosound();
				game.sudoku::usercontrol(3);
			   }
			   else if(mouseloop(200,345,289,313)==1) //new game
			   {
				sound(2000);
				ob.hide_mouse();
				delay(30);
				nosound();
				setbkcolor(4);
				setcolor(14);
				cleardevice();
				delay(300);
				sound(2000);
				outtextxy(180,190,"Please Wait");
				delay(100);
				nosound();
				delay(1000);
				pointer_based_intialisation(1);
				game.sudoku::solve();
				game.sudoku::interchange();
				game.sudoku::selective_assign();
				game.sudoku::start();
				flag=1;
			   }
			   else if(mouseloop(200,250,340,365)==1)       //exit
			   {
				sound(2000);
				ob.hide_mouse();
				ct=1;
				delay(30);
				nosound();
				ret=1;
			   }
			   else p=2;
		 }
	 }while(ret!=1);
}
				    //drop 7
//____________________________________________________________________________________________________________________________________________
int drop_7:: gameover()
{
	 int	p=0;
	 char s[50];
	 for(int i=0;i<7;i++)
	 {
	     if(drop_7_array[0][i]==0)
	     {
		p=1;
	     }
	 }

	 if(p==0)
	 {
		cleardevice();
		setbkcolor(2);
		itoa(sc,s,10);
		setcolor(14);
		settextstyle(6,0,5);
		outtextxy(190,200,"Your Score : ");
		setcolor(14);
		outtextxy(405,195,s);
		drop_7_screen_show=1;
		delay(3000);
		cleardevice();
		setbkcolor(15);
		setcolor(12);
		settextstyle(5,0,5);
		outtextxy(350,250,"Game Over");
		delay(1000);
		setbkcolor(15);
		int x=getmaxx()/2;
		int y=getmaxy()/2;
		float j=116.6225;
		for(int i=30;i<200;i++)
		{
			sound(j);
			delay(100);
			setcolor(i/10);
			arc(x,y,0,180,i-10);
			nosound();
			j+=15.5601;
		}
		delay(1000);
		sound(261.114);
		delay(100);
		nosound();
		cleardevice();
		setcolor(12);
		settextstyle(5,0,3);
		delay(1000);
		outtextxy(350,250,"Thanks For Playing");
		pointer_based_intialisation(2);
		// game.game.drop_7::zero(drop_7_array);
		drop_7_screen_show=1;
		sc=0;
		settextstyle(6,0,3);
		outtextxy(100,400," Press ESC to go back");
		delay(1000);
		while(bioskey(0)!=283);
		sc=0;
		return 1;
	  }
	  return 0;
}
void  drop_7::push_down(int m ,int n)
{
     int p,ct;
	for(int i=6;i>=0;i--)
	{
		p=0;
		if(drop_7_array[i][n]==0)
		{

			for(ct=i;drop_7_array[ct][n]==0&&ct>=0;ct--)
			{
				p=1;
				if(ct==0)
				p=0;
			}
		}
		if(p==1)
		{
			drop_7_array[i][n]=drop_7_array[ct][n];
			drop_7_array[ct][n]=0;
		}
	}
}
void drop_7::count(int m,int n)
{
  int ct=0;

  if((drop_7_array[m][n]!=20)&&(drop_7_array[m][n]!=10))
  {
    int r=m;            //along column
	int t,v=0,tp=0;
	r=0;
	tp=7-r;
	tp--;
	while(tp>=1)
	{
		t=tp-1;
		v=0;
		while(t>=1)
		{

			if((drop_7_array[7-t][n]==drop_7_array[7-tp][n]||v==drop_7_array[7-t][n])&&(drop_7_array[7-t][n]!=0)&&(drop_7_array[7-tp][n]!=drop_7_array[m][n])&&(t!=tp)&&(drop_7_array[7-t][n]!=10)&&(drop_7_array[7-t][n]!=20))
			{

			       v=drop_7_array[7-t][n];
			       sound(1000);
			       drop_7_array[7-tp][n]=drop_7_array[7-t][n]=0;
				//sc+=5;
			       if(ct==0)
			       {
				ct++;
			       }
			       nosound();
			       push_down(m,n);
			}
			t--;
		}
		tp--;
	}
	ct=0;
	for(int p =0;p<7;p++)
	{                            //along row
	   for(int i=0;i<7;i++)
	   {
			if((i!=p)&&(drop_7_array[m][n]!=drop_7_array[m][p])&&(drop_7_array[m][p]!=20)&&(drop_7_array[m][p]!=10))
			{
			    if(drop_7_array[m][p]==drop_7_array[m][i])
			    {
			       sound(1000);
			       drop_7_array[m][p]=drop_7_array[m][i]=0;
			       nosound();
			       game.drop_7::push_down(m,p);
			       game.drop_7::push_down(m,i);
			       if(ct==0)
			       {
				ct++;
			       }
					//sc+=5;
			    }
			}
		}
	 }
     }


}
void drop_7:: secret_check(int m, int n,int a[4])//int & solved_array[4])
{

	 int r,s,p,o;
	 s=r=o=n=0;
	if(drop_7_array[m][n-1]==20)
	{
		sound(3000);
		delay(50);
		drop_7_array[m][n-1]=10;
		nosound();
	}
	else if(drop_7_array[m][n-1]==10)
	{
		sound(3000);
		delay(50);
		int p;
		p = random(7)+1;
		//sc+=2;
		sc+=2;
		drop_7_array[m][n-1]=p;
		nosound();
		p= 2;
		//drop(m,n-1);
	}
	if(drop_7_array[m][n+1]==20)
	{
		sound(3000);
		delay(50);
		drop_7_array[m][n+1]=10;
		nosound();
	}
	else if(drop_7_array[m][n+1]==10)
	{
		sound(3000);
		delay(50);
		int p;
		p = random(7)+1;
		sc+=2;
		//sc+=2;
		drop_7_array[m][n+1]=p;
		nosound();
		r= 3;
	}
	if(drop_7_array[m+1][n]==20)
	{
		sound(3000);
		delay(50);
		drop_7_array[m+1][n]=10;
		nosound();
	}
	else if(drop_7_array[m+1][n]==10)
	{
		sound(3000);
		delay(50);
		int p;
		p = random(7)+1;
		sc+=2;
		drop_7_array[m+1][n]=p;
		nosound();
		s= 4;

	}
	if(drop_7_array[m-1][n]==20)
	{
		sound(3000);
		delay(50);
		drop_7_array[m-1][n]=10;
		nosound();
	}
	else if(drop_7_array[m-1][n]==10)
	{
		sound(3000);
		delay(50);
		int p;
		p = random(7)+1;
		sc+=2;
		drop_7_array[m-1][n]=p;
		nosound();
		o= 1;

	}
}
void check(int m,int n)
{
	 int ch=1;
	 int c=0,secret[4]; // integer pointer
		ch=1;c=0;
		int d=0;
		for(int i=n;(i>=0)&&(ch==1);i--)
		{
			if(drop_7_array[m][i]!=0)
			{
				c++;
			}
			else if(drop_7_array[m][i]==0)ch=0;

		}
		ch=1;
		for(i=n;i<7&&ch==1;i++)
		{
			if(drop_7_array[m][i]!=0)
			{
				d++;
			}
			else if(drop_7_array[m][i]==0)
			{
				ch=0;
			}

		}

		for(int p=0;p<7;p++)
		{

			    if(drop_7_array[m][p]==c+d-1)
			    {
					drop_7_array[m][p]=0;
					 sc+=5;
					  game.drop_7::secret_check(m,p,secret);

					game.drop_7::push_down(m,p);

			    }
		}
}
void find(int m, int n )
{
       int   t= 7-m,h=9;
       int ch=1;
       int c=0,secret[4]; // integer pointer
		  check(m,n);
		  int i=0;
		  int g=6,c_times=0;
	       do
	       {
		  i=0;g=6;
		  do
		  {
			if(drop_7_array[i][n]!=0&&drop_7_array[g][n]!=0)
			{
				check(i,n);
				check(g,n);
			}
			i++;
			g--;
		  }while(i<7);
		  c_times++;
		}while(c_times!=4);
		for( i=0;i<7;i++) // to eliminate same number along a column
		{
		     if(drop_7_array[i][n]!=0)
		     {
			int ch=drop_7_array[i][n];
			for(int j=0;j<7;j++)
			{
			     if(drop_7_array[j][n]!=0&&i!=j&&drop_7_array[i][n]!=10&&drop_7_array[i][n]!=20)
			     {
			       if(drop_7_array[j][n]==drop_7_array[i][n])
			       {
					drop_7_array[i][n]=0;
					drop_7_array[j][n]=0;
					sc+=5;
					game.drop_7::secret_check(i,n,secret);
					game.drop_7::secret_check(j,n,secret);
					game.drop_7::push_down(i,n);
					game.drop_7::push_down(j,n);
			       }
			     }
			 }
		     }
		 }


	     for(int b=0;b<7;b++)
	     {
		if((t==drop_7_array[b][n])&&(drop_7_array[b][n]!=0))
		{
			sc+=5;
			drop_7_array[b][n]=0;
			game.drop_7::push_down(b,n);

			game.drop_7::secret_check(b,n,secret);
		  }
	    }
}

void drop_7::drop(int m, int n)
{


		int   t= 7-m,h=9;
		int ch=1;
	      int c=0,secret[4]; // integer pointer
		  int i=0;
		  int g=6,c_times=0;
		  find(m,n);

		if((drop_7_array[m][n]!=20)&&(drop_7_array[m][n]!=10)&&(turn==1))//&&(drop_7_array[m][n]!=1))
		{
			if(drop_7_array[m][n]==t)
			{
				drop_7_array[m][n]=0;
				sc+=10;
				game.drop_7::secret_check(m,n,secret);
				count(m,n);

			}
			ch=1;c=0;
			int d=0;
			for(int i=n;(i>=0)&&(ch==1);i--)
			{
				if(drop_7_array[m][i]!=0)
				{
					c++;
				}
				else if(drop_7_array[m][i]==0)ch=0;
			}
			ch=1;
			for(i=n;i<7&&ch==1;i++)
			{
				if(drop_7_array[m][i]!=0)
				{
					d++;
				}
				else if(drop_7_array[m][i]==0)
				{
					ch=0;
				}
			}
			if(c+d-1==drop_7_array[m][n])
			{

				drop_7_array[m][n]=0;
				sc+=10;
				game.drop_7::secret_check(m,n,secret);
			}
			count(m,n);
		     }

		     find(m,n);

}
void graphics::disc(int p ,int x,int y ,int num  )
{
	      if(sde!=0)
	      {
		 sound(2000);//sound(261);
	      }
	      setcolor(p);
	      circle(x+34,y,21);
	      setfillstyle(1,p);
	      floodfill(x+34,y,p);
	      if(sde!=0)nosound();
	      switch(num)
	      {
		case 1 :  	setcolor(0);
				settextstyle(10,0,3);
				outtextxy(x+25,y-28,"1");
				break;
		case 2 :  	setcolor(0);
				settextstyle(10,0,3);
				outtextxy(x+25,y-28,"2");
				break;

		case 3 :  	setcolor(0);
				settextstyle(10,0,3);
				outtextxy(x+25,y-28,"3");
				break;
		case 4 :  	setcolor(0);
				settextstyle(10,0,3);
				outtextxy(x+25,y-28,"4");
				break;
		case 5 :  	setcolor(0);
				settextstyle(10,0,3);
				outtextxy(x+25,y-28,"5");
				break;
		case 6 :  	setcolor(0);
				settextstyle(10,0,3);
				outtextxy(x+25,y-28,"6");
				break;

		case 7 :  	setcolor(0);
				settextstyle(10,0,3);
				outtextxy(x+25,y-28,"7");
				break;

		case 0 :       	break;

	      }
}
int drop_7::generate(int x, int y ,int p)
{

	int g=4;
	if(p==0)
	{
		game.sudoku::solve();
		game.sudoku::interchange();
		g=random(2)+1;
		// g=0;
		ag:
		if(g==2)
		{


			p= solved_array[s][l];
			if(l==6)
			{
				l=0;
			}
			else l++;
		}
		else if(g==1)
		{
			int h;
			h = random(36);
			switch(solved_array[h][0])
			{
				case 3:p=7;seven++;break;
				case 6:p=7;seven++;break;    //assigning number seven &secret
				case 2:p=20;sec++;break;
				case 4:p=20;sec++;break;
				default: p=20;sec++;break;
			}
			if(seven==4)
			{
				g=2;
				seven=0;
				goto ag;
			}
			else if(sec==4)
			{
				g=2;goto ag;
				seven=0;
			}


		}
	}
	switch(p)
	{
	   case 1 :game.drop_7::disc(14,x,y,1);break;
	  case 2 : game.drop_7::disc(13,x,y,2);break;
	  case 3 : game.drop_7::disc(12,x,y,3);break;
	  case 4 : game.drop_7::disc(11,x,y,4);break;
	  case 5 : game.drop_7::disc(10,x,y,5);break;
	  case 6 : game.drop_7::disc(6,x,y,6);break;
	  case 7 : game.drop_7::disc(15,x,y,7);break;
	  case 20 : game.drop_7::disc(8,x,y);break;
	  case 10 : game.drop_7::disc(7,x,y);break;
	  default : break;
	}
	return p;
}
void graphics::disp(int m[7][7])
{
	  char s[20];
	  int flag=0;
	    for(int x=110,i=0;x<453&&flag==0;x+=49)
	    {
		for(int y=147,j=0;y<623&&flag==0;y+=68)
		{
		     if(m[i][j]!=0)
		     {                             //change flickering

			 game.drop_7::generate(y,x+25,m[i][j]);

		     }
		      j++;
		}
		i++;

	    }
}
void drop_7::controls_drop()
{
	cleardevice();
	setbkcolor(1);
	setcolor(15);
	settextstyle(1,0,7);
	outtextxy(150,0,"CONTROLS");
	setcolor(2);
		setlinestyle(SOLID_LINE,2,3);
	rectangle(72,120,120,160);
	setfillstyle(6,2);
	floodfill(85,138,2);
	setlinestyle(SOLID_LINE,2,3);
	line(30,135,70,110);
	line(30,135,70,170);
	line(70,110,70,170);
	line(70,140,120,140);
	setfillstyle(6,2);
	floodfill(59,132,2);
	setlinestyle(SOLID_LINE,2,3);
	rectangle(60,210,110,250);
	setfillstyle(6,2);
	floodfill(74,222,2);
	line(150,230,110,200);
	line(150,230,110,260);
	line(110,200,110,260);
	line(60,230,110,230);
	setfillstyle(6,2);
	floodfill(126,230,2);
	settextstyle(2,0,5);
	rectangle(60,290,140,340);
	setcolor(4);
	settextstyle(2,0,5);
	outtextxy(80,310,"ENTER");
	settextstyle(2,0,5);
	outtextxy(200,120,"left arrow key to move the disc to the left side ");
	outtextxy(200,220,"right arrow key to move the disc to the right side ");
	outtextxy(200,320,"press enter to drop the disc");
	setbkcolor(1);
	setcolor(15);
	settextstyle(2,0,8);
	outtextxy(30,440,"Press Esc To Go Back");
	setlinestyle(SOLID_LINE,1,1);
	while(bioskey(0)!=283);
	sound(3000);
	delay(50);
	nosound();
	cleardevice();
}
void drop_7::rules_drop()
{
	setbkcolor(1);
	settextstyle(1,0,7);
	outtextxy(250,5,"RULES");
	settextstyle(2,0,5);
	outtextxy(5,80,"1.When the number on the disc becomes equal to the no of rows or columns arranged");
	outtextxy(0,100,"continously without any empty spaces the score gets added by 10 ,and the respective");
	outtextxy(0,120,"disc dissapears");
	outtextxy(5,150,"2.While dissapearing ,if there are more than one disc of the same number(except the");
	outtextxy(0,170,"current disc) the corresponding disc appears and score increases by 5");
	outtextxy(5,200,"3.In between the game you will have unnumbered disc falling down , these are called ");
	outtextxy(0,220,"secret disc.");
	outtextxy(0,250,"4.Secret disc needs to be broken twice to get a random new number that acts as the ");
	outtextxy(0,270,"current disc " );
	outtextxy(5,350,"6.For once when a disc disappears placed next to it its color changes from dark grey");
	outtextxy(0,370,"to light grey indicating that its broken once and the scores increase by 2");
	outtextxy(5,400,"7.For the next chances of breaking it a random number appears and score ads by 2");
	outtextxy(5,420,"8. The game ends when all the columkns are filled completely ");
	getch();
	sound(3000);
	delay(50);
	nosound();
	cleardevice();

}
void drop_7::option_drop()
{

	int 	flag=0,ret=6,ct=0;
	cleardevice();
       do
       {
	    setbkcolor(1);
	    settextstyle(10,0,4);
	    setcolor(15);
	    outtextxy(140,3,"DROP 7-OPTIONS");
	    settextstyle(10,0,1);
	    outtextxy(150,172,"*");
	    outtextxy(200,175,"Controls");
	    outtextxy(150,222,"*");
	    outtextxy(200,225,"How To PLay");
	    outtextxy(150,272,"*");
	    outtextxy(200,275,"New Game");
	    outtextxy(150,323,"*");
	    outtextxy(200,325,"Mode");
	    outtextxy(150,372,"*");
	    outtextxy(200,375,"Back");


				ct=0;
				ob.show_mouse();
				ob.get_status();
				if(mouseloop(200,332,185,212)==1) //controls
				{
					sound(2000);
					delay(30);
					ob.hide_mouse();
					nosound();
					game.drop_7::controls_drop();
					flag=1;
				}
				else if(mouseloop(200,383,239,270)==1)//rules			 {
				{
					sound(2000);
					delay(30);
					ob.hide_mouse();
					cleardevice();
					nosound();
					game.drop_7::rules_drop();
				}
				else if(mouseloop(200,353,289,310)==1)// new game
				{
					sound(2000);
					delay(30);
					char ch[20];
					ob.hide_mouse();
					nosound();
					cleardevice();
					setbkcolor(1);
					settextstyle(2,0,8);
					outtextxy(200,175,"Your Score:");
					itoa(sc,ch,10);
					outtextxy(400,175,ch);
					setcolor(15);
					outtextxy(30,340,"Press Enter To Erase The current play");
					outtextxy(100,440,"Press ESC To Continue Playing ");
					int u=bioskey(0);
					sound(3000);
					delay(50);
					nosound();
					int y=0;
					while(y!=2)
					{
					      if(u==7181)
					      {
						drop_7_screen_show=1;
						sc=0;
						y=2;
						for(int i=0;i<7;i++)
						{
							for(int j=0;j<7;j++)
							{
								drop_7_array[i][j]=0;
							}
						}
						sc=0;
					      }
					      else if(u==283)
					      {
						  y=2;
					      }
					      else
					      {
						 u= bioskey(0);
					      }
					}
					cleardevice();
				}
				else if(mouseloop(200,270,339,360)==1)    //mode
				{
				       sound(2000);
				       delay(30);
				       ob.hide_mouse();
				       nosound();
				       cleardevice();
				       setbkcolor(1);
				       setcolor(15);
				       settextstyle(10,0,1);
				       outtextxy(150,172,"*");
				       outtextxy(200,175,"Normal");
				       outtextxy(150,222,"*");
				       outtextxy(200,225,"Hard");
				       int y=0;
				       do
				       {


						do
						{

							ob.show_mouse();
							y=0;
							ob.get_status();
							if(mouseloop(200,312,185,212)==1) //normal					{
							{
								sound(2000);
								delay(50);
								ob.hide_mouse();
								drop_7_mode=1;
								y=1;
								nosound();
								setcolor(15);
								settextstyle(2,0,8);
								outtextxy(30,440,"Press Esc To Go Back");
							}
							else if(mouseloop(200,270,239,270)==1)//hard			 {
							{
								sound(2000);
								delay(50);
								ob.hide_mouse();
								drop_7_mode=2;
								y=1;
								nosound();
								setcolor(15);
								settextstyle(2,0,8);
								outtextxy(30,440,"Press Esc To Go Back");
							}
						}while(y==0);
					}while(bioskey(0)!=283);
					sound(3000);
					delay(50);
					nosound();
					cleardevice();

			    }
			    else if(mouseloop(200,270,383,411)==1)    //back
			    {
					sound(2000);
					ob.hide_mouse();
					delay(30);
					nosound();
					cleardevice();
					ct=1;
					ret=1;

			    }

		      }while(ct!=1);


}
void graphics::mainpage_drop()
{
	  #define m1 "DROP 7";
	  #define m2 "Options";
	  #define m3 "Exit";
	  #define m4 "Start";
	  #define m5 "Continue";
	  char s1[20]=m1;
	  char s2[20]=m2;
	  char s3[20]=m3;
	  char s4[20]=m4;
	  char s5[20]=m5;
	  cleardevice();
	  if(drop_7_screen_show==1)
	  {
	     setbkcolor(1);
	     setcolor(15);
	     settextstyle(10,0,6);
	     outtextxy(100,95,s1);
	     settextstyle(8,0,4);
	     setcolor(2);
	     outtextxy(490,360,s2);
	     outtextxy(490,420,s3);
	     outtextxy(490,300,s4);
	     setcolor(2);
	     line(460,0,460,480);
	     line(0,290,640,290);
	  }
	  if(drop_7_screen_show==2)
	  {
	     setbkcolor(1);
	     setcolor(15);
	     settextstyle(10,0,6);
	     outtextxy(100,95,s1);
	     setcolor(2);
	     settextstyle(8,0,4);
	     outtextxy(490,360,s2);
	     outtextxy(490,420,s3);

	     outtextxy(490,300,s5);
	     line(460,0,460,480);
	     line(0,290,640,290);

	  }
}
void graphics::selection_drop()
{
	      char s[20];

	      #define m6 "Score";
	      #define m7 "ESC";
	      char s1[20]=m6;
	      char s2[20]=m7;
	      if(sc<1000)
	      {
			itoa(sc,s,10);
			settextstyle(6,0,5);
			outtextxy(30,110,s1);
			if(sc!=0)outtextxy(40,150,s);
	      }
	      else if(sc>1000)
	      {
			itoa(sc,s,10);
			settextstyle(6,0,4);
			outtextxy(20,110,s1);
			if(sc!=0)outtextxy(30,150,s);
	      }
	      else if(sc>10000)
	      {
			itoa(sc,s,10);
			settextstyle(6,0,3);
			outtextxy(15,110,s1);
			if(sc!=0)outtextxy(22,150,s);
	      }
	      setcolor(4);
	      settextstyle(10,0,2 );
	      outtextxy(45,410,s2);
	      line(15,435,40,420);
	      line(15,435,40,450);
	      rectangle(40,420,130,450);

}
void graphics::box_drop()
{
	setbkcolor(1);
	game.drop_7::selection_drop();
	setcolor(15);
	rectangle(147,110,623,453);
	for(int i=147+68;i<=623;i=i+68)
	{
		line(i,110,i,453);
	}
	for(int j=110+49;j<=453;j=j+49)
	{
			line(147,j,623,j);
	}

}
void drop_7::start()
{
	cleardevice();
	setbkcolor(1);
	setcolor(15);
	game.drop_7::box_drop();
	game.drop_7::disp(drop_7_array);
	drop_7_screen_show =2;
	setcolor(15);
       int 	x=147,y=110,gmover=0;
       int m=0,n=0,u=0;int f=2;
		if(drop_7_mode==2)               //difficulty
		{
			int g= random(3);
			if(g==0)
			{
				for(int k=0;k<7;k++)
				drop_7_array[6][k]=20;
			}
			else if(g==1)
			{
				for(int k=0;k<7;k++)
				{
					if(k%2==0)drop_7_array[6][k]=10;
					else drop_7_array[6][k]=20;
				}
			}
			else if(g==2)
			{
				for(int k=0;k<7;k++)
				{
					if(k%2==0)drop_7_array[6][k]=random(5)+2;
					else drop_7_array[6][k]=20;
				}
			}
		}
		int who=110,y1,x1;
		do
		{


			int p=110;

			 p = generate(147,75);

			f=0;
	     int  x=147,y=110;
	     int m=0,n=0;



     do
     {
	  u=bioskey(0);
	 gmover= gameover();
	 sde=0;
	while(((u!=7181))&&(gmover==0)&&(u!=283))
	{
		 u=bioskey(0);
		 sde=0;
		while((u==19712)&&(gmover==0)&&(u!=283))
		{
				n++;
				x+=68;
				for(int i=x;i<=x;i+=68)
				{
					setcolor(15);
					cleardevice();
					game.drop_7:: box_drop();
					game.drop_7::disp(drop_7_array);
				}
				if(n-6<=0)generate(i-68,75,p);
				u=bioskey(0);

			}
			while((u==19200)&&(gmover==0)&&(u!=283))// move left
			{
					sde=0;
					n--;
					x-=68;
					for(int i=x;i<=x;i+=68)
					{

						setcolor(15);
						cleardevice();
						game.drop_7::box_drop();
						game.drop_7::disp(drop_7_array);
					}
					if(n-6<=0)generate(i-68,75,p);

						u=bioskey(0);

					}
				}
			}while(drop_7_array[0][n]!=0&&(u!=283));
			y=110;
			m =0  ;
		    int l=0;


			if(n>6)
			{
				n=6;
			 }
			 else if(n<0)
			 {
				n=0;
			 }

			 int st=n;
			 while(drop_7_array[m][n]==0&&m<=6&&(gmover==0)&&(u!=283)&&(drop_7_array[0][n]==0))
			 {
				{
					setcolor(1);
					rectangle(17,0,623,108);
					setfillstyle(1,1);
					floodfill(177,3,1);
				}
				if((n==0)&&(l==0))
				{

					cleardevice();
					game.drop_7::box_drop();
					selection_drop();
				}
				sde=1;
				y+=49;
				if(st==0)
				{
					delay(300);
					st++;
				}
				generate(x,y-25,p);
				if((y>49+110)&&(l!=0)&&(p!=7))
				{
					setfillstyle(1,1);
					floodfill(x+5,y-49-10,15);
				}
				if(p==7)
				{
					setcolor(1);
					rectangle(17,0,623,108);
					setfillstyle(1,1);
					floodfill(177,3,1);
					setcolor(1);
					rectangle(x+3,y-97,x+65,y-50);
					setfillstyle(1,1);
					floodfill(x+5,y-90,1);

				}
				if(st!=0)
				{
					delay(200);
				}
				game.drop_7::disp(drop_7_array);

				m++;
				l++;
			 }
			 delay(20);
			 m--;
			 drop_7_array[m][n] =p;
			 game.drop_7::disp(drop_7_array);
			 drop(m,n);
			 sde=0;
		}while((u!=283)&&(gmover==0));
		sound(3000);
		delay(50);
		nosound();
}



void drop_7::startup()
{
	int opt=0;
	sc=0 ;
	cleardevice();
	game.drop_7::mainpage_drop();
	int count=0;
	int ret=0;
	  do
	  {
	       opt=0;
	       cx=cy=0;
	       if(count==0)
	       {
			cleardevice();
			game.drop_7::mainpage_drop();
	       }
	       count=0;

	       ob.show_mouse();
	       ob.get_status();
	       delay(200);
	       if(mouseloop(490,570,312,337)==1)
	       {
			sound(2000);
			delay(50);
			ob.hide_mouse();
			opt=1;
			nosound();
	       }
	       else if(mouseloop(490,620,370,396)==1)
	       {
			sound(2000);
			delay(50);
			ob.hide_mouse();
			opt=2;
			nosound();
	       }
	       else if(mouseloop(490,550,433,460)==1)
	       {
			sound(2000);
			delay(50);
			nosound();
			ob.hide_mouse();
			ret=1;
	       }                         //error
	       else count=1;
	       switch(opt)
	       {
		 case 1: game.drop_7::start();break;
		 case 2: option_drop();break;
	       }
	  }while(ret!=1);

}

				// TRACE----2048
//----------------------------------------------------------------------------------------------------
void Trace_2048::disp(int a[4][4])
{
	int 	i=9,j=2,k=0,l1=0,d;
	char	z[20];
		cleardevice();
		setcolor(3);
		rectangle(5,70,180,150);
		rectangle(5,370,180,450);
		rectangle(5,230,180,300);
		rectangle(60,180,120,300);
		setcolor(14);
		setbkcolor(19);
		rectangle(200,70,600,470);
		settextstyle(1,0,3);
		outtextxy(200,0,"* controls(enter c)");
		outtextxy(200,30,"* options(enter o)");
		line(300,70,300,470);
		line(400,70,400,470);
		line(500,70,500,470);
		line(200,170,600,170);
		line(200,270,600,270);
		line(200,370,600,370);
		settextstyle(1,0,7);
		outtextxy(15,75,"2048");
		outtextxy(70,160,"w");
		outtextxy(15,220,"a");
		outtextxy(85,220,"s");
		outtextxy(145,220,"d");
		outtextxy(15,300,"score");
		itoa(s1,z,10);
		if(s1>=10000)settextstyle(1,0,6);
		outtextxy(15,370,z);
		setcolor(2);
		for(i=70;i<470;i=i+100)
		{
			l1=0;
			for(j=210;j<610;j=j+100)
			{
					settextstyle(1,0,5);
					itoa(a[k][l1],z,10);
					if(a[k][l1]==3)
					{
						settextstyle(1,0,8);
						outtextxy(j,i,"x");
					}
					else if(a[k][l1]!=0)
					{
						if(a[k][l1]<100)d=7;
						else if((a[k][l1]>100)&&(a[k][l1]<1000))d=4;
						else if(a[k][l1]>10000)d=3;
						settextstyle(1,0,d);
						outtextxy(j,i,z);
					}
					l1++;
			}
			k++;
		}

}
int Trace_2048::ins(int a[4][4])
{
	int 	l1,h,f,k,p=1;
		m=0;
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(a[i][j]==0)
				{
					m++;
					p=0;
				}
			}
		}
		randomize();
		l1=random(1+m);
		m=0;
		for(i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				if(a[i][j]==0)
				{
					m++;
					if((m==l1)&&(m%2==0))a[i][j]=2;
					else if((m==l1)&&(m%2!=0))a[i][j]=4;
				}
			}
		}
		disp(a);
		return p;
}
int Trace_2048::up(int a[4][4])
{
	int	k,p=1,i;
		for(int j=0;j<4;j++)
		{
			for(k=0;k<3;k++)
			{       i=1;
				while((a[k][j]==0)&&(i<=(3-k)))
				{
					a[k][j]=a[k+i][j];
					a[k+i][j]=0;
					if(a[k][j]!=0)p=0;
					i++;
				}
			}
			k=0;
			while(k<3)
			{
				if(a[k][j]==a[k+1][j])
				{
					a[k][j]=2*a[k+1][j];
					a[k+1][j]=0;
					s1=s1+a[k][j];
					if(a[k][j]!=0)p=0;
				}
				k++;
			}
			for(k=0;k<3;k++)
			{
				if(a[k][j]==0)
				{
					a[k][j]=a[k+1][j];
					a[k+1][j]=0;
				}
			}
		}
		if(p==0)
			ins(a);
		else
			disp(a);
		return p;
}
int Trace_2048::down(int a[4][4])
{
	int	k,p=1,i;
		for(int j=0;j<4;j++)
		{
			for(k=3;k>0;k--)
			{
				i=1;
				while((a[k][j]==0)&&(i<=k))
				{
					a[k][j]=a[k-i][j];
					a[k-i][j]=0;
					if(a[k][j]!=0)p=0;
					i++;
				}
			}
			k=3;
			while(k>0)
			{
				if(a[k][j]==a[k-1][j])
				{
					a[k][j]=2*a[k][j];
					s1=s1+a[k][j];
					a[k-1][j]=0;
					if(a[k][j]!=0)p=0;
				}
				k--;
			}
			for(k=3;k>0;k--)
			{
				if(a[k][j]==0)
				{
					a[k][j]=a[k-1][j];
					a[k-1][j]=0;
				}
			}
		}
		if(p==0)
			ins(a);
		else
			disp(a);
		return p;
}
int Trace_2048::left(int a[4][4])
{
	int	k=0,p=1,j;
		for(int i=0;i<4;i++)
		{
			for(k=0;k<3;k++)
			{
				j=1;
				while((a[i][k]==0)&&(j<=(3-k)))
				{
					a[i][k]=a[i][k+j];
					a[i][k+j]=0;
					if(a[i][k]!=0)p=0;
					j++;
				}
			}
			k=0;
			while(k<3)
			{
				if(a[i][k]==a[i][k+1])
				{
					a[i][k]=2*a[i][k+1];
					s1=s1+a[i][k];
					a[i][k+1]=0;
					if(a[i][k]!=0)p=0;
				}
				k++;
			}
			for(k=0;k<3;k++)
			{
				if(a[i][k]==0)
				{
					a[i][k]=a[i][k+1];
					a[i][k+1]=0;
				}
			}
		}
		if(p==0)
			ins(a);
		else
			disp(a);
		return p;
}
int Trace_2048::right(int a[4][4])
{
	int	k,p=1,j;
		for(int i=0;i<4;i++)
		{
			for(k=3;k>0;k--)
			{
				j=1;
				while((a[i][k]==0)&&(j<=k))
				{
					a[i][k]=a[i][k-j];
					a[i][k-j]=0;
					j=j+1;
					if(a[i][k]!=0)p=0;
				}
			}
			k=3;
			while(k>0)
			{
				if(a[i][k]==a[i][k-1])
				{
					a[i][k]=2*a[i][k];
					s1=s1+a[i][k];
					a[i][k-1]=0;
					if(a[i][k]!=0)p=0;
				}
				k--;
			}
			for(k=3;k>0;k--)
			{
				if(a[i][k]==0)
				{
					a[i][k]=a[i][k-1];
					a[i][k-1]=0;
				}
			}
		}
		if(p==0)
			ins(a);
		else
			disp(a);
		return p;
}
void Trace_2048::control(int a[4][4])
{
	cleardevice();
	settextstyle(1,0,15);
		outtextxy(100,20,"controls");
		settextstyle(1,0,5);
		outtextxy(50,200,"* to move up press w");
		outtextxy(50,250,"* to move down press s");
		outtextxy(50,300,"* to move left press a");
		outtextxy(50,350,"* to move right press d");
	getch();
	disp(a);
}
int Trace_2048::option(int a[4][4])
{
	char	ch;
		cleardevice();
		settextstyle(1,0,15);
		outtextxy(100,20,"options");
		settextstyle(1,0,6);
		outtextxy(50,200,"-modes ");
		settextstyle(1,0,5);
		outtextxy(70,250,"* clas1sic(enter c)");
		outtextxy(70,300,"* xtiles(enter x)");
		settextstyle(1,0,6);
		outtextxy(50,350,"-return(enter r)");
		outtextxy(50,400,"-exit(enter e)");
		do
		{
			ch=getch();
		}while((ch!='c')&&(ch!='x')&&(ch!='r')&&(ch!='e'));
		if(ch=='c')
			return 1;
		else if(ch=='r')
			{
				disp(a);
				return 0;
			}
		else if(ch=='x')
			return 2;
		else if(ch=='e')
			return 3;
}
int Trace_2048::source(int m[4][4])
{
	int	a,b,c,d,k=0;
	char	ch;
		a=b=c=d=0;
		while((a==0)||(b==0)||(c==0)||(d==0))
		{
			ch=getch();
			if(ch=='w')
				a=up(m);
			else if(ch=='a')
				b=left(m);
			else if(ch=='s')
				c=down(m);
			else if(ch=='d')
				d=right(m);
			else if(ch=='c')
				control(m);
			else if(ch=='o')
			{
				k=option(m);
				if(k!=0)return k;
			}
		}
		cleardevice();
		settextstyle(1,0,10);
		outtextxy(100,20,"game over");
		settextstyle(1,0,5);
		outtextxy(50,200,"* classic(enter c)");
		outtextxy(50,250,"* xtiles(enter x)");
		outtextxy(50,300,"* exit(enter e)");
		do
		{
			ch=getch();
		}while((ch!='x')&&(ch!='c')&&(ch!='e'));
		do
		{
			if((ch=='c')||(k==1))
				return 1;
			else if((ch=='x')||(k==2))
				return 2;
			else if(ch=='e')
				return 0;
		}while(k!=0);
}
void Trace_2048::initial(int a[4][4])
{
	int	h,k,l1;
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				a[i][j]=0;
			}
		}
		i=0;
		randomize();
		h=random(4);
		k=random(4);
		l1=random(6);
		if((h+k)==l1)
			a[k][h]=4;
		else
			a[k][h]=2;
		i++;
		a[h][k]=a[k][h];
		disp(a);
}
void Trace_2048::initialx(int a[4][4])
{
	int	h,k,l1,c,d;
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				a[i][j]=0;
			}
		}
		i=0;
		randomize();
		c=random(4);
		d=random(4);
		h=random(4);
		k=random(4);
		l1=random(6);
		if((h+k)==l1)
			a[k][h]=4;
		else
			a[k][h]=2;
		i++;
		a[h][k]=a[k][h];
		a[c][d]=3;
		disp(a);
}
void Trace_2048::start_2048(int a[4][4])
{
	int	k=1;
	char	ch;
		setbkcolor(1);
		settextstyle(1,0,15);
		outtextxy(100,20,"2048");
		settextstyle(1,0,5);
		outtextxy(50,200,"* classic(enter c)");
		outtextxy(50,250,"* xtiles(enter x)");
		outtextxy(50,300,"* exit(enter e)");
		do
		{
			ch=getch();
		}while((ch!='x')&&(ch!='c')&&(ch!='e'));
		k=4;
		do
		{
			if((ch=='c')||(k==1))
				initial(a);
			else if((ch=='x')||(k==2))
				initialx(a);
			else if(ch=='e')
				k=0;

		     ch='a';
		    if((k!=0)&&(k!=3))
		    k=source(a);
		}while(k!=0&&k!=3);
}
class score
{
    public:	char s[25];
		int sc;
}t;
void score2()
{
	cleardevice();
	int c=0;
	ofstream f("score");
	settextstyle(1,0,2);
	outtextxy(100,100,"enter you name ");
	gotoxy(6,12);
	cin>>t.s;
}
void score()
{
	char sc2[25],sc3[25];
	outtextxy(100,420,"level");
	itoa(t.sc/10+1,sc3,10);
	outtextxy(210,420,sc3);
	settextstyle(1,0,5);
	outtextxy(100,50,"score");
	itoa(t.sc,sc2,10);
	outtextxy(100,115,sc2);

}
int Trace_2048::gameover()
{
	cleardevice();
	setcolor(4);
	setbkcolor(0);
	char sc2[25];
	char ch;
	setbkcolor(1);
	settextstyle(1,0,5);
	outtextxy(150,100,"Your score is ");
	itoa(t.sc,sc2,10);
	outtextxy(150,150,sc2);
	settextstyle(1,0,2);
	outtextxy(450,300,"Exit(press e)");
	do
	{
		ch=getch();
		if(ch=='e')return 0;
	}while(ch!='e');


}
void Trace_2048::disp(int a[8][5])
{
		cleardevice();
	int 	i,j,k=0,l1=0;
	char	z[20],s1c2[25];
		setbkcolor(1);
		score();
		setcolor(12);
		outtextxy(70,160,"w");
		outtextxy(15,220,"a");
		outtextxy(85,220,"s");
		outtextxy(145,220,"d");
		rectangle(60,180,120,300);
		rectangle(5,230,180,300);
		setcolor(12);
		rectangle(270,50,520,450);
		settextstyle(1,0,2);
		outtextxy(350,15,"FINISH POINT");
		for(i=270;i<520;i=i+50)
		{
			line(i,50,i,450);
		}
		for(j=100;j<450;j=j+50)
		{
			line(270,j,520,j);
		}
		k=280;
		l1=50;

		for(i=0;i<8;i++)
		{
			k=280;
			for(int j=0;j<5;j++)
			{
				settextstyle(1,0,4);
				itoa(a[i][j],z,10);
				if(a[i][j]==2)
				{
					setfillstyle(SOLID_FILL,2);
					floodfill(k+20,l1+10,12);
				}
				k=k+50;
			}
			l1=l1+50;
		}
}

void Trace_2048::disp1(int a[8][5])
{
		cleardevice();
	int 	i,j,k=0,l1=0;
	char	z[20];
	cleardevice();
	setbkcolor(1);
		outtextxy(80,160,"w");
		outtextxy(20,220,"a");
		outtextxy(90,220,"s");
		outtextxy(150,220,"d");
		rectangle(60,180,120,300);
		rectangle(5,230,180,300);
		score();
		setbkcolor(1);
		setcolor(12);
		rectangle(270,50,520,450);
		mine=0;
		settextstyle(1,0,3);
		outtextxy(350,15,"FINISH POINT");
		for(i=270;i<520;i=i+50)
		{
			line(i,50,i,450);
		}
		for(j=100;j<450;j=j+50)
		{
			line(270,j,520,j);
		}
		setfillstyle(SOLID_FILL,14);
		floodfill(365,30,12);
		k=280;
		l1=50;
		for(i=0;i<8;i++)
		{
			k=280;
			for(int j=0;j<4;j++)
			{
				settextstyle(1,0,4);
				itoa(r[i][j],z,10);
				if(r[i][j]==1)
				{
					setfillstyle(SOLID_FILL,14);
					floodfill(365,30,12);
					setfillstyle(SOLID_FILL,4);
					floodfill(k+20,l1+10,12);
				}
				k=k+50;
			}
			l1=l1+50;
		}
		delay(700);
}
int Trace_2048::source(int a[8][5])
{
	char	ch;
		g=7,l1=2,s1=5;
		if(screen_counter==0)
		{
			cleardevice();
			setbkcolor(14);
			settextstyle(1,0,3);
			setcolor(2);
			outtextxy(100,230," Memorize the upcoming mines quickly ");
			for(int p=0;p<=620;p++)
			{
				sound(222.5+p*20);
				outtextxy(p,430,"<|>");
				delay(5)  ;
			}
			nosound();
			outtextxy(200,345,"LOADING.. ");
			delay(400);
		}
		screen_counter=1;
		cleardevice();
		a[g][l1]=2;
		disp1(a);
		disp(a);
		do
		{
			ch=getch();
			if(ch=='w')
				g--;
			else if(ch=='a')
				l1--;
			else if(ch=='s')
				g++;
			else if(ch=='d')
				l1++;
			else if(ch=='e')
				exit(0);
			a[g][l1]=2;
			disp(a);

		}while(((a[g][l1]-1)!=r[g][l1])&&((g!=0)||(l1!=2)));
		if((g==0)&&(l1==2))return 1;
		else return 0;
}
int Trace_2048::ins(int a[8][5])
{
	int 	l1,h,f,k,x=0;
		k=0;
		do
		{
			for(int i=1;i<4;i++)
			{
				for(int j=0;j<3;j++)
				{
					if(r[i][j]==0)
					{
						k++;
					}
				}
			}
			randomize();
			l1=random(k);
			k=0;
			for(i=1;i<7;i++)
			{
				for(int j=0;j<4;j++)
				{
					if(r[i][j]==0)
					{
						k++;
						if(l1==k)
						{
							r[i][j]=1;
							x++;
						}
					}

				}
			}
		}while(m>=x);
		m++;
		k=source(a);
		return k;
}

void Trace_2048::initialp(int a[8][5])
{
	int	k=1;
		int s=0;
		do
		{
			for(int i=0;i<8;i++)
			{
				for(int j=0;j<5;j++)
				{
					a[i][j]=0;
					r[i][j]=0;
				}
			}
			c++;
			k=ins(a);
			if(k==1)
			{
				t.sc=t.sc+10;
			}
			else
			{
				k=gameover();
			}

		}while(k!=0) ;

}
int Trace_2048::trace()
{
	cleardevice();
	screen_counter=0;
	int a[8][5];
	setbkcolor(14);
	setcolor(4);
	settextstyle(1,0,7);
	outtextxy(50,15,"TRACE");
	settextstyle(3,0,5);
	char ch;
	outtextxy(80,155,"Play(Press p)");
	outtextxy(80,185,"Exit(press e)");
	settextstyle(1,0,1);

	setcolor(128);
	setcolor(12);
	outtextxy(400,235,"look the mines");
	outtextxy(400,255,"trace the mines");
	outtextxy(400,275,"escape the mines");
	setcolor(2);
	line(400,50,500,50);
	line(400,50,400,100);
	line(400,100,550,100);
	line(550,50,550,100);
	line(500,0,500,50);
	line(550,0,550,50);
	//l1ine(550,350,550,400);
	line(0,350,640,350);
	line(0,400,640,400);
	setfillstyle(1,2);
	floodfill(501,51,2);
	floodfill(580,374,2);
	do
	{
		ch=getch();
		if(ch=='p')initialp(a);
		else if(ch=='e')return 0;
	}while((ch!='e')&&(ch!='p'));
}


void game::start_game()
{
	int mainpage_screening_counter=0;
	setbkcolor(14);
	settextstyle(1,0,7);
	cleardevice();
	settextstyle(1,0,5);
	setcolor(2);
	outtextxy(150,150,"Mind Stormmer");
	 delay(500);
	 sound(1034.44467);
	 delay(100);
	 nosound();
	cleardevice();
	setbkcolor(15);
	do
	{

		if(mainpage_screening_counter==0)
		{
			cleardevice();
			setlinestyle(SOLID_LINE,1,1);
			setbkcolor(1);
			settextstyle(1,0,5);
			setcolor(2);
			outtextxy(150,15,"Mind Stormmer");
			setcolor(14);
			outtextxy(170,100,"2048");
			outtextxy(170,150,"Trace");
			outtextxy(170,200,"Sudoku");
			outtextxy(170,250,"Drop7");
			outtextxy(170,300,"Exit");
		}
		mainpage_screening_counter=1;
		ob.show_mouse();
		ob.get_status();
		delay(100);
		if(mouseloop(170,290,100,150)==1)
		{
			ob.hide_mouse();
			cleardevice();
			int a[4][4];
			game.start_2048(a);
			mainpage_screening_counter=0;
		}
		else if(mouseloop(170,290,155,205)==1)
		{
			ob.hide_mouse();
			cleardevice() ;
			game.trace();
			mainpage_screening_counter=0;
		}
		else if(mouseloop(170,285,205,240)==1)
		{
			ob.hide_mouse();
			cleardevice() ;
			game.sudoku::startup();
			sudoku_screen_changer=1;
			mainpage_screening_counter=0;
		}
		else if(mouseloop(170,255,255,285)==1)
		{
			ob.hide_mouse();
			cleardevice() ;
			game.drop_7::startup();
			mainpage_screening_counter=0;
		}
		else if(mouseloop(170,235,305,335)==1)
		{
			  ob.hide_mouse();
			  game.end_game();
		}

	}while(5);

}
void main()
{
	int	opt;
	int gd=9,gn=2;
	char ch;
	initgraph(&gd,&gn,"c:\\TC\\BGI");
	char s;
	sudoku_screen_changer=1;
	sc=0;
	game.start_game();
	closegraph();

}






