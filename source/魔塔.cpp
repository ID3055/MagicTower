#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "map.cpp"					//地图数据 
#include "warrior.cpp"				//主角数据 
#include "ghost.cpp"				//怪物数据 
#include "item.cpp"					//道具数据 
#include "SpecialItem.cpp"			//特殊道具
#include "npc.cpp"					//NPC

mouse_msg msg = {0};				//鼠标信息存储变量

void menu();						//开始游戏菜单

void Button();						//游戏主界面内鼠标检测

void showimg32(PIMAGE img,int x,int y,int ximg,int yimg); //在游戏主界面显示32*32图像
void Show();						//显示全部元素汇总

void ShowMap();						//显示地图
void ShowWarrior();					//显示主角 
void ShowGhost(); 					//显示怪物 
void ShowNpc();						//显示NPC
void ShowItem();					//显示道具
void ShowShop();					//显示商店
void ShowLeft();					//显示左栏
void ShowRight();					//显示右栏
void ShowFight(int x,int y);		//战斗画面
void Showframe();					//边框

void Boost();						//楼层传送
void choice();						//楼层传送选择框

void Move();						//移动
BOOL JudgeMove(int key);			//按键时判断移动
void Item(int x,int y);				//碰到道具时
void SpecialItem(int x,int y);		//碰到特殊道具
BOOL Shop(int x,int y);				//遇到商店
void Door(int x,int y);				//碰到门时
void OpenDoor(int x,int y,int kind);//开门
BOOL Npc(int x,int y);				//npc
BOOL Monster(int x,int y);			//碰到怪物时
BOOL fight(int x,int y);			//战斗判定
void stair();						//变更楼层后主角位置

void Mouse();
void TextBox(char *str);			//显示剧情对话框 

void plot();						//剧情汇总
 
void plot1();						//具体剧情 
void plot2();
void plot3();
void plot4();

void Save();						//存档 
void Load();				 		//读档 

int floor=0;						//当前楼层 

#define _x 144						//游戏主界面偏移量 
#define _y 24

