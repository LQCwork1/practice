#pragma once//防止头文件重复包含
#include <iostream>//标准输入输出流
using namespace std;//标准命名空间
#include"Identity.h";//继承父类引用文件
#include<string>
#include"orderfile.h"
#include<vector>




class Manager:public Identity
{
public:
	//默认构造	
	Manager();
	//有参构造
	Manager(int empId, string name, string pwd);
	//菜单界面
	virtual void operMenu();

	//查看所有预约
	void showAllOrder();
	//审核预约
	void validOrder();
	//员工号
	int m_empId;
};