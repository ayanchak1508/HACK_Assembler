#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

static int last_val = 0;
static int last_label = 0;

string removeSpaces(string str)	//This function basically removes all spaces from a line
{ 
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    return str; 
}

string removeNewLines(string str)	//This function basically removes all carriage returns from a line  
{ 
    str.erase(remove(str.begin(), str.end(), '\r'), str.end()); 
    return str; 
}

string removeExtension(string str)	//This function removes the .asm extension to get the filename to use for the output file
{
	int i = str.find(".asm");
	if(i>=0)
		str.erase(i, str.size()); 
    return str;
}

string removeComments(string str)  //Remove any instances of single line comments present in a single line
{ 
    int i = str.find("//");
	if(i>=0)
		str.erase(i, str.size()); 
    return str; 
}

void decToBinary_16(int n, char* arr) //Converts a number to its 16 bit representation and stores it in a 16 bit character array
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

void empty(char* arr)	//Initialises a 16 bit character array to 0
{
	for(int i = 15; i >= 0; i--) {
		arr[i] = '0';
	}
	arr[16] = '\0';
}

void get7digitCode(char* arr, string str)	//Updates the 7 bits depending on the operation being performed by the C-Type Instruction
{
	//cout<<"Value being passed: "<<str<<endl;
	//cout<<"Binary being passed: "<<arr<<endl;
	if(str.compare("0") == 0)	//It is nothing but a case by case comparison
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

void getDest(char* arr, string str)	//Updates the 3 bits depending on the destination of the result of the operation being performed by the C-Type Instruction
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

void getJump(char* arr, string str)	//To update the Jump bits
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

void init(string* table_names, int* table_values)	//Inititalizes the symbol table
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
	last_val = 22;				//Stores the index of the last value inside the symbol table
	last_label = 15;			//Stores the last value stored by a variable (excluding labels)
}

int return_val(string table[8192], int labels[8192], string str)	//Lookup function to return the value assosicated with a symbol
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

void add_new(string table[8192], int labels[8192], string str, int val)	//Add a new symbol and its value to the symbol table
{
	last_val++;
	table[last_val] = str;
	labels[last_val] = val;
}

void display(string table[8192], int labels[8192])	//Display the symbol table
{
	int i = 0;
	for(i = 0; i<=last_val; i++)
	{
		cout<<table[i]<<"\t"<<labels[i]<<endl;
	}
}

bool isNumber(string s)	//Check if a string is a number or not
{ 
    for (int i = 0; i < s.length(); i++) 
        if (isdigit(s[i]) == false) 
            return false; 
    return true; 
}

void assign(string table[8192], int labels[8192], string str)	//Asign an unencountered variable to a space in memory starting from 16
{
	last_val++;
	last_label++;
	table[last_val] = str;
	labels[last_val] = last_label;
}

