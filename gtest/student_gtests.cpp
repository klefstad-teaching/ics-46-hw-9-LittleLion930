#include <gtest/gtest.h>

#include "../src/dijkstras.h"
#include "../src/ladder.h"

class LadderTest : public ::testing::Test {
protected:
    void SetUp() override {
        word_list = {"were", "wear", "bear", "beer", "bees", "been", "seen", "seed", "weed"};
    }

    set<string> word_list;
};

TEST_F(LadderTest, SameWordLadder) {
    vector<string> ladder = generate_word_ladder("were", "were", word_list);
    EXPECT_EQ(ladder.size(), 1);
    EXPECT_EQ(ladder[0], "were");
}

TEST_F(LadderTest, WordNotInDictionary) {
    vector<string> ladder = generate_word_ladder("were", "test", word_list);
    EXPECT_TRUE(ladder.empty());
}

TEST_F(LadderTest, LongestPossibleLadder) {
    vector<string> ladder = generate_word_ladder("were", "weed", word_list);
    EXPECT_GE(ladder.size(), 4);
    EXPECT_EQ(ladder[0], "were");
    EXPECT_EQ(ladder[ladder.size() - 1], "weed");
}
