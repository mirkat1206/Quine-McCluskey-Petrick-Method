// main.cpp
#include "Quine_McCluskey.h"
#include "Petrick_Method.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
using namespace std;

void Init(ifstream &,Quine_McCluskey &);
void Output(ofstream &,Quine_McCluskey &,Petrick_Method &);

int main(int argc, char *argv[])
{
	if( argc!=3 ) {
		cerr<<"Wrong number of arguments. Please execute as follow : \n"
			<<"./hw1.o <input_file name> <output_file name>"<< endl;
		exit(-1);
	}

	ifstream fin( argv[1] );
	ofstream fout( argv[2] );			

	cout<<"\n***** Quine-McCluskey Algorithm *****"<< endl;
	Quine_McCluskey QM;
	Init( fin , QM );
	QM.Solve();
	QM.Print_Prime_Impli();

	cout<<"\n***** Petrick's Method *****"<< endl;
	Petrick_Method PM( QM.Get_Prime_Impli() , QM.Get_On_Set() );
	PM.Solve();
	PM.Print_POS();
//	PM.Print_SOP();

	cout<<"\n***** All possible fewest-terms results *****"<< endl;
	PM.Print_FewestTerm_P();
	
	cout<<"\n***** Final Answer *****"<< endl;
	Output( fout , QM , PM );
	
	fin.close();
	fout.close();

	return 0;
}

/* 	input format example
 *	.i 4				( the function f has 4 input variables: A,B,C,D )
 *	.m					( on set )
 *	4 5 6 8 9 10 13
 *	.d					( don't care set )
 *	0 7 15
 */

void Init(ifstream &fin, Quine_McCluskey &QM) {
	// input from a file
	char c;
	while( fin>> c ) {
		if( c=='.' )	
			continue;
		if( c=='i' ) {
			int n;
			fin>> n ;
			QM.Set_Num_Var(n);
		}
		else if( c=='m' ) {
			string s;
			stringstream ss;
			getline( fin , s );
			getline( fin , s );
			ss<< s ;
			int n;
			while( ss>> n ) 
				QM.Add_On_Set(n);
		}
		else if( c=='d' ) {
			string s;
			stringstream ss;
			getline( fin , s );
			getline( fin , s );
			ss<< s ;
			int n;
			while( ss>> n ) 
				QM.Add_DC_Set(n);
		}
		else {
			cerr<<"Wrong input format."<< endl;
			exit(-1);
		}
	}
}

/* output format example
 * 	.pi 7				( there are 7 prime implicants )
 * 	0-00
 * 	-000
 *  100-
 *	10-0
 *	01--
 *	1-01
 *	-1-1
 *	.mc 3				( 3 prime implicants in minimum covering )
 *	10-0
 *	1-01
 *	01--
 *	cost=8
 */

void Output(ofstream &fout, Quine_McCluskey &QM, Petrick_Method &PM) {
	QM.HW1_Print_Prime_Impli();
	QM.HW1_Print_Prime_Impli(fout);
	PM.HW1_Print_Minimum_Cover();	
	PM.HW1_Print_Minimum_Cover(fout);	
	cout<< endl;
}
