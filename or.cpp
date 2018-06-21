/*
 --------------------------------
 *        c++ code              *
 * costom by ZYoung 2018/06/09  *
 --------------------------------
*/
#include <iostream>
#include <conio.h>

#define clr system("cls")
#define inside(x,y) ((x>0)&&(y>0)&&(x<16)&&(y<16))

using namespace std;

int pan[16][16],nums[4],x,y,oldx,oldy;
bool isBlack;

void instruction(int i)
{
    if(i==1) 
    {
        cout<<"          五子棋           "<<endl; 
        cout<<"---------------------------"<<endl;
        cout<<"本游戏是双人五子棋，不是人机"<<endl; 
        cout<<"输入“S”开始游戏"<<endl;
        cout<<"输入“?”获取帮助"<<endl;
    }
    if(i==2) 
    {
        cout<<"---------------------------"<<endl;
        cout<<"            指令"<<endl;
        cout<<"---------------------------"<<endl;
        cout<<"操作方法："<<endl;
        cout<<"·N x y   ：将棋子下在(x,y)位置。"<<endl;
        cout<<"注意：输入时请输入10进制坐标。(A=10,F=15)"<<endl;
        cout<<"·A 指令 n：将棋子下在当前棋子附近n个单位"<<endl;
        cout<<"指令: R-右侧  L-左侧  U-上方  D-下方"<<endl;
        cout<<"RD-右下 RU-右上 LD-左下 LU-左上"<<endl; 
        cout<<"例子:A R 1：将棋子下在当前棋子 右侧 1 个单位"<<endl;
        cout<<" A LD 3:将棋子下在当前棋子左下方 3 个单位"<<endl; 
        cout<<"tips:开局时可随意输入一个n为0的指令在棋盘中央下棋"<<endl; 
        cout<<"         例如: A L 0"<<endl; 
    }
}

char makech(int n)
{
    if(n<10)
        return (char)n+48;
    return (char)n+55;
}

void print()
{
    cout<<"   ";
    for(int i=1;i<16;i++)
        cout<<makech(i)<<" ";
    cout<<endl<<"  ------------------------------"<<endl;
    for(int i=1;i<16;i++)
    {
        for(int j=1;j<16;j++)
        {
            if(j==1)
                cout<<makech(i)<<"| ";
            switch(pan[i][j])
            {
                case 9:
                    cout<<"- ";
                    break;
                case 0:
                    cout<<"●";
                    break;
                case 1:
                    cout<<"○";
                    break;
                case 2:
                    cout<<"卐";
                    break;
            }
        }
        cout<<endl;
    }
}

void dfs2(int x,int y,int fx)
{
    int trues=isBlack?1:0;
    if(pan[x][y]==trues)
        {nums[fx]++; }
    else
        {return;}
    switch(fx)
    {
        case 0:
            if(inside(x+1,y))
                {dfs2(x+1,y,0);}
            else
                {return;}
            break;
        case 1:
            if(inside(x,y+1))
                {dfs2(x,y+1,1);}
            else
                {return;}
            break;
        case 2:
            if(inside(x+1,y+1))
                {dfs2(x+1,y+1,2);}
            else
                {return;}
            break;
        case 3:
            if(inside(x+1,y-1))
                {dfs2(x+1,y-1,3);}
            else
                {return;}
            break;
    }
}

void dfs1(int x,int y,int fx)//0 上下 1 左右 2 ＼  3／ 
{
    int trues=isBlack?1:0;
    switch(fx)
    {
        case 0:
            if((pan[x-1][y]==trues)&&inside(x-1,y))
            {
                dfs1(x-1,y,0);
                return;
            }else
            {
                dfs2(x,y,0);
            }
            break;
        case 1:
            if((pan[x][y-1]==trues)&&inside(x,y-1))
            {
                dfs1(x,y-1,1);
                return;
            }else
            {
                dfs2(x,y,1);
            }
            break;
        case 2:
            if((pan[x-1][y-1]==trues)&&inside(x-1,y-1))
            {
                dfs1(x-1,y-1,2);
                return;
            }else
            {
                dfs2(x,y,2);
            }
            break;
        case 3:
            if((pan[x-1][y+1]==trues)&&inside(x-1,y+1))
            {
                dfs1(x-1,y+1,3);
                return;
            }else
            {
                dfs2(x,y,3);
            }
            break;
    }
}

void resetAll()
{
    for(int i=1;i<16;i++)
        for(int j=1;j<16;j++)
            pan[i][j]=9;
    x=8;
    y=8;
    isBlack=true;
}

int main()
{
	system("title ZYoung五子棋");//设置标题
	system("mode con cols=33 lines=19");//设置窗口大小
	system("color B2");//设置颜色
    resetAll();
    print();
    while(1)
    {

    int input;//输入变量
    input=getch();//等待键盘按下一个字符
        oldx=x;oldy=y;
        if(input==27)
        {
            
            exit(0);
        }
         else if(input==0xE0)//如果按下的是方向键，会填充两次输入，第一次为0xE0表示按下的是控制键
				{
				input=getch();//获得第二次输入信息
					switch(input)//判断方向键方向并移动光标位置
										{
case 0x4B:y--;clr;print();cout<<x<<","<<y<<endl;break;
case 0x48:x--;clr;print();cout<<x<<","<<y<<endl;break;
case 0x4D:y++;clr;print();cout<<x<<","<<y<<endl;break;
case 0x50:x++;clr;print();cout<<x<<","<<y<<endl;break;
 }
				}
        
        
        
        
        
        else if(input==0x20)//如果是空格则开始走子
{
        if((inside(x,y))&&(pan[x][y]==9) )
        {
            pan[x][y]=(isBlack)?1:0;
            clr;
            print();
            for(int i=0;i<4;i++)
            {
                nums[i]=0;
                dfs1(x,y,i);
                if(nums[i]>=5)
                {
                    string winner=!isBlack?"白棋":"黑棋";
                    cout<<winner<<"获得胜利！"<<endl<<"是否重新开始?(输入Y/N)";
                    string temp;cin>>temp;
                    if(temp=="Y") 
                    {
                        resetAll();
                        continue;
                    }else{break;}
                }
            }
            isBlack=!isBlack;
            continue;
        }else
        {
            cout<<"坐标错误或已有棋子。"<<endl;
            x=oldx;y=oldy;
            continue;
        }

}
    }
    return 0;
    
}


