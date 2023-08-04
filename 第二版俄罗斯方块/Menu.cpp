#include "Menu.h"
const string BlanksFile = "document/players.txt";
const string Recored = "document/recorder1.txt";
const string Blockfile = "document/BlockFile.txt";
const string address[2] = {"sucai/tiles.png","sucai/blocks.png"};
const string MapData[2] = {"document/Map1Data.txt","document/Map2Data.txt"};
int WhichMap = 0;
string tempname;
string BlockName;
struct KeyData {
	string name="";
	int keydata = 0;
}Keydata[10];
Menu::Menu()
{
	
}
void Menu::SelectSetting(ExMessage*msg)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (IsInRect(msg, 111, 232, 400, 110))
		{
			cout << "2";
			/*setfillcolor(RGB(19, 214, 41));*/
			
			MenuState = KeySetting;
			//cout << 2;
		}
		else if (IsInRect(msg, 112, 430, 400, 110))
		{
			/*setfillcolor(RGB(19, 214, 41));*/
			cout << "3";
			
			MenuState = BgpSetting;

		}
		else if (IsInRect(msg, 112, 596, 400, 130))
		{
			cout << "4";
			
			MenuState = SelectBlock;
		}
		else if (IsInRect(msg, 60, 750, 120, 120))
		{
			cout << "5";
			
			DropSpeed = "Easy";
		}
		else if (IsInRect(msg, 240, 750, 120, 120))
		{
			cout << "6";
			
			DropSpeed = "Normal";
		}
		else if (IsInRect(msg, 430, 750, 120, 120))
		{
			cout << "6";
			
			DropSpeed = "Hard";
		}
		
	}

}
void Menu::ReadFile()
{
	ifstream fin;
	fin.open("document/MapData.txt", ios::in);
	if (!fin.is_open())
	{
		cout << "打开文件失败2333";
		exit(-1);
	}
	string in;
	fin >> in;
	if (in == "map1")
	{
		WhichMap = 0;
		MapName = "map1";
	}
	else if (in == "map2")
	{
		WhichMap =1;
		MapName = "map2";
	}
	fin.close();
}
bool Menu::IsInRect(ExMessage* msg, int x, int y, int w, int h)
{
	if (msg->x > x && msg->x<x + w && msg->y>y && msg->y < y + h)
	{
		return true;
	}
	else
		return false;
}

void Menu::ChangeWindow(ExMessage* msg)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (IsInRect(msg, 120, 315, 410, 66))
		{
			cout << "2";
			
			MenuState = SelectName;
			IfPlay = true;
			//cout << 2;
		}
		else if (IsInRect(msg, 120, 557, 410, 66))
		{
			
			cout << "3";
			MenuState = Content;

		}
		else if (IsInRect(msg, 120, 476, 410, 66))
		{
			cout << "4";
			
			MenuState = PlayerBlank;
		}
		else if (IsInRect(msg, 246, 677, 72, 203))
		{
			cout << "5";
			
			MenuState = GameDoc;
		}
		else if (IsInRect(msg, 120, 400, 410, 66))
		{
			cout << "6";
			
			MenuState = HomeGameSetting;
		}
	}
}

void Menu::KeyAct()
{
	int ch2 = 0;
	if (_kbhit()) {
		ch2 = _getch();
		if (ch2 == 27)
		{
			switch (MenuState)
			{
			case StartGame:
				MenuState = SelectName;
				break;
			case SelectName:
				MenuState = Home;
				break;
			case HomeGameSetting:
				MenuState = Home;
				break;
			case PlayerBlank:
				MenuState = Home;
				break;
			case Content:
				MenuState = Home;
				break;
			case GameDoc:
				MenuState = Home;
				break;
			case KeySetting:
				MenuState = HomeGameSetting;
				break;
			case BgpSetting:
				MenuState = HomeGameSetting;
				break;
			case Home:
				MenuState = Home;
				break;
			case SelectBlock:
				MenuState = HomeGameSetting;
				break;
			default:
				MenuState = Home;
				break;
			}
		}
	}
}

