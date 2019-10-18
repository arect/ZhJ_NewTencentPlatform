#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"Time.h"
#include"Ways.h"
using namespace std;
//面对管理员的成员信息设计(￣y▽￣)╭ 
class class_MemberInfo4Admin {
protected:
	int PlatformID = 0;
	int QQID = 0;
	string WeChatID = "$empty$";
public:
	int SaveIdInfo(const int a, const int b, const string c) {
		if (a != -1)
			PlatformID = a;
		if (b != -1)
			QQID = b;
		if (c.compare("$empty$") != 0)
			WeChatID = c;
		return 0;
	}
	const int ReturnQQID() {
		return QQID;
	}
	const int ReturnPlatformID() {
		return PlatformID;
	}
	const string ReturnWeChatID() {
		return WeChatID;
	}
};
//群的管理员权限 
class class_Admin {
protected:
	//注册成员及其其它ID
	vector<class_MemberInfo4Admin> QQMembers;
	vector<class_MemberInfo4Admin> WeChatMembers;
	//好友名单
	//0-陌生人 1-好友 2-请求为好友
	vector<vector<int>> FriendsList;
public:
	class_Admin() {
		ReadAllData();
		WriteLog("调用管理员");
	}
	~class_Admin() {
		SaveAllData();
	}
	//保存数据
	int SaveAllData() {
		if (!QQMembers.empty()) {
			ofstream AdminData_QQMembers;
			AdminData_QQMembers.open("AdminData_QQMembers.txt", ios::trunc);
			if (AdminData_QQMembers.is_open()) {
				for (unsigned int i = 0; i < QQMembers.size(); i++) {
					AdminData_QQMembers << i + 1 << "#" << QQMembers[i].ReturnPlatformID() << "#" << QQMembers[i].ReturnQQID();
					AdminData_QQMembers << "\n";
				}
				WriteLog("保存QQ成员数据");
			}
			AdminData_QQMembers.close();
		}
		if (!WeChatMembers.empty()) {
			ofstream AdminData_WeChatMembers;
			AdminData_WeChatMembers.open("AdminData_WeChatMembers.txt", ios::trunc);
			if (AdminData_WeChatMembers.is_open()) {
				for (unsigned int i = 0; i < WeChatMembers.size(); i++) {
					AdminData_WeChatMembers << i + 1 << "#" << WeChatMembers[i].ReturnPlatformID() << "#" << WeChatMembers[i].ReturnWeChatID();
					AdminData_WeChatMembers << "\n";
				}
				WriteLog("保存微信成员数据");
			}
			AdminData_WeChatMembers.close();
		}
		if (!FriendsList.empty()) {
			ofstream AdminData_Friends;
			AdminData_Friends.open("AdminData_FriendsList.txt", ios::trunc);
			if (AdminData_Friends.is_open()) {
				for (unsigned int i = 0; i < FriendsList.size(); i++) {
					for (unsigned int n = 0; n < FriendsList[i].size(); n++) {
						AdminData_Friends << FriendsList[i][n] << "#";
					}
					AdminData_Friends << "\n";
				}
				WriteLog("保存好友数据");
			}
			AdminData_Friends.close();
		}
		if (QQMembers.empty()) {
			WriteLog("QQ成员数据为空，数据保存至文件失败");
		}
		if (WeChatMembers.empty()) {
			WriteLog("微信成员数据为空，数据保存至文件失败");
		}
		if (FriendsList.empty()) {
			WriteLog("好友数据为空，数据保存至文件失败");
		}
		return 0;
	}

