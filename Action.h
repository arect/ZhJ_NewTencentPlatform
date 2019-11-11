#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"Ways.h"
#include"Body.h"
#include"Friends.h"
#include"Admin.h"
#include"Time.h"
#include"UI.h"
using namespace std;
void QQAction(class_PlatformBody* p);
int FriendsListPage(const vector<int> a, const int b);
void DisFriPage(const int a);
int GroupListPage(vector<class_Group> a);
int FriendsListPage_2(const vector<int> a, const int b);
//******************************************************************
//******************************************************************
class_PlatformBody* QQAction_Plus(const int QQID) {
	class_PlatformBody* p;
	p = new(class_PlatformBody)("login");
	(*p).ReadNew(QQID);
	return p;
}
//QQ
void QQAction(class_PlatformBody* p) {
	bool Exit = false;
	string Option;
	do {
		bool judge = false;
		class_Admin* Admin;
		Admin = new(class_Admin);
		vector<int> xx = (*Admin).FindFriends(Str2Num((*p).ReturnInfo("PlatformID")));
		for (unsigned int i = 0; i < xx.size(); i++) {
			judge = false;
			for (unsigned int n = 0; n < (*p).LocalFriendsList.ExportFriendsData().size(); n++) {
				if ((*p).LocalFriendsList.ExportFriendsData()[n] == xx[i]) {
					judge = true;
					break;
				}
			}
			if (!judge) {
				(*p).LocalFriendsList.PushInFriend(xx[i]);
			}
		}
		delete(Admin);
		//群
		judge = false;
		class_QQGroup4Member* work;
		work = new(class_QQGroup4Member);
		for (int i = 20001; i < 20100; i++) {
			if ((*work).ReadData(i) == -1) {
				break;
			}
			else {
				if ((*work).QueryIdentity(Str2Num((*p).ReturnInfo("PlatformID"))) == 4) {
					continue;
				}
				else {
					for (unsigned int n = 0; n < (*p).LocalGroupsList.size(); n++) {
						if ((*p).LocalGroupsList[n].ReturnGroupID() == (*work).ReturnGroupID()) {
							judge = true;
						}
					}
					if (judge == false) {
						(*p).LocalGroupsList.push_back((*work));
					}
					(*work).SaveData();
					judge = false;
				}
			}
		}
		delete(work);
		OutputBox(14, 41);
		Locate(XLocation + 3, YLocation);
		cout << "  QQ ";
		XLocation += 4;
		YLocation += 2;
		Locate(XLocation, YLocation++);
		cout << "您好，" << (*p).ReturnInfo("name") << "\n";
		Locate(XLocation, YLocation++);
		Locate(XLocation, YLocation++);
		cout << "1 好友";
		Locate(XLocation, YLocation++);
		cout << "2 群列表";
		Locate(XLocation, YLocation++);
		cout << "3 添加、管理或创建群";
		Locate(XLocation, YLocation++);
		cout << "4 好友申请";
		Locate(XLocation, YLocation++);
		cout << "5 注销账户";
		Locate(XLocation, YLocation++);
		Locate(XLocation, YLocation++);
		cout << "→";
		cin >> Option;
		getchar();
		switch (Str2Num(Option))
		{
			//查看好友，可以添加
		case 1: {
			int aa = FriendsListPage((*p).ReturnInfo(), Str2Num((*p).ReturnInfo("PlatformID")));
			if (aa > 0) {
				class_Admin* Admin;
				Admin = new(class_Admin);
				int bbb = (*Admin).ReturnPlatformID(Num2Str(aa));
				if ((*Admin).FindMember((*p).ReturnInfo("PlatformID")) != (*Admin).FindMember(Num2Str(bbb))) {
					Locate(XLocation, YLocation++);
					cout << "不同世界的人是不能在一起的哟，";
					system("pause");
					DisFriPage((*p).ReturnInfo().size() * 10);
					WriteLog("添加失败");
					break;
				}
				(*Admin).SaveAllData();
				int bb = (*p).LocalFriendsList.AddFriend(Str2Num((*p).ReturnInfo("PlatformID")), bbb);
				if (Str2Num((*p).ReturnInfo("PlatformID")) == bbb) {
					(*Admin).CancelShip(Str2Num((*p).ReturnInfo("PlatformID")), bbb);
					delete(Admin);
					Locate(XLocation, YLocation++);
					cout << "的确要和自己做朋友呢，";
					WriteLog("添加失败");
					system("pause");
					DisFriPage((*p).ReturnInfo().size() * 10);
				}
				else if (bb == 1) {
					Locate(XLocation, YLocation++);
					cout << "发送请求成功，";
					WriteLog("添加成功");
					system("pause");
					DisFriPage((*p).ReturnInfo().size() * 10);
				}
				else if (bb == 0 || bb == -2) {
					Locate(XLocation, YLocation++);
					cout << "已经是好友了，";
					WriteLog("添加失败");
					system("pause");
					DisFriPage((*p).ReturnInfo().size() * 10);
				}
				else if (bb == -1) {
					Locate(XLocation, YLocation++);
					cout << "系统数据错误，";
					WriteLog("添加失败，系统数据错误");
					system("pause");
					DisFriPage((*p).ReturnInfo().size() * 10);
				}
				else if (bb == -2) {
					Locate(XLocation, YLocation++);
					cout << "后悔了吧2333，";
					system("pause");
					DisFriPage((*p).ReturnInfo().size() * 10);
				}
				else if (bb == -4 || bb == -3) {
					Locate(XLocation, YLocation++);
					cout << "请勿重复申请，";
					WriteLog("添加失败，重复申请");
					system("pause");
					DisFriPage((*p).ReturnInfo().size() * 10);
				}
				else if (bb == -10) {
					DisFriPage((*p).ReturnInfo().size() * 10);
				}
			}
			break;
		}
			//查看群
		case 2: {
			GroupListPage((*p).LocalGroupsList);
			break;
		}
			//查找/创建群
		case 3: {
			YLocation = 4;
			Locate(60, YLocation++);
			cout << "╭ ───────────────────────────────────── ╮";
			Locate(60, YLocation++);
			cout << "│                                       │";
			Locate(60, YLocation++);
			cout << "╰ ───────────────────────────────────── ╯";
			Locate(63, YLocation - 2);
			cin >> Option;
			getchar();
			if (Option.compare("$exit$") == 0) {
				Option = "$empty$";
				DisFriPage(2);
				break;
			}
			WriteLog("查找群" + Option);
			class_QQGroup4Member* pp;
			pp = new(class_QQGroup4Member);
			int bx = (*pp).ReadData(Str2Num(Option));
			int ax = (*pp).ReturnGroupID();
			//创建群聊
			if (Option.compare("+") == 0 || Option.compare("create") == 0) {
				WriteLog("创建群聊");
				class_QQGroup4Manager* pppp;
				pppp = new(class_QQGroup4Manager)(Str2Num((*p).ReturnInfo("PlatformID")));
				do {
					Locate(63, YLocation - 2);
					cout << "输入群名：";
					cin >> Option;
					if (Option.compare("$exit$") == 0) {
						break;
					}
					(*pppp).ChangeGroupName(Option);
				} while (Option.compare("$empty$") == 0);
				if (Option.compare("$exit$") == 0) {
					break;
				}
				else {
					if (pppp != NULL) {
						(*p).LocalGroupsList.push_back(*pppp);
						(*p).SaveThis(); (*pppp).SaveData();
						Locate(63, YLocation - 2);
						cout << "创建成功，群号为：" << (*pppp).ReturnGroupID();
					}
				}
				delete(pppp);
			}
			//群号错误
			else if ((Str2Num(Option) < 20000)||(Str2Num(Option) > 29999)) {
				Locate(60, YLocation++);
				cout << "群号格式非法，";
				system("pause");
				DisFriPage(2);
				break;
			}
			//找不到群
			else if (bx == -1) {
				Locate(60, YLocation++);
				cout << "查找失败，";
				system("pause");
				DisFriPage(2);
				delete(pp);
				break;
			}
			else {
				switch (GetGroup((*pp).ReturnGroupID(), Str2Num((*p).ReturnInfo("PlatformID")))) {
				//群主
				case 1: {
					delete(pp);
					class_QQGroup4Manager* ppp;
					ppp = new(class_QQGroup4Manager)(-1);
					(*ppp).ReadData(ax);
					GroupPage(ppp);
					string aaa;
					do {
						do {
							Locate(XLocation + 2, YLocation);
							cout << "                             ";
							Locate(XLocation + 2, YLocation);
							cin >> aaa;
							getchar();
						} while (Str2Num(aaa) < 1 || Str2Num(aaa) > 5);
						switch (Str2Num(aaa))
						{
							//拉人
						case 1: {
							Locate(XLocation + 2, YLocation);
							cout << "     ";
							int AccountID;
							class_Admin* Admin;
							Admin = new(class_Admin);
							do {
								Locate(XLocation + 2, YLocation);
								cout << "                              ";
								Locate(XLocation + 2, YLocation);
								cout << "输入对方QQ号码：";
								cin >> aaa;
								if (aaa.compare("$exit$") == 0) {
									Exit = true;
									break;
								}
								WriteLog("拉人" + aaa);
								getchar();
								AccountID = (*Admin).ReturnPlatformID(aaa);
							} while (AccountID <= 0);
							if (Exit) {
								Exit = false;
								break;
							}
							if ((*ppp).QueryIdentity(AccountID) == 1) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 群主就不要再加了。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 2) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 他已经是管理员了。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 3) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 别试了他是群员。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 4) {
								AccountID = (*ppp).ManageGroupMember(AccountID, "Add");
								if (AccountID == 1) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 添加成功";
									(*ppp).SaveData();
									Sleep(1200);
									GroupPage(ppp);
								}
								else if (AccountID == -1) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 已是群员";
								}
								else if (AccountID == 0) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 没有权限";
								}
							}
							delete(Admin);
							Sleep(1000);
							break;
						}
							//踢人
						case 2: {
							Locate(XLocation + 2, YLocation);
							cout << "     ";
							int AccountID;
							class_Admin* Admin;
							Admin = new(class_Admin);
							do {
								Locate(XLocation + 2, YLocation);
								cout << "                              ";
								Locate(XLocation + 2, YLocation);
								cout << "输入对方QQ号码：";
								cin >> aaa;
								if (aaa.compare("$exit$") == 0) {
									Exit = true;
									break;
								}
								WriteLog("踢人" + aaa);
								AccountID = (*Admin).ReturnPlatformID(aaa);
							} while (AccountID <= 0);
							if (Exit) {
								Exit = false;
								break;
							}
							if ((*ppp).QueryIdentity(AccountID) == 1) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 自己都删？";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 2) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 请先取消管理员身份";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 3) {
								AccountID = (*ppp).ManageGroupMember(AccountID, "Del");
								if (AccountID == 1) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 删除成功";
									(*ppp).SaveData();
									Sleep(1200);
									GroupPage(ppp);
								}
								else if (AccountID == -2) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 未找到该群员";
								}
								else if (AccountID == 0) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 没有权限";
								}
							}
							else if ((*ppp).QueryIdentity(AccountID) == 4) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 纯路人……";
							}
							delete(Admin);
							Sleep(1000);
							break;
						}
							//改群名
						case 3: {
							Locate(XLocation + 2, YLocation);
							cout << "     ";
							do {
								Locate(XLocation + 2, YLocation);
								cout << "                              ";
								Locate(XLocation + 2, YLocation);
								cout << "输入新群名：";
								cin >> aaa;
							} while (aaa.compare("$empty$") == 0);
							WriteLog("改群名" + aaa);
							if (aaa.compare("$exit$") == 0) {
								break;
							}
							else {
								aaa = (*ppp).ChangeGroupName(aaa);
								Locate(XLocation + 2, YLocation);
								cout << "成功了                 ";
								(*ppp).SaveData();
								Sleep(1200);
								GroupPage(ppp);
							}
							break;
						}
							//设置管理员
						case 4: {
							Locate(XLocation + 2, YLocation);
							cout << "     ";
							int AccountID;
							class_Admin* Admin;
							Admin = new(class_Admin);
							do {
								Locate(XLocation + 2, YLocation);
								cout << "如果是管理员则会取消资格";
								Locate(XLocation + 2, YLocation + 1);
								cout << "如果是群员就设置为管理员";
								Sleep(2400);
								Locate(XLocation + 2, YLocation);
								cout << "                      ";
								Locate(XLocation + 2, YLocation + 1);
								cout << "                        ";
								Locate(XLocation + 2, YLocation);
								cout << "输入对方QQ号码：";
								cin >> aaa;
								if (aaa.compare("$exit$") == 0) {
									Exit = true;
									break;
								}
								AccountID = (*Admin).ReturnPlatformID(aaa);
							} while (AccountID <= 0);
							if (Exit) {
								Exit = false;
								break;
							}
							cout << "                              ";
							if ((*ppp).QueryIdentity(AccountID) == 1) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 你是群主欸。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 2) {
								AccountID = (*ppp).ManageGroupAdmin(AccountID, "Del");
								if (AccountID == 1) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 删除成功";
									(*ppp).SaveData();
									Sleep(1200);
									GroupPage(ppp);
								}
								else if (AccountID == -2) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 无法删除";
								}
								else if (AccountID == 0) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 没有权限";
								}
							}
							else if ((*ppp).QueryIdentity(AccountID) == 3) {
								AccountID = (*ppp).ManageGroupAdmin(AccountID, "Add");
								if (AccountID == 1) {
									WriteLog("设置管理员" + aaa);
									Locate(XLocation + 2, YLocation + 1);
									cout << " 添加成功";
									(*ppp).SaveData();
									Sleep(1200);
									GroupPage(ppp);
								}
								else if (AccountID == -1) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 已是管理";
								}
								else if (AccountID == 0) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 没有权限";
								}
							}
							else if ((*ppp).QueryIdentity(AccountID) == 4) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 你要是愿意可以先拉他入群";
							}
							delete(Admin);
							Sleep(1000);
							break;
						}
						default: {
							break; 
						}
						}
						if (aaa.compare("5") == 0) {
							break;
						}
					} while (aaa.compare("5") != 0);
					DisFriPage((*ppp).ReturnMemberList().size() + 15);
					delete(ppp);
					break;
				}
				//管理员
				case 2: {
					delete(pp);
					class_QQGroup4Manager* ppp;
					ppp = new(class_QQGroup4Manager)(-1);
					(*ppp).ReadData(ax);
					GroupPage(ppp);
					string aaa;
					do {
						do {
							Locate(XLocation + 2, YLocation);
							cout << "                             ";
							Locate(XLocation + 2, YLocation);
							cin >> aaa;
							getchar();
						} while (Str2Num(aaa) < 1 || Str2Num(aaa) > 5);
						switch (Str2Num(aaa))
						{
							//拉人
						case 1: {
							Locate(XLocation + 2, YLocation);
							cout << "     ";
							int AccountID;
							class_Admin* Admin;
							Admin = new(class_Admin);
							do {
								Locate(XLocation + 2, YLocation);
								cout << "                              ";
								Locate(XLocation + 2, YLocation);
								cout << "输入对方QQ号码：";
								cin >> aaa; 
								if (aaa.compare("$exit$") == 0) {
									Exit = true;
									break;
								}
								AccountID = (*Admin).ReturnPlatformID(aaa);
							} while (AccountID > 0);
							if (Exit) {
								Exit = false;
								break;
							}
							if ((*ppp).QueryIdentity(AccountID) == 1) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 群主就不要再加了。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 2) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 他已经是管理员了。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 3) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 别试了他是群员。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 4) {
								AccountID = (*ppp).ManageGroupMember(AccountID, "Add");
								if (AccountID == 1) {
									WriteLog("拉人" + aaa);
									Locate(XLocation + 2, YLocation + 1);
									cout << " 添加成功";
									Sleep(1200);
									(*ppp).SaveData();
									GroupPage(ppp);
								}
								else if (AccountID == -1) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 已是群员";
								}
								else if (AccountID == 0) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 没有权限";
								}
							}
							delete(Admin);
							Sleep(1000);
							break;
						}
							//踢人
						case 2: {
							Locate(XLocation + 2, YLocation);
							cout << "     ";
							int AccountID;
							class_Admin* Admin;
							Admin = new(class_Admin);
							do {
								Locate(XLocation + 2, YLocation);
								cout << "                              ";
								Locate(XLocation + 2, YLocation);
								cout << "输入对方QQ号码：";
								cin >> aaa;
								if (aaa.compare("$exit$") == 0) {
									Exit = true;
									break;
								}
								AccountID = (*Admin).ReturnPlatformID(aaa);
							} while (AccountID > 0);
							if (Exit) {
								Exit = false;
								break;
							}
							if ((*ppp).QueryIdentity(AccountID) == 1) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 自己都删？";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 2) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 请先取消管理员身份";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 3) {
								AccountID = (*ppp).ManageGroupMember(AccountID, "Del");
								if (AccountID == 1) {
									WriteLog("踢人" + aaa);
									Locate(XLocation + 2, YLocation + 1);
									cout << " 删除成功";
									Sleep(1200);
									(*ppp).SaveData();
									GroupPage(ppp);
								}
								else if (AccountID == -2) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 未找到该群员";
								}
								else if (AccountID == 0) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 没有权限";
								}
							}
							else if ((*ppp).QueryIdentity(AccountID) == 4) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 纯路人……";
							}
							delete(Admin);
							Sleep(1000);
							break;
						}
							//改群名
						case 3: {
							Locate(XLocation + 2, YLocation);
							cout << "     ";
							do {
								Locate(XLocation + 2, YLocation);
								cout << "输入新群名：";
								cin >> aaa;
							} while (aaa.compare("$exit$") != 0 || aaa.compare("$empty$") == 0);
							if (aaa.compare("$exit$") == 0) {
								break;
							}
							else {
								WriteLog("改群名" + aaa);
								aaa = (*ppp).ChangeGroupName(aaa);
								Locate(XLocation + 2, YLocation);
								cout << "成功了                 ";
								(*ppp).SaveData();
								Sleep(1200);
								GroupPage(ppp);
							}
							break;
						}
						default:
							break;
						}
						if (aaa.compare("4") == 0) {
							break;
						}
					} while (aaa.compare("4") != 0);
					DisFriPage((*ppp).ReturnMemberList().size() + (*ppp).ReturnGroupAdmin().size() + 15);
					delete(ppp);
					break;
				}
				//群员
				case 3: {
					delete(pp);
					class_QQGroup4Member* ppp;
					ppp = new(class_QQGroup4Member);
					(*ppp).ReadData(ax);
					GroupPage(ppp);
					string aaa;
					do {
						do {
							Locate(XLocation + 2, YLocation);
							cout << "                             ";
							Locate(XLocation + 2, YLocation);
							cin >> aaa;
						} while (Str2Num(aaa) < 1 || Str2Num(aaa) > 5);
						switch (Str2Num(aaa))
						{
							//拉人
						case 1: {
							Locate(XLocation + 2, YLocation);
							cout << "     ";
							int AccountID;
							class_Admin* Admin;
							Admin = new(class_Admin);
							do {
								Locate(XLocation + 2, YLocation);
								cout << "                              ";
								Locate(XLocation + 2, YLocation);
								cout << "输入对方QQ号码：";
								cin >> aaa;
								if (aaa.compare("$exit$") == 0) {
									Exit = true;
									break;
								}
								AccountID = (*Admin).ReturnPlatformID(aaa);
							} while (AccountID > 0);
							if (Exit) {
								Exit = false;
								break;
							}
							if ((*ppp).QueryIdentity(AccountID) == 1) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 群主就不要再加了。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 2) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 他已经是管理员了。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 3) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 别试了他是群员。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 4) {
								AccountID = (*ppp).ManageGroupMember(AccountID, "Add");
								if (AccountID == 1) {
									WriteLog("拉人" + aaa);
									Locate(XLocation + 2, YLocation + 1);
									cout << " 添加成功";
									Sleep(1200);
									(*ppp).SaveData();
									GroupPage(ppp);
								}
								else if (AccountID == -1) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 已是群员";
								}
								else if (AccountID == 0) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 没有权限";
								}
							}
							delete(Admin);
							Sleep(1000);
							break;
						}
							//退群
						case 2: {
							Locate(XLocation + 2, YLocation);
							cout << "     ";
							(*ppp).ManageGroupMember(Str2Num((*p).ReturnInfo("PlatformID")), "Out");
							for (unsigned int i = 0; i < (*p).LocalGroupsList.size(); i++) {
								if ((*p).LocalGroupsList[i].ReturnGroupID() == (*ppp).ReturnGroupID()) {
									(*p).LocalGroupsList.erase((*p).LocalGroupsList.begin() + i);
									(*p).SaveThis();
									aaa = "3";
									WriteLog("退群");
									break;
								}
							}
							break;
						}
						default:
							break;
						}
						if (aaa.compare("3") == 0) {
							break;
						}
					} while (aaa.compare("3") != 0);
					DisFriPage((*ppp).ReturnMemberList().size() + (*ppp).ReturnGroupAdmin().size() + 15);
					delete(ppp);
					break;
				}
				//路人
				case 4: {
					GroupCard(*pp, 0);
					Locate(61, 12);
					cout << "按下y加入该群";
					class_Admin* Admin;
					Admin = new(class_Admin);
					if ((*Admin).FindMember(Num2Str((*pp).ReturnManager())) != (*Admin).FindMember((*p).ReturnInfo("PlatformID"))) {
						Locate(60, 13);
						cout << " 穿越次元的联系？";
						(*pp).SaveData();
					}
					else if (getchar() == 'y' || getchar() == 'Y') {
						if ((*pp).ManageGroupMember(Str2Num((*p).ReturnInfo("PlatformID")), "Add") == 1) {
							Locate(60, 13);
							cout << " 成功了";
							WriteLog("加入群聊");
							(*pp).SaveData();
						}
						else {
							Locate(60, 13);
							cout << " 失败了";
							(*pp).SaveData();
						}
						Sleep(1200);
						DisFriPage(7);
					}
					break;
				}
				default: {
					break;
				}
				}
			}
			XLocation = 15;
			YLocation = 4;
			break;
		}
			//信息
		case 4: {
			//是否有申请好友
			string aaa;
			class_Admin* Admin;
			Admin = new(class_Admin);
			vector<int> aa = (*Admin).FindRequest(Str2Num((*p).ReturnInfo("PlatformID")));
			XLocation = 60;
			YLocation = 4;
			if (aa.size() != 0) {
				Locate(XLocation, YLocation++);
				cout << "有" << aa.size() << "个好友申请" << " y接受、n拒绝";
				Sleep(2000);
				for (unsigned int i = 0; i < aa.size(); i++) {
					QQInfoCard(aa[i], i);
					if (getchar() == 'y') {
						if ((*Admin).BuildShip(Str2Num((*p).ReturnInfo("PlatformID")), aa[i]) != 1)
							exit(0);
						(*p).LocalFriendsList.PushInFriend(aa[i]);
						WriteLog("同意好友" + Num2Str(aa[i]));
					}
					else if (getchar() == 'n') {
						(*Admin).CancelShip(Str2Num((*p).ReturnInfo("PlatformID")), aa[i]);
						WriteLog("不同意好友" + Num2Str(aa[i]));
					}
				}
				DisFriPage(aa.size());
				delete(Admin);
			}
			else {
				Locate(XLocation, YLocation);
				cout << "无未读消息";
				Sleep(1000);
				Locate(XLocation, YLocation++);
				cout << "个人信息    ";
				QQInfoCard_2(Str2Num((*p).ReturnInfo("PlatformID")), 1);
				Locate(XLocation, 12);
				cout << "按下y修改绑定的微信";
				if (getchar() == 'y') {
					YLocation = 15;
					XLocation = 60;
					OutputBox(3, 41);
					Locate(62, 16);
					cin >> aaa;
					class_Admin* Admin;
					Admin = new(class_Admin);
					if (((*Admin).FindMember(aaa) / 10) % 10 == 3) {
						Locate(61, 19);
						cout << "输入被绑定的账户的密码：";
						string bbb = "$empty$";
						//验证密码
						do {
							cin >> bbb;
							if (bbb.compare("$exit$") == 0) {
								break;
							}
							if (bbb.compare(GetLoginInfo(Num2Str((*Admin).ReturnPlatformID(aaa)), "Password")) == 0) {
								if ((*p).ReturnInfo("BindingID").empty());
								else {
									class_PlatformBody wewe("login");
									wewe.ReadNew((*Admin).ReturnPlatformID((*p).ReturnInfo("BindingID")));
									wewe.ModifyBindingID(-10);
									wewe.SaveThis();
								}
								(*p).ModifyBindingID((*Admin).ReturnPlatformID(aaa));
								class_PlatformBody wechat("login");
								wechat.ReadNew((*Admin).ReturnPlatformID(aaa));
								wechat.ModifyBindingID(Str2Num((*p).ReturnInfo("PlatformID")));
								wechat.SaveThis();
								(*p).SaveThis();
								Locate(61, 20);
								cout << "成功";
								WriteLog("改绑微信" + aaa);
								break;
							}
							Locate(61, 19);
							cout << "                                         ";
							Locate(61, 19);
							cout << "密码错误：";
						} while (bbb.compare("$exit$") == 0 || bbb.compare(GetLoginInfo(Num2Str((*Admin).ReturnPlatformID(aaa)), "Password")) == 0);
					}
					else {
						Locate(61, 20);
						cout << "微信号不存在";
					}
					Sleep(1200);
				}
				DisFriPage(6);
			}
			break;
		}
			//注销
		case 5: {
			Exit = true;
			break;
		}
		default: {
			Exit = false;
			break; 
		}
		}
		XLocation = 15;
		YLocation = 4;
		if (Exit) {
			break;
		}
	} while (Option.compare("$exit$") != 0);
	WriteLog("注销");
}
void DisFriPage(const int a) {
	for (int i = 0; i < a + 15; i++) {
		Locate(58, i + 4);
		cout << "                                           ";
	}
	Locate(15, 4);
}
int FriendsListPage(const vector<int> a, const int b) {
	string GetStr;//搜索用
	if (a.size() == 0) {
		WriteLog("查看好友");
		Locate(61, 4);
		cout << "空空如也……在下面搜索QQ用户";
		Locate(60, 5);
		cout << "╭ ───────────────────────────────────── ╮";
		Locate(60, 6);
		cout << "│                                       │";
		Locate(60, 7);
		cout << "╰ ───────────────────────────────────── ╯";
		YLocation = 8;
		Locate(62, 6);
	}
	else {
		for (unsigned int i = 0; i < a.size(); i++) {
			QQInfoCard(a[i], i);
		}
		YLocation = 4 + a.size() * 8;
		Locate(60, YLocation++);
		cout << "╭ ───────────────────────────────────── ╮";
		Locate(60, YLocation++);
		cout << "│                                       │";
		Locate(60, YLocation++);
		cout << "╰ ───────────────────────────────────── ╯";
	}
	class_Admin* Admin;
	Admin = new(class_Admin);
	vector<int> rf = (*Admin).RecommendFriends(b);
	YLocation = 9 + a.size() * 8;
	Locate(60, YLocation++);
	cout << "推荐好友：";
	if (a.size() == 0) {
		cout << "暂无";
	}
	for (unsigned int i = 0; i < rf.size(); i++) {
		QQInfoCard(rf[i], a.size() + i + 1);
	}
	do {
		if (a.size() == 0) {
			Locate(62, 6);
			cout << "                   ";
			Locate(62, 6);
			cin >> GetStr;
			WriteLog("搜索好友" + GetStr);
		}
		else {
			YLocation--;
			Locate(62, 5 + 8 * a.size());
			cout << "                   ";
			Locate(62, 5 + 8 * a.size());
			cin >> GetStr;
			WriteLog("搜索好友" + GetStr);
		}
		if (GetStr.compare("$exit$") == 0) {
			DisFriPage(8);
			break;
		}
		int AccountID = (*Admin).ReturnPlatformID(GetStr);
		if (AccountID != 0) {
			DisFriPage(a.size()*9);
			QQInfoCard(AccountID, 0);
			YLocation = 12;
			Locate(XLocation, YLocation++);
			cout << "输入y申请添加好友";
			getchar();
			if (getchar() == 'y') {
				WriteLog("申请好友" + Num2Str(AccountID));
				return AccountID;
			}
			else {
				DisFriPage(8);
				break;
			}
		}
		else {
			Locate(61, YLocation + 1);
			YLocation++;
			cout << "没有查询到此人，仅搜索支持QQ号";
			Sleep(1000);
			Locate(61, YLocation);
			cout << "                              ";
		}
	} while (GetStr.compare("$exit$") != 0);
	delete(Admin);
	return -10;
}
int GroupListPage(vector<class_Group> a) {
	if (a.size() == 0) {
		Locate(61, 4);
		cout << "空空如也……你还没有加入任何群聊。";
		Sleep(2000);
		DisFriPage(0);
		return 0;
	}
	else {
		WriteLog("查看群聊");
		for (unsigned int i = 0; i < a.size(); i++) {
			GroupCard(a[i], i);
		}
		Locate(60, a.size() * 7 + 5);
		system("pause");
	}
	DisFriPage(a.size() * 6);
	return 0;
}
//******************************************************************
//******************************************************************
class_PlatformBody* WeChatAction_Plus(const int WeChatID) {
	class_PlatformBody* p;
	p = new(class_PlatformBody)("login");
	(*p).ReadNew(WeChatID);
	return p;
}
//微信
void WeChatAction(class_PlatformBody* p) {
	bool Exit = false;
	string Option;
	do {
		bool judge = false;
		class_Admin* Admin;
		Admin = new(class_Admin);
		vector<int> xx = (*Admin).FindFriends(Str2Num((*p).ReturnInfo("PlatformID")));
		for (unsigned int i = 0; i < xx.size(); i++) {
			judge = false;
			for (unsigned int n = 0; n < (*p).LocalFriendsList.ExportFriendsData().size(); n++) {
				if ((*p).LocalFriendsList.ExportFriendsData()[n] == xx[i]) {
					judge = true;
					break;
				}
			}
			if (!judge) {
				(*p).LocalFriendsList.PushInFriend(xx[i]);
			}
		}
		delete(Admin);
		//群
		judge = false;
		class_WeChatGroup4Member* work;
		work = new(class_WeChatGroup4Member);
		for (int i = 30001; i < 30100; i++) {
			if ((*work).ReadData(i) == -1) {
				break;
			}
			else {
				if ((*work).QueryIdentity(Str2Num((*p).ReturnInfo("PlatformID"))) == 4) {
					continue;
				}
				else {
					for (unsigned int n = 0; n < (*p).LocalGroupsList.size(); n++) {
						if ((*p).LocalGroupsList[n].ReturnGroupID() == (*work).ReturnGroupID()) {
							judge = true;
						}
					}
					if (judge == false) {
						(*p).LocalGroupsList.push_back((*work));
					}
					(*work).SaveData();
					judge = false;
				}
			}
		}
		delete(work);
		OutputBox(14, 41);
		Locate(XLocation + 3, YLocation);
		cout << "  微信 ";
		XLocation += 4;
		YLocation += 2;
		Locate(XLocation, YLocation++);
		cout << "欢迎回来，" << (*p).ReturnInfo("name") << "\n";
		Locate(XLocation, YLocation++);
		Locate(XLocation, YLocation++);
		cout << "1 通讯录";
		Locate(XLocation, YLocation++);
		cout << "2 群聊列表";
		Locate(XLocation, YLocation++);
		cout << "3 添加、管理或创建群";
		Locate(XLocation, YLocation++);
		cout << "4 新朋友";
		Locate(XLocation, YLocation++);
		cout << "5 退出微信";
		Locate(XLocation, YLocation++);
		Locate(XLocation, YLocation++);
		cout << "→";
		cin >> Option;
		getchar();
		switch (Str2Num(Option))
		{
			//查看好友，可以添加
		case 1: {
			int aa = FriendsListPage_2((*p).ReturnInfo(), Str2Num((*p).ReturnInfo("PlatformID")));
			if (aa > 0) {
				class_Admin* Admin;
				Admin = new(class_Admin);
				int bbb = (*Admin).ReturnPlatformID(Num2Str(aa));
				if ((*Admin).FindMember((*p).ReturnInfo("PlatformID")) != (*Admin).FindMember(Num2Str(bbb))) {
					Locate(XLocation, YLocation++);
					cout << "不同世界的人是不能在一起的哟，";
					WriteLog("申请好友失败");
					system("pause");
					DisFriPage((*p).ReturnInfo().size() * 10);
					break;
				}
				int bb = (*p).LocalFriendsList.AddFriend(Str2Num((*p).ReturnInfo("PlatformID")), bbb);
				if(Str2Num((*p).ReturnInfo("PlatformID"))== bbb){
					(*Admin).CancelShip(Str2Num((*p).ReturnInfo("PlatformID")), bbb);
					delete(Admin);
					Locate(XLocation, YLocation++);
					cout << "的确要和自己做朋友呢，";
					WriteLog("申请好友失败");
					system("pause");
					DisFriPage((*p).ReturnInfo().size() * 10);
				}
				else if (bb == 1) {
					Locate(XLocation, YLocation++);
					cout << "耐心等待回应，";
					WriteLog("申请好友成功");
					system("pause");
					DisFriPage((*p).ReturnInfo().size() * 10);
				}
				else if (bb == 0 || bb == -2) {
					Locate(XLocation, YLocation++);
					cout << "已添加至通讯录，";
					WriteLog("申请好友失败，已添加");
					system("pause");
					DisFriPage((*p).ReturnInfo().size() * 10);
				}
				else if (bb == -1) {
					Locate(XLocation, YLocation++);
					cout << "系统数据错误，";
					WriteLog("申请好友失败，系统数据错误");
					system("pause");
					DisFriPage((*p).ReturnInfo().size() * 10);
				}
				else if (bb == -2) {
					Locate(XLocation, YLocation++);
					cout << "讲道理是个BUG但是我自动修好了厉害吧嘿嘿嘿，";
					system("pause");
					DisFriPage((*p).ReturnInfo().size() * 10);
				}
				else if (bb == -4 || bb == -3) {
					Locate(XLocation, YLocation++);
					cout << "请勿重复申请，";
					WriteLog("申请好友失败，重复申请");
					system("pause");
					DisFriPage((*p).ReturnInfo().size() * 10);
				}
				else if (bb == -10) {
					DisFriPage((*p).ReturnInfo().size() * 10);
				}
			}
			break;
		}
			  //查看群
		case 2: {
			GroupListPage((*p).LocalGroupsList);
			break;
		}
			  //创建或管理群
		case 3: {
			YLocation = 4;
			Locate(60, YLocation++);
			cout << "╭ ───────────────────────────────────── ╮";
			Locate(60, YLocation++);
			cout << "│                                       │";
			Locate(60, YLocation++);
			cout << "╰ ───────────────────────────────────── ╯";
			Locate(63, YLocation - 2);
			cin >> Option;
			getchar();
			if (Option.compare("$exit$") == 0) {
				Option = "$empty$";
				DisFriPage(2);
				break;
			}
			class_WeChatGroup4Member* pp;
			pp = new(class_WeChatGroup4Member);
			int bx = (*pp).ReadData(Str2Num(Option));
			int ax = (*pp).ReturnGroupID();
			//创建群聊
			if (Option.compare("+") == 0 || Option.compare("create") == 0) {
				class_WeChatGroup4Manager* pppp;
				pppp = new(class_WeChatGroup4Manager)(Str2Num((*p).ReturnInfo("PlatformID")));
				do {
					Locate(63, YLocation - 2);
					cout << "输入群名：";
					cin >> Option;
					if (Option.compare("$exit$") == 0) {
						break;
					}
					(*pppp).ChangeGroupName(Option);
				} while (Option.compare("$empty$") == 0);
				if (Option.compare("$exit$") == 0) {
					break;
				}
				else {
					if (pppp != NULL) {
						(*p).LocalGroupsList.push_back(*pppp);
						(*p).SaveThis(); (*pppp).SaveData();
						Locate(63, YLocation - 2);
						cout << "创建成功，群号为：" << (*pppp).ReturnGroupID();
						WriteLog("创建群聊");
					}
				}
				delete(pppp);
			}
			//群号错误
			else if ((Str2Num(Option) < 30000) || (Str2Num(Option) > 30100)) {
				Locate(60, YLocation++);
				cout << "群号格式非法，";
				system("pause");
				DisFriPage(2);
				break;
			}
			//找不到群
			else if (bx == -1) {
				Locate(60, YLocation++);
				cout << "查找失败，";
				WriteLog("查找微信群聊失败");
				system("pause");
				DisFriPage(2);
				delete(pp);
				break;
			}
			else {
				switch (GetGroup((*pp).ReturnGroupID(), Str2Num((*p).ReturnInfo("PlatformID")))) {
					//群主
				case 1: {
					delete(pp);
					class_WeChatGroup4Manager* ppp;
					ppp = new(class_WeChatGroup4Manager)(-1);
					(*ppp).ReadData(ax);
					GroupPage(ppp);
					string aaa;
					do {
						do {
							Locate(XLocation + 2, YLocation);
							cout << "                             ";
							Locate(XLocation + 2, YLocation);
							cin >> aaa;
							getchar();
						} while (Str2Num(aaa) < 1 || Str2Num(aaa) > 5);
						switch (Str2Num(aaa))
						{
							//拉人
						case 1: {
							Locate(XLocation + 2, YLocation);
							cout << "     ";
							int AccountID;
							class_Admin* Admin;
							Admin = new(class_Admin);
							do {
								Locate(XLocation + 2, YLocation);
								cout << "                              ";
								Locate(XLocation + 2, YLocation);
								cout << "输入对方微信号：";
								cin >> aaa;
								if (aaa.compare("$exit$") == 0) {
									Exit = true;
									break;
								}
								getchar();
								AccountID = (*Admin).ReturnPlatformID(aaa);
							} while (AccountID <= 0);
							if (Exit) {
								Exit = false;
								break;
							}
							if ((*ppp).QueryIdentity(AccountID) == 1) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 拉群主可还行。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 2) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 他已经是管理员了。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 3) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 别试了他是群员。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 4) {
								AccountID = (*ppp).ManageGroupMember(AccountID, "Add");
								if (AccountID == 1) {
									WriteLog("拉人" + aaa);
									cout << " 添加成功";
									(*ppp).SaveData();
									Sleep(1200);
									GroupPage(ppp);
								}
								else if (AccountID == -1) {
									cout << " 已是群员";
								}
								else if (AccountID == 0) {
									cout << " 没有权限";
								}
							}
							delete(Admin);
							Sleep(1000);
							break;
						}
							//踢人
						case 2: {
							Locate(XLocation + 2, YLocation);
							cout << "     ";
							int AccountID;
							class_Admin* Admin;
							Admin = new(class_Admin);
							do {
								Locate(XLocation + 2, YLocation);
								cout << "                              ";
								Locate(XLocation + 2, YLocation);
								cout << "输入对方微信号：";
								cin >> aaa;
								if (aaa.compare("$exit$") == 0) {
									Exit = true;
									break;
								}
								AccountID = (*Admin).ReturnPlatformID(aaa);
							} while (AccountID <= 0);
							if (Exit) {
								Exit = false;
								break;
							}
							if ((*ppp).QueryIdentity(AccountID) == 1) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 自己都删？";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 2) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 请先取消管理员身份";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 3) {
								AccountID = (*ppp).ManageGroupMember(AccountID, "Del");
								if (AccountID == 1) {
									WriteLog("踢人" + aaa);
									Locate(XLocation + 2, YLocation + 1);
									cout << " 删除成功";
									(*ppp).SaveData();
									Sleep(1200);
									GroupPage(ppp);
								}
								else if (AccountID == -2) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 未找到该群员";
								}
								else if (AccountID == 0) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 没有权限";
								}
							}
							else if ((*ppp).QueryIdentity(AccountID) == 4) {
								cout << " 纯路人……";
							}
							delete(Admin);
							Sleep(1000);
							break;
						}
							//改群名
						case 3: {
							Locate(XLocation + 2, YLocation);
							cout << "     ";
							do {
								Locate(XLocation + 2, YLocation);
								cout << "                              ";
								Locate(XLocation + 2, YLocation);
								cout << "输入新群名：";
								cin >> aaa;
							} while (aaa.compare("$empty$") == 0);
							if (aaa.compare("$exit$") == 0) {
								break;
							}
							else {
								WriteLog("改群名" + aaa);
								aaa = (*ppp).ChangeGroupName(aaa);
								Locate(XLocation + 2, YLocation);
								cout << "成功了                 ";
								(*ppp).SaveData();
								Sleep(1200);
								GroupPage(ppp);
							}
							break;
						}
						default:
							break;
						}
						if (aaa.compare("4") == 0) {
							break;
						}
					} while (aaa.compare("4") != 0);
					DisFriPage((*ppp).ReturnMemberList().size() + 15);
					delete(ppp);
					break;
				}
					//群员
				case 3: {
					delete(pp);
					class_WeChatGroup4Member* ppp;
					ppp = new(class_WeChatGroup4Member);
					(*ppp).ReadData(ax);
					GroupPage(ppp);
					string aaa;
					do {
						do {
							Locate(XLocation + 2, YLocation);
							cout << "                             ";
							Locate(XLocation + 2, YLocation);
							cin >> aaa;
						} while (Str2Num(aaa) < 1 || Str2Num(aaa) > 5);
						switch (Str2Num(aaa))
						{
							//拉人
						case 1: {
							Locate(XLocation + 2, YLocation);
							cout << "     ";
							int AccountID;
							class_Admin* Admin;
							Admin = new(class_Admin);
							do {
								Locate(XLocation + 2, YLocation);
								cout << "                              ";
								Locate(XLocation + 2, YLocation);
								cout << "输入对方微信号：";
								cin >> aaa;
								if (aaa.compare("$exit$") == 0) {
									Exit = true;
									break;
								}
								AccountID = (*Admin).ReturnPlatformID(aaa);
							} while (AccountID > 0);
							if (Exit) {
								Exit = false;
								break;
							}
							if ((*ppp).QueryIdentity(AccountID) == 1) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 群主就不要再加了。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 2) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 他已经是管理员了。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 3) {
								Locate(XLocation + 2, YLocation + 1);
								cout << " 别试了他是群员。";
							}
							else if ((*ppp).QueryIdentity(AccountID) == 4) {
								AccountID = (*ppp).ManageGroupMember(AccountID, "Add");
								if (AccountID == 1) {
									WriteLog("拉人" + aaa);
									Locate(XLocation + 2, YLocation + 1);
									cout << " 添加成功";
									Sleep(1200);
									(*ppp).SaveData();
									GroupPage(ppp);
								}
								else if (AccountID == -1) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 已是群员";
								}
								else if (AccountID == 0) {
									Locate(XLocation + 2, YLocation + 1);
									cout << " 没有权限";
								}
							}
							delete(Admin);
							Sleep(1000);
							break;
						}
							//退群
						case 2: {
							Locate(XLocation + 2, YLocation);
							cout << "     ";
							(*ppp).ManageGroupMember(Str2Num((*p).ReturnInfo("PlatformID")), "Out");
							for (unsigned int i = 0; i < (*p).LocalGroupsList.size(); i++) {
								if ((*p).LocalGroupsList[i].ReturnGroupID() == (*ppp).ReturnGroupID()) {
									(*p).LocalGroupsList.erase((*p).LocalGroupsList.begin() + i);
									(*p).SaveThis();
									aaa = "3";
									WriteLog("退群");
									break;
								}
							}
							break;
						}
						default:
							break;
						}
						if (aaa.compare("3") == 0) {
							break;
						}
					} while (aaa.compare("3") != 0);
					DisFriPage((*ppp).ReturnMemberList().size() + 15);
					delete(ppp);
					break;
				}
					//路人
				case 4: {
					GroupCard(*pp, 0);
					Locate(61, 11);
					system("pause");
					DisFriPage(5);
					break;
				}
				default: {
					break;
				}
				}
			}
			XLocation = 15;
			YLocation = 4;
			break;
		}
			  //信息
		case 4: {
			//是否有申请好友
			string aaa;
			class_Admin* Admin;
			Admin = new(class_Admin);
			vector<int> aa = (*Admin).FindRequest(Str2Num((*p).ReturnInfo("PlatformID")));
			XLocation = 60;
			YLocation = 4;
			if (aa.size() != 0) {
				Locate(XLocation, YLocation++);
				cout << "有" << aa.size() << "个好友申请" << " y接受、n拒绝";
				Sleep(2000);
				for (unsigned int i = 0; i < aa.size(); i++) {
					WeChatInfoCard(aa[i], i);
					if (getchar() == 'y') {
						if ((*Admin).BuildShip(Str2Num((*p).ReturnInfo("PlatformID")), aa[i]) != 1)
							exit(0);
						(*p).LocalFriendsList.PushInFriend(aa[i]);
						WriteLog("同意好友申请" + Num2Str(aa[i]));
					}
					else if (getchar() == 'n') {
						(*Admin).CancelShip(Str2Num((*p).ReturnInfo("PlatformID")), aa[i]);
						WriteLog("拒绝好友申请" + Num2Str(aa[i]));
					}
				}
				DisFriPage(aa.size());
				delete(Admin);
			}
			else {
				Locate(XLocation, YLocation);
				cout << "无未读消息";
				Sleep(1000);
				Locate(XLocation, YLocation++);
				cout << "个人信息    ";
				WeChatInfoCard_2(Str2Num((*p).ReturnInfo("PlatformID")), 0);
				Locate(XLocation, 11);
				cout << "按下y修改绑定的QQ";
				if (getchar() == 'y') {
					YLocation = 14;
					XLocation = 60;
					OutputBox(3, 41);
					Locate(62, 16);
					cin >> aaa;
					class_Admin* Admin;
					Admin = new(class_Admin);
					Locate(60, 19);
					if (((*Admin).FindMember(aaa) / 10) % 10 == 2) {
						Locate(61, 19);
						cout << "输入被绑定的账户的密码：";
						string bbb = "$empty$";
						//验证密码
						do {
							cin >> bbb;
							if (bbb.compare("$exit$") == 0) {
								break;
							}
							if (bbb.compare(GetLoginInfo(Num2Str((*Admin).ReturnPlatformID(aaa)), "Password")) == 0) {
								if ((*p).ReturnInfo("BindingID").empty());
								else {
									class_PlatformBody qqq("login");
									qqq.ReadNew((*Admin).ReturnPlatformID((*p).ReturnInfo("BindingID")));
									qqq.ModifyBindingID(-10);
									qqq.SaveThis();
								}
								(*p).ModifyBindingID((*Admin).ReturnPlatformID(aaa));
								class_PlatformBody qq("login");
								qq.ReadNew((*Admin).ReturnPlatformID(aaa));
								qq.ModifyBindingID(Str2Num((*p).ReturnInfo("PlatformID")));
								qq.SaveThis();
								(*p).SaveThis();
								Locate(61, 20);
								cout << "成功";
								WriteLog("改绑" + aaa);
								break;
							}
							Locate(61, 19);
							cout << "                                         ";
							Locate(61, 19);
							cout << "密码错误：";
						} while (bbb.compare("$exit$") == 0|| bbb.compare(GetLoginInfo(Num2Str((*Admin).ReturnPlatformID(aaa)), "Password")) == 0);
					}
					else {
						Locate(61, 20);
						cout << "QQ号不存在";
					}
					Sleep(1200);
				}
				DisFriPage(6);
			}
			break;
		}
			  //注销
		case 5: {
			Exit = true;
			break;
		}
		default: {
			Exit = false;
			break; 
		}
		}
		XLocation = 15;
		YLocation = 4;
		if (Exit) {
			break;
		}
	} while (Option.compare("$exit$") != 0);
}
int FriendsListPage_2(const vector<int> a, const int b) {
	string GetStr;//搜索用
	if (a.size() == 0) {
		Locate(61, 4);
		cout << "空空如也……在下面搜索微信用户";
		Locate(60, 5);
		cout << "╭ ───────────────────────────────────── ╮";
		Locate(60, 6);
		cout << "│                                       │";
		Locate(60, 7);
		cout << "╰ ───────────────────────────────────── ╯";
		YLocation = 8;
		Locate(62, 6);
	}
	else {
		WriteLog("查看好友");
		for (unsigned int i = 0; i < a.size(); i++) {
			WeChatInfoCard(a[i], i);
		}
		YLocation = 4 + a.size() * 8;
		Locate(60, YLocation++);
		cout << "╭ ───────────────────────────────────── ╮";
		Locate(60, YLocation++);
		cout << "│                                       │";
		Locate(60, YLocation++);
		cout << "╰ ───────────────────────────────────── ╯";
	}
	class_Admin* Admin;
	Admin = new(class_Admin);
	vector<int> rf = (*Admin).RecommendFriends(b);
	for (unsigned int i = 0; i < rf.size(); i++) {
		WeChatInfoCard_2(rf[i], a.size() + i + 1);
	}
	do {
		if (a.size() == 0) {
			Locate(62, 6);
			cout << "                   ";
			Locate(62, 6);
			cin >> GetStr;
		}
		else {
			YLocation--;
			Locate(62, 5 + 8 * a.size());
			cout << "                   ";
			Locate(62, 5 + 8 * a.size());
			cin >> GetStr;
		}
		if (GetStr.compare("$exit$") == 0) {
			DisFriPage(8);
			break;
		}
		int AccountID = (*Admin).ReturnPlatformID(GetStr);
		if (AccountID != 0) {
			DisFriPage(a.size() * 9);
			WeChatInfoCard(AccountID, 0);
			YLocation = 12;
			Locate(XLocation, YLocation++);
			cout << "输入y申请添加好友";
			getchar();
			if (getchar() == 'y') {
				WriteLog("申请好友" + Num2Str(AccountID));
				return AccountID;
			}
			else {
				DisFriPage(8);
				break;
			}
		}
		else {
			Locate(61, YLocation + 1);
			YLocation++;
			cout << "没有查询到此人，仅搜索支持微信号";
			Sleep(1000);
			Locate(61, YLocation);
			cout << "                              ";
		}
	} while (GetStr.compare("$exit$") != 0);
	delete(Admin);
	return -10;
}
void WeiBoAction() {
	system("cls");
	XLocation = 15;
	YLocation = 4;
	OutputBox(3,41);
	Locate(18, 5);
	cout << "啥都没有233";
	Locate(16, 7);
	system("pause");
}
//***********************************************

