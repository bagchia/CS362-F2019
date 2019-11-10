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
    printf("Unit Test 2: Minion\n");
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

    //Give the player a minion and 5 other cards
    G.handCount[0] = 6;
    G.hand[0][0] = minion;
    G.hand[0][1] = baron;
    G.hand[0][2] = estate;
    G.hand[0][3] = gardens;
    G.hand[0][4] = baron;
    G.hand[0][5] = province;

    //Give another player < 5 cards
    G.handCount[1] = 3;
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;
    G.hand[1][2] = copper;

    
    //Give another player > 5 cards
    G.handCount[2] = 6;
    G.hand[1][0] = copper;
    G.hand[1][1] = copper;
    G.hand[1][2] = copper;
    G.hand[1][3] = gold;
    G.hand[1][4] = gold;
    G.hand[1][5] = gold;

    printf("Play the minion and opt to recieve 2 coins\n");
    int old_coins = G.coins;
    minionEffect(1, 0, &G, 0);
    test_bool(count_array(G.hand[0], G.handCount[0], minion) == 0, "The player now has exactly 0 minions in hand");
    test_bool(count_array(G.playedCards, G.playedCardCount, minion) == 1, "There is exactly 1 minion in the played cards pile");
    test_bool(G.coins == old_coins + 2, "The number of coins has increased by exactly 2");

    printf("Play the minion and opt to discard your hand\n");
    old_coins = G.coins;
    int old_hand[G.handCount[0]];
    memcpy(old_hand, G.hand[0], sizeof(int) * G.handCount[0]);
    int old_hand_p2[G.handCount[1]];
    memcpy(old_hand_p2, G.hand[1], sizeof(int) * G.handCount[1]);
    int old_hand_p3[G.handCount[2]];
    memcpy(old_hand_p3, G.hand[2], sizeof(int) * G.handCount[2]);
    minionEffect(0, 1, &G, 0);
    test_bool(count_array(G.hand[0], G.handCount[0], minion) == 0, "The player now has exactly 0 minions in hand");
    test_bool(count_array(G.playedCards, G.playedCardCount, minion) == 1, "There is exactly 1 minion in the played cards pile");
    test_bool(G.coins == old_coins, "The number of coins is unchanged");
    test_bool(memcmp(old_hand, G.hand[0], sizeof(int)*G.handCount[0]) != 0, "Current player got a new hand");
    test_bool(G.handCount[0] == 4, "Current player has 4 cards");
    test_bool(memcmp(old_hand_p2, G.hand[1], sizeof(int)*G.handCount[1]) == 0, "Player with < 5 card's hand left intact");
    test_bool(memcmp(old_hand, G.hand[2], sizeof(int)*G.handCount[2]) != 0, "Player with < 5 got a new hand");
    test_bool(G.handCount[2] == 4, "Player with < 5 cards has 4 cards now");
    test_bool(G.playedCardCount == 8, "Exactly 8 cards played between 2 players");
}
