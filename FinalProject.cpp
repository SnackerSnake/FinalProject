//============================================================================
// Name        : FinalProject.cpp
// Author      : David
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <random>
using namespace std;

//These variables need to be global because they are used by every function.
	  int lifePointsPlayer=8000;
	  int lifePointsOpponent=8000;

	  int drawForPlayer=6;
	  int drawForAI=6;


//Initialize deck, hand, and playing field
	  int deck[40] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40};
	  int hand[40] = {};
	  int enemyDeck[35]= {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
	  int enemyHand[35]={};

	  int playerMonsterZones[5]={};
	  int opponentMonsterZones[5]={};
	  int playerSpellAndTrapZones[5]={};
	  int opponentSpellAndTrapZones[5]={};

	  int playerMonsterZonesBattlePosition[5]={};
	  int opponentMonsterZonesBattlePosition[5]={};

	  //List of cards
	  string cardList[40]={"Blue-Eyes White Dragon", "Cosmo Queen", "Summoned Skull", "Cyber-Tech Alligator", "Alexandrite Dragon", "Gene-Warped Warwolf",
			  "Luster Dragon", "Angel Trumpeter", "Archfiend Soldier", "Vorse Raider", "Gemini Elf", "Alien Shocktrooper", "Mechanicalchaser", "Blazing Inpachi",
			  "Neo Bug", "Dark Blade", "Dunames Dark Witch", "7 Colored Fish", "Giant Red Seasnake", "Sky Scout", "Master Kyonshee", "Beta the Magnet Warrior",
			  "The Dragon Dwelling in the Cave", "Hunter Dragon", "Giant Soldier of Stone", "Man-Eater Bug", "Noble Knight Artorigus", "Shining Abyss", "Mist Valley Watcher",
			  "Inpachi", "Robotic Knight", "Gamma the Magnet Warrior", "Kanan the Swordmistress", "Humanoid Slime", "Elemental Hero Clayman", "Raigeki",
			  "Pot of Greed", "Dian Keto the Cure Master", "Widespread Ruin", "Magic Cylinder"};

	  //Information for every card in the game
	  string cardInformation[40]={"Blue-Eyes White Dragon: 3000ATK 2500DEF LEVEL 8", "Cosmo Queen: 2900ATK 2450DEF LEVEL 8", "Summoned Skull: 2500ATK 1200DEF LEVEL 6", "Cyber-Tech Alligator: 2500ATK 1600DEF LEVEL 5", "Alexandrite Dragon: 2000ATK 100DEF", "Gene-Warped Warwolf: 2000ATK 100DEF",
	  			  "Luster Dragon: 1900ATK 1600DEF", "Angel Trumpeter: 1900ATK 1600DEF", "Archfiend Soldier: 1900ATK 1500DEF", "Vorse Raider: 1900ATK 1200DEF", "Gemini Elf: 1900ATK 900DEF", "Alien Shocktrooper: 1900ATK 800DEF", "Mechanicalchaser: 1850ATK 800DEF", "Blazing Inpachi: 1850ATK 0DEF",
	  			  "Neo Bug: 1800ATK 1700DEF", "Dark Blade: 1800ATK 1500DEF", "Dunames Dark Witch: 1800ATK 1050DEF", "7 Colored Fish: 1800ATK 800DEF", "Giant Red Seasnake: 1800ATK 800DEF", "Sky Scout: 1800ATK 600DEF", "Master Kyonshee: 1750ATK 1000DEF", "Beta the Magnet Warrior: 1700ATK 1600DEF",
	  			  "The Dragon Dwelling in the Cave: 1300ATK 2000DEF", "Hunter Dragon: 1700ATK 100DEF", "Giant Soldier of Stone: 1300ATK 2000DEF", "Man-Eater Bug: 450ATK 600DEF", "Noble Knight Artorigus: 1800ATK 1800DEF", "Shining Abyss: 1600ATK 1800DEF", "Mist Valley Watcher: 1500ATK 1900DEF",
				  "Inpachi: 1600ATK 1800DEF", "Robotic Knight: 1600ATK 1800DEF", "Gamma the Magnet Warrior: 1500ATK 1800DEF", "Kanan the Swordmistress: 1400ATK 1400DEF", "Humanoid Slime: 800ATK 2000DEF", "Elemental Hero Clayman: 800ATK 2000DEF", "Raigeki: Destroy all monsters your opponent controls.",
				  "Pot of Greed: Draw 2 cards.", "Dian Keto the Cure Master: Increase your Life Points by 1,000.", "Widespread Ruin: When an opponent's monster declares an attack: Destroy the 1 Attack Position monster your opponent controls with the highest attack.", "Magic Cylinder: When an opponent's monster declares an attack: Target the attacking monster: negate the attack, and if you do, inflict damage to your opponent equal to its ATK."};

	  //Each monster's attack points
	  int cardAttack[40]={3000, 2900, 2500, 2500, 2000, 2000, 1900, 1900, 1900, 1900, 1900, 1900, 1850, 1850,
			  1800, 1800, 1800, 1800, 1800, 1800, 1750, 1700, 1300, 1700, 1300, 450, 1800, 1600, 1500, 1600, 1600, 1500, 1400, 800, 800};

	  //Each monster's defense points
	  	  int cardDefense[40]={2500, 2450, 1200, 1600, 100, 100, 1600, 1600, 1500, 1200, 900, 800, 800, 0, 1700,
	  			  1500, 1050, 800, 800, 600, 1000, 1600, 2000, 100, 2000, 600, 1800, 1800, 1900, 1900, 1800, 1800, 1400, 2000, 2000};

	  //If the human player summoned a monster, change to 1. Otherwise 0.
	  int didPlayerSummon=0;

	  //Checks if human player used a trap.
	  int trapUsed=0;

//Check if the human player won.
void checkVictoryPlayer(int LP){
	if (LP<=0){
		cout<<"Opponent's Life Points: "<< LP <<endl;
		cout<<"You won!"<<endl;
		exit(0);
	}
}

//Check if the AI player won.
void checkVictoryOpponent(int LP){
	if (LP<=0){
		cout<<"Your Life Points: "<< LP <<endl;
		cout<<"You lost."<<endl;
		exit(0);
	}
}

//Draws the player's hand for them.
void drawHand() {
	for (int index = 0; index < 6; ++index) {
		hand[index]=deck[index];
	  }
}

//Draws a card for the player.
void drawOne() {
		if(drawForPlayer==40){
			return;
		}

		for (int index = 0; index < 40; ++index) {
			if (hand[index]==0){
				hand[index]=deck[drawForPlayer];
				drawForPlayer+=1;
				return;

				}}

}


//Shows what cards the player has in their hand
void cardsInHand() {
	cout<<"Your Hand: ";
	for (int index = 0; index < 40; ++index) {
		if (hand[index]!=0){
			int number=hand[index]-1;
			cout<<cardList[number];
			cout<<", ";
        }
	  }
	  cout<<endl;
}

//Draws the AI's hand.
void drawEnemyHand() {
	for (int index = 0; index < 6; ++index) {
		enemyHand[index]=enemyDeck[index];
	  }
}

//Test Function
void cardsInEnemyHand() {
	cout<<"AI Hand (TEST CODE): ";
	for (int index = 0; index < 35; ++index) {
		if (enemyHand[index]!=0){
			int number=enemyHand[index]-1;
			cout<<cardList[number];
			cout<<", ";
        }
	  }
	  cout<<endl;
}

//Draws a card for the AI opponent.
void drawOneAI() {
		if(drawForAI==35){
			return;
		}

		for (int index = 0; index < 40; ++index) {
			if (enemyHand[index]==0){
				enemyHand[index]=enemyDeck[drawForAI];
				drawForAI+=1;
				return;
					}}

}



void checkTrap(){
	int activateTrapInput=0;
	int highestAttack=0;
	int thisOne=0;

	if (playerSpellAndTrapZones[0]==39 || playerSpellAndTrapZones[1]==39){
		cout<<"Activate your trap, Widespread Ruin? Press 1 for yes; 0 for no."<<endl;
		cin>>activateTrapInput;
		if (activateTrapInput==1){
			for (int index = 0; index < 5; ++index){
				if (opponentMonsterZones[index]!=0){
					if (cardAttack[opponentMonsterZones[index]-1]>highestAttack){
						highestAttack=cardAttack[opponentMonsterZones[index]-1];
						thisOne=index;
										}
					}

	}
			opponentMonsterZones[thisOne]=0;
			trapUsed=1;
			//Remove trap after use.
			if (playerSpellAndTrapZones[0]==39){
				playerSpellAndTrapZones[0]=0;
			}
			if (playerSpellAndTrapZones[1]==39){
							playerSpellAndTrapZones[1]=0;
						}
		}
	}
	if (playerSpellAndTrapZones[0]==40 || playerSpellAndTrapZones[1]==40){
		cout<<"Activate your trap, Magic Cylinder? Press 1 for yes; 0 for no."<<endl;
				cin>>activateTrapInput;
				if (activateTrapInput==1){
							for (int index = 0; index < 5; ++index){
								if (opponentMonsterZones[index]!=0){
									if (cardAttack[opponentMonsterZones[index]-1]>highestAttack){
										highestAttack=cardAttack[opponentMonsterZones[index]-1];
										//thisOne=index;
														}
									}

					}
							lifePointsOpponent-=highestAttack;
							cout<<"Opponent LP: "<<lifePointsOpponent<<endl;
							checkVictoryPlayer(lifePointsOpponent);

							trapUsed=1;

							//Remove trap after use.
							if (playerSpellAndTrapZones[0]==40){
								playerSpellAndTrapZones[0]=0;
										}
							if (playerSpellAndTrapZones[1]==40){
								playerSpellAndTrapZones[1]=0;
													}
						}
	}

}


//Shows the playing field.
//X stand for no cards. ? stand for face down card
//If the element has a number, print the card name.
void showField(){
	int number=-1;

	cout<<"[";
	for (int index = 0; index < 5; ++index){
		if (opponentSpellAndTrapZones[index]==0){
			cout<<"X ";
	}
	}
	cout<<endl;
	for (int index = 0; index < 5; ++index){
		if (opponentMonsterZones[index]==0){
			cout<<"X ";
			}
		else if (opponentMonsterZones[index]>0 && opponentMonsterZones[index]<=40){
					number=opponentMonsterZones[index];
					cout<<cardList[number-1];
					//1 for attack 2 for defense
					if(opponentMonsterZonesBattlePosition[index]==1){
							cout<<"(ATK)";
						}
					else if(opponentMonsterZonesBattlePosition[index]==2){
							cout<<"(DEF)";
								}
					cout<<" ";
				}
	}
	cout<<endl;
	for (int index = 0; index < 5; ++index){

		if (playerMonsterZones[index]==0){
			cout<<"X ";
			}
		else if (playerMonsterZones[index]>0 && playerMonsterZones[index]<=40){
			number=playerMonsterZones[index];
			cout<<cardList[number-1];
			//1 for attack 2 for defense
			if(playerMonsterZonesBattlePosition[index]==1){
				cout<<"(ATK)";
			}
			else if(playerMonsterZonesBattlePosition[index]==2){
				cout<<"(DEF)";
			}
			cout<<" ";
		}
	}
	cout<<endl;
	for (int index = 0; index < 5; ++index){
		if (playerSpellAndTrapZones[index]==0){
			cout<<"X ";
					}
		else{
			cout<<"? "; }
	}
	cout<<"]"<<endl;
}

//Calculates who wins a battle
//Attacking vs. defending
//assuming human player is attacking
void calculateBattle(int monsterOne, int monsterTwo){
	int attackOne=cardAttack[monsterOne-1];
	int attackTwo=cardAttack[monsterTwo-1];
	int defenseOne=cardDefense[monsterOne-1];

	//Check for attack or defense mode
		for (int index = 0; index < 5; ++index) {
			if (playerMonsterZones[index]==monsterOne){

				//ATTACK MODE PLAYER 1
			if (playerMonsterZonesBattlePosition[index]==1){
				//cout<<"TESTING: Attack Mode"<<endl;

				cout<<cardList[monsterOne-1]<<"(ATK): "<<attackOne<<endl;
				cout<<cardList[monsterTwo-1]<<"(ATK): "<<attackTwo<<endl;

				//Destroy attacked monster and reduce opponent's life points
					if(attackOne>attackTwo){
						lifePointsOpponent-=attackOne-attackTwo;

						//Destroy attacked monster
								for (int index = 0; index < 5; ++index){
										if (opponentMonsterZones[index]==monsterTwo){
											opponentMonsterZones[index]=0;
											}
																		}
								//Check if human player won
								checkVictoryPlayer(lifePointsOpponent);
					}

					//Destroy both monsters
					else if(attackOne==attackTwo){
						//Destroy attacking monster
						for (int index = 0; index < 5; ++index){
										if (playerMonsterZones[index]==monsterOne){
											playerMonsterZones[index]=0;
											}
																		}

						//Destroy attacked monster
						for (int index = 0; index < 5; ++index){
								if (opponentMonsterZones[index]==monsterTwo){
									opponentMonsterZones[index]=0;
									}
																}
					}
					else if(attackOne<attackTwo){
						lifePointsPlayer-=attackTwo-attackOne;

						//Destroy attacking monster
						for (int index = 0; index < 5; ++index){
							if (playerMonsterZones[index]==monsterOne){
							playerMonsterZones[index]=0;
													}
									}
						//Check if AI won
						checkVictoryOpponent(lifePointsPlayer);

					}
			}
			//DEFENSE MODE PLAYER 1
			else if(playerMonsterZonesBattlePosition[index]==2){
				//cout<<"TESTING: Defense Mode"<<endl;

				cout<<cardList[monsterOne-1]<<"(DEF): "<<defenseOne<<endl;
				cout<<cardList[monsterTwo-1]<<"(ATK): "<<attackTwo<<endl;
				//Reduce opponent's life points
									if(defenseOne>attackTwo){
										lifePointsOpponent-=defenseOne-attackTwo;
										//Check if human won.
										checkVictoryPlayer(lifePointsOpponent);

									}

									//Neither monster is destroyed. LP stays the same.
									else if(defenseOne==attackTwo){
										cout<<"Neither monster is destroyed because the ATK equals the DEF."<<endl;
									}
									//Destroy attacked monster
									else if(defenseOne<attackTwo){

										for (int index = 0; index < 5; ++index){
											if (playerMonsterZones[index]==monsterOne){
											playerMonsterZones[index]=0;
																	}
													}

									}

			}
			}
		}



	showField();
	cout<<"Your Life Points: "<<lifePointsPlayer<<endl;
	cout<<"Your Opponent's Points: "<<lifePointsOpponent<<endl;

}

//This function handles the AI opponent's turn.
void AITurn(){

	//Summoning Monsters
	int highestAttack=0;
	int monsterWithHighestAttack;
	int countMonsterZones=0;
	int number;
	int indexOfMonster;

	int checkForTwoEnemyMonsters=0;
	int checkForOneEnemyMonsters=0;

	int checkForTwoEnemyTributes=0;
	int checkForOneEnemyTributes=0;

	for (int index = 0; index < 35; ++index) {
			if (enemyHand[index]!=0){
				number=enemyHand[index];
				//cout<<"TEST Card Attack Number AHHH:"<<cardAttack[number-1]<<endl;
				//Checking for highest attack (and if two tributes is possible)
				if(cardAttack[number-1]>highestAttack && cardAttack[number-1]>2500){
					for (int index = 0; index < 5; ++index) {
						if(opponentMonsterZones[index]!=0){
							checkForTwoEnemyMonsters+=1;
						}
					}
					if (checkForTwoEnemyMonsters>=2){
						highestAttack=cardAttack[number-1];
						//cout<<highestAttack<<endl; //TEST CODE
						monsterWithHighestAttack=number;
						indexOfMonster=index;
						//get rid of two monsters
						for (int index = 0; index < 5; ++index) {
							if(opponentMonsterZones[index]!=0){
								opponentMonsterZones[index]=0;
								opponentMonsterZonesBattlePosition[index]=0;
								checkForTwoEnemyTributes+=1;
							}
							if(checkForTwoEnemyTributes==2){
								//index=5;
								break;
														}

												}
					}
					}
				//check for highest attack (and if one tribute is possible)
				else if(cardAttack[number-1]>highestAttack && cardAttack[number-1]==2500){
					for (int index = 0; index < 5; ++index) {
						if(opponentMonsterZones[index]!=0){
							checkForOneEnemyMonsters+=1;
											}
										}
					if (checkForOneEnemyMonsters>=1){
						highestAttack=cardAttack[number-1];
											//cout<<highestAttack<<endl; //TEST CODE
						monsterWithHighestAttack=number;
						indexOfMonster=index;

						//get rid of one monsters
						for (int index = 0; index < 5; ++index) {
							if(opponentMonsterZones[index]!=0){
								opponentMonsterZones[index]=0;
								opponentMonsterZonesBattlePosition[index]=0;
								checkForOneEnemyTributes+=1;
												}
							if(checkForOneEnemyTributes==1){
								//index=5;
								break;
																				}

																		}
										}
								}
				//check for highest attack
				else if(cardAttack[number-1]>highestAttack && cardAttack[number-1]<2500){
					highestAttack=cardAttack[number-1];
					//cout<<highestAttack<<endl; //TEST CODE
					monsterWithHighestAttack=number;
					indexOfMonster=index;
				}
			}
	        }


	//Check for empty zones
	for (int index = 0; index < 5; ++index) {
		//If monster zone empty, place the monster there.
		if (opponentMonsterZones[countMonsterZones]==0){
			//Summon the monster with the highest attack to the field in attack mode
			opponentMonsterZones[countMonsterZones]=monsterWithHighestAttack;
			//Put monster in ATK mode.
			opponentMonsterZonesBattlePosition[countMonsterZones]=1;
			//Remove the monster card from the hand.
			enemyHand[indexOfMonster]=0;
			//End the for loop.
			break;
						}
			//Otherwise, next monster zone
		else {
			countMonsterZones+=1;
								}
							}
	//========Test code==========
	//cardsInEnemyHand();
	//============Test code=================
	cout<<"Main Phase 1"<<endl;
	showField();
	cout<<endl;

	//AI Battle Phase
	cout<<"Battle Phase"<<endl;

	checkTrap();
	if (trapUsed==1){
		trapUsed=0;
		return;
	}

	//Check for monster targets
	int checkForPlayerMonsters=0;
	for (int index = 0; index < 5; ++index) {
		if (playerMonsterZones[index]!=0){
			checkForPlayerMonsters+=playerMonsterZones[index];
		}
	}
	//No player monsters, attack directly
	if (checkForPlayerMonsters==0){
		cout<<"No Player Monsters."<<endl;
		cout<<"The AI opponent attacks with all of its monsters."<<endl;
		//Attack with all monsters
		for (int index = 0; index < 5; ++index) {
				if (opponentMonsterZones[index]!=0){
					int attackingMonster=opponentMonsterZones[index];
					lifePointsPlayer-=cardAttack[attackingMonster-1];
					cout<<"Your Life Points: "<<endl;
					cout<<lifePointsPlayer;
					cout<<endl;
				}
	}
		//Check if AI won.
		checkVictoryOpponent(lifePointsPlayer);
	}
	//attack player monsters
	else {
		cout<<"Player has Monsters."<<endl;
		int playerMonsterAttacked=-1;

		//For every AI monster zone
		for (int index = 0; index < 5; ++index) {
			//If monster zone not blank
			if(opponentMonsterZones[index]!=0){
		//For every player monster zone
		for (int jindex = 0; jindex < 5; ++jindex) {
			//Check every human player monster zone for monsters and if the zone has a monster...
					if (playerMonsterZones[jindex]!=0){
						//If the zone has a higher attack mode monster, select that monster.
						if(cardAttack[opponentMonsterZones[index]-1]>cardAttack[playerMonsterZones[jindex]-1]){
							playerMonsterAttacked=playerMonsterZones[jindex];
						}
						}
			        }
				//If a monster was selected.
				if(playerMonsterAttacked!=-1){
					calculateBattle(playerMonsterAttacked, opponentMonsterZones[index]);
				}
				  }
		}


	}
	cout<<endl;
	}

//do the second Main Phase
void MainPhaseTwo(){
	//Variables:
		//Input 1 is for if the player wants to take their turn.
		//Input 2 is if they want to play a card.
		//Input 3 is to place the card.
		//Input 5 is for viewing cards.
		//Input 7 is for battle positions of summoned monsters.
		//Input 8 and 9 are for tribute summoning.
		int input, inputTwo, inputThree, inputFive, inputSix;
		inputFive=-1;
		int numberForCardInHand;
		int inputSeven=-1;
		int checkForEmptyMonsterZone=0;
		int validCard=1;
		int inputEight=-1;
		int inputNine=-1;
		int number=0;
		int chooseMonsterToTribute=1;
		int checkForTwoMonsters=0;
		int chooseMonsterToTributeVersionTwo=2;

		while (inputFive!=0){
		cout<<"View a card's details? Press 0 for no. Press 1 for the left most card, and add 1 for each card to the right (e.g. 3 for third card)."<<endl;
		cin>>inputFive;
		if (inputFive!=0){
			numberForCardInHand=hand[inputFive-1];

			if (numberForCardInHand==0){
				cout<<"Blank card"<<endl;
			}
			else{
					cout<<cardInformation[numberForCardInHand-1]<<endl;
				}
			}
		}
		cout<<endl;

		cout<<"Play a card? 1 for yes, anything other number for no"<<endl;
		cin>>input;
		if (input==1){

			while(validCard==1){
			//While loop is checking for valid plays
			cout<<"Play which card? Press a number; the left starts at 1 and adds 1 for each card (e.g. 3 for third card)."<<endl;
			cin>>inputTwo;
			//cout<<inputTwo;
			number=hand[inputTwo-1];
			//cout<<"TEST: "<<number-1;
			//cout<<"TEST: "<<cardList[number-1];

			//Check for tribute monster (level 8)
			if (didPlayerSummon==0 && (hand[inputTwo-1]==1 || hand[inputTwo-1]==2)){
						//Check all monster zone for monsters
				for (int index = 0; index < 5; ++index) {
						if (playerMonsterZones[index]!=0){
							checkForTwoMonsters+=1;
						}
					}
						if (checkForTwoMonsters<2){
							cout<<"You do not have enough monsters to tribute, so you cannot use this card."<<endl;
							continue;
						}
						cout<<"Tribute two monsters to summon this card? 1 for yes; 0 for no"<<endl;
						cin>>inputEight;
						if (inputEight==1){
							while(chooseMonsterToTributeVersionTwo!=0){
								cout<<"Tribute a monster to summon this card; the left starts at 1 and adds 1 for each card (e.g. 3 for third card)."<<endl;
								cin>>inputNine;
								if(playerMonsterZones[inputNine-1]==0){
									cout<<"There is no monster there."<<endl;
									continue;
							}
								else{
									playerMonsterZones[inputNine-1]=0;
									chooseMonsterToTributeVersionTwo-=1;
									validCard=0;
							}
							}
						}
						else{
							continue;
						}
			}
			//Check for tribute monster (level 5 or 6)
			else if (didPlayerSummon==0 && (hand[inputTwo-1]==3 || hand[inputTwo-1]==4)){
				//Check all monster zone for monsters
				if (playerMonsterZones[0]==0&&playerMonsterZones[1]==0&&playerMonsterZones[2]==0&&playerMonsterZones[3]==0&&playerMonsterZones[4]==0){
					cout<<"You have no monsters to tribute, so you cannot use this card."<<endl;
					continue;
				}
				cout<<"Tribute a monster to summon this card? 1 for yes; 0 for no"<<endl;
				cin>>inputEight;
				if (inputEight==1){
					while(chooseMonsterToTribute==1){
						cout<<"Tribute a monster to summon this card; the left starts at 1 and adds 1 for each card (e.g. 3 for third card)."<<endl;
						cin>>inputNine;
						if(playerMonsterZones[inputNine-1]==0){
							cout<<"There is no monster there."<<endl;
							continue;
					}
						else{
							playerMonsterZones[inputNine-1]=0;
							chooseMonsterToTribute=0;
							validCard=0;
					}
					}
				}
				else{
					continue;
				}

			}
			//Check for spells
			else if (hand[inputTwo-1]==36){
				for (int index = 0; index < 5; ++index) {
				opponentMonsterZones[index]=0;
				opponentMonsterZonesBattlePosition[index]=0;
				}
				cout<<"Raigeki destroyed all your opponent's monsters!"<<endl;
				showField();
				//Get rid of the card from the hand played.
				hand[inputTwo-1]=0;
				cardsInHand();
				continue;

			}
			//Check for spells
					else if (hand[inputTwo-1]==37){
						cout<<"Pot of Greed lets you draw two more cards!"<<endl;
						//Get rid of the card from the hand played.
						hand[inputTwo-1]=0;
						drawOne();
						drawOne();
						cardsInHand();
						continue;

					}
			//Check for spells
					else if (hand[inputTwo-1]==38){
						cout<<"You gain 1,000 Life Points!"<<endl;
						lifePointsPlayer+=1000;
						cout<<"Your LP: "<<lifePointsPlayer<<endl;
						//Get rid of the card from the hand played.
						hand[inputTwo-1]=0;
						cardsInHand();
						continue;

					}
					//Check for trap
					else if (hand[inputTwo-1]==39){
										cout<<"You set Widespread Ruin."<<endl;
										//set card
										if(playerSpellAndTrapZones[0]==0){
											playerSpellAndTrapZones[0]=hand[inputTwo-1];
										}
										else{
											playerSpellAndTrapZones[1]=hand[inputTwo-1];
										}
										//Get rid of the card from the hand played.
										hand[inputTwo-1]=0;
										cardsInHand();
										continue;

									}
					//Check for trap
					else if (hand[inputTwo-1]==40){
										cout<<"You set Magic Cylinder."<<endl;
										//set card
										if(playerSpellAndTrapZones[0]==0){
											playerSpellAndTrapZones[0]=hand[inputTwo-1];
																			}
										else{
											playerSpellAndTrapZones[1]=hand[inputTwo-1];
																			}
										//Get rid of the card from the hand played.
										hand[inputTwo-1]=0;
										cardsInHand();
										continue;

									}
			else{
				validCard=0;
			}
			}

			while(checkForEmptyMonsterZone==0 && didPlayerSummon==0){
			cout<<"Which zone (1 to 5, left to right)?"<<endl;
			cin>>inputThree;
			if (playerMonsterZones[inputThree-1]==0){
				playerMonsterZones[inputThree-1]=number;
				checkForEmptyMonsterZone=1;
			}
			else{
			cout<<"That monster zone has a monster."<<endl;
			}
			}
			//cout<<"TEST: "<<playerMonsterZones[inputThree-1];

			//Player chooses attack or defense.
			if (didPlayerSummon==0){
			cout<<"In attack mode (1) or defense mode (2)?"<<endl;
			cin>>inputSix;
			if (inputSix==1){
				playerMonsterZonesBattlePosition[inputThree-1]=1;
			}
			else if (inputSix==2){
				playerMonsterZonesBattlePosition[inputThree-1]=2;
			}

			//Get rid of the card from the hand played.
			hand[inputTwo-1]=0;
			}

			showField();

		}
		cout<<endl;

		//Handles changing battle position of monsters.
				while (inputSeven!=0){
							cout<<"Switch the battle position of a monster? 1 to 5 based on Monster Zone (left to right), 0 for no"<<endl;
							cin>>inputSeven;
							if (inputSeven==1 || inputSeven==2 || inputSeven==3 || inputSeven==4 || inputSeven==5){
								if (playerMonsterZonesBattlePosition[inputSeven-1]==1){
								playerMonsterZonesBattlePosition[inputSeven-1]=2;
								}
								else if (playerMonsterZonesBattlePosition[inputSeven-1]==2){
								playerMonsterZonesBattlePosition[inputSeven-1]=1;
								}
							}
				}
				showField();
				cout<<endl;

			if (didPlayerSummon==1){didPlayerSummon=0;}


}

//do BattlePhase
void battlePhase(){
	int inputOne, inputPlayerMonster;
	int loopForErrors=1;
	int loopForErrorsWhileLoopTwo=1;
	int clearCounter=0;
	int theBigWhileLoop=1;

	int attackingMonster, defendingMonster;

	int alreadyAttackedMonsters[5]={};
	int kindex=0;



	//If the opponent's monster zones have no monsters, the player can attack directly.
	int index;
	for (index = 0; index < 5; index++ ) {
		if (opponentMonsterZones[index]==0){
			clearCounter+=1;
		}
		//TEST code
	  //printf("MZ[%d] = %d\n", index, opponentMonsterZones[index] );
	  }
	//Lets the player attack directly.
	if (clearCounter==5){
		cout<<"You can attack directly!"<<endl;

		//Attack with all monsters
		for (int index = 0; index < 5; ++index) {
			if (playerMonsterZonesBattlePosition[index]==1&&playerMonsterZones[index]!=0){
			int attackingMonster=playerMonsterZones[index];
			lifePointsOpponent-=cardAttack[attackingMonster-1];
							//cout<<"TEST(playerMonsterZones[index]): "<<playerMonsterZones[index]<<endl;
							//cout<<"TEST(cardAttack[attackingMonster-1]): "<<cardAttack[attackingMonster-1]<<endl;
							cout<<"Your Opponent's Life Points: "<<endl;
							cout<<lifePointsOpponent;
							cout<<endl;
			}
		}

		//Check if human player won
		checkVictoryPlayer(lifePointsOpponent);

		MainPhaseTwo();
	}
	else{

		//Loops until player cancels
	while(theBigWhileLoop==1){
		loopForErrors=1;
		loopForErrorsWhileLoopTwo=1;

	while (loopForErrors==1){

		//Player chooses a monster of their own to attack with.
		cout<<"Which of your monsters do you want to attack with? (1 to 5; left to right; -1 to cancel)";
			cin>>inputPlayerMonster;

		if(inputPlayerMonster==-1){
			loopForErrors=0;
			loopForErrorsWhileLoopTwo=0;
			theBigWhileLoop=0;
		}
		else if(alreadyAttackedMonsters[0]==inputPlayerMonster || alreadyAttackedMonsters[1]==inputPlayerMonster|| alreadyAttackedMonsters[2]==inputPlayerMonster || alreadyAttackedMonsters[3]==inputPlayerMonster ||alreadyAttackedMonsters[4]==inputPlayerMonster){
			cout<<"You already attacked with that monster.";
			continue;
		}
		else if(inputPlayerMonster>5 || inputPlayerMonster<1){
			cout<<"Not a valid monster zone.";
			continue;
		}
		else if(playerMonsterZones[inputPlayerMonster-1]==0){
			cout<<"Not a valid monster zone.";
			continue;
		}
		else if(playerMonsterZonesBattlePosition[inputPlayerMonster-1]==2){
			cout<<"You cannot attack with a defense position monster.";
			continue;
		}
		else{
			attackingMonster=playerMonsterZones[inputPlayerMonster-1];
			alreadyAttackedMonsters[kindex]=inputPlayerMonster;
			kindex+=1;
			//cout<<"TEST: "<<cardList[attackingMonster-1];
			loopForErrors=0;
		}
	}

	//Player chooses an opponent's monster that they want to attack.
	while(loopForErrorsWhileLoopTwo==1){
		//If enemy has no monsters
		if(opponentMonsterZones[0]==0 &&opponentMonsterZones[1]==0 && opponentMonsterZones[2]==0 && opponentMonsterZones[3]==0 && opponentMonsterZones[4]==0){
			cout<<"You attack directly!"<<endl;
			lifePointsOpponent-=cardAttack[playerMonsterZones[inputPlayerMonster-1]-1]; //check if this is correct
			cout<<"Your Opponent's Life Points: "<<lifePointsOpponent<<endl;
			checkVictoryPlayer(lifePointsOpponent);
			loopForErrorsWhileLoopTwo=0;
		}
		else{
		cout<<"Which of your opponent's monsters do you want to attack? (1 to 5; left to right)";
					cin>>inputOne;

				//Player attacks a monster.
				if (opponentMonsterZones[inputOne-1]>0 && opponentMonsterZones[inputOne-1]<=35){
					defendingMonster=opponentMonsterZones[inputOne-1];
					cout<<"Attacking "<<cardList[defendingMonster-1]<<endl;

					calculateBattle(attackingMonster, defendingMonster);

					loopForErrorsWhileLoopTwo=0;
			}
				//Player attacks an empty monster zone.
				else if (opponentMonsterZones[inputOne-1]==0){
					cout<<"There is no monster there. ";
				}
	}
	}
		}

	MainPhaseTwo();
	}
	cout<<endl;

}

//do function to look at cards
void mainPhaseOne(){
	//Variables:
	//Input 1 is for if the player wants to take their turn.
	//Input 2 is if they want to play a card.
	//Input 3 is to place the card.
	//Input 4 is for phase control.
	//Input 5 is for viewing cards.
	//Input 7 is for battle positions of summoned monsters.
	//Input 8 and 9 are for tribute summoning.
	int input, inputTwo, inputThree, inputFour, inputFive, inputSix;
	inputFive=-1;
	int numberForCardInHand;
	int inputSeven=-1;
	int checkForEmptyMonsterZone=0;
	int validCard=1;
	int inputEight=-1;
	int inputNine=-1;
	int number=0;
	int chooseMonsterToTribute=1;
	int checkForTwoMonsters=0;
	int chooseMonsterToTributeVersionTwo=2;

	while (inputFive!=0){
	cout<<"View a card's details? Press 0 for no. Press 1 for the left most card, and add 1 for each card to the right (e.g. 3 for third card)."<<endl;
	cin>>inputFive;
	if (inputFive!=0){
		numberForCardInHand=hand[inputFive-1];

		if (numberForCardInHand==0){
			cout<<"Blank card"<<endl;
		}
		else{
				cout<<cardInformation[numberForCardInHand-1]<<endl;
			}
		}
	}
	cout<<endl;

	cout<<"Play a card? 1 for yes, anything other number for no"<<endl;
	cin>>input;
	if (input==1){

		while(validCard==1){
		//While loop is checking for valid plays
		cout<<"Play which card? Press a number; the left starts at 1 and adds 1 for each card (e.g. 3 for third card)."<<endl;
		cin>>inputTwo;
		//cout<<inputTwo;
		number=hand[inputTwo-1];
		//cout<<"TEST: "<<number-1;
		//cout<<"TEST: "<<cardList[number-1];

		//Check for tribute monster (level 8)
		if (hand[inputTwo-1]==1 || hand[inputTwo-1]==2){
					//Check all monster zone for monsters
			for (int index = 0; index < 5; ++index) {
					if (playerMonsterZones[index]!=0){
						checkForTwoMonsters+=1;
					}
				}
					if (checkForTwoMonsters<2){
						cout<<"You do not have enough monsters to tribute, so you cannot use this card."<<endl;
						continue;
					}
					cout<<"Tribute two monsters to summon this card? 1 for yes; 0 for no"<<endl;
					cin>>inputEight;
					if (inputEight==1){
						while(chooseMonsterToTributeVersionTwo!=0){
							cout<<"Tribute a monster to summon this card; the left starts at 1 and adds 1 for each card (e.g. 3 for third card)."<<endl;
							cin>>inputNine;
							if(playerMonsterZones[inputNine-1]==0){
								cout<<"There is no monster there."<<endl;
								continue;
						}
							else{
								playerMonsterZones[inputNine-1]=0;
								chooseMonsterToTributeVersionTwo-=1;
								validCard=0;
						}
						}
					}
					else{
						continue;
					}
		}
		//Check for tribute monster (level 5 or 6)
		else if (hand[inputTwo-1]==3 || hand[inputTwo-1]==4){
			//Check all monster zone for monsters
			if (playerMonsterZones[0]==0&&playerMonsterZones[1]==0&&playerMonsterZones[2]==0&&playerMonsterZones[3]==0&&playerMonsterZones[4]==0){
				cout<<"You have no monsters to tribute, so you cannot use this card."<<endl;
				continue;
			}
			cout<<"Tribute a monster to summon this card? 1 for yes; 0 for no"<<endl;
			cin>>inputEight;
			if (inputEight==1){
				while(chooseMonsterToTribute==1){
					cout<<"Tribute a monster to summon this card; the left starts at 1 and adds 1 for each card (e.g. 3 for third card)."<<endl;
					cin>>inputNine;
					if(playerMonsterZones[inputNine-1]==0){
						cout<<"There is no monster there."<<endl;
						continue;
				}
					else{
						playerMonsterZones[inputNine-1]=0;
						chooseMonsterToTribute=0;
						validCard=0;
				}
				}
			}
			else{
				continue;
			}

		}
		//Check for spells
		else if (hand[inputTwo-1]==36){
			for (int index = 0; index < 5; ++index) {
			opponentMonsterZones[index]=0;
			opponentMonsterZonesBattlePosition[index]=0;
			}
			cout<<"Raigeki destroyed all your opponent's monsters!"<<endl;
			showField();
			//Get rid of the card from the hand played.
			hand[inputTwo-1]=0;

			cardsInHand();
			continue;

		}
		//Check for spells
				else if (hand[inputTwo-1]==37){
					cout<<"Pot of Greed lets you draw two more cards!"<<endl;
					//Get rid of the card from the hand played.
					hand[inputTwo-1]=0;
					drawOne();
					drawOne();

					cardsInHand();
					continue;

				}
		//Check for spells
				else if (hand[inputTwo-1]==38){
					cout<<"You gain 1,000 Life Points!"<<endl;
					lifePointsPlayer+=1000;
					cout<<"Your LP: "<<lifePointsPlayer<<endl;
					//Get rid of the card from the hand played.
					hand[inputTwo-1]=0;

					cardsInHand();
					continue;

				}
				//Check for trap
				else if (hand[inputTwo-1]==39){
									cout<<"You set Widespread Ruin."<<endl;
									//set card
									if(playerSpellAndTrapZones[0]==0){
										playerSpellAndTrapZones[0]=hand[inputTwo-1];
									}
									else{
										playerSpellAndTrapZones[1]=hand[inputTwo-1];
									}
									//Get rid of the card from the hand played.
									hand[inputTwo-1]=0;

									cardsInHand();
									continue;

								}
				//Check for trap
				else if (hand[inputTwo-1]==40){
									cout<<"You set Magic Cylinder."<<endl;
									//set card
									if(playerSpellAndTrapZones[0]==0){
										playerSpellAndTrapZones[0]=hand[inputTwo-1];
																		}
									else{
										playerSpellAndTrapZones[1]=hand[inputTwo-1];
																		}
									//Get rid of the card from the hand played.
									hand[inputTwo-1]=0;

									cardsInHand();
									continue;

								}
		else{
			validCard=0;
		}
		}

		while(checkForEmptyMonsterZone==0){
		cout<<"Which zone (1 to 5, left to right)?"<<endl;
		cin>>inputThree;
		if (playerMonsterZones[inputThree-1]==0){
			playerMonsterZones[inputThree-1]=number;
			checkForEmptyMonsterZone=1;
			//Player summoned a monster.
			didPlayerSummon=1;
		}
		else{
		cout<<"That monster zone has a monster."<<endl;
		}
		}
		//cout<<"TEST: "<<playerMonsterZones[inputThree-1];

		//Player chooses attack or defense.
		cout<<"In attack mode (1) or defense mode (2)?"<<endl;
		cin>>inputSix;
		if (inputSix==1){
			playerMonsterZonesBattlePosition[inputThree-1]=1;
		}
		else if (inputSix==2){
			playerMonsterZonesBattlePosition[inputThree-1]=2;
		}

		//Get rid of the card from the hand played.
		hand[inputTwo-1]=0;

		showField();

	}
	cout<<endl;

	//Handles changing battle position of monsters.
			while (inputSeven!=0){
						cout<<"Switch the battle position of a monster? 1 to 5 based on Monster Zone (left to right), 0 for no"<<endl;
						cin>>inputSeven;
						if (inputSeven==1 || inputSeven==2 || inputSeven==3 || inputSeven==4 || inputSeven==5){
							if (playerMonsterZonesBattlePosition[inputSeven-1]==1){
							playerMonsterZonesBattlePosition[inputSeven-1]=2;
							}
							else if (playerMonsterZonesBattlePosition[inputSeven-1]==2){
							playerMonsterZonesBattlePosition[inputSeven-1]=1;
							}
						}
			}
			showField();
			cout<<endl;

			//Change of Phase
	cout<<"Battle Phase, Main Phase 2, or End Phase? (1, 2, 3)";
			cin>>inputFour;
			if (inputFour==1){
				cout<<"Battle Phase"<<endl;
				battlePhase();
			}
			else if (inputFour==2){
				cout<<"Main Phase 2"<<endl;
				MainPhaseTwo();
			}
			else if (inputFour==3){
				cout<<"EndPhase";
				}
			cout<<endl;

}






//need to fix hand array after playing card
int main() {
	//Test code; opponent has Dark Blade
	//opponentMonsterZones[2]=16;
	//Test code; opponent has 2000 ATK monster
	//opponentMonsterZones[2]=6;

	  //Shuffle the deck
    random_device device;
    mt19937 generator(device());

    random_device devicetwo;
    mt19937 generatortwo(devicetwo());

    shuffle(&deck[0], &deck[40], generator);
    shuffle(&enemyDeck[0], &enemyDeck[35], generatortwo);

	  //Draw player's hand.
	 drawHand();

    //draws enemy hand
    drawEnemyHand();

    cardsInHand();

     //====================TEST CODE======================
    //cardsInEnemyHand();
     //====================TEST CODE======================

     showField();

     mainPhaseOne();

     AITurn();

    while (lifePointsPlayer>0 && lifePointsOpponent>0){

    	drawOne();

    	cardsInHand();

    //====================TEST CODE======================
    	//cardsInEnemyHand();
    //====================TEST CODE======================

    	showField();

    	mainPhaseOne();

    	drawOneAI();

    	AITurn();
    }

	return 0;
}

/*===============TEST CODE==================
    	  //Print out each value in the deck array

      for (int index = 0; index < 40; index++ ) {
    	      printf("Deck[%d] = %d\n", index, deck[index] );
    	   }


            for (int index = 0; index < 35; index++ ) {
          	      printf("EnemyDeck[%d] = %d\n", index, enemyDeck[index] );
          	   }


      ===============TEST CODE==================*/

/*
===============TEST CODE==================
	  //Print out each value in the deck array
	   int index=0;
 for (index = 0; index < 40; index++ ) {
	      printf("Deck[%d] = %d\n", index, deck[index] );
	   }

 //Print out each value in the deck array
	   for (index = 0; index < 40; index++ ) {
	      printf("Hand[%d] = %d\n", index, hand[index] );
	   }

	   for (int i = 0; i < 40; i++)  {
	           cout << cardList[i] << endl; }

	           for (index = 0; index < 5; index++ ) {
   	      printf("MZ[%d] = %d\n", index, playerMonsterZones[index] );
   	   }

 */

   //TEST CODE
   		//Print out each value in the deck array
   		/*
   				cout<<(numberForCardInHand)<<endl;
   				cout<<numberForCardInHand-1<<endl;

   			   for (int index = 0; index < 40; index++ ) {
   			      printf("Hand[%d] = %d\n", index, hand[index] );
   			   }
   			   //TEST CODE
   	}*/
