/*
 * Room.hpp
 *
 *  Created on: Nov 20, 2017
 *      Author: chulwoopark
 */

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include "Header.hpp"
#include "Border.hpp"

class Room {
public:
	string name;
	string status;
	string type;
	string description;
	map<string,Border*> border_structure;
	vector<string> container_structure;
	vector<string> item_structure;
	vector<string> creature_structure;
	vector<Trigger*> trigger_structure;

	Room(xml_node<> *pointer){
		read_room(pointer);
	}
	virtual ~Room() {};
private:
	void read_room(xml_node<> *pointer){
		// INITIALIZE type TO regular
		type = "regular";
		for(xml_node<> *cursor = pointer -> first_node(); cursor; cursor = cursor -> next_sibling()){
			if(string(cursor->name()) == "name"){
				name = cursor->value();
			}
			else if(string(cursor->name()) == "status"){
				status = cursor->value();
			}
			else if(string(cursor->name()) == "type"){
				type = cursor->value();
			}
			else if(string(cursor->name()) == "description"){
				description = cursor->value();
			}
			else if(string(cursor->name()) == "border"){
				Border *border = new Border(cursor);
				border_structure[border->direction] = border;
			}
			else if(string(cursor->name()) == "container"){
				container_structure.push_back(cursor->value());
			}
			else if(string(cursor->name()) == "item"){
				item_structure.push_back(cursor->value());
			}
			else if(string(cursor->name()) == "creature"){
				creature_structure.push_back(cursor->value());
			}
			else if(string(cursor->name()) == "trigger"){
				Trigger * trigger = new Trigger(cursor);
				trigger_structure.push_back(trigger);
			}
		}

	}
};




#endif /* ROOM_HPP_ */
