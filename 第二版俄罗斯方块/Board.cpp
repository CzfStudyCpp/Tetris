#include "Board.h"
#include<graphics.h>
#include"Block.h"
#include<time.h>
#include<stdlib.h>
#include <graphics.h>
#include <conio.h>
#include<fstream>
#include<iostream>
#include<string.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;

const string fileName = "document/recorder.txt";
const int Max_Levels = 5;
const int SPEED_NORMAL[Max_Levels] = { 500,400,300,200,100 };//ms
const int SPEED_QUICK = 10;

Board::Board(int _rows, int _cols, int left, int top, int blockSize, string _MapName)
{
	rows = _rows;
	cols = _cols;
	LeftMargin = left;
	TopMargin = top;
	BlockSize = blockSize;
	MapName = _MapName;
	
	//��ʼ����ά����
	for (int i = 0; i < rows; i++) {
		vector<int>mapRow;
		for (int j = 0; j < cols; j++)
		{
			mapRow.push_back(0);
		}
		map.push_back(mapRow);
	}
}

void Board::SetName(string _name)//ѡ���ͼ����
{
	MapName = _name;
}

void Board::init()
{
	/*mciSendString("open sucai/bgm2.mp3 alias bgmusic", 0, 0, 0);
	mciSendString("play bgmusic repeat", 0, 0, 0);*/
	ReadMapData();
	Cmusic = 1;
	PlayMusic(Cmusic);
	delay = SPEED_NORMAL[0];
	srand(time(NULL));
	//initgraph(672, 896);

	ImgOver = new IMAGE;
	if (MapName == "map1")
	{
		loadimage(&ImgBg, "sucai/bgi.png");
	}
	else if (MapName == "map2")
	{
		loadimage(&ImgBg, "sucai/Bg2.png");
	}
	loadimage(ImgOver, "sucai/12.png");

	ImgWin = new IMAGE;
	loadimage(ImgWin, "sucai/win.png");
	//putimage(0, 0, &ImgBg);
	//��ʼ����Ϸ��������
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			map[i][j] = 0;
		}
	}
	score = 0;
	LineCount = 0;
	levels = 1;
	//��ʼ����߷�
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << fileName << "open field" << endl;
		HighestScore = 0;
	}
	else {
		file >> HighestScore;//���ļ���ȡ����
	}
	file.close();
	GameOver = false;
}

void Board::DrawScore()
{
	char scoreText[32];
	sprintf_s(scoreText, sizeof(scoreText), "%d", score);//ͨ��C#�ķ�ʽ���л��Ʒ�����

	setcolor(RGB(0, 0, 0));//���ݻ�ͼ��������ɫ�������Ӷ������Լ���Ҫ����ɫ
	LOGFONT f;//����
	gettextstyle(&f);//��ȡ��ǰ����
	f.lfHeight = 60;
	f.lfWidth = 30;
	f.lfQuality = ANTIALIASED_QUALITY;//�����
	strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI Black"));//ѡ������
	settextstyle(&f);//��������

	setbkmode(TRANSPARENT);//����ı�������Ϊ͸��Ч��
	outtextxy(SavePos[1].x, SavePos[1].y, scoreText);//����



	sprintf_s(scoreText, sizeof(scoreText), "%d", levels);//��levels����
	outtextxy(SavePos[0].x, SavePos[0].y, scoreText);

	sprintf_s(scoreText, sizeof(scoreText), "%d", HighestScore);
	outtextxy(SavePos[3].x, SavePos[3].y, scoreText);

	sprintf_s(scoreText, sizeof(scoreText), "%d", LineCount);
	LOGFONT g;
	gettextstyle(&g);
	g.lfHeight = 40;
	g.lfWidth = 20;
	g.lfQuality = ANTIALIASED_QUALITY;//�����
	strcpy_s(g.lfFaceName, sizeof(g.lfFaceName), _T("Segoe UI Black"));//ѡ������
	settextstyle(&g);//��������

	int xPos = SavePos[4].x - f.lfWeight * strlen(scoreText);
	outtextxy(xPos, SavePos[4].y, scoreText);
}

