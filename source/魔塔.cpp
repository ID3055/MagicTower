#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "map.cpp"					//��ͼ���� 
#include "warrior.cpp"				//�������� 
#include "ghost.cpp"				//�������� 
#include "item.cpp"					//�������� 
#include "SpecialItem.cpp"			//�������
#include "npc.cpp"					//NPC

mouse_msg msg = {0};				//�����Ϣ�洢����

void menu();						//��ʼ��Ϸ�˵�

void Button();						//��Ϸ�������������

void showimg32(PIMAGE img,int x,int y,int ximg,int yimg); //����Ϸ��������ʾ32*32ͼ��
void Show();						//��ʾȫ��Ԫ�ػ���

void ShowMap();						//��ʾ��ͼ
void ShowWarrior();					//��ʾ���� 
void ShowGhost(); 					//��ʾ���� 
void ShowNpc();						//��ʾNPC
void ShowItem();					//��ʾ����
void ShowShop();					//��ʾ�̵�
void ShowLeft();					//��ʾ����
void ShowRight();					//��ʾ����
void ShowFight(int x,int y);		//ս������
void Showframe();					//�߿�

void Boost();						//¥�㴫��
void choice();						//¥�㴫��ѡ���

void Move();						//�ƶ�
BOOL JudgeMove(int key);			//����ʱ�ж��ƶ�
void Item(int x,int y);				//��������ʱ
void SpecialItem(int x,int y);		//�����������
BOOL Shop(int x,int y);				//�����̵�
void Door(int x,int y);				//������ʱ
void OpenDoor(int x,int y,int kind);//����
BOOL Npc(int x,int y);				//npc
BOOL Monster(int x,int y);			//��������ʱ
BOOL fight(int x,int y);			//ս���ж�
void stair();						//���¥�������λ��

void Mouse();
void TextBox(char *str);			//��ʾ����Ի��� 

void plot();						//�������
 
void plot1();						//������� 
void plot2();
void plot3();
void plot4();

void Save();						//�浵 
void Load();				 		//���� 

int floor=0;						//��ǰ¥�� 

#define _x 144						//��Ϸ������ƫ���� 
#define _y 24

