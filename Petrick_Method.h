// Petrick_Method.h

#ifndef PETRICK_METHOD
#define PETRICK_METHOD

#include <set>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Petrick_Method {
	friend bool sort_by_SOP(const set<string>,const set<string>);
private:
	vector< vector<string> > POS;		// Product of Sum
	vector< set<string> > SOP;			// Sum of Product, XX=X
	set<string> s_SOP;					// string of SOP, X+X=X
	vector<int> SOP_cost;				// cost of each term in SOP

	bool is_On_in_Prime_Impli(string,string);
	void POS2SOP();
	void Expansion(set<string> &,int,int);
	void CountAllCost();
	int  CountCost(string);
	string set2string(set<string> &);
public:
	Petrick_Method(vector<string> &Prime_Impli, vector<string> &On_Set);
	~Petrick_Method();

	set<string> Solve();		// return prime implicants with minimun-cover

	void Print_POS();
	void Print_SOP();
	void Print_FewestTerm_P();
	void HW1_Print_Minimum_Cover();
	void HW1_Print_Minimum_Cover(ofstream &);
};

#endif
