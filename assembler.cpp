#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

static int last_val = 0;
static int last_label = 0;

string removeSpaces(string str)  
{ 
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    return str; 
}

string removeNewLines(string str)  
{ 
    str.erase(remove(str.begin(), str.end(), '\r'), str.end()); 
    return str; 
}

string removeExtension(string str)
{
	int i = str.find(".asm");
	if(i>=0)
		str.erase(i, str.size()); 
    return str;
}

string removeComments(string str)  
{ 
    int i = str.find("//");
	if(i>=0)
		str.erase(i, str.size()); 
    return str; 
}

void decToBinary_16(int n, char* arr) 
{  
	//char str[16];
    for (int i = 15; i >= 0; i--) { 
        int k = n >> i; 
        if (k & 1) 
            arr[15-i] = '1'; 
        else
            arr[15-i] = '0'; 
    }
    arr[16] = '\0';
    //cout<<arr<<endl;
    //return str; 
}

void empty(char* arr)
{
	for(int i = 15; i >= 0; i--) {
		arr[i] = '0';
	}
	arr[16] = '\0';
}

void get7digitCode(char* arr, string str)
{
	//cout<<"Value being passed: "<<str<<endl;
	//cout<<"Binary being passed: "<<arr<<endl;
	if(str.compare("0") == 0)
	{
		arr[3] = '0';
		arr[4] = '1';
		arr[5] = '0';
		arr[6] = '1';
		arr[7] = '0';
		arr[8] = '1';
		arr[9] = '0';
	}
	else if(str.compare("1") == 0)
	{
		arr[3] = '0';
		arr[4] = '1';
		arr[5] = '1';
		arr[6] = '1';
		arr[7] = '1';
		arr[8] = '1';
		arr[9] = '1';
	}
	else if(str.compare("-1") == 0)
	{
		arr[3] = '0';
		arr[4] = '1';
		arr[5] = '1';
		arr[6] = '1';
		arr[7] = '0';
		arr[8] = '1';
		arr[9] = '0';
	}
	else if(str.compare("D") == 0)
	{
		arr[3] = '0';
		arr[4] = '0';
		arr[5] = '0';
		arr[6] = '1';
		arr[7] = '1';
		arr[8] = '0';
		arr[9] = '0';
	}
	else if(str.compare("A") == 0)
	{
		//cout<<"Check Successful\n";
		arr[3] = '0';
		arr[4] = '1';
		arr[5] = '1';
		arr[6] = '0';
		arr[7] = '0';
		arr[8] = '0';
		arr[9] = '0';
	}
	else if(str.compare("M") == 0)
	{
		arr[3] = '1';
		arr[4] = '1';
		arr[5] = '1';
		arr[6] = '0';
		arr[7] = '0';
		arr[8] = '0';
		arr[9] = '0';
	}
	else if(str.compare("!D") == 0)
	{
		arr[3] = '0';
		arr[4] = '0';
		arr[5] = '0';
		arr[6] = '1';
		arr[7] = '1';
		arr[8] = '0';
		arr[9] = '1';
	}
	else if(str.compare("!A") == 0)
	{
		arr[3] = '0';
		arr[4] = '1';
		arr[5] = '1';
		arr[6] = '0';
		arr[7] = '0';
		arr[8] = '0';
		arr[9] = '1';
	}
	else if(str.compare("!M") == 0)
	{
		arr[3] = '1';
		arr[4] = '1';
		arr[5] = '1';
		arr[6] = '0';
		arr[7] = '0';
		arr[8] = '0';
		arr[9] = '1';
	}
	else if(str.compare("-D") == 0)
	{
		arr[3] = '0';
		arr[4] = '0';
		arr[5] = '0';
		arr[6] = '1';
		arr[7] = '1';
		arr[8] = '1';
		arr[9] = '1';
	}
	else if(str.compare("-A") == 0)
	{
		arr[3] = '0';
		arr[4] = '1';
		arr[5] = '1';
		arr[6] = '0';
		arr[7] = '0';
		arr[8] = '1';
		arr[9] = '1';
	}
	else if(str.compare("-M") == 0)
	{
		arr[3] = '1';
		arr[4] = '1';
		arr[5] = '1';
		arr[6] = '0';
		arr[7] = '0';
		arr[8] = '1';
		arr[9] = '1';
	}
	else if(str.compare("D+1") == 0)
	{
		arr[3] = '0';
		arr[4] = '0';
		arr[5] = '1';
		arr[6] = '1';
		arr[7] = '1';
		arr[8] = '1';
		arr[9] = '1';
	}
	else if(str.compare("A+1") == 0)
	{
		arr[3] = '0';
		arr[4] = '1';
		arr[5] = '1';
		arr[6] = '0';
		arr[7] = '1';
		arr[8] = '1';
		arr[9] = '1';
	}
	else if(str.compare("M+1") == 0)
	{
		arr[3] = '1';
		arr[4] = '1';
		arr[5] = '1';
		arr[6] = '0';
		arr[7] = '1';
		arr[8] = '1';
		arr[9] = '1';
	}
	else if(str.compare("D-1") == 0)
	{
		arr[3] = '0';
		arr[4] = '0';
		arr[5] = '0';
		arr[6] = '1';
		arr[7] = '1';
		arr[8] = '1';
		arr[9] = '0';
	}
	else if(str.compare("A-1") == 0)
	{
		arr[3] = '0';
		arr[4] = '1';
		arr[5] = '1';
		arr[6] = '0';
		arr[7] = '0';
		arr[8] = '1';
		arr[9] = '0';
	}
	else if(str.compare("M-1") == 0)
	{
		arr[3] = '1';
		arr[4] = '1';
		arr[5] = '1';
		arr[6] = '0';
		arr[7] = '0';
		arr[8] = '1';
		arr[9] = '0';
	}
	else if(str.compare("D+A") == 0)
	{
		arr[3] = '0';
		arr[4] = '0';
		arr[5] = '0';
		arr[6] = '0';
		arr[7] = '0';
		arr[8] = '1';
		arr[9] = '0';
	}
	else if(str.compare("D+M") == 0)
	{
		arr[3] = '1';
		arr[4] = '0';
		arr[5] = '0';
		arr[6] = '0';
		arr[7] = '0';
		arr[8] = '1';
		arr[9] = '0';
	}
	else if(str.compare("D-A") == 0)
	{
		arr[3] = '0';
		arr[4] = '0';
		arr[5] = '1';
		arr[6] = '0';
		arr[7] = '0';
		arr[8] = '1';
		arr[9] = '1';
	}
	else if(str.compare("D-M") == 0)
	{
		arr[3] = '1';
		arr[4] = '0';
		arr[5] = '1';
		arr[6] = '0';
		arr[7] = '0';
		arr[8] = '1';
		arr[9] = '1';
	}
	else if(str.compare("A-D") == 0)
	{
		arr[3] = '0';
		arr[4] = '0';
		arr[5] = '0';
		arr[6] = '0';
		arr[7] = '1';
		arr[8] = '1';
		arr[9] = '1';
	}
	else if(str.compare("M-D") == 0)
	{
		arr[3] = '1';
		arr[4] = '0';
		arr[5] = '0';
		arr[6] = '0';
		arr[7] = '1';
		arr[8] = '1';
		arr[9] = '1';
	}
	else if(str.compare("D&A") == 0)
	{
		arr[3] = '0';
		arr[4] = '0';
		arr[5] = '0';
		arr[6] = '0';
		arr[7] = '0';
		arr[8] = '0';
		arr[9] = '0';
	}
	else if(str.compare("D&M") == 0)
	{
		arr[3] = '1';
		arr[4] = '0';
		arr[5] = '0';
		arr[6] = '0';
		arr[7] = '0';
		arr[8] = '0';
		arr[9] = '0';
	}
	else if(str.compare("D|A") == 0)
	{
		arr[3] = '0';
		arr[4] = '0';
		arr[5] = '1';
		arr[6] = '0';
		arr[7] = '1';
		arr[8] = '0';
		arr[9] = '1';
	}
	else if(str.compare("D|M") == 0)
	{
		arr[3] = '1';
		arr[4] = '0';
		arr[5] = '1';
		arr[6] = '0';
		arr[7] = '1';
		arr[8] = '0';
		arr[9] = '1';
	}
	//cout<<"Value being returned: "<<arr<<endl;
}

