// Quine_McCluskey.cpp

#include "Quine_McCluskey.h"
#include <iostream>
#include <algorithm>
using namespace std;

/* -------------------- FRIEND -------------------- */
bool sort_by_num_of_1(const string a, const string b) {
	int cnt_a = 0 , cnt_b = 0 , size = a.length() ;
	for( int i=0 ; i<size ; i++ ) {
		if( a[i]=='1' )		cnt_a++ ;
		if( b[i]=='1' )		cnt_b++ ;
	}
	return ( cnt_a < cnt_b ) ;
}

bool sort_by_num_of_literal(const string a, const string b) {
	int cnt_a = 0 , cnt_b = 0 , size = a.length() ;
	for( int i=0 ; i<size ; i++ ) {
		if( a[i]!='-' )		cnt_a++ ;
		if( b[i]!='-' )		cnt_b++ ;
	}
	return ( cnt_a < cnt_b ) ;
}

/* -------------------- PUBLIC -------------------- */
Quine_McCluskey::Quine_McCluskey() {}

Quine_McCluskey::~Quine_McCluskey() {}

void Quine_McCluskey::Set_Num_Var(int n) {	Num_Var = n ;	}

void Quine_McCluskey::Add_On_Set(int n) {	On_Set.push_back(n);	}

void Quine_McCluskey::Add_DC_Set(int n) {	DC_Set.push_back(n);	}

vector<string> Quine_McCluskey::Solve() {
	Init_Impli();
	sort( Impli.begin() , Impli.end() );
	sort( Impli.begin() , Impli.end() , sort_by_num_of_1 );

	int round = 0 ;
	while( !Impli.empty() ) {
//		cout<<"round "<< round++ <<" : "<< endl;
//		Print_Impli();
		Generate_Prime_Impli();
	}
	return Prime_Impli ;
}

vector<string> & Quine_McCluskey::Get_On_Set() {	return s_On_Set ;	}

vector<string> & Quine_McCluskey::Get_Prime_Impli() {	return Prime_Impli ;	}

/* -------------------- PRIVATE -------------------- */
void Quine_McCluskey::Generate_Prime_Impli() {
	vector<bool> flag;
	int size = Impli.size() ;
	for( int i=0 ; i<size ; i++ )
		flag.push_back( false );
	
	string s;
	vector<string> temp;
	for( int i=0 ; i<size ; i++ ) {
		for( int j=i+1 ; j<size ; j++ ) {
			if( is_GrayCode( Impli[i] , Impli[j] ) ) {
				string s = Merge( Impli[i] , Impli[j] ) ;
				if( find( temp.begin() , temp.end() , s )==temp.end() )
					temp.push_back( s );
				flag[i] = true ;
				flag[j] = true ;
			}
		}
		if( flag[i]==false ) 
			Prime_Impli.push_back( Impli[i] );
	}
	Impli.clear();
	size = temp.size() ;
	for( int i=0 ; i<size ; i++ )
		Impli.push_back( temp[i] );
}

string Quine_McCluskey::Merge(string a, string b) {
	int size = a.length() ;
	for( int i=0 ; i<size ; i++ ) {
		if( a[i]!=b[i] ) {
			a[i] = '-' ;
			return a ;
		}
	}
}

bool Quine_McCluskey::is_GrayCode(string a, string b) {
	int flag = 0 , size = a.length() ;
	for( int i=0 ; i<size ; i++ ) {
		if( a[i]!=b[i] )
			flag++ ;
	}
	return ( flag==1 );
}

void Quine_McCluskey::Init_Impli() {
	int size;	
	// on set
	size = On_Set.size() ;
	for( int i=0 ; i<size ; i++ ) {
		Impli.push_back( Dec2Bin(On_Set[i]) ) ;
		s_On_Set.push_back( Impli.back() );
	}
	// don't care set
	size = DC_Set.size() ;
	for( int i=0 ; i<size ; i++ )
		Impli.push_back( Dec2Bin(DC_Set[i]) ) ;
}

string Quine_McCluskey::Dec2Bin(int n) {
	string s;
	while( n!=0 ) {
		s += '0'+n%2 ;
		n /= 2 ;
	}
	int pad = Num_Var - s.length() ;
	while( pad-- ) {
		s += '0' ;
	}
	reverse( s.begin() , s.end() );
	return s ;
}

/* -------------------- PUBLIC/Print -------------------- */
void Quine_McCluskey::Print_Impli() {
	int size = Impli.size() ;
	for( int i=0 ; i<size ; i++ )
		cout<< Impli[i] << endl;
}

void Quine_McCluskey::Print_Prime_Impli() {
	int size = Prime_Impli.size() ;
	cout<<"Total number of Prime Implicant = "<< size << endl;
	for( int i=0 ; i<size ; i++ )
		cout<< Prime_Impli[i] << endl;
}

/* Below is HW1 output format spec.
 * Generate all prime implicants to a file. 
 * If there are more than 20 primary implicants, report only the first 20 primary implicants with the least number of literals to reduce the file size. 
 * However, you still have to report the correct number of total primary implicants at “.pi” field.
 */
void Quine_McCluskey::HW1_Print_Prime_Impli() {
	sort( Prime_Impli.begin() , Prime_Impli.end() , sort_by_num_of_literal );
	int size = Prime_Impli.size() ;
	cout<<".pi "<< size << endl;
	for( int i=0 ; i<size && i<20 ; i++ )
		cout<< Prime_Impli[i] << endl;
}

void Quine_McCluskey::HW1_Print_Prime_Impli(ofstream &fout) {
	sort( Prime_Impli.begin() , Prime_Impli.end() , sort_by_num_of_literal );
	int size = Prime_Impli.size() ;
	fout<<".pi "<< size << endl;
	for( int i=0 ; i<size && i<20 ; i++ )
		fout<< Prime_Impli[i] << endl;
}


