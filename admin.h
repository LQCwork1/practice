#pragma once//防止头文件重复包含
#include <iostream>//标准输入输出流
using namespace std;//标准命名空间
#include"Identity.h";//继承父类引用文件
#include<string>
#include<fstream>
#include"globalFile.h"
#include <limits> //用来获取数据类型范围信息
#include<vector>
#include"manager.h"
#include"staff.h"
#include<algorithm> 
#include"room.h"



class Admin :public Identity
{
public:
	//默认构造
	Admin();
	//有参构造
	Admin(string name, string pwd);
	//菜单界面
	virtual void operMenu();
	//添加账号
	void addPerson();
	//查看账号
	void showPerson();
	//查看房间信息
	void showRoom();
	//清空预约记录
	void cleanFile();

	//初始化容器
	void initVector();

	//检测重复    员工号 类型
	bool checkRepeat(int id,int type);

	//员工容器
	vector<Staff>vSta;

	//经理容器
	vector<Manager>vMan;

	//房间容器
	vector<Room>vRoom;
};
