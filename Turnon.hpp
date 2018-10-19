/*
 * Turnon.hpp
 *
 *  Created on: Nov 20, 2017
 *      Author: chulwoopark
 */

#ifndef TURNON_HPP_
#define TURNON_HPP_

#include "Header.hpp"

class Turnon {
public:
	string print;
	string action;
	Turnon(xml_node<> *pointer){
		read_turnon(pointer);
	}
private:
	void read_turnon(xml_node<> *pointer){
		// GET THE PRINT NODE
		xml_node<> * cursor = pointer -> first_node();
		if(string(cursor->name()) == "print"){
			print = cursor->value();
		}
		else{
			action = cursor->value();
		}
		// GET THE ACTION NODE
		cursor = cursor -> next_sibling();
		if(string(cursor->name()) == "action"){
			action = cursor->value();
		}
		else{
			print = cursor->value();
		}
	}
};



#endif /* TURNON_HPP_ */
