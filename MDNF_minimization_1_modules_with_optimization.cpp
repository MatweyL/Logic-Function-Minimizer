#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
using namespace std;

struct f
{
	string name;//��� ���������
	string number;//�������� ������ ����������
	char status;//������ - ������������� �� � ��� ���������� ��� ���; ����� ����� ���������, �������� �� ��������� �������
	int rang;
};

string to_string(int n)
{
	int dig;
	char digChar;
	string ans = "";
	if (n != 0)
	{
		while (n != 0)
		{
			dig = n % 10;
			digChar = 48 + dig;
			n /= 10;
			ans = digChar + ans;
		}
	}
	else 
	{
		ans = "0";
	}
	return ans;
}

int getDim(int size)//���������� ���������� ���������� �������
{
	bool flag = false;
	int i = 0, ans = 0;
	while (!flag)
	{
		if (pow(2, i) < size && pow(2, i + 1) >= size)
		{
			flag = true;
			ans = i + 1;
		}
		i++;
	}
	return ans;
}

string getBin(int num, int dim)//���������� �������� ������������� ����� ���������� ����
{
	string ans = "";
	for (int i = 0; i < dim; i ++)
	{
		if (num % 2 == 1)
		{
			ans = '1' + ans;
		}
		else 
		{
			ans = '0' + ans;
		}
		num /= 2;
	}
	return ans;
}

string getNumOfK(string name, int start, int &step)//start - ������ ������ ������ ��������� (���������� � K), step - ��� ��� ����������� � �����
{
	string ans = "";
	int i = 0;//����� ������
	int pos = start + 1;
	while (name[pos] != 'K' && pos < name.size())
	{
		ans += name[pos];
		pos++;
		i++;
	}
	step = i + 1;
	return ans;
}

void printV(vector<string> v)
{
	cout << endl;
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << ' ';
	}
}


void readData(vector<string> &inputV)
{
	string s = "0111";
	cin >> s;
	int dim = getDim(s.size());
	string num;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '1')
		{
			num = getBin(i, dim);
			inputV.push_back(num);
		}
	}
}

int getNumOfOnes(string s)
{
	int ans = 0;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '1')
		{
			ans++;
		}
	}
	return ans;
}

void sortByClasses(vector<string> &v)//��������� �� ������ �� ���������� ������
{
	int dim = v[0].size(), numOfOnes = 0, startPos = 0;
	int elNumOfOnes = 0;
	for (int j = 0; j < dim; j++)
	{
		for (int i = startPos;i < v.size(); i++)
		{
			elNumOfOnes = getNumOfOnes(v[i]);
			if (elNumOfOnes == numOfOnes)
			{
				swap(v[i], v[startPos]);
				startPos++;
			}
		}
		numOfOnes++;
	}
} 

void initializeK(vector<f*> &k, vector<string> inputV)//������� ������ ����������
{
	f* temp;
	for (int i = 0; i < inputV.size(); i++)
	{
		temp = new f;
		temp->number = inputV[i];
		temp->name = "K" + to_string(i);
		temp->status = 'n';
		k.push_back(temp);
	}
}

void printK(vector<f*> k)
{
	cout << endl;
	for (int i = 0; i < k.size(); i++)
	{
		cout << endl << k[i]->name << ' ' << k[i]->number << ' ' << k[i]->status;
	}
}

int getNumberN(vector<f*> k)//���������� ���������� �� �������������� � ������� ����������
{
	int ans = 0;
	for (int i = 0; i < k.size(); i++)
	{
		if (k[i]->status == 'n')
		{
			ans++;
		}
	}
	return ans;
}

void compare(f* f1, f* f2, int &uneqS, int &pos)//���������� ��������� ���� ����������, ������� ����������� ���� ��� ����� ��������� �����
{
	uneqS = 0;
	//cout << endl << "===comparing===";
	for (int i = 0; i < f1->number.size(); i++)
	{
		//cout <<  endl << f1->number[i] << " and " <<  f2->number[i];
		if (f1->number[i] != f2->number[i])
		{
			uneqS++;
			pos = i;
		}
	}
	//cout << endl << " uneqS = " << uneqS;
}