int WinMain()						//������ 
{
	initgraph(640, 400);
	setrendermode(RENDER_MANUAL);
	setcaption("ħ�� v0.2");

	menu();
	for (;is_run();delay_fps(60))
	{
		Move();
		Show();
		plot();
		Button();
	}
	closegraph();
	return 0;
}
void plot()							//���� 
{
	plot1();
	plot2();
	plot3();
	plot4();
}
void Button()						//��������갴�� 
{
	while (mousemsg())
	{
		msg = getmouse();
	}
	PIMAGE img,imgB;
	img = newimage();
	imgB = newimage();
	getimage(img,"button.png",0,0);
	getimage(imgB,"B.png",0,0);
	if(msg.x>542&&msg.x<618&&msg.y>303&&msg.y<322)
	{
		putimage_withalpha(NULL,img,542,303,0,0);
		if(1== (int)msg.is_down())
		{
			Save();
		}
	}
	if(msg.x>542&&msg.x<618&&msg.y>343&&msg.y<362)
	{
		putimage_withalpha(NULL,img,542,343,0,0);
		if(1== (int)msg.is_down())
		{
			Load();
		}
	}
	if(msg.x>16&&msg.x<48&&msg.y>228&&msg.y<260)
	{
		if(1==boost)
		putimage_withalpha(NULL,imgB,16,228,0,0,32,32);
		if(1==boost&&1== (int)msg.is_down())
		{
			Boost();
		}
	}
	if(msg.x>50&&msg.x<82&&msg.y>228&&msg.y<260)
	{
		if(1==book)
		putimage_withalpha(NULL,imgB,50,228,32,0,32,32);
		if(1==book&&1== (int)msg.is_down())
		{
			
		}
	}
	delimage(img);
	delimage(imgB);
}
void menu()
{
	PIMAGE img,img2,img3;
	img = newimage();
	img2 = newimage();
	img3 = newimage();
	getimage(img,"menu.png",0,0);
	getimage(img2,"menu2.png",0,0);
	getimage(img3,"menu3.png",0,0);
	for (;is_run();delay_fps(60))
	{
		putimage_withalpha(NULL,img,0,0,0,0);
		while (mousemsg())
		{
			msg = getmouse();
		}

		if(msg.x>237&&msg.x<365&&msg.y>175&&msg.y<204)
		{
			putimage_withalpha(NULL,img2,0,0,0,0);
			if(1== (int)msg.is_down())
			{
				delay_ms(500);
				break;
			}
		}
		if(msg.x>237&&msg.x<365&&msg.y>248&&msg.y<275)
		{
			putimage_withalpha(NULL,img3,0,0,0,0);
			if(1== (int)msg.is_down())
			{
				Load();
				delay_ms(500);
				break;
			}
		}
		
	}
	delimage(img);
	delimage(img2);
	delimage(img3);
}
int p[]={1,1,0,1};
void plot1()		//���� 
{
	int i;
	if(p[0])
	{
		if(2==floor&&warrior.x==4&&warrior.y==8&&floor==2)
		{
			int alpha = 0,alpha2 = 0;
			PIMAGE img;
			img = newimage();
			getimage(img,"ghost.png",0,0);
			for (;1;delay_fps(60))	//ħ������ 
			{
				Show();
				putimage_alphatransparent(NULL, img, (4*32)+_x, (6*32)+_y, BLACK, (unsigned char)alpha,(6*32),(3*32),32,32);
				if (alpha < 0xFE)
				alpha += 2;
				if (alpha >= 0xFE) 	//ħ��������Ϻ� 
				{
					char str[]="ħ�� Zeno ˵������ӭ����ħ�������ǵ�һ��λ��ս�ߡ������ܴ�������е����£��Ҿ�����һ��һ�ľ������������������ҵİ��š�";
					TextBox(str);
					if (kbhit())
					break;
				}
			}
			for (;1;delay_fps(60))	//ħ�����³��� 
			{
				Show();
				putimage_alphatransparent(NULL, img, (4*32)+_x, (6*32)+_y, BLACK, (unsigned char)alpha,6*32,3*32,32,32);
				putimage_alphatransparent(NULL, img, (3*32)+_x, (8*32)+_y, BLACK, (unsigned char)alpha2,8*32,3*32,32,32);
				putimage_alphatransparent(NULL, img, (4*32)+_x, (7*32)+_y, BLACK, (unsigned char)alpha2,8*32,3*32,32,32);
				putimage_alphatransparent(NULL, img, (5*32)+_x, (8*32)+_y,BLACK, (unsigned char)alpha2,8*32,3*32,32,32);
				putimage_alphatransparent(NULL, img, (4*32)+_x, (9*32)+_y, BLACK, (unsigned char)alpha2,8*32,3*32,32,32);
				
				if (alpha2 < 0xFE)
				alpha2 += 2;
				
				if (alpha2 >= 0xFE) //ħ������������Ϻ� 
				{
					char str[]="������~~";
					TextBox(str);
					if (i=kbhit())		//�˴���bug���ж�δ��Ч���ҳ���������˴���ֱ�������ⰴ�� 
					break;
				}
			}
			delimage(img);
			ShowFight(warrior.x,warrior.y);

			floor=1;
			warrior.hp=400;
			warrior.atk=10;
			warrior.def=10;
			warrior.x=2;
			warrior.y=7;
			warrior.ybmp=0;
			p[0]=0;
		}
	}
}

void plot2()
{
	int i=0;
	if(p[1])
	{
		if(warrior.x==2&&warrior.y==7&&warrior.ybmp==3||warrior.x==3&&warrior.y==6&&warrior.ybmp==1&&floor==1)
		{
			char str[]="�����������㵽����ʱ�����ڻ����У�ħ�����������ӵ���������䡣��������ˣ��Ҹ�������ܵİ���������ˣ�����һ��Խ���ɡ�";
			TextBox(str);
			getch();
			p[1]=0;
			map[1][6][1].ybmp=0;
			for(;is_run();delay_fps(60))
			{
				Show();
				i++;
				if(npc[1][0].x!=0)
				{
					if(i==10)
					{
						npc[1][0].x--;
						i=0;
					}
				}
				else if(npc[1][0].y!=8)
				{
					if(i==10)
					{
						npc[1][0].y++;
						i=0;
					}
				}
				if(npc[1][0].y==8)
				{
					p[2]=1;
					break;
				}
			}
		}
	}
}

