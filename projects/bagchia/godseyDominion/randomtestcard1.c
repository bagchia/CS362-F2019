#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include "test_assert.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define NUM_ITERATIONS 1000;

int main()
{
    srand(time(NULL));
    printf("Random Test 1: Baron\n");
    int r, i;
    int seed = 2;
    int handCount = 5;
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
    r = initializeGame(2, kingdom, seed, &G); // initialize a new game
    G.handCount[0] = handCount;               // set any other variables

    for (i = 0; i < 1000; i++)
    {
        int j;
        //Give the player a random hand size
        G.handCount[0] = rand_range(5, 10);
        //Fill the player's hand with coppers as a place holder
        for (j = 0; j < G.handCount[0]; j++)
        {
            G.hand[0][j] = copper;
        }
        int num_rand_estates = rand_range(0, 3);
        for (j = 0; j < num_rand_estates; j++)
        {
            G.hand[0][rand_range(0, G.handCount[0] - 1)] = estate;
        }
        G.hand[0][0] = baron;
        G.supplyCount[estate] = rand_range(0, 3);
        int choice = rand_range(0, 1);
        int num_estates = count_array(G.hand[0], G.handCount[0], estate);
        int old_coins = G.coins;
        int old_hand_count = G.handCount[0];
        int old_played_count = G.playedCardCount;
        int old_deck_count = G.deckCount[0];
        int old_estate_supply_count = G.supplyCount[estate];
        playBaron(choice, 0, 0, &G, 0, NULL, 0);
        //baronEffect(choice, &G);
        printHand(0, &G);
        printf("Playing Baron with choice = %d\n", choice);
        if (choice == 1)
        {
            if (num_estates != 0)
            {
                test_bool(G.handCount[0] == old_hand_count - 2, "Player's handcount has decreased by 2 (1 for estate and 1 for baron)");
                test_bool(count_array(G.hand[0], G.handCount[0], estate) == num_estates - 1, "Exactly one less estate remaining in hand");
                test_bool(count_array(G.hand[0], G.handCount[0], baron) == 0, "Exactly zero barons remaining in hand");
                test_bool(G.coins == old_coins + 4, "Coins increased by 4");
            }
            else if(num_estates == 0){
                test_bool(G.handCount[0] == old_hand_count - 1, "Player's handcount stays the same");
                test_bool(count_array(G.hand[0], G.handCount[0], estate) == num_estates + 1, "One more estate in hand");
                test_bool(G.playedCardCount == old_played_count + 1, "Number of played cards increased by 1");
                test_bool(G.coins == old_coins, "Coins remains the same");
                test_bool(G.deckCount == old_deck_count + 1, "Player's deck size increased by one");
                test_bool(supplyCount(estate, &G) == old_estate_supply_count - 1, "Number of estates in supply decremented by one");
                if(old_estate_supply_count != 0){
                    test_bool(isGameOver(&G) != 1, "Gameover condition is not met");
                }
                else{
                    test_bool(isGameOver(&G) != 1, "Gameover condition is met");
                }
            }
        }
        else{
                test_bool(G.handCount[0] == old_hand_count - 1, "Player's handcount stays the same");
                test_bool(count_array(G.hand[0], G.handCount[0], estate) == num_estates + 1, "One more estate in hand");
                test_bool(G.playedCardCount == old_played_count + 1, "Number of played cards increased by 1");
                test_bool(G.coins == old_coins, "Coins remains the same");
                test_bool(G.deckCount == old_deck_count + 1, "Player's deck size increased by one");
                test_bool(supplyCount(estate, &G) == old_estate_supply_count - 1, "Number of estates in supply decremented by one");
                if(old_estate_supply_count != 0){
                    test_bool(isGameOver(&G) != 1, "Gameover condition is not met");
                }
                else{
                    test_bool(isGameOver(&G) != 1, "Gameover condition is met");
                }
        }
    }
}