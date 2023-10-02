#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
#include<math.h>
#include<cstdio>
#include<iomanip>
#include<polarity.h>
#include<vector>
#include<fstream>
#include<windows.h>
#include<stdio.h>

using namespace std;

typedef long long ll;

//用户结构体
struct USER
{
    ll user_id;//用户的编号
    string user_name;//用户的姓名
    string user_account;//用户的账户
    string user_passwd;//用户的密码
    ll user_Permissions;//用户的权限 0为最高，1为读写，2为只读
}user[1010];

//目录及文件结构体
struct DF//Directories and files -> 目录及文件
{
    char df_name[1010];//目录及文件的名字
    char df_main[1010];//文件的内容
    struct DF* df_father;//父目录
    struct DF* df_next;//同级下一个目录
    struct DF* df_front;//同级上一个目录
    struct DF* df_son_0;//第一个子目录或子文件
    struct DF* df_son_1;//最后一个子目录或子文件
    ll df_type;//df的类型:目录为 0 | 文本为 1
    ll df_Permissions;//目录及文件的权限
};



void solving_0();
void init_0();
void init_directory();
void init_user();
int end();
void user_login();
void user_enroll();
void solving_1();
void gin_DF(DF* temp_df);
void ret_DF(DF* temp_df);
void get_DF(DF* temp_df);
void init_directory();
void init_df_0(DF* df_now);
void init_DF(DF* temp_df);
void init_1();
void mak_DF();
void init_2();
void solving_2();

ll user_num;//设定用户总数
ll choice_0;//第一初始界面的选择
ll temp_id;//临时编号
string temp_name;//临时姓名
string temp_account;//临时账户
string temp_passwd;//临时密码
ll temp_Permissions;//临时权限
ll choice_1;//第二初始界面的选择
DF* df,* df_now;//提前定义结构体df全局变量
ll choice_2;//第三初始界面的选择
ll choice_3;//增加文本类型的选择
bool st_choice_3=true;//表示文本类型选择的正确性
bool st_del=false;//表示删除文本是否查询到
bool st_gin_3=true;//表示删除文本是否查询到

//由于所有的登录失败的可能全部去掉，那么剩下的就只剩下成功的可能，所以不需要记录是否成功
//bool st_login=false;//定义记录是否登录成功的变量

//初始化最高特权用户
void init_user()
{
    user_num=1;
    user[1].user_id=1;
    user[1].user_name="寒枫";
    user[1].user_account="root";
    user[1].user_passwd="123456";
    user[1].user_Permissions=0;
}

//第一初始界面->用户登录|注册1
void init_0()
{
    cout<<"1.登录"<<endl;
    cout<<"2.注册"<<endl;
    cout<<"3.退出"<<endl;
    cout<<"请输入要进行的选项：";
}

//第一初始界面->选项2
void solving_0()
{
    cin>>choice_0;
    system("cls");
    switch(choice_0)
    {
        case 1://用户登录
            user_login();
            break;
        case 2://用户注册
            user_enroll();
            break;
        case 3://退出系统
            end();
    }
}

//系统退出
int end()
{
    cout<<"感谢使用，再见！"<<endl;
    exit(0);
}

//用户登录
void user_login()
{

    bool st_account_0=true;//定义死循环，直到用户登录成功|三次登录失败，否则重新输入账户
    bool st_passwd_0=true;//定义死循环，直到用户登录成功|三次登录失败,否则重新输入密码
    ll login_account_num=0;//记录账户错误的次数
    ll login_num=0;//记录密码错误的次数
    while(st_account_0)
    {
        cout<<"请输入账户:";
        cin>>temp_account;
        for(ll i=1;i<=user_num;i++)
        {
            if(user[i].user_account==temp_account)
            {
                st_account_0=false;//更新已经查询到账户
                while(st_passwd_0)
                {
                    cout<<"请输入密码:";
                    cin>>temp_passwd;
                    if(user[i].user_passwd==temp_passwd)
                    {
                        st_passwd_0=false;
                        temp_id=i;
                        temp_name=user[i].user_name;
                        temp_Permissions=user[i].user_Permissions;//更新临时权限为当前用户的权限
                        system("cls");
                        //st_login=true;//记录成功登录
                        cout<<"登录成功！\n欢迎 "<<temp_name<<endl;
                        //st_passwd_0=false;//更新账户密码正确
                        break;
                    }
                    else
                    {
                        login_num++;
                        if(login_num==3)
                        {
                            cout<<"您已连续三次登录失败，系统将关闭"<<"\n"<<"如需使用，请重新进入！"<<endl;
                            system("pause");
                            end();
                        }
                        else 
                        {
                            cout<<"密码错误！请重新输入！"<<endl;
                        }
                    }
                }
            }
        }
        login_account_num++;//账户不存在，更新登录的失败次数
        if(login_account_num==3)
        {
            cout<<"您已连续三次登录失败，系统将关闭"<<"\n"<<"如需使用，请重新进入！"<<endl;
            system("pause");
            end();
        }
        else if(st_passwd_0)//如果密码仍为未查询到的状态，代表账户不存在
        {
            cout<<"账户不存在！请重新输入！"<<endl;
            system("pause");
            system("cls");
        }
    }
}


