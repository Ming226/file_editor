#include "editor.h"

int main()
{
	char in[20];
	char out[20];
	cout << "������ �����ļ�����" << endl;
	cin >> in; 
	cout <<"������ ����ļ�����" << endl;
	cin >> out;
	Editor a(in,out);
	a.Run();
	return 0;
}

