#include "Play.h"
#include<iostream>
#include<fstream>
#include<conio.h>
#include"MyInput.h"
//#include<tchar.h>
using namespace std;
const string fileName = "document/recorder.txt";//历史最高分
const string SaveFile[5] = {"document/爱玩方块的小明.txt","document/爱玩方块的小红.txt"
,"document/方块专家老陈.txt","document/方块专家小美.txt","document/方块专家旭东.txt"};//存档
const string BlankFile = "document/players.txt";//保存玩家排名
const string SaveRecored = "document/recorder1.txt";
const int Max_Levels = 5;
const int SPEED_NORMAL[Max_Levels] = { 500,400,300,200,100 };//ms
const int SPEED_QUICK = 10;
static int PlayerNumber= 1;
int counter2 = 0;
int SaveCounter = 0;
struct classWindowData {
	int width = 672;
	int height = 896;
}classWindow;
void Play::SaveScore()
{
	if (score > HighestScore) {
		HighestScore = score;
		ofstream file(fileName);
		if (!file.is_open()) {
			cout << "保存最高分失败" << endl;
			exit(0);
		}
		file << HighestScore;
		file.close();
	}
}
/// <summary>
/// /保存游戏
/// </summary>
void Play::SaveData()
{
	//保存数据
	int counter = 0;
	for (int i = 0; i < 5; i++)
	{
		if (PlayerName == PlayersNames[i])
			counter = i;
	}
	fstream fout;
	ifstream fin;
	fout.open(SaveFile[counter], ios::out);
	fin.open("document/BlockFile.txt", ios::in);
	if (!fin.is_open())
	{
		cout << "打开方块样式文件错误" << endl;
		exit(-1);
	}
	string tempky;
	fin >> tempky;
	fin.close();
	if (!fout.is_open())
	{
		exit(-1);
	}
	fout<<MapName<<"\n"<<tempky<<"\n" << PlayerName << "\n" << levels << "\n" << score << "\n" << LineCount << "\n" << CurBlock->getBlockType() << "\n"
		<< NextBlock->getBlockType()<<"\n"<<timer<<"\n";//存储普通数据
	//方块数据
	for (int i = 0; i < 4; i++)
	{
		fout<<CurBlock->GetBlockRows(i)<<"\n";
		fout << CurBlock->GetBlockCols(i) << "\n";
	}
	for (int j = 0; j < 4; j++)
	{
		fout << NextBlock->GetBlockRows(j) << "\n";
		fout << NextBlock->GetBlockCols(j) << "\n";
	}
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			//if(j==cols-1)
			fout << map[i][j];
			/*else
			fout << map[i][j] ;*/
		}
		if(i!=rows-1)
		fout << "\n";
	}


}