//用户注册
void user_enroll()
{
    user_num++;//更新用户总数

    cout<<"请输入姓名:";
    cin>>user[user_num].user_name;
    cout<<"请输入账户:";
    cin>>user[user_num].user_account;
    cout<<"请输入密码:";
    cin>>user[user_num].user_passwd;

    user[user_num].user_id=user_num;//初始化新用户的编号
    user[user_num].user_Permissions=2;//初始化新用户的特权为2

    //更新临时用户的所有资料
    temp_account=user[user_num].user_account;
    temp_id=user[user_num].user_id;
    temp_name=user[user_num].user_name;
    temp_passwd=user[user_num].user_passwd;
    temp_Permissions=user[user_num].user_Permissions;

    system("cls");
    cout<<"登录成功！\n欢迎 "<<temp_name<<endl;
    //st_login=true;//更新登录成功

}

/*
    以上是第一初始界面->用户登录|注册问题的所以相关程序
*/

//第二初始界面->文件管理系统的操作
void init_1()
{
    cout<<"*******************************"<<endl;
    cout<<"**********文件管理系统*********"<<endl;
    cout<<"*******************************"<<endl;
    cout<<"1.查看当前目录下的内容"<<endl;
    cout<<"2.返回父目录"<<endl;
    cout<<"3.进入子目录"<<endl;
    cout<<"4.在当前目录下进行操作"<<endl;
    cout<<"5.退出系统"<<endl;
}

//初始化DF根目录
void init_DF(DF* temp_df)
{
    DF* t=temp_df;
    strcpy(t->df_name, "bin");
    t->df_father=NULL;
    t->df_front=NULL;
    t->df_next=NULL;
    t->df_Permissions=3;
    t->df_type=0;
    t->df_son_0=NULL;
    t->df_son_1=NULL;
}

