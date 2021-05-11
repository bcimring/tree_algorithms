/*
 * qttest.cpp
 *
 *  Created on: Oct 11, 2020
 *      Author: BCimr
 */

#include "iostream"
#include "string"
#include "quadtree\QuadTree.h"
#include "iomanip"

bool in_str( std::string txt, char m ) {
	for ( unsigned int i = 0; i < txt.length(); i++ ) {
		if ( txt[i] == m ) {
			return true;
		}
	}
	return false;
}

double str2double( std::string string ) {
	double result{};
	bool dec_flag = false;
	bool neg_flag = false;
	double div{1.0};
	if ( string[0] == '-' ) {
		neg_flag = true;
		string = string.substr( 1, string.length() - 1 );
	}
	for ( int i = 0; i < string.length(); i++ ) {
		if ( string[i]-46 == 0 ) {
			dec_flag = true;
		} else if (string[i] == '\n') {
			break;
		} else {
			result = result*10 + string[i]-48;
			if ( dec_flag ) {
				div *= 10;
			}
		}
	}
	if ( neg_flag ) {
		return -result/div;
	}
	return result/div;
}
//i
int main() {
	std::string line {};
	QuadTree* T = new QuadTree();
	bool instantiated = false;

	while ( !std::cin.eof() )  {
		getline(std::cin, line);

		if ( line == "exit" ) {
			T->clear();
			delete T;
			return 0;
		}

		if ( line[line.size()-1] == '\r' ) {
			line = line.substr(0, line.size()-1);
		}

		int insert_idx = line.find("i")+1;
		int search_idx = line.find("s")+1;
		int max_idx = line.find("q_max")+1;
		int min_idx = line.find("q_min")+1;
		int total_idx = line.find("q_total")+1;
		int print_idx = line.find("print")+1;
		int clear_idx = line.find("clear")+1;
		int size_idx = line.find("size")+1;
		int exit_idx = line.find("exit")+1;

		if (insert_idx == 1) {
			std::string name{};
			double longit, latit, col, avg_sal;
			long pop;

			// parse all elements
			long s_elem{}, e_elem{};
			s_elem = 2;
			e_elem = line.find( ";", 0 );
			name = line.substr( s_elem, e_elem-s_elem );
			line = line.substr( e_elem+1, line.size()-1 );

			s_elem = 0;
			e_elem = line.find( ";", 0 );
			longit = str2double( line.substr( s_elem, e_elem-s_elem ) );
			line = line.substr( e_elem+1, line.size()-1 );

			s_elem = 0;
			e_elem = line.find( ";", 0 );
			latit = str2double( line.substr( s_elem, e_elem-s_elem ) );
			line = line.substr( e_elem+1, line.size()-1 );

			s_elem = 0;
			e_elem = line.find( ";", 0 );
		    pop = str2double( line.substr( s_elem, e_elem-s_elem ) );
			line = line.substr( e_elem+1, line.size()-1 );

			s_elem = 0;
			e_elem = line.find( ";", 0 );
			col = str2double( line.substr( s_elem, e_elem-s_elem ) );
			line = line.substr( e_elem+1, line.size()-1 );

			s_elem = 0;
			e_elem = line.find( ";", 0 );
			avg_sal = str2double( line.substr( s_elem, e_elem-s_elem ) );
			line = line.substr( e_elem+1, line.size()-1 );

			QuadTree* to_insert{ new QuadTree( nullptr, name, longit, latit, pop, col, avg_sal ) };
			if ( T->search( longit, latit ) == nullptr ) {

				if ( T->size(0) == 0 ) {
					delete T;
					T = to_insert;
					std::cout << "success" << std::endl;
					instantiated = true;
				} else {
					bool success = T->insert( to_insert );
					if (success) {
						std::cout << "success" << std::endl;
						instantiated = true;

					} else {
						std::cout << "failure" << std::endl;
						delete to_insert;
					}
				}
			} else {
				std::cout << "failure" << std::endl;
				delete to_insert;
			}

		} else if ( (search_idx == 1) && (size_idx != 1 ) ) {
			double longit, latit;

			// parse all elements
			long s_elem{}, e_elem{};
			s_elem = 2;
			e_elem = line.find( ";", 0 );
			longit = str2double( line.substr( s_elem, e_elem-s_elem ) );
			line = line.substr( e_elem+1, line.size()-1 );

			s_elem = 0;
			e_elem = line.find( ";", 0 );
			latit = str2double( line.substr( s_elem, e_elem-s_elem ) );
			line = line.substr( e_elem+1, line.size()-1 );

			QuadTree* find = T->search( longit, latit );
			if ( find != nullptr ) {
				std::cout << "found " << find->get_name() << std::endl;
			} else {
				std::cout << "not found" << std::endl;
			}
			find = nullptr;


		} else if ( ( (max_idx == 1) || (min_idx == 1) || (total_idx == 1) )  && ( instantiated ) ){
			std::string name{};
			double longit, latit;
			std::string d, goal;
			char attr;

			long s_elem = 2;
			long e_elem = line.find( ' ', 0 );
			goal = line.substr( s_elem, e_elem - s_elem );
			line = line.substr( e_elem+1, line.size() -1 );

			// parse all elements

			s_elem = 0;
			e_elem = line.find( ";", 0 );
			longit = str2double( line.substr( s_elem, e_elem-s_elem ) );
			line = line.substr( e_elem+1, line.size()-1 );

			s_elem = 0;
			e_elem = line.find( ";", 0 );
			latit = str2double( line.substr( s_elem, e_elem-s_elem ) );
			line = line.substr( e_elem+1, line.size()-1 );

			e_elem = line.find( ";", 0 );
			d = line.substr( s_elem, e_elem-s_elem );
			line = line.substr( e_elem+1, line.size()-1 );

			e_elem = line.find( ";", 0 );
			attr = line[0];

			double result = T->attr_search( longit, latit, d, attr, goal );
			long res{};
			if ( attr == 'p' ) {
				res = static_cast<long>(result);
				if ( max_idx == 1) {
					if ( result != -1 ) { std::cout << "max " << res << std::endl;}
					else { std::cout << "failure" << std::endl; }
				} else if ( min_idx == 1) {
					if ( result != -1 ) { std::cout << "min " << res << std::endl;}
					else { std::cout << "failure" << std::endl; }
				} else if ( total_idx == 1) {
					if ( result != -1 ) { std::cout << "total " << res << std::endl;}
					else { std::cout << "failure" << std::endl; }
					}
			} else {
				if ( max_idx == 1) {

					if ( result != -1 ) {
						std::cout << std::fixed;
						std::cout << std::setprecision(2);
						std::cout << "max " << result << std::endl;}
					else { std::cout << "failure" << std::endl; }
				} else if ( min_idx == 1) {
					if ( result != -1 ) {
						std::cout << std::fixed;
						std::cout << std::setprecision(2);
						std::cout << "min " << result << std::endl;}
					else { std::cout << "failure" << std::endl; }
				} else if ( total_idx == 1) {
					if ( result != -1 ) {
						std::cout << std::fixed;
						std::cout << std::setprecision(2);
						std::cout << "total " << result << std::endl;}
					else { std::cout << "failure" << std::endl; }
				}
			}
		} else if (print_idx == 1) {
			unsigned int temp{};
			T->print( T->size(0), temp );
			if (T->size(0) > 0 ) {
				std::cout << std::endl;
			}
		} else if (clear_idx == 1) {
			T->clear();
			instantiated = false;
			std::cout << "success" << std::endl;
		} else if (size_idx == 1) {
			std::cout << "tree size " << T->size(0) << std::endl;
		} else if (exit_idx == 1) {
			T->clear();
			delete T;
			break;

		} else {
			std::cout << "failure" << std::endl;
		}
	}

	return 0;

}
