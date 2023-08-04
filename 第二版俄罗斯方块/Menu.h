#pragma once
#include"Play.h"
#include <graphics.h>
#include <conio.h>
#include<iostream>
#include<fstream>
#include"Block.h"
#include"Board.h"
using namespace std;
struct PaiMing {
	string name = "";
	int score = 0;
};
enum MenuOp {
	StartGame,//开始游戏
	SelectName,//开始游戏后选择玩家昵称
	HomeGameSetting,//游戏设置
	PlayerBlank,//排行榜
	Content, //关于规则内容
	GameDoc, //游戏存档
	SelectBlock,
	KeySetting,
	BgpSetting,
	Home    //主菜单
};
class Menu
{
private:
	int rows=20;
	int cols=10;
	int left=88;
	int top=60;
	int blockSize=37;
	string MapName="map1";
	string DropSpeed = "Normal";
	enum MenuOp MenuState = Home;//初始化枚举常量
	PaiMing paiMing[5];
	void SelectSetting(ExMessage*msg);
private:
	//作为记录第几个玩家名字
	int counter = 0;
	//代指哪个方块
	int which = 0;
	//代之哪个地图
	void ReadFile();
	//枚举菜单选项
	
	
	string Players[5] = { "爱玩方块的小明" ,"爱玩方块的小红","方块专家老陈","方块专家小美","方块专家旭东" };
	const string SaveFile[5] = { "document/爱玩方块的小明.txt",
		"document/爱玩方块的小红.txt",
		"document/方块专家老陈.txt",
		"document/方块专家小美.txt",
		"document/方块专家旭东.txt" };
	//窗口数据，方面进行良好的管理数据
	struct WindowData {
		int width = 672;
		int height = 896;
	}windowData;
	//判断是否开始游戏
	bool IfPlay = false;
	bool IfLoadGame = false;
private:
	IMAGE MenuMap;
	IMAGE SubMenu;
	IMAGE NameMap;
	IMAGE Blanks;
	IMAGE LoadMenu;
	IMAGE FailMenu;
	IMAGE SetTing;
	IMAGE Block;
	IMAGE Map;
	IMAGE KeysMap;
private:
	ExMessage msg;
	//ExMessage *msg1;
private:
	//判断是否在选项框中
	bool IsInRect(ExMessage* msg, int x, int y, int w, int h);
	//窗口切换
	void ChangeWindow(ExMessage* msg);
	//获取按键切换
	void KeyAct();
	void selectName(ExMessage* msg);
	//读取和展示
	void ReadAndShowBlank();
	//选择存档
	void SelectDoc(ExMessage*msg);
	//判断文件是否为空
	bool FileIfEmpty(int i);
	//选择方块样式
	void selectblock(ExMessage*msg);
	//选择地图
	void selectMap(ExMessage*msg);
	//读出地图名字
	void ReadMapName();
	//读取存档时把地图换上存档地图
	void ChangeMapFile();
	//获取键码
	void ReadKeyCode();
	//画出当前的按键设置，除了控制键外
	void showYourKey();
	//修改按键设置
	void ChangKeys(ExMessage*msg);
	//写入修改后的按键信息
	void WriteKeysCode();
	//读取方块类型
	void LoadBlockType();
	

public:
	Menu();
	~Menu(){};
	void InitWindow();
	//总操作
	void Operatoration();
};