void CMD() {
	string command;
	XLocation = 15;
	YLocation = 4;
	OutputBox(3, 41);
	Locate(17, 5);
	cout << ">>";
	cin >> command;
	if (command.compare("UISpeed") == 0|| command.compare("uispeed") == 0) {
		UISpeed = 15;
	}
	else if (command.compare(0, 8, "UISpeed_", 0, 8) == 0) {
		command = command.substr(8, command.size() - 8);
		if (Str2Num(command) > 0) {
			UISpeed = Str2Num(command);
		}
		else if (command.compare("a") == 0 || command.compare("A") == 0) {
			UISpeed = 15;
		}
		else if (command.compare("b") == 0 || command.compare("B") == 0) {
			UISpeed = 20;
		}
		else if (command.compare("c") == 0 || command.compare("C") == 0) {
			UISpeed = 30;
		}
		else if (command.compare("d") == 0 || command.compare("D") == 0) {
			UISpeed = 0;
		}
	}
	else if (command.compare("inspiration") == 0|| command.compare("INSPIRATION") == 0) {
		Locate(17, 5);
		cout << "                        ";
		Locate(17, 5);
		cout << "Hi~ o(*￣▽￣*)ブ";
	}
	else if (command.compare("zhongjian") == 0 || command.compare("zj") == 0 || command.compare("钟健") == 0) {
		Locate(17, 5);
		cout << "                        ";
		Locate(17, 5);
		cout << "(づ￣ 3￣)づ";
	}
	else if (command.compare("View_log") == 0) {
		system("cls");
		ifstream out;
		string out_;
		out.open("Log.txt", ios::in);
		out.seekg(ios::beg);
		cout << "          日志：" << "\n\n";
		if (out.is_open()) {
			while (!out.eof()) {
				out >> out_;
				cout << "          " << out_ << " ";
				out >> out_;
				cout << out_ << " ";
				out >> out_;
				cout << out_ << "\n";
			}
		}
		else {
			cout << "暂时没有日志。" << "\n";
		}
		out.seekg(ios::end);
		out.close();
		Locate(10, 1);
		system("pause");
		system("cls");
	}
	else {
		Locate(17, 5);
		cout << "                        ";
		Locate(17, 5);
		cout << "没有这条命令";
	}
	Locate(16, 7);
	system("pause");
	system("cls");
	Transition_1(15, 21, 1);
}
