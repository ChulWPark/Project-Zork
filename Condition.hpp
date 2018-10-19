/*
 * Condition.hpp
 *
 *  Created on: Nov 20, 2017
 *      Author: chulwoopark
 */

#ifndef CONDITION_HPP_
#define CONDITION_HPP_

#include "Header.hpp"

class Condition{
public:
	string object;
	string has;
	string owner;
	string status;
	Condition(xml_node<> *pointer){
		read_condition(pointer);
	}
	virtual ~Condition() {};
private:
	void read_condition(xml_node<> *pointer){
		for(xml_node<> *cursor = pointer -> first_node(); cursor; cursor = cursor -> next_sibling()){
			if(string(cursor->name()) == "object"){
				object = cursor->value();
			}
			else if(string(cursor->name()) == "has"){
				has = cursor->value();
			}
			else if(string(cursor->name()) == "owner"){
				owner = cursor->value();
			}
			else if(string(cursor->name()) == "status"){
				status = cursor->value();
			}
		}
	}
};




#endif /* CONDITION_HPP_ */