void getDest(char* arr, string str)
{
	if(str.compare("M") == 0)
	{
		arr[10] = '0';
		arr[11] = '0';
		arr[12] = '1';
	}
	else if(str.compare("D") == 0)
	{
		arr[10] = '0';
		arr[11] = '1';
		arr[12] = '0';
	}
	else if(str.compare("MD") == 0)
	{
		arr[10] = '0';
		arr[11] = '1';
		arr[12] = '1';
	}
	else if(str.compare("A") == 0)
	{
		arr[10] = '1';
		arr[11] = '0';
		arr[12] = '0';
	}
	else if(str.compare("AM") == 0)
	{
		arr[10] = '1';
		arr[11] = '0';
		arr[12] = '1';
	}
	else if(str.compare("AD") == 0)
	{
		arr[10] = '1';
		arr[11] = '1';
		arr[12] = '0';
	}
	else if(str.compare("AMD") == 0)
	{
		arr[10] = '1';
		arr[11] = '1';
		arr[12] = '1';
	}
}

void getJump(char* arr, string str)
{
	if(str.compare("JGT") == 0)
	{
		arr[13] = '0';
		arr[14] = '0';
		arr[15] = '1';
	}
	else if(str.compare("JEQ") == 0)
	{
		arr[13] = '0';
		arr[14] = '1';
		arr[15] = '0';
	}
	else if(str.compare("JGE") == 0)
	{
		arr[13] = '0';
		arr[14] = '1';
		arr[15] = '1';
	}
	else if(str.compare("JLT") == 0)
	{
		arr[13] = '1';
		arr[14] = '0';
		arr[15] = '0';
	}
	else if(str.compare("JNE") == 0)
	{
		arr[13] = '1';
		arr[14] = '0';
		arr[15] = '1';
	}
	else if(str.compare("JLE") == 0)
	{
		arr[13] = '1';
		arr[14] = '1';
		arr[15] = '0';
	}
	else if(str.compare("JMP") == 0)
	{
		arr[13] = '1';
		arr[14] = '1';
		arr[15] = '1';
	}
}

