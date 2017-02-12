#include "resolver.h"

int main()
{
    const std::vector<std::pair<std::string, std::string>> addresses{
        {{"rambler.ru"}, {"8080"}},
        {{"mail.ru"},{"8080"}},
        {{"rambler.ru"}, {"1000"}},
        {{"rasmadeus.ru"}, {"8080"}},
        {{"sadf.df"}, {"8080"}}
    };

    for(const auto address : addresses)
    {
        std::cout << "Host " << address.first << ":" << address.second << std::endl;
        resolve(address.first, address.second);
    }
}
