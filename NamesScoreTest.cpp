#include <gtest/gtest.h>

#include "NamesScore.hpp"

using namespace ::testing;

TEST(NameScoreErrorsHandling, shouldReturnZeroWhenFileDoesNotExists)
{
    constexpr auto unknownFilePath = "../xtf/tdt.txt";
    ASSERT_EQ(getNamesScore(unknownFilePath), 0);
}

TEST(NameScoreErrorsHandling, shouldReturnZeroWhenFileIsEmpty)
{
    ASSERT_EQ(getNamesScore("../names_scores_test/empty.txt"), 0);
}

TEST(NameScoreTest, shouldCalculateNameScoreForLowerCaseNames)
{
    ASSERT_EQ(getNamesScore("../names_scores_test/lowerCase.txt"), 25);
}

TEST(NameScoreTest, shouldCalculateNameScoreForMixedCaseNames)
{
    ASSERT_EQ(getNamesScore("../names_scores_test/mixedCase.txt"), 22);
}

TEST(NameScoreTest, shouldCalculateNameScoreForUpperCaseNames)
{
    ASSERT_EQ(getNamesScore("../names_scores_test/upperCase.txt"), 25);
}

TEST(NameScoreTest, shouldCalculateNameScoreWhenOneOfNamesIsMissing)
{
    ASSERT_EQ(getNamesScore("../names_scores_test/missingName.txt"), 25);
}

TEST(NameScoreTest, finalAttemptForDataGivenFromProjectEuler)
{
    constexpr auto expectedValue = 871198282u;
    ASSERT_EQ(getNamesScore("../names_scores_test/p022_names.txt"), expectedValue);
}