void Menu::selectName(ExMessage* msg)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (IsInRect(msg, 200, 45, 290, 90))
		{
			
			MenuState = StartGame;
			counter = 0;
		}
		else if (IsInRect(msg, 200, 190, 290, 90))
		{
			
			MenuState = StartGame;
			counter = 1;
		}
		else if (IsInRect(msg, 200, 330, 290, 90))
		{
			
			MenuState = StartGame;
			counter = 2;
		}
		else if (IsInRect(msg, 200, 460, 290, 90))
		{
			
			MenuState = StartGame;
			counter = 3;
		}
		else if (IsInRect(msg, 200, 585, 290, 90))
		{
			
			MenuState = StartGame;
			counter = 4;
		}
	}
	
}

void Menu::ReadAndShowBlank()
{
	int pos[5][2] = {
	90,200,
	90,350,
	90,500,
	90,641,
	90,780, };
	ifstream fin;
	ifstream Savecount;
	fin.open(BlanksFile, ios::in);
	Savecount.open(Recored, ios::in);
	
	char temp[10];
	Savecount >> temp;

	int counter = stoi(temp);
	Savecount.close();
	//cout << counter;
		if (counter == 0)
		{
			cout << "暂时无排名";
		}
		else if (counter > 0)
		{
			char in[50];
			fin.seekg(0, ios::beg);
			for (int i = 0; i < counter; i++)
			{
			
				fin >> in;
				cout << in << endl;
				setcolor(RGB(0, 0, 0));
				LOGFONT f;//字体
				gettextstyle(&f);//获取当前字体
				f.lfHeight = 50;
				f.lfWidth = 30;
				f.lfQuality = ANTIALIASED_QUALITY;//抗锯齿
				strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI Black"));//选择字体
				settextstyle(&f);//设置字体

				setbkmode(TRANSPARENT);//字体的背景设置为透明效果
				outtextxy(pos[i][0], pos[i][1], in);
			}
			fin.close();

		}
}

void Menu::SelectDoc(ExMessage*msg)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (IsInRect(msg, 93, 80, 360, 95))
		{
			int i = 0;
			if (FileIfEmpty(i))
			{
				
				MenuState = StartGame;
				IfLoadGame = true;
				counter = 0;
			}
			else
			{
				putimage(0, 0, &FailMenu);
				
					MenuState = GameDoc;

			}
		}
		else if (IsInRect(msg, 93, 235, 360, 95))
		{
			int i = 1;
			if (FileIfEmpty(1))
			{
				
				MenuState = StartGame;
				IfLoadGame = true;
				counter = 1;
			}
			else
			{
				putimage(0, 0, &FailMenu);
				
				MenuState = GameDoc;
				
			}
		}
		else if (IsInRect(msg, 93, 380, 360, 95))
		{
			int i = 2;
			if (FileIfEmpty(2))
			{
				
				MenuState = StartGame;
				IfLoadGame = true;
				counter = 2;
			}
			else
			{

				putimage(0, 0, &FailMenu);
				
					MenuState = GameDoc;

			}
		}
		else if (IsInRect(msg, 93, 523, 360, 95))
		{
			
			if (FileIfEmpty(3))
			{
				MenuState = StartGame;
			
				IfLoadGame = true;
				counter = 3;
			}
			else
			{
				putimage(0, 0, &FailMenu);
				
					MenuState = GameDoc;
			}
		}
		else if (IsInRect(msg, 93, 670, 360, 95))
		{
			
			if (FileIfEmpty(4))
			{
				MenuState = StartGame;
				
				IfLoadGame = true;
				counter = 4;
			}
			else
			{
				putimage(0, 0, &FailMenu);
				
					MenuState = GameDoc;

			}

		}
	}
}

