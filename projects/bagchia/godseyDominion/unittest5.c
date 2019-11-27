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
    printf("Unit Test 5: Mine\n");
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
    r = initializeGame(2, kingdom, seed, &G); // initialize a new game               // set any other variables
    //Fill the player's hand with coppers as a place holder
    memcpy(G.hand[0], coppers, sizeof(int) * 500);

    //Give the player a mine and 5 other cards
    G.handCount[0] = 6;
    G.hand[0][0] = mine;
    G.hand[0][1] = copper;
    G.hand[0][2] = silver;
    G.hand[0][3] = gold;
    G.hand[0][4] = baron;
    G.hand[0][5] = province;

    printf("Trash a copper for a silver\n");
    int return_value = playTribute(1, silver, 0, &G, 0, NULL, 0);
    //int return_value = mineEffect(1, silver, &G, 0);
    test_bool(count_array(G.hand[0], G.handCount[0], mine) == 0, "Number of mines in hand exactly 0");
    test_bool(count_array(G.hand[0], G.handCount[0], copper) == 0, "Number of coppers in hand exactly 0");
    test_bool(count_array(G.hand[0], G.handCount[0], silver) == 0, "Number of silvers in hand exactly 2");
    test_bool(return_value == 0, "Return value is 0");

    //Give the player a mine and 5 other cards
    G.handCount[0] = 6;
    G.hand[0][0] = mine;
    G.hand[0][1] = copper;
    G.hand[0][2] = silver;
    G.hand[0][3] = gold;
    G.hand[0][4] = baron;
    G.hand[0][5] = province;

    
    printf("Trash a copper for a copper\n");
    return_value = playMine(1, copper, 0, &G, 0, NULL, 0);
    // return_value = mineEffect(1, copper, &G, 0);
    test_bool(count_array(G.hand[0], G.handCount[0], mine) == 0, "Number of mines in hand exactly 0");
    test_bool(count_array(G.hand[0], G.handCount[0], copper) == 0, "Number of coppers in hand exactly 1");
    test_bool(return_value == 0, "Return value is 0");

    G.handCount[0] = 6;
    G.hand[0][0] = mine;
    G.hand[0][1] = copper;
    G.hand[0][2] = silver;
    G.hand[0][3] = gold;
    G.hand[0][4] = baron;
    G.hand[0][5] = province;
        
    printf("Trash a copper for a gold\n");
    return_value = playMine(1, gold, 0, &G, 0, NULL, 0);
    //return_value = mineEffect(1, gold, &G, 0);
    test_bool(count_array(G.hand[0], G.handCount[0], mine) == 0, "Number of mines in hand exactly 1");
    test_bool(count_array(G.hand[0], G.handCount[0], copper) == 0, "Number of gold in hand exactly 0");
    test_bool(return_value == 0, "Return value is -1");

}