bool checkRepeats(string number, vector<f*> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (number == v[i]->number)
		{
			return false;
		}
	}
	return true;
}

vector<f*> appendNewTable(vector<f*> &v)//��������� ����� �������, ��������� �� ��������� ���������
{
	vector <f*> answer;
	f* temp;
	int uneqS = 0, pos = 0;
	for (int i = 0; i < v.size() - 1; i++)
	{
		for (int j = i + 1; j < v.size(); j++)
		{
			compare(v[i], v[j], uneqS, pos);
			if (uneqS == 1)
			{
				v[i]->status = 'y';
				v[j]->status = 'y';
				temp = new f;
				temp->name = v[i]->name + v[j]->name;
				temp->number = v[i]->number;
				temp->number[pos] = '-';
				temp->status = 'n';
				if (checkRepeats(temp->number, answer))//�������� �� ����������; ���� �� ����������� �������, �� ���������� � ����� �������
				{
					answer.push_back(temp);
				}
			}
		}
	}
	if (answer.size() == 0)
	{
		temp = new f;
		temp->name = "2";
		temp->number = "2";
		temp->status = 'n';
		answer.push_back(temp);
	}
	return answer;
}

bool checkImpName(string name)
{
	bool incr = true;
	int prev = -1, step = 1;
	int curr;
	for (int i = 0; i < name.size(); i += step)
	{
		curr = atoi(getNumOfK(name, i, step).c_str());
		if (curr > prev)
		{
			prev = curr;
		}
		else
		{
			incr = false;
			break;
		}
	}
	return incr;
}
void sortImpName(string &name)
{
	if (!checkImpName(name))
	{
		vector<int> kNumbers;
		int step = 1;
		for (int i = 0; i < name.size(); i += step)//���������� � ������ ������� ���������� ��� ���������� 
		{
			kNumbers.push_back(atoi(getNumOfK(name, i, step).c_str()));
		}
		for (int i = 0; i < kNumbers.size() - 1; i++)// ���������� ������� �� ����������� (���������)
			for (int j = i + 1; j < kNumbers.size(); j++)
				if (kNumbers[i] > kNumbers[j])
					swap(kNumbers[i], kNumbers[j]);
		string newName = "";
		for (int i = 0; i < kNumbers.size(); i++)
		{
			newName = newName + 'K' + to_string(kNumbers[i]);
		}
		name = newName;
	}
}

void appendImpInSum(vector<string> &sum, string name)
{
	//��������� name �� ��������� ������, ��������� �� ����������� ��� ���������� � sum; ���� �� ������������, �� ��������� � ����� �������
	vector<string> nameS;
	int step = 1;
	for (int i = 0; i < name.size(); i += step)//���������� � ������ ���������� ��� ��������� 
	{
		nameS.push_back('K' + getNumOfK(name, i, step));
	}
	cout << endl << "nameS: ";
	printV(nameS);
	if (sum.size() != 0)
	{
		bool existing;
		for (int i = 0; i < nameS.size(); i++)
		{
			existing = false;
			for (int j = 0; j < sum.size(); j++)
			{
				if (nameS[i] == sum[j])
				{
					existing = true;
					break;
				}
			}
			if (!existing)
			{
				sum.push_back(nameS[i]);
			}
		}
	}
	else//���� ������ ����� ����, �� ����������� ��� ���� ������ nameS
	{
		for (int i = 0; i < nameS.size(); i++)
		{
			sum.push_back(nameS[i]);
		}
	}
}

void sortSum(vector<string> &sum)
{
	vector<int> sumI;
	for (int i = 0; i < sum.size(); i++)
	{
		sumI.push_back(atoi((sum[i].erase(0, 1)).c_str()));//�������� � ������������� ������ �������� ������� �����, ��������������� � �����
	}
	//��������� �� ����������� ������������� ������ �����
	for (int i = 0; i < sumI.size() - 1; i++)
		for (int j = i + 1; j < sumI.size(); j++)
			if (sumI[i] > sumI[j])
				swap(sumI[i], sumI[j]);
	//����������� ��������� ������� ����� ��� ��������������� ��������
	for (int i = 0; i < sum.size(); i++)
	{
		sum[i] = 'K' + to_string(sumI[i]);
	}
}

