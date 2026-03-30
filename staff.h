#pragma once//防止头文件重复包含
#include <iostream>//标准输入输出流
using namespace std;//标准命名空间
#include"Identity.h";//继承父类引用文件
#include<string>
#include<vector>
#include"room.h"
#include<fstream>
#include"globalFile.h"
#include"orderfile.h"


class Staff : public Identity
{
public:
	//默认构造
	Staff();
	//有参构造  工号 姓名 密码
	Staff(int id,string name,string pwd);
	//菜单界面
	virtual void operMenu();
	//申请预约
	void applyOrder();
	//查看自身预约
	void showMyOrder();
	//查看所有预约
	void showAllOrder();
	// 取消预约
	void cancelOrder();
	//员工工号
	int m_ID;

	//房间容器
	vector<Room>vRoom;
};