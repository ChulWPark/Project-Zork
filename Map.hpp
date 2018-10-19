/*
 * Map.hpp
 *
 *  Created on: Nov 20, 2017
 *      Author: chulwoopark
 */

#ifndef MAP_HPP_
#define MAP_HPP_
#include "Container.hpp"
#include "Creature.hpp"
#include "Item.hpp"
#include "Room.hpp"
#include "Header.hpp"

class Map {
public:
	map<string,Container*> container_structure;
	map<string,Creature*> creature_structure;
	map<string,Item*> item_structure;
	map<string,Room*> room_structure;

	Map(const char *filename){
		read_map(filename);
	}
	virtual ~Map(){};
private:
	void read_map(const char *filename) {
		// START PARSING THE XML FILE
		file<> xml_file(filename);
		xml_document<> doc;
		doc.parse<0>(xml_file.data());
		xml_node<> *node = doc.first_node();
		// GOING THROUGH THE ENTIRE XML NODES
		for(xml_node<>*pointer = node -> first_node(); pointer; pointer = pointer -> next_sibling()){
			if (string(pointer->name()) == "item") {
				Item* item = new Item(pointer);
				item_structure[item->name] = item;
			}
			if (string(pointer->name()) == "container") {
				Container* container = new Container(pointer);
				container_structure[container->name] = container;
			}
			if (string(pointer->name()) == "room") {
				Room* room = new Room(pointer);
				room_structure[room->name] = room;
			}
			if (string(pointer->name()) == "creature") {
				Creature* creature = new Creature(pointer);
				creature_structure[creature->name] = creature;
			}
		}
	}
};

#endif /* MAP_HPP_ */