void plot3()
{
	int i=0;
	if(p[2])
	{
		if(warrior.x==0&&warrior.y==7&&warrior.ybmp==0&&floor==1)
		{
			char str[]="    ���������ӳ����ˡ���Ľ��Ͷܱ����������ˣ���������ҵ���������֪��������5¥��������9¥���������ȡ�����ǡ�����������Ҫ��û�����㣬�ټ���";
			TextBox(str);
			getch();
			p[2]=0;
			for(;is_run();delay_fps(60))
			{
				Show();
				i++;
				if(npc[1][0].y!=11)
				{
					if(i==10)
					{
						npc[1][0].y++;
						i=0;
					}
				}
				if(npc[1][0].y==11)
				{
					npc[1][0].xbmp=-2;
					break;
				}
			}
		}
	}
}
void plot4()
{
	int i=0;
	if(p[3])
	{
		if(warrior.x==7&&warrior.y==10&&warrior.ybmp==2)
		{
			map[floor][10][8].ybmp=0;
			p[3]=0;
		}
	}
}
void TextBox(char *str)
{
	PIMAGE img;
	img = newimage();
	getimage(img,"textbox.png",0,0);
	putimage_withalpha(NULL,img,159,90,0,0);
	setcolor(EGERGB(0xff, 0xff, 0xff));
	setfont(16,0,"����");
	outtextrect(170,101,298,158,str);
	delimage(img);
} 
void Move()		//�ƶ� 
{
	int k=0;
	if (kbhit()) 
	{
		k = getch();
		switch(k){
			case 293:{	
			warrior.ybmp=1;
			ShowWarrior();
			if(JudgeMove(k))
			warrior.x--;
			} break;
			case 294:{
			warrior.ybmp=3;
			ShowWarrior();
			if(JudgeMove(k))
			warrior.y--;
			}break;
			case 295:{
			warrior.ybmp=2;
			ShowWarrior();
			if(JudgeMove(k))
			warrior.x++;
			}break;
			case 296:{
			warrior.ybmp=0;
			ShowWarrior();
			if(JudgeMove(k))
			warrior.y++;
			}break;
			case 98:{	
			if(boost)
			Boost();
			} break;
		}
	}
	if(map[floor][warrior.y][warrior.x].xbmp==2)//����ƶ�����¥�� 
	stair();
}
void stair()
{
	int x=warrior.x,y=warrior.y;	
	if(map[floor][y][x].ybmp==0)		//��������ϵ�¥�� 
	floor++;
	else if(map[floor][y][x].ybmp==1)	//��������µ�¥��
	floor--;
	
	reach[floor]=1;
	
	//ʹ���Ǹı�¥����뿪¥�� 
	if(y<10&&map[floor][y+1][x].xbmp==0&&map[floor][y+1][x].ybmp==0)
	warrior.y++;
 	else if(y>0&&map[floor][y-1][x].xbmp==0&&map[floor][y-1][x].ybmp==0)
 	warrior.y--;
 	else if(x>0&&map[floor][y][x-1].xbmp==0&&map[floor][y][x-1].ybmp==0)
 	warrior.x--;
 	else if(x<10&&map[floor][y][x+1].xbmp==0&&map[floor][y][x+1].ybmp==0)
 	warrior.x++;
 	warrior.ybmp=0;
}
void Boost()//���ͷ��� 
{
    char str[100];
    int k,i,j;
    k=floor;
	choice();
    if(floor==k)
    return;
	else if(floor<k)
	{
		for(i=0;i<11;i++)
	    {
	    	for(j=0;j<11;j++)
	    	{
		    	if(map[floor][j][i].xbmp==2&&map[floor][j][i].ybmp==0)
		    	break;
		    }
		    if(map[floor][j][i].xbmp==2&&map[floor][j][i].ybmp==0)
	    	break;
	    }
	} 
	
	else if(floor>k)
	{
		for(i=0;i<11;i++)
	    {
	    	for(j=0;j<11;j++)
	    	{
		    	if(map[floor][j][i].xbmp==2&&map[floor][j][i].ybmp==1)
		    	break;
		    }
		    if(map[floor][j][i].xbmp==2&&map[floor][j][i].ybmp==1)
	    	break;
	    }
	}
 	warrior.x=i,warrior.y=j;
	if(j<10&&map[floor][j+1][i].xbmp==0&&map[floor][j+1][i].ybmp==0)
	warrior.y++;
 	else if(j>0&&map[floor][j-1][i].xbmp==0&&map[floor][j-1][i].ybmp==0)
 	warrior.y--;
 	else if(i>0&&map[floor][j][i-1].xbmp==0&&map[floor][j][i-1].ybmp==0)
 	warrior.x--;
 	else if(i<10&&map[floor][j][i+1].xbmp==0&&map[floor][j][i+1].ybmp==0)
 	warrior.x++;
 	warrior.ybmp=0;
} 
void choice()
{
	int i,j,a,b;
	PIMAGE img,img2,img3;
	img = newimage();
	img2 = newimage();
	img3 = newimage();
	getimage(img,"boost.png",0,0);
	getimage(img2,"boost-s.png",0,0);
	getimage(img3,"boost-b.png",0,0);
	for (;is_run();delay_fps(60))
	{
		Show();
		putimage_withalpha(NULL,img,159,90,0,0);
		for(a=0;a<10;a++)
		{
			for(b=0;b<5;b++)
			{
				if(!reach[a+10*b])
				putimage_withalpha(NULL,img3,170+a*30,101+b*30,0,0);
			}
		}
		while (mousemsg())
		{
			msg = getmouse();
		}
		for(i=0;i<10;i++)
		{
			for(j=0;j<5;j++)
			{
				if(msg.x>(170+i*30)&&msg.x<(170+i*30+28)&&msg.y>(101+j*30)&&msg.y<(101+j*30+28))
				{
					putimage_withalpha(NULL,img,159,90,0,0);
					for(a=0;a<10;a++)
					{
						for(b=0;b<5;b++)
						{
							if(!reach[a+10*b])
							putimage_withalpha(NULL,img3,170+a*30,101+b*30,0,0);
						}
					}
					if(reach[i+10*j])
					putimage_withalpha(NULL,img2,170+i*30,101+j*30,0,0);
					if(1==(int)msg.is_down())
					{
						if(reach[i+10*j])
						{
							floor=i+10*j;
							return;
						}
					}
				}
			}
		}
		if(msg.x>(159+320-11)&&msg.x<(159+320)&&msg.y>(90)&&msg.y<(90+11)&&1==(int)msg.is_down())
		return;
		int k=0;
		if (kbhit()) 
		{
			k = getch();
			if(k==98)	
			return;
		}
	}
    delimage(img);
    delimage(img2);
    delimage(img3);
}
void Show()
{
	Showframe();
	ShowMap();
	ShowShop();
	ShowLeft();
	ShowRight();
	ShowWarrior();
	ShowGhost();
	ShowNpc();
	ShowItem();
}

