/*
 * QuadTree_Definitions.cpp
 *
 *  Created on: Oct 11, 2020
 *      Author: BCimr
 */

#include "QuadTree.h"
#include "iostream"
#include "cmath"

QuadTree::QuadTree(QuadTree* guardian, std::string title, double longit, double latit, double ppltn, double col, double avg_sal) {
	longitude = longit;
	latitude = latit;
	cost_of_living = col;
	avg_salary = avg_sal;
	pop = ppltn;
	p_parent = guardian;
	p_ne = nullptr;
	p_nw = nullptr;
	p_se = nullptr;
	p_sw = nullptr;
	name = title;
	leaf = true;
	empty = false;

}

QuadTree::QuadTree() {
	longitude = 0;
	latitude = 0;
	cost_of_living = 0;
	avg_salary = 0;
	pop = 0;
	p_parent = nullptr;
	p_ne = nullptr;
	p_nw = nullptr;
	p_se = nullptr;
	p_sw = nullptr;
	name = "";
	leaf = true;
	empty = true;

}

QuadTree::QuadTree( const QuadTree &other ) {
	longitude = other.longitude;
	latitude = other.latitude;
	cost_of_living = other.cost_of_living;
	avg_salary = other.avg_salary;
	pop = other.pop;
	p_parent = other.p_parent;
	p_ne = other.p_ne;
	p_nw = other.p_nw;
	p_se = other.p_se;
	p_sw = other.p_sw;
	name = other.name;
	leaf = other.leaf;
	empty = other.empty;
}

QuadTree& QuadTree::operator=( const QuadTree &other ) {
	QuadTree temp(other);

	std::swap(longitude, temp.longitude);
	std::swap(latitude, temp.latitude);
	std::swap(cost_of_living, temp.cost_of_living);
	std::swap(avg_salary, temp.avg_salary);
	std::swap(pop, temp.pop);
	std::swap(p_parent, temp.p_parent);
	std::swap(p_ne, temp.p_ne);
	std::swap(p_nw, temp.p_nw);
	std::swap(p_se, temp.p_se);
	std::swap(p_sw, temp.p_sw);
	std::swap(name, temp.name);
	std::swap(leaf, temp.leaf);
	std::swap(empty, temp.empty);

	return *this;
}

QuadTree::~QuadTree() {
	this->clear();
}

void QuadTree::set_ne( QuadTree* new_ne ) {
	p_ne = new_ne;
	leaf = this->check_leaf();

	return;
}

void QuadTree::set_nw( QuadTree* new_nw ) {
	p_nw = new_nw;
	leaf = this->check_leaf();

	return;
}

void QuadTree::set_se( QuadTree* new_se ) {
	p_se = new_se;
	leaf = this->check_leaf();
	return;
}

void QuadTree::set_sw( QuadTree* new_sw ){
	p_sw = new_sw;
	leaf = this->check_leaf();
	return;
}

void QuadTree::set_parent( QuadTree* new_p ) {
	p_parent = new_p;
	return;
}

bool QuadTree::check_leaf() {
	if ( ( p_ne == nullptr ) && ( p_se == nullptr ) && ( p_nw == nullptr ) && ( p_sw == nullptr ) ) {
		return true;
	}
	return false;
}

void QuadTree::set_long( double new_long ) {
	longitude = new_long;
	return;
}

void QuadTree::set_lat( double new_lat ) {
	latitude = new_lat;
	return;
}

void QuadTree::set_col( double new_col ) {
	cost_of_living = new_col;
	return;
}

void QuadTree::set_avg_sal( double new_avg_sal ) {
	avg_salary = new_avg_sal;
	return;
}

void QuadTree::set_pop( long new_pop ) {
	pop = new_pop;
	return;
}

QuadTree* QuadTree::ne() {
	return p_ne;
}

QuadTree* QuadTree::nw() {
	return p_nw;
}

QuadTree* QuadTree::se() {
	return p_se;
}

QuadTree* QuadTree::sw() {
	return p_sw;
}

QuadTree* QuadTree::parent() {
	return p_parent;
}

double QuadTree::get_long() {
	return longitude;
}

double QuadTree::get_lat()  {
	return latitude;
}

double QuadTree::get_col()  {
	return cost_of_living;
}

