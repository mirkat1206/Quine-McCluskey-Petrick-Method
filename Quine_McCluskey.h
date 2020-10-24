// Quine_McCluskey.h

#ifndef QUINE_MCCLUSKEY
#define QUINE_MCCLUSKEY

#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Quine_McCluskey {
	friend bool sort_by_num_of_1(const string,const string);
	friend bool sort_by_num_of_literals(const string,const string);
private:
	int Num_Var;
	vector<int> On_Set;
	vector<int> DC_Set;
	vector<string> s_On_Set;
	vector<string> Impli;
	vector<string> Prime_Impli;
	
	void Init_Impli();
	string Dec2Bin(int);
	void Generate_Prime_Impli();
	string Merge(string,string);
	bool is_GrayCode(string,string);
public:
	Quine_McCluskey();
	~Quine_McCluskey();

	void Set_Num_Var(int);
	void Add_On_Set(int);
	void Add_DC_Set(int);
	vector<string> Solve();			// return prime implicants
	
	vector<string> & Get_On_Set();
	vector<string> & Get_Prime_Impli();

	void Print_Impli();
	void Print_Prime_Impli();
	void HW1_Print_Prime_Impli();
	void HW1_Print_Prime_Impli(ofstream &);
};

#endif
