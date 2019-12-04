#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>

#include "rngs.h"



int test_bug_10(){
    // set card array to include minion
    int k[10] = { ambassador, minion, tribute, gardens, mine, remodel, smithy, village, baron, great_hall };
    // declare the game state
    struct gameState G;

    initializeGame(2, k, 6, &G); // initialize a new game state
    printf("Test for Bug 10: Ambassador doesn't search for cards to return correctly\n");
    //Test 1: User chooses to gain two coins from minion
    //Pre Game State Requirements: Player 0 has minion in their hand,3 coppers, and 1 estate
    //Other player has same game state as initialization
    //Post Game State Requirements: Player 0 has 4 cards in their hand, 5 in deck, 1 in discard
    struct gameState initial = G;

    //set pre game state
    initial.hand[0][0] = ambassador;
    initial.hand[0][1] = copper; 
    initial.hand[0][2] = copper; 
    initial.hand[0][3] = estate; 
    initial.hand[0][4] = estate;

    initial.coins = 2;
    int bonus = 0;
    //run function
    int r = cardEffect(ambassador,1,2,0,&initial,0,&bonus);


    int successful = 1;
    //check if game state meets post game state requirements
    if(r != 0){
        printf("\ncardEffect returned nonzero!\n");
        successful = 0;
    }
    int i;
    int wrong_count = 0;
    for(i = 0; i < initial.discardCount[0];i++){
        if(initial.discard[0][i] == copper){
            wrong_count++;
        }
    }
    if(wrong_count > 0){
        printf("\ncards weren't successfully removed from hand\n");
        successful = 0;
    }
    if(successful){
        printf("\nSuccess! Unit test for bug 10 passed.\n");
    }
    else{
        printf("\nFailure! Unit test for bug 10 failed.\n");
    }

    
    return 0;
}

int main(){

    test_bug_10();

    printf("\ndone with test for bug 10:\n\n");
    
}