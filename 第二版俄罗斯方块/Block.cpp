#include "Block.h"
#include<stdlib.h>
#include<fstream>

IMAGE* Block::imgs[7] = { NULL, };//��ʼ��Ϊ��

int Block::size = 37;
Block::Block()
{
	string a;
	ifstream fin;
	fin.open("document/BlockFile.txt", ios::in);//��ȡ��������
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
			loadimage(&imagTmp, "sucai/tiles.png");//����ͼƬ
		}
		else if (a == "sucai/blocks.png")
		{
			loadimage(&imagTmp, "sucai/blocks.png");//����ͼƬ
		}
		SetWorkingImage(&imagTmp);//�ָ�ͼƬ
		//�����Ҫ��ĳ�� IMAGE ����ͼ����������ͨ���ú�����������Ϊ��ǰ�Ļ�ͼ�豸��֮�����еĻ�ͼ��䶼������ڸ� IMAGE ���档��������Ϊ NULL �ɻָ���Ĭ�ϻ�ͼ���ڵĻ�ͼ������
		for (int i = 0; i < 7; i++)
		{
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size, 0, size, size);//���ÿ�����͵ķ����С�����Ӧ����ɫ
		}
		SetWorkingImage();//�ָ�������
	}
	int blocks[7][4] = {
	1,3,5,7,//I
	2,4,5,7,//Z1
	3,5,4,6,//Z2
	3,5,4,7,//T
	2,3,5,7,//L
	3,5,7,6,//J
	2,3,4,5,//��

	};
	blockType = 1 + rand() % 7;//�������һ�ֶ���˹����

	for (int i = 0; i < 4; i++)//��ʼ��С����
	{
		int value = blocks[blockType - 1][i];
		smallBlocks[i].row = value / 2;//ȷ��ÿ��С��������
		smallBlocks[i].col = value % 2;
	}
	img = imgs[blockType - 1];//ȷ��ָ��ķ���ͼƬ
	 
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
			loadimage(&imagTmp, "sucai/tiles.png");//����ͼƬ
		}
		else if (a == "sucai/blocks.png")
		{
			loadimage(&imagTmp, "sucai/blocks.png");//����ͼƬ
		}
		SetWorkingImage(&imagTmp);//�ָ�ͼƬ
		//�����Ҫ��ĳ�� IMAGE ����ͼ����������ͨ���ú�����������Ϊ��ǰ�Ļ�ͼ�豸��֮�����еĻ�ͼ��䶼������ڸ� IMAGE ���档��������Ϊ NULL �ɻָ���Ĭ�ϻ�ͼ���ڵĻ�ͼ������
		for (int i = 0; i < 7; i++)
		{
			imgs[i] = new IMAGE;
			getimage(imgs[i], i * size, 0, size, size);//���ÿ�����͵ķ����С�����Ӧ����ɫ
		}
		SetWorkingImage();//�ָ�������
	}
	int blocks[7][4] = {
	1,3,5,7,//I
	2,4,5,7,//Z1
	3,5,4,6,//Z2
	3,5,4,7,//T
	2,3,5,7,//L
	3,5,7,6,//J
	2,3,4,5,//��

	};
	blockType = _blockType;//�������һ�ֶ���˹����

	for (int i = 0; i < 4; i++)//��ʼ��С����
	{
		int value = blocks[blockType - 1][i];
		smallBlocks[i].row = value / 2;//ȷ��ÿ��С��������
		smallBlocks[i].col = value % 2;
	}
	img = imgs[blockType - 1];//ȷ��ָ��ķ���ͼƬ

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
	
		Point center = smallBlocks[1]; // ��ת���ĵ�
		int matrix[2][2] = { {0, 1}, {-1, 0} }; // ˳ʱ����ת90�Ⱦ���
		for (int i = 0; i < 4; i++) {
			int rowDiff = smallBlocks[i].row - center.row;
			int colDiff = smallBlocks[i].col - center.col;
			int newRow = matrix[0][0] * rowDiff + matrix[0][1] * colDiff;
			int newCol = matrix[1][0] * rowDiff + matrix[1][1] * colDiff;
			smallBlocks[i] = { center.row + newRow, center.col + newCol };
		}
	

}



void Block::draw(int leftMargin, int topMargin)//�����γ����в�ͬ�ķ���
{
	
	for (int i = 0; i < 4; i++)
	{
		int x = leftMargin + smallBlocks[i].col * size;
		int y = topMargin + smallBlocks[i].row * size;
		putimage(x, y, img);//���뷽��ͼƬ
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
	// TODO: �ڴ˴����� return ���
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
		map[smallBlocks[i].row][smallBlocks[i].col] = blockType;//��ɶ�
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
		putimage(x, y, img);//���뷽��ͼƬ
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

