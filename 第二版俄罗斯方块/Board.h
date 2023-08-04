#pragma once
#include<string.h>
#include<string>
#include<cstring>
#include<iomanip>
#include<vector>
#include<graphics.h>
#include"Block.h"
#include"MyInput.h"
using namespace std;
//采用虚基类背景板，方便之后选择不同的背景图
const int Musics = 3;//音乐数量。可自定义修改，或函数增加，后续优化
struct AllData {

	int x = 0;
	int y = 0;
};
class Board
{
protected:
	string MapName;
protected:
	Board(int _rows, int _cols, int left, int top, int blockSize, string _MapName );
	void SetName(string _name);
	void init();
	 void DrawScore() ;//绘制分数，包括现有分数和历史最高分
	// void DrawLevels();//绘制当前关卡等级
	 //void LinesCleared() ;//绘制清除的行数
	 void UpdateWindow() ;//更新窗口
	 void displayOver();//结算画面
	 AllData SavePos[5];
	 //读取地图各个参数的xy坐标，边界由初始化可得
	 void ReadMapData();
public:
	vector<vector<int>>map;//二维可变向量数组，内容零代表没有方块，1；代表第一类方块
protected:
	
	int BlockSize;
	int LeftMargin;
	int TopMargin;
	int rows;
	int cols;
	int delay;
	bool GameOver;
	
protected:
	int levels;
	int HighestScore;
	int LineCount;
	int score;

	IMAGE ImgBg;

	Block* CurBlock;
	Block* NextBlock;
	Block BakBlock;
protected:

	//IMAGE ImgOver;
	IMAGE* ImgOver;
	//IMAGE ImgWin;
	IMAGE *ImgWin;
protected:
	int Cmusic = 1;
	bool IfPlayMusic = true;
	void PlayMusic(int Cmusic1);//播放音乐
	void StopMusic(int Cmusic1);//停止播放音乐

};