double QuadTree::get_avg_sal()  {
	return avg_salary;
}

long QuadTree::get_pop() {
	return pop;
}

std::string QuadTree::get_name() {
	return name;
}

bool QuadTree::clear() {

	if ( this->nw() != nullptr ) {
		this->nw()->clear();
		delete this->nw();
		this->set_nw( nullptr );
	}

	if ( this->sw() != nullptr ) {
		this->sw()->clear();
		delete this->sw();
		this->set_sw( nullptr );
	}

	if ( this->se() != nullptr ) {
		this->se()->clear();
		delete this->se();
		this->set_se( nullptr );
	}

	if ( this->ne() != nullptr ) {
		this->ne()->clear();
		delete this->ne();
		this->set_ne( nullptr );
	}

	if ( p_parent == nullptr ) {
		this->name = "";
		this->cost_of_living = 0;
		this->avg_salary = 0;
		this->latitude = 0;
		this->longitude = 0;
		this->leaf = true;
		this->pop = 0;
	}
	empty = true;

	return true;
}

bool QuadTree::insert( QuadTree* to_insert ) {
	if ( ( fabs(this->latitude - to_insert->get_lat()) < 0.000001 ) && ( fabs(this->longitude - to_insert->get_long()) < 0.000001 ) ) {
		return false;

	} else if ( ( this->longitude <= to_insert->get_long()) && ( this->latitude < to_insert->get_lat() ) ) {
		if ( this->ne() == nullptr ) {
			this->set_ne( to_insert );
			to_insert->set_parent( this );
			return true;

		}
		return this->ne()->insert( to_insert );
	} else if ( ( this->longitude > to_insert->get_long()) && ( this->latitude <= to_insert->get_lat() ) ) {
		if ( this->nw() == nullptr ) {
			this->set_nw( to_insert );
			to_insert->set_parent( this );
			return true;
		}
		return this->nw()->insert( to_insert );
	} else if ( ( this->longitude >= to_insert->get_long()) && ( this->latitude > to_insert->get_lat() ) ) {
		if ( this->sw() == nullptr ) {
			this->set_sw( to_insert );
			to_insert->set_parent( this );
			return true;

		}
		return this->sw()->insert( to_insert );
	} else if ( ( this->longitude < to_insert->get_long()) && ( this->latitude >= to_insert->get_lat() ) ) {
		if ( this->se() == nullptr ) {
			this->set_se( to_insert );
			to_insert->set_parent( this );
			return true;

		}
		return this->se()->insert( to_insert );
	}

	empty = false;
	return true;
}

QuadTree* QuadTree::search( double long_to_search, double lat_to_search )  {
	if ( this->empty ) {
		return nullptr;
	}
	if ( ( fabs(this->longitude - long_to_search) < 0.000001 ) && ( fabs(this->latitude - lat_to_search) < 0.000001 ) ) {
		return this;
	}

	if ( ( this->longitude <= long_to_search) && ( this->latitude < lat_to_search ) ) {
		if ( this->ne() == nullptr ) {
			return nullptr;
		}

		QuadTree* val = this->ne()->search( long_to_search, lat_to_search );
		if ( val != nullptr ) {
			return val;
		}
	} else if ( ( this->longitude > long_to_search) && ( this->latitude <= lat_to_search ) ) {
		if ( this->nw() == nullptr ) {
			return nullptr;
		}

		QuadTree* val = this->nw()->search( long_to_search, lat_to_search );
		if ( val != nullptr ) {
			return val;
		}
	} else if ( ( this->longitude >= long_to_search) && ( this->latitude > lat_to_search ) ) {
		if ( this->sw() == nullptr ) {
			return nullptr;
		}
		QuadTree* val = this->sw()->search( long_to_search, lat_to_search );
		if ( val != nullptr ) {
			return val;
		}
	} else if ( ( this->longitude < long_to_search) && ( this->latitude >= lat_to_search ) ) {
		if ( this->se() == nullptr ) {
			return nullptr;
		}

		QuadTree* val = this->se()->search( long_to_search, lat_to_search );
		if ( val != nullptr ) {
			return val;
		}
	}

	return nullptr;
}