//初始化自定义的目录
void init_df_0(DF* df_now)
{
    DF* df_new_1,* df_new_2,* df_new_3,* df_new_4,* df_new_5,* df_new_6,* df_new_7;
    df_new_1=(DF*)malloc(sizeof(DF));
    df_new_2=(DF*)malloc(sizeof(DF));
    df_new_3=(DF*)malloc(sizeof(DF));
    df_new_4=(DF*)malloc(sizeof(DF));
    df_new_5=(DF*)malloc(sizeof(DF));
    df_new_6=(DF*)malloc(sizeof(DF));
    df_new_7=(DF*)malloc(sizeof(DF));
    //df_now=(DF*)malloc(sizeof(DF));
    strcpy(df_new_1->df_name,"root");
    strcpy(df_new_2->df_name,"home");
    strcpy(df_new_3->df_name,"etc");
    strcpy(df_new_4->df_name,"a");
    strcpy(df_new_5->df_name,"b");
    strcpy(df_new_6->df_name,"tsq");
    strcpy(df_new_7->df_name,"hfeng");
    df_now->df_son_0=df_new_1;
    df_now->df_son_1=df_new_3;
    df_new_1->df_father=df_now;
    df_new_1->df_type=0;
    df_new_1->df_son_1=NULL;
    df_new_1->df_son_0=NULL;
    df_new_1->df_Permissions=3;
    df_new_1->df_next=df_new_2;
    df_new_1->df_front=NULL;
    df_new_2->df_father=df_now;
    df_new_2->df_next=df_new_3;
    df_new_2->df_front=df_new_1;
    df_new_2->df_son_0=df_new_4;
    df_new_2->df_son_1=df_new_5;
    df_new_2->df_type=0;
    df_new_2->df_Permissions=0;;
    df_new_3->df_father=df_now;
    df_new_3->df_next=NULL;
    df_new_3->df_front=df_new_2;
    df_new_3->df_son_0=NULL;
    df_new_3->df_son_1=NULL;
    df_new_3->df_Permissions=0;
    df_new_3->df_type=0;
    df_new_4->df_father=df_new_2;
    strcpy(df_new_4->df_main,"hanfengzhenshuai");
    df_new_4->df_next=df_new_5;
    df_new_4->df_front=NULL;
    df_new_4->df_son_0=NULL;
    df_new_4->df_son_1=NULL;
    df_new_4->df_type=1;
    df_new_4->df_Permissions=0;
    df_new_5->df_father=df_new_2;
    df_new_5->df_next=NULL;
    df_new_5->df_front=df_new_4;
    df_new_5->df_son_0=df_new_6;
    df_new_5->df_son_1=df_new_7;
    df_new_5->df_Permissions=0;
    df_new_5->df_type=0;
    df_new_6->df_father=df_new_5;
    df_new_6->df_next=df_new_7;
    df_new_6->df_front=NULL;
    df_new_6->df_son_0=NULL;
    df_new_6->df_son_1=NULL;
    df_new_6->df_type=1;
    df_new_6->df_Permissions=0;
    strcpy(df_new_6->df_main,"666");
    df_new_7->df_father=df_new_5;
    df_new_7->df_front=df_new_6;
    df_new_7->df_next=NULL;
    df_new_7->df_Permissions=0;
    df_new_7->df_type=1;
    df_new_7->df_son_0=NULL;
    df_new_7->df_son_1=NULL;
    strcpy(df_new_7->df_main,"plus");
    cout<<"\n"<<endl;
    /*
    cout<<"0000000000000000000000"<<endl;
    cout<<df_now->df_name<<endl;
    cout<<df_now->df_son_0->df_name<<endl;
    cout<<df_now->df_son_1->df_name<<endl;
    cout<<"1111111111111111111111"<<endl;  
    */
}

//初始化目录
void init_directory()
{
    df = (DF*)malloc(sizeof(DF));
	df_now = (DF*)malloc(sizeof(DF));
    init_DF(df);//初始化DF根目录
    df_now=df;
    init_df_0(df_now);//初始化自定义的目录 

}

//查看当前文件下目录的内容
void get_DF(DF* temp_df)
{
    cout<<"当前目录下的内容如下：";
    DF* t=temp_df;
    while(1)
    {
        if(t->df_front!=NULL)
        {
            t=t->df_front;
        }
        else 
        {
            break;
        }
    }
    while(1)
    {
        cout<<t->df_name<<" ";
        if(t->df_next!=NULL)
        {
            t=t->df_next;
        }
        else
        {
            break;
        }
    }
    cout<<endl;
    init_1();
    solving_1();
}

//返回父目录
void ret_DF(DF* temp_df)
{
    DF* t=temp_df;
    if(t->df_father==NULL)
    {
        cout<<"该目录为根目录，无父目录！"<<endl;
    }
    else 
    {
        t=t->df_father;
        df_now=t;
    }
    system("pause");
    system("cls");
    init_1();
    solving_1();
}

//进入当前目录的子目录
void gin_DF(DF* temp_df)
{
    //cout<<df_now->df_name<<endl;
    cout<<"请输入要进入的目录名：";
    char temp_name[1010];
    string s;
    cin>>s;
    ll len_s=ll(s.size())-1;
    for(ll i=0;i<=len_s;i++)
    {
        temp_name[i]=s[i];
    }

    DF* t=temp_df;

    bool flag=false;//定义是否寻找到目录
    while(1)
    {
        if(t->df_front!=NULL)
        {
            t=t->df_front;
        }
        else if(t->df_front==NULL)
        {
            break;
        }
    }
    while(1)
    {
        bool st_gin=true;
        for(ll i=0;i<=(ll)max((ll)strlen(t->df_name),(ll)strlen(temp_name))-(ll)1;i++)//表示查找到该名字的文件
        {
             if(t->df_name[i]!=temp_name[i])
            {
                st_gin=false;
            }
        }
        if(st_gin)
        {
            flag=true;
            break;
        }
        else if(t->df_next==NULL)
        {
            break;
        }
        else 
        {
            t=t->df_next;
        }
    }
    if(flag==true)
    {
        //cout<<"+++++++++"<<endl;
        //cout<<t->df_type<<endl;
        if(t->df_type==0)//如果该文件的类型是目录的话，那么直接进入子目录
        {
            //cout<<t->df_son_0->df_name;
            df_now=t->df_son_0;
            df=t->df_son_0;
        }
        else 
        {
            cout<<"该文件不是目录，无法进入"<<endl;
        }
    }
    else 
    {
        cout<<"该目录名不存在！"<<endl;
    }
    //system("pause");
    init_1();
    solving_1();
}

