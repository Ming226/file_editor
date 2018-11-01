#include "line_editor.h"
#include <fstream> 

class Editor
{
	private:
		Text_line buffer; //文本缓存 
		int cur; //当前行号
		ifstream infile; //输入文件
		ofstream outfile; //输出文件
	
	public:
		Editor(char in[], char out[]);//构造函数；
		void Run(); //运行编辑器
		void next();// 跳转到下一行
		void back(); //跳转到前一行
		void jump(); //跳转到指定行
		void insert(); //插入一行
		void del();//删除某一行
		void exchange();//替换当前行
		void find(); //查找子串 
		void show(); //展示缓存所有行
		void change_string(); //替换子串  （还有问题） 
		void read_file(); //读入文件
		void write_file();//写文本文件
		void all();//文件行数和字符数 
};
Editor::Editor(char in[], char out[])
{
	infile.open(in);
	if (infile.fail())
	{
		cout << "打开文件失败" << endl;
		exit(1);
	}
	outfile.open(out);
	if (outfile.fail())
	{
		cout << "打开文件失败" << endl;
		exit(1);
	}
	cur = 0; 
} 
void Editor::next()
{
	if (buffer.Next_line() == -1)
	{
		cout << "已经到了最后一行了" << endl; 
	}
	else 
	{
		buffer.Show_cur();	
	}
 } 

void Editor::back()
{
	//buffer.Pre_line();
	if (buffer.Pre_line() == -1)
	{
		cout <<"已经是第一行了" << endl; 
	}
	else
	{
		buffer.Show_cur();
	} 
}
		 
void Editor::jump()
{
	int temp;
	cout << "请输入跳转行数" << endl;
	cin >> temp;
	buffer.Jump_line(temp);
	buffer.Show_cur(); 
}

void Editor::insert()
{
	int temp;
	string tempst; 
	cout << "请输入插入行号" << endl;
	cin >> temp;
	cout << "请输入插如内容" << endl;
	cin >> tempst; 
	buffer.Insert_line(temp,tempst);
	cur = temp;  
 } 
 
void Editor::del()
{
		int temp;
	cout << "请输入删除行号" << endl;
	cin >> temp;
	buffer.Del_line(temp);
	if (temp <= cur)
	{
		cur--;
	}
}
void Editor::exchange()
{
	string exstring;
	cout << "请输入替换内容" << endl;
	cin >> exstring;
	buffer.Ex_line(exstring); 
}
void Editor::find()
{
	string fstring;
	cout <<"请输入查找子串" << endl;
	cin >> fstring;
	buffer.Find_string(fstring); 
}
void Editor::show()
{
	buffer.Show_all();
}
void Editor::all()
{
	cout << "当前文件字数" << endl;
	cout << buffer.Total_ch() << endl;
	cout << "当前文件行数"  << endl;
	cout << buffer.Number_line() << endl; 
}
void Editor::change_string()
{
	string goal;
	string begoal;
	cout << "请输入替换字符串" << endl;
	cin.ignore();
	getline(cin,goal);
	//cin.ignore(); //getline() ?? 
	cout << "请输入被替换字符串" << endl;
	getline(cin,begoal); 
	buffer.Ex_string(goal,begoal); 
 } 
void Editor::Run()
{
	char usercmd;
	char a[99];  //假设每行不超过99个字符 
	while (!infile.eof())
	{
		infile.getline(a,99);
         string templ(a);
		buffer.Append_line(templ); 
	}
	infile.close();
	cout << "第一行:" << endl;
	buffer.Set_cur();
	buffer.Show_cur();
	do
	{
		cout << "请选择操作：1：转到下一行                   2：转到前一行" << endl
			 << "            3：转到指定行                   4：插入一行  " << endl
			 << "            5：替换当前行                   6：查找串    " << endl
			 << "            7：显示当前文件内容             8：替换子串  " << endl
			 << "            9：显示当前文件行数和字符数     0：退出        " << endl;
		cin >> usercmd; 
		switch(usercmd)
		{
			case '1': 
				next();
				break;
			case '2':
				back();
				break;
			case '3':
				jump();
				break;
			case '4':
				insert();
				break;
			case '5':
				exchange();
				break;
			case '6':
				find();
				break;
			case '7':
				show();
				break;
			case '8' :
				change_string();
				break;
			case '9' :
				all();
				break;
			case '0' :
				 break;		
		}	
	} while (usercmd != '0');
	for (int i = 1 ;i <= buffer.Number_line();i++)
	{
		 outfile << buffer.Get_ptr(i) -> line << endl;
	}
	outfile.close();
}
