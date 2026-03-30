#include"orderfile.h"


//构造函数
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string date;//日期
	string interval;//时间段
	string staID;//编号
	string staName;//姓名
	string roomID;//房间号
	string status;//状态

	this->m_Size = 0;//预约记录条数

	while (ifs>>date && ifs>>interval && ifs>>staID && ifs>>staName && ifs>>roomID && ifs>>status)
	{

		//date:1
		string key;
		string value;

		map<string, string>m;

		//截取日期
		int pos = date.find(":");//返回位置 4
		if (pos != -1)//防止pos没找到冒号 没找到会返回-1
		{
			key = date.substr(0, pos);//截取冒号前面的值
			value = date.substr(pos + 1, date.size() - pos - 1);//截取冒号后面的值

			m.insert(make_pair(key, value));
		}
		//截取时间段
		pos = interval.find(":");//返回位置 4
		if (pos != -1)//防止pos没找到冒号 没找到会返回-1
		{
			key = interval.substr(0, pos);//截取冒号前面的值
			value = interval.substr(pos + 1, interval.size() - pos - 1);//截取冒号后面的值

			m.insert(make_pair(key, value));
		}
		//截取编号
		pos = staID.find(":");//返回位置 4
		if (pos != -1)//防止pos没找到冒号 没找到会返回-1
		{
			key = staID.substr(0, pos);//截取冒号前面的值
			value = staID.substr(pos + 1, staID.size() - pos - 1);//截取冒号后面的值

			m.insert(make_pair(key, value));
		}
		//截取姓名
		pos = staName.find(":");//返回位置 4
		if (pos != -1)//防止pos没找到冒号 没找到会返回-1
		{
			key = staName.substr(0, pos);//截取冒号前面的值
			value = staName.substr(pos + 1, staName.size() - pos - 1);//截取冒号后面的值

			m.insert(make_pair(key, value));
		}
		//截取房间号
		pos = roomID.find(":");//返回位置 4
		if (pos != -1)//防止pos没找到冒号 没找到会返回-1
		{
			key = roomID.substr(0, pos);//截取冒号前面的值
			value = roomID.substr(pos + 1, roomID.size() - pos - 1);//截取冒号后面的值

			m.insert(make_pair(key, value));
		}
		//截取状态
		pos = status.find(":");//返回位置 4
		if (pos != -1)//防止pos没找到冒号 没找到会返回-1
		{
			key = status.substr(0, pos);//截取冒号前面的值
			value = status.substr(pos + 1, status.size() - pos - 1);//截取冒号后面的值

			m.insert(make_pair(key, value));
		}
		
		//将小的map容器，放到大的map容器中
		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;


	}

	ifs.close();

	//测试最大的map
	/*for (map<int, map<string, string>>::iterator it = m_orderData.begin();it != m_orderData.end();it++)
	{
		cout << "条数为：" << it->first << "value=" << endl;
		for (map<string, string>::iterator mit = (*it).second.begin();mit != it->second.end();mit++)
		{
			cout << " key= " << mit->first << " value=" << mit->second << " ";
		}
		cout << endl;
	}*/
}

//更新预约记录
void OrderFile::updateOrder()
{

	if (this->m_Size == 0)
	{
		return;//如果没有记录直接返回
	}

	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < this->m_Size; i++)
	{
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "staID:" << this->m_orderData[i]["staID"] << " ";
		ofs << "staName:" << this->m_orderData[i]["staName"] << " ";
		ofs << "roomID:" << this->m_orderData[i]["roomID"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << endl;
	}

	ofs.close();
}