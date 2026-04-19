#include"admin.h"



//默认构造
Admin::Admin()
{

}
//有参构造
Admin::Admin(string name, string pwd)
{
	//初始化管理员信息
	this->m_name = name;
	this->m_pwd = pwd;

    //初始化容器 并获取文件中员工经理的信息
    this->initVector();

    //初始化房间信息
    ifstream ifs;
    ifs.open(ROOM_FILE, ios::in);

    Room rom;

    while (ifs>>rom.m_roomID && ifs>>rom.m_MaxNum)
    {
        vRoom.push_back(rom);
    }
    ifs.close();

    cout << "房间的数量为：" << vRoom.size() << endl;

}
//菜单界面
void Admin::operMenu()
{
    cout << "欢迎管理员："<<this->m_name <<" 登录！"<< endl;
    cout << "\t\t ---------------------------------\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|            1.添加账号           |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|            2.查看账号           |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|            3.查看会议室         |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|            4.清空预约           |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t|            0.注销登陆           |\n";
    cout << "\t\t|                                 |\n";
    cout << "\t\t ---------------------------------\n";
    cout << "请选择您的操作：";
}
//添加账号
void Admin::addPerson()
{
    

    string fileName;//操作的文件名
    string tip;//提示id号
    string errorTip;//重复错误提示


    ofstream ofs;//文件操作对象

    int select = 0;

    while (true)
    {
        system("cls");//清屏
        operMenu();

        cout << "请选择添加账号的类型：" << endl;
        cout << "1.员工账号" << endl;
        cout << "2.经理账号" << endl;

        
        cin >> select;

        // 检测输入是否失败
        if (cin.fail())
        {
            cin.clear(); // 清除错误状态

            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 清空缓冲区

            cout << "输入非法，请输入数字！" << endl;
            system("pause");
            system("cls");
            continue; // 重新循环
        }

        if (select == 1)
        {
            //添加员工
            fileName = STAFF_FILE;
            tip = "请输入员工号";
            errorTip = "员工号重复，请重新输入";
            break;
        }
        else if (select == 2)
        {
            //添加经理
            fileName = MANAGER_FILE;
            tip = "请输入员工号";
            errorTip = "员工号重复，请重新输入";
            break;
        }
        else
        {
            //输入错误
            cout << "输入有误，请重新选择！" << endl;
            system("pause");
            
        }
    }
    //用追加的方式写文件
    ofs.open(fileName, ios::out | ios::app);

    int id;
    string name;
    string pwd;

    cout << tip << endl;

    while (true)//检测重复
    {
        cin >> id;
        bool ret = checkRepeat(id, select);
        if (ret)//重复
        {
            cout << errorTip << endl;
        }
        else
        {
            break;
        }
    }

   
    //cin >> id;

    cout << "请输入姓名" << endl;
    cin >> name;

    cout << "请输入密码" << endl;
    cin >> pwd;
    
    //向文件中添加数据
    ofs << id << " " << name << " " << pwd << " " << endl;
    cout << "添加成功！" << endl;

    system("pause");
    system("cls");

    ofs.close();

    //调用初始化容器接口，重新获取数据，解决没有实时更新的问题
    this->initVector();

}


void printStaff(Staff & s)
{
    cout << "员工号：" << s.m_ID << " 姓名：" << s.m_name << " 密码：" << s.m_pwd << endl;
}
void printManager(Manager& m)
{
    cout << "员工号：" << m.m_empId << " 姓名：" << m.m_name << " 密码：" << m.m_pwd << endl;
}



//查看账号
void Admin::showPerson()
{
    cout << "请选择你要查看的账号类型：" << endl;
    cout << "1.员工：" << endl;
    cout << "2.经理：" << endl;

    int select = 0;
    cin >> select;

    if (select==1)
    {
        //查看员工
        cout << "所有的员工信息如下：" << endl;
        for_each(vSta.begin(), vSta.end(), printStaff);
    }
    else
    {
        //查看经理
        cout << "所有的经理信息如下：" << endl;
        for_each(vMan.begin(), vMan.end(), printManager);
    }
    system("pause");
    system("cls");

}
//查看房间信息
void Admin::showRoom()
{
    cout << "房间的信息如下：" << endl;
    for (vector<Room>::iterator it = vRoom.begin();it != vRoom.end();it++)
    {
        cout << "房间编号：" << it->m_roomID << " 房间容量：" << it->m_MaxNum << endl;
    }


    system("pause");
    system("cls");


}
//清空预约记录
void Admin::cleanFile()
{
    ofstream ofs(ORDER_FILE, ios::trunc);
    ofs.close();

    cout << "清空成功！" << endl;
    system("pause");
    system("cls");

}



//初始化容器
void Admin::initVector()
{

    //确保容器清空
    vSta.clear();
    vMan.clear();

    //读取信息 员工 
    ifstream ifs;
    ifs.open(STAFF_FILE, ios::in);

    if (!ifs.is_open())
    {

        cout << "文件读取失败" << endl;
        return;

    }

    Staff s;
    while (ifs>>s.m_ID && ifs>>s.m_name && ifs>>s.m_pwd)
    {
        vSta.push_back(s);
    }

    cout << "当前的员工数量为：" << vSta.size() << endl;

    ifs.close();


    //读取经理信息

    ifs.open(MANAGER_FILE, ios::in);

    if (!ifs.is_open())
    {

        cout << "文件读取失败" << endl;
        return;

    }

    Manager m;
    while (ifs >> m.m_empId && ifs >> m.m_name && ifs >> m.m_pwd)
    {
        vMan.push_back(m);
    }

    cout << "当前的经理数量为：" << vMan.size() << endl;

    ifs.close();
}


//检测重复    员工号 类型
bool Admin::checkRepeat(int id, int type)
{
    if (type==1)//检测员工
    {
        for (vector<Staff>::iterator it = vSta.begin();it != vSta.end(); it++)
        {
            if (id==it->m_ID)
            {
                return true;
            }
        }

    }
    else//检测经理
    {
        for (vector<Manager>::iterator it = vMan.begin();it != vMan.end(); it++)
        {
            if (id == it->m_empId)
            {
                return true;
            }
        }
    }
    return false;
}
