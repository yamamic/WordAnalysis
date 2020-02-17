#include<stdio.h>
#include<fstream>
#include<string>
#include<string.h>
#include<malloc.h>
using namespace std;
string str = "";
fstream file;
fstream w_file;
int i(0);//���ڷ��ر����ַ�������
char ch;
int site_h(1), site_l(1);
int sign_sitel;
/*���еĴ�*/
/*�ؼ���:
	program */
struct keyword {
	string kword;
};
keyword Kd[41];
/*typedef struct letterword {
	string word;
	struct letterword* next;
}*LWord,LW;							//������ķ�ʽ���ʴ洢���ļ���*/
void GetChar()//������һ�ַ�
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

void GetBC()//���ch���ַ��Ƿ�Ϊ�ո�,����������GetChar����ֱ��ch��Ϊ��
{
	while (ch == ' ' || ch == '\n')
	{
		GetChar();
	}
}

void Concat()//��ch�е��ַ����ӵ�str֮��
{
	str += ch;
}

bool Is_Letter()//�ж��Ƿ�Ϊ��ĸ
{
	if ('a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z')
	{
		return true;
	}
	return false;
}

bool Is_Digit()//�ж��Ƿ�Ϊ����
{
	if ('0' <= ch && ch <= '9')
	{
		return true;
	}
	return false;
}

int Reserve()//��str�е��ַ������ұ����ֱ�,�����Ǳ������򷵻����ı���,���򷵻�0ֵ.(0���Ǳ����ַ�)
{
	int i(0);
	for (i = 1; i < 41; i++)
	{
		if (Kd[i].kword._Equal(str))
		{
			return i;
		}
	}
	return 0;
}

void Retract()//������ָ����ǰ�ص�һ���ַ�λ��,����ch��Ϊ���ַ�
{
	file.seekg(-1, ios::cur);
	ch = ' ';
}
bool Judge()
{
	if (Is_Letter())
		return true;
	if (ch == ',')
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
	if (ch == ',')
		return true;
	return false;
}

void Find_s()//Ѱ����һ���ո���߻س�
{
	while (ch != ' ' && ch != '\n')
	{
		GetChar();
	}
}
void Lexical_Analysis()//ת������
{
	GetBC();
	if (Is_Letter())//����ĸ��ͷ
	{
		while (Is_Letter() || Is_Digit())//����Ȼ����ĸ,����ѭ��
		{
			Concat();
			GetChar();
		}
		if (Judge() || file.eof())
		{
			i = Reserve();
			if (i)
				w_file << str << " keyword" << endl;
			else
				w_file << str << " id" << endl;
		}
		else
		{
			GetChar();
			site_l--;
			if (Is_Letter())
			{
				if (ch == '\n')
					printf("��%d��,��%d�г��ִʷ�����!\n", site_h - 1, sign_sitel);
				else
					printf("��%d��,��%d�г��ִʷ�����!\n", site_h, site_l);
				site_l++;
				Find_s();
				return;
			}
			else
			{
				i = Reserve();
				if (i)
					w_file << str << " keyword" << endl;
				else
					w_file << str << " id" << endl;
				if (ch == '\n')
					printf("��%d��,��%d�г��ִʷ�����!\n", site_h - 1, sign_sitel);
				else
					printf("��%d��,��%d�г��ִʷ�����!\n", site_h, site_l);
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
			printf("��%d��,��%d�г��ִʷ�����!\n", site_h, site_l);
			Find_s();
			return;
		}
		if (Judge())
		{
			w_file << str << " integer" << endl;
		}
		else
		{
			GetChar();
			if (Is_Digit())
			{
				printf("��%d��,��%d�г��ִʷ�����!\n", site_h, site_l);
				Find_s();
				return;
			}
			else
			{
				w_file << str << " integer" << endl;
				printf("��%d��,��%d�г��ִʷ�����!\n", site_h, site_l);
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
			w_file << str << " lop" << endl;
			GetChar();
			return;
		}
		else
		{
			w_file << str << " lop" << endl;
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
			w_file << str << " lop" << endl;
			return;
		}
		if (ch == '=')
		{
			Concat();
			w_file << str << " lop" << endl;
			GetChar();
			return;
		}
		else
		{
			w_file << str << " lop" << endl;
			return;
		}
	}
	if (ch == '+')
	{
		w_file << ch << " aop" << endl;
		GetChar();
		return;
	}
	if (ch == '-')
	{
		w_file << ch << " aop" << endl;
		GetChar();
		return;
	}
	if (ch == '*')
	{
		w_file << ch << " mop" << endl;
		GetChar();
		return;
	}
	if (ch == '/')
	{
		w_file << ch << " mop" << endl;
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
			w_file << str << " keyword" <<endl;
			GetChar();
			return;
		}
		else
		{
			//w_file << "��" << site_h << "��,��" << site_l << "�г��ִʷ�����!\n";
			printf("��%d��,��%d�г��ִʷ�����!\n", site_h, site_l);
			site_l++;
			return;
		}
	}
	else
	{
		Concat();
		if (i = Reserve())
		{
			w_file << str << " keyword" <<endl;
			GetChar();
			return;
		}
		else
		{
			printf("��%d��,��%d�г��ִʷ�����!\n", site_h, site_l);
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
	kd[40].kword = ",";
}
void wordanalyse_menu()
{
	Make_kd(Kd);
	file.open("sentence.txt", ios::in);
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
	while (!file.eof())
	{
		Lexical_Analysis();
		str = "";
	}
	file.close();
	w_file.close();
}