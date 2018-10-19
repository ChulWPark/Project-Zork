/*
 * Trigger.hpp
 *
 *  Created on: Nov 20, 2017
 *      Author: chulwoopark
 */

#ifndef TRIGGER_HPP_
#define TRIGGER_HPP_

#include "Header.hpp"
#include "Condition.hpp"

class Trigger{
public:
	string type;
	string command;
	string print;
	vector<string> action_structure;
	Condition * condition;
	Trigger(xml_node<> *pointer){
		read_trigger(pointer);
	}
private:
	void read_trigger(xml_node<> *pointer){
		for(xml_node<> *cursor = pointer -> first_node(); cursor; cursor = cursor -> next_sibling()){
			if(string(cursor->name()) == "type"){
				type = cursor->value();
			}
			else if(string(cursor->name()) == "command"){
				command = cursor->value();
			}
			else if(string(cursor->name()) == "print"){
				print = cursor->value();
			}
			else if(string(cursor->name()) == "action"){
				action_structure.push_back(cursor->value());
			}
			else if(string(cursor->name()) == "condition"){
				condition = new Condition(cursor);
			}
		}
	}

};




#endif /* TRIGGER_HPP_ */