void QuadTree::print( unsigned int size, unsigned int &num_printed ) {
	// must print first outside the recursive function

	if ( this->ne() != nullptr ) {
		this->ne()->print( size, num_printed );
	}
	if ( this->nw() != nullptr ) {
		this->nw()->print( size, num_printed );
	}
	if ( name != "" ) {
		std::cout << name;
		if ( num_printed < size-1 ) {
			std::cout << ' ';
			num_printed++;
		}
	}
	if ( this->sw() != nullptr ) {
		this->sw()->print( size, num_printed );
	}
	if ( this->se() != nullptr ) {
		this->se()->print( size, num_printed);
	}

	return;

}

double QuadTree::attr_search( double long_to_start, double lat_to_start, std::string d, char attr, std::string goal ) {
	int f{};
	double val{-1};
	if ( goal == "total" ) {
		f = 0;
	} else if ( goal == "max" ) {
		f = 1;
	} else if ( goal == "min" ) {
		f = 2;
	} else {
		return -1;
	}

	QuadTree* start = this->search( long_to_start, lat_to_start );
	if ( start == nullptr ) {
		return -1;
	}

	if ( d == "NE" ) {
		if ( start->ne() == nullptr ) {
			return -1;
		} else{
			return start->ne()->find( attr, f, val );
		}
	} else if ( d == "NW" ) {
		if ( start->nw() == nullptr ) {
			return -1;
		} else{
			return start->nw()->find( attr, f, val );
		}
	} else if ( d == "SE" ) {
		if ( start->se() == nullptr ) {
			return -1;
		} else{
			return start->se()->find( attr, f, val );
		}
	} else if ( d == "SW" ) {
		if ( start->sw() == nullptr ) {
			return -1;
		} else{
			return start->sw()->find( attr, f, val );
		}
	} else {
		return -1;
	}


	return val;
}

double QuadTree::find( char attr, int f, double val ) {
	bool first = false;
	if ( val == -1 ) {
		val = this->get_attr( attr );
		first = true;
	}
	if ( f == 0 ) {
		if ( !first ) {
			val += this->get_attr( attr );
		}
	} else if ( f == 1 ) {
		if ( this->get_attr( attr ) > val ) {
			val = this->get_attr( attr );
		}
	} else if ( f == 2 ) {
		if ( this->get_attr( attr ) < val ) {
			val = this->get_attr( attr );
		}
	}



	if ( this->se() != nullptr ) {
		val = this->se()->find( attr, f, val );
	}
	if ( this->sw() != nullptr ) {
		val = this->sw()->find( attr, f, val );
	}
	if ( this->ne() != nullptr ) {
		val = this->ne()->find( attr, f, val );
	}
	if ( this->nw() != nullptr ) {
		val = this->nw()->find( attr, f, val );
	}

	return val;

}

unsigned int QuadTree::size( unsigned int curr_size ) {
	if ( ( this->ne() == nullptr ) && ( this->nw() == nullptr ) && ( this->se() == nullptr ) && ( this->sw() == nullptr ) && ( this->parent() != nullptr ) ) {
		return curr_size+1;
	}
	if ( this->parent() != nullptr )  {
		curr_size++;
	} else if ( this->name != "" ) {
		curr_size++;
	}
	if ( this->nw() != nullptr ) {
		curr_size = this->nw()->size(curr_size);
	}
	if ( this->sw() != nullptr ) {
		curr_size = this->sw()->size(curr_size);
	}
	if ( this->se() != nullptr ) {
		curr_size = this->se()->size(curr_size);
	}
	if ( this->ne() != nullptr ) {
		curr_size = this->ne()->size(curr_size);
	}

	return curr_size;
}

QuadTree* QuadTree::get_child( std::string d ) {
	if ( d == "NE" ) {
		return this->ne();
	} else if ( d == "NW" ) {
		return this->nw();
	} else if ( d == "SE" ) {
		return this->se();
	} else if ( d == "SW" ) {
		return this->sw();
	}
	return nullptr;
}

double QuadTree::get_attr( char attr ) {
	if ( attr == 'p' ) {
		return this->pop;
	} else if ( attr == 'r' ) {
		return this->cost_of_living;
	} else if ( attr == 's' ) {
		return this->avg_salary;
	}
	return -1;
}