	//导入数据
	int ReadAllData() {
		ifstream AdminData_QQMembers;
		AdminData_QQMembers.open("AdminData_QQMembers.txt", ios::in);
		if (AdminData_QQMembers.is_open()) {
			int GetNum = 0;
			char GetChar = '0';
			class_MemberInfo4Admin temp;
			while (!AdminData_QQMembers.eof()) {
				AdminData_QQMembers >> GetNum;//序号
				AdminData_QQMembers >> GetChar;//#
				if (AdminData_QQMembers.eof()) {
					break;
				}
				AdminData_QQMembers >> GetNum;//平台号
				temp.SaveIdInfo(GetNum, -1, "$empty");
				QQMembers.push_back(temp);
				AdminData_QQMembers >> GetChar;//#
				AdminData_QQMembers >> GetNum;//QQ号
				QQMembers.back().SaveIdInfo(-1, GetNum, "$empty$");
			}
			WriteLog("将QQ成员数据导入至管理员");
		}
		AdminData_QQMembers.close();
		ifstream AdminData_WeChatMembers;
		AdminData_WeChatMembers.open("AdminData_WeChatMembers.txt", ios::in);
		if (AdminData_WeChatMembers.is_open()) {
			int GetNum = 0;
			char GetChar = '0';
			class_MemberInfo4Admin temp;
			string GetStr;
			while (!AdminData_WeChatMembers.eof()) {
				AdminData_WeChatMembers >> GetNum;//序号
				AdminData_WeChatMembers >> GetChar;//#
				if (AdminData_WeChatMembers.eof()) {
					break;
				}
				AdminData_WeChatMembers >> GetNum;//平台号
				temp.SaveIdInfo(GetNum, -1, "$empty");
				WeChatMembers.push_back(temp);
				AdminData_WeChatMembers >> GetChar;//#
				AdminData_WeChatMembers >> GetStr;//WeChat号
				WeChatMembers.back().SaveIdInfo(-1, -1, GetStr);
			}
			WriteLog("将WeChat成员数据导入至管理员");
		}
		AdminData_WeChatMembers.close();
		ifstream AdminData_Friends;
		AdminData_Friends.open("AdminData_FriendsList.txt", ios::in);
		if (AdminData_Friends.is_open()) {
			vector<int> temp;
			int GetNum = 0;
			char GetChar = '0';
			string a;
			AdminData_Friends >> a;
			int x = 0;
			for (unsigned int i = 0; i < a.size(); i++) {
				if (a[i] == '#')
					x++;
			}
			AdminData_Friends.seekg(0);
			for (int i = 0; i < x; i++) {
				for (int n = 0; n < x; n++) {
					AdminData_Friends >> GetNum;
					temp.push_back(GetNum);
					AdminData_Friends >> GetChar;//#
				}
//				AdminData_Friends >> GetChar;//接收每行最后的\n
				FriendsList.push_back(temp);
				temp.clear();
			}
			WriteLog("将好友数据导入至管理员");
		}
		AdminData_Friends.close();
		return 0;
	}

	//导入部分数据

	//导入QQ
	int ReadQQData() {
		QQMembers.clear();
		ifstream AdminData_QQMembers;
		AdminData_QQMembers.open("AdminData_QQMembers.txt", ios::in);
		if (AdminData_QQMembers.is_open()) {
			int GetNum = 0;
			char GetChar = '0';
			class_MemberInfo4Admin temp;
			while (!AdminData_QQMembers.eof()) {
				AdminData_QQMembers >> GetNum;//序号
				AdminData_QQMembers >> GetChar;//#
				if (AdminData_QQMembers.eof()) {
					break;
				}
				AdminData_QQMembers >> GetNum;//平台号
				temp.SaveIdInfo(GetNum, -1, "$empty");
				QQMembers.push_back(temp);
				AdminData_QQMembers >> GetChar;//#
				AdminData_QQMembers >> GetNum;//QQ号
				QQMembers.back().SaveIdInfo(-1, GetNum, "$empty$");
			}
			WriteLog("将QQ成员数据导入至管理员");
		}
		AdminData_QQMembers.close();
		return 0;
	}
	//导入微信
	int ReadWeChatData() {
		WeChatMembers.clear();
		ifstream AdminData_WeChatMembers;
		AdminData_WeChatMembers.open("AdminData_WeChatMembers.txt", ios::in);
		if (AdminData_WeChatMembers.is_open()) {
			int GetNum = 0;
			char GetChar = '0';
			class_MemberInfo4Admin temp;
			string GetStr;
			while (!AdminData_WeChatMembers.eof()) {
				AdminData_WeChatMembers >> GetNum;//序号
				AdminData_WeChatMembers >> GetChar;//#
				if (AdminData_WeChatMembers.eof()) {
					break;
				}
				AdminData_WeChatMembers >> GetNum;//平台号
				temp.SaveIdInfo(GetNum, -1, "$empty");
				WeChatMembers.push_back(temp);
				AdminData_WeChatMembers >> GetChar;//#
				AdminData_WeChatMembers >> GetStr;//WeChat号
				WeChatMembers.back().SaveIdInfo(-1, -1, GetStr);
			}
			WriteLog("将WeChat成员数据导入至管理员");
		}
		AdminData_WeChatMembers.close();
		return 0;
	}
	//导入好友关系
	int ReadFriendsData() {
		FriendsList.clear();
		ifstream AdminData_Friends;
		AdminData_Friends.open("AdminData_FriendsList.txt", ios::in);
		if (AdminData_Friends.is_open()) {
			vector<int> temp;
			int GetNum = 0;
			char GetChar = '0';
			string a;
			AdminData_Friends >> a;
			int x = 0;
			for (unsigned int i = 0; i < a.size(); i++) {
				if (a[i] == '#')
					x++;
			}
			AdminData_Friends.seekg(0);
			for (int i = 0; i < x; i++) {
				for (int n = 0; n < x; n++) {
					AdminData_Friends >> GetNum;
					temp.push_back(GetNum);
					AdminData_Friends >> GetChar;//#
				}
				AdminData_Friends >> GetChar;//接收每行最后的\n
				FriendsList.push_back(temp);
				temp.clear();
			}
			WriteLog("将好友数据导入至管理员");
		}
		AdminData_Friends.close();
		return 0;
	}