void Showframe()
{
	PIMAGE img;
	img = newimage();
	getimage(img,"biankunag.png",0,0);
	putimage_withalpha(NULL,img,120,0,0,0);
	delimage(img);
}

int trans;		//���ڿ��ƹ���ȶ�����ʾ�ı��� 
void ShowMap()	//����ͼ 
{
	int i,j;
	PIMAGE img;
	img = newimage();
	getimage(img,"bg.png",0,0);
	for(i=0;i<11;i++)
	{
		for(j=0;j<11;j++)
		{
			if(map[floor][i][j].xbmp==1||map[floor][i][j].xbmp==3&&map[floor][i][j].ybmp==0)//������ҽ������� 
			{
				if(trans>10)
				showimg32(img,map[floor][i][j].x,map[floor][i][j].y,map[floor][i][j].xbmp,map[floor][i][j].ybmp+1);
				else
				showimg32(img,map[floor][i][j].x,map[floor][i][j].y,map[floor][i][j].xbmp,map[floor][i][j].ybmp);
			}
			else
			showimg32(img,map[floor][i][j].x,map[floor][i][j].y,map[floor][i][j].xbmp,map[floor][i][j].ybmp);
		}
	}
	delimage(img);
	trans++;
	if(trans>=20)
	trans=0;
 }
