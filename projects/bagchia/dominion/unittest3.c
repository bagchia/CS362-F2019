#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "test_assert.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main()
{
    printf("Unit Test 3: Ambassador\n");
    int r, i;
    int seed = 2;
    // set your card array
    int kingdom[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    // declare the game state
    struct gameState G;
    // declare the arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    //
    // set the state of your variables
    // comment on what this is going to test
    //
    memset(&G, 23, sizeof(struct gameState)); // set the game state
    r = initializeGame(3, kingdom, seed, &G); // initialize a new game               // set any other variables
    //Fill the player's hand with coppers as a place holder
    memcpy(G.hand[0], coppers, sizeof(int) * 500);

    //Give the player an ambassador and 5 other cards
    G.handCount[0] = 6;
    G.hand[0][0] = ambassador;
    G.hand[0][1] = baron;
    G.hand[0][2] = gardens;
    G.hand[0][3] = gardens;
    G.hand[0][4] = baron;
    G.hand[0][5] = province;

    //Give another player cards
    G.handCount[1] = 3;
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;
    G.hand[1][2] = copper;

    
    //Give another player cards
    G.handCount[2] = 6;
    G.hand[2][0] = copper;
    G.hand[2][1] = copper;
    G.hand[2][2] = copper;
    G.hand[2][3] = gold;
    G.hand[2][4] = gold;
    G.hand[2][5] = gold;

    int old_hand_count = G.handCount[0];
    int old_amb_in_played_cards = count_array(G.playedCards, G.playedCardCount, ambassador);
    printf("Play the ambassador and choose to discard 2 gardens\n");
    int return_value = ambassadorEffect(2, 2, &G, 0);
    test_bool(return_value == 0, "Return value should be 0");
    test_bool(count_array(G.hand[0], G.handCount[0], ambassador) == 0, "Number of ambassadors in hand is exactly 0");
    test_bool(count_array(G.hand[0], G.handCount[0], gardens) == 0, "Number of gardens in hand is exactly 0");
    test_bool(G.handCount[0] == old_hand_count-3, "Hand size decreased by 3");
    test_bool(count_array(G.playedCards, G.playedCardCount, ambassador) == old_amb_in_played_cards + 1, "1 more ambassador in the played card pile");
    test_bool(count_array(G.hand[1], G.handCount[1], gardens) == 1, "Player 2 has a gardens now");
    test_bool(count_array(G.hand[2], G.handCount[2], gardens) == 1, "Player 3 has a gardens now");
    printf("Play the ambassador with an invalid choice\n");
    return_value = ambassadorEffect(2, 1000, &G, 0);
    test_bool(return_value == -1, "Return value should equal -1");
    printf("Play the ambassador with the ambassador itself\n");
    return_value = ambassadorEffect(0, 1, &G, 0);
    test_bool(return_value == -1, "Return value should equal -1");
}