	//新增用户 a-平台ID b-QQ c-微信
	int AddNewMember(const int a, const int b, const string c) {
		class_MemberInfo4Admin temp;
		if (b != -1) {
			if (QQMembers.empty()) {
				ReadQQData();
			}
			temp.SaveIdInfo(a, b, c);
			QQMembers.push_back(temp);
			WriteLog("新增QQ用户：" + Num2Str(b));
		}
		if (c.compare("$empty$") != 0) {
			if (WeChatMembers.empty()) {
				ReadWeChatData();
			}
			temp.SaveIdInfo(a, b, c);
			WeChatMembers.push_back(temp);
			WriteLog("新增微信用户：" + c);
		}
		vector<int> temp_;
		if (FriendsList.size() == 0) {
			temp_.push_back(0);
			temp_.push_back(a);
			FriendsList.push_back(temp_);
			temp_.clear();
			temp_.push_back(a);
			temp_.push_back(0);
			FriendsList.push_back(temp_);
			return 0;
		}
		else {
			temp_.push_back(a);
			for (unsigned int i = 0; i < FriendsList.size() - 1; i++) {
				temp_.push_back(0);
				FriendsList[i + 1].push_back(0);
			}
			FriendsList[0].push_back(a);
			temp_.push_back(0);
			FriendsList.push_back(temp_);
			return -1;
		}
	}

	//删除用户QAQ
	int DeleteMember(const int a) {
		for (unsigned int i = 0; i < QQMembers.size(); i++) {
			if (QQMembers[i].ReturnPlatformID() == a) {
				QQMembers.erase(QQMembers.begin() + i);
			}
		}
		for (unsigned int i = 0; i < WeChatMembers.size(); i++) {
			if (WeChatMembers[i].ReturnPlatformID() == a) {
				WeChatMembers.erase(WeChatMembers.begin() + i);
			}
		}
		unsigned int i;
		for (i = 0; i < FriendsList.size(); i++) {
			if (FriendsList[i][0] == a)
				break;
		}
		for (unsigned int n = 0; n < FriendsList.size(); n++) {
			FriendsList[n].erase(FriendsList[n].begin() + i);
		}
		FriendsList.erase(FriendsList.begin() + i);
		WriteLog("删除用户" + Num2Str(a));
		return -1;
	}
	