void ShowWarrior()//��ʾ����
{
	PIMAGE img;
	img = newimage();
	getimage(img,"warrior.png",0,0);
	showimg32(img,warrior.x,warrior.y,warrior.xbmp,warrior.ybmp);
	delimage(img);
}

void ShowGhost()//��ʾ����
{
	PIMAGE img;
	img = newimage();
	getimage(img,"ghost.png",0,0);
	int i;
	for(i=0;strcmp(monster[floor][i].name,"end");i++)
	{
		if(trans>10)
		showimg32(img,monster[floor][i].x,monster[floor][i].y,monster[floor][i].xbmp,monster[floor][i].ybmp);
		else
		showimg32(img,monster[floor][i].x,monster[floor][i].y,monster[floor][i].xbmp+1,monster[floor][i].ybmp);
	}
	delimage(img);
}

void ShowNpc()
{
	PIMAGE img;
	img = newimage();
	getimage(img,"npc.png",0,0);
	int i;
	for(i=0;strcmp(npc[floor][i].name,"end");i++)
	{
		if(trans>10)
		showimg32(img,npc[floor][i].x,npc[floor][i].y,npc[floor][i].xbmp,npc[floor][i].ybmp);
		else
		showimg32(img,npc[floor][i].x,npc[floor][i].y,npc[floor][i].xbmp+1,npc[floor][i].ybmp);
	}
	delimage(img);
}

void ShowShop()
{
	if(3==floor)
	{
		PIMAGE img;
		img = newimage();
		getimage(img,"shop.png",0,0);
		showimg32(img,4,0,0,0);
		if(trans>10)
		showimg32(img,5,0,1,0);
		else
		showimg32(img,5,0,3,0);
		showimg32(img,6,0,2,0);
		delimage(img);
	}
}
void ShowItem()//��ʾ������Ʒ
{
	PIMAGE img,img2;
	img = newimage();
	getimage(img,"item.png",0,0);
	int i;
	for(i=0;strcmp(item[floor][i].name,"end");i++)
	showimg32(img,item[floor][i].x,item[floor][i].y,item[floor][i].xbmp,item[floor][i].ybmp);
	delimage(img);	
	
	img2 = newimage();
	getimage(img2,"specialitem.png",0,0);
	for(i=0;strcmp(sitem[floor][i].name,"end");i++)
	showimg32(img2,sitem[floor][i].x,sitem[floor][i].y,sitem[floor][i].xbmp,sitem[floor][i].ybmp);
	delimage(img2);
} 
void ShowLeft()//��ʾ������Ϣ 
{
	char hp[20],atk[20],def[20],gold[20],level[20],exp[20],stairs[20];
	sprintf(hp,"%8d",warrior.hp); 
	sprintf(atk,"%8d",warrior.atk); 
	sprintf(def,"%8d",warrior.def);
	sprintf(gold,"%8d",warrior.gold);
	sprintf(level,"%8d",warrior.level);
	sprintf(exp,"%8d",warrior.exp);
	sprintf(stairs,"ħ�� ��%02d��",floor+1); 
	
	PIMAGE img;
	img = newimage(); 
	getimage(img,"left.png",0,0);
	setviewport(0,0,120,400,1);
	clearviewport();
	putimage_withalpha(NULL,img,0,0,0,0);
	setbkmode(TRANSPARENT);
	setcolor(EGERGB(0xFF,0xFF,0xFF));
	setfont(14,0,"����");
	
	outtextxy(50,70,hp);
	outtextxy(50,95,atk);
	outtextxy(50,119,def);
	outtextxy(50,143,gold);
	outtextxy(50,167,exp);
	outtextxy(50,191,level);
	outtextxy(19, 40, stairs);
	setviewport(0,0,getwidth(),getheight(),1);
	
	delimage(img);

	PIMAGE img2;
	img2 = newimage();
	getimage(img2,"specialitem.png",0,0);
	if(1==boost)
	{
		putimage_withalpha(NULL,img2,16,228,0,0,32,32);
	}
	if(1==book)
	{
		putimage_withalpha(NULL,img2,50,228,32,0,32,32);
	}
	delimage(img2);
}