bool Menu::FileIfEmpty(int i)
{
	ifstream fin;
	string line;
	fin.open(SaveFile[i], ios::in);
	if (!fin.is_open())
	{
		cout << "检查文件是否为空时，打开失败";
		exit(-1);
	}
	//因为存档文件不存在空行，读取整行，如果读取失败，则文件为空
	if (getline(fin, line))//有内容
	{
		return true;
	}
	else 
	return false;
	fin.close();
}

void Menu::selectblock(ExMessage* msg)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (IsInRect(msg, 130, 330, 322, 48))
		{
			
			which = 0;
		}
		else if (IsInRect(msg, 137, 444, 203, 70))
		{
			
			which = 1;
		}
	}
}

void Menu::selectMap(ExMessage*msg)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (IsInRect(msg, 116, 94, 404, 240))
		{
			//第一张背景
			
			WhichMap = 0;
			MapName = "map1";
			cout << "选择地图为" <<" " <<WhichMap<< endl;
		}
		else if (IsInRect(msg, 125, 434, 339, 243))
		{
			
			WhichMap = 1;
			MapName = "map2";
			cout << "选择地图为" << " " << WhichMap << endl;
		}
	}
}

void Menu::ReadMapName()
{
	ifstream fin;
	fin.open(SaveFile[counter],ios::in);
	if (!fin.is_open())
	{
		cout  << "读取玩家地图文件失败666" << endl;
		exit(-1);
	}
	fin >> tempname;
}

void Menu::ChangeMapFile()
{
	int data[5][2];
	ifstream fin;
	int subtemp=0;
	if (tempname == "map1")
	{
		subtemp = 0;
	}
	else if(tempname == "map2")
	{
		subtemp = 1;
	}
	fin.open(MapData[subtemp], ios::in);
	if (!fin.is_open())
	{
		exit(-1);
	}
	string map;
	fin >> map;
	for (int i = 1; i < 6; i++)
	{
		string in;
		int j = i - 1;
		fin >> in;
		MyInput Cin(in);
		data[j][0] = stoi(Cin[0]);
		data[j][1] = stoi(Cin[1]);
	}
	fin.close();
	ofstream fout;
	fout.open("document/MapData.txt", ios::out);
	if (!fout.is_open())
	{
		exit(-1);
	}
	fout << map << "\n";
	for (int i = 0; i < 5; i++)
	{
		fout << data[i][0] << "," << data[i][1] << "\n";
	}
	fout.close();
	KeyAct();
}

void Menu::ReadKeyCode()
{
	ifstream fin;
	fin.open("document/keycode.txt", ios::in);
	if (!fin.is_open())
	{
		cout << "菜单读取键码表失败";
		exit(-1);
	}
	for (int i = 0; i < 10; i++)
	{
		string in;
		fin >> in;
		MyInput CIN(in);
		Keydata[i].name = CIN[0];
		Keydata[i].keydata =stoi(CIN[1]);
	}
	
}

void Menu::showYourKey()
{
	int pos[6] = {100,180,260,340,420,500};
	int counter3 = 0;
	for (int i = 4; i < 10; i++)
	{

		char scoreText[32];
		//sprintf_s(scoreText, sizeof(scoreText), "%d", Keydata[i].keydata);//通过C#的方式进行绘制方便快捷
		char a = Keydata[i].keydata;
		if (Keydata[i].keydata == 27)
		{
			char b[3] = { 'E','S','C'};
		}
		setcolor(RGB(0, 0, 0));//根据绘图软件获得颜色参数，从而设置自己想要的颜色
		LOGFONT f;//字体
		gettextstyle(&f);//获取当前字体
		f.lfHeight = 60;
		f.lfWidth = 30;
		f.lfQuality = ANTIALIASED_QUALITY;//抗锯齿
		strcpy_s(f.lfFaceName, sizeof(f.lfFaceName), _T("Segoe UI Black"));//选择字体
		settextstyle(&f);//设置字体
		setbkmode(TRANSPARENT);//字体的背景设置为透明效果
		if (Keydata[i].keydata == 27)
		{
			char b[3] = { 'E','S','C' };
			outtextxy(290, pos[counter3], "ESC");
		}
		else
		{
			char b[3] = { 'E','S','C' };
			outtextxy(290, pos[counter3], a);
		}
		counter3++;
	}
}