//第三初始化界面->当前路劲下的操作
void init_2()
{
    system("cls");
    cout<<"--------------------"<<endl;
    cout<<"1.增加目录/文件"<<endl;
    cout<<"2.删除目录/文件"<<endl;
    cout<<"3.读取文件内容"<<endl;
    cout<<"4.编写文件内容"<<endl;
    cout<<"5.返回上一页"<<endl;
}

//增加目录/文件
void add_df()
{
    
    if((temp_Permissions==1||temp_Permissions==0)!=1)
    {
        cout<<"对不起！您没有权限增加目录/文件！"<<endl;
        system("pause");
        system("cls");
        init_2();
        solving_2();
    }
    else if(df_now->df_father==NULL)
    {
        cout<<"对不起！当前目录为根目录，无法增加并列目录或文件！\n";
        system("pause");
        system("cls");
        init_2();
        solving_2();
    }
    else 
    {
        st_choice_3=true;
        cout<<"----------------------------"<<endl;
        cout<<"1.文件"<<endl;
        cout<<"2.目录"<<endl;
        while(st_choice_3)
        {
            cout<<"请输入要增加的类型：";
            cin>>choice_3;//增加文本类型的选择；
            if(choice_3==1||choice_3==2)
            {
                st_choice_3=false;
            }
        }
        cout<<"请输入你要增加的文本名:";
        char temp_name[1010];
        scanf("%s",&temp_name);
        //cout<<"---------"<<endl;
        DF* temp_df;
        temp_df=(DF*)malloc(sizeof(DF));
        //cout<<"---------"<<endl;
        strcpy(temp_df->df_name,temp_name);
        //cout<<"---------"<<endl;
        temp_df->df_father=df_now->df_father;//将新加的文本的父目录改为当前的目录
        //cout<<"---------"<<endl;
        temp_df->df_front=df_now->df_father->df_son_1;//将新加的文本的上一个改为当前目录的最后一个
        //cout<<"---------"<<endl;
        //cout<<df_now->df_son_1->df_name<<endl;
        //cout<<temp_df->df_name<<endl;
        df_now->df_father->df_son_1->df_next=temp_df;//将当前文本的最后一个的下一个改为新加的文本
        //cout<<"---------"<<endl;
        df_now->df_father->df_son_1=temp_df;//最后更改当前目录的最后一个为新加的文本
        //cout<<"---------"<<endl;
        temp_df->df_next=NULL;//更新新加的文本的下一个为空
        //cout<<"---------"<<endl;
        if(choice_3==1)
        {
            temp_df->df_type=1;
            temp_df->df_Permissions=1;
        }
        else 
        {
            temp_df->df_type=0;
            temp_df->df_Permissions=0;
        }
        cout<<"增加成功！"<<endl;
        system("pause");
        system("cls");
        init_1();
        solving_1();
    }
}