int WinMain()						//主函数 
{
	initgraph(640, 400);
	setrendermode(RENDER_MANUAL);
	setcaption("魔塔 v0.2");

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
void plot()							//剧情 
{
	plot1();
	plot2();
	plot3();
	plot4();
}
void Button()						//界面内鼠标按键 
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
void plot1()		//剧情 
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
			for (;1;delay_fps(60))	//魔王出现 
			{
				Show();
				putimage_alphatransparent(NULL, img, (4*32)+_x, (6*32)+_y, BLACK, (unsigned char)alpha,(6*32),(3*32),32,32);
				if (alpha < 0xFE)
				alpha += 2;
				if (alpha >= 0xFE) 	//魔王显形完毕后 
				{
					char str[]="魔王 Zeno 说：“欢迎来到魔塔，你是第一百位挑战者。你若能打败我所有的手下，我就与你一对一的决斗。现在你必须接受我的安排。";
					TextBox(str);
					if (kbhit())
					break;
				}
			}
			for (;1;delay_fps(60))	//魔王手下出现 
			{
				Show();
				putimage_alphatransparent(NULL, img, (4*32)+_x, (6*32)+_y, BLACK, (unsigned char)alpha,6*32,3*32,32,32);
				putimage_alphatransparent(NULL, img, (3*32)+_x, (8*32)+_y, BLACK, (unsigned char)alpha2,8*32,3*32,32,32);
				putimage_alphatransparent(NULL, img, (4*32)+_x, (7*32)+_y, BLACK, (unsigned char)alpha2,8*32,3*32,32,32);
				putimage_alphatransparent(NULL, img, (5*32)+_x, (8*32)+_y,BLACK, (unsigned char)alpha2,8*32,3*32,32,32);
				putimage_alphatransparent(NULL, img, (4*32)+_x, (9*32)+_y, BLACK, (unsigned char)alpha2,8*32,3*32,32,32);
				
				if (alpha2 < 0xFE)
				alpha2 += 2;
				
				if (alpha2 >= 0xFE) //魔王手下显形完毕后 
				{
					char str[]="啊？！~~";
					TextBox(str);
					if (i=kbhit())		//此处有bug，判定未生效，且程序会阻塞此处，直到有任意按键 
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
			char str[]="你清醒了吗？你到监狱时还处在昏迷中，魔法警卫把你扔到我这个房间。但你很幸运，我刚完成逃跑的暗道你就醒了，我们一起越狱吧。";
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
			char str[]="    我们终于逃出来了。你的剑和盾被警卫拿走了，你必须先找到武器。我知道铁剑在5楼，铁盾在9楼，你最好先取到它们。我现在有事要做没法帮你，再见。";
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
	setfont(16,0,"宋体");
	outtextrect(170,101,298,158,str);
	delimage(img);
} 
void Move()		//移动 
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
	if(map[floor][warrior.y][warrior.x].xbmp==2)//如果移动后是楼梯 
	stair();
}
void stair()
{
	int x=warrior.x,y=warrior.y;	
	if(map[floor][y][x].ybmp==0)		//如果是向上的楼梯 
	floor++;
	else if(map[floor][y][x].ybmp==1)	//如果是向下的楼梯
	floor--;
	
	reach[floor]=1;
	
	//使主角改变楼层后离开楼梯 
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
void Boost()//传送法杖 
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

int trans;		//用于控制怪物等动作显示的变量 
void ShowMap()	//画地图 
{
	int i,j;
	PIMAGE img;
	img = newimage();
	getimage(img,"bg.png",0,0);
	for(i=0;i<11;i++)
	{
		for(j=0;j<11;j++)
		{
			if(map[floor][i][j].xbmp==1||map[floor][i][j].xbmp==3&&map[floor][i][j].ybmp==0)//如果是岩浆或星星 
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
void ShowWarrior()//显示主角
{
	PIMAGE img;
	img = newimage();
	getimage(img,"warrior.png",0,0);
	showimg32(img,warrior.x,warrior.y,warrior.xbmp,warrior.ybmp);
	delimage(img);
}

void ShowGhost()//显示怪物
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
void ShowItem()//显示道具物品
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
void ShowLeft()//显示主角信息 
{
	char hp[20],atk[20],def[20],gold[20],level[20],exp[20],stairs[20];
	sprintf(hp,"%8d",warrior.hp); 
	sprintf(atk,"%8d",warrior.atk); 
	sprintf(def,"%8d",warrior.def);
	sprintf(gold,"%8d",warrior.gold);
	sprintf(level,"%8d",warrior.level);
	sprintf(exp,"%8d",warrior.exp);
	sprintf(stairs,"魔塔 第%02d层",floor+1); 
	
	PIMAGE img;
	img = newimage(); 
	getimage(img,"left.png",0,0);
	setviewport(0,0,120,400,1);
	clearviewport();
	putimage_withalpha(NULL,img,0,0,0,0);
	setbkmode(TRANSPARENT);
	setcolor(EGERGB(0xFF,0xFF,0xFF));
	setfont(14,0,"宋体");
	
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

void ShowRight()//显示主角信息 
{
	
	char hp[20],atk[20],def[20],gold[20],level[20],exp[20],keyOrange[20],keyBlue[20],keyRed[20],str[20],stairs[20];

	sprintf(keyOrange,"%3d",warrior.ykey);
	sprintf(keyBlue,"%3d",warrior.bkey);
	sprintf(keyRed,"%3d",warrior.rkey);
	sprintf(str, "fps %.02f", getfps()); //调用getfps取得当前帧率

	PIMAGE img;
	img = newimage(); 
	getimage(img,"right.png",0,0);
	setviewport(352+24+_x,0,640,400,1);
	clearviewport();
	putimage_withalpha(NULL,img,352+24+_x,0,0,0);
	setbkmode(TRANSPARENT);
	setcolor(EGERGB(0x00,0x00,0x00));
	outtextxy(0, 0, str);
	setfont(20,0,"宋体");
	
	setcolor(EGERGB(0xFF,0xFF,0xFF));
	outtextxy(65,170,keyOrange);
	outtextxy(65,200,keyBlue);
	outtextxy(65,230,keyRed);
	
	setviewport(0,0,getwidth(),getheight(),1);
	delimage(img);
}

BOOL JudgeMove(int key)//判断按键后是否能移动 
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
	Door(x,y);						//如果碰到的是门 
	Item(x,y);						//如果是道具 
	SpecialItem(x,y);				//特殊道具 
	
	if(!Shop(x,y))					//如果遇到商店
	return FALSE;
	if(!Monster(x,y))				//如果是怪物 
	return FALSE;
	if(!Npc(x,y))
	return FALSE;
	if(map[floor][y][x].xbmp==2||map[floor][y][x].xbmp==0&&map[floor][y][x].ybmp==0)	//如果仅仅是地板或楼梯 	
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
void Item(int x,int y)//移动若遇到道具
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
			if(!strcmp(sitem[floor][i].name,"传送法杖"))
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
void Door(int x,int y)//移动若遇到门 
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
void OpenDoor(int x,int y,int kind) //开门 
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
	map[floor][y][x].xbmp=0,map[floor][y][x].ybmp=0; //开完门后将门改为地板 
	delimage(img);
}
BOOL fight(int x,int y) //战斗
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
	if(hpA<=0||warrior.atk<monster[floor][i].def)//不能打败怪物 
	return FALSE; 
	else	//能够打败 
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
		printf("打开目标文件错误\n");
		exit(1);
	}
	//主角部分 
	fprintf(out,"warrior.x=%d warrior.y=%d floor=%d\n",warrior.x,warrior.y,floor);
	fprintf(out,"level=%d gold=%d exp=%d\n",warrior.level,warrior.gold,warrior.exp);
	fprintf(out,"hp=%d atk=%d def=%d\n",warrior.hp,warrior.atk,warrior.def);
	fprintf(out,"rkey=%d bkey=%d ykey=%d\n",warrior.rkey,warrior.bkey,warrior.ykey);
	//怪物部分 
	for(i=0;strcmp(monster[i][j].name,"endghost");i++)
	{
		for(j=0;strcmp(monster[i][j].name,"end");j++)
		{
			fprintf(out,"%d ",monster[i][j].xbmp);	
		}
	} 
	//地图部分 
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
	//道具 
	for(i=0;strcmp(item[i][j].name,"enditem");i++)
	{
		for(j=0;strcmp(item[i][j].name,"end");j++)
		{
			fprintf(out,"%d ",item[i][j].xbmp);	
		}
	} 
	//剧情
 	for(i=0;i<4;i++)
 	fprintf(out,"%d ",p[i]);
 	//npc
	fprintf(out,"%d %d %d ",npc[1][0].x,npc[1][0].y,npc[1][0].ybmp);
	//特殊道具
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
		printf("打开目标文件错误\n");
		exit(1);
	}
	//主角部分 
	fscanf(out,"warrior.x=%d warrior.y=%d floor=%d\n",&warrior.x,&warrior.y,&floor);
	fscanf(out,"level=%d gold=%d exp=%d\n",&warrior.level,&warrior.gold,&warrior.exp);
	fscanf(out,"hp=%d atk=%d def=%d\n",&warrior.hp,&warrior.atk,&warrior.def);
	fscanf(out,"rkey=%d bkey=%d ykey=%d\n",&warrior.rkey,&warrior.bkey,&warrior.ykey);
	//怪物部分 
	for(i=0;strcmp(monster[i][j].name,"endghost");i++)
	{
		for(j=0;strcmp(monster[i][j].name,"end");j++)
		{
			fscanf(out,"%d ",&monster[i][j].xbmp);	
		}
	} 
	//地图部分 
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
	//道具 
	for(i=0;strcmp(item[i][j].name,"enditem");i++)
	{
		for(j=0;strcmp(item[i][j].name,"end");j++)
		{
			fscanf(out,"%d ",&item[i][j].xbmp);	
		}
	} 
	//剧情
 	for(i=0;i<4;i++)
 	fscanf(out,"%d ",&p[i]);
 	//npc
	fscanf(out,"%d %d %d ",&npc[1][0].x,&npc[1][0].y,&npc[1][0].xbmp);
	//特殊道具
 	fscanf(out,"%d %d ",&boost,&book);
	fclose(out);
}

void showimg32(PIMAGE img,int x,int y,int ximg,int yimg)  //打包的显示函数 
{
	putimage_withalpha(NULL,img,(x*32)+_x,(y*32)+_y,ximg*32,yimg*32,32,32);
}
