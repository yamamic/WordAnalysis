#include<stdio.h>
#include<fstream>
#include<string>
using namespace std;
string str2;//当前语句
string ch_first,ch_next;//当前词
fstream read_file;
int site(0);
bool jd(0);//判断变量
bool block_check();
bool factor_check();
bool term_check();
bool exp_check();
bool lexp_check();
bool statement_check();
bool body_check();
bool Judge_next();
bool const_check();
bool condecl_check();
bool vardecl_check();
bool proc_check();
bool block_check();

bool factor_check()
{
	if (ch_next == "id")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		return 1;
	}
	else if (ch_next == "integer")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		return 1;
	}
	else if (ch_first == "(")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		exp_check();
		return 1;
	}
	else
	{
		printf("语法错误");
		return 1;
	}
}
bool term_check()
{
	string sign;
	factor_check();
	sign = ch_next;
	if(ch_next == "mop")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		while (sign == "mop")
		{
			factor_check();
			read_file >> ch_first;
			read_file >> ch_next;
			sign = ch_next;
		}
	}
	return 1;
}
bool exp_check()
{
	if (ch_first == "+")
	{
		read_file >> ch_first;
		read_file >> ch_next;
	}
	else if (ch_first == "-")
	{
		read_file >> ch_first;
		read_file >> ch_next;
	}
	else
	{
		term_check();
		while (ch_next == "aop")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			term_check();
		}
	}
	return 1;
}
bool lexp_check()
{
	if (ch_first == "odd")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		exp_check();
	}
	else
	{
		exp_check();
		while (ch_next == "lop")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			exp_check();
		}
	}
	return 1;
}
bool statement_check()
{
	if (ch_first == "if")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		lexp_check();
		if (ch_first == "then")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			statement_check();
			if (ch_first == "else")
			{
				read_file >> ch_first;
				read_file >> ch_next;
				statement_check();
			}
			else return 1;
		}
		else
		{
			printf("语法错误\n");
			return 1;
		}

	}
	if (ch_first == "while")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		lexp_check();
		if (ch_first == "do")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			statement_check();
		}
		else
		{
			printf("第%d处语法错误\n",site);
			return 1;
		}
	}
	if (ch_first == "call")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		site++;
		if (ch_next == "id")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			site++;
			if (ch_first == "(")
			{
				read_file >> ch_first;
				read_file >> ch_next;
				site++;
				while (ch_first != ")")
				{
					exp_check();
					if (Judge_next())
					{
						printf("语法错误");
						return 0;
					}
						
				}
			}
			else {
				printf("语法错误");
				return 1;
			}
		}
		else
		{
			printf("语法错误");
			return 1;
		}
	}
	if (ch_first == "begin")
		body_check();
	if (ch_first == "read")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		site++;
		if (ch_first == "(")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			site++;
			while (ch_first != ")")
			{
				if (ch_next == "id")
				{
					read_file >> ch_first;
					read_file >> ch_next;
					site++;
					if (ch_first == ",")
						continue;
					else
						printf("缺少', '\n");
				}
				if (Judge_next())
				{
					printf("语法错误\n");
					return 0;
				}
			}
		}

		if (ch_next == "id")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			if (ch_first == ":=")
			{
				read_file >> ch_first;
				read_file >> ch_next;
				exp_check();
			}
			else
			{
				printf("应为':='");
				return 1;
			}
		}
		else
		{
			printf("语法错误\n");
			return 1;
		}
	}
	if (ch_first == "write")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		if (ch_first == "(")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			exp_check();
			while (ch_first!=")")
			{
				if (ch_first == ",")
				{
					read_file >> ch_first;
					read_file >> ch_next;
					exp_check();
				}
				if (Judge_next())
				{
					printf("语法错误");
					return 1;
				}
				read_file >> ch_first;
				read_file >> ch_next;
			}
		}
		else
		{
			printf("语法错误");
			return 1;
		}
	}
	if (ch_next == "id")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		if (ch_first == ":=")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			exp_check();
		}
		else
		{
			printf("应为':='");
			return 1;
		}
	}
}
bool body_check()
{
	if (ch_first != "begin")
	{
		printf("缺少begin");
	}
	while (ch_first != "end")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		if (ch_first == "begin")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			statement_check();
		}
		statement_check();
	}
	return 1;
}
bool Judge_next()
{
	if (ch_first == "const")
		return true;
	if (ch_first == "var")
		return true;
	if (ch_first == "procedure")
		return true;
	if (ch_first == "begin")
		return true;
	if (ch_first == "if")
		return true;
	if (ch_first == "while")
		return true;
	if (ch_first == "call")
		return true;
	if (ch_first == "read")
		return true;
	if (ch_first == "write")
		return true;
	return false;
}
bool const_check()//常数检查
{
	if (ch_next == "id")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		if (ch_first == ":=")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			if (ch_first == "integer")
				return 1;
			else
			{
				printf(":=右侧应为常数");
				return 0;
			}
		}
		else
		{
			printf("缺少:=");
			return 0;
		}
	}
	else
	{
		printf("应为变量");
		return 0;
	}
}
bool condecl_check()
{
	if (ch_first == "const")
	{
		const_check();
		read_file >> ch_first;
		read_file >> ch_next;
		while (ch_first != ";")
		{
			if (Judge_next())
			{
				printf("缺少';'\n");
				return 0;
			}
			if (ch_first == ",")
			{
				read_file >> ch_first;
				read_file >> ch_next;
				const_check();
			}
			else if(ch_next=="id")
			{
				printf("缺少','\n");
				read_file >> ch_first;
				read_file >> ch_next;
				const_check();
			}
			read_file >> ch_first;
			read_file >> ch_next;
		}
		return 1;
	}
}

