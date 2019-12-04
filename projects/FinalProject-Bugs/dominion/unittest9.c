#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

#include "rngs.h"



int test_bug_9(){
    // set card array to include minion
    int k[10] = { ambassador, minion, tribute, gardens, mine, remodel, smithy, village, baron, great_hall };
    // declare the game state
    struct gameState G;

    initializeGame(2, k, 6, &G); // initialize a new game state
    printf("Test for Bug 9: Duplicate cards aren't handled properly for tribute\n");
    //Test 1: User chooses to gain two coins from minion
    //Pre Game State Requirements: Player 0 has minion in their hand,3 coppers, and 1 estate
    //Other player has same game state as initialization
    //Post Game State Requirements: Player 0 has 4 cards in their hand, 5 in deck, 1 in discard
    struct gameState initial = G;

    //set pre game state
    initial.hand[0][0] = tribute;
    initial.hand[0][1] = copper; 
    initial.hand[0][2] = copper; 
    initial.hand[0][3] = copper; 
    initial.hand[0][4] = estate;
    
    initial.deck[1][9] = copper;
    initial.deck[1][8] = copper;
    initial.numActions = 1;
    initial.coins = 3;
    int bonus = 0;
    //run function
    int r = cardEffect(tribute, 0,0,0,&initial,0,&bonus);


    int successful = 1;
    //check if game state meets post game state requirements
    if(bonus != 2){
        printf("\nBonus was not updated correctly!\n");
        successful = 0;
    }else{
        printf("\nBonus was updated correctly!\n");
    }
    if(r != 0){
        printf("\ncardEffect returned nonzero!\n");
        successful = 0;
    }else{
        printf("\ncardEffect properly returned 0\n");
    }
    if(initial.numActions != 1){
        printf("\nplayer was granted incorrect number of additional actions\n");
        successful = 0;
    }else{
        printf("\nplayer was granted correct number of additional actions\n");
    }
    if(successful){
        printf("\nSuccess! Unit test for bug 9 passed.\n");
    }
    else{
        printf("\nFailure! Unit test for bug 9 failed.\n");
    }

    
    return 0;
}

int main(){

    test_bug_9();

    printf("\ndone with test for bug 9:\n\n");
    
}