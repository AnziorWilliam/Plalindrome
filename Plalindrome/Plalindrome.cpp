#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

//�ᳬʱ�����Ż�
#pragma region brute�ⷨ
bool IsPlalindrome(string Detectstr);
void LongestPlalindrome(string Inputstr, string& LST_PLD, int& lens);
#pragma endregion
//25ms 534kb
#pragma region ���ĵ���ɢ�ⷨ
int SpreadCenter(int startPos, int endPos, string iptStr);
int LST_plalindrome(string iptstr);
#pragma endregion
//260ms 504kb
#pragma region ������Ӵ��ⷨ
void lstpld(string rawipt);
void LstSubstr(string& rawipt);
#pragma endregion
//755ms 24068kb ��������
#pragma region ��̬�滮�ⷨ
void TranStatus(string &Raput);
#pragma endregion
//
#pragma region Manacher�ⷨ
void AppendStr(string& InputStr);

int  Manacher_plalindrome(string InputStr);
#pragma endregion

int main()
{
	//string RetPlalindrome = "";//���ػ���
	int PLD_maxlen = 0;//����ĳ���
	string inst;

	while (getline(cin, inst))
	{
		//***brute �ⷨ***
		//LongestPlalindrome(inst, RetPlalindrome,PLD_maxlen);
		//cout << RetPlalindrome << endl;

		//������ɢ��
		//PLD_maxlen = LST_plalindrome(inst);

		//������Ӵ�
		//LstSubstr(inst);
		//PLD_maxlen = inst.length();

		//��̬�滮
		//TranStatus(inst);
		//PLD_maxlen = inst.length();

		//Manacher
		if (inst == "")
		{
			cout << endl;
			continue;
		}
		string Manacher = inst;
		AppendStr(Manacher);
		PLD_maxlen = Manacher_plalindrome(Manacher);
		cout << PLD_maxlen << endl;
		PLD_maxlen = 0;
		//RetPlalindrome = "";
	}
	return 0;
}

#pragma region brute �ⷨ
bool IsPlalindrome(string Detectstr)
{
	string RDt_str = Detectstr;
	reverse(RDt_str.begin(), RDt_str.end());

	return RDt_str != Detectstr ? false : true;
}

void LongestPlalindrome(string Inputstr, string& LST_PLD, int& lens)
{
	string RetPlalindrome = "";//���ػ���
	int PLD_maxlen = 0;//����ĳ���

	int len = Inputstr.length();

	string temp = "";

	for (int i = 0; i < len; i++)
	{
		for (int j = i + 1; j <= len; j++)
		{
			temp = Inputstr.substr(i, j);
			if (IsPlalindrome(temp) && temp.length() > PLD_maxlen)//�ǻ����һ��ĳ��ȴ�����֪��Ļ��ĳ�
			{
				PLD_maxlen = temp.length() > PLD_maxlen ? temp.length() : PLD_maxlen;
				RetPlalindrome = temp;
			}
			temp = "";
		}
	}
	LST_PLD = RetPlalindrome;
	lens = PLD_maxlen;
}
#pragma endregion

#pragma region ���ĵ���ɢ�ⷨ
int SpreadCenter(int startPos, int endPos, string iptStr)
{
	int plalindrom_len = 0;
	int len = iptStr.length();
	int Lchild = startPos;
	int Rchild = endPos;
	if (iptStr[startPos] != iptStr[endPos])
	{
		return plalindrom_len;
	}
	if (startPos == endPos)
	{
		plalindrom_len = 1;
	}
	else
	{
		plalindrom_len = 2;
	}
	while (Lchild >= 0 && Rchild < len && iptStr[Lchild] == iptStr[Rchild])//��������
	{
		plalindrom_len += 2;
		Lchild--;
		Rchild++;
	}
	plalindrom_len -= 2;
	return plalindrom_len;
}
int LST_plalindrome(string iptstr)
{
	int plalindrome_mx = 0;
	if (iptstr == "")
	{
		return plalindrome_mx;
	}
	int lens = iptstr.length();

	for (int i = 0; i < lens; i++)
	{
		int SigLen = SpreadCenter(i, i, iptstr);
		int DooLen = SpreadCenter(i, i + 1, iptstr);
		int temps = SigLen > DooLen ? SigLen : DooLen;
		plalindrome_mx = plalindrome_mx > temps ? plalindrome_mx : temps;
	}
	return plalindrome_mx;
}
#pragma endregion

#pragma region ������Ӵ��ⷨ
void LstSubstr(string& rawipt)
{
	string RVTstr = rawipt;
	string MirIpt = rawipt;
	string retTp;

	int mxlen = 0;

	if (rawipt.length() == 1)
	{
		return;
	}
	reverse(RVTstr.begin(), RVTstr.end());
	if (RVTstr == MirIpt)
	{
		return;
	}

	int len = MirIpt.length();
	for (int i = 0; i < len; i++)
	{
		string temp;
		for (int j = i; j < len; j++)
		{
			temp += MirIpt[j];
			if (mxlen > temp.length())
			{
				continue;
			}

			else if (RVTstr.find(temp) != RVTstr.npos)//���ڸ��Ӵ�
			{
				retTp = temp;
				reverse(retTp.begin(), retTp.end());

				if (retTp == temp)
				{
					mxlen = temp.length();
					rawipt = temp;
				}
			}
			else
				break;
		}
		temp = "";
	}
}
#pragma endregion