bool kSumInImp(string k, f* imp)//��������� ��������� ������� ���������� ����� � ���������
{
	bool existing = false;
	int step = 1;
	for (int i = 0; i < imp->name.size(); i += step)
	{
		if ('K' + getNumOfK(imp->name, i, step) == k)
		{
			existing = true;
			break;
		}
	}
	return existing;
}

vector<string> delKfromSum(vector<string> sum, f* impI)
{
	int step;
	for (int sI = 0; sI < sum.size(); sI++)//���� �� ���� ����������� �����
	{
		step = 1;
		for (int i = 0; i < impI->name.size(); i += step)//���� �� ���� ����������� ����������
		{
			if ('K' + getNumOfK(impI->name, i, step) == sum[sI])
			{
				sum.erase(sum.begin() + sI);
				sI--;//������������� �������� ��� ���������� ��������� ����� �������
				break;
			}
		}
	}
	return sum;
}

void appendCombination(vector<f*> comb, vector< vector<f*> > &combinations, vector<f*> imp, vector<string> sum, int &size)//����������, �������� (�������� ���� � �������-�������� �������������� ��������� ����� ����������)
{
	if (sum.size() == 0)//���� ������ ������� ����� �������, �� ������� ��������� ����������� ������� �����������
	{
		combinations.push_back(comb);
		if (comb.size() != size)//��������� ��� �������� ������ ��� ���� ����������
		{
			size = comb.size();
		}
	}
	else
	{
		for (int i = 0; i < imp.size(); i++)
		{
			if (kSumInImp(sum[0], imp[i]))//���� � ������� ��������� ������ ������(�������) �������� �����, �� ���������� ���������� (� � ��������� ����� �������� ����� ��� ��� �������� �����������)
			{
				comb.push_back(imp[i]);
				if (comb.size() <= size)//��������� ��� �������� ������ ��� ���� ����������
				{
					appendCombination(comb, combinations, imp, delKfromSum(sum, imp[i]), size);
				}
				comb.pop_back();
			}
		}
	}
}

int getRang(string number)
{
	int ans = 0;
	for (int i = 0; i < number.size(); i++)
	{
		if (number[i] != '-')
		{
			ans++;
		}
	}
	return ans;
}

vector<f*> searchMinComb(vector< vector<f*> > combinations)
{
	vector<int> rangs;
	int tempR;
	for (int i = 0; i < combinations.size(); i++)
	{
		int tempR = 0;
		for (int j = 0; j < combinations[i].size(); j++)
		{
			tempR += combinations[i][j]->rang;
		}
		rangs.push_back(tempR);
	}
	int minR = rangs[0], minRInd = 0;
	for (int i = 1; i < rangs.size(); i++)
	{
		if (rangs[i] < minR)
		{
			minR = rangs[i];
			minRInd = i;
		}
	}
	return combinations[minRInd];
}

string getLogicalFunction(vector<string> ans)
{
	string answer = "";
	for (int i = 0; i < ans.size(); i++)
	{
		for (int k = 0; k < ans[i].size(); k++)
		{
			if (ans[i][k] == '1')
			{
				answer += 'X' + to_string(k + 1);
			}
			else if (ans[i][k] == '0')
			{
				answer += "!X" + to_string(k + 1);
			}
			
		}
		answer += " v ";
	}
	answer.erase(answer.size() - 3, answer.size() - 1);
	return answer;
}

bool checkCoreInAns(string number, vector<string> ans)
{
	bool checking = false;
	for (int i = 0; i < ans.size(); i++)
	{
		if (number == ans[i])
		{
			checking = true;
			break;
		}
	}
	printV(ans);
	return checking;
}

