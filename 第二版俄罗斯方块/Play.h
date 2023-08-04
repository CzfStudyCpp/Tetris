#pragma once
#include"Board.h"
#include<vector>
#include<graphics.h>
#include"Block.h"
#include"Menu.h"
#include<map>
#include<stdexcept>
using namespace std;
struct PlayerMessage {
	string name="未知玩家";
	int score=0;
};
struct PlayMessage {
	string SaveName = "未知玩家";
	int SaveScore = 0;
};
enum GameKey {
	KEY_ROTATE,//旋转
	KEY_RIGHT,//右
	KEY_LEFT,//左
	KEY_DOWN,//降落
	KEY_SAVEDOC,//存档
	KEY_GAMEPAUSE,//暂停
	KEY_CHANGMUSIC,//切换音乐
	KEY_RESETGAME,//重置游戏
	KEY_LOADLASTGAME,//加载上次游戏
	KEY_RETURNMENU //返回菜单
};

class Play:public Board
{
private:
	bool update = true;//记录是否更新画面
	int DropRows = 0;//暂时无用
	bool IfSaveGame = false;//记录是否存档
	bool IfLoadPastGame = false;//记录是否要加载存档
	string PlayerName;//玩家姓名
	bool ReuturnMenu = false;
	PlayerMessage Players;//当前玩家信息
	PlayMessage SavePlayers[6];//存档的玩家信息,排行五位，留多一位进行比较
	string PlayersNames[5] = { "爱玩方块的小明" ,"爱玩方块的小红","方块专家老陈","方块专家小美","方块专家旭东" };
	int timer = 0;
	string DropSpeed;
	//GameKey KeyInput;
	std::map<GameKey,int>KeyMap;
private:
	int GetDelay();//返回延迟
	void KeyEvent();//读取按键输入
	void drop();//控制降落
	void ClearLine();//清除行
	void MoveLeftRight(int offest);//左右移动
	void rotate();//旋转
	void CheckOver();//检查游戏是否结束
	void SaveScore();//保存最高分

	void SaveData();//保存数据
	void LoadGame();//加载游戏
	//写入信息
	void WriteNameAndScore();
	
	void ChangBgMusic();
	//读取所有信息排名
	void ReadMessage();
	//读入按键信息
	int  ReadKeyCode(const string key);
public:
	//panduan是否加载游戏
	void ifLoadGame(bool Ifloadgame);
public:
	Play(int rows, int cols, int left, int top, int blockSize, string name,string Drop);
	void play();//主函数操作
	//设置玩家昵称
	void SetPlayerName(string temp);
};

