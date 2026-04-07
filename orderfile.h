#pragma once
#include <iostream>//标准输入输出流
using namespace std;//标准命名空间
#include"globalFile.h"
#include<fstream>
#include<string>
#include<map>

class OrderFile
{
public:

	//构造函数
	OrderFile();

	//更新预约记录
	void updateOrder();

	//记录预约条数
	int m_Size;

	//记录所有预约信息的容器  key是记录的条数 value是具体记录键值对信息
	map<int, map<string, string>>m_orderData;


};