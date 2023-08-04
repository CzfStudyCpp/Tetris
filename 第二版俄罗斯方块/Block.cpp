#include "Block.h"
#include<stdlib.h>
#include<fstream>

IMAGE* Block::imgs[7] = { NULL, };//初始化为空

int Block::size = 37;
Block::Block()
{
	string a;
	ifstream fin;
	fin.open("document/BlockFile.txt", ios::in);//读取方块类型
	if (!fin.is_open())
	{
		exit(-1);
	}
	fin >> a;
	fin.close();
	if (imgs[0] == NULL)
	{
		IMAGE imagTmp;
		if (a == "sucai/tiles.png")
		{
			loadimage(&imagTmp, "sucai/tiles.png");//载入图片
		}
		else if (a == "sucai/blocks.png")
		{
			loadimage(&imagTmp, "sucai/blocks.png");//载入图片
		}
		SetWorkingImage(&imagTmp);//分割图片
		//如果需要对某个 IMAGE 做绘图操作，可以通过该函数将其设置为当前的绘图设备，之后所有的绘图语句都会绘制在该 IMAGE 上面。将参数置为 NULL 可恢复对默认绘图窗口的绘图操作。
		for (int i = 0; i < 7; i++)
		{
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size, 0, size, size);//获得每个类型的方块的小方块对应的颜色
		}
		SetWorkingImage();//恢复工作区
	}
	int blocks[7][4] = {
	1,3,5,7,//I
	2,4,5,7,//Z1
	3,5,4,6,//Z2
	3,5,4,7,//T
	2,3,5,7,//L
	3,5,7,6,//J
	2,3,4,5,//田

	};
	blockType = 1 + rand() % 7;//随机生成一种俄罗斯方块

	for (int i = 0; i < 4; i++)//初始化小方块
	{
		int value = blocks[blockType - 1][i];
		smallBlocks[i].row = value / 2;//确定每个小方块坐标
		smallBlocks[i].col = value % 2;
	}
	img = imgs[blockType - 1];//确定指向的方块图片
	 
}
Block::Block(int _blockType,string Blocktype12)
{
	string a;
	a = Blocktype12;
	/*ifstream fin;
	fin.open("document/BlockFile.txt", ios::in);
	if (!fin.is_open())
	{
		exit(-1);
	}
	fin >> a;
	fin.close();*/
	if (imgs[0] == NULL)
	{
		IMAGE imagTmp;
		if (a == "sucai/tiles.png")
		{
			loadimage(&imagTmp, "sucai/tiles.png");//载入图片
		}
		else if (a == "sucai/blocks.png")
		{
			loadimage(&imagTmp, "sucai/blocks.png");//载入图片
		}
		SetWorkingImage(&imagTmp);//分割图片
		//如果需要对某个 IMAGE 做绘图操作，可以通过该函数将其设置为当前的绘图设备，之后所有的绘图语句都会绘制在该 IMAGE 上面。将参数置为 NULL 可恢复对默认绘图窗口的绘图操作。
		for (int i = 0; i < 7; i++)
		{
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size, 0, size, size);//获得每个类型的方块的小方块对应的颜色
		}
		SetWorkingImage();//恢复工作区
	}
	int blocks[7][4] = {
	1,3,5,7,//I
	2,4,5,7,//Z1
	3,5,4,6,//Z2
	3,5,4,7,//T
	2,3,5,7,//L
	3,5,7,6,//J
	2,3,4,5,//田

	};
	blockType = _blockType;//随机生成一种俄罗斯方块

	for (int i = 0; i < 4; i++)//初始化小方块
	{
		int value = blocks[blockType - 1][i];
		smallBlocks[i].row = value / 2;//确定每个小方块坐标
		smallBlocks[i].col = value % 2;
	}
	img = imgs[blockType - 1];//确定指向的方块图片

}
void Block::drop()
{
	
		for (int i = 0; i < 4; i++) {
			smallBlocks[i].row++;
		}
}

void Block::moveLeftRight(int offest)
{
	for (int i = 0; i < 4; i++) {
		smallBlocks[i].col += offest;
	}
}

void Block::rotate()
{
	
		Point center = smallBlocks[1]; // 旋转中心点
		int matrix[2][2] = { {0, 1}, {-1, 0} }; // 顺时针旋转90度矩阵
		for (int i = 0; i < 4; i++) {
			int rowDiff = smallBlocks[i].row - center.row;
			int colDiff = smallBlocks[i].col - center.col;
			int newRow = matrix[0][0] * rowDiff + matrix[0][1] * colDiff;
			int newCol = matrix[1][0] * rowDiff + matrix[1][1] * colDiff;
			smallBlocks[i] = { center.row + newRow, center.col + newCol };
		}
	

}



void Block::draw(int leftMargin, int topMargin)//绘制形成七中不同的方块
{
	
	for (int i = 0; i < 4; i++)
	{
		int x = leftMargin + smallBlocks[i].col * size;
		int y = topMargin + smallBlocks[i].row * size;
		putimage(x, y, img);//放入方块图片
	}
}


IMAGE** Block::getImages()
{
	return imgs;
}

Block& Block::operator=(const Block& other)
{
	if (this == &other) return*this;
	this->blockType = other.blockType;
	for (int i = 0; i < 4; i++) {
		this->smallBlocks[i] = other.smallBlocks[i];
	}
	return *this;
	// TODO: 在此处插入 return 语句
}

bool Block::blockInMap(const vector<vector<int>>& map)
{
	int rows = map.size();
	int cols = map[0].size();
	for (int i = 0; i < 4; i++) {
		if (smallBlocks[i].col < 0 || smallBlocks[i].col >= cols ||
			smallBlocks[i].row < 0 || smallBlocks[i].row >= rows ||
			map[smallBlocks[i].row][smallBlocks[i].col]) {
			return false;
		}
	}
	return true;
}

void Block::solidify(vector<vector<int>>& map)
{
	for (int i = 0; i < 4; i++) {
		map[smallBlocks[i].row][smallBlocks[i].col] = blockType;//完成对
	}
}

int Block::getBlockType()
{
	return blockType;
}

void Block::drawNextBlock(int left, int top)
{
	for (int i = 0; i < 4; i++)
	{
		int x = left + smallBlocks[i].col * size;
		int y = top + smallBlocks[i].row * size;
		putimage(x, y, img);//放入方块图片
	}
}



int Block::GetBlockRows(int pos)
{
	return smallBlocks[pos].row;
}

int Block::GetBlockCols(int pos)
{
	return smallBlocks[pos].col;
}

void Block::SetBlockType(int type)
{
	blockType = type;
}

void Block::SetBlockPos(int i,int rows, int cols)
{
	smallBlocks[i].row = rows;
	smallBlocks[i].col = cols;
}

