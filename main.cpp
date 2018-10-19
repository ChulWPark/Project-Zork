/*
 * main.cpp
 *
 *  Created on: Nov 20, 2017
 *      Author: chulwoopark
 */

#include "Header.hpp"
#include "Container.hpp"
#include "Creature.hpp"
#include "Item.hpp"
#include "Room.hpp"
#include "Map.hpp"
#include "LCU.hpp"

int main(int argc, char * argv[]){


	Map * world = new Map("Free_Map.xml"); // WORKS

	LCU * controller = new LCU(world);

	if(controller->GameOver == true){
		//cout<<"Game Over"<<endl;
		cout<<"Victory!"<<endl;
	}

	return 0;
};
