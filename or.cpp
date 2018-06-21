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
        cout<<"          ������           "<<endl; 
        cout<<"---------------------------"<<endl;
        cout<<"����Ϸ��˫�������壬�����˻�"<<endl; 
        cout<<"���롰S����ʼ��Ϸ"<<endl;
        cout<<"���롰?����ȡ����"<<endl;
    }
    if(i==2) 
    {
        cout<<"---------------------------"<<endl;
        cout<<"            ָ��"<<endl;
        cout<<"---------------------------"<<endl;
        cout<<"����������"<<endl;
        cout<<"��N x y   ������������(x,y)λ�á�"<<endl;
        cout<<"ע�⣺����ʱ������10�������ꡣ(A=10,F=15)"<<endl;
        cout<<"��A ָ�� n�����������ڵ�ǰ���Ӹ���n����λ"<<endl;
        cout<<"ָ��: R-�Ҳ�  L-���  U-�Ϸ�  D-�·�"<<endl;
        cout<<"RD-���� RU-���� LD-���� LU-����"<<endl; 
        cout<<"����:A R 1�����������ڵ�ǰ���� �Ҳ� 1 ����λ"<<endl;
        cout<<" A LD 3:���������ڵ�ǰ�������·� 3 ����λ"<<endl; 
        cout<<"tips:����ʱ����������һ��nΪ0��ָ����������������"<<endl; 
        cout<<"         ����: A L 0"<<endl; 
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
                    cout<<"��";
                    break;
                case 1:
                    cout<<"��";
                    break;
                case 2:
                    cout<<"�e";
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

void dfs1(int x,int y,int fx)//0 ���� 1 ���� 2 ��  3�� 
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
	system("title ZYoung������");//���ñ���
	system("mode con cols=33 lines=19");//���ô��ڴ�С
	system("color B2");//������ɫ
    resetAll();
    print();
    while(1)
    {

    int input;//�������
    input=getch();//�ȴ����̰���һ���ַ�
        oldx=x;oldy=y;
        if(input==27)
        {
            
            exit(0);
        }
         else if(input==0xE0)//������µ��Ƿ������������������룬��һ��Ϊ0xE0��ʾ���µ��ǿ��Ƽ�
				{
				input=getch();//��õڶ���������Ϣ
					switch(input)//�жϷ���������ƶ����λ��
										{
case 0x4B:y--;clr;print();cout<<x<<","<<y<<endl;break;
case 0x48:x--;clr;print();cout<<x<<","<<y<<endl;break;
case 0x4D:y++;clr;print();cout<<x<<","<<y<<endl;break;
case 0x50:x++;clr;print();cout<<x<<","<<y<<endl;break;
 }
				}
        
        
        
        
        
        else if(input==0x20)//����ǿո���ʼ����
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
                    string winner=!isBlack?"����":"����";
                    cout<<winner<<"���ʤ����"<<endl<<"�Ƿ����¿�ʼ?(����Y/N)";
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
            cout<<"���������������ӡ�"<<endl;
            x=oldx;y=oldy;
            continue;
        }

}
    }
    return 0;
    
}