void createImplicants(vector< vector<f*> > &kTables, vector<f*> &imp)
{
	for (int i = kTables.size() - 1; i >= 0; i--)//���������� ����������� �� ������ � ���� ������
	{
		for (int j = kTables[i].size() - 1; j >= 0; j--)
		{
			if (kTables[i][j]->status == 'n')
			{
				kTables[i][j]->rang = getRang(kTables[i][j]->number);
				imp.push_back(kTables[i][j]);
			}
		}
	}
}

void findCoreImp(vector<f*> k, vector<f*> &imp, vector<string> &ans)
{
	string compN;//� ���������� ����� ������������ ����� ���������
	string tempName;//� ���������� ����� ������������ ��� �������� ����������
	int repCount = 0;//���������� ���������� ��������� � ������� �����������; ���� ���������� ����� 1 ����� ����������� ����������� �����, �� ������� ��������� - �������
	int numOfPotentialCore;//����������, � ������� ����� ��������� ����� �������������� �������� ����������
	
	//����� ������� � ��������� ������� ���������� - � ��� � ���������� ������ ���� ���������� (����� �� ��������������) �i 
	cout << endl << "K: ";
	printK(k);
	for (int i = 0; i < k.size(); i++)//���� �� ���� �������� ����������
	{
		compN = k[i]->name;
		compN.erase(0, 1);//� ���� ���������� ����� ������������� � ������� ���������� ����� 'K'
		for (int j = 0; j < imp.size(); j++)//���� �� ���� �����������
		{
			if (repCount > 1)
			{
				break;
			}
			tempName = imp[j]->name;
			int step = 1;
			for (int r = 0; r < tempName.size(); r += step)
			{
				if (compN == getNumOfK(tempName, r, step))
				{
					numOfPotentialCore = j;//���������� ����� ���������� ����
					repCount++;//�� ��������� ��������, ���������� ���������� ��������� �������� ������ ���������
					break;
				}
			}
		}
		cout << endl << "The COUNT of reps of the " << imp[numOfPotentialCore]->name << " is: " << repCount;
		if (repCount == 1 && !checkCoreInAns(imp[numOfPotentialCore]->number, ans))
		{
			imp[numOfPotentialCore]->status = 'c';
			ans.push_back(imp[numOfPotentialCore]->number);
		}
		repCount = 0;
	}
}

void delCoreKFromImp(vector<f*> &imp)
{
	string tempNumOfK;//����� ����������, ������� ���� ��������� �� ��������� � �������
	for (int i = 0; i < imp.size(); i++)
	{
		if (imp[i]->status == 'c')
		{
			int step = 1;
			for (int r = 0; r < imp[i]->name.size(); r += step)//���� ����������� �� ����� (������ � �������) �������� ����������
			{
				tempNumOfK = getNumOfK(imp[i]->name, r, step);
				for (int j = 0; j < imp.size(); j++)
				{
					if (imp[j]->status != 'c')//���� ������� ��������� ���������, �� ����� ��������� ���������� ������������� ���� ����������
					{
						int step2 = 1;
						for (int b = 0; b < imp[j]->name.size(); b += step2)//���� ����������� �� ���������� ����������
						{
							if (getNumOfK(imp[j]->name, b, step2) == tempNumOfK)
							{
								imp[j]->name.erase(b, step2);
								break;
							}
						}
					}
				}
			}
		}
	}
}

void createSum_delCoreImp(vector<f*> imp, vector<string> &sum)
{
	for (int i = 0; i < imp.size(); i++)
	{
		if (imp[i]->status == 'c')
		{
			imp.erase(imp.begin() + i);
			i--;//����� ������������� �����, ������� ��������� ��� �������� ��������
		}
		else
		{
			cout << endl << "IMP NAME BEFORE SORT: " << imp[i]->name;
			sortImpName(imp[i]->name);
			cout << endl << "IMP NAME AFTER SORT: " << imp[i]->name;
			appendImpInSum(sum, imp[i]->name);
		}
	}
}