void Menu::ChangKeys(ExMessage*msg)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (IsInRect(msg, 250, 35, 180, 52))
		{
			
			Keydata[0].keydata = 72;
			Keydata[1] .keydata= 80;
			Keydata[2].keydata = 75;
			Keydata[3].keydata = 77;
			
		}
		else if (IsInRect(msg, 470, 37, 180, 52))
		{
		
			Keydata[0].keydata = 119;
			Keydata[1].keydata = 115;
			Keydata[2].keydata = 97;
			Keydata[3].keydata = 100;
		}
		else if (IsInRect(msg, 258, 115, 156, 47))
		{
			if (_kbhit())
			{
				unsigned char ch;
				ch = _getch();
				int a = ch;
				Keydata[4].keydata = a;
				
			}

		}
		else if (IsInRect(msg, 258, 200, 156, 47))
		{
			if (_kbhit())
			{
				unsigned char ch;
				ch = _getch();
				int a = ch;
				Keydata[5].keydata = a;
				
			}

		}
		else if (IsInRect(msg, 258, 280, 156, 47))
		{
			if (_kbhit())
			{
				unsigned char ch;
				ch = _getch();
				int a = ch;
				Keydata[6].keydata = a;
				
			}

		}
		else if (IsInRect(msg, 258, 363, 156, 47))
		{
			if (_kbhit())
			{
				unsigned char ch;
				ch = _getch();
				int a = ch;
				Keydata[7].keydata = a;
				
			}

		}
		else if (IsInRect(msg, 258, 436, 156, 47))
		{
			if (_kbhit())
			{
				unsigned char ch;
				ch = _getch();
				int a = ch;
				Keydata[8].keydata = a;
				
			}

		}
		else if (IsInRect(msg, 140, 643, 190, 75))
		{

			Keydata[0].keydata = 72;
			Keydata[1].keydata = 80;
			Keydata[2].keydata = 75;
			Keydata[3].keydata = 77;
			Keydata[4].keydata = 107;
			Keydata[5].keydata = 112;
			Keydata[6].keydata = 113;
			Keydata[7].keydata = 99;
			Keydata[8].keydata = 106;
			
		}
	}
}

void Menu::WriteKeysCode()
{
	ofstream fout;
	fout.open("document/keycode.txt", ios::in);
	if (!fout.is_open())
	{
		cout << "写入键码文件时候打开文件失败" << endl;
	}
	for (int i = 0; i < 10; i++)
	{
		fout << Keydata[i].name << ":" << Keydata[i].keydata << "\n";
	}
}

void Menu::LoadBlockType()
{
	ifstream fin;
	fin.open(SaveFile[counter], ios::in);
	if (!fin.is_open())
	{
		cout << "读取玩家方块样式文件失败666" << endl;
		exit(-1);
	}
	string temp;
	fin >> temp;
	fin >> BlockName;
	fin.close();
	ofstream fout;
	fout.open("document/BlockFile.txt", ios::out);
	if (!fout.is_open())
	{
		exit(-1);
	}
	fout << BlockName;
}




