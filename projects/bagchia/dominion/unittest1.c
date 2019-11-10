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
    printf("Unit Test 1: Baron\n");
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
    //Fill the player's hand with coppers as a place holder
    memcpy(G.hand[0], coppers, sizeof(int) * handCount);

    //Give the player a baron and 2 estates
    G.hand[0][0] = baron;
    G.hand[0][1] = estate;
    G.hand[0][4] = estate;

    int old_hand_count = G.handCount[0];
    int old_discard_count = G.discardCount[0];
    int old_played_count = G.playedCardCount;
    int old_coins = G.coins;
    printf("Play the baron and choose to discard the an estate\n");
    baronEffect(1, &G);
    test_bool(G.handCount[0] == old_hand_count - 2, "Player's handcount has decreased by 2 (1 for estate and 1 for baron)");
    test_bool(count_array(G.hand[0], G.handCount[0], estate) == 1, "Exactly one estate remaining in hand");
    test_bool(count_array(G.hand[0], G.handCount[0], baron) == 0, "Exactly zero barons remaining in hand");
    test_bool(G.discardCount[0] == old_discard_count + 1, "Player's discard count increased by 1");
    test_bool(count_array(G.discard[0], G.discardCount[0], estate) == 1, "Discard contains exactly one estate");
    test_bool(G.playedCardCount == old_played_count + 1, "Number of played cards increased by 1");
    test_bool(count_array(G.playedCards, G.playedCardCount, baron) == 1, "Played pile contains exactly 1 baron");
    test_bool(G.coins == old_coins + 4, "Coins increased by 4");

    G.hand[0][0] = baron;
    printf("Play the baron and choose to gain an estate\n");
    int old_deck_count = G.deckCount[0];
    int old_estates_deck = count_array(G.deck[0], G.deckCount[0], estate);
    int old_estate_supply_count = supplyCount(estate, &G);
    old_hand_count = G.handCount[0];
    old_discard_count = G.discardCount[0];
    old_played_count = G.playedCardCount;
    old_coins = G.coins;
    baronEffect(0, &G);
    test_bool(G.handCount[0] == old_hand_count - 1, "Player's handcount has decreased by 1");
    test_bool(count_array(G.hand[0], G.handCount[0], estate) == 1, "Exactly one estate still remaining in hand");
    test_bool(G.playedCardCount == old_played_count + 1, "Number of played cards increased by 1");
    test_bool(count_array(G.playedCards, G.playedCardCount, baron) == 1, "Played pile contains exactly 1 baron");
    test_bool(G.coins == old_coins, "Coins remains the same");
    test_bool(G.deckCount == old_deck_count + 1, "Player's deck size increased by one");
    test_bool(count_array(G.deck[0], G.deckCount[0], estate) == old_estates_deck + 1, "One more estate in the player's deck");
    test_bool(supplyCount(estate, &G) == old_estate_supply_count - 1, "Number of estates in supply decremented by one");
    test_bool(isGameOver(&G) != 1, "Gameover condition is not met");

    G.hand[0][3] = copper;
    G.hand[0][3] = copper;
    printf("Play the baron and choose to discard an estate with no estates remaining in the hand (should gain estate in deck)\n");
    old_deck_count = G.deckCount[0];
    old_estates_deck = count_array(G.deck[0], G.deckCount[0], estate);
    old_estate_supply_count = supplyCount(estate, &G);
    old_hand_count = G.handCount[0];
    old_discard_count = G.discardCount[0];
    old_played_count = G.playedCardCount;
    old_coins = G.coins;
    baronEffect(1, &G);
    test_bool(G.handCount[0] == old_hand_count - 1, "Player's handcount has decreased by 1");
    test_bool(count_array(G.hand[0], G.handCount[0], estate) == 0, "Exactly zero estate still remaining in hand");
    test_bool(G.playedCardCount == old_played_count + 1, "Number of played cards increased by 1");
    test_bool(count_array(G.playedCards, G.playedCardCount, baron) == 1, "Played pile contains exactly 1 baron");
    test_bool(G.coins == old_coins, "Coins remains the same");
    test_bool(G.deckCount == old_deck_count + 1, "Player's deck size increased by one");
    test_bool(count_array(G.deck[0], G.deckCount[0], estate) == old_estates_deck + 1, "One more estate in the player's deck");
    test_bool(supplyCount(estate, &G) == old_estate_supply_count - 1, "Number of estates in supply decremented by one");
    test_bool(isGameOver(&G) != 1, "Gameover condition is not met");

    G.supplyCount[sea_hag] = 0;
    G.supplyCount[mine] = 0;
    G.supplyCount[estate] = 1;
    G.hand[0][3] = copper;
    printf("Play the baron and choose to gain an estate as it depletes the third supply\n");
    baronEffect(0, &G);
    test_bool(isGameOver(&G) == 1, "Gameover condition is met");
}
