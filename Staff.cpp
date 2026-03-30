#include"staff.h"

//默认构造
Staff::Staff() 
{

}
//有参构造  工号 姓名 密码
Staff::Staff(int id, string name, string pwd) 
{
	this->m_ID = id;
	this->m_name = name;
	this->m_pwd = pwd;

    //初始化房间信息
    ifstream ifs;
    ifs.open(ROOM_FILE, ios::in);

    Room rom;
    while (ifs>>rom.m_roomID && ifs>>rom.m_MaxNum)
    {
        //将读取的信息放入到容器中
        vRoom.push_back(rom);
        
    }
    ifs.close();


}
//菜单界面
void Staff::operMenu()
{
    cout << "欢迎员工：" << this->m_name << " 登录！" << endl;
    cout << "\t\t ----------------------------------\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|            1.申请预约            |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|            2.查看自身预约        |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|            3.查看所有预约        |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|            4.取消预约            |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t|            0.注销登陆            |\n";
    cout << "\t\t|                                  |\n";
    cout << "\t\t ----------------------------------\n";
    cout << "请选择您的操作：";
}
//申请预约
void Staff::applyOrder()
{
    cout << "房间预约开放时间为周一至周五！" << endl;
    cout << "请输入预约的时间：" << endl;
    cout << "1.周一" << endl;
    cout << "2.周二" << endl;
    cout << "3.周三" << endl;
    cout << "4.周四" << endl;
    cout << "5.周五" << endl;

    int date = 0;//日期
    int interval = 0;//时间段
    int room = 0;//房间编号

    while (true)
    {
        cin >> date;
        if (date>=1 && date<=5)
        {
            break;
        }
        cout << "输入有误，请重新输入！" << endl;

    }
    cout << "请输入申请预约的时间段：" << endl;
    cout << "1.上午" << endl;
    cout << "2.下午" << endl;
    while (true)
    {
        cin >> interval;
        if (interval >= 1 && interval <= 2)
        {
            break;
        }
        cout << "输入有误，请重新输入！" << endl;

    }
    cout << "请选择房间：" << endl;
    for(int i=0;i<vRoom.size();i++)
    {
        cout << vRoom[i].m_roomID << "号房间容量为：" << vRoom[i].m_MaxNum << endl;

    }
    while (true)
    {
        cin >> room;
        if (room >= 1 && room <= 3)
        {
            break;
        }
        cout << "输入有误，请重新输入！" << endl;

    }
    cout << "预约成功，审核中！" << endl;

    ofstream ofs;
    ofs.open(ORDER_FILE, ios::app);
    
    ofs << "date:" << date << " ";
    ofs << "interval:" << interval << " ";
    ofs << "staID:" << this->m_ID << " ";
    ofs << "staName:" << this->m_name << " ";
    ofs << "roomID:" <<room << " ";
    ofs << "status:" << 1 << endl;

    ofs.close();

    system("pause");
    system("cls");

}
//查看自身预约
void Staff::showMyOrder()
{
    OrderFile of;
    
    if (of.m_Size == 0)
    {
        cout << "无预约记录!" << endl;
        system("pause");
        system("cls");
        return;
    }

    for (int i = 0;i < of.m_Size;i++)
    {
        //string 转 int
        //string 用 .c_str() 转为c++字符串就是 const char *
        //用atoi(const char *)转 int
        if (this->m_ID == atoi(of.m_orderData[i]["staID"].c_str()))//找到自身预约
        {
            cout << "预约日期：周" << of.m_orderData[i]["date"];
            cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
            cout << " 房间号：" << of.m_orderData[i]["roomID"];

            string status = " 状态：";
            // 1 审核中   2 已预约  -1 预约失败  0已取消
            if (of.m_orderData[i]["status"] == "1")
            {
                status += "审核中";
            }
            else if (of.m_orderData[i]["status"] == "2")
            {
                status += "预约成功";
            }
            else if (of.m_orderData[i]["status"] == "-1")
            {
                status += "预约失败，审核未通过";
            }
            else
            {
                status += "预约已取消";
            }
            cout << status << endl;

        }
    }
    system("pause");
    system("cls");

}
//查看所有预约
void Staff::showAllOrder()
{
    OrderFile of;

    if (of.m_Size == 0)
    {
        cout << "无预约记录!" << endl;
        system("pause");
        system("cls");
        return;
    }

    for (int i = 0;i < of.m_Size;i++)
    {
        cout << i + 1 << "、" ;
        cout << "预约日期：周" << of.m_orderData[i]["date"];
        cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
        cout << " 员工号：" << of.m_orderData[i]["staID"];
        cout << " 姓名：" << of.m_orderData[i]["staName"];
        cout << " 房间号：" << of.m_orderData[i]["roomID"];

        string status = " 状态：";
        // 1 审核中   2 已预约  -1 预约失败  0已取消
        if (of.m_orderData[i]["status"] == "1")
        {
            status += "审核中";
        }
        else if (of.m_orderData[i]["status"] == "2")
        {
            status += "预约成功";
        }
        else if (of.m_orderData[i]["status"] == "-1")
        {
            status += "预约失败，审核未通过";
        }
        else
        {
            status += "预约已取消";
        }
        cout << status << endl;

    }

    system("pause");
    system("cls");

}
// 取消预约
void Staff::cancelOrder()
{
    OrderFile of;

    if (of.m_Size == 0)
    {
        cout << "无预约记录!" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "审核中和预约成功的记录可以取消，请输入要取消的记录：" << endl;

    int index = 1;
    vector<int>v;//存放在最大容器中的下标编号

    for (int i = 0;i < of.m_Size;i++)
    {
        //先判断自身的编号
        if (this->m_ID == atoi(of.m_orderData[i]["staID"].c_str()))//找到自身预约
        {
            //再筛选状态  审核中或预约成功的
            if (of.m_orderData[i]["status"]=="1" || of.m_orderData[i]["status"] == "2")
            {
                v.push_back(i);
                cout << index++ << "、";
                cout << "预约日期：周" << of.m_orderData[i]["date"];
                cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
                cout << " 房间号：" << of.m_orderData[i]["roomID"];

                string status = " 状态：";                
                if (of.m_orderData[i]["status"] == "1")
                {
                    status += "审核中";
                }
                else if (of.m_orderData[i]["status"] == "2")
                {
                    status += "预约成功";
                }
                cout << status << endl;

            }

        }

    }

    cout << "请输入要取消的记录，按0返回：" << endl;
    int select = 0;

    while (true)
    {
        cin >> select;
        
        if (select >= 0 && select <= v.size()) 
        {
            if (select == 0)
            {
                break;
            }
            else
            {
                of.m_orderData[v[select - 1]]["status"] = "0";

                of.updateOrder();

                cout << "已取消预约" << endl;

                break;
            }

        }

        cout << "输入有误，请重新输入！" << endl;

    }

    system("pause");
    system("cls");
}