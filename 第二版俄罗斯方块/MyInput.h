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
	MyInput(string in = ""); // ��������ַ��������ŷֳɵ������ַ���

	string operator [](int index);

	int GetLen();

};


