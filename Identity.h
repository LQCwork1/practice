#pragma once//防止头文件重复包含
#include <iostream>//标准输入输出流
using namespace std;//标准命名空间

class Identity//身份抽象基类
{
public:

	//纯虚函数 操作菜单
	virtual void operMenu() = 0;

	//用户名
	string m_name;
	//密码
	string m_pwd;


};