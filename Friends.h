/*好友类
/*用于管理好友
*/
#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include"Admin.h"
#include"Ways.h"
//#include "UI.h"
using namespace std;
class class_Friends {
protected:
	vector<int> FriendsList;
public:
	class_Friends(){}
	~class_Friends(){}
	//添加好友
	//-4-明明不是好友还加到了…… -3-正在申请 -2-本地已经删除好友,但是现在已经添加 -1-终端错误，可能未找到数据 0-已经是好友 1-申请成功
	int AddFriend(const int a, const int b) {
		class_Admin* Admin;
		Admin = new(class_Admin);
		//查询是否已是好友
		int c = (*Admin).RequestShip(a, b);
		delete(Admin);
		if (c == -4) {
			for (unsigned int i = 0; i < FriendsList.size(); i++) {
				if (FriendsList[i] == b)
					return 0;
			}
			FriendsList.push_back(b);
			WriteLog(Num2Str(a) + "遗失好友信息，现已补回部分");
			return -2;
		}
		else if (c == -3) {
			for (unsigned int i = 0; i < FriendsList.size(); i++) {
				if (FriendsList[i] == b) {
					FriendsList.erase(FriendsList.begin() + i);
					return -4;
				}
			}
			WriteLog(Num2Str(a) + "和" + Num2Str(b) + "已经申请好友");
			return -3;
		}
		else if (c != 1) {
			WriteLog(Num2Str(a) + "和" + Num2Str(b) + "好友申请失败，查无此人");
			return -1;
		}
		else {
			//本地已经保存好友
			for (unsigned int i = 0; i < FriendsList.size(); i++) {
				if (FriendsList[i] == b) {
					FriendsList.erase(FriendsList.begin() + i);
					return -4;
				}
			}
			WriteLog(Num2Str(a) + "和" + Num2Str(b) + "好友申请成功");
			return 1;
		}
		return -5;
	}
	//删除好友
	//1-成功 -1-查无此人 -2-本地未添加
	int DelFriend(const int a, const int b) {
		//查看是否为好友
		WriteLog(Num2Str(a));
		WriteLog(Num2Str(b));
		class_Admin* Admin;
		Admin = new(class_Admin);
		for (unsigned int i = 0; i < FriendsList.size(); i++) {
			if (FriendsList[i] == b) {
				if ((*Admin).CancelShip(a, b) == 1) {
					FriendsList.erase(FriendsList.begin() + i);
					WriteLog("M两者解除好友关系");
					return 1;
				}
				else {
					WriteLog("M出错");
					FriendsList.erase(FriendsList.begin() + i);
					return -1;
				}
			}
			else {
				//无此好友
				(*Admin).CancelShip(a, b);
				WriteLog("M尚不是好友");
				return -2;
			}
		}
		delete(Admin);
	}
	//导出好友
	const vector<int> ExportFriendsData() {
		return FriendsList;
	}
	//存入好友
	int PushInFriend(const int a) {
		for (unsigned int i = 0; i < FriendsList.size(); i++) {
			if (FriendsList[i] == a)
				return 0;
		}
		FriendsList.push_back(a);
		return 1;
	}
};

class class_Group {
protected:
	int GroupID = 0;//群ID
	string GroupName = "";//群名
	int GroupManager = 0;//群主
	vector<int> GroupMember;//群员
	//群管理通过继承实现
public:
	static int GroConstID;
	//修改群名 群主和管理员专属
	virtual string ChangeGroupName(const string a) {
		return GroupName;
	};
	virtual int ReturnManager() {
		return GroupManager;
	}
	//设置管理员
	virtual int ManageGroupAdmin(const int a, const string b) {
		return 0;
	}
	//管理群员
	virtual int ManageGroupMember(const int a, const string b) {
		return 0;
	}
	//查找群员
	virtual int FindGroupMember(const string a) {
		return 0;
	}
	//保存文件
	virtual int SaveData() {
		return 0;
	}
	//读入文件
	virtual int ReadData(const int a) {
		return 0;
	}
	//返回群号
	int ReturnGroupID() {
		return GroupID;
	}
	vector<int> ReturnMemberList() {
		return GroupMember;
	}
	//查询身份
	//1-群主 2-管理 3-群员 4-其它
	virtual int QueryIdentity(const int a) {
		//1
		if (a == GroupManager) {
			return 1;
		}
		for (unsigned int i = 0; i < GroupMember.size(); i++) {
			if (a == GroupMember[i]) {
				return 3;
			}
		}
		return 4;
	}
};

