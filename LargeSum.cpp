#include "LargeSum.hpp"

namespace
{
std::string getResultWithoutUnnecessaryZeros(std::string&& result)
{
    if (result.front() == '0')
    {
        return {result.begin() + 1, result.end()};
    }
    else
    {
        return result;
    }
}

void addRemainedCarry(const uint remainedCarry, const auto resultIt)
{
    if (0 != remainedCarry)
    {
         *resultIt += remainedCarry;
    }
}
} //namesapce

std::string sumOfLargeNumbers(const std::string& x, const std::string& y)
{
    auto& shorterNumber = x.size() >= y.size() ? y : x;
    auto& longerNumber = x.size() >= y.size() ? x : y;

    uint carry = 0u;
    std::string result(longerNumber.size() + 1, '0');
    auto shorterNumberIt = shorterNumber.rbegin();
    auto longerNumberIt = longerNumber.rbegin();
    auto resultNumberIt = result.rbegin();

    for (;std::distance(longerNumber.rbegin(), longerNumberIt) < shorterNumber.size();
         ++shorterNumberIt, ++longerNumberIt, ++resultNumberIt)
    {

        const auto value = *shorterNumberIt - '0' + *longerNumberIt - '0' + carry;
        carry = value / 10;
        *resultNumberIt += (value % 10);
    }

    addRemainedCarry(carry, resultNumberIt);

    for (;longerNumberIt < longerNumber.rend();
         ++longerNumberIt, ++resultNumberIt)
    {
        const auto value = *resultNumberIt - '0' + *longerNumberIt - '0';
        carry = value / 10;

        addRemainedCarry(carry, std::next(resultNumberIt, 1));

        *resultNumberIt = (value % 10) + '0';

    }

    return getResultWithoutUnnecessaryZeros(std::move(result));
}


std::string largeSumProjectEuler(const std::vector<std::string>& input)
{
    std::string result;
    for (const auto& number : input)
    {
        result = sumOfLargeNumbers(result, number);
    }

    return {result.begin(), result.begin() + 10};
}