//删除目录文件
void del_df()
{
    if((temp_Permissions==1||temp_Permissions==0)!=1)
    {
        cout<<"对不起！您没有权限删除目录/文件！"<<endl;
        system("pause");
        system("cls");
        init_2();
        solving_2();
    }
    else if(df_now->df_father==NULL)
    {
        cout<<"对不起！当前目录为根目录，无法删除该目录！\n";
        system("pause");
        system("cls");
        init_2();
        solving_2();
    }
    else 
    {
        cout<<"请输入你要删除的文本名:";
        char temp_name[1010];
        scanf("%s",&temp_name);
        DF* temp_df;
        temp_df=(DF*)malloc(sizeof(DF));
        temp_df=df_now->df_father->df_son_0;
        //cout<<"================"<<endl;
        //cout<<df_now->df_father->df_name<<" "<<df_now->df_father->df_son_0->df_name<<" "<<df_now->df_father->df_son_1->df_name<<endl;
        //cout<<temp_df->df_name<<" "<<temp_name<<endl;
        //cout<<"================"<<endl;
        while(1)
        {
            st_gin_3=true;
            for(ll i=0;i<=(ll)max((ll)strlen(temp_df->df_name),(ll)strlen(temp_name))-(ll)1;i++)//表示查找到该名字的文件
            {
                if(temp_df->df_name[i]!=temp_name[i])
                {
                    st_gin_3=false;
                }
            }
            if(st_gin_3)
            {
                bool st_gin_3_1=true;
                bool st_gin_3_2=true;
                //cout<<"================"<<endl;
                for(ll i=0;i<=(ll)max((ll)strlen(df_now->df_father->df_son_0->df_name),(ll)strlen(temp_name))-(ll)1;i++)
                {
                    if(df_now->df_father->df_son_0->df_name[i]!=temp_name[i])
                    {
                        st_gin_3_1=false;
                    }
                }
                for(ll i=0;i<=(ll)max((ll)strlen(df_now->df_father->df_son_1->df_name),(ll)strlen(temp_name))-(ll)1;i++)
                {
                    if(df_now->df_father->df_son_1->df_name[i]!=temp_name[i])
                    {
                        st_gin_3_2=false;
                    }
                }
                if(st_gin_3_1)
                {
                    //cout<<"1==============="<<endl;
                    df_now->df_father->df_son_0=temp_df->df_next;
                    //cout<<"==============="<<endl;
                    df_now->df_father->df_son_0->df_front=NULL;
                    df_now=temp_df->df_next;
                    //cout<<"==============="<<endl;
                    temp_df->df_father=NULL;
                    //cout<<"==============="<<endl;
                    temp_df->df_next=NULL;
                    //cout<<"==============="<<endl;
                    st_del=true;
                    //cout<<"==============="<<endl;
                    break;
                }
                else if(st_gin_3_2)
                {
                    //cout<<"2==============="<<endl;
                    df_now->df_father->df_son_1=temp_df->df_front;
                    df_now->df_father->df_son_1->df_next=NULL;
                    temp_df->df_next=NULL;
                    temp_df->df_father=NULL;
                    st_del=true;
                    break;
                }
                else 
                {
                    temp_df->df_next->df_front=temp_df->df_front;
                    temp_df->df_front->df_next=temp_df->df_next;
                    temp_df->df_father=NULL;
                    temp_df->df_next=NULL;
                    temp_df->df_front=NULL;
                    st_del=true;
                    //cout<<"====3==="<<endl;
                    break;
                }
            }
            else if(temp_df==df_now->df_son_1)
            {
                //cout<<"====4==="<<endl;
                break;
            }
            else 
            {
                temp_df=temp_df->df_next;
            }
        }
        //cout<<"==============="<<endl;
        if(st_del)
        {
            cout<<"删除成功！"<<endl;
            system("pause");
            system("cls");
            init_1();
            solving_1();
        }
        else 
        {
            cout<<"文件不存在"<<endl;
            system("pause");
            system("cls");
            mak_DF();
        }
    }
}

//读取文件内容
void red_df(DF* temp_df)
{
    if((temp_Permissions==1||temp_Permissions==0||temp_Permissions==2)!=1)
    {
        cout<<"对不起！您没有权限读取目录/文件！"<<endl;
        system("pause");
        system("cls");
        init_2();
        solving_2();
    }
    else if(df_now->df_father==NULL)
    {
        cout<<"对不起！该文本类型为目录，无法读取！\n";
        system("pause");
        system("cls");
        init_2();
        solving_2();
    }
    bool st_red_1=true;
    cout<<"请输入你要读取的文本名字"<<endl;
    char temp_name[1010];
    scanf("%s",&temp_name);
    DF* t_3;
    t_3=(DF*)malloc(sizeof(DF));
    t_3=temp_df->df_father->df_son_0;
    while(1)
    {
        st_red_1=true;
        for(ll i=0;i<=max((ll)strlen(temp_name),(ll)strlen(t_3->df_name))-(ll)1;i++)
        {
            if(t_3->df_name[i]!=temp_name[i])
            {
                st_red_1=false;
            }
        }
        if(st_red_1)
        {
            if(t_3->df_type==1)
            {
                cout<<"该文件内容为:"<<endl;
                cout<<t_3->df_main<<endl;
                system("pause");
                mak_DF();
                break;
            }
            else 
            {
                cout<<"对不起，该文本类型为目录，无法读取！"<<endl;
                system("pause");
                mak_DF();
                break;
            }
        }
        else if(t_3->df_name==df_now->df_father->df_son_1->df_name)
        {
            cout<<"对不起，该文本名不存在！"<<endl;
            system("pause");
            mak_DF();
            break;
        }
        else 
        {
            t_3=t_3->df_next;
        }
    }
    cout<<"对不起，该文本不存在！"<<endl;
    system("pause");
    mak_DF();

}