bool vardecl_check()
{
	read_file >> ch_first;
	read_file >> ch_next;
	if (ch_next == "id")
	{
		read_file >> ch_first;
		read_file >> ch_next;
	}
	else
		printf("缺少id");
	while (ch_first != ";")
	{
		if (ch_first == ",")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			if (ch_next == "id")
			{
				read_file >> ch_first;
				read_file >> ch_next;
				continue;
			}
				
			else
			{
				printf("','后应为id");

				if(Judge_next())
					return 0;
			}
		}
		if (ch_next == "id")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			printf("缺少','");
			continue;
		}
		if (Judge_next())
			return 0;
	}
	read_file >> ch_first;
	read_file >> ch_next;
	return 1;
}

bool proc_check()
{
	read_file >> ch_first;
	read_file >> ch_next;
	if (ch_next == "id")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		while (ch_first != "(" )
		{
			if (ch_first == ";")
				break;
			printf("缺少左括号\n");
			if (Judge_next())
				return 0;
			read_file >> ch_first;
			read_file >> ch_next;
		}
		if (ch_first == "(")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			if (ch_next == "id")
			{
				read_file >> ch_first;
				read_file >> ch_next;
				while (ch_first != ")")
				{
					if (ch_first == ";")
						break;
					if (ch_first == ",")
					{
						read_file >> ch_first;
						read_file >> ch_next;
						if (ch_next == "id")
							continue;
					}
					else {
						printf("缺少','\n");
					}
					read_file >> ch_first;
					read_file >> ch_next;
					if (Judge_next())
						return 0;
				}

			}
			if (ch_first == ")")
			{
				read_file >> ch_first;
				read_file >> ch_next;
				if (ch_first == ";")
				{
					read_file >> ch_first;
					read_file >> ch_next;
					block_check();
					read_file >> ch_first;
					read_file >> ch_next;
					if (ch_first == ";")
					{
						proc_check();
					}
				}
				else
				{
					printf("缺少';'");
					return 0;
				}
			}
		}
		
	}
	else
	{
		printf("语法错误");
		return 1;
	}
	return 1;
}

bool block_check()
{
	int condecl_num(0), vardecl_num(0), proc_num(0);
	while (jd == 0)
	{
		if (ch_first == "const")
		{
			jd = condecl_check();
			condecl_num++;
			if (condecl_num > 1)
				printf("多重condecl");
		}
		if (ch_first == "var")
		{
			jd = vardecl_check();
			vardecl_num++;
			if (vardecl_num > 1)
				printf("多重vardecl");
		}
		if (ch_first == "procedure")
		{
			jd = proc_check();
			proc_num++;
			if (proc_num > 1)
				printf("多重proc");
		}
		else
		{
			body_check();
			jd = 1;
		}
	}
	return 1;
}
bool prog()
{
	read_file >> ch_first;
	read_file >> ch_next;
	if (ch_next == "id")
	{
		read_file >> ch_first;
		read_file >> ch_next;
		if (ch_first == ";")
		{
			read_file >> ch_first;
			read_file >> ch_next;
			block_check();
		}
	}
	return 1;
}
void grammar_analyse()
{
	if (ch_first == "program")
	{
		prog();
	}
}
void grammaranlyse_menu()
{
	read_file.open("word.txt", ios::in);
	if (read_file.fail())
	{
		printf("open file error!");
		exit(0);
	}
	read_file >> ch_first;
	read_file >> ch_next;
	while (!read_file.eof())
	{
		if (ch_next == "id")
			const_check();
		if (ch_first == "var")
			vardecl_check();
		if (ch_first == "procedure")
			proc_check();
		read_file >> ch_first;
		read_file >> ch_next;
	}
}