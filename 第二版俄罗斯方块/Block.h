#pragma once
#include<graphics.h>//easyx
#include<vector>
#include<string>
#include<string.h>
//�����������Է��������йصĲ������������ƣ��ж���
using namespace std;
//��������
struct Point {
	int row;
	int col;
};

class Block
{
public:
	Block();//Ĭ�Ϲ��캯��
	Block(int _blockType,string Blocktype12);//������ʱ��Է�����й��죬��ֵ��ǰ�����ͺͷ�����ʽ
	void drop();//���齵��
	void moveLeftRight(int offest);//�����ƶ�
	void rotate();//��ת
	void draw(int leftMargin, int topMargin);//��������
	static IMAGE** getImages();//���ͼƬ
	Block& operator=(const Block& other);//�������������������
	bool blockInMap(const vector<vector<int>>& map);//�жϷ����Ƿ��ڵ�ͼ
	void solidify(vector<vector<int>>& map);//�̶�ͼƬ
	int getBlockType();//�������
	void drawNextBlock(int left, int top);//��Ԥ�淽��

	
private:
	int count = 1;
	
	int blockType;//��������
	Point smallBlocks[4];//�ĸ�С�����λ��
	IMAGE* img;//ָ������ͼ��ָ�������ĳ������

	static IMAGE* imgs[7];//��̬ͼ��ָ�룬���Ч��
	static int size;
public:
	int GetBlockRows(int pos);//��ȡ�ĸ����������
	int GetBlockCols(int pos);
	void SetBlockType(int type);//�������ͣ��������Բ���
	void SetBlockPos(int i,int rows, int cols);
};