// Petrick_Method.cpp
#include "Petrick_Method.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
using namespace std;

set<string>::iterator iter;

/* -------------------- FRIEND -------------------- */
bool sort_by_SOP(const set<string> a, const set<string> b) {
	return ( a.size() < b.size() ) ;
}

/* -------------------- PUBLIC -------------------- */
Petrick_Method::Petrick_Method(vector<string> &Prime_Impli, vector<string> &On_Set) {
	int size1 = On_Set.size(), size2 = Prime_Impli.size() ;
	for( int i=0 ; i<size1 ; i++ ) {
		vector<string> sum;
		for( int j=0 ; j<size2 ; j++ ) {
			if( is_On_in_Prime_Impli( On_Set[i] , Prime_Impli[j] ) )
				sum.push_back( Prime_Impli[j] ) ;
		}
		POS.push_back( sum );
	}
}

Petrick_Method::~Petrick_Method() {}

set<string> Petrick_Method::Solve() {
	POS2SOP();
	sort( SOP.begin() , SOP.end() , sort_by_SOP );
	CountAllCost();
	return SOP[0] ;
}

/* -------------------- PRIVATE -------------------- */
void Petrick_Method::POS2SOP() {
	set<string> product;
	Expansion( product , 0 , POS.size() );
}

void Petrick_Method::Expansion(set<string> &product, int i_POS, int maxi) {
	if( i_POS==maxi ) { 
		string s = set2string(product) ;
		if( s_SOP.find(s)==s_SOP.end() ) {
			s_SOP.insert( s );
			SOP.push_back( product );
		}
	}
	int size = POS[ i_POS ].size() ;
	for( int i=0 ; i<size ; i++ ) {
		if( product.find( POS[ i_POS ][i] )==product.end() ) {
			product.insert( POS[ i_POS ][ i ] );
			Expansion( product , i_POS+1 , maxi );
			product.erase( POS[ i_POS ][i] );
		}
		else
			Expansion( product , i_POS+1 , maxi );
	}
}

string Petrick_Method::set2string(set<string> &temp) {
	stringstream ss;
	for( iter=temp.begin() ; iter!=temp.end() ; iter++ )
		ss<< *iter ;
	string s;
	ss>> s ;
	return s ;
}

bool Petrick_Method::is_On_in_Prime_Impli(string On, string Prime_Impli) {
	int size = On.size() ;
	for( int i=0 ; i<size ; i++ ) {
		if( Prime_Impli[i]!='-' && Prime_Impli[i]!=On[i] )
			return false ;
	}
	return true ;
}

void Petrick_Method::CountAllCost() {
	int min_cover = SOP[0].size() ;
	for( int i=0 ; SOP[i].size()==min_cover ; i++ ) {
		int cost = 0 ;
		for( iter=SOP[i].begin() ; iter!=SOP[i].end() ; iter++ )
			cost += CountCost( *iter ) ;
		SOP_cost.push_back(cost);
	}
}

int Petrick_Method::CountCost(string impli) {
	int size = impli.size(), cost = 0 ;
	for( int i=0 ; i<size ; i++ ) {
		if( impli[i]!='-' )
			cost++ ;
	}
	return cost ;
}

/* -------------------- PUBLIC/Print -------------------- */
void Petrick_Method::Print_POS() {
	cout<<"Product of Sum = ";
	int size1 = POS.size() ;
	for( int i=0 ; i<size1 ; i++ ) {
		cout<<"( "<< POS[i][0] ;
		int size2 = POS[i].size() ;
		for( int j=1 ; j<size2 ; j++ )
			cout<<" + "<< POS[i][j] ;
		cout<<" )";
	}
	cout<< endl;
}

void Petrick_Method::Print_SOP() {
	cout<<"Sum of Product = "<< endl;
	int size = SOP.size() ;
	for( int i=0 ; i<size ; i++ ) {
		iter = SOP[i].begin() ;
		cout<<"("<< *iter <<")";
		for( iter++ ; iter!=SOP[i].end() ; iter++ )
			cout<<"("<< *iter <<")";
		cout<< endl;
	}
	cout<< endl;
}

void Petrick_Method::Print_FewestTerm_P() {
	int min_cover = SOP[0].size() ;
	for( int i=0 ; SOP[i].size()==min_cover ; i++ ) {
		cout<<"Answer "<< i+1 <<" : "<< endl;
		iter = SOP[i].begin() ;
		cout<< *iter ;
		for( iter++ ; iter!=SOP[i].end() ; iter++ )
			cout<<"\n"<< *iter ;
		cout<< endl ;
		cout<<"cost = "<< SOP_cost[i] << endl ;
	}
}

void Petrick_Method::HW1_Print_Minimum_Cover() {
	int min_cover = SOP[0].size(), min_cost = SOP_cost[0] , ans = 0 ;
	int size = SOP.size() ;
	for( int i=0 ; SOP[i].size()==min_cover ; i++ ) {
		if( SOP_cost[i]<min_cost ) {
			min_cost = SOP_cost[i] ;
			ans = i ;
		}
	}
	cout<<".mc "<< min_cover << endl;
	for( iter=SOP[ans].begin() ; iter!=SOP[ans].end() ; iter++ )
		cout<< *iter << endl;
	cout<<"cost="<< min_cost << endl;
}

void Petrick_Method::HW1_Print_Minimum_Cover(ofstream &fout) {
	int min_cover = SOP[0].size(), min_cost = SOP_cost[0] , ans = 0 ;
	int size = SOP.size() ;
	for( int i=0 ; SOP[i].size()==min_cover ; i++ ) {
		if( SOP_cost[i]<min_cost ) {
			min_cost = SOP_cost[i] ;
			ans = i ;
		}
	}
	fout<<".mc "<< min_cover << endl;
	for( iter=SOP[ans].begin() ; iter!=SOP[ans].end() ; iter++ )
		fout<< *iter << endl;
	fout<<"cost="<< min_cost << endl;
}
