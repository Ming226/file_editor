#include "line_editor.h"
#include <fstream> 

class Editor
{
	private:
		Text_line buffer; //�ı����� 
		int cur; //��ǰ�к�
		ifstream infile; //�����ļ�
		ofstream outfile; //����ļ�
	
	public:
		Editor(char in[], char out[]);//���캯����
		void Run(); //���б༭��
		void next();// ��ת����һ��
		void back(); //��ת��ǰһ��
		void jump(); //��ת��ָ����
		void insert(); //����һ��
		void del();//ɾ��ĳһ��
		void exchange();//�滻��ǰ��
		void find(); //�����Ӵ� 
		void show(); //չʾ����������
		void change_string(); //�滻�Ӵ�  ���������⣩ 
		void read_file(); //�����ļ�
		void write_file();//д�ı��ļ�
		void all();//�ļ��������ַ��� 
};
Editor::Editor(char in[], char out[])
{
	infile.open(in);
	if (infile.fail())
	{
		cout << "���ļ�ʧ��" << endl;
		exit(1);
	}
	outfile.open(out);
	if (outfile.fail())
	{
		cout << "���ļ�ʧ��" << endl;
		exit(1);
	}
	cur = 0; 
} 
void Editor::next()
{
	if (buffer.Next_line() == -1)
	{
		cout << "�Ѿ��������һ����" << endl; 
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
		cout <<"�Ѿ��ǵ�һ����" << endl; 
	}
	else
	{
		buffer.Show_cur();
	} 
}
		 
void Editor::jump()
{
	int temp;
	cout << "��������ת����" << endl;
	cin >> temp;
	buffer.Jump_line(temp);
	buffer.Show_cur(); 
}

void Editor::insert()
{
	int temp;
	string tempst; 
	cout << "����������к�" << endl;
	cin >> temp;
	cout << "�������������" << endl;
	cin >> tempst; 
	buffer.Insert_line(temp,tempst);
	cur = temp;  
 } 
 
void Editor::del()
{
		int temp;
	cout << "������ɾ���к�" << endl;
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
	cout << "�������滻����" << endl;
	cin >> exstring;
	buffer.Ex_line(exstring); 
}
void Editor::find()
{
	string fstring;
	cout <<"����������Ӵ�" << endl;
	cin >> fstring;
	buffer.Find_string(fstring); 
}
void Editor::show()
{
	buffer.Show_all();
}
void Editor::all()
{
	cout << "��ǰ�ļ�����" << endl;
	cout << buffer.Total_ch() << endl;
	cout << "��ǰ�ļ�����"  << endl;
	cout << buffer.Number_line() << endl; 
}
void Editor::change_string()
{
	string goal;
	string begoal;
	cout << "�������滻�ַ���" << endl;
	cin.ignore();
	getline(cin,goal);
	//cin.ignore(); //getline() ?? 
	cout << "�����뱻�滻�ַ���" << endl;
	getline(cin,begoal); 
	buffer.Ex_string(goal,begoal); 
 } 
void Editor::Run()
{
	char usercmd;
	char a[99];  //����ÿ�в�����99���ַ� 
	while (!infile.eof())
	{
		infile.getline(a,99);
         string templ(a);
		buffer.Append_line(templ); 
	}
	infile.close();
	cout << "��һ��:" << endl;
	buffer.Set_cur();
	buffer.Show_cur();
	do
	{
		cout << "��ѡ�������1��ת����һ��                   2��ת��ǰһ��" << endl
			 << "            3��ת��ָ����                   4������һ��  " << endl
			 << "            5���滻��ǰ��                   6�����Ҵ�    " << endl
			 << "            7����ʾ��ǰ�ļ�����             8���滻�Ӵ�  " << endl
			 << "            9����ʾ��ǰ�ļ��������ַ���     0���˳�        " << endl;
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