void Play::LoadGame()
{
	int counter = 0;
	for (int i = 0; i < 5; i++)
	{
		if (PlayerName == PlayersNames[i])
			counter = i;
	}
	ifstream fin;
	fin.open(SaveFile[counter], ios::in);
	if (!fin.is_open())
	{
		exit(-1);
	}
	string tempjl;
	int curType = 0;//临时变量作为中间
	int nextType = 0;
	char data3[20];

	fin>>MapName>>tempjl>>PlayerName>> levels >> score >> LineCount>> curType >>nextType>>data3;//读取普通数据
	timer = stoi(data3); 
	NextBlock = new Block(curType,tempjl);
	CurBlock = NextBlock;
	NextBlock = new Block(nextType,tempjl);
	CurBlock->SetBlockType(curType);
	NextBlock->SetBlockType(nextType);
	
	int SubRow = 0;
	int SubCol = 0;
	for (int i = 0; i < 4; i++)
	{
		char data1[10];
		char data2[10];
		fin >> data1 >> data2;
		SubRow = stoi(data1);
		SubCol = stoi(data2);
		CurBlock->SetBlockPos(i, SubRow, SubCol);
	}
	for (int i = 0; i < 4; i++)
	{
		char data1[10];
		char data2[10];
		fin >> data1 >> data2;
		SubRow = stoi(data1);
		SubCol = stoi(data2);
		NextBlock->SetBlockPos(i, SubRow, SubCol);
	}
	char MapData[20][11];
	for (int i = 0; i < 20; i++)
	{
		fin >> MapData[i];
		for (int j = 0; j < 10; j++)
		{
			map[i][j] = (MapData[i][j] - '0');
		}
	}
}
void Play::WriteNameAndScore()
{
		ofstream fout;
		fout.open(BlankFile, ios::out);
		if (!fout.is_open())
		{
			cout << "打开保存玩家信息文件失败";
			exit(-1);
		}

			Players.name = PlayerName;
			Players.score = score;
			//存储当前玩家信息
			SavePlayers[counter2].SaveName = PlayerName;
			SavePlayers[counter2].SaveScore = score;
			counter2++;
			for (int i = 0; i < counter2; i++)
			{
				int temp = 0;
				string tempname;
				for (int j = 0; j < counter2 - i - 1; j++)
				{
					if (SavePlayers[j].SaveScore < SavePlayers[j + 1].SaveScore)
					{
						temp = SavePlayers[j].SaveScore;
						tempname = SavePlayers[j].SaveName;
						SavePlayers[j].SaveScore = SavePlayers[j + 1].SaveScore;
						SavePlayers[j].SaveName = SavePlayers[j + 1].SaveName;
						SavePlayers[j + 1].SaveScore = temp;
						SavePlayers[j + 1].SaveName = tempname;
					}
				}
			}
			if (counter2 <= 5)
			{
				for (int i = 0; i < counter2; i++)
				{
					fout << SavePlayers[i].SaveName << ":" << SavePlayers[i].SaveScore << "\n";
				}
			}
			else
			{
				for (int i = 0; i < counter2; i++)
				{
					fout << SavePlayers[i].SaveName << ":" << SavePlayers[i].SaveScore << "\n";
				}
			}
			fout.close();
			ofstream fin;
			fin.open(SaveRecored, ios::out);
			if (!fin.is_open())
				exit(-1);
			if (counter2 <= 5)
			{
				SaveCounter = counter2;
			}
			else if (counter2 > 5)
			{
				SaveCounter = 5;
			}
			fin << SaveCounter;
			fin.close();
		
}

void Play::ChangBgMusic()
{
	StopMusic(Cmusic);
	if (Cmusic < 3)
	{
		Cmusic++;
	}
	else if (++Cmusic >= 4)//做到无缝链接切换音乐
	{
		Cmusic = 1;
	}
	PlayMusic(Cmusic);
}


void Play::ReadMessage()
{
	char temp[10];
	ifstream fin;
	fin.open(SaveRecored, ios::in);
	if (!fin.is_open())
	{
		cout << "打开保存排名文件失败" << endl;
		exit(-1);
	}
	fin >>temp;
	SaveCounter = stoi(temp);
	if (SaveCounter == 0)
	{
		counter2 = 0;
		fin.close();
	}
	else if (SaveCounter > 0)
	{
		counter2 = SaveCounter;
		fin.close();
		ifstream fout;
		fout.open(BlankFile, ios::in);
		if (!fout.is_open())
		{
			cout << "打开保存排名文件失败" << endl;
			exit(-1);
		}
		for (int i = 0; i < SaveCounter; i++) {
			char data[20];
			fout >> data;
			MyInput CIN(data);
			SavePlayers[i].SaveName = CIN[0];
			SavePlayers[i].SaveScore = stoi(CIN[1]);
		}
	}

		
	//读出来顺便使用冒泡排序
	for (int i = 0; i < counter2; i++)
	{
		int temp = 0;
		string tempname;
		for (int j = 0; j < counter2 - i - 1; j++)
		{
			if (SavePlayers[j].SaveScore < SavePlayers[j+1].SaveScore)
			{
				temp = SavePlayers[j].SaveScore;
				tempname = SavePlayers[j].SaveName;
				SavePlayers[j].SaveScore = SavePlayers[j + 1].SaveScore;
				SavePlayers[j].SaveName = SavePlayers[j + 1].SaveName;
				SavePlayers[j + 1].SaveScore = temp;
				SavePlayers[j + 1].SaveName = tempname;
			}
		}
	}
	
}

