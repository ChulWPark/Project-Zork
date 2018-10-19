/*
 * Container.hpp
 *
 *  Created on: Nov 20, 2017
 *      Author: chulwoopark
 */

#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include "Header.hpp"
#include "Trigger.hpp"

class Container{
public:
	string name;
	string status;
	string description;
	vector<string> accept_structure;
	vector<string> item_structure;
	vector<Trigger*> trigger_structure;
	Container(xml_node<> *pointer){
		read_container(pointer);
	}
	virtual ~Container() {};
private:
	void read_container(xml_node<> *pointer){
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
			else if(string(cursor->name()) == "accept"){
				accept_structure.push_back(cursor->value());
			}
			else if(string(cursor->name()) == "item"){
				item_structure.push_back(cursor->value());
			}
			else if(string(cursor->name()) == "trigger"){
				Trigger * trigger = new Trigger(cursor);
				trigger_structure.push_back(trigger);
			}
		}
	}
};




#endif /* CONTAINER_HPP_ */
