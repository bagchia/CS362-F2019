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
    printf("Unit Test 4: Tribute\n");
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

    //Give the player an tribute
    G.handCount[0] = 6;
    G.hand[0][0] = tribute;
    G.hand[0][1] = baron;
    G.hand[0][2] = gardens;
    G.hand[0][3] = gardens;
    G.hand[0][4] = baron;
    G.hand[0][5] = province;

    //Give another player an action and treasure card
    G.deckCount[1] = 3;
    G.deck[1][0] = baron;
    G.deck[1][1] = copper;
    G.deck[1][2] = province;

    int old_actions = G.numActions;
    int old_coins = G.coins;
    printf("Play the tribute to discard the baron and copper from the next player\n");
    tributeEffect(&G);
    test_bool(count_array(G.hand[0], G.handCount[0], tribute) == 0, "Number of tributes in player 1's hand is exactly 0");
    test_bool(count_array(G.hand[1], G.handCount[1], copper) == 0, "Number of coppers in player 2's hand is exactly 0");
    test_bool(count_array(G.hand[1], G.handCount[1], baron) == 0, "Number of barons in player 2's hand is exactly 0");
    test_bool(G.numActions == old_actions + 2, "Number of actions increased by 2");
    test_bool(G.coins == old_coins + 2, "Number of coins increased by 2");
    G.hand[0][0] = tribute;
    printf("Play the tribute to discard the province from the next player\n");
    int old_hand_count = G.handCount[0];
    tributeEffect(&G);
    test_bool(count_array(G.hand[0], G.handCount[0], tribute) == 0, "Number of tributes in player 1's hand is exactly 0");
    test_bool(count_array(G.hand[1], G.handCount[1], copper) == 0, "Number of provinces in player 2's hand is exactly 0");
    test_bool(G.handCount[0] == old_hand_count + 2, "Player gained exactly two cards");
    printf("Play the tribute when the next player has duplicate cards");
    //Give the player an tribute
    G.handCount[0] = 6;
    G.hand[0][0] = tribute;
    G.hand[0][1] = baron;
    G.hand[0][2] = gardens;
    G.hand[0][3] = gardens;
    G.hand[0][4] = baron;
    G.hand[0][5] = province;

    //Give another treasure cards
    G.deckCount[1] = 3;
    G.deck[1][0] = copper;
    G.deck[1][1] = copper;
    G.deck[1][2] = copper;
    printf("Play the tribute to discard only one copper from the next player\n");
    tributeEffect(&G);
    test_bool(count_array(G.hand[0], G.handCount[0], tribute) == 0, "Number of tributes in player 1's hand is exactly 0");
    test_bool(count_array(G.hand[1], G.handCount[1], copper) == 0, "Number of coppers in player 2's hand is exactly 2");
    test_bool(G.coins == old_coins + 2, "Number of coins increased by 2");

        //Give the player an tribute
    G.handCount[0] = 6;
    G.hand[0][0] = tribute;
    G.hand[0][1] = baron;
    G.hand[0][2] = gardens;
    G.hand[0][3] = gardens;
    G.hand[0][4] = baron;
    G.hand[0][5] = province;

    //Give another treasure cards
    G.deckCount[1] = 0;
    G.discardCount[1] = 1;
    printf("Play the tribute when the next player does not have enough cards\n");
    tributeEffect(&G);
    test_bool(count_array(G.hand[0], G.handCount[0], tribute) == 0, "Number of tributes in player 1's hand is exactly 0");
    test_bool(G.coins == old_coins + 0, "Number of coins increased by 0");

    //Give the player an tribute
    G.handCount[0] = 6;
    G.hand[0][0] = tribute;
    G.hand[0][1] = baron;
    G.hand[0][2] = gardens;
    G.hand[0][3] = gardens;
    G.hand[0][4] = baron;
    G.hand[0][5] = province;

    //Give another treasure cards
    G.deckCount[1] = 1;
    G.discardCount[1] = 0;
    printf("Play the tribute when the next player does not have enough cards in another configuration\n");
    tributeEffect(&G);
    test_bool(count_array(G.hand[0], G.handCount[0], tribute) == 0, "Number of tributes in player 1's hand is exactly 0");
    test_bool(G.coins == old_coins + 0, "Number of coins increased by 0");

    G.handCount[1] = 6;
    G.hand[1][0] = tribute;
    G.hand[1][1] = baron;
    G.hand[1][2] = gardens;
    G.hand[1][3] = gardens;
    G.hand[1][4] = baron;
    G.hand[1][5] = province;

    //Give another player an action and treasure card
    G.deckCount[0] = 3;
    G.deck[0][0] = baron;
    G.deck[0][1] = copper;
    G.deck[0][2] = province;
    G.whoseTurn = 1;
    printf("Play the tribute when the next player is the first player\n");
    
    old_actions = G.numActions;
    old_coins = G.coins;
    tributeEffect(&G);
    test_bool(count_array(G.hand[1], G.handCount[0], tribute) == 0, "Number of tributes in player 2's hand is exactly 0");
    test_bool(count_array(G.hand[0], G.handCount[1], copper) == 0, "Number of coppers in player 1's hand is exactly 0");
    test_bool(count_array(G.hand[0], G.handCount[1], baron) == 0, "Number of barons in player 1's hand is exactly 0");
    test_bool(G.numActions == old_actions + 2, "Number of actions increased by 2");
    test_bool(G.coins == old_coins + 2, "Number of coins increased by 2");
}