void init(string* table_names, int* table_values)
{
	table_names[0] = "R0";
	table_values[0] = 0;
	table_names[1] = "R1";
	table_values[1] = 1;
	table_names[2] = "R2";
	table_values[2] = 2;
	table_names[3] = "R3";
	table_values[3] = 3;
	table_names[4] = "R4";
	table_values[4] = 4;
	table_names[5] = "R5";
	table_values[5] = 5;
	table_names[6] = "R6";
	table_values[6] = 6;
	table_names[7] = "R7";
	table_values[7] = 7;
	table_names[8] = "R8";
	table_values[8] = 8;
	table_names[9] = "R9";
	table_values[9] = 9;
	table_names[10] = "R10";
	table_values[10] = 10;
	table_names[11] = "R11";
	table_values[11] = 11;
	table_names[12] = "R12";
	table_values[12] = 12;
	table_names[13] = "R13";
	table_values[13] = 13;
	table_names[14] = "R14";
	table_values[14] = 14;
	table_names[15] = "R15";
	table_values[15] = 15;
	table_names[16] = "SCREEN";
	table_values[16] = 16384;
	table_names[17] = "KBD";
	table_values[17] = 24576;
	table_names[18] = "SP";
	table_values[18] = 0;
	table_names[19] = "LCL";
	table_values[19] = 1;
	table_names[20] = "ARG";
	table_values[20] = 2;
	table_names[21] = "THIS";
	table_values[21] = 3;
	table_names[22] = "THAT";
	table_values[22] = 4;
	last_val = 22;
	last_label = 15;
}

int return_val(string table[8192], int labels[8192], string str)
{
	int val = -1;
	for(int i = 0; i <= last_val; i++)
	{
		if(table[i].compare(str)==0)
		{
			val = labels[i];
			break;
		}
	}
	return val;
}

void add_new(string table[8192], int labels[8192], string str, int val)
{
	last_val++;
	table[last_val] = str;
	labels[last_val] = val;
}

void display(string table[8192], int labels[8192])
{
	int i = 0;
	for(i = 0; i<=last_val; i++)
	{
		cout<<table[i]<<"\t"<<labels[i]<<endl;
	}
}

bool isNumber(string s) 
{ 
    for (int i = 0; i < s.length(); i++) 
        if (isdigit(s[i]) == false) 
            return false; 
    return true; 
}