int main()
{
	string file_name, str, line, binary;
	string symbol_table[8192];				//The symbol table is made up of two parts: one is a string array storing the names of the symbol
	int labels[8192];						//One more part is labels integer array containing the value assosciated to the symbol
	init(symbol_table, labels);				//Initialize the memory map
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
	else if(!f_in){							//Exit the program if file opening failed
		cout<<"File opening failed"<<endl;
		return 0;
	}
	file_name = removeExtension(str);
	file_name.append(".hack");				//Creating the file name for the output file
	f_out.open(file_name);
	while(f_in){							//Travel once through the file to get the values of the labels used in the program
		getline(f_in, line);
		line = removeSpaces(line);
		line = removeComments(line);
		line = removeNewLines(line);
		if(line.empty())					//Ignore all the useless line
			continue;
		cout<<line<<endl;
		if(line[0] == '(' && line[line.size()-1] == ')')	//this means it contains a label declaration
		{
			string token1 = line.substr(1, line.size()-2);	//get the label name
			//cout<<token1<<endl;
			int index = return_val(symbol_table, labels, token1);	//get the value assosciated with the label
			if(index<0)												//this means that the label was not found
				add_new(symbol_table, labels, token1, counter);		//add the label with its corresponding value which is nothing but the next line number
		}
		else
			counter++;										//Update the line number
	}
	f_in.close();
	f_in.open(str);											//To reset the file pointer to the beginning of the file
	while(f_in){
		getline(f_in, line);
		line = removeSpaces(line);
		line = removeComments(line);
		line = removeNewLines(line);
		if(line.empty()||(line[0] == '(' && line[line.size()-1] == ')'))	//Ignore the empty lines and the labels
			continue;
		cout<<line<<endl;
		binary = "";
		empty(binary_val);
		if(line[0] == '@')	//means it is an A type instruction
		{
			binary = line.substr(1, line.size());	//get the string after the @ symbol
			bool res = isNumber(binary);			//check if its a number or a symbol
			if(res == true)
				binary_16 = stoi(binary);			//if number convert it to an integer
			else
			{
				int val = return_val(symbol_table, labels, binary);	//if symbol then get its value
				if(val < 0){										//if value not found then it means its a variable
					assign(symbol_table, labels, binary);			//assign the variable the next available space after 16
					val = return_val(symbol_table, labels, binary);
				}
				binary_16 = val;
			}
			decToBinary_16(binary_16, binary_val);	//Convert the value into 16 bit binary
			binary_val[0] = '0';
			cout<<binary_val<<endl;
		}
		else
		{
			binary_val[0] = '1';	//A type instruction has the 3 MSBs one
			binary_val[1] = '1';
			binary_val[2] = '1';
			int index = line.find(";");	//for seperating the JUMP instruction
			//cout<<"; found at: "<<index<<endl;
			if(index<0)		//then means no Jump instruction present
			{
				binary_val[15] = '0';	//set the appropriate values to the JUMP bits
				binary_val[14] = '0';
				binary_val[13] = '0';
				index = line.find("=");	//for seperating the opeation and the destination
				//cout<<"= found at: "<<index<<endl;
				if(index<0)	//so only the operation is present
				{
					binary_val[12] = '0';	//set the appropriate destination bits
					binary_val[11] = '0';
					binary_val[10] = '0';
					get7digitCode(binary_val, line);	//get the code for the operation
				}
				else
				{
					string token1 = line.substr(0,index); //get the destination
					string token2 = line.substr(index+1, line.size());	//get the operation

					//cout<<"Token 1: "<<token1<<endl;
					//cout<<"Token 2: "<<token2<<endl;
					//cout<<"Token2 is:"<<token2<<"Test";
					//cout<<"Length of token2 is: "<<token2.size()<<endl;
					get7digitCode(binary_val, token2);	//Update the destination bits
					getDest(binary_val, token1);	//Update the operation bits
				}
			}
			else
			{
				string token1 = line.substr(index+1, line.size()); //Get the JUMP instruction
				string token2 = line.substr(0, index);	//Get the rest of the instruction
				getJump(binary_val, token1);	//Update the Jump bits
				index = token2.find("=");
				//cout<<"Token 1: "<<token1<<endl;
				//cout<<"Token 2: "<<token2<<endl;
				//cout<<"= found at: "<<index<<endl;
				if(index<0)	//destination not found only operation
				{
					binary_val[12] = '0';	//update the destination bits
					binary_val[11] = '0';
					binary_val[10] = '0';
					get7digitCode(binary_val, token2);	//update the operation bits
				}
				else
				{
					string token1_1 = token2.substr(0,index);	//get the destination
					string token2_1 = token2.substr(index+1, token2.size());	//get the operation
					get7digitCode(binary_val, token2_1);	//update the operation bits
					getDest(binary_val, token1_1);	//iupdate the destination bits
				}
			}
			binary_val[16] = '\0';	//put a delimiter at the end of the array for safety reasons
			cout<<binary_val<<endl;
		}
		f_out<<binary_val<<"\r";	//Write the 16 bit binary value to the output file
	}
	f_in.close();	//Close all the opened files
	f_out.close();
	return 0; 
}