int getMaxSizeOfComb(vector<f*> imp, vector<string> sum)
{
	int answerSize = 0;
	int size, numOfMaxImp;
	while (sum.size() != 0)
	{
		size = 0;
		for (int i = 0; i < imp.size(); i++)
		{
			if (kSumInImp(sum[0], imp[i]) && imp[i]->name.size() > size)
			{
				size = imp[i]->name.size();
				numOfMaxImp = i;
			}
		}
		sum = delKfromSum(sum, imp[numOfMaxImp]);
		answerSize++;
	}
	return answerSize;
}

/*void getUslessImp(vector<f*> &imp)
{
	vector< vector<int> > impNums;
	for (int i = 0; i < imp.size(); i++)
	{
		
	}
}*/
void findAns(vector<string> &sum, vector<f*> &imp, vector<string> &ans)
{
	if (sum.size() != 0)//���� ������� ���������� �� ��������� ��� �����, �� ���������� ������� ����� ����������� ���������� ������������
	{
		sortSum(sum);//��������� �������� ������� ����� �� �����������
		vector< vector<f*> > combinations;//����� ����� ��������� ���������� �����������, ����������� �����
		vector<f*> comb;
		int size = getMaxSizeOfComb(imp, sum);
		//delUslessImp(imp);
		appendCombination(comb,combinations,imp, sum, size);
		cout << endl << "COMBINATIONS:";
		for (int i = 0; i < combinations.size(); i++)//����� ���������� ����������
		{
			cout << endl << "The combination number " << i;
			printK(combinations[i]);
		}
		comb = searchMinComb(combinations);//� comb ��������� �����������(������) ���������� �� ���� ���������
		for (int i = 0; i < comb.size(); i++)
		{
			ans.push_back(comb[i]->number);
		}
	}
}

string minimaize(vector<f*> k)
{
	vector< vector<f*> > kTables;//������� ����������, ����� ��� ���������� ������� ����������� � ����������� ��������� �������
	kTables.push_back(k);
	int i = 0;
	do
	{
		kTables.push_back(appendNewTable(kTables.back()));
	}
	while (kTables.back().back()->name != "2");//����� ���������� �� ���������, ��������� ������ �� ������ �������� � ������ '2'
	kTables.pop_back();
	for (int i = 0; i < kTables.size(); i++)//����� ���������� ������
	{
		cout << endl << "The table number " << i;
		printK(kTables[i]);
	}
	vector<f*> imp;//����� ����� ��������� ����������
	createImplicants(kTables, imp);
	cout << endl << "Implicants: ";
	printK(imp);
	vector<string> ans;
	findCoreImp(k, imp, ans);
	cout << endl << "The core: ";
	printV(ans);
	cout << endl << "//";
	//������� �� ���� ����������� ������������� ���������
	delCoreKFromImp(imp);
	//���������� �� ������� ����������� � ������� ������� ����������, ����� ������� �����, ��������� ����� �����������
	vector<string> sum;
	createSum_delCoreImp(imp, sum);
	cout << endl << "SUM: ";
	printV(sum);
	cout<< endl << "//";
	cout << endl << "Implicants: ";
	printK(imp);
	cout << endl << "//";
	findAns(sum, imp, ans);	
	string answer = getLogicalFunction(ans);
	return answer;
}

bool funIsConstNullOrOne(vector<string> inputV)
{
	bool ans = false;
	if (inputV.size() == 0 || inputV.size() == pow(2, inputV[0].size()))
	{
		ans = true;
	}
	return ans;
}

string getMinimazedF(vector<string> &inputV)
{
	string answer;
	if (!funIsConstNullOrOne(inputV))
	{
		sortByClasses(inputV);
		printV(inputV);
		vector<f*> k;
		initializeK(k, inputV);
		printK(k);
		answer = minimaize(k);
	}
	else
	{
		if (inputV.size() == 0)
		{
			answer = '0';
		}
		else
		{
			answer = '1';
		}
		
	}
	return answer;
}

int main()
{
	vector<string> inputV;
	string answer;
	readData(inputV);
	printV(inputV);
	answer = getMinimazedF(inputV);
	cout << endl << "f = " << answer;
}