	//申请好友关系
	//1-成功 -1-无第一人数据 -2-无第二人数据 -3-已经申请还未回应 -4-已经是好友 -5-数据错误
	int RequestShip(const int a, const int b) {
		for (unsigned int i = 0; i < QQMembers.size(); i++) {
			if (QQMembers[i].ReturnPlatformID() == a) {
				for (unsigned int n = 0; n < QQMembers.size(); n++) {
					if (QQMembers[n].ReturnPlatformID() == b) {
						for (unsigned int m = 0; m < FriendsList.size(); m++) {
							if (FriendsList[m][0] == a) {
								for (unsigned int q = 0; q < FriendsList.size(); q++) {
									if (FriendsList[0][q] == b) {
										if (FriendsList[q][m] == 2) {
											return -3;
										}
										if (FriendsList[q][m] == 1) {
											return -4;
										}
										FriendsList[q][m] = 2;
										WriteLog("好友申请" + Num2Str(a) + Num2Str(b));
										return 1;
									}
								}
								return -5;
							}

						}
						return -5;
					}
				}
				return -2;
			}
		}
		for (unsigned int i = 0; i < WeChatMembers.size(); i++) {
			if (WeChatMembers[i].ReturnPlatformID() == a) {
				for (unsigned int n = 0; n < WeChatMembers.size(); n++) {
					if (WeChatMembers[n].ReturnPlatformID() == b) {
						for (unsigned int m = 0; m < FriendsList.size(); m++) {
							if (FriendsList[m][0] == a) {
								for (unsigned int q = 0; q < FriendsList.size(); q++) {
									if (FriendsList[0][q] == b) {
										if (FriendsList[q][m] == 2) {
											return -3;
										}
										if (FriendsList[q][m] == 1) {
											return -4;
										}
										FriendsList[q][m] = 2;
										WriteLog("好友申请" + Num2Str(a) + Num2Str(b));
										return 1;
									}
								}
								return -5;
							}

						}
						return -5;
					}
				}
				return -2;
			}
		}
		return -1;
	}
	//查找是否有好友申请
	vector<int> FindRequest(const int a) {
		vector<int> b;
		for (unsigned int i = 0; i < FriendsList.size(); i++) {
			if (FriendsList[i][0] == a) {
				for (unsigned int n = 1; n < FriendsList[i].size(); n++) {
					if (FriendsList[i][n] == 2) {
						b.push_back(FriendsList[0][n]);
					}
				}
			}
		}
		return b;
	}
	vector<int> FindFriends(const int a) {
		vector<int> b;
		for (unsigned int i = 0; i < FriendsList.size(); i++) {
			if (FriendsList[i][0] == a) {
				for (unsigned int n = 1; n < FriendsList[i].size(); n++) {
					if (FriendsList[i][n] == 1) {
						b.push_back(FriendsList[0][n]);
					}
				}
			}
		}
		return b;
	}
	//查看关系
	//-1 账户不同不能相爱（；´д｀）ゞ 0-无关系 1-好友 2-申请ing
	int GetShip(const string a, const string b) {
		if (FindMember(a) % 100 == FindMember(b) % 100) {
			for (unsigned int i = 0; i < FriendsList.size(); i++) {
				if (FriendsList[i][0] == ReturnPlatformID(a)) {
					for (unsigned int n = 0; n < FriendsList[i].size(); n++) {
						if (FriendsList[0][n] == ReturnPlatformID(b)) {
							return FriendsList[i][n];
						}
					}
				}
			}
		}
		else {
			return -1;
		}
	}
	//确立好友关系
	//1-成功 -1-无第一人数据 -2-无第二人数据 -3-没有申请 -4-已经是好友 -5-数据错误
	int BuildShip(const int a, const int b) {
		for (unsigned int i = 0; i < QQMembers.size(); i++) {
			if (QQMembers[i].ReturnPlatformID() == a) {
				for (unsigned int n = 0; n < QQMembers.size(); n++) {
					if (QQMembers[n].ReturnPlatformID() == b) {
						for (unsigned int m = 0; m < FriendsList.size(); m++) {
							if (FriendsList[0][m] == a) {
								for (unsigned int q = 0; q < FriendsList.size(); q++) {
									if (FriendsList[q][0] == b) {
										if (FriendsList[m][q] == 2) {
											FriendsList[q][m] = 1;
											FriendsList[m][q] = 1;
											WriteLog("确立关系" + Num2Str(a) + Num2Str(b));
											return 1;
										}
										if (FriendsList[m][q] == 1) {
											return -4;
										}
										return -3;
									}
								}
								return -5;
							}

						}
						return -5;
					}
				}
				return -2;
			}
		}
		for (unsigned int i = 0; i < QQMembers.size(); i++) {
			if (WeChatMembers[i].ReturnPlatformID() == a) {
				for (unsigned int n = 0; n < WeChatMembers.size(); n++) {
					if (WeChatMembers[n].ReturnPlatformID() == b) {
						for (unsigned int m = 0; m < FriendsList.size(); m++) {
							if (FriendsList[0][m] == a) {
								for (unsigned int q = 0; q < FriendsList.size(); q++) {
									if (FriendsList[q][0] == b) {
										if (FriendsList[m][q] == 2) {
											FriendsList[q][m] = 1;
											FriendsList[m][q] = 1;
											WriteLog("确立关系" + Num2Str(a) + Num2Str(b));
											return 1;
										}
										if (FriendsList[m][q] == 1) {
											return -4;
										}
										return -3;
									}
								}
								return -5;
							}

						}
						return -5;
					}
				}
				return -2;
			}
		}
		return -1;
	}
	
