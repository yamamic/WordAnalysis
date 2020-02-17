#include<stdio.h>
#include<fstream>
#include<string>
#include<string.h>
using namespace std;
string str = "";
fstream file;
fstream w_file;
int i(0);//用于返回保留字符的数字
char ch;
int site_h(1), site_l(1);
int sign_sitel;
/*含有的词*/
/*关键字:
	program */
struct keyword {
	string kword;
};
keyword Kd[40];
struct letterword {
	
};
struct digitword {

};
void GetChar()//读入下一字符
{
	ch = file.get();
	site_l++;
	sign_sitel = site_l;
	if (ch == '\n')
	{
		site_h++;
		site_l = 0;
		sign_sitel--;
	}
}

void GetBC()//检查ch中字符是否为空格,如果是则调用GetChar函数直至ch不为空
{
	while (ch == ' '||ch=='\n')
	{
		GetChar();
	}
}

void Concat()//将ch中的字符连接到str之后
{
	str += ch;
}

bool Is_Letter()//判断是否为字母
{
	if ('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z')
	{
		return true;
	}
	return false;
}

bool Is_Digit()//判断是否为数字
{
	if ('0' <= ch && ch <= '9')
	{
		return true;
	}
	return false;
}

int Reserve()//对str中的字符串查找保留字表,若它是保留字则返回它的编码,否则返回0值.(0不是编码字符)
{
	int i(0);
	for (i = 1; i < 40; i++)
	{
		if (Kd[i].kword._Equal(str))
		{
			return i;
		}
	}
	return 0;
}

void Retract()//将搜索指针往前回调一个字符位置,并将ch置为空字符
{
	file.seekg(-1, ios::cur);
	ch = ' ';
}

/*letterword* InsertId(string str)//插入符号表(空置)
{

}

digitword* InsertConst(string str)//插入常数表(空置)
{

}
*/
bool Judge()
{
	if (Is_Letter())
		return true;
	if (Is_Digit())
		return true;
	if (ch == '=')
		return true;
	if (ch == '>')
		return true;
	if (ch == '<')
		return true;
	if (ch == '+')
		return true;
	if (ch == '-')
		return true;
	if (ch == '*')
		return true;
	if (ch == '/')
		return true;
	if (ch == ':')
		return true;
	if (ch == '{')
		return true;
	if (ch == '}')
		return true;
	if (ch == '[')
		return true;
	if (ch == ']')
		return true;
	if (ch == ';')
		return true;
	if (ch == ' ')
		return true;
	if (ch == '(')
		return true;
	if (ch == ')')
		return true;
	if (ch == '\n')
		return true;
	return false;
}

