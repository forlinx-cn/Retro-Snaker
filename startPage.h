#include "prepare.h"
#ifndef __STARTPAGE_H__
#define __STARTPAGE_H__

Player* loadStartPage();				//加载起始页面
void printMenu();						//打印菜单
int haveUser(const char* username);		//判断是否存在该用户
void showHelpInfo();					//打印帮助信息

#endif