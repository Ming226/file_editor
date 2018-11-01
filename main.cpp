#include "editor.h"

int main()
{
	char in[20];
	char out[20];
	cout << "请输入 输入文件名：" << endl;
	cin >> in; 
	cout <<"请输入 输出文件名：" << endl;
	cin >> out;
	Editor a(in,out);
	a.Run();
	return 0;
}

