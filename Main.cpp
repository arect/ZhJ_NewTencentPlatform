#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include"Ways.h"
#include"Body.h"
#include"Friends.h"
#include"Admin.h"
#include"Time.h"
#include"UI.h"
#include"Action.h"
using namespace std;
int class_PlatformBody::ConstID = 1;
int class_Group::GroConstID = 20000;
bool Exit = false;
int main() {
	string Option;//选择
	string Account;//输入的账户
	int AccountID;//输入的账户返回的平台ID
	string Password;//获得的密码
	int FalseTime = 0;//密码错误次数
	bool axz = true;
	do {
		system("cls");
		HomePage(axz);
		axz = false;
		cin >> Option;
		getchar();
		switch (Str2Num(Option))
		{
			//QQ
		case 1: {
			WriteLog("进入QQ");
			Transition_1(15, 21, 1);
			do {
				SecondHomePage("QQ");
				cin >> Option;
				getchar();
				switch (Str2Num(Option))
				{
					//登入
				case 1: {
					WriteLog("QQ登入");
					Transition_2(41, 14, 7);
					do {
						//输入账号
						LoginPage("account", "反正这个不会打印出来所以我随便乱写也是可以的对吧(*￣3￣)╭");
						//输入账号
						if (cin >> Account) {
							//退出
							if (Account.compare("$exit$") == 0)
								break;
							class_Admin* Admin;
							Admin = new(class_Admin);
							AccountID = (*Admin).ReturnPlatformID(Account);
							delete(Admin);
							//账号存在
							if (AccountID != 0) {
								//读取密码
								const string Password_ = GetLoginInfo(Num2Str(AccountID), "Password");
								//读取密码成功
								if (Password.compare("$Wrong$") != 0) {
									//输入密码界面
									do {
										LoginPage("password", GetLoginInfo(Num2Str(AccountID), "Name"));
										//输入密码
										int aa = 22;
										do {
												Locate(aa++, 8);
												Password.push_back(_getch());
												if (Password.back() == 13) {
													Password.pop_back();
													break;
												}
												if (Password.back() == 8) {
													if (!Password.empty()) {
														Password.pop_back();
														aa--;
														Locate(aa, 8);
														cout << " ";
													}
													if (!Password.empty()) {
														Password.pop_back();
														aa--;
														Locate(aa, 8);
														cout << " ";
													}
												}
												else cout << "*";
											} while (1);
										if (Password.compare("$exit$") == 0) {
											Password.clear();
											Exit = true;
											break;
										}
										//成功登入
										if (Password.compare(Password_) == 0) {
											Password.clear();
											QQAction(QQAction_Plus(AccountID));
											Exit = true;
											break;
										}
										//密码错误
										else {
											Password.clear();
											continue;
										}
									} while (1);
									if (Exit) {
										break;
									}
								}
								//没找到密码，一般不可能
								else {
									Warning(" 此账户信息受损，请联系管理员 ", "yellow");
									cout << "                 ";
									system("pause");
								}
							}
							else {
								Warning(" 没有查找到此账号 ", "red");
								cout << "                 ";
								system("pause");
							}
						}
					} while (Account.compare("$exit$") != 0);
					Exit = false;
					break;
				}
					//注册
				case 2: {
					WriteLog("QQ注册");
					Transition_2(41, 14, 8);
					QQSignUpPage();
					string temp;
					//*****************************************
					class_PlatformBody NewAccount("new");
					//输入昵称
					while (1) {
						Locate(26, 7);
						cin >> temp;
						if ((temp.compare("$empty$") == 0)) {
							Locate(26, 7);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
							cout << "昵称不合法                   ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
							Sleep(1000);
							Locate(26, 7);
							cout << "                             ";
							continue;
						}
						else if ((temp.compare("钟健") == 0) || (temp.compare("zj") == 0)) {
							Locate(26, 7);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
							cout << "昵称太高贵                   ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
							Sleep(1000);
							Locate(26, 7);
							cout << "                             ";
							continue;
						}
						else if (temp.compare("$exit$") == 0) {
							Exit = true;
							break;
						}
						else {
							temp = NewAccount.ModifyName(temp);
							Exit = false;
							break;
						}
					}
					//*****************************************
					if (Exit) {
						Exit = false;
						break;
					}
					//*****************************************
					//输入生日
					while (1) {
						Locate(26, 8);
						cin >> temp;
						if (temp.compare("$exit$") != 0) {
							int a = Str2Num(temp);
							if (NewAccount.ModifyBirthday(a / 10000, (a % 10000) / 100, a % 100) != a) {
								Locate(26, 8);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
								cout << "输入的时间不合法";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
								Sleep(1000);
								Locate(26, 8);
								cout << "                    ";
							}
							else break;
						}
						else {
							Exit = true;
							break;
						}
					}
					//*****************************************
					if (Exit) {
						Exit = false;
						break;
					}
					//*****************************************
					//输入出生地
					while (1) {
						Locate(28, 9);
						cin >> temp;
						if ((temp.compare("$empty$") == 0) || (temp.compare("钟健") == 0) || (temp.compare("zj") == 0)) {
							Locate(28, 9);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
							cout << "输入不合法                   ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
							Sleep(1000);
							Locate(28, 9);
							cout << "                             ";
							continue;
						}
						else if (temp.compare("$exit$") == 0) {
							Exit = true;
							break;
						}
						else {
							temp = NewAccount.ModifyBirthplace(temp);
							Exit = false;
							break;
						}
					}
					//*****************************************
					if (Exit) {
						Exit = false;
						break;
					}
					//*****************************************
					//输入密码
					Transition_1(8, 19, 4);
					system("cls");
					PasswordInputPage("first");
					string Password_1;
					string Password_2;
					int aa = 20;
					//第一次输入
					do {
						Locate(aa++, 8);
						Password_1.push_back(_getch());
						if (Password_1.back() == 13) {
							Password_1.pop_back();
							break;
						}
						if (Password_1.back() == 8) {
							if (!Password_1.empty()) {
								Password_1.pop_back();
								aa--;
								Locate(aa, 8);
								cout << " ";
							}
							if (!Password_1.empty()) {
								Password_1.pop_back();
								aa--;
								Locate(aa, 8);
								cout << " ";
							}
						}
						else cout << "*";
					} while (1);
					if (Password_1.compare("$exit$") == 0) {
						break;
					}
					Transition_1(8, 19, 4);
					system("cls");
					PasswordInputPage("again");
					aa = 20;
					//第二次确认
					do {
						Locate(aa++, 8);
						Password_2.push_back(_getch());
						if (Password_2.back() == 13) {
							Password_2.pop_back();
							break;
						}
						if (Password_2.back() == 8) {
							if (!Password_2.empty()) {
								Password_2.pop_back();
								aa--;
								Locate(aa, 8);
								cout << " ";
							}
							if (!Password_2.empty()) {
								Password_2.pop_back();
								aa--;
								Locate(aa, 8);
								cout << " ";
							}
						}
						else cout << "*";
					} while (1);
					if (Password_2.compare("$exit$") == 0) {
						break;
					}
					if (Password_1.compare(Password_2) == 0) {
						temp = NewAccount.ModiFyPassword(Password_1);
					}
					else {
						do {
							aa = 20;
							Password_2.clear();
							system("cls");
							PasswordInputPage("wrong");
							do {
								Locate(aa++, 8);
								Password_2.push_back(_getch());
								if (Password_2.back() == 13) {
									Password_2.pop_back();
									break;
								}
								if (Password_2.back() == 8) {
									if (!Password_2.empty()) {
										Password_2.pop_back();
										aa--;
										Locate(aa, 8);
										cout << " ";
									}
									if (!Password_2.empty()) {
										Password_2.pop_back();
										aa--;
										Locate(aa, 8);
										cout << " ";
									}
								}
								else cout << "*";
							} while (1);
							if (Password_1.compare(Password_2) == 0) {
								temp = NewAccount.ModiFyPassword(Password_1);
								break;
							}
						} while (1);
					}
					//*****************************************
					//记录、注册
					class_Admin* Admin;
					Admin = new(class_Admin);
					(*Admin).AddNewMember(Str2Num(NewAccount.ReturnInfo("PlatformID")), Str2Num(NewAccount.ReturnInfo("ID")), "$empty$");
					delete(Admin);
					//*****************************************
					//返回QQ号
					Warning("你的QQ号码是" + NewAccount.ReturnInfo("ID"), "blue");
					Sleep(1000);
					cout << "                ";
					system("pause");
					break;
				}
					//帮助
				case 3: {
					WriteLog("QQ帮助");
					Transition_2(41, 14, 5);
					QQHelpPage();
					getchar();
					Exit = false;
					break;
				}
					//退出
				case 4: {
					WriteLog("QQ返回");
					Exit = true;
					break;
				}
				default: {
					Warning("非法操作，你即将被逮捕！", "red");
					cout << "                 ";
					system("pause");
					break;
				}
				}
				if (Exit) {
					Exit = false;
					break;
				}
			}while (1);
			Exit = false;
			break;
		}
			//微信
		case 2: {
			WriteLog("进入微信");
			Transition_1(15, 21, 1);
			do {
				SecondHomePage("WeChat");
				cin >> Option;
				getchar();
				switch (Str2Num(Option))
				{
					//登入
				case 1: {
					WriteLog("微信登入");
					Transition_2(41, 14, 7);
					do {
						//输入账号
						LoginPage("account", "反正这个不会打印出来所以我随便乱写也是可以的对吧(*￣3￣)╭");
						//输入账号
						if (cin >> Account) {
							//退出
							if (Account.compare("$exit$") == 0)
								break;
							class_Admin* Admin;
							Admin = new(class_Admin);
							AccountID = (*Admin).ReturnPlatformID(Account);
							delete(Admin);
							//账号存在
							if (AccountID != 0) {
								//读取密码
								const string Password_ = GetLoginInfo(Num2Str(AccountID), "Password");
								//读取密码成功
								if (Password.compare("$Wrong$") != 0) {
									//输入密码界面
									do {
										LoginPage("password", GetLoginInfo(Num2Str(AccountID), "Name"));
										//输入密码
										int aa = 22;
										do {
											Locate(aa++, 8);
											Password.push_back(_getch());
											if (Password.back() == 13) {
												Password.pop_back();
												break;
											}
											if (Password.back() == 8) {
												if (!Password.empty()) {
													Password.pop_back();
													aa--;
													Locate(aa, 8);
													cout << " ";
												}
												if (!Password.empty()) {
													Password.pop_back();
													aa--;
													Locate(aa, 8);
													cout << " ";
												}
											}
											else cout << "*";
										} while (1);
										if (Password.compare("$exit$") == 0) {
											Password.clear();
											Exit = true;
											break;
										}
										//成功登入
										if (Password.compare(Password_) == 0) {
											Password.clear();
											WeChatAction(WeChatAction_Plus(AccountID));
											Exit = true;
											break;
										}
										//密码错误
										else {
											Password.clear();
											continue;
										}
									} while (1);
									if (Exit) {
										break;
									}
								}
								//没找到密码，一般不可能
								else {
									Warning(" 此账户信息受损，请联系管理员 ", "yellow");
									cout << "                 ";
									system("pause");
								}
							}
							else {
								Warning(" 没有查找到此账号 ", "red");
								cout << "                 ";
								system("pause");
							}
						}
					} while (Account.compare("$exit$") != 0);
					Exit = false;
					break;
				}
					  //注册
				case 2: {
					WriteLog("微信注册");
					Transition_2(41, 14, 8);
					WeChatSignUpPage();
					string temp;
					//*****************************************
					class_PlatformBody NewAccount("new");
					//输入微信号
					while (1) {
						Locate(26, 7);
						cin >> temp;
						if ((temp.compare("$empty$") == 0)) {
							Locate(28, 7);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
							cout << "微信号不合法                   ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
							Sleep(1000);
							Locate(28, 7);
							cout << "                             ";
							continue;
						}
						else if ((temp.compare("钟健") == 0) || (temp.compare("zj") == 0)) {
							Locate(26, 7);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
							cout << "微信号太高贵                   ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
							Sleep(1000);
							Locate(26, 7);
							cout << "                             ";
							continue;
						}
						else if (temp.compare("$exit$") == 0) {
							Exit = true;
							break;
						}
						else {
							temp = NewAccount.ModifyID(temp);
							Exit = false;
							break;
						}
					}
					//*****************************************
					if (Exit) {
						Exit = false;
						break;
					}
					//输入昵称
					while (1) {
						Locate(26, 8);
						cin >> temp;
						if ((temp.compare("$empty$") == 0)) {
							Locate(26, 8);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
							cout << "昵称不合法                   ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
							Sleep(1000);
							Locate(26, 8);
							cout << "                             ";
							continue;
						}
						else if ((temp.compare("钟健") == 0) || (temp.compare("zj") == 0)) {
							Locate(26, 7);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
							cout << "昵称太高贵                   ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
							Sleep(1000);
							Locate(26, 7);
							cout << "                             ";
							continue;
						}
						else if (temp.compare("$exit$") == 0) {
							Exit = true;
							break;
						}
						else {
							temp = NewAccount.ModifyName(temp);
							Exit = false;
							break;
						}
					}
					//*****************************************
					if (Exit) {
						Exit = false;
						break;
					}
					//*****************************************
					//输入生日
					while (1) {
						Locate(26, 9);
						cin >> temp;
						if (temp.compare("$exit$") != 0) {
							int a = Str2Num(temp);
							if (NewAccount.ModifyBirthday(a / 10000, (a % 10000) / 100, a % 100) != a) {
								Locate(26, 9);
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
								cout << "输入的时间不合法";
								SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
								Sleep(1000);
								Locate(26, 9);
								cout << "                    ";
							}
							else break;
						}
						else {
							Exit = true;
							break;
						}
					}
					//*****************************************
					if (Exit) {
						Exit = false;
						break;
					}
					//*****************************************
					//输入出生地
					while (1) {
						Locate(28, 10);
						cin >> temp;
						if ((temp.compare("$empty$") == 0) || (temp.compare("钟健") == 0) || (temp.compare("zj") == 0)) {
							Locate(28, 10);
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
							cout << "输入不合法                   ";
							SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
							Sleep(1000);
							Locate(28, 10);
							cout << "                             ";
							continue;
						}
						else if (temp.compare("$exit$") == 0) {
							Exit = true;
							break;
						}
						else {
							temp = NewAccount.ModifyBirthplace(temp);
							Exit = false;
							break;
						}
					}
					//*****************************************
					if (Exit) {
						Exit = false;
						break;
					}
					//*****************************************
					//输入密码
					Transition_1(8, 19, 4);
					system("cls");
					PasswordInputPage("first");
					string Password_1;
					string Password_2;
					int aa = 20;
					//第一次输入
					do {
						Locate(aa++, 8);
						Password_1.push_back(_getch());
						if (Password_1.back() == 13) {
							Password_1.pop_back();
							break;
						}
						if (Password_1.back() == 8) {
							if (!Password_1.empty()) {
								Password_1.pop_back();
								aa--;
								Locate(aa, 8);
								cout << " ";
							}
							if (!Password_1.empty()) {
								Password_1.pop_back();
								aa--;
								Locate(aa, 8);
								cout << " ";
							}
						}
						else cout << "*";
					} while (1);
					if (Password_1.compare("$exit$") == 0) {
						break;
					}
					Transition_1(8, 19, 4);
					system("cls");
					PasswordInputPage("again");
					aa = 20;
					//第二次确认
					do {
						Locate(aa++, 8);
						Password_2.push_back(_getch());
						if (Password_2.back() == 13) {
							Password_2.pop_back();
							break;
						}
						if (Password_2.back() == 8) {
							if (!Password_2.empty()) {
								Password_2.pop_back();
								aa--;
								Locate(aa, 8);
								cout << " ";
							}
							if (!Password_2.empty()) {
								Password_2.pop_back();
								aa--;
								Locate(aa, 8);
								cout << " ";
							}
						}
						else cout << "*";
					} while (1);
					if (Password_2.compare("$exit$") == 0) {
						break;
					}
					if (Password_1.compare(Password_2) == 0) {
						temp = NewAccount.ModiFyPassword(Password_1);
					}
					else {
						do {
							aa = 20;
							Password_2.clear();
							system("cls");
							PasswordInputPage("wrong");
							do {
								Locate(aa++, 8);
								Password_2.push_back(_getch());
								if (Password_2.back() == 13) {
									Password_2.pop_back();
									break;
								}
								if (Password_2.back() == 8) {
									if (!Password_2.empty()) {
										Password_2.pop_back();
										aa--;
										Locate(aa, 8);
										cout << " ";
									}
									if (!Password_2.empty()) {
										Password_2.pop_back();
										aa--;
										Locate(aa, 8);
										cout << " ";
									}
								}
								else cout << "*";
							} while (1);
							if (Password_1.compare(Password_2) == 0) {
								temp = NewAccount.ModiFyPassword(Password_1);
								break;
							}
						} while (1);
					}
					//*****************************************
					//记录、注册
					class_Admin* Admin;
					Admin = new(class_Admin);
					(*Admin).AddNewMember(Str2Num(NewAccount.ReturnInfo("PlatformID")), -1, NewAccount.ReturnInfo("ID"));
					delete(Admin);
					//*****************************************
					//返回QQ号
					Warning("欢迎来到微信", "blue");
					Sleep(1000);
					cout << "                ";
					system("pause");
					break;
				}
					  //帮助
				case 3: {
					WriteLog("微信帮助");
					Transition_2(41, 14, 5);
					WeChatHelpPage();
					getchar();
					Exit = false;
					break;
				}
					  //退出
				case 4: {
					WriteLog("微信退出");
					Exit = true;
					break;
				}
				default: {
					Warning("非法操作，你即将被逮捕！", "red");
					cout << "                 ";
					system("pause");
					break;
				}
				}
				if (Exit) {
					Exit = false;
					break;
				}
			} while (1);
			Exit = false;
			break;
		}
			//微博
		case 3: {
			WriteLog("进入微博");
			Transition_1(15, 21, 1);
			do {
				SecondHomePage("WeiBo");
				cin >> Option;
				getchar();
				switch (Str2Num(Option))
				{
					//登入
				case 1: {
					Transition_2(41, 14, 7);
					do {
						//输入账号
						LoginPage("account", "反正这个不会打印出来所以我随便乱写也是可以的对吧(*￣3￣)╭");
						//输入账号
						if (cin >> Account) {
							//退出
							if (Account.compare("$exit$") == 0)
								break;
							class_Admin* Admin;
							Admin = new(class_Admin);
							AccountID = (*Admin).ReturnPlatformID(Account);
							delete(Admin);
							//账号存在
							if (AccountID != 0) {
								//读取密码
								const string Password_ = GetLoginInfo(Num2Str(AccountID), "Password");
								//读取密码成功
								if (Password.compare("$Wrong$") != 0) {
									//输入密码界面
									do {
										LoginPage("password", GetLoginInfo(Num2Str(AccountID), "Name"));
										//输入密码
										int aa = 22;
										do {
											Locate(aa++, 8);
											Password.push_back(_getch());
											if (Password.back() == 13) {
												Password.pop_back();
												break;
											}
											if (Password.back() == 8) {
												if (!Password.empty()) {
													Password.pop_back();
													aa--;
													Locate(aa, 8);
													cout << " ";
												}
												if (!Password.empty()) {
													Password.pop_back();
													aa--;
													Locate(aa, 8);
													cout << " ";
												}
											}
											else cout << "*";
										} while (1);
										//成功登入
										if (Password.compare("$exit$") == 0) {
											Password.clear();
											Exit = true;
											break;
										}
										if (Password.compare(Password_) == 0) {
											Password.clear();
											WeiBoAction();
											Exit = true;
											break;
										}
										//密码错误
										else {
											Password.clear();
											continue;
										}
									} while (1);
									if (Exit) {
										break;
									}
								}
								//没找到密码，一般不可能
								else {
									Warning(" 此账户信息受损，请联系管理员 ", "yellow");
									cout << "                 ";
									system("pause");
								}
							}
							else {
								Warning(" 没有查找到此账号 ", "red");
								cout << "                 ";
								system("pause");
							}
						}
					} while (Account.compare("$exit$") != 0);
					Exit = false;
					break;
				}
					  //注册
				case 2: {
					WriteLog("微博注册");
					Transition_2(41, 14, 11);
					WeiBoSignUpPage();
					Locate(16, 9);
					system("pause");
					//*****************************************
					if (Exit) {
						Exit = false;
						break;
					}
					break;
				}
					  //帮助
				case 3: {
					WriteLog("微博帮助");
					Transition_2(41, 14, 5);
					QQHelpPage();
					getchar();
					Exit = false;
					break;
				}
					  //退出
				case 4: {
					WriteLog("微博退出");
					Exit = true;
					break;
				}
				default: {
					Warning("非法操作，你即将被逮捕！", "red");
					cout << "                 ";
					system("pause");
					break;
				}
				}
				if (Exit) {
					Exit = false;
					break;
				}
			} while (1);
			Exit = false;
			break;
		}
		//其它
		case 4: {
			Transition_2(41, 14, 13);
			CMD();
			break;
		}
		default: {
			Warning("非法操作，你即将被逮捕！", "red");
			cout << "                 ";
			system("pause");
		}
			   break;
		}
		if (Exit) {
			Exit = false;
			break;
		}
	} while (1);
}