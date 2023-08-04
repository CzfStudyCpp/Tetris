#include "MyInput.h"

MyInput::MyInput(string in)
{
	{
		int j = 0;
		string temp = "";
		len = 0;
		for (int i = 0; i < in.size(); i++)
		{
			if (in[i] == ':'||in[i]==',')
			{
				data[j++] = temp;
				temp = "";
			}
			else
				temp = temp + in[i];
		}
		data[j] = temp;
		len = j + 1;
	}
}

string MyInput::operator[](int index)
{
	
		return data[index];
	
}

int MyInput::GetLen()
{
		return len;
}
