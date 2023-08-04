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
	string name="δ֪���";
	int score=0;
};
struct PlayMessage {
	string SaveName = "δ֪���";
	int SaveScore = 0;
};
enum GameKey {
	KEY_ROTATE,//��ת
	KEY_RIGHT,//��
	KEY_LEFT,//��
	KEY_DOWN,//����
	KEY_SAVEDOC,//�浵
	KEY_GAMEPAUSE,//��ͣ
	KEY_CHANGMUSIC,//�л�����
	KEY_RESETGAME,//������Ϸ
	KEY_LOADLASTGAME,//�����ϴ���Ϸ
	KEY_RETURNMENU //���ز˵�
};

class Play:public Board
{
private:
	bool update = true;//��¼�Ƿ���»���
	int DropRows = 0;//��ʱ����
	bool IfSaveGame = false;//��¼�Ƿ�浵
	bool IfLoadPastGame = false;//��¼�Ƿ�Ҫ���ش浵
	string PlayerName;//�������
	bool ReuturnMenu = false;
	PlayerMessage Players;//��ǰ�����Ϣ
	PlayMessage SavePlayers[6];//�浵�������Ϣ,������λ������һλ���бȽ�
	string PlayersNames[5] = { "���淽���С��" ,"���淽���С��","����ר���ϳ�","����ר��С��","����ר����" };
	int timer = 0;
	string DropSpeed;
	//GameKey KeyInput;
	std::map<GameKey,int>KeyMap;
private:
	int GetDelay();//�����ӳ�
	void KeyEvent();//��ȡ��������
	void drop();//���ƽ���
	void ClearLine();//�����
	void MoveLeftRight(int offest);//�����ƶ�
	void rotate();//��ת
	void CheckOver();//�����Ϸ�Ƿ����
	void SaveScore();//������߷�

	void SaveData();//��������
	void LoadGame();//������Ϸ
	//д����Ϣ
	void WriteNameAndScore();
	
	void ChangBgMusic();
	//��ȡ������Ϣ����
	void ReadMessage();
	//���밴����Ϣ
	int  ReadKeyCode(const string key);
public:
	//panduan�Ƿ������Ϸ
	void ifLoadGame(bool Ifloadgame);
public:
	Play(int rows, int cols, int left, int top, int blockSize, string name,string Drop);
	void play();//����������
	//��������ǳ�
	void SetPlayerName(string temp);
};