//编写文件内容
void wre_df(DF* temp_df)
{
    if((temp_Permissions==1||temp_Permissions==0)!=1)
    {
        cout<<"对不起！您没有权限增加目录/文件！"<<endl;
        system("pause");
        system("cls");
        init_2();
        solving_2();
    }
    else if(df_now->df_father==NULL)
    {
        cout<<"对不起！该文本类型为目录，无法修改！\n";
        system("pause");
        system("cls");
        init_2();
        solving_2();
    }
    bool st_wre_1=true;
    cout<<"请输入你要修改的文本名字"<<endl;
    char temp_name[1010];
    scanf("%s",&temp_name);
    DF* t_3;
    t_3=(DF*)malloc(sizeof(DF));
    t_3=temp_df->df_father->df_son_0;
    while(1)
    {
        st_wre_1=true;
        for(ll i=0;i<=max((ll)strlen(temp_name),(ll)strlen(t_3->df_name))-(ll)1;i++)
        {
            if(t_3->df_name[i]!=temp_name[i])
            {
                st_wre_1=false;
            }
        }
        if(st_wre_1)
        {
            if(t_3->df_type==1)
            {
                ll len_rem=0;
                cout<<"请输入修改后的内容:"<<endl;
                cout<<"以#结尾"<<endl;
                char ch;
                while(ch=getchar())
                {
                    if(ch=='#')
                    {
                        break;
                    }
                    t_3->df_main[len_rem]=ch;
                    len_rem++;
                }
                system("pause");
                mak_DF();
                break;
            }
            else 
            {
                cout<<"对不起，该文本类型为目录，无法修改！"<<endl;
                system("pause");
                mak_DF();
                break;
            }
        }
        else if(t_3->df_name==df_now->df_son_1->df_name)
        {
            cout<<"对不起，该文本名不存在！"<<endl;
            system("pause");
            mak_DF();
            break;
        }        
        else 
        {
            t_3=t_3->df_next;
        }
    }
    cout<<"对不起，该文本不存在！"<<endl;
    system("pause");
    mak_DF();
}

//返回上一页
void ref_df()
{
    init_1();
    solving_1();
}

//第三初始化界面->选项
void solving_2()
{
    cout<<"请输入你的选项:";
    cin>>choice_2;//第三初始界面的选择
    switch(choice_2)
    {
        case 1:
            add_df();//增加目录/文件
            break;
        case 2:
            del_df();//删除目录/文件
            break;
        case 3:
            //cout<<df_now->df_name<<endl;
            red_df(df_now);//读取目录/文件
            break;
        case 4:
            wre_df(df_now);//编写目录/文件
            break;
        case 5:
            ref_df();//返回上一页
            break;
    }
}

//当前路径下的操作
void mak_DF()
{
    init_2();//第三初始化界面->当前路劲下的操作
    solving_2();//第三初始界面->选项
}

//第二初始界面->选项
void solving_1()
{
    //cout<<endl<<df_now->df_son_0->df_name<<endl;
    cin>>choice_1;
    switch(choice_1)
    {
        case 1:
            get_DF(df_now);//查看当前文件目录下的内容
            break;
        case 2:
            ret_DF(df_now);//返回当前文件的父目录
            break;
        case 3:
            gin_DF(df_now);//进入当前目录的子目录
            break;
        case 4:
            mak_DF();//当前路劲下的操作
            break;
        case 5:
            end();//退出系统
            break;
    }
}

//主函数
int main()
{
    init_user();//初始化最高特权用户
    init_0();//第一初始界面->用户登录|注册
    solving_0();//第一初始界面->选项
    init_directory();//初始化目录
    init_1();//第二初始界面->文件管理系统的操作
    solving_1();//第二初始界面->选项
    return 0;
}