void assign(string table[8192], int labels[8192], string str)
{
	last_val++;
	last_label++;
	table[last_val] = str;
	labels[last_val] = last_label;
}

int main()
{
	string file_name, str, line, binary;
	string symbol_table[8192];
	int labels[8192];
	init(symbol_table, labels);
	int i = 0, counter = 0;
	char binary_val[16];
	ifstream f_in;
	ofstream f_out;
	int binary_16;
	cout<<"Enter File Name:"<<endl;
	cin>>str;
	cout<<"File Name Entered: "<<str<<endl;
	f_in.open(str);
	if(f_in)
		cout<<"File Opened Sucessfully"<<endl;
	else if(!f_in){
		cout<<"File opening failed"<<endl;
		return 0;
	}
	file_name = removeExtension(str);
	file_name.append(".hack");
	f_out.open(file_name);
	while(f_in){
		getline(f_in, line);
		line = removeSpaces(line);
		line = removeComments(line);
		line = removeNewLines(line);
		if(line.empty())
			continue;
		cout<<line<<endl;
		if(line[0] == '(' && line[line.size()-1] == ')')
		{
			string token1 = line.substr(1, line.size()-2);
			//cout<<token1<<endl;
			int index = return_val(symbol_table, labels, token1);
			if(index<0)
				add_new(symbol_table, labels, token1, counter);
		}
		else
			counter++;
	}
	f_in.close();
	f_in.open(str);
	while(f_in){
		getline(f_in, line);
		line = removeSpaces(line);
		line = removeComments(line);
		line = removeNewLines(line);
		if(line.empty()||(line[0] == '(' && line[line.size()-1] == ')'))
			continue;
		cout<<line<<endl;
		binary = "";
		empty(binary_val);
		if(line[0] == '@')
		{
			binary = line.substr(1, line.size());
			bool res = isNumber(binary);
			if(res == true)
				binary_16 = stoi(binary);
			else
			{
				int val = return_val(symbol_table, labels, binary);
				if(val < 0){
					assign(symbol_table, labels, binary);
					val = return_val(symbol_table, labels, binary);
				}
				binary_16 = val;
			}
			decToBinary_16(binary_16, binary_val);
			binary_val[0] = '0';
			cout<<binary_val<<endl;
		}
		else
		{
			binary_val[0] = '1';
			binary_val[1] = '1';
			binary_val[2] = '1';
			int index = line.find(";");
			//cout<<"; found at: "<<index<<endl;
			if(index<0)
			{
				binary_val[15] = '0';
				binary_val[14] = '0';
				binary_val[13] = '0';
				index = line.find("=");
				//cout<<"= found at: "<<index<<endl;
				if(index<0)
				{
					binary_val[12] = '0';
					binary_val[11] = '0';
					binary_val[10] = '0';
					get7digitCode(binary_val, line);
				}
				else
				{
					string token1 = line.substr(0,index);
					string token2 = line.substr(index+1, line.size());

					//cout<<"Token 1: "<<token1<<endl;
					//cout<<"Token 2: "<<token2<<endl;
					//cout<<"Token2 is:"<<token2<<"Test";
					//cout<<"Length of token2 is: "<<token2.size()<<endl;
					get7digitCode(binary_val, token2);
					getDest(binary_val, token1);
				}
			}
			else
			{
				string token1 = line.substr(index+1, line.size());
				string token2 = line.substr(0, index);
				getJump(binary_val, token1);
				index = token2.find("=");
				//cout<<"Token 1: "<<token1<<endl;
				//cout<<"Token 2: "<<token2<<endl;
				//cout<<"= found at: "<<index<<endl;
				if(index<0)
				{
					binary_val[12] = '0';
					binary_val[11] = '0';
					binary_val[10] = '0';
					get7digitCode(binary_val, token2);
				}
				else
				{
					string token1_1 = token2.substr(0,index);
					string token2_1 = token2.substr(index+1, token2.size());
					get7digitCode(binary_val, token2_1);
					getDest(binary_val, token1_1);
				}
			}
			binary_val[16] = '\0';
			cout<<binary_val<<endl;
		}
		f_out<<binary_val<<"\r";
	}
	f_in.close();
	f_out.close();
	return 0; 
}