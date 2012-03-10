#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "rngs.h"

void test_buy_random() {
	struct gameState state;

 	state.supplyCount[curse] = 100;
 	state.supplyCount[estate] = 100;
 	state.supplyCount[duchy] = 100;
 	state.supplyCount[province] = 100;
 	state.supplyCount[copper] = 100;
 	state.supplyCount[silver] = 100;
 	state.supplyCount[gold] = 100;
 	state.supplyCount[adventurer] = 100;
 	state.supplyCount[council_room] = 100;
 	state.supplyCount[feast] = 100;
 	state.supplyCount[gardens] = 100;
 	state.supplyCount[mine] = 100;
 	state.supplyCount[remodel] = 100;
 	state.supplyCount[smithy] = 100;
 	state.supplyCount[village] = 100;
 	state.supplyCount[baron] = 100;
 	state.supplyCount[great_hall] = 100;
 	state.supplyCount[minion] = 100;
 	state.supplyCount[steward] = 100; 	
	state.supplyCount[tribute] = 100;
 	state.supplyCount[ambassador] = 100;
 	state.supplyCount[cutpurse] = 100;
 	state.supplyCount[embargo] = 100;
 	state.supplyCount[outpost] = 100;
 	state.supplyCount[salvager] = 100;
 	state.supplyCount[sea_hag] = 100;
 	state.supplyCount[treasure_map] = 100;

	int i = 0;
	

	for(i = 0 ; i < 100000; i++){ 
		state.phase = 0;
		state.coins = rand()%100;
		state.numBuys = rand()%5;
		int card = rand()%27;
		int whoseTurn =  state.whoseTurn;
		int coins = state.coins;
		int supply = state.supplyCount[card];
		int discardCount = state.discardCount[state.whoseTurn] = 0;
		int buys = state.numBuys;	
		printf("Running buyCard\n");
		int ret = buyCard(card, &state);
	
		printf("Starting Random Buy Test\n");
		
		printf("Coins: %d\n", coins);
		printf("Card to buy: %d\n", card);
		printf("Current supply count: %d\n", state.supplyCount[card]);
	
		if(state.supplyCount[card] != supply - 1){
			printf("---%d did not decrement\n\n",card);
		}

		else if(state.numBuys != buys - 1 && ret != -1){
			printf("---Did not update the number of buys\n\n");
		}
			
		else if(state.discardCount[whoseTurn] != discardCount + 1){
			printf("---Did not update discard count\n\n");
		}
		
		else if(state.discard[whoseTurn][state.discardCount[whoseTurn] - 1] != card){
			printf("---Not the proper card at the top of discard\n");
			printf("%d on top, should be %d\n\n", state.discard[whoseTurn][state.discardCount[whoseTurn]], card);
		}
		
		else{
			printf("PASSED!\n\n");
		}
	}
}

