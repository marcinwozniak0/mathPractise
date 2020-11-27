#include <fstream>
#include <iostream>
#include "NamesScore.hpp"
#include <algorithm>
#include <exception>

namespace
{
ReturnValue countNameValue(const std::string& name)
{
    ReturnValue result {};

    for (const auto c : name)
    {
        result += std::toupper(c) - '@';
    }
    return result;
}

void updateResult(ReturnValue& result, const ReturnValue valueToAdd)
{
    result += valueToAdd;
    if (result < 0)
    {
        throw std::overflow_error("Overflow of result value");
    }
}

ReturnValue countNamesValue(const std::vector<std::string>& names)
{
    ReturnValue result {};
    auto namePosition = 1u;

    for (const auto& name : names)
    {
        if (not name.empty())
        {
            updateResult(result, countNameValue(name) * namePosition);
            ++namePosition;
        }
    }

    return result;
}

std::vector<std::string> extractNames(const std::string& names)
{
    std::vector<std::string> extractedNames {};
    auto firstDelimer = names.find_first_of('"');
    auto lastDelimer = names.find_first_of('"', firstDelimer + 1);

    while (std::string::npos not_eq firstDelimer)
    {
        const auto extractedName = std::string{names.begin() + firstDelimer + 1,
                                               names.begin() + lastDelimer};
        extractedNames.push_back(extractedName);

        firstDelimer = names.find_first_of('"', lastDelimer + 1);
        lastDelimer = names.find_first_of('"', firstDelimer + 1);
    }

    return extractedNames;
}
} //namespace

ReturnValue getNamesScore(const std::string& fileName) try
{
    if(std::ifstream fileToOpen(fileName);
       fileToOpen.is_open())
    {
        ReturnValue result {};
        std::string buffer;

        while(getline(fileToOpen, buffer))
        {
            auto extractedNames = extractNames(buffer);
            std::sort(extractedNames.begin(), extractedNames.end());

            updateResult(result, countNamesValue(extractedNames));
        }

        return result;
    }

    return 0;
}
catch(const std::overflow_error& e)
{
    std::cerr << e.what() << std::endl;
    return 0;
}
