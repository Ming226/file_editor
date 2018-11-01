#ifndef _LINE_EDITOR_H
#define _LINE_EDITOR_H
#include <iostream>
#include <string>
#include<cstdlib>
using namespace std;
//�ڵ��� 
struct Line_node 
{
    string line;
	Line_node *pre;
    Line_node *next;

	Line_node(); //�޲ι���
	Line_node(string p_line, Line_node *pre_link = NULL , Line_node *next_link = NULL);
};
Line_node::Line_node()
{
	next = NULL;
}

Line_node::Line_node(string p_line, Line_node *pre_link , Line_node *next_link )
{
    pre = pre_link;
    next = next_link;
    line = p_line;
}
//������ 
class Text_line
{
    protected:
        Line_node *head;
        Line_node *cur_line;
        void Init();    //��ʼ�� 
       
    
    public:
    	 Line_node *Get_ptr(int postion) const;  //��ȡָ��λ�ýڵ� 
        Text_line();//���캯�� 
        virtual ~Text_line(); //�������� 
        void Show_cur(); //���Ŀǰ�� 
        int Number_line() const ; //���������������� 
        void Clear();   //������� 
        void Show_all();    //չʾ������ 
        void Jump_line(int pos);  //��ת��ָ���� 
        int Next_line();   //��ת����һ�� 
        int Pre_line();   //��ת��ǰһ�� 
		void Append_line(const string &e);//׷��Ԫ�� 
		void Set_cur();//���õ�ǰ��Ϊ��һ�� 
        void Insert_line(int pos,const string &e);   //��ָ��λ�ò����� 
        void Del_line(int pos);   //ɾ��ָ���� 
        void Ex_line(const string &e);  //�滻��ǰ�� 
        void Ex_string(const string &goal); //�滻�Ӵ� 
        void Find_string(const string &goal);  //�����Ӵ� 
        int Total_ch(); //ͳ�������ַ� 
		void Cur_line();
};

void Text_line::Set_cur()
{
	cur_line = head -> next; 
 } 
void Text_line::Show_cur()
{
	cout << cur_line -> line << endl;
 } 
Line_node * Text_line::Get_ptr(int pos) const
{
	Line_node *ptr = head;
	int cur_pos = 0;

	while (ptr != NULL && cur_pos < pos)
	{
		ptr = ptr -> next;
		cur_pos++;
	}

	if (ptr != NULL && cur_pos == pos) return ptr;

	else return NULL;

}
void Text_line::Init()
{
	head = new Line_node();
	cur_line = head;
}
void Text_line::Cur_line()
{
	cout << cur_line->line;
}

Text_line::Text_line()
{
	Init();
}

Text_line::~Text_line()
{
	Clear();
	delete head;
}

int Text_line::Number_line() const 
{
	int count = 0;
	for (Line_node *ptr = head -> next; ptr != NULL; ptr = ptr->next)
	{
		count++;
	}
	return count;
}

void Text_line::Clear()
{
	while (Number_line() > 0)
	{
		Del_line(1);
	}
}

void Text_line::Show_all()
{
	for (Line_node *ptr = head -> next; ptr != NULL; ptr = ptr -> next)
	{
		cout << ptr -> line << endl;
	}
}
void Text_line::Jump_line(int pos)
{
	if (pos < 0 || pos > Number_line())
	{
		cout << "ָ���в�����" << endl;
	}
	else
	{
		Line_node *ptr;
		ptr = Get_ptr(pos);
		cur_line = ptr;
	}
}

int Text_line::Next_line()
{
	if (cur_line == Get_ptr(Number_line())) return -1;
	else 
	{
	cur_line = cur_line->next;
	return 1;
	}
}

int Text_line::Pre_line()
{
	if (cur_line == head) return -1;
	else 
	{
	cur_line = cur_line->pre;
	return 1;
	}
}
void Text_line::Append_line(const string &e)
{
	Line_node *ptr, *newptr;
	ptr = Get_ptr(Number_line());
	newptr = new Line_node(e,ptr,NULL);
	ptr -> next = newptr;
	cur_line = newptr;
	cout << "��ӵ�����ɹ�" << endl;
}

void Text_line::Insert_line(int pos, const string &e)
{
	if (pos < 1 || pos > Number_line() + 1)
	{
		cout << "��Χ����" << endl;
	}
	else
	{
		Line_node *ptr, *next_ptr, *new_ptr;
		ptr = Get_ptr(pos - 1);
		next_ptr = ptr->next;
		new_ptr = new Line_node(e, ptr, next_ptr);
		ptr -> next = new_ptr;
		next_ptr -> pre = new_ptr;
		cout << "����ɹ�" << endl;
	}

}

void Text_line::Del_line(int pos)
{
	if (pos < 1 || pos > Number_line())
	{
		cout << "��Χ����" << endl;
	}
	else 
	{
		Line_node *ptr;
		ptr = Get_ptr(pos);
		if (pos != Number_line())
		{
			ptr->pre->next = ptr->next;
			ptr->next->pre = ptr->pre;
		} //��β�ڵ�
		else  //β�ڵ�
		{
			ptr->pre->next = NULL;
		}
		delete ptr;
		cout << "�ӻ�����ɾ���ɹ�" << endl;
	}
}

void Text_line::Ex_line(const string &e)
{
	cur_line->line = e;
}

void Text_line::Ex_string(const string &goal)
{
	Line_node *ptr;
	for (ptr = head->next; ptr != NULL; ptr = ptr->next)
	{
		if (ptr->line.find(goal) != NULL)
		{
			ptr->line.replace(0, goal.length(), goal);
		}
	}
}

void Text_line::Find_string(const string &goal)
{
	int count = 1;
	Line_node *ptr;
	ptr = head->next;
	while (ptr != NULL)
	{
		if (ptr->line.find(goal) != string::npos)
		{
			cout << count << "�� " << endl;
		}
		ptr = ptr->next;
		count++;
	}
	if(head -> next ->line.find(goal) == string::npos && count ==1)
	{
		cout <<"�����Ӵ�������" << endl;
	 } 

}

int Text_line::Total_ch()
{
	int num = 0;
	Line_node *ptr;
	ptr = head->next;
	while (ptr != NULL)
	{
		num += ptr->line.length();
		ptr = ptr->next;
	}
	return num;
}
#endif