void Menu::InitWindow()
{
	//对菜单所有图片初始化，初始化音乐
	initgraph(windowData.width, windowData.height,SHOWCONSOLE);
	loadimage(&MenuMap, "sucai/menu.png", windowData.width, windowData.height);
	putimage(0, 0, &MenuMap);

	mciSendString("open sucai/MenuBgm.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);
	
	loadimage(&SubMenu, "sucai/introd.png", windowData.width, windowData.height);
	loadimage(&NameMap, "sucai/players.png", windowData.width, windowData.height);
	loadimage(&Blanks, "sucai/blank.png", windowData.width, windowData.height);
	loadimage(&LoadMenu, "sucai/存档.png", windowData.width, windowData.height);
	loadimage(&FailMenu, "sucai/读取存档失败.png");
	loadimage(&SetTing, "sucai/setting.png", windowData.width, windowData.height);
	loadimage(&Block, "sucai/1.png", windowData.width, windowData.height);
	loadimage(&Map, "sucai/map.png", windowData.width, windowData.height);
	loadimage(&KeysMap, "sucai/keysetting.png", windowData.width, windowData.height);
	ReadKeyCode();
}

void Menu::Operatoration()
{
	InitWindow();
	while (1)
	{
		//cout << "1";
		while (peekmessage(&msg, EM_MOUSE))
		{
			//主菜单
			if (MenuState == Home)
			{
				cout << "1";
				putimage(0, 0, &MenuMap);
				ChangeWindow(&msg);
			}
			else if (MenuState == SelectName)
			{
				//选择昵称
				putimage(0, 0, &NameMap);
				selectName(&msg);
				KeyAct();
			}
			else if (MenuState == StartGame)//开始游戏
			{
				cout << "IfPlay:" << 1;
				mciSendString("close BGM", 0, 0, 0);
				ReadFile();//读取地图信息
				if (WhichMap == 0)
				{
					left = 88;
					top = 60;
				}
				else if (WhichMap == 1)
				{
					left = 31;
					top = 35;
				}
				Play game(rows, cols, left, top, blockSize, MapName,DropSpeed);
				game.SetPlayerName(Players[counter]);
				game.ifLoadGame(IfLoadGame);
				game.play();
			}
			else if (MenuState == Content)//显示简介
			{
				putimage(0, 0, &SubMenu);
				KeyAct();
			}
			else if (MenuState == PlayerBlank)
			{
				//提供一个缓冲区，解决屏闪
				BeginBatchDraw();
				putimage(0, 0, &Blanks);
				ReadAndShowBlank();
				EndBatchDraw();
				KeyAct();
			}
			else if (MenuState == GameDoc)
			{
				putimage(0, 0, &LoadMenu);
				SelectDoc(&msg);
				ReadMapName();
				ChangeMapFile();
				LoadBlockType();
				KeyAct();
			}
			else if (MenuState == HomeGameSetting)
			{
				putimage(0, 0, &SetTing);
				SelectSetting(&msg);
			
				KeyAct();
			}
			else if (MenuState == SelectBlock)
			{
				putimage(0, 0, &Block);
				selectblock(&msg);
				ofstream fin;
				fin.open(Blockfile, ios::out);
				if (!fin.is_open())
				{
					exit(-1);
				}
				if (which == 0)
				{
					fin << address[1];
				}
				else if (which == 1)
				{
					fin << address[0];
				}
				fin.close();
				cout <<"方块样式" << which;
				KeyAct();
			}
			else if (MenuState == BgpSetting)
			{
				putimage(0, 0, &Map);
				selectMap(&msg);
				int subwhichmap = WhichMap;
				int data[5][2];
				ifstream fin;
				fin.open(MapData[subwhichmap], ios::in);
				if (!fin.is_open())
				{
					exit(-1);
				}
				string map;
				fin >> map;
				for (int i =1; i < 6; i++)
				{
					string in;
					int j = i - 1;
					fin >> in;
					MyInput Cin(in);
					data[j][0] = stoi(Cin[0]);
					data[j][1] = stoi(Cin[1]);
				}
				fin.close();
				ofstream fout;
				fout.open("document/MapData.txt", ios::out);
				if (!fout.is_open())
				{
					exit(-1);
				}
				fout << map<<"\n";
				for (int i = 0; i < 5; i++)
				{
					fout << data[i][0] << "," << data[i][1] << "\n";
				}
				fout.close();
				KeyAct();
			}
			else if (MenuState == KeySetting)
			{
				BeginBatchDraw();
				putimage(0, 0, &KeysMap);
				showYourKey();
				ChangKeys(&msg);
				showYourKey();
				EndBatchDraw();
				WriteKeysCode();
				KeyAct();
				}
		}
		 
	}
	//开始游戏

}