void test_play_card(){
	struct gameState state;
	
 	state.supplyCount[curse] = 100;
 	state.supplyCount[estate] = 100;
 	state.supplyCount[duchy] = 100;
 	state.supplyCount[province] = 100;
 	state.supplyCount[copper] = 100;
 	state.supplyCount[silver] = 100;
 	state.supplyCount[gold] = 100;
 	state.supplyCount[adventurer] = 100;
 	state.supplyCount[council_room] = 100;
 	state.supplyCount[feast] = 100;
 	state.supplyCount[gardens] = 100;
 	state.supplyCount[mine] = 100;
 	state.supplyCount[remodel] = 100;
 	state.supplyCount[smithy] = 100;
 	state.supplyCount[village] = 100;
 	state.supplyCount[baron] = 100;
 	state.supplyCount[great_hall] = 100;
 	state.supplyCount[minion] = 100;
 	state.supplyCount[steward] = 100; 	
	state.supplyCount[tribute] = 100;
 	state.supplyCount[ambassador] = 100;
 	state.supplyCount[cutpurse] = 100;
 	state.supplyCount[embargo] = 100;
 	state.supplyCount[outpost] = 100;
 	state.supplyCount[salvager] = 100;
 	state.supplyCount[sea_hag] = 100;
 	state.supplyCount[treasure_map] = 100;

	int turn = state.whoseTurn = 0;
	state.numPlayers = 2;
	int handFlag = 2;
	int discardFlag = 0;
	int deckFlag = 1;
	int j;
	int y, z;
	int coin;
	int hcount;
	int act;
	int hand;
	int buys;
	int choice;
	int discard;
	state.numBuys = 1;
	state.handCount[turn] = 0;
	state.discardCount[turn] = 0;
	state.playedCardCount = 0;

	for(j = 0; j < 1000; j++){
		int i,k,l;
		state.numActions = 100000;
		state.numBuys = 1;
		state.handCount[turn] = 0;
	    state.discardCount[turn] = 0;
	    state.playedCardCount = 0;		
		printf("---Setting Hand---\n");
		for(k = 0; k < 27; k++){
			//Put card into hand
			if(gainCard(rand()%27, &state, handFlag, turn) == -1){
				printf("---FAILED: failed to gain a %d card\n", k);
			}
		}

		//Random init discard
		printf("---Setting Discard---\n");
		if(state.handCount[turn] != 27){
			printf("---FAILED: Incorrect hand count\n");
			return;
		}

		printf("---Init Discard---\n");
		for(i = 0; i < rand()%100; i++){
			//Put card into discard
			int card_choice = rand()%26;
			if(gainCard(card_choice, &state, discardFlag, turn) == -1){
				printf("---FAILED: Card not added to discard\n");
			}
		}

		printf("---Setting Deck---\n");
		for(i = 0; i < rand()%50; i++){
			//Put card into deck
			if(gainCard(i%27, &state, deckFlag, turn) == -1){
				printf("---FAILED: Card not added to the deck\n");
			}
		}
	
	
		//playCard(handPos, choice1, choice2, choice3)
		int passed;
		int card_played;
		while(state.handCount[turn] >= 0){
			passed = 0;
			card_played = state.deck[turn][state.handCount[turn] -1];
			printf("---Playing a %d\n", state.deck[turn][state.handCount[turn]-1]);

			//Skip over cards not covered in the switch statement as it messes with the test
			
			if(card_played < 7){
				printf("---CARD NOT TESTABLE\n");
				state.handCount[turn]--;
			}

			else if(state.deck[turn][state.handCount[turn]-1] == 11 || state.deck[turn][state.handCount[turn]-1] == 12 ){
				if(playCard(state.handCount[turn]-1, rand()%state.handCount[turn],rand()%26, -1, &state) == -1){
					printf("---FAILED: Card Test Failed\n");
					state.handCount[turn]--;
				}
				else{
					passed = 1;
					state.handCount[turn]--;
				}
			}
			else if(state.deck[turn][state.handCount[turn]-1] == 9 || state.deck[turn][state.deckCount[turn]-1] == 22){
				if(playCard(state.handCount[turn]-1, rand()%26, -1, -1, &state) == -1){
					printf("---FAILED: Card Test Failed\n");
					state.handCount[turn]--;
				}
				else{
					passed =1;
					state.handCount[turn]--;
				}
			}
			else if(state.deck[turn][state.handCount[turn]-1] == 24){
				if(playCard(state.handCount[turn]-1, rand()%state.handCount[turn], -1, -1, &state) == -1){
					printf("---FAILED: Card Test Failed\n");
					state.handCount[turn]--;
				}
				else{
					passed = 1;
					state.handCount[turn]--;
				}
			}
			else if(state.deck[turn][state.handCount[turn]-1] == 15){
				if(playCard(state.handCount[turn]-1, rand()%2, -1, -1, &state) == -1){
					printf("---FAILED: Card Test Failed\n");
					state.handCount[turn]--;
				}
				else{
					passed = 1;
					state.handCount[turn]--;
				}
			}
			else if(state.deck[turn][state.handCount[turn]-1] == 17){
				if(playCard(state.handCount[turn]-1, rand()%2 + 1, -1, -1, &state) == -1){
					printf("---FAILED: Card Test Failed\n");
					state.handCount[turn]--;
				}
				else{
					passed = 1;
					state.handCount[turn]--;
				}
			}
			else if(state.deck[turn][state.handCount[turn]-1] == 18){
				if(playCard(state.handCount[turn]-1, rand()%3 + 1, rand()%state.handCount[turn], rand()%state.handCount[turn], &state) == -1){
					printf("---FAILED: Card Test Failed\n");
					state.handCount[turn]--;
				}
				else{
					passed = 1;
					state.handCount[turn]--;
				}
			}
			else if(state.deck[turn][state.handCount[turn]-1] == 20){
				if(playCard(state.handCount[turn]-1, rand()%state.handCount[turn], 1, -1, &state) == -1){
					printf("---FAILED: Card Test Failed\n");
					state.handCount[turn]--;
				}
				else{
					passed = 1;
					state.handCount[turn]--;
				}
			}
			else if(state.deck[turn][state.handCount[turn]-1] == 23){
				state.handCount[turn]--;			  
			}
			else if(state.deck[turn][state.handCount[turn]-1] != -1) {
				if(playCard(state.handCount[turn]-1, -1, -1, -1, &state) == -1){
					printf("---FAILED: Card Test Failed\n");
					state.handCount[turn]--;
				}
				else{
					passed = 1;
					state.handCount[turn]--;
				}
			}
				
			if(passed == 1){
				printf("\n\n---PASSED PLAY TEST: Card test passed play test\n");
				printf("---STATE DUMP TEST:         \n");
				printf("Card Played: %d\n", card_played);
				printf("DeckCount: %d\n", state.deckCount[turn]);
				printf("HandCount: %d\n", state.handCount[turn]);
				printf("DiscardCount: %d\n", state.discardCount[turn]);
				printf("numActions: %d\n", state.numActions);
				printf("coins: %d\n", state.coins);
				printf("numBuys: %d\n", state.numBuys);
				state.handCount[turn]--;
			}
			       
		}
		
		state.handCount[turn] = 0;
	}
}   


int main(int argc, char * argv[]){

	if(strcmp(argv[1], "-br") == 0){
		test_buy_random();
	}

	else if(strcmp(argv[1],"-pc") == 0){
		test_play_card();
	}
	
	else{
		printf("%s <test_flag>\n", argv[0]);
	}

	return 0;

}
