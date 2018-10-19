/*
 * Border.hpp
 *
 *  Created on: Nov 20, 2017
 *      Author: chulwoopark
 */

#ifndef BORDER_HPP_
#define BORDER_HPP_

#include "Header.hpp"

class Border{
public:
	string direction;
	string name;
	Border(xml_node<> *pointer){
		read_border(pointer);
	}
	virtual ~Border() {};
private:
	void read_border(xml_node<> *pointer){
		// GET THE NAME AND DIRECTION
		xml_node<> * cursor = pointer -> first_node();
		if(string(cursor->name()) == "direction"){
			direction = cursor->value();
		}
		else{
			name = cursor->value();
		}
		cursor = cursor -> next_sibling();
		if(string(cursor->name()) == "name"){
			name = cursor->value();
		}
		else{
			direction = cursor->value();
		}
	}
};




#endif /* BORDER_HPP_ */
