#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include"Ways.h"
#include"Body.h"
#include"Friends.h"
#include"Admin.h"
#include"Time.h"
using namespace std;
void OutputBox(const int h, const int l);
void DisBox(const int h, const int l);
COORD pos;
int XLocation = 15;
int YLocation = 4;
unsigned int UISpeed = 15;
//定位光标
void Locate(const int x, const int y) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}
//警告
void Warning(const string a,const string Color) {
	system("cls");
	if (Color.compare("red") == 0)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	else if (Color.compare("blue") == 0)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	else if (Color.compare("green") == 0)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	else if (Color.compare("purple") == 0)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE);
	else if (Color.compare("yellow") == 0)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	else if (Color.compare("cyan") == 0)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE);
	Locate(XLocation, YLocation);
	cout << "╭ ───";
	for (unsigned int i = 0; i < a.size(); i++)
		cout << "─";
	cout << "─── ╮" << "\n";
	Locate(XLocation, YLocation + 1);
	cout << "│    ";
	cout << a;
	cout << "    │" << "\n";
	Locate(XLocation, YLocation + 2);
	cout << "╰ ───";
	for (unsigned int i = 0; i < a.size(); i++)
		cout << "─";
	cout << "─── ╯" << "\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
//主页
void HomePage(const bool judge) {
	if (judge) {
		Locate(XLocation, YLocation);
		cout << "╭ ───────────────────────────────────── ╮";
		YLocation++;
		Locate(XLocation, YLocation);
		cout << "│                                       │";
		YLocation++;
		Locate(XLocation, YLocation);
		cout << "│                                       │";
		YLocation++;
		Locate(XLocation, YLocation);
		cout << "│                                       │";
		YLocation++;
		Locate(XLocation, YLocation);
		cout << "│          ◢████████◣         │";
		YLocation++;
		Locate(XLocation, YLocation);
		cout << "│          ██████████         │";
		YLocation++;
		Locate(XLocation, YLocation);
		cout << "│                 ◢█◤                │";
		YLocation++;
		Locate(XLocation, YLocation);
		cout << "│                ◢█◤                 │";
		YLocation++;
		Locate(XLocation, YLocation);
		cout << "│               ◢█◤                  │";
		YLocation++;
		Locate(XLocation, YLocation);
		cout << "│              ◢█◤                   │";
		YLocation++;
		Locate(XLocation, YLocation);
		cout << "│             ◢█◤                    │";
		YLocation++;
		Locate(XLocation, YLocation);
		cout << "│            ◢█◤                     │";
		YLocation++;
		Locate(XLocation, YLocation);
		cout << "│               Loading                 │";
		YLocation++;
		Locate(XLocation, YLocation);
		cout << "│                                       │";
		YLocation++;
		Locate(XLocation, YLocation);
		cout << "╰ ───────────────────────────────────── ╯";
		YLocation++;
		Sleep(1000);
		YLocation = 4;
		for (int i = 0; i < 15; i++) {
			Locate(XLocation, YLocation);
			cout << " ████████████████████ ";
			YLocation++;
			Sleep(UISpeed);
		}
		Sleep(UISpeed);
	}
	YLocation = 4;
	Locate(XLocation, YLocation);
	cout << "╭ ───────────────────────────────────── ╮";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│             全新腾X平台               │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│         1  QQ                         │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│         2  微信                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│         3  微博                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│         4  选项                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│         →                            │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "╰ ───────────────────────────────────── ╯";
	YLocation++;
	Locate(27, 16);
	YLocation = 4;
}
//过渡界面
//第一个行数，第二个列数，第三个方向
//1-向下 2-向上 3-向右 4-向左
void Transition_1(const int h,const int l,const int f) {
	system("cls");
	XLocation = 15;
	YLocation = 4;
	if (f == 1) {
		for (int i = 0; i < h; i++) {
			Locate(XLocation, YLocation++);
			for (int n = 0; n < l; n++) {
				cout << "█";
			}
			Sleep(UISpeed);
		}
	}
	else if (f == 2) {
		YLocation += h;
		for (int i = 0; i < h; i++) {
			Locate(XLocation, YLocation--);
			for (int n = 0; n < l; n++) {
				cout << "█";
			}
			Sleep(UISpeed);
		}
	}
	else if (f == 3) {
		for (int i = 0; i < l; i++) {
			Locate(XLocation+=2, YLocation);
			for (int n = 0; n < h; n++) {
				Locate(XLocation, YLocation++);
				cout << "█";
			}
			YLocation = 4;
			Sleep(UISpeed);
		}
	}
	else if (f == 4) {
		XLocation = XLocation + l + l;
		for (int i = 0; i < l; i++) {
			Locate(XLocation-=2, YLocation);
			for (int n = 0; n < h; n++) {
				Locate(XLocation, YLocation++);
				cout << "█";
			}
			YLocation = 4;
			Sleep(UISpeed);
		}
	}
	else {
		cout << "不可能出现的你放心吧……";
	}
	XLocation = 15;
	YLocation = 4;
}
//a-长度 b-位置 c-移动长度
void Transition_2(const int a,const int b,const int c) {
	YLocation += b;
	for (int i = 0; i < c; i++) {
		Locate(XLocation, YLocation);
		cout << "╰ ";
		for (int n = 0; n < a - 4; n++) {
			cout << "─";
		}
		cout << " ╯";
		Locate(XLocation, YLocation + 1);
		for (int n = 0; n < a; n++) {
			cout << " ";
		}
		YLocation -= 1;
		Sleep(UISpeed);
	}
}
//输出盒子
void OutputBox(const int h, const int l) {
	Locate(XLocation, YLocation++);
	cout << "╭ ";
	for (int i = 0; i < l-4; i++) {
		cout << "─";
	}
	cout << " ╮";
	for (int i = 0; i < h - 2; i++) { 
		Locate(XLocation, YLocation++);
		cout << "│"; 
		for (int i = 0; i < l - 2; i++) {
			cout << " ";
		}
		cout << "│";
	}
	Locate(XLocation, YLocation++);
	cout << "╰ ";
	for (int i = 0; i < l - 4; i++) {
		cout << "─";
	}
	cout << " ╯";
	XLocation = 15;
	YLocation = 4;
}
//摧毁盒子=￣ω￣=
void DisBox(const int h, const int l) {
	Locate(XLocation, YLocation++);
	cout << "  ";
	for (int i = 0; i < l - 4; i++) {
		cout << " ";
	}
	cout << "  ";
	for (int i = 0; i < h - 2; i++) {
		Locate(XLocation, YLocation++);
		cout << " ";
		for (int i = 0; i < l - 2; i++) {
			cout << " ";
		}
		cout << " ";
	}
	Locate(XLocation, YLocation++);
	cout << "  ";
	for (int i = 0; i < l - 4; i++) {
		cout << " ";
	}
	cout << "  ";
	XLocation = 15;
	YLocation = 4;
}
//二级界面
void SecondHomePage(const string a) {
	YLocation = 4;
	Locate(XLocation, YLocation);
	cout << "╭ ───────────────────────────────────── ╮";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	if (a.compare("QQ") == 0 || a.compare("qq") == 0)
		cout << "│                  QQ                   │";
	else if (a.compare("微信") == 0 || a.compare("WeChat") == 0)
		cout << "│                 微信                  │";
	else if (a.compare("微博") == 0 || a.compare("WeiBo") == 0)
		cout << "│                 微博                  │";
	else cout << "│                unknown                │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│         1  登入                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│         2  注册                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│         3  帮助                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│         4  返回上一级                 │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│         →                            │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "╰ ───────────────────────────────────── ╯";
	YLocation++;
	Locate(27, 16);
	YLocation = 4;
}
//登入
void LoginPage(const string a, const string b) {
	system("cls");
	YLocation = 4;
	Locate(XLocation, YLocation);
	cout << "╭ ───────────────────────────────────── ╮";
	YLocation++;// Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++;// Sleep(UISpeed);
	if (a.compare("account") == 0) {
		Locate(XLocation, YLocation);
		cout << "│      请输入账户：                     │";
		YLocation++;// Sleep(UISpeed);
	}
	else if (a.compare("password") == 0) {
		Locate(XLocation, YLocation);
		cout << "│                                       │";
		Locate(XLocation + 7, YLocation);
		cout << "您好，" << b << "  请输入密码：";
		YLocation++;// Sleep(UISpeed);
	}
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++;// Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++;// Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++;// Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++;// Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "╰ ───────────────────────────────────── ╯";
	YLocation++;
	Locate(22, 8);
	YLocation = 4;
}
//QQ用户界面
void QQMemberPage() {
	YLocation = 4;
	Locate(XLocation, YLocation);
	cout << "╭ ───────────────────────────────────── ╮";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "╰ ───────────────────────────────────── ╯";
	YLocation++;
	Locate(27, 16);
	YLocation = 4;
}
//QQ注册界面
void QQSignUpPage() {
	YLocation = 4;
	Locate(XLocation, YLocation);
	cout << "╭ ───────────────────────────────────── ╮";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│    注册新的QQ账户                     │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│    昵称：                             │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│    生日：                             │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│    出生地：                           │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "╰ ───────────────────────────────────── ╯";
	YLocation = 4;
}
//微信注册界面
void WeChatSignUpPage() {
	YLocation = 4;
	Locate(XLocation, YLocation);
	cout << "╭ ───────────────────────────────────── ╮";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│    欢迎来到微信                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│    微信号：                           │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│    昵称：                             │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│    生日：                             │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│    出生地：                           │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "╰ ───────────────────────────────────── ╯";
	YLocation = 4;
}
//注册输入密码
void PasswordInputPage(const string a) {
	YLocation = 4;
	Locate(XLocation, YLocation);
	cout << "╭ ───────────────────────────────────── ╮";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	if (a.compare("first") == 0) {
		cout << "│    请输入你的密码                     │";
	}
	else if (a.compare("again") == 0) {
		cout << "│    请再次输入密码                     │";
	}
	else if (a.compare("wrong") == 0) {
		cout << "│    两次密码不一致                     │";
	}
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "╰ ───────────────────────────────────── ╯";
	YLocation = 4;
}
//QQ信息卡
void QQInfoCard(const int ID, const int a) {
	XLocation = 60;
	YLocation = 4 + a * 8;
	OutputBox(8, 41);
	YLocation = 4 + a * 8;
	XLocation = 64;
	YLocation++;
	YLocation++;
	Locate(XLocation, YLocation++);
	cout << GetLoginInfo(Num2Str(ID), "Name") << "  " << GetLoginInfo(Num2Str(ID), "ID");
	Locate(XLocation, YLocation++);
	cout << "生日：" << GetLoginInfo(Num2Str(ID), "Birthday");
	Locate(XLocation, YLocation++);
	cout << "注册日期：" << GetLoginInfo(Num2Str(ID), "RegistrationDate");
	Locate(XLocation, YLocation++);
	cout << "出生地：" << GetLoginInfo(Num2Str(ID), "Birthplace");
}
//QQ帮助
void QQHelpPage() {
	YLocation = 4;
	Locate(XLocation, YLocation);
	cout << "╭ ────  欢迎使用QQ ──────────────────── ╮";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│      在QQ界面选择1进行登入,如果输入了 │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│  错误的账户,将会提示没有找到此账户,在 │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│  数据输入界面输入$exit$可以强制退出.  │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│  请注意,生日输入的格式为年月日相连,即:│";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│         20000304表示2000年3月4日      │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│  登入时输入密码若无反应则是密码错误,重│";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│  新输入即可.                          │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "╰ ───────────────────────────────────── ╯";
	YLocation++;
	Locate(15, 15);
	cout << " ← 按下回车退出";
	YLocation = 4;
}
//QQ帮助
void WeChatHelpPage() {
	YLocation = 4;
	Locate(XLocation, YLocation);
	cout << "╭ ────  欢迎使用微信 ────────────────── ╮";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│      在wx界面选择1进行登入,如果输入了 │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│  错误的账户,将会提示没有找到此账户,在 │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│  数据输入界面输入$exit$可以强制退出.  │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│  请注意,生日输入的格式为年月日相连,即:│";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│         20000304表示2000年3月4日      │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│  登入时输入密码若无反应则是密码错误,重│";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│  新输入即可.                          │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "╰ ───────────────────────────────────── ╯";
	YLocation++;
	Locate(15, 15);
	cout << " ← 按下回车退出";
	YLocation = 4;
}
//群信息卡
void GroupCard(class_Group a,const int i) {
	XLocation = 60;
	YLocation = 4 + i * 7;
	OutputBox(7, 41);
	YLocation = 4 + i * 7;
	XLocation = 64;
	YLocation++;
	YLocation++;
	Locate(XLocation, YLocation++);
	cout << "群名：" << a.ChangeGroupName("$empty$");
	Locate(XLocation, YLocation++);
	cout << "群号：" << a.ReturnGroupID();
	Locate(XLocation, YLocation++);
	cout << "群主：" << GetLoginInfo(Num2Str(a.ReturnManager()), "Name");
	XLocation = 15;
	YLocation = 4;
}
//群操作
int GroupPage(class_QQGroup4Manager* p) {
	XLocation = 60;
	YLocation = 4;
	OutputBox((*p).ReturnMemberList().size() + (*p).ReturnGroupAdmin().size() + 16, 41);
	XLocation = 63;
	YLocation = 6;
	Locate(XLocation, YLocation++);
	cout << (*p).ChangeGroupName("$empty$");
	Locate(XLocation, YLocation++);
	cout << "群主：" << GetLoginInfo(Num2Str((*p).ReturnManager()), "Name") << "  " << GetLoginInfo(Num2Str((*p).ReturnManager()), "ID");
	Locate(XLocation, YLocation++);
	cout << "群管理：";
	for (unsigned int i = 0; i < (*p).ReturnGroupAdmin().size(); i++) {
		Locate(XLocation, YLocation++);
		cout << GetLoginInfo(Num2Str((*p).ReturnGroupAdmin()[i]), "Name") << "  " << GetLoginInfo(Num2Str((*p).ReturnGroupAdmin()[i]), "ID");
	}
	Locate(XLocation, YLocation++);
	cout << "群员：";
	for (unsigned int i = 0; i < (*p).ReturnMemberList().size(); i++) {
		Locate(XLocation, YLocation++);
		cout << GetLoginInfo(Num2Str((*p).ReturnMemberList()[i]), "Name") << "  " << GetLoginInfo(Num2Str((*p).ReturnMemberList()[i]), "ID");
	}
	Locate(XLocation, YLocation++);
	Locate(XLocation, YLocation++);
	cout << "1 拉人入群";
	Locate(XLocation, YLocation++);
	cout << "2 踢人出群";
	Locate(XLocation, YLocation++);
	cout << "3 修改群名";
	Locate(XLocation, YLocation++);
	cout << "4 设置管理员";
	Locate(XLocation, YLocation++);
	cout << "5 退出";
	Locate(XLocation, YLocation++);
	Locate(XLocation, YLocation);
	cout << "→";
	return 0;
}
int GroupPage(class_QQGroup4Admin* p) {
	XLocation = 60;
	YLocation = 4;
	OutputBox((*p).ReturnMemberList().size() + (*p).ReturnGroupAdmin().size() + 15, 41);
	XLocation = 62;
	YLocation = 6;
	Locate(XLocation, YLocation++);
	cout << (*p).ChangeGroupName("$empty$");
	Locate(XLocation, YLocation++);
	cout << "群主：" << GetLoginInfo(Num2Str((*p).ReturnManager()), "Name") << "  " << GetLoginInfo(Num2Str((*p).ReturnManager()), "ID");
	Locate(XLocation, YLocation++);
	cout << "群管理：";
	for (unsigned int i = 0; i < (*p).ReturnGroupAdmin().size(); i++) {
		Locate(XLocation, YLocation++);
		cout << GetLoginInfo(Num2Str((*p).ReturnGroupAdmin()[i]), "Name") << "  " << GetLoginInfo(Num2Str((*p).ReturnGroupAdmin()[i]), "ID");
	}
	Locate(XLocation, YLocation++);
	cout << "群员：";
	for (unsigned int i = 0; i < (*p).ReturnMemberList().size(); i++) {
		Locate(XLocation, YLocation++);
		cout << GetLoginInfo(Num2Str((*p).ReturnMemberList()[i]), "Name") << "  " << GetLoginInfo(Num2Str((*p).ReturnMemberList()[i]), "ID");
	}
	Locate(XLocation, YLocation++);
	Locate(XLocation, YLocation++);
	cout << "1 拉人入群";
	Locate(XLocation, YLocation++);
	cout << "2 踢人出群";
	Locate(XLocation, YLocation++);
	cout << "3 修改群名";
	Locate(XLocation, YLocation++);
	cout << "4 退出";
	Locate(XLocation, YLocation++);
	Locate(XLocation, YLocation);
	cout << "→";
	return 0;
}
int GroupPage(class_QQGroup4Member* p) {
	XLocation = 60;
	YLocation = 4;
	OutputBox((*p).ReturnMemberList().size() + (*p).ReturnGroupAdmin().size() + 14, 41);
	XLocation = 62;
	YLocation = 6;
	Locate(XLocation, YLocation++);
	cout << (*p).ChangeGroupName("$empty$");
	Locate(XLocation, YLocation++);
	cout << "群主：" << GetLoginInfo(Num2Str((*p).ReturnManager()), "Name") << "  " << GetLoginInfo(Num2Str((*p).ReturnManager()), "ID");
	Locate(XLocation, YLocation++);
	cout << "群管理：";
	for (unsigned int i = 0; i < (*p).ReturnGroupAdmin().size(); i++) {
		Locate(XLocation, YLocation++);
		cout << GetLoginInfo(Num2Str((*p).ReturnGroupAdmin()[i]), "Name") << "  " << GetLoginInfo(Num2Str((*p).ReturnGroupAdmin()[i]), "ID");
	}
	Locate(XLocation, YLocation++);
	cout << "群员：";
	for (unsigned int i = 0; i < (*p).ReturnMemberList().size(); i++) {
		Locate(XLocation, YLocation++);
		cout << GetLoginInfo(Num2Str((*p).ReturnMemberList()[i]), "Name") << "  " << GetLoginInfo(Num2Str((*p).ReturnMemberList()[i]), "ID");
	}
	Locate(XLocation, YLocation++);
	Locate(XLocation, YLocation++);
	cout << "1 拉人入群";
	Locate(XLocation, YLocation++);
	cout << "2 退群";
	Locate(XLocation, YLocation++);
	cout << "3 退出";
	Locate(XLocation, YLocation++);
	Locate(XLocation, YLocation);
	cout << "→";
	return 0;
}
int GroupPage(class_WeChatGroup4Manager* p) {
	XLocation = 60;
	YLocation = 4;
	OutputBox((*p).ReturnMemberList().size() + 15, 41);
	XLocation = 62;
	YLocation = 6;
	Locate(XLocation, YLocation++);
	cout << (*p).ChangeGroupName("$empty$");
	Locate(XLocation, YLocation++);
	cout << "群主：" << GetLoginInfo(Num2Str((*p).ReturnManager()), "Name");
	Locate(XLocation, YLocation++);
	cout << "群员：";
	for (unsigned int i = 0; i < (*p).ReturnMemberList().size(); i++) {
		Locate(XLocation, YLocation++);
		cout << GetLoginInfo(Num2Str((*p).ReturnMemberList()[i]), "Name") << "  " << GetLoginInfo(Num2Str((*p).ReturnMemberList()[i]), "ID");
	}
	Locate(XLocation, YLocation++);
	Locate(XLocation, YLocation++);
	cout << "1 拉人入群";
	Locate(XLocation, YLocation++);
	cout << "2 踢人出群";
	Locate(XLocation, YLocation++);
	cout << "3 修改群名";
	Locate(XLocation, YLocation++);
	cout << "4 退出";
	Locate(XLocation, YLocation++);
	Locate(XLocation, YLocation);
	cout << "→";
	return 0;
}
int GroupPage(class_WeChatGroup4Member* p) {
	XLocation = 60;
	YLocation = 4;
	OutputBox((*p).ReturnMemberList().size() + 14, 41);
	XLocation = 62;
	YLocation = 6;
	Locate(XLocation, YLocation++);
	cout << (*p).ChangeGroupName("$empty$");
	Locate(XLocation, YLocation++);
	cout << "群主：" << GetLoginInfo(Num2Str((*p).ReturnManager()), "Name");
	Locate(XLocation, YLocation++);
	cout << "群员：";
	for (unsigned int i = 0; i < (*p).ReturnMemberList().size(); i++) {
		Locate(XLocation, YLocation++);
		cout << GetLoginInfo(Num2Str((*p).ReturnMemberList()[i]), "Name") << "  " << GetLoginInfo(Num2Str((*p).ReturnMemberList()[i]), "ID");
	}
	Locate(XLocation, YLocation++);
	Locate(XLocation, YLocation++);
	cout << "1 拉人入群";
	Locate(XLocation, YLocation++);
	cout << "2 退群";
	Locate(XLocation, YLocation++);
	cout << "3 退出";
	Locate(XLocation, YLocation++);
	Locate(XLocation, YLocation);
	cout << "→";
	return 0;
}
//QQ信息卡2
void QQInfoCard_2(const int ID, const int a) {
	XLocation = 60;
	YLocation = 4 + a;
	OutputBox(10, 41);
	YLocation = 4 + a;
	XLocation = 64;
	YLocation++;
	YLocation++;
	Locate(XLocation, YLocation++);
	cout << GetLoginInfo(Num2Str(ID), "Name") << "  " << GetLoginInfo(Num2Str(ID), "PlatformID");
	Locate(XLocation, YLocation++);
	cout << "生日：" << GetLoginInfo(Num2Str(ID), "Birthday");
	Locate(XLocation, YLocation++);
	cout << "注册日期：" << GetLoginInfo(Num2Str(ID), "RegistrationDate");
	Locate(XLocation, YLocation++);
	cout << "出生地：" << GetLoginInfo(Num2Str(ID), "Birthplace");
	Locate(XLocation, YLocation++);
	cout << "微信：";
	if (GetLoginInfo(Num2Str(ID), "BindingID").compare("$wrong$") == 0 || GetLoginInfo(Num2Str(ID), "BindingID").compare("") == 0) {
		cout << "无";
	}
	else {
		cout << GetLoginInfo(GetLoginInfo(Num2Str(ID), "BindingID"), "ID");
	}
}
void WeChatInfoCard(const int ID, const int a) {
	XLocation = 60;
	YLocation = 4 + a * 8;
	OutputBox(8, 41);
	YLocation = 4 + a * 8;
	XLocation = 64;
	YLocation++;
	YLocation++;
	Locate(XLocation, YLocation++);
	cout << GetLoginInfo(Num2Str(ID), "Name") << "  " << GetLoginInfo(Num2Str(ID), "PlatformID");
	Locate(XLocation, YLocation++);
	cout << "微信号：" << GetLoginInfo(Num2Str(ID), "ID");
	Locate(XLocation, YLocation++);
	cout << "生日：" << GetLoginInfo(Num2Str(ID), "Birthday");
	Locate(XLocation, YLocation++);
	cout << "出生地：" << GetLoginInfo(Num2Str(ID), "Birthplace");
}
void WeChatInfoCard_2(const int ID, const int a) {
	XLocation = 60;
	YLocation = 5 + a * 8;
	OutputBox(8, 41);
	YLocation = 4 + a * 8;
	XLocation = 64;
	YLocation++;
	YLocation++;
	Locate(XLocation, YLocation++);
	cout << GetLoginInfo(Num2Str(ID), "Name") << "  " << GetLoginInfo(Num2Str(ID), "PlatformID");
	Locate(XLocation, YLocation++);
	cout << "微信号：" << GetLoginInfo(Num2Str(ID), "ID");
	Locate(XLocation, YLocation++);
	cout << "生日：" << GetLoginInfo(Num2Str(ID), "Birthday");
	Locate(XLocation, YLocation++);
	cout << "出生地：" << GetLoginInfo(Num2Str(ID), "Birthplace");
	Locate(XLocation, YLocation++);
	cout << "QQ：";
	if (GetLoginInfo(Num2Str(ID), "BindingID").compare("$wrong$") == 0 || GetLoginInfo(Num2Str(ID), "BindingID").compare("") == 0) {
		cout << "无";
	}
	else {
		cout << GetLoginInfo(GetLoginInfo(Num2Str(ID), "BindingID"), "ID");
	}
}
//
void WeiBoSignUpPage() {
	YLocation = 4;
	Locate(XLocation, YLocation);
	cout << "╭ ───────────────────────────────────── ╮";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│    请去QQ界面注册微博通用账户         │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "│                                       │";
	YLocation++; Sleep(UISpeed);
	Locate(XLocation, YLocation);
	cout << "╰ ───────────────────────────────────── ╯";
	YLocation = 4;
}