int Play::ReadKeyCode(const string key)
{
	int a;
	ifstream fin;
	fin.open("document/keycode.txt", ios::in);
	if (!fin.is_open())
	{
		cout << "键码表文件打开错误" << endl;
		exit(-1);
	}
	for (int i = 0; i < 10; i++)
	{
		string in;

		fin >> in;
		MyInput CINKEY(in);
		if (CINKEY[0] == key)
		{
			a = stoi(CINKEY[1]);
			return a;
			break;
		}
	}
	fin.close();
}

void Play::ifLoadGame(bool ifloadgame)
{
	IfLoadPastGame = ifloadgame;
}



Play::Play(int rows,int cols,int left,int top,int blockSize,string name,string Drop):
	Board(rows,cols,left,top,blockSize,name)
{
	KeyMap[KEY_ROTATE]=ReadKeyCode("KEY_ROTATE");
	KeyMap[KEY_DOWN] = ReadKeyCode("KEY_DOWN");
	KeyMap[KEY_LEFT] = ReadKeyCode("KEY_LEFT" );
	KeyMap[KEY_RIGHT] = ReadKeyCode("KEY_RIGHT");
	KeyMap[KEY_SAVEDOC] = ReadKeyCode("KEY_SAVEDOC");
	KeyMap[KEY_GAMEPAUSE] = ReadKeyCode("KEY_GAMEPAUSE");
	KeyMap[KEY_CHANGMUSIC] = ReadKeyCode("KEY_CHANGMUSIC");
	KeyMap[KEY_RESETGAME] = ReadKeyCode("KEY_RESETGAME");
	KeyMap[KEY_LOADLASTGAME] = ReadKeyCode("KEY_LOADLASTGAME");
	KeyMap[KEY_RETURNMENU] = ReadKeyCode("KEY_RETURNMENU");
	DropSpeed = Drop;
}

void Play::play()
{
	init();
	
		NextBlock = new Block;
		CurBlock = NextBlock;
		NextBlock = new Block;
		if (IfLoadPastGame == true)
		{
			StopMusic(Cmusic);
			LoadGame(); 
			PlayMusic(Cmusic);
		}
		
	ReadMessage();
	
	while (1)
	{
		
		//接受用户输入
		KeyEvent();
		timer += GetDelay();
		//渲染游戏画面
		if (timer > delay)
		{
			timer = 0;
			drop();
			update = true;
		}
		if (update)
		{
			update = false;
			UpdateWindow();//更新游戏画面

			ClearLine();
		}
		if (GameOver) {
			SaveScore();
			displayOver();
			//DisplayMessage();
			WriteNameAndScore();
			system("pause");
			
			init();
		}
	}
}



void Play::SetPlayerName(string temp)
{
	PlayerName = temp;
}



int Play::GetDelay()
{
	static unsigned long long lastTime = 0;
	unsigned long long currentTime = GetTickCount();//获取运行毫秒数
	if (lastTime == 0)
	{
		lastTime = currentTime;
		return 0;
	}
	else
	{
		int ret = currentTime - lastTime;
		lastTime = currentTime;
		return ret;//返回时间间隔
	}
	
}