void ShowRight()//��ʾ������Ϣ 
{
	
	char hp[20],atk[20],def[20],gold[20],level[20],exp[20],keyOrange[20],keyBlue[20],keyRed[20],str[20],stairs[20];

	sprintf(keyOrange,"%3d",warrior.ykey);
	sprintf(keyBlue,"%3d",warrior.bkey);
	sprintf(keyRed,"%3d",warrior.rkey);
	sprintf(str, "fps %.02f", getfps()); //����getfpsȡ�õ�ǰ֡��

	PIMAGE img;
	img = newimage(); 
	getimage(img,"right.png",0,0);
	setviewport(352+24+_x,0,640,400,1);
	clearviewport();
	putimage_withalpha(NULL,img,352+24+_x,0,0,0);
	setbkmode(TRANSPARENT);
	setcolor(EGERGB(0x00,0x00,0x00));
	outtextxy(0, 0, str);
	setfont(20,0,"����");
	
	setcolor(EGERGB(0xFF,0xFF,0xFF));
	outtextxy(65,170,keyOrange);
	outtextxy(65,200,keyBlue);
	outtextxy(65,230,keyRed);
	
	setviewport(0,0,getwidth(),getheight(),1);
	delimage(img);
}

BOOL JudgeMove(int key)//�жϰ������Ƿ����ƶ� 
{
	int x=warrior.x,y=warrior.y;
	switch(key)
	{
		case 293:{	
			if(x>0)
			x--;
			else
			return FALSE;
		}break;
		case 294:{
			if(y>0)
			y--;
			else
			return FALSE;
		}break;
		case 295:{
			if(x<10)
			x++;
			else
			return FALSE;
		} break;
		case 296:{
			if(y<10)
			y++;
			else
			return FALSE;
		}break;
	}
	Door(x,y);						//������������� 
	Item(x,y);						//����ǵ��� 
	SpecialItem(x,y);				//������� 
	
	if(!Shop(x,y))					//��������̵�
	return FALSE;
	if(!Monster(x,y))				//����ǹ��� 
	return FALSE;
	if(!Npc(x,y))
	return FALSE;
	if(map[floor][y][x].xbmp==2||map[floor][y][x].xbmp==0&&map[floor][y][x].ybmp==0)	//��������ǵذ��¥�� 	
	{
		return TRUE;
	}
	return FALSE;
} 
BOOL Npc(int x,int y)
{
	int i;
	for(i=0;strcmp(npc[floor][i].name,"end");i++)
	{
		if(npc[floor][i].xbmp!=-2&&npc[floor][i].x==x&&npc[floor][i].y==y)
		{
			return FALSE;
		}
	}
	return TRUE;
} 
BOOL Monster(int x,int y)
{
	int i;
	for(i=0;strcmp(monster[floor][i].name,"end");i++)
	{
		if(monster[floor][i].xbmp!=-2&&monster[floor][i].x==x&&monster[floor][i].y==y)
		{
			if(!fight(x,y))
			return FALSE;
		}
	}
	return TRUE;
}
void Item(int x,int y)//�ƶ�����������
{
	int i;
	for(i=0;strcmp(item[floor][i].name,"end");i++)
	{
		if(item[floor][i].xbmp!=-1&&item[floor][i].x==x&&item[floor][i].y==y)
		{
			item[floor][i].xbmp=-1;
			warrior.hp+=(floor/10+1)*item[floor][i].hp;
			warrior.atk+=item[floor][i].atk;
			warrior.def+=item[floor][i].def;
			warrior.ykey+=item[floor][i].ykey;
			warrior.bkey+=item[floor][i].bkey;
			warrior.rkey+=item[floor][i].rkey;
		}
	}
}
void SpecialItem(int x,int y)
{
	int i;
	for(i=0;strcmp(sitem[floor][i].name,"end");i++)
	{
		if(sitem[floor][i].xbmp!=-1&&sitem[floor][i].x==x&&sitem[floor][i].y==y)
		{
			sitem[floor][i].xbmp=-1;
			if(!strcmp(sitem[floor][i].name,"���ͷ���"))
			boost=1;
		}
	}
}
BOOL Shop(int x,int y)
{
	if(3==floor)
	{
		if((x==4||x==5||x==6)&&y==0)
		{
			//Shoping();
			return FALSE;	
		}
	}
	return TRUE; 
} 
void Door(int x,int y)//�ƶ��������� 
{
	switch(map[floor][y][x].xbmp){
		case 4:{
		if(warrior.ykey>0)
		{
			OpenDoor(x,y,4);
			warrior.ykey--;
		}
		}break;
		case 5:{
		if(warrior.bkey>0)
		{
			OpenDoor(x,y,5);
			warrior.bkey--;
		}
		}break;
		case 6:{
		if(warrior.rkey>0)
		{
			OpenDoor(x,y,6);
			warrior.rkey--;
		}
		}break;
		case 7:
		{
			OpenDoor(x,y,7);
		}break;
	}
}
int time=0;
void OpenDoor(int x,int y,int kind) //���� 
{
	int i;
	PIMAGE img;
	img = newimage();
	getimage(img,"bg.png",0,0);
	for(i=0;i<4;)
	{	
		Show();
		showimg32(img,x,y,kind,i);
		delay_fps(60);
		time++;
		if(time==5)
		{
			time=0;
			i++;
		}
	}
	map[floor][y][x].xbmp=0,map[floor][y][x].ybmp=0; //�����ź��Ÿ�Ϊ�ذ� 
	delimage(img);
}
BOOL fight(int x,int y) //ս��
{	

	int i,hpA,hpB,atkA=0,atkB=0;
	for(i=0;strcmp(monster[floor][i].name,"end");i++)
	{
		if(monster[floor][i].x==x&&monster[floor][i].y==y)
		break;
	}
	hpA=warrior.hp;
 	hpB=monster[floor][i].hp;
 	while(warrior.atk>monster[floor][i].def&&hpA>0&&hpB>0)
 	{	
		hpB-=(warrior.atk-monster[floor][i].def);
		if(hpB>0&&monster[floor][i].atk>warrior.def)
 		{
	 		hpA-=(monster[floor][i].atk-warrior.def);
 		}
 	}
	if(hpA<=0||warrior.atk<monster[floor][i].def)//���ܴ�ܹ��� 
	return FALSE; 
	else	//�ܹ���� 
	{	
		hpA=warrior.hp;
	 	hpB=monster[floor][i].hp;
	 	while(hpA>0&&hpB>0)
	 	{	
			hpB-=(warrior.atk-monster[floor][i].def);
			int j=0;
	 		for (;j<10;delay_fps(60))
	 		{
			Show();
			ShowFight(x,y);
			j++;
	 		}
			if(hpB>0&&monster[floor][i].atk>warrior.def)
	 		{
		 		hpA-=(monster[floor][i].atk-warrior.def);
		 		warrior.hp=hpA;
	 		}
	 		if(hpB>0)
	 		{
		 		j=0;
		 		for ( ; j<10; delay_fps(60) )
		 		{
			 	Show();
		 		ShowFight(warrior.x,warrior.y);
		 		j++;
				}
	 		}
	 	}
		Show();
		warrior.hp=hpA;
		warrior.exp+=monster[floor][i].exp;
		warrior.gold+=monster[floor][i].gold;
		monster[floor][i].xbmp=-2;
		return TRUE;
	}
}
void ShowFight(int x,int y)
{
	PIMAGE img;
	img = newimage();
	getimage(img,"bg.png",0,0);
	showimg32(img,x,y,0,3);
	
	delimage(img);
}

