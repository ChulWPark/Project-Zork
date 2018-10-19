/*
 * LCU.hpp
 *
 *  Created on: Nov 22, 2017
 *      Author: chulwoopark
 */

#ifndef LCU_HPP_
#define LCU_HPP_

#include "Header.hpp"
#include "Map.hpp"
#include <sstream>

class LCU{
public:
	bool GameOver;
	Room * GPS_tracker;
	vector<string> player_inventory;
	LCU(Map * world){
		running(world);
	}
	virtual ~LCU( ) { };
private:
	void running(Map * world){
		// VARIABLE DECLARAIONS & INITIALIZATION
		string user_input;
		GameOver = false;
		// Initial room will always be named "Entrance"
		GPS_tracker = world->room_structure["Entrance"];
		cout<<GPS_tracker->description<<endl;
		// WHILE LOOP UNTIL GAME IS OVER
		while(GameOver == false){
			//cout<<">> ";
			getline(cin,user_input);
			bool Error = false;
			// GO NORTH
			if(user_input == "n"){
				bool item_exist = false;
				bool no_check = false;
				if(GPS_tracker->border_structure["north"] == NULL){
					cout<<"Can't go that way."<<endl;
				}
				else{
					if(GPS_tracker->trigger_structure.size() != 0){
						if(GPS_tracker->trigger_structure.size() == 1){
							for(int lec = 0; lec < GPS_tracker->trigger_structure.size(); lec++){
								if(GPS_tracker->trigger_structure[lec]->command == user_input){
									if(GPS_tracker->trigger_structure[lec]->condition->owner == "inventory"){
										for(int index = 0; index < player_inventory.size(); index++){
											if(player_inventory[index] == GPS_tracker->trigger_structure[lec]->condition->object){
												item_exist = true;
												GPS_tracker = world->room_structure[GPS_tracker->border_structure["north"]->name];
												cout<<GPS_tracker->description<<endl;
											}
										}
										if(item_exist == false){
											cout<<GPS_tracker->trigger_structure[lec]->print<<endl;
										}
									}
									else if(world->container_structure[GPS_tracker->trigger_structure[lec]->condition->object]->status == "locked"){
										cout<<GPS_tracker->trigger_structure[lec]->print<<endl;
									}
									else if(world->container_structure[GPS_tracker->trigger_structure[lec]->condition->object]->status == "unlocked"){
										GPS_tracker = world->room_structure[GPS_tracker->border_structure["north"]->name];
										cout<<GPS_tracker->description<<endl;
									}
								}
								else{
									GPS_tracker = world->room_structure[GPS_tracker->border_structure["north"]->name];
									cout<<GPS_tracker->description<<endl;
								}
							}
						}
						else if(GPS_tracker->trigger_structure.size() == 2){
							for(int lec = 1; lec < GPS_tracker->trigger_structure.size(); lec--){
								if(no_check == false){
									if(GPS_tracker->trigger_structure[lec]->command == user_input){
										if(GPS_tracker->trigger_structure[lec]->condition->owner == "inventory"){
											for(int index = 0; index < player_inventory.size(); index++){
												if(player_inventory[index] == GPS_tracker->trigger_structure[lec]->condition->object){
													item_exist = true;
													GPS_tracker = world->room_structure[GPS_tracker->border_structure["north"]->name];
													cout<<GPS_tracker->description<<endl;
												}
											}
											if(item_exist == false){
												cout<<GPS_tracker->trigger_structure[lec]->print<<endl;
											}
										}
										else if(world->container_structure[GPS_tracker->trigger_structure[lec]->condition->object]->status == "locked"){
											cout<<GPS_tracker->trigger_structure[lec]->print<<endl;
											no_check = true;
										}
										else if(world->container_structure[GPS_tracker->trigger_structure[lec]->condition->object]->status == "unlocked"){
											GPS_tracker = world->room_structure[GPS_tracker->border_structure["north"]->name];
											cout<<GPS_tracker->description<<endl;
										}
									}
									else{
										GPS_tracker = world->room_structure[GPS_tracker->border_structure["north"]->name];
										cout<<GPS_tracker->description<<endl;
									}
								}
							}
						}
					}
					else{
						GPS_tracker = world->room_structure[GPS_tracker->border_structure["north"]->name];
						cout<<GPS_tracker->description<<endl;
					}
				}
			}
			// GO SOUTH
			else if(user_input == "s"){
				if(GPS_tracker->border_structure["south"] == NULL){
					cout<<"Can't go that way."<<endl;
				}
				else{
					GPS_tracker = world->room_structure[GPS_tracker->border_structure["south"]->name];
					cout<<GPS_tracker->description<<endl;
				}
			}
			// GO EAST
			else if(user_input == "e"){
				if(GPS_tracker->border_structure["east"] == NULL){
					cout<<"Can't go that way."<<endl;
				}
				else{
					GPS_tracker = world->room_structure[GPS_tracker->border_structure["east"]->name];
					cout<<GPS_tracker->description<<endl;
				}
			}
			// GO WEST
			else if(user_input == "w"){
				if(GPS_tracker->border_structure["west"] == NULL){
					cout<<"Can't go that way."<<endl;
				}
				else{
					GPS_tracker = world->room_structure[GPS_tracker->border_structure["west"]->name];
					cout<<GPS_tracker->description<<endl;
				}
			}
			// CHECK INVENTORY
			else if(user_input == "i"){
				if(player_inventory.empty() == 1){
					cout<<"Inventory: empty"<<endl;
				}
				else{
					cout<<"Inventory: ";
					for(int inventory_index = 0; inventory_index < player_inventory.size(); inventory_index++){
						if(inventory_index == (player_inventory.size() - 1)){
							cout<<player_inventory[inventory_index]<<endl;
						}
						else{
							cout<<player_inventory[inventory_index]<<", ";
						}
					}
				}
			}
			// TAKE (ITEM)
            else if(user_input == "take"){
                cout<<"ERROR: take what?"<<endl;
            }
			else if(user_input.find("take") != string::npos){
				istringstream iss(user_input);
				string word;
				while(iss >> word){
					if(word == "take"){
						// DO NOTHING
					}
					else{
						bool exist = false;
						for(int item_index = 0; item_index < GPS_tracker->item_structure.size(); item_index++){
							if(GPS_tracker->item_structure[item_index] == word){
								GPS_tracker->item_structure.erase(GPS_tracker->item_structure.begin() + item_index);
								exist = true;
								for(int container_index = 0; container_index < GPS_tracker->container_structure.size(); container_index++){
									for(int container_index2 = 0; container_index2 < world->container_structure[GPS_tracker->container_structure[container_index]]->item_structure.size(); container_index2++){
										if(world->container_structure[GPS_tracker->container_structure[container_index]]->item_structure[container_index2] == word){
											world->container_structure[GPS_tracker->container_structure[container_index]]->item_structure.erase(world->container_structure[GPS_tracker->container_structure[container_index]]->item_structure.begin() + container_index2);
										}
									}
								}
							}
						}
						if(exist == true){
							player_inventory.push_back(word);
							cout<<"Item "<<word<<" added to inventory."<<endl;
						}
						else{
							cout<<"ERROR: Item "<<word<<" is not in the room and also in the container."<<endl;
						}
					}
				}
			}
			// GAME OVER ASSERTION
			else if(user_input == "open exit"){
				if(GPS_tracker->trigger_structure.size() == 0){
					if(GPS_tracker->type == "exit"){
						GameOver = true;
					}
					else{
						cout<<"ERROR: You are currently not in exit room!"<<endl;
					}
				}
				else{
					if(GPS_tracker->type == "exit"){
						if(GPS_tracker->trigger_structure[0]->condition->owner == "inventory"){
							bool exist = false;
							for(int iin = 0; iin < player_inventory.size(); iin++){
								if(player_inventory[iin] == GPS_tracker->trigger_structure[0]->condition->object){
									exist = true;
								}
							}
							if(GPS_tracker->trigger_structure[0]->condition->has == "yes"){
								if(exist == true){
									cout<<GPS_tracker->trigger_structure[0]->print<<endl;
								}
								else{
									GameOver = true;
								}
							}
							else if(GPS_tracker->trigger_structure[0]->condition->has == "no"){
								if(exist == false){
									cout<<GPS_tracker->trigger_structure[0]->print<<endl;
								}
								else{
									GameOver = true;
								}
							}
						}
						if(GPS_tracker->trigger_structure[0]->condition->owner == ""){
							string condition_object = GPS_tracker->trigger_structure[0]->condition->object;
							string condition_status = GPS_tracker->trigger_structure[0]->condition->status;
							if(world->container_structure[condition_object]->status == condition_status){
								cout<<GPS_tracker->trigger_structure[0]->print<<endl;
							}
							else{
								GameOver = true;
							}
						}
					}
					else{
						cout<<"ERROR: You are currently not in exit room!"<<endl;
					}

				}
			}
            else if(user_input == "open"){
                cout<<"ERROR: open what?"<<endl;
            }
			// OPEN (CONTAINER)
			else if(user_input.find("open") != string::npos){
				istringstream iss(user_input);
				string word;
				bool already = false;
				while(iss >> word){
					if(word == "open"){
						// DO NOTHING
					}
					else{
						if(GPS_tracker->trigger_structure.size() == 0){
							bool exist = false;
							for(int index = 0; index < GPS_tracker->container_structure.size(); index++){
								if(GPS_tracker->container_structure[index] == word){
									exist = true;
									if(world->container_structure[word]->item_structure.size() == 0){
										cout<<word<<" is empty."<<endl;
									}
									else{
										cout<<word<<" contains ";
										for(int index2 = 0; index2 < world->container_structure[word]->item_structure.size(); index2++){
											if(index2 == (world->container_structure[word]->item_structure.size() - 1)){
												cout<<world->container_structure[word]->item_structure[index2];
												for(int index3 = 0; index3 < GPS_tracker->item_structure.size(); index3++){
													if(world->container_structure[word]->item_structure[index2] == GPS_tracker->item_structure[index3]){
														already = true;
													}
												}
												if(already == false){
													GPS_tracker->item_structure.push_back(world->container_structure[word]->item_structure[index2]);
													//world->container_structure[word]->item_structure.erase(world->container_structure[word]->item_structure.begin() + index2);
												}
											}
											else{
												cout<<world->container_structure[word]->item_structure[index2]<<", ";
												for(int index3 = 0; index3 < GPS_tracker->item_structure.size(); index3++){
													if(world->container_structure[word]->item_structure[index2] == GPS_tracker->item_structure[index3]){
														already = true;
													}
												}
												if(already == false){
													GPS_tracker->item_structure.push_back(world->container_structure[word]->item_structure[index2]);
													//world->container_structure[word]->item_structure.erase(world->container_structure[word]->item_structure.begin() + index2);
												}
											}
										}
										cout<<"."<<endl;
									}
								}
							}
							if(exist == false){
								cout<<"ERROR: There is no "<<word<<" in the room."<<endl;
							}
						}
						else if(GPS_tracker->trigger_structure.size() != 0){
							if(user_input == GPS_tracker->trigger_structure[0]->command){
								string condition_object = GPS_tracker->trigger_structure[0]->condition->object;
								string condition_status = GPS_tracker->trigger_structure[0]->condition->status;
								if(world->container_structure[condition_object]->status == condition_status){
									cout<<GPS_tracker->trigger_structure[0]->print<<endl;
								}
								else if(world->container_structure[condition_object]->status != condition_status){
									bool exist = false;
									for(int index = 0; index < GPS_tracker->container_structure.size(); index++){
										if(GPS_tracker->container_structure[index] == word){
											exist = true;
											if(world->container_structure[word]->item_structure.size() == 0){
												cout<<word<<" is empty."<<endl;
											}
											else{
												cout<<word<<" contains ";
												for(int index2 = 0; index2 < world->container_structure[word]->item_structure.size(); index2++){
													if(index2 == (world->container_structure[word]->item_structure.size() - 1)){
														cout<<world->container_structure[word]->item_structure[index2];
														for(int index3 = 0; index3 < GPS_tracker->item_structure.size(); index3++){
															if(world->container_structure[word]->item_structure[index2] == GPS_tracker->item_structure[index3]){
																already = true;
															}
														}
														if(already == false){
															GPS_tracker->item_structure.push_back(world->container_structure[word]->item_structure[index2]);
															//world->container_structure[word]->item_structure.erase(world->container_structure[word]->item_structure.begin() + index2);
														}
													}
													else{
														cout<<world->container_structure[word]->item_structure[index2]<<", ";
														for(int index3 = 0; index3 < GPS_tracker->item_structure.size(); index3++){
															if(world->container_structure[word]->item_structure[index2] == GPS_tracker->item_structure[index3]){
																already = true;
															}
														}
														if(already == false){
														GPS_tracker->item_structure.push_back(world->container_structure[word]->item_structure[index2]);
														//world->container_structure[word]->item_structure.erase(world->container_structure[word]->item_structure.begin() + index2);
														}
													}
												}
												cout<<"."<<endl;
											}
										}
									}
									if(exist == false){
										cout<<"ERROR: There is no "<<word<<" in the room."<<endl;
									}
								}
							}
							else if(user_input != GPS_tracker->trigger_structure[0]->command){
								bool exist = false;
								for(int index = 0; index < GPS_tracker->container_structure.size(); index++){
									if(GPS_tracker->container_structure[index] == word){
										exist = true;
										if(world->container_structure[word]->item_structure.size() == 0){
											cout<<word<<" is empty."<<endl;
										}
										else{
											cout<<word<<" contains ";
											for(int index2 = 0; index2 < world->container_structure[word]->item_structure.size(); index2++){
												if(index2 == (world->container_structure[word]->item_structure.size() - 1)){
													cout<<world->container_structure[word]->item_structure[index2];
													for(int index3 = 0; index3 < GPS_tracker->item_structure.size(); index3++){
														if(world->container_structure[word]->item_structure[index2] == GPS_tracker->item_structure[index3]){
															already = true;
														}
													}
													if(already == false){
														GPS_tracker->item_structure.push_back(world->container_structure[word]->item_structure[index2]);
														//world->container_structure[word]->item_structure.erase(world->container_structure[word]->item_structure.begin() + index2);
													}
												}
												else{
													cout<<world->container_structure[word]->item_structure[index2]<<", ";
													for(int index3 = 0; index3 < GPS_tracker->item_structure.size(); index3++){
														if(world->container_structure[word]->item_structure[index2] == GPS_tracker->item_structure[index3]){
															already = true;
														}
													}
													if(already == false){
														GPS_tracker->item_structure.push_back(world->container_structure[word]->item_structure[index2]);
														//world->container_structure[word]->item_structure.erase(world->container_structure[word]->item_structure.begin() + index2);
													}
												}
											}
											cout<<"."<<endl;
										}
									}
								}
								if(exist == false){
									cout<<"ERROR: There is no "<<word<<" in the room."<<endl;
								}
							}
						}
					}
				}
			}
            else if(user_input == "read"){
                cout<<"ERROR: read what?"<<endl;
            }
			// READ (ITEM)
			else if(user_input.find("read") != string::npos){
				istringstream iss(user_input);
				string word;
				while(iss >> word){
					if(word == "read"){
						// DO NOTHING
					}
					else{
						bool exist = false;
						for(int index = 0; index < player_inventory.size(); index++){
							if(player_inventory[index] == word){
								exist = true;
								if(world->item_structure[word]->writing == ""){
									cout<<"Nothing written."<<endl;
								}
								else{
									cout<<world->item_structure[word]->writing<<endl;
								}
							}
						}
						if(exist == false){
							cout<<"ERROR: "<<word<<" is not in the inventory"<<endl;
						}

					}
				}
			}
            else if(user_input == "drop"){
                cout<<"ERROR: drop what?"<<endl;
            }
			// DROP (ITEM)
			else if(user_input.find("drop") != string::npos){
				istringstream iss(user_input);
				string word;
				while(iss >> word){
					if(word == "drop"){
						// DO NOTHING
					}
					else{
						bool exist = false;
						for(int index = 0; index < player_inventory.size(); index++){
							if(player_inventory[index] == word){
								exist = true;
								player_inventory.erase(player_inventory.begin() + index);
								GPS_tracker->item_structure.push_back(word);
								cout<<word<<" dropped."<<endl;
							}
						}
						if(exist == false){
							cout<<"ERROR: "<<word<<" is not in your inventory"<<endl;
						}
					}
				}
			}
            else if(user_input == "put"){
                cout<<"ERROR: put what in what?"<<endl;
            }
			// PUT (ITEM) IN (CONTAINER)
			else if(user_input.find("put") != string::npos){
				istringstream iss(user_input);
				string word;
				bool put_enable = false;
				bool in_enable = false;
				bool item_exist = false;
				bool container_exist = false;
				bool accept_possible = false;
				bool target_enable = false;
				bool update_enable = false;
				string target_item;
				int target_index;
				while(iss >> word){
					if(word == "put"){
						put_enable = true;
					}
					else if(word == "in"){
						in_enable = true;
					}
					else{
						if(put_enable == true){
							for(int index = 0; index < player_inventory.size(); index++){
								if(player_inventory[index] == word){
									item_exist = true;
									target_item = word;
									target_index = index;
								}
							}
							put_enable = false;
						}
						else if(in_enable == true){
							for(int index2 = 0; index2 < GPS_tracker->container_structure.size(); index2++){
								if(GPS_tracker->container_structure[index2] == word){
									container_exist = true;
									if(item_exist == true){
										if(world->container_structure[word]->accept_structure.size() == 0){
											accept_possible = true;
											player_inventory.erase(player_inventory.begin() + target_index);
											world->container_structure[word]->item_structure.push_back(target_item);
											GPS_tracker->item_structure.push_back(target_item);
											cout<<"Item "<<target_item<<" added to "<<word<<"."<<endl;
											if(world->container_structure[word]->trigger_structure.size() != 0){
												cout<<world->container_structure[word]->trigger_structure[0]->print<<endl;
												if(world->container_structure[word]->trigger_structure[0]->action_structure[0].find("Update") != string::npos){
													istringstream iss(world->container_structure[word]->trigger_structure[0]->action_structure[0]);
													string word2;
													while(iss >> word2){
														if(word2 == "Update"){
															target_enable = true;
														}
														else if(word2 == "to"){
															update_enable = true;
														}
														else{
															if(target_enable == true){
																target_item = word2;
																target_enable = false;
															}
															else if(update_enable == true){
																world->container_structure[target_item]->status = word2;
															}
														}
													}
												}
											}
										}
										else{
											for(int index3 = 0; index3 < world->container_structure[word]->accept_structure.size(); index3++){
												if(world->container_structure[word]->accept_structure[index3] == target_item){
													accept_possible = true;
													player_inventory.erase(player_inventory.begin() + target_index);
													world->container_structure[word]->item_structure.push_back(target_item);
													cout<<"Item "<<target_item<<" added to "<<word<<"."<<endl;
													if(world->container_structure[word]->trigger_structure.size() != 0){
														cout<<world->container_structure[word]->trigger_structure[0]->print<<endl;
														for(int index20 = 0; index20 < world->container_structure[word]->trigger_structure[0]->action_structure.size(); index20++){
															if(world->container_structure[word]->trigger_structure[0]->action_structure[index20].find("Update") != string::npos){
																istringstream iss(world->container_structure[word]->trigger_structure[0]->action_structure[index20]);
																string word2;
																while(iss >> word2){
																	if(word2 == "Update"){
																		target_enable = true;
																	}
																	else if(word2 == "to"){
																		update_enable = true;
																	}
																	else{
																		if(target_enable == true){
																			target_item = word2;
																			target_enable = false;
																		}
																		else if(update_enable == true){
																			world->container_structure[target_item]->status = word2;
																		}
																	}
																}
															}
															if(world->container_structure[word]->trigger_structure[0]->action_structure[index20].find("Delete") != string::npos){
																istringstream iss(world->container_structure[word]->trigger_structure[0]->action_structure[index20]);
																string word20;
																while(iss >> word20){
																	if(word20 == "Delete"){
																		// DO NOTHING
																	}
																	else{
																		for(int dui = 0; dui < world->container_structure[word]->item_structure.size(); dui++){
																			if(world->container_structure[word]->item_structure[dui] == word20){
																				world->container_structure[word]->item_structure.erase(world->container_structure[word]->item_structure.begin() + dui);
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
										if(accept_possible == false){
											cout<<"ERROR: You can't put "<<target_item<<" in "<<word<<" because it is not acceptable"<<endl;
										}
									}
								}
							}
							in_enable = false;
						}
					}
				}
				if(item_exist == false){
					cout<<"ERROR: Item is not in your inventory."<<endl;
				}
				if(container_exist == false){
					cout<<"ERROR: Container is not in the room."<<endl;
				}
			}
			else if(user_input == "turn on"){
				cout<<"ERROR: turn on what?"<<endl;
			}
			// TURN ON (ITEM)
			else if(user_input.find("turn on") != string::npos){
				istringstream iss(user_input);
				string word;
				string target_item;
				bool target_enable = false;
				bool update_enable = false;
				while(iss >> word){
					if(word == "turn"){
						// DO NOTHING
					}
					else if(word == "on"){
						// DO NOTHING
					}
					else{
						bool exist = false;
						for(int index = 0; index < player_inventory.size(); index++){
							if(player_inventory[index] == word){
								exist = true;
								cout<<"You activate the "<<word<<endl;
								cout<<world->item_structure[word]->turnon->print<<endl;
								if(world->item_structure[word]->turnon->action.find("Update") != string::npos){
									istringstream iss(world->item_structure[word]->turnon->action);
									string word2;
									while(iss >> word2){
										if(word2 == "Update"){
											target_enable = true;
										}
										else if(word2 == "to"){
											update_enable = true;
										}
										else{
											if(target_enable == true){
												target_item = word2;
												target_enable = false;
											}
											else if(update_enable == true){
												for(int lec1 = 0; lec1 < GPS_tracker->container_structure.size(); lec1++){
													if(GPS_tracker->container_structure[lec1] == target_item){
														world->container_structure[target_item]->status = word2;
													}
												}
												for(int lec2 = 0; lec2 < world->item_structure.size(); lec2++){
													if(GPS_tracker->item_structure.size() != 0){
														if(GPS_tracker->item_structure[lec2] == target_item){
															world->item_structure[target_item]->status = word2;
														}
													}
												}
												for(int lec3 = 0; lec3 < player_inventory.size(); lec3++){
													if(player_inventory[lec3] == target_item){
														world->item_structure[player_inventory[lec3]]->status = word2;
													}
												}
											}
										}
									}
								}
								if(world->item_structure[word]->turnon->action.find("drop") != string::npos){
									istringstream iss(world->item_structure[word]->turnon->action);
									string word2;
									while(iss >> word2){
										if(word2 == "drop"){
											// DO NOTHING
										}
										else{
											for(int index = 0; index < player_inventory.size(); index++){
												if(player_inventory[index] == word2){
													player_inventory.erase(player_inventory.begin() + index);
													GPS_tracker->item_structure.push_back(word2);
													cout<<word<<" dropped."<<endl;
												}
											}
										}
									}
								}
							}
						}
						if(exist == false){
							cout<<"ERROR: Item is not in your inventory"<<endl;
						}
					}
				}
			}
            else if(user_input == "attack"){
                cout<<"ERROR: attack what with what?"<<endl;
            }
			// ATTACK (CREATURE) WITH (ITEM)
			else if(user_input.find("attack") != string::npos){
				istringstream iss(user_input);
				string word;
				string word2;
				bool creature_enable = false;
				bool item_enable = false;
				bool creature_exist = false;
				bool item_exist = false;
				bool attackable = false;
				bool add_enable = false;
				bool to_enable = false;
				Room * location_save = NULL;
				string target_creature;
				string target_item;
				while(iss >> word){
					if(word == "attack"){
						creature_enable = true;
					}
					else if(word == "with"){
						item_enable = true;
					}
					else{
						if(creature_enable == true){
							for(int index = 0; index < GPS_tracker->creature_structure.size(); index++){
								if(GPS_tracker->creature_structure[index] == word){
									creature_exist = true;
									target_creature = word;
								}
							}
							creature_enable = false;
						}
						else if(item_enable == true){
							for(int index2 = 0; index2 < player_inventory.size(); index2++){
								if(player_inventory[index2] == word){
									item_exist = true;
									if(creature_exist == false){
										// DO NOTHING
									}
									else if(world->creature_structure[target_creature]->attack == NULL){
										// DO NOTHING
										for(int vul_i = 0; vul_i < world->creature_structure[target_creature]->vulnerability_structure.size(); vul_i++){
											if(world->creature_structure[target_creature]->vulnerability_structure[vul_i] == word){
												attackable = true;
												if(world->creature_structure[target_creature]->trigger_structure.size() == 1){
													if(world->creature_structure[target_creature]->trigger_structure[0]->command == user_input){
														if(world->item_structure[world->creature_structure[target_creature]->trigger_structure[0]->condition->object]->status ==  world->creature_structure[target_creature]->trigger_structure[0]->condition->status){
															// HANDLED BY TRIGGER METHOD BELOW
														}
														else{
															cout<<"You assault the "<<target_creature<<" with the "<<word<<"."<<endl;
														}
													}
													else{
														cout<<"You assault the "<<target_creature<<" with the "<<word<<"."<<endl;
													}
												}
												if(world->creature_structure[target_creature]->trigger_structure.size() == 2){
													if(world->creature_structure[target_creature]->trigger_structure[0]->command == user_input){
														if(world->item_structure[world->creature_structure[target_creature]->trigger_structure[0]->condition->object]->status ==  world->creature_structure[target_creature]->trigger_structure[0]->condition->status){
															// HANDLED BY TRIGGER METHOD BELOW
														}
														else{
															cout<<"You assault the "<<target_creature<<" with the "<<word<<"."<<endl;
														}
													}
													else if(world->creature_structure[target_creature]->trigger_structure[1]->command == user_input){
														if(world->item_structure[world->creature_structure[target_creature]->trigger_structure[1]->condition->object]->status ==  world->creature_structure[target_creature]->trigger_structure[1]->condition->status){
															// HANDLED BY TRIGGER METHOD BELOW
														}
														else{
															cout<<"You assault the "<<target_creature<<" with the "<<word<<"."<<endl;
														}

													}

												}
											}
										}
										if(attackable == false){
											Error = true;
											cout<<"ERROR: You can't attack "<<target_creature<<" with the "<<word<<"."<<endl;
										}
									}
									else if(world->creature_structure[target_creature]->attack->condition == NULL){
										for(int vul_i = 0; vul_i < world->creature_structure[target_creature]->vulnerability_structure.size(); vul_i++){
											if(world->creature_structure[target_creature]->vulnerability_structure[vul_i] == word){
												attackable = true;
												cout<<"You assault the "<<target_creature<<" with the "<<word<<"."<<endl;
												if(world->creature_structure[target_creature]->attack->print != ""){
													cout<<world->creature_structure[target_creature]->attack->print<<endl;
												}
												for(int index3 = 0; index3 < world->creature_structure[target_creature]->attack->action_structure.size(); index3++){
													if(world->creature_structure[target_creature]->attack->action_structure[index3].find("Add") != string::npos){
														istringstream iss(world->creature_structure[target_creature]->attack->action_structure[index3]);
														while(iss >> word2){
															if(word2 == "Add"){
																add_enable = true;
															}
															else if(word2 == "to"){
																to_enable = true;
															}
															else{
																if(add_enable == true){
																	target_item = word2;
																	add_enable = false;
																}
																else if(to_enable == true){
																	if(world->item_structure[target_item] != NULL){
																		world->room_structure[word2]->item_structure.push_back(target_item);
																	}
																	if(world->creature_structure[target_item] != NULL){
																		world->room_structure[word2]->creature_structure.push_back(target_item);
																	}
																	to_enable = false;
																}
															}
														}
													}
													if(world->creature_structure[target_creature]->attack->action_structure[index3].find("Delete") != string::npos){
														istringstream iss(world->creature_structure[target_creature]->attack->action_structure[index3]);
														while(iss >> word2){
															if(word2 == "Delete"){
																// DO NOTHING
															}
															else{
																if(location_save != NULL){
																	for(int index4 = 0; index4 < location_save->creature_structure.size(); index4++){
																		if(location_save->creature_structure[index4] == word2){
																			location_save->creature_structure.erase(location_save->creature_structure.begin() + index4);
																		}
																	}
																}
																else{
																	for(int index4 = 0; index4 < GPS_tracker->creature_structure.size(); index4++){
																		if(GPS_tracker->creature_structure[index4] == word2){
																			GPS_tracker->creature_structure.erase(GPS_tracker->creature_structure.begin() + index4);
																		}
																	}
																}
															}
														}
													}
													if(world->creature_structure[target_creature]->attack->action_structure[index3] == "s"){
														location_save = GPS_tracker;
														GPS_tracker = world->room_structure[GPS_tracker->border_structure["south"]->name];
														cout<<GPS_tracker->description<<endl;
													}
													if(world->creature_structure[target_creature]->attack->action_structure[index3] == "Game Over"){
														GameOver = true;
													}
												}
											}
										}
										if(attackable == false){
											Error = true;
											cout<<"ERROR: You can't attack "<<target_creature<<" with the "<<word<<"."<<endl;
										}
									}
									else if(creature_exist == true && world->item_structure[world->creature_structure[target_creature]->attack->condition->object]->status == world->creature_structure[target_creature]->attack->condition->status){
										if(world->creature_structure[target_creature]->vulnerability_structure[0] == word){
											cout<<"You assault the "<<target_creature<<" with the "<<word<<"."<<endl;
											cout<<world->creature_structure[target_creature]->attack->print<<endl;
											for(int index3 = 0; index3 < world->creature_structure[target_creature]->attack->action_structure.size(); index3++){
												if(world->creature_structure[target_creature]->attack->action_structure[index3].find("Add") != string::npos){
													istringstream iss(world->creature_structure[target_creature]->attack->action_structure[index3]);
													while(iss >> word2){
														if(word2 == "Add"){
															add_enable = true;
														}
														else if(word2 == "to"){
															to_enable = true;
														}
														else{
															if(add_enable == true){
																target_item = word2;
																add_enable = false;
															}
															else if(to_enable == true){
																world->room_structure[word2]->item_structure.push_back(target_item);
																to_enable = false;
															}
														}
													}
												}
												if(world->creature_structure[target_creature]->attack->action_structure[index3].find("Delete") != string::npos){
													istringstream iss(world->creature_structure[target_creature]->attack->action_structure[index3]);
													while(iss >> word2){
														if(word2 == "Delete"){
															// DO NOTHING
														}
														else{
															for(int index4 = 0; index4 < GPS_tracker->creature_structure.size(); index4++){
																if(GPS_tracker->creature_structure[index4] == word2){
																	GPS_tracker->creature_structure.erase(GPS_tracker->creature_structure.begin() + index4);
																}
															}
														}
													}
												}
											}
										}
										else{
											Error = true;
											cout<<"ERROR: You can't attack "<<target_creature<<" with the "<<word<<"."<<endl;
										}
									}
								}
							}
							item_enable = false;
						}
					}
				}
				if(creature_exist == true){
					if(world->creature_structure[target_creature]->attack != NULL){
						if(world->creature_structure[target_creature]->attack->condition != NULL){
							if(world->item_structure[world->creature_structure[target_creature]->attack->condition->object]->status != world->creature_structure[target_creature]->attack->condition->status){
								cout<<"ERROR: item might have to be turned on because status is not in correct condition"<<endl;
							}
						}
					}
				}
				if(creature_exist == false){
					cout<<"ERROR: There is no such creature in this room."<<endl;
				}
				if(item_exist == false){
					cout<<"ERROR: There is no such item in your inventory."<<endl;
				}
			}
			// QUIT COMMAND
			else if(user_input == "quit"){
				cout<<"Quitting the game."<<endl;
				return;
			}
			// INVALID COMMAND DETECTED
			else{
				cout<<"ERROR: Wrong command! Check if there is a typo!"<<endl;
			}

			//CHECKING CREATURE TRIGGER
			if(GPS_tracker->creature_structure.size() != 0){
				for(int iii = 0; iii < GPS_tracker->creature_structure.size(); iii++){
					if(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure.size() != 0){
						for(int final = 0; final < world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure.size(); final++){
							if(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->command == user_input){
								if(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->type == "single"){
									string condition_object = world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->condition->object;
									string condition_status = world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->condition->status;
									if(world->item_structure[condition_object]->status == condition_status){
										cout<<world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->print<<endl;
										world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->type = "done";
										for(int tin = 0; tin < world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->action_structure.size(); tin++){
											if(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->action_structure[tin].find("take") != string::npos){
												istringstream iss(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->action_structure[tin]);
												string word10;
												bool is_in_inventory = false;
												while(iss >> word10){
													if(word10 == "take"){
														// DO NOTHING
													}
													else{
														for(int iin = 0; iin < GPS_tracker->item_structure.size(); iin++){
															if(word10 == GPS_tracker->item_structure[iin]){
																is_in_inventory = true;
																player_inventory.push_back(word10);
																cout<<"Item "<<word10<<" added to inventory"<<endl;
															}
														}
														if(is_in_inventory == false){
															cout<<"ERROR: Item "<<word10<<" is not in the room."<<endl;
														}
													}
												}
											}
											if(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->action_structure[tin].find("Update") != string::npos){
												istringstream iss(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->action_structure[tin]);
												string word10;
												bool item_enable = false;
												bool status_enable = false;
												string target_item;
												while(iss >> word10){
													if(word10 == "Update"){
														item_enable = true;
													}
													else if(word10 == "to"){
														status_enable = true;
													}
													else{
														if(item_enable == true){
															target_item = word10;
															item_enable = false;
														}
														else if(status_enable == true){
															world->container_structure[target_item]->status = word10;
														}
													}
												}
											}
											if(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->action_structure[tin].find("attack") != string::npos){
												istringstream iss(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->action_structure[tin]);
												string word10;
												bool target_enable = false;
												bool item_enable = false;
												string target_creature;
												while(iss >> word10){
													if(word10 == "attack"){
														target_enable = true;
													}
													else if(word10 == "with"){
														item_enable = true;
													}
													else{
														if(target_enable == true){
															target_creature = word10;
															target_enable = false;
														}
														else if(item_enable == true){
															cout<<"You assault the "<<target_creature<<" with "<<word10<<endl;
														}
													}
												}
											}
											if(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->action_structure[tin] == "Game Over"){
												GameOver = true;
											}
										}
									}
								}
							}
							else{
								if(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->type == "single"){
									if(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->command == ""){
										string condition_object = world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->condition->object;
										string condition_status = world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->condition->status;
										if(world->item_structure[condition_object]->status == condition_status){
											cout<<world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->print<<endl;
											world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->type = "done";
										}
									}
									else{
										// DO NOTHING
									}
								}
								else{
									bool OKOK = false;
									if(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->condition->owner == "inventory"){
										for(int iin = 0; iin < player_inventory.size(); iin++){
											if(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->condition->object == player_inventory[iin]){
												OKOK = true;
											}
										}
									}
									if(OKOK == true && Error == false){
										cout<<world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->print<<endl;
										for(int tin = 0; tin < world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->action_structure.size(); tin++){
											if(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->action_structure[tin].find("Update") != string::npos){
												istringstream iss(world->creature_structure[GPS_tracker->creature_structure[iii]]->trigger_structure[final]->action_structure[tin]);
												string word10;
												bool item_enable = false;
												bool status_enable = false;
												string target_item;
												while(iss >> word10){
													if(word10 == "Update"){
														item_enable = true;
													}
													else if(word10 == "to"){
														status_enable = true;
													}
													else{
														if(item_enable == true){
															target_item = word10;
															item_enable = false;
														}
														else if(status_enable == true){
															world->item_structure[target_item]->status = word10;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		return;
	}
};



#endif /* LCU_HPP_ */
