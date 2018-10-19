/*
 * Attack.hpp
 *
 *  Created on: Nov 20, 2017
 *      Author: chulwoopark
 */

#ifndef ATTACK_HPP_
#define ATTACK_HPP_

#include "Header.hpp"
#include "Condition.hpp"

class Attack{
public:
	Condition * condition;
	string print;
	vector<string> action_structure;
	Attack(xml_node<> * pointer){
		read_attack(pointer);
	}
	virtual ~Attack() {};
private:
	void read_attack(xml_node<> * pointer){
		condition = NULL;
		for(xml_node<> *cursor = pointer -> first_node(); cursor; cursor = cursor -> next_sibling()){
			if(string(cursor->name()) == "condition"){
				condition = new Condition(cursor);
			}
			else if(string(cursor->name()) == "print"){
				print = cursor->value();
			}
			else if(string(cursor->name()) == "action"){
				action_structure.push_back(cursor->value());
			}
		}
	}

};




#endif /* ATTACK_HPP_ */
