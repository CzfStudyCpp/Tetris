#pragma once
#include<graphics.h>//easyx
#include<vector>
#include<string>
#include<string.h>
//方块类总揽对方块所有有关的操作，包括绘制，行动等
using namespace std;
//方块坐标
struct Point {
	int row;
	int col;
};

class Block
{
public:
	Block();//默认构造函数
	Block(int _blockType,string Blocktype12);//读档的时候对方块进行构造，赋值当前的类型和方块样式
	void drop();//方块降落
	void moveLeftRight(int offest);//左右移动
	void rotate();//旋转
	void draw(int leftMargin, int topMargin);//画出方块
	static IMAGE** getImages();//获得图片
	Block& operator=(const Block& other);//方便两个对象进行运算
	bool blockInMap(const vector<vector<int>>& map);//判断方块是否在地图
	void solidify(vector<vector<int>>& map);//固定图片
	int getBlockType();//获得类型
	void drawNextBlock(int left, int top);//画预告方块

	
private:
	int count = 1;
	
	int blockType;//方块类型
	Point smallBlocks[4];//四个小方块的位置
	IMAGE* img;//指向下面图形指针数组的某个对象

	static IMAGE* imgs[7];//静态图形指针，提高效能
	static int size;
public:
	int GetBlockRows(int pos);//获取四个方块的坐标
	int GetBlockCols(int pos);
	void SetBlockType(int type);//设置类型，不过可以不用
	void SetBlockPos(int i,int rows, int cols);
};