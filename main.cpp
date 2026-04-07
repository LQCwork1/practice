#include <iostream>//标准输入输出流
#include <windows.h>//引入 Windows 提供的系统函数库 SetConsoleCP
using namespace std;//标准命名空间
#include"Identity.h"
#include<fstream>
#include<string>
#include"globalFile.h"
#include"staff.h"
#include"manager.h"
#include"admin.h"




//进入员工子菜单界面
void staffMenu(Identity * &staff)
{
    while (true)
    {
        //调用员工子菜单
        staff->operMenu();
        Staff* sta = (Staff *)staff;

        int select = 0;
        cin >> select;

        if (select==1)//申请预约
        {
            sta->applyOrder();
        }
        else if (select==2)//查看自身预约
        {
            sta->showMyOrder();
        }
        else if (select==3)//查看所有预约
        {
            sta->showAllOrder();
        }
        else if (select == 4)//取消预约
        {
            sta->cancelOrder();
        }
        else//注销登陆
        {
            delete staff;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");

            return;
        }

    }




}


//进入经理子菜单界面
void managerMenu(Identity*& manager)
{
    while (true)
    {
        //调用子菜单界面
        manager->operMenu();

        Manager* man = (Manager*)manager;

        int select = 0;
        cin >> select;

        if (select==1)//查看所有预约
        {

            man->showAllOrder();
        }
        else if (select==2)//审核预约
        {
            man->validOrder();

        }
        else//注销登录
        {
            delete manager;
            cout << "注销成功" << endl;
            system("pause");
            system("cls");

            return;

        }

    }


}


//进入管理员的子菜单界面
void adminMenu(Identity * &admin)
{
    while (true)
    {
        //调用管理员子菜单
        admin->operMenu();

        //将父类指针转为子类指针，可以调用子类里的特有接口
        Admin* adm = (Admin*)admin;

        int select = 0;
        //接受用户选择
        cin >> select;

        if (select==1)//添加账号
        {
            //cout << "添加账号" << endl;
            adm->addPerson();

        }
        else if (select==2)//查看账号
        {
            //cout << "查看账号" << endl;
            adm->showPerson();

        }
        else if (select==3)//查看会议室
        {
           // cout << "查看会议室" << endl;
            adm->showRoom();

        }
        else if (select == 4)//清空预约
        {
            //cout << "清空预约" << endl;
            adm->cleanFile();

        }
        else
        {
            //注销
            delete admin;//销毁堆区对象
           // cout << "注销成功" << endl;
            system("pause");
            system("cls");
            return;
        }

    }
}




//登录功能 全局函数  (文件名称，身份类型)
void LoginIn(string fileName, int type)
{
    //父类指针，用于指向子类对象
    Identity* person = NULL;

    //读文件
    ifstream ifs;
    ifs.open(fileName, ios::in);

    //判断文件是否存在
    if (!ifs.is_open())
    {
        cout << "文件不存在" << endl;
        ifs.close();
        return;
    }

    //准备接受用户的信息
    int id = 0;
    string name;
    string pwd;

    //判断身份
    if (type==1)//员工身份
    {
        cout << "请输入你的员工号：" << endl;
        cin >> id;
    }
    else if (type==2)//经理身份
    {
        cout << "请输入你的员工号：" << endl;
        cin >> id;
    }

    cout << "请输入用户名：" << endl;
    cin >> name;

    cout << "请输入密码：" << endl;
    cin >> pwd;

    int fid;//从文件中读取的id
    string fname;//从文件中读取的姓名
    string fpwd;//从文件中读取的密码

    if (type==1)//员工身份验证
    {
        

        while (ifs >> fid && ifs >> fname && ifs >> fpwd)
        {    
            
           //与用户输入的信息做对比
            if (fid == id && fname == name && fpwd == pwd)
            {
                cout << "员工验证登陆成功！" << endl;
                system("pause");
                system("cls");

                person = new Staff(id, name, pwd);

                //进入员工的子菜单

                staffMenu(person);

                return;
            }
            
        }
      

    }
    else if (type==2)//经理身份验证
    {
        

        while (ifs >> fid && ifs >> fname && ifs >> fpwd)
        {

            //与用户输入的信息做对比
            if (fid == id && fname == name && fpwd == pwd)
            {
                cout << "经理验证登陆成功！" << endl;
                system("pause");
                system("cls");

                person = new Manager(id, name, pwd);

                //进入经理的子菜单

                managerMenu(person);

                return;
            }

        }
    }
    else if (type==3)//管理员身份验证
    {
        

        while (ifs >> fname && ifs >> fpwd)
        {

            //与用户输入的信息做对比
            if (fname == name && fpwd == pwd)
            {
                cout << "管理员验证登陆成功！" << endl;
                system("pause");
                system("cls");

                person = new Admin(name, pwd);

                //进入管理员的子菜单
                adminMenu(person);


                return;
            }

        }
    }

    cout << "验证登陆失败！" << endl;
    system("pause");
    system("cls");

    return;
}


int main()
{
    //SetConsoleOutputCP(65001);//输出统一源文件和控制台的编码一致为utf8，不然会打印乱码
    //SetConsoleCP(65001);//输入 65001=UTF8中文
    //system("chcp 65001");

    int select = 0;//用于接收用户选择

    while (true)
    {
        cout << "======================  欢迎来到会议室预约系统  =======================" << endl;
        cout << endl << "请输入您的身份：" << endl;
        cout << "\t\t -------------------------------\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|            1.员工             |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|            2.经理             |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|            3.管理员           |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t|            0.退出             |\n";
        cout << "\t\t|                               |\n";
        cout << "\t\t -------------------------------\n";
        cout << "请输入您的选择：";

        cin >> select;//接受用户选择

        switch (select)//根据用户的选择来实现不同接口
        {
        case 1://员工身份
            LoginIn(STAFF_FILE, 1);
            break;
        case 2://经理身份
            LoginIn(MANAGER_FILE, 2);
            break;
        case 3://管理员身份
            LoginIn(ADMIN_FILE, 3);
            break;
        case 0://退出
            cout << "欢迎下一次使用" << endl;
            system("pause");
            return 0;
            break;
        default:
            cout << "输入有误，请重新选择！" << endl;
            system("pause");
            system("cls");//清屏
            break;
        }
    }


    system("pause");
    return 0;
}