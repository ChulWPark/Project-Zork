/*
 * Item.hpp
 *
 *  Created on: Nov 20, 2017
 *      Author: chulwoopark
 */

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include "Header.hpp"
#include "Turnon.hpp"
#include "Trigger.hpp"

class Item {
public:
	string name;
	string status;
	string description;
	string writing;
	Turnon * turnon;
	vector<Trigger*> trigger_structure;
	Item(xml_node<> *pointer){
		read_item(pointer);
	}
	virtual ~Item() {};
private:
	void read_item(xml_node<> *pointer){
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
			else if(string(cursor->name()) == "writing"){
				writing = cursor->value();
			}
			else if(string(cursor->name()) == "turnon"){
				turnon = new Turnon(cursor);
			}
			else if(string(cursor->name()) == "trigger"){
				Trigger * trigger = new Trigger(cursor);
				trigger_structure.push_back(trigger);
			}

		}
	}
};




#endif /* ITEM_HPP_ */