#pragma region ��̬�滮�ⷨ
void TranStatus(string &Raput)
{
	string tpRa = Raput;
	int Ralen = Raput.length();
	if (Raput.empty() || Ralen < 2)//�մ����ߵ����ַ�
	{
		return;
	}

	int Lst = 0;
	//int Rst = 0;
	int mxLen = 1;

	/*bool **dp= new bool *[Ralen];
	for (int i = 0; i < Ralen; i++)
	{
		dp[i] = new bool[Ralen];
	}*/

	vector<vector<int>>dp(Ralen, vector<int>(Ralen));

	for (int i = 0; i < Ralen; i++)
	{
		dp[i][i] = 1;
		if (i < Ralen - 1 && tpRa[i] == tpRa[i + 1])
		{
			dp[i][i+1] = 1;
			mxLen = 2;
			Lst = i;
		}
	}


	for (auto Right = 3; Right <= Ralen ; Right++) //�ұ߽߱�
	{
		for (auto Left = 0; Left + Right < Ralen + 1; Left++)//��߽߱�
		{
			int j = Left + Right - 1;
			if (tpRa[Left] == tpRa[j]&&dp[Left+1][j-1] == 1)
			{
				dp[Left][j] = 1;
				Lst = Left;
				mxLen = Right;
			}
		}
	}
	Raput = tpRa.substr(Lst, mxLen);
}
#pragma endregion

#pragma region Manacher�ⷨ
void AppendStr(string& InputStr)
{
	int len = InputStr.length();
	string ManacherStr ="";
	for (auto i : InputStr)
	{
		ManacherStr.append("*");
		ManacherStr.append(string(1,i));
	}
	ManacherStr.append("*");
	InputStr = ManacherStr;
}
int  Manacher_plalindrome(string InputStr)
{
	//�ַ�����ʼ��
	int R = 0;
	int C = 0;

	int mx_Manacher = 0;
	int* p = new int[InputStr.length()];
	//memset(p, 1, InputStr.length());
	if (InputStr == "" || InputStr.length() < 2)
	{
		return 1;
	}

	string s = InputStr;
	int go;
	for (int i = 0; i < InputStr.length(); i++)
	{
		p[i] = R > i ? min(R - i, p[2 * C - i]) : 1;
		//��ǰλ������֪�������ұ߽����߻����ұߣ�

		//���ұ�����ƥ�䣬��һ����뾶������Ϊ1

		//��������������ж�i�����c�ĶԳƵ�Ļ��İ뾶��r-i�Ĺ�ϵ;

		//����û��İ뾶С��r-i˵��i��Ļ��İ뾶Ҳ�ض�С��r-i�����ڻ��ĶԳ�����p[i] = p[2c-i]

		/*����û��İ뾶���ڵ���r-i�����ڻ��ĶԳ��Թ��򣺴���r-i������£��ض���p[i]=r-i
		������Ϊ���p[i]>r-i�Ļ���ôi��Ļ��İ뾶�߽�y�ض�����r��y����i�ĶԳƵ�Ϊy'��y'����c�ĶԳƵ�Ϊx��x����j�ĶԳƵ�Ϊx'
		�����Ƶ���x'�ض�Ҳ��r����c�ĶԳƵ�l֮�⣬ͬ����ڻ����ڲ��ĶԳ��Կ���֪���⼸�����ַ��ض�����ȣ���ôԭ�е�rΪ���ұ߽����㲻����,
		��ʱp[i]=r-i ֻ��ȡ����*/

		/*���ȡ���ǵ����������ôj�����߽�+1������j���ұ߽�+1����i����ұ߽߱�����֪�����ұ߽�r֮�⣬���Զ����ڱ߽�֮��ĵ����豩��ƥ���ж�
		��iΪ�Գ����ĵĻ����ܷ�������������ţ����������i�Ļ��İ뾶ҲӦ����r-iΪ��㳢����������  ---��p[i]>=r-i*/

		while (i+p[i]< InputStr.length()&&i-p[i]>=0)//���ұ߽�
		{
			if (s[i + p[i]] == s[i - p[i]])//��������
			{
				p[i]++;
			}
			else//����һ�β�ƥ�����˳�
			{
				break;
			}
		}

		//���� R,C��ֵ �����б�Ҫ
		if (i + p[i] > R)
		{
			R = i + p[i];
			C = i;
		}
		mx_Manacher = max(mx_Manacher, p[i]);
	}
	delete[]p;
	return mx_Manacher - 1;
}
#pragma endregion