void Board::UpdateWindow()
{
	BeginBatchDraw();//ͳһ����
	putimage(0, 0, &ImgBg);//�ڳ�ʼ0��0�ĵط����Ʊ���ͼƬ
	//cleardevice();
	IMAGE** imgs = Block::getImages();//��ȡ����ͼƬ
	//BeginBatchDraw();//ͳһ����
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (map[i][j] == 0) continue;//��ʾû�з���
			int x = j * BlockSize + LeftMargin;
			int y = i * BlockSize + TopMargin;
			putimage(x, y, imgs[map[i][j] - 1]);
		}
	}
	//������
	CurBlock->draw(LeftMargin, TopMargin);
	NextBlock->drawNextBlock(SavePos[2].x, SavePos[2].y);

	DrawScore();//���Ʒ���
	EndBatchDraw();//�����������ƣ���ִ��δ���еĻ�������
}

void Board::displayOver()
{
	StopMusic(Cmusic);
	BeginBatchDraw();//ͳһ������ͼ
	if (levels <= Max_Levels)
	{
		putimage(87, 250, ImgOver);//����ͼ��ָ���������ͼƬ�Ϳ���չʾͼƬ
		
		//putimage(87, 250, ImgOver);//��͸����ͼ
		
		mciSendString("play sucai/defeat.mp3", 0, 0, 0);
	}
	else if (levels > Max_Levels && score <= HighestScore)
	{
		putimage(87, 250, ImgOver);
		mciSendString("play sucai/defeat.mp3", 0, 0, 0);
	}
	else {
		//putimage(137, 400, &ImgWin);
		putimage(87, 250, ImgWin);
		mciSendString("play sucai/win.mp3", 0, 0, 0);
	}
	FlushBatchDraw();//�����˺���������ͼ����������ϣ���ɻ�ͼ
}
//��ȡ��ͼ����
void Board::ReadMapData()
{
	ifstream fin;
	fin.open("document/MapData.txt", ios::in);
	if (!fin.is_open())
	{
		cout << "��ȡ��ͼ�����ļ�ʧ��" << endl;
		exit(-1);
	}
	string k;
	fin >> k;
	for (int i = 1; i < 6; i++)
	{
		string in;
		fin >> in;
		int j = i - 1;
		MyInput Cin(in);
		SavePos[j].x = stoi(Cin[0]);
		SavePos[j].y = stoi(Cin[1]);
	}
	fin.close();
}

void Board::PlayMusic(int Cmusic1)
{
	if (Cmusic1 == 1) {
		mciSendString("open sucai/bgm2.mp3 alias bgmusic1", 0, 0, 0);
		mciSendString("play bgmusic1 repeat", 0, 0, 0);
	}
	else if (Cmusic1 == 2) {
		mciSendString("open sucai/��������.mp3 alias bgmusic2", 0, 0, 0);
		mciSendString("play bgmusic2 repeat", 0, 0, 0);
	}
	else if (Cmusic1 == 3) {
		mciSendString("open sucai/õ������.mp3 alias bgmusic3", 0, 0, 0);
		mciSendString("play bgmusic3 repeat", 0, 0, 0);
	}

}

void Board::StopMusic(int Cmusic1)
{
	if (Cmusic1 == 1) {
		mciSendString("stop bgmusic1", 0, 0, 0);
		mciSendString("close bgmusic1", 0, 0, 0);
	}
	else if (Cmusic1 == 2)
	{
		mciSendString("stop bgmusic2", 0, 0, 0);
		mciSendString("close bgmusic2", 0, 0, 0);
	}
	else if (Cmusic1 == 3) {
		mciSendString("stop bgmusic3", 0, 0, 0);
		mciSendString("close bgmusic3", 0, 0, 0);
	}
}