void Find_s()//寻找下一个空格或者回车
{
	while (ch != ' ' && ch != '\n')
	{
		GetChar();
	}
}
void Lexical_Analysis()//转换程序
{
	GetBC();
	if (Is_Letter())//以字母开头
	{
		while (Is_Letter() || Is_Digit())//若依然是字母,继续循环
		{
			Concat();
			GetChar();
		}
		if (Judge()||file.eof())
		{
			i = Reserve();
			if (i)
				w_file << str << " " << "保留字符\n";
			else
				w_file << str << " id\n";
		}
		else
		{
			GetChar();
			site_l--;
			if (Is_Letter())
			{
				if(ch=='\n')
					printf("第%d行,第%d列出现词法错误!\n", site_h-1, sign_sitel);
				//w_file << "第" << site_h << "行,第" << site_l << "列出现词法错误!\n";
				else
					printf("第%d行,第%d列出现词法错误!\n", site_h, site_l);
				site_l++;
				Find_s();
				return;
			}
			else
			{
				i = Reserve();
				if (i)
					w_file << str << " " << "保留字符\n";
				else
					w_file << str << " id\n";
				//w_file << "第" << site_h << "行,第" << site_l << "列出现词法错误!\n";
				if (ch == '\n')
					printf("第%d行,第%d列出现词法错误!\n", site_h - 1, sign_sitel);
				else
					printf("第%d行,第%d列出现词法错误!\n", site_h, site_l);
				site_l++;
				return;
			}
		}
		return;
	}
	if (Is_Digit())
	{
		while (Is_Digit())
		{
			Concat();
			GetChar();
		}
		if (Is_Letter())
		{
			//w_file << "第" << site_h << "行,第" << site_l << "列出现词法错误!\n";
			printf("第%d行,第%d列出现词法错误!\n", site_h, site_l);
			Find_s();
			return;
		}
		if (Judge())
		{
			w_file << str << " integer\n";
		}
		else
		{
			GetChar();
			if (Is_Digit())
			{
				//w_file << "第" << site_h << "行,第" << site_l << "列出现词法错误!\n";
				printf("第%d行,第%d列出现词法错误!\n", site_h, site_l);
				Find_s();
				return;
			}
			else
			{
				w_file << str << " integer\n";
				//w_file << "第" << site_h << "行,第" << site_l << "列出现词法错误!\n";
				printf("第%d行,第%d列出现词法错误!\n", site_h, site_l);
				return;
			}
		}
		return;
	}
	if (ch == '=')
	{
		w_file << ch << " lop\n";
		GetChar();
		return;
	}
	if (ch == '>')
	{
		Concat();
		GetChar();
		if (ch == '=')
		{
			Concat();
			w_file << str << " lop\n";
			GetChar();
			return;
		}
		else
		{
			w_file << str << " lop\n";
			return;
		}
	}
	if (ch == '<')
	{
		Concat();
		GetChar();
		if (ch == '>')
		{
			Concat();
			w_file << str << " lop\n";
			GetChar();
			return;
		}
		if (ch == '=')
		{
			Concat();
			w_file << str << " lop\n";
			GetChar();
			return;
		}
		else
		{
			w_file << str << " lop\n";
			return;
		}
	}
	if (ch == '+')
	{
		w_file << ch << " aop\n";
		GetChar();
		return;
	}
	if (ch == '-')
	{
		w_file << ch << " aop\n";
		GetChar();
		return;
	}
	if (ch == '*')
	{
		w_file << ch << " mop\n";
		GetChar();
		return;
	}
	if (ch == '/')
	{
		w_file << ch << " mop\n";
		GetChar();
		return;
	}
	if (ch == ':')
	{
		Concat();
		GetChar();
		site_l--;
		if (ch == '=')
		{
			site_l++;
			Concat();
			i = Reserve();
			w_file << str << ' ' << "保留字符" << endl;
			GetChar();
			return;
		}
		else
		{
			//w_file << "第" << site_h << "行,第" << site_l << "列出现词法错误!\n";
			printf("第%d行,第%d列出现词法错误!\n", site_h, site_l);
			site_l++;
			return;
		}
	}
	else
	{
		Concat();
		if (i = Reserve())
		{
			w_file << str << ' ' << "保留字符" << endl;
			GetChar();
			return;
		}
		else
		{
			//w_file << "第" << site_h << "行,第" << site_l << "列出现词法错误!\n";
			printf("第%d行,第%d列出现词法错误!\n", site_h, site_l);
			GetChar();
			return;
		}
	}
}
void Make_kd(keyword* kd)
{
	kd[1].kword = "prog";
	kd[2].kword = "program";
	kd[3].kword = "block";
	kd[4].kword = "condecl";
	kd[5].kword = "const";
	kd[6].kword = "id";
	kd[7].kword = "integer";
	kd[8].kword = "vardecl";
	kd[9].kword = "var";
	kd[10].kword = "proc";
	kd[11].kword = "procedure";
	kd[12].kword = "body";
	kd[13].kword = "begin";
	kd[14].kword = "statement";
	kd[15].kword = "end";
	kd[16].kword = "if";
	kd[17].kword = "then";
	kd[18].kword = "else";
	kd[19].kword = "while";
	kd[20].kword = "do";
	kd[21].kword = "call";
	kd[22].kword = "read";
	kd[23].kword = "write";
	kd[24].kword = "lexp";
	kd[25].kword = "odd";
	kd[26].kword = "exp";
	kd[27].kword = "term";
	kd[28].kword = "factor";
	kd[29].kword = "lop";
	kd[30].kword = "aop";
	kd[31].kword = "mop";
	kd[32].kword = "{";
	kd[33].kword = "}";
	kd[34].kword = "[";
	kd[35].kword = "]";
	kd[36].kword = ":=";
	kd[37].kword = ";";
	kd[38].kword = "(";
	kd[39].kword = ")";
}
int main()
{
	Make_kd(Kd);
	file.open("sentence.txt",ios::in);
	if (file.fail())
	{
		printf("file open errors!");
		exit(0);
	}
	w_file.open("word.txt", ios::out);
	if (w_file.fail())
	{
		printf("w_file open errors!");
		exit(0);
	}
	GetChar();
	GetBC();
	while(!file.eof())
	{ 
		Lexical_Analysis();
		str = "";
	}
	file.close();
	w_file.close();
	return 0;
}