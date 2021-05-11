/*
 * QuadTree.h
 *
 *  Created on: Oct 11, 2020
 *      Author: BCimr
 */
#include "string"
#ifndef QUADTREE_H_
#define QUADTREE_H_

class QuadTree{
private:
	QuadTree* p_parent;
	QuadTree* p_ne;
	QuadTree* p_nw;
	QuadTree* p_se;
	QuadTree* p_sw;

	double longitude;
	double latitude;
	double cost_of_living;
	double avg_salary;
	double pop;

	bool leaf;
	bool empty;

	std::string name;

public:
	QuadTree(QuadTree* guardian, std::string name, double longit, double latit, double col, double avg_sal, double pop);
	QuadTree();
	QuadTree( const QuadTree &other );

	~QuadTree();

	QuadTree& operator=( const QuadTree &other );

	void set_ne( QuadTree* new_ne );
	void set_nw( QuadTree* new_nw );
	void set_se( QuadTree* new_se );
	void set_sw( QuadTree* new_sw );
	void set_parent( QuadTree* new_p );
	void set_long( double new_long );
	void set_lat( double new_lat );
	void set_col( double new_col );
	void set_avg_sal( double new_avg_sal );
	void set_pop( long new_pop );

	QuadTree* ne();
	QuadTree* nw();
	QuadTree* se();
	QuadTree* sw();
	QuadTree* parent();
	double get_long();
	double get_lat();
	double get_col();
	double get_avg_sal();
	long get_pop();
	std::string get_name();

	bool check_leaf();
	bool clear();
	bool insert( QuadTree* to_insert );
	QuadTree* search( double long_to_search, double lat_to_search );
	void print( unsigned int size, unsigned int &num_printed );
	double attr_search( double long_to_start, double lat_to_start, std::string d, char attr, std::string goal );
	unsigned int size( unsigned int curr_size );
	QuadTree* get_child( std::string d );
	double get_attr( char attr );
	double find( char attr, int f, double val );


};




#endif /* QUADTREE_H_ */