void Play::KeyEvent()
{
	unsigned char ch;
	bool rotateFlag = false;
	DropRows = 0;//下降行数重置
	int dx = 0;
	if (_kbhit())
	{
		ch = _getch();
		if (KeyMap[KEY_ROTATE] == 72)
		{
			if (ch == 224)
			{
				ch = _getch();

				if (ch == KeyMap[KEY_ROTATE])
					rotateFlag = true;
				else if (ch == KeyMap[KEY_DOWN])
					delay = SPEED_QUICK;
				else if (ch == KeyMap[KEY_LEFT])
					dx = -1;
				else if (ch == KeyMap[KEY_RIGHT])
					dx = 1;

			}
			else if (ch == KeyMap[KEY_SAVEDOC])
				SaveData();
			else if (ch == KeyMap[KEY_GAMEPAUSE])
				system("pause");
			else if (ch == KeyMap[KEY_CHANGMUSIC])
				ChangBgMusic();
			else if (ch == KeyMap[KEY_RESETGAME])
			{
				StopMusic(Cmusic);//做到避免上一首音乐与下一首音乐重合播放
				init();
				CurBlock = new Block;
				NextBlock = new Block;
			}
			else if (ch == KeyMap[KEY_LOADLASTGAME])
			{
				LoadGame();
			}
			else if (ch == KeyMap[KEY_RETURNMENU])
			{
				cout << "返回键运行了";
				StopMusic(Cmusic);
				Menu OP1;
				OP1.Operatoration();
			}
		}
		else if (KeyMap[KEY_ROTATE] == 119)
		{
			if (ch == KeyMap[KEY_ROTATE])
				rotateFlag = true;
			else if (ch == KeyMap[KEY_DOWN])
				delay = SPEED_QUICK;
			else if (ch == KeyMap[KEY_LEFT])
				dx = -1;
			else if (ch == KeyMap[KEY_RIGHT])
				dx = 1;
			else if (ch == KeyMap[KEY_SAVEDOC])
				SaveData();
			else if (ch == KeyMap[KEY_GAMEPAUSE])
				system("pause");
			else if (ch == KeyMap[KEY_CHANGMUSIC])
				ChangBgMusic();
			else if (ch == KeyMap[KEY_RESETGAME])
			{
				StopMusic(Cmusic);//做到避免上一首音乐与下一首音乐重合播放
				init();
				CurBlock = new Block;
				NextBlock = new Block;
			}
			else if (ch == KeyMap[KEY_LOADLASTGAME])
			{
				LoadGame();
			}
			else if (ch == KeyMap[KEY_RETURNMENU])
			{
				cout << "返回键运行了";
				StopMusic(Cmusic);
				Menu OP1;
				OP1.Operatoration();
			}
		}
		if (rotateFlag) {
			//旋转
			rotate();
			update = true;
		}
		//左右移动
		if (dx != 0) {
			MoveLeftRight(dx);
			update = true;
		}
	}
}


void Play::drop()
{
	BakBlock = *CurBlock;
	//cout << DropRows;
	CurBlock->drop();
	if (!CurBlock->blockInMap(map)) {
		BakBlock.solidify(map); //固定位置
		mciSendString("play sucai/luokuai.mp3", 0, 0, 0);
		delete CurBlock;//释放
		CurBlock = NextBlock;
		NextBlock = new Block;

		CheckOver();//检查是否结束
	}
	//设置游戏降落速度
	if (levels <= 5&&DropSpeed=="Normal")
	{
		delay = SPEED_NORMAL[levels - 1];
	}
	else if ((levels > 5||DropSpeed=="Hard")&&DropSpeed!="Easy")
	{
		delay = 50;
	}
	else if (DropSpeed == "Easy")
	{
		delay = SPEED_NORMAL[0];
	}
}
void Play::ClearLine()
{
	int lines = 0;
	int k = rows - 1;//存储行数
	for (int i = rows - 1; i >= 0; i--) {
		//检查是否满行
		int count = 0;
		for (int j = 0; j < cols; j++) {
			if (map[i][j]) {
				count++;
			}
			map[k][j] = map[i][j];
		}
		if (count < cols) {//不是满行
			k--;
		}
		else {
			lines++;
		}
	}
	if (lines > 0) {
		//计算得分
		int addScore[10] = { 20,40,60,80,90,100,110,120,130,140 };
		if (levels <= 10)
			score += addScore[levels - 1];
		else
			score += addScore[9];
		mciSendString("play xiaohang.mp3", 0, 0, 0);
		update = true;
		levels = (score + 99) / 100;
		/*if (levels > Max_Levels) {
			GameOver = true;
		}*/
		LineCount += lines;
	}
}
void Play::MoveLeftRight(int offest)
{
	BakBlock = *CurBlock;
	CurBlock->moveLeftRight(offest);
	if (!CurBlock->blockInMap(map)) {
		*CurBlock = BakBlock;
	}
}
void Play::rotate()
{
	//田字形不需要旋转
	if (CurBlock->getBlockType() == 7) {
		return;
	}
	BakBlock = *CurBlock;
	CurBlock->rotate();
	mciSendString("play sucai/rotate.mp3", 0, 0, 0);
	if (!CurBlock->blockInMap(map)) {
		*CurBlock = BakBlock;
	}
}
void Play::CheckOver()
{
	GameOver = (CurBlock->blockInMap(map) == false);
}
