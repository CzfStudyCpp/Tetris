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
//��������౳���壬����֮��ѡ��ͬ�ı���ͼ
const int Musics = 3;//�������������Զ����޸ģ��������ӣ������Ż�
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
	 void DrawScore() ;//���Ʒ������������з�������ʷ��߷�
	// void DrawLevels();//���Ƶ�ǰ�ؿ��ȼ�
	 //void LinesCleared() ;//�������������
	 void UpdateWindow() ;//���´���
	 void displayOver();//���㻭��
	 AllData SavePos[5];
	 //��ȡ��ͼ����������xy���꣬�߽��ɳ�ʼ���ɵ�
	 void ReadMapData();
public:
	vector<vector<int>>map;//��ά�ɱ��������飬���������û�з��飬1�������һ�෽��
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
	void PlayMusic(int Cmusic1);//��������
	void StopMusic(int Cmusic1);//ֹͣ��������

};

