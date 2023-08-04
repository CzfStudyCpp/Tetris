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
	StartGame,//��ʼ��Ϸ
	SelectName,//��ʼ��Ϸ��ѡ������ǳ�
	HomeGameSetting,//��Ϸ����
	PlayerBlank,//���а�
	Content, //���ڹ�������
	GameDoc, //��Ϸ�浵
	SelectBlock,
	KeySetting,
	BgpSetting,
	Home    //���˵�
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
	enum MenuOp MenuState = Home;//��ʼ��ö�ٳ���
	PaiMing paiMing[5];
	void SelectSetting(ExMessage*msg);
private:
	//��Ϊ��¼�ڼ����������
	int counter = 0;
	//��ָ�ĸ�����
	int which = 0;
	//��֮�ĸ���ͼ
	void ReadFile();
	//ö�ٲ˵�ѡ��
	
	
	string Players[5] = { "���淽���С��" ,"���淽���С��","����ר���ϳ�","����ר��С��","����ר����" };
	const string SaveFile[5] = { "document/���淽���С��.txt",
		"document/���淽���С��.txt",
		"document/����ר���ϳ�.txt",
		"document/����ר��С��.txt",
		"document/����ר����.txt" };
	//�������ݣ�����������õĹ�������
	struct WindowData {
		int width = 672;
		int height = 896;
	}windowData;
	//�ж��Ƿ�ʼ��Ϸ
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
	//�ж��Ƿ���ѡ�����
	bool IsInRect(ExMessage* msg, int x, int y, int w, int h);
	//�����л�
	void ChangeWindow(ExMessage* msg);
	//��ȡ�����л�
	void KeyAct();
	void selectName(ExMessage* msg);
	//��ȡ��չʾ
	void ReadAndShowBlank();
	//ѡ��浵
	void SelectDoc(ExMessage*msg);
	//�ж��ļ��Ƿ�Ϊ��
	bool FileIfEmpty(int i);
	//ѡ�񷽿���ʽ
	void selectblock(ExMessage*msg);
	//ѡ���ͼ
	void selectMap(ExMessage*msg);
	//������ͼ����
	void ReadMapName();
	//��ȡ�浵ʱ�ѵ�ͼ���ϴ浵��ͼ
	void ChangeMapFile();
	//��ȡ����
	void ReadKeyCode();
	//������ǰ�İ������ã����˿��Ƽ���
	void showYourKey();
	//�޸İ�������
	void ChangKeys(ExMessage*msg);
	//д���޸ĺ�İ�����Ϣ
	void WriteKeysCode();
	//��ȡ��������
	void LoadBlockType();
	

public:
	Menu();
	~Menu(){};
	void InitWindow();
	//�ܲ���
	void Operatoration();
};

