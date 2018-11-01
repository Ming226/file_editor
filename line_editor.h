#ifndef _LINE_EDITOR_H
#define _LINE_EDITOR_H
#include <iostream>
#include <string>
#include<cstdlib>
using namespace std;
//节点类 
struct Line_node 
{
    string line;
	Line_node *pre;
    Line_node *next;

	Line_node(); //无参构造
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
//链表类 
class Text_line
{
    protected:
        Line_node *head;
        Line_node *cur_line;
        void Init();    //初始化 
       
    
    public:
    	 Line_node *Get_ptr(int postion) const;  //获取指定位置节点 
        Text_line();//构造函数 
        virtual ~Text_line(); //析构函数 
        void Show_cur(); //输出目前行 
        int Number_line() const ; //计算行数（链表长） 
        void Clear();   //清空链表 
        void Show_all();    //展示所有行 
        void Jump_line(int pos);  //跳转到指定行 
        int Next_line();   //跳转到下一行 
        int Pre_line();   //跳转到前一行 
		void Append_line(const string &e);//追加元素 
		void Set_cur();//设置当前行为第一行 
        void Insert_line(int pos,const string &e);   //在指定位置插入行 
        void Del_line(int pos);   //删除指定行 
        void Ex_line(const string &e);  //替换当前行 
        void Ex_string(const string &goal); //替换子串 
        void Find_string(const string &goal);  //查找子串 
        int Total_ch(); //统计所有字符 
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
		cout << "指定行不存在" << endl;
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
	cout << "添加到缓存成功" << endl;
}

void Text_line::Insert_line(int pos, const string &e)
{
	if (pos < 1 || pos > Number_line() + 1)
	{
		cout << "范围错误" << endl;
	}
	else
	{
		Line_node *ptr, *next_ptr, *new_ptr;
		ptr = Get_ptr(pos - 1);
		next_ptr = ptr->next;
		new_ptr = new Line_node(e, ptr, next_ptr);
		ptr -> next = new_ptr;
		next_ptr -> pre = new_ptr;
		cout << "插入成功" << endl;
	}

}

void Text_line::Del_line(int pos)
{
	if (pos < 1 || pos > Number_line())
	{
		cout << "范围错误" << endl;
	}
	else 
	{
		Line_node *ptr;
		ptr = Get_ptr(pos);
		if (pos != Number_line())
		{
			ptr->pre->next = ptr->next;
			ptr->next->pre = ptr->pre;
		} //非尾节点
		else  //尾节点
		{
			ptr->pre->next = NULL;
		}
		delete ptr;
		cout << "从缓存区删除成功" << endl;
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
			cout << count << "行 " << endl;
		}
		ptr = ptr->next;
		count++;
	}
	if(head -> next ->line.find(goal) == string::npos && count ==1)
	{
		cout <<"查找子串不存在" << endl;
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
