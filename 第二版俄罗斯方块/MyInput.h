#pragma once
#include<string>
#include<string.h>
using namespace std;
class MyInput
{

private:
	string data[10];
	int len;
public:
	MyInput(string in = ""); // 把输入的字符串按逗号分成单独的字符串

	string operator [](int index);

	int GetLen();

};


