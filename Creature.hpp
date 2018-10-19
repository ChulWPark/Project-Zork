/*
 * Creature.hpp
 *
 *  Created on: Nov 20, 2017
 *      Author: chulwoopark
 */

#ifndef CREATURE_HPP_
#define CREATURE_HPP_

#include "Header.hpp"
#include "Attack.hpp"

class Creature {
public:
	string name;
	string status;
	string description;
	vector<string> vulnerability_structure;
	Attack * attack;
	vector<Trigger*> trigger_structure;

	Creature(xml_node<> *pointer){
		read_creature(pointer);
	}
	virtual ~Creature() {};
private:
	void read_creature(xml_node<> *pointer){
		for(xml_node<> *cursor = pointer -> first_node(); cursor; cursor = cursor -> next_sibling()){
			if(string(cursor->name()) == "name"){
				name = cursor->value();
			}
			else if(string(cursor->name()) == "status"){
				status = cursor->value();
			}
			else if(string(cursor->name()) == "description"){
				description = cursor->value();
			}
			else if(string(cursor->name()) == "vulnerability"){
				vulnerability_structure.push_back(cursor->value());
			}
			else if(string(cursor->name()) == "attack"){
				attack = new Attack(cursor);
			}
			else if(string(cursor->name()) == "trigger"){
				Trigger * trigger = new Trigger(cursor);
				trigger_structure.push_back(trigger);
			}
		}
	}

};



#endif /* CREATURE_HPP_ */
