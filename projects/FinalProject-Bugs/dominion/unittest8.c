#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

#include "rngs.h"



int test_bug_8(){
    // set card array to include minion
    int k[10] = { ambassador, minion, tribute, gardens, mine, remodel, smithy, village, baron, great_hall };
    // declare the game state
    struct gameState G;

    initializeGame(2, k, 6, &G); // initialize a new game state
    printf("Test for Bug 8 : bonuses are not properly recorded\n");
    //Test 1: User chooses to gain two coins from minion
    //Pre Game State Requirements: Player 0 has minion in their hand,3 coppers, and 1 estate
    //Other player has same game state as initialization
    //Post Game State Requirements: Player 0 has 4 cards in their hand, 5 in deck, 1 in discard
    struct gameState initial = G;
    //set pre game state
    initial.hand[0][0] = minion;
    initial.hand[0][1] = copper; 
    initial.hand[0][2] = copper; 
    initial.hand[0][3] = copper; 
    initial.hand[0][4] = estate; 
    initial.coins = 3;
    int bonus = 0;
    //run function
    cardEffect(minion, 1,0,0,&initial,0,&bonus);

    //check if game state meets post game state requirements
    if(bonus != 2){
        printf("\nbonus not recorded properly!\n");
        printf("\nFailure! Unit test for bug 8 failed!\n");
    }
    else{
        printf("\nSuccess! Unit test for bug 8 passed\n");
    }


    return 0;
}

int main(){

    test_bug_8();

    printf("\ndone with unit test 8:\n\n");
    
}