//QQ群
class class_QQGroup4Manager:public class_Group {
protected:
	vector<int> GroupAdmin;
public:
	class_QQGroup4Manager(const int ManID) {
		if (ManID > 0) {
			ifstream file_;
			//确认目前ID
			for (int i = 20001;; i++) {
				file_.open(Num2Str(i), ios::in);
				if (!file_.is_open()) {
					GroupID = i;
					break;
				}
				file_.close();
			}
			if (GroupID >= 29999) {
				exit(0);
			}
			GroupManager = ManID;
		}
		else if (ManID <= 0) {
			//－O－
		}
	}
	~class_QQGroup4Manager() {
		SaveData();
	}
	//修改群名 群主和管理员专属＞︿＜
	virtual string ChangeGroupName(const string a) {
		if (a.compare("$empty$") != 0)
			GroupName = a;
		return GroupName;
	}
	//设置管理员
	//-1-已经是管理员，添加失败 1-成功 -2-不是管理员无法删除 0-无权限
	//a-成员ConstID b-操作
	virtual int ManageGroupAdmin(const int a, const string b) {
		if (b.compare("Add") == 0) {
			//已经是管理
			for (unsigned int i = 0; i < GroupAdmin.size(); i++) {
				if (GroupAdmin[i] == a)
					return -1;
			}
			//添加
			GroupAdmin.push_back(a);
			//移除群员
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				if (GroupMember[i] == a) {
					GroupMember.erase(GroupMember.begin() + i);
				}
				return -2;
			}
			return 1;
		}
		if (b.compare("Del") == 0) {
			for (unsigned int i = 0; i < GroupAdmin.size(); i++) {
				if (GroupAdmin[i] == a) {
					GroupAdmin.erase(GroupAdmin.begin() + i);
					GroupMember.push_back(a);
					return 1;
				}
				return -2;
			}
		}
		return 0;
	}
	//管理群员
	//-1-已是群员无需添加 1-成功 -2-无该成员删除失败 0-无权限
	//a-成员ConstID b-操作
	virtual int ManageGroupMember(const int a, const string b) {
		if (b.compare("Add") == 0) {
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				if (GroupMember[i] == a) {
					return -1;
				}
			}
			GroupMember.push_back(a);
			return 1;
		}
		if (b.compare("Del") == 0) {
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				if (GroupMember[i] == a) {
					GroupMember.erase(GroupMember.begin() + i);
					return 1;
				}
			}
			return -2;
		}
		return 0;
	}
	//查找群员//////////////////////////////////////////////////////////
	virtual int FindGroupMember(const string a) {
		return 0;
	}
	//保存文件
	virtual int SaveData() {
		ofstream SaveData;
		SaveData.open(Num2Str(GroupID), ios::trunc);
		if (SaveData.is_open()) {
			SaveData << "群号：" << GroupID << "\n";
			SaveData << "群名：" << GroupName << "\n";
			SaveData << "群主：" << GroupManager << "\n";
			SaveData << "群管理：" << "\n";
			for (unsigned int i = 0; i < GroupAdmin.size(); i++) {
				SaveData << GroupAdmin[i] << "\n";
			}
			SaveData << "群员：" << "\n";
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				SaveData << GroupMember[i] << "\n";
			}
			SaveData.close();
			return 1;
		}
		return -1;
	}
	//读入文件
	virtual int ReadData(const int a) {
		if (a <= 0) {
			return 0;
		}
		ifstream ReadData;
		string GetStr = "$empty$";
		string TempStr = "$empty$";
		int GetNum = 0;
		ReadData.open(Num2Str(a), ios::in);
		streamoff x;
		if (ReadData.is_open()) {
			while (!ReadData.eof()) {
				ReadData >> GetStr;
				if (GetStr.compare(0, 6, "群号：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupID = Str2Num(TempStr);
					continue;
				}
				if (GetStr.compare(0, 6, "群主：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupManager = Str2Num(TempStr);
					continue;
				}
				if (GetStr.compare(0, 6, "群名：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupName = TempStr;
					continue;
				}
				if (GetStr.compare(0, 8, "群管理：", 0, 8) == 0) {
					x = ReadData.tellg();
					ReadData >> GetStr;
					while (Str2Num(GetStr) != 0) {
						GroupAdmin.push_back(Str2Num(GetStr));
						x = ReadData.tellg();
						ReadData >> GetStr;
					}
					ReadData.seekg(x);
					continue;
				}
				if (GetStr.compare(0, 6, "群员：", 0, 6) == 0) {
					x = ReadData.tellg();
					ReadData >> GetStr;
					while (Str2Num(GetStr) != 0) {
						GroupMember.push_back(Str2Num(GetStr));
						x = ReadData.tellg();
						if (!(ReadData >> GetStr)) {
							break;
						}
						if (ReadData.eof()) {
							break;
						}
					}
					continue;
				}
			}
			ReadData.close();
			return 1;
		}
		return -1;
	}
	//返回管理员
	vector<int> ReturnGroupAdmin() {
		return GroupAdmin;
	}
	//查询身份
	//1-群主 2-管理 3-群员 4-其它
	virtual int QueryIdentity(const int a) {
		//1
		if (a == GroupManager) {
			return 1;
		}
		for (unsigned int i = 0; i < GroupAdmin.size(); i++) {
			if (a == GroupAdmin[i]) {
				return 2;
			}
		}
		for (unsigned int i = 0; i < GroupMember.size(); i++) {
			if (a == GroupMember[i]) {
				return 3;
			}
		}
		return 4;
	}
};
class class_QQGroup4Admin :public class_Group {
protected:
	vector<int> GroupAdmin;
public:
	~class_QQGroup4Admin() {
		SaveData();
	}
	//修改群名 群主和管理员专属＞︿＜
	virtual string ChangeGroupName(const string a) {
		if (a.compare("$empty$") != 0)
			GroupName = a;
		return GroupName;
	}
	//设置管理员 就是无权限
	virtual int ManageGroupAdmin(const int a, const string b) {
		return 0;
	}
	//管理群员
	//-1-已是群员无需添加 1-成功 -2-无该成员删除失败 0-无权限
	//a-成员ConstID b-操作
	virtual int ManageGroupMember(const int a, const string b) {
		if (b.compare("Add") == 0) {
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				if (GroupMember[i] == a) {
					return -1;
				}
			}
			GroupMember.push_back(a);
			return 1;
		}
		if (b.compare("Del") == 0) {
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				if (GroupMember[i] == a) {
					GroupMember.erase(GroupMember.begin() + i);
					return 1;
				}
			}
			return -2;
		}
		return 0;
	}
	//保存文件
	virtual int SaveData() {
		ofstream SaveData;
		SaveData.open(Num2Str(GroupID), ios::trunc);
		if (SaveData.is_open()) {
			SaveData << "群号：" << GroupID << "\n";
			SaveData << "群名：" << GroupName << "\n";
			SaveData << "群主：" << GroupManager << "\n";
			SaveData << "群管理：" << "\n";
			for (unsigned int i = 0; i < GroupAdmin.size(); i++) {
				SaveData << GroupAdmin[i] << "\n";
			}
			SaveData << "群员：" << "\n";
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				SaveData << GroupMember[i] << "\n";
			}
			SaveData.close();
			return 1;
		}
		return -1;
	}
	//读入文件
	virtual int ReadData(const int a) {
		if (a <= 0) {
			return 0;
		}
		ifstream ReadData;
		string GetStr = "$empty$";
		string TempStr = "$empty$";
		int GetNum = 0;
		ReadData.open(Num2Str(a), ios::in);
		streamoff x;
		if (ReadData.is_open()) {
			while (!ReadData.eof()) {
				ReadData >> GetStr;
				if (GetStr.compare(0, 6, "群号：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupID = Str2Num(TempStr);
					continue;
				}
				if (GetStr.compare(0, 6, "群主：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupManager = Str2Num(TempStr);
					continue;
				}
				if (GetStr.compare(0, 6, "群名：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupName = TempStr;
					continue;
				}
				if (GetStr.compare(0, 8, "群管理：", 0, 8) == 0) {
					x = ReadData.tellg();
					ReadData >> GetStr;
					while (Str2Num(GetStr) != 0) {
						GroupAdmin.push_back(Str2Num(GetStr));
						x = ReadData.tellg();
						ReadData >> GetStr;
					}
					ReadData.seekg(x);
					continue;
				}
				if (GetStr.compare(0, 6, "群员：", 0, 6) == 0) {
					x = ReadData.tellg();
					ReadData >> GetStr;
					while (Str2Num(GetStr) != 0) {
						GroupMember.push_back(Str2Num(GetStr));
						x = ReadData.tellg();
						if (!(ReadData >> GetStr)) {
							break;
						}
						if (ReadData.eof()) {
							break;
						}
					}
					continue;
				}
			}
			return 1;
		}
		return -1;
	}
	vector<int> ReturnGroupAdmin() {
		return GroupAdmin;
	}
	//查询身份
	//1-群主 2-管理 3-群员 4-其它
	virtual int QueryIdentity(const int a) {
		//1
		if (a == GroupManager) {
			return 1;
		}
		for (unsigned int i = 0; i < GroupAdmin.size(); i++) {
			if (a == GroupAdmin[i]) {
				return 2;
			}
		}
		for (unsigned int i = 0; i < GroupMember.size(); i++) {
			if (a == GroupMember[i]) {
				return 3;
			}
		}
		return 4;
	}
};
class class_QQGroup4Member :public class_Group {
protected:
	vector<int> GroupAdmin;
public:
	~class_QQGroup4Member() {
		SaveData();
	}
	//修改群名
	virtual string ChangeGroupName(const string a) {
		return GroupName;
	}
	//设置管理员 就是无权限
	virtual int ManageGroupAdmin(const int a, const string b) {
		return 0;
	}
	//管理群员
	virtual int ManageGroupMember(const int a, const string b) {
		if (b.compare("Add") == 0) {
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				if (GroupMember[i] == a) {
					return -1;
				}
			}
			GroupMember.push_back(a);
			return 1;
		}
		if (b.compare("Out") == 0) {
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				if (GroupMember[i] == a) {
					GroupMember.erase(GroupMember.begin() + i);
					break;
				}
			}
			return 1;
		}
		return 0;
	}
	//保存文件
	virtual int SaveData() {
		ofstream SaveData;
		SaveData.open(Num2Str(GroupID), ios::trunc);
		if (SaveData.is_open()) {
			SaveData << "群号：" << GroupID << "\n";
			SaveData << "群名：" << GroupName << "\n";
			SaveData << "群主：" << GroupManager << "\n";
			SaveData << "群管理：" << "\n";
			for (unsigned int i = 0; i < GroupAdmin.size(); i++) {
				SaveData << GroupAdmin[i] << "\n";
			}
			SaveData << "群员：" << "\n";
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				SaveData << GroupMember[i] << "\n";
			}
			SaveData.close();
			return 1;
		}
		return -1;
	}
	//读入文件
	virtual int ReadData(const int a) {
		if (a <= 0) {
			return 0;
		}
		ifstream ReadData;
		string GetStr = "$empty$";
		string TempStr = "$empty$";
		int GetNum = 0;
		ReadData.open(Num2Str(a), ios::in);
		streamoff x;
		if (ReadData.is_open()) {
			while (!ReadData.eof()) {
				ReadData >> GetStr;
				if (GetStr.compare(0, 6, "群号：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupID = Str2Num(TempStr);
					continue;
				}
				if (GetStr.compare(0, 6, "群主：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupManager = Str2Num(TempStr);
					continue;
				}
				if (GetStr.compare(0, 6, "群名：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupName = TempStr;
					continue;
				}
				if (GetStr.compare(0, 8, "群管理：", 0, 8) == 0) {
					x = ReadData.tellg();
					ReadData >> GetStr;
					while (Str2Num(GetStr) != 0) {
						GroupAdmin.push_back(Str2Num(GetStr));
						x = ReadData.tellg();
						ReadData >> GetStr;
					}
					ReadData.seekg(x);
					continue;
				}
				if (GetStr.compare(0, 6, "群员：", 0, 6) == 0) {
					x = ReadData.tellg();
					ReadData >> GetStr;
					while (Str2Num(GetStr) != 0) {
						GroupMember.push_back(Str2Num(GetStr));
						x = ReadData.tellg();
						if (!(ReadData >> GetStr)) {
							break;
						}
						if (ReadData.eof()) {
							break;
						}
					}
					continue;
				}
			}
			ReadData.close();
			return 1;
		}
		return -1;
	}
	vector<int> ReturnGroupAdmin() {
		return GroupAdmin;
	}
	//查询身份
	//1-群主 2-管理 3-群员 4-其它
	virtual int QueryIdentity(const int a) {
		//1
		if (a == GroupManager) {
			return 1;
		}
		for (unsigned int i = 0; i < GroupAdmin.size(); i++) {
			if (a == GroupAdmin[i]) {
				return 2;
			}
		}
		for (unsigned int i = 0; i < GroupMember.size(); i++) {
			if (a == GroupMember[i]) {
				return 3;
			}
		}
		return 4;
	}
};

//微信群
class class_WeChatGroup4Manager:public class_Group {
protected:
public:
	class_WeChatGroup4Manager(const int ManID) {
		if (ManID > 0) {
			ifstream file_;
			//确认目前ID
			for (int i = 30001;; i++) {
				file_.open(Num2Str(i), ios::in);
				if (!file_.is_open()) {
					GroupID = i;
					break;
				}
				file_.close();
			}
			if (GroupID >= 99999) {
				exit(0);
			}
			GroupManager = ManID;
		}
		else if (ManID <= 0) {
			//－O－
		}
	}
	~class_WeChatGroup4Manager() {
		SaveData();
	}
	//修改群名 群主专属
	virtual string ChangeGroupName(const string a) {
		if (a.compare("$empty$") != 0)
			GroupName = a;
		return GroupName;
	}
	//设置管理员
	virtual int ManageGroupAdmin(const int a, const string b) {
		return 0;
	}
	//管理群员
	//-1-已是群员无需添加 1-成功 -2-无该成员删除失败 0-无权限
	//a-成员ConstID b-操作
	virtual int ManageGroupMember(const int a, const string b) {
		if (b.compare("Add") == 0) {
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				if (GroupMember[i] == a) {
					return -1;
				}
			}
			GroupMember.push_back(a);
			return 1;
		}
		if (b.compare("Del") == 0) {
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				if (GroupMember[i] == a) {
					GroupMember.erase(GroupMember.begin() + i);
					return 1;
				}
			}
			return -2;
		}
		return 0;
	}
	//保存文件
	virtual int SaveData() {
		ofstream SaveData;
		SaveData.open(Num2Str(GroupID), ios::trunc);
		if (SaveData.is_open()) {
			SaveData << "群号：" << GroupID << "\n";
			SaveData << "群名：" << GroupName << "\n";
			SaveData << "群主：" << GroupManager << "\n";
			SaveData << "群员：" << "\n";
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				SaveData << GroupMember[i] << "\n";
			}
			SaveData.close();
			return 1;
		}
		return -1;
	}
	//读入文件
	virtual int ReadData(const int a) {
		if (a <= 0) {
			return 0;
		}
		ifstream ReadData;
		string GetStr = "$empty$";
		string TempStr = "$empty$";
		int GetNum = 0;
		ReadData.open(Num2Str(a), ios::in);
		if (ReadData.is_open()) {
			while (!ReadData.eof()) {
				ReadData >> GetStr;
				if (GetStr.compare(0, 6, "群号：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupID = Str2Num(TempStr);
					continue;
				}
				if (GetStr.compare(0, 6, "群主：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupManager = Str2Num(TempStr);
					continue;
				}
				if (GetStr.compare(0, 6, "群名：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupName = TempStr;
					continue;
				}
				if (GetStr.compare(0, 6, "群员：", 0, 6) == 0) {
					ReadData >> GetStr;
					while (Str2Num(GetStr) != 0) {
						if (ReadData.eof()) {
							break;
						}
						GroupMember.push_back(Str2Num(GetStr));
						ReadData >> GetStr;
						if (ReadData.eof()) {
							break;
						}
					}
					continue;
				}
			}
			return 1;
		}
		return -1;
	}
};
class class_WeChatGroup4Member :public class_Group {
protected:
public:
	~class_WeChatGroup4Member() {
		SaveData();
	}
	//修改群名 群主专属
	virtual string ChangeGroupName(const string a) {
		return GroupName;
	}
	//设置管理员
	virtual int ManageGroupAdmin(const int a, const string b) {
		return 0;
	}
	//管理群员
	//-1-已是群员无需添加 1-成功 -2-无该成员删除失败 0-无权限
	//a-成员ConstID b-操作
	virtual int ManageGroupMember(const int a, const string b) {
		if (b.compare("Add") == 0) {
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				if (GroupMember[i] == a) {
					return -1;
				}
			}
			GroupMember.push_back(a);
			return 1;
		}
		if (b.compare("Out") == 0) {
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				if (GroupMember[i] == a) {
					GroupMember.erase(GroupMember.begin() + i);
					return 1;
				}
			}
			return -2;
		}
		return 0;
	}
	//保存文件
	virtual int SaveData() {
		ofstream SaveData;
		SaveData.open(Num2Str(GroupID), ios::trunc);
		if (SaveData.is_open()) {
			SaveData << "群号：" << GroupID << "\n";
			SaveData << "群名：" << GroupName << "\n";
			SaveData << "群主：" << GroupManager << "\n";
			SaveData << "群员：" << "\n";
			for (unsigned int i = 0; i < GroupMember.size(); i++) {
				SaveData << GroupMember[i] << "\n";
			}
			SaveData.close();
			return 1;
		}
		return -1;
	}
	//读入文件
	virtual int ReadData(const int a) {
		if (a <= 0) {
			return 0;
		}
		ifstream ReadData;
		string GetStr = "$empty$";
		string TempStr = "$empty$";
		int GetNum = 0;
		ReadData.open(Num2Str(a), ios::in);
		if (ReadData.is_open()) {
			while (!ReadData.eof()) {
				ReadData >> GetStr;
				if (GetStr.compare(0, 6, "群号：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupID = Str2Num(TempStr);
					continue;
				}
				if (GetStr.compare(0, 6, "群主：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupManager = Str2Num(TempStr);
					continue;
				}
				if (GetStr.compare(0, 6, "群名：", 0, 6) == 0) {
					TempStr = GetStr.substr(6, GetStr.size() - 6);
					GroupName = TempStr;
					continue;
				}
				if (GetStr.compare(0, 6, "群员：", 0, 6) == 0) {
					ReadData >> GetStr;
					while (Str2Num(GetStr) != 0) {
						if (ReadData.eof()) {
							break;
						}
						GroupMember.push_back(Str2Num(GetStr));
						ReadData >> GetStr;
						if (ReadData.eof()) {
							break;
						}
					}
					continue;
				}
			}
			return 1;
		}
		return -1;
	}
};

//匹配群
//-1-文件受损 0-没有这个群 1-群主 2-管理 3-群员 4-什么都不是
int GetGroup(const int GroID, const int MemID) {
	ifstream file;
	file.open(Num2Str(GroID), ios::in);
	string temp;
	if (file.is_open()) {
		streamoff x;
		while (!file.eof()) {
			file >> temp;
			if (temp.compare(0, 6, "群号：", 0, 6) == 0) {
				temp = temp.substr(6, temp.size() - 6);
				if (GroID != Str2Num(temp)) {
					WriteLog("群号为" + temp + "文件名为" + Num2Str(GroID) + "受损");
					file.close();
					return -1;
				}
			}
			else if (temp.compare(0, 6, "群主：", 0, 6) == 0) {
				temp = temp.substr(6, temp.size() - 6);
				if (MemID == Str2Num(temp)) {
					file.close();
					return 1;
				}
			}
			else if (temp.compare(0, 8, "群管理：", 0, 8) == 0) {
				x = file.tellg();
				file >> temp;
				while (Str2Num(temp) != 0) {
					if (Str2Num(temp) == MemID) {
						return 2;
					}
					x = file.tellg();
					file >> temp;
				}
				file.seekg(x);
			}
			else if (temp.compare(0, 6, "群员：", 0, 6) == 0) {
				x = file.tellg();
				file >> temp;
				while (Str2Num(temp) != 0) {
					if (Str2Num(temp) == MemID) {
						return 3;
					}
					file >> temp;
					if (file.eof()) {
						break;
					}
				}
				if (file.eof()) {
					break;
				}
				file.seekg(x);
			}
		}
		return 4;
	}
	else {
		WriteLog("无法找到" + temp + "群");
		return 0;
	}
	file.close();
	return 0;
}