void Save()
{
	FILE *out;
	char ch;
	int i=0,j=0,k=0;

	if((out = fopen("save.dat","w")) == NULL)
	{
		printf("��Ŀ���ļ�����\n");
		exit(1);
	}
	//���ǲ��� 
	fprintf(out,"warrior.x=%d warrior.y=%d floor=%d\n",warrior.x,warrior.y,floor);
	fprintf(out,"level=%d gold=%d exp=%d\n",warrior.level,warrior.gold,warrior.exp);
	fprintf(out,"hp=%d atk=%d def=%d\n",warrior.hp,warrior.atk,warrior.def);
	fprintf(out,"rkey=%d bkey=%d ykey=%d\n",warrior.rkey,warrior.bkey,warrior.ykey);
	//���ﲿ�� 
	for(i=0;strcmp(monster[i][j].name,"endghost");i++)
	{
		for(j=0;strcmp(monster[i][j].name,"end");j++)
		{
			fprintf(out,"%d ",monster[i][j].xbmp);	
		}
	} 
	//��ͼ���� 
	for(k=0;k<50;k++)
	{
		for(i=0;i<11;i++)
		{
			for(j=0;j<11;j++)
			{
				fprintf(out,"%d ",map[k][i][j].xbmp);
				fprintf(out,"%d ",map[k][i][j].ybmp);
			}
		}
	} 
	//���� 
	for(i=0;strcmp(item[i][j].name,"enditem");i++)
	{
		for(j=0;strcmp(item[i][j].name,"end");j++)
		{
			fprintf(out,"%d ",item[i][j].xbmp);	
		}
	} 
	//����
 	for(i=0;i<4;i++)
 	fprintf(out,"%d ",p[i]);
 	//npc
	fprintf(out,"%d %d %d ",npc[1][0].x,npc[1][0].y,npc[1][0].ybmp);
	//�������
 	fprintf(out,"%d %d ",boost,book);
	fclose(out);
}
void Load()
{
	FILE *out;
	char ch;
	int i=0,j=0,k=0;

	if((out = fopen("save.dat","r")) == NULL)
	{
		printf("��Ŀ���ļ�����\n");
		exit(1);
	}
	//���ǲ��� 
	fscanf(out,"warrior.x=%d warrior.y=%d floor=%d\n",&warrior.x,&warrior.y,&floor);
	fscanf(out,"level=%d gold=%d exp=%d\n",&warrior.level,&warrior.gold,&warrior.exp);
	fscanf(out,"hp=%d atk=%d def=%d\n",&warrior.hp,&warrior.atk,&warrior.def);
	fscanf(out,"rkey=%d bkey=%d ykey=%d\n",&warrior.rkey,&warrior.bkey,&warrior.ykey);
	//���ﲿ�� 
	for(i=0;strcmp(monster[i][j].name,"endghost");i++)
	{
		for(j=0;strcmp(monster[i][j].name,"end");j++)
		{
			fscanf(out,"%d ",&monster[i][j].xbmp);	
		}
	} 
	//��ͼ���� 
	for(k=0;k<50;k++)
	{
		for(i=0;i<11;i++)
		{
			for(j=0;j<11;j++)
			{
				fscanf(out,"%d ",&map[k][i][j].xbmp);
				fscanf(out,"%d ",&map[k][i][j].ybmp);
			}
		}
	} 
	//���� 
	for(i=0;strcmp(item[i][j].name,"enditem");i++)
	{
		for(j=0;strcmp(item[i][j].name,"end");j++)
		{
			fscanf(out,"%d ",&item[i][j].xbmp);	
		}
	} 
	//����
 	for(i=0;i<4;i++)
 	fscanf(out,"%d ",&p[i]);
 	//npc
	fscanf(out,"%d %d %d ",&npc[1][0].x,&npc[1][0].y,&npc[1][0].xbmp);
	//�������
 	fscanf(out,"%d %d ",&boost,&book);
	fclose(out);
}

void showimg32(PIMAGE img,int x,int y,int ximg,int yimg)  //�������ʾ���� 
{
	putimage_withalpha(NULL,img,(x*32)+_x,(y*32)+_y,ximg*32,yimg*32,32,32);
}