	//解除好友关系
	//1-成功 -1-无第一人数据 -2-无第二人数据 -3-本来就不是好友 -4-正在申请无法撤销 -5-数据错误
	int CancelShip(const int a, const int b) {
		for (unsigned int i = 0; i < QQMembers.size(); i++) {
			if (QQMembers[i].ReturnPlatformID() == a) {
				for (unsigned int n = 0; n < QQMembers.size(); n++) {
					if (QQMembers[n].ReturnPlatformID() == b) {
						for (unsigned int m = 0; m < FriendsList.size(); m++) {
							if (FriendsList[0][m] == a) {
								for (unsigned int q = 0; q < FriendsList.size(); q++) {
									if (FriendsList[q][0] == b) {
										if (FriendsList[q][m] == 1) {
											FriendsList[q][m] = 0;
											FriendsList[m][q] = 0;
											WriteLog("解除关系" + Num2Str(a) + Num2Str(b));
											return 1;
										}
										if (FriendsList[q][m] == 2) {
											FriendsList[q][m] = 0;
											FriendsList[m][q] = 0;
											WriteLog("解除申请" + Num2Str(a) + Num2Str(b));
											return -4;
										}
										return -3;
									}
								}
								return -5;
							}

						}
						return -5;
					}
				}
				return -2;
			}
		}
		return -1;
	}
	
	//单纯查找成员
	//百位 输入的是什么ID 十位 在哪找到的 个位是否找到
	//1-平台 2-QQ 3-微信
	int FindMember(const string b) {
		int a = Str2Num(b);
		if (a > 0) {
			for (unsigned int i = 0; i < QQMembers.size(); i++) {
				if (QQMembers[i].ReturnPlatformID() == a)
					return 121;
				if (QQMembers[i].ReturnQQID() == a)
					return 221;
			}
			for (unsigned int i = 0; i < WeChatMembers.size(); i++) {
				if (WeChatMembers[i].ReturnPlatformID() == a)
					return 131;
			}
		}
		else {
			for (unsigned int i = 0; i < WeChatMembers.size(); i++) {
				if (b.compare(WeChatMembers[i].ReturnWeChatID()) == 0)
					return 331;
			}
		}
		return 0;
	}

	//查找成员并返回PlatformID
	int ReturnPlatformID(const string b) {
		int a = Str2Num(b);
		if (a > 0) {
			for (unsigned int i = 0; i < QQMembers.size(); i++) {
				if (QQMembers[i].ReturnPlatformID() == a)
					return QQMembers[i].ReturnPlatformID();
				if (QQMembers[i].ReturnQQID() == a)
					return QQMembers[i].ReturnPlatformID();
			}
			for (unsigned int i = 0; i < WeChatMembers.size(); i++) {
				if (WeChatMembers[i].ReturnPlatformID() == a)
					return WeChatMembers[i].ReturnPlatformID();
			}
		}
		for (unsigned int i = 0; i < WeChatMembers.size(); i++) {
			if (b.compare(WeChatMembers[i].ReturnWeChatID()) == 0)
				return WeChatMembers[i].ReturnPlatformID();
		}
		return 0;
	}
	vector<int> RecommendFriends(const int a) {
		unsigned int i;
		vector<int> rf;
		vector<int> b;
		for (i = 0; i < FriendsList.size(); i++) {
			if (FriendsList[i][0] == a) {
				break;
			}
		}
		for (unsigned int n = 0; n < FriendsList[i].size(); n++) {
			if (FriendsList[i][n] == 1) {
				b.push_back(FriendsList[n][0]);
				for (unsigned int m = 0; m < FriendsList[n].size(); m++) {
					if (FriendsList[n][m] == 1) {
						rf.push_back(FriendsList[m][0]);
					}
				}
			}
		}
		for (unsigned int n = 0; n < rf.size(); n++) {
			for (unsigned int m = n + 1; m < rf.size(); m++) {
				if (rf[n] == rf[m]) {
					rf.erase(rf.begin() + m);
					m--;
				}
			}
		}
		for (unsigned int n = 0; n < rf.size(); n++) {
			if (rf[n] == 0) {
				rf.erase(rf.begin() + n);
				n--;
			}
		}
		for (unsigned int n = 0; n < rf.size(); n++) {
			if (rf[n] == a) {
				rf.erase(rf.begin() + n);
				n--;
			}
		}
		for (unsigned int n = 0; n < rf.size(); n++) {
			for (unsigned int m = 0; m < b.size(); m++) {
				if (b[m] == rf[n]) {
					rf.erase(rf.begin() + n);
					n--;
					break;
				}
			}
		}
		return rf;
	}
};