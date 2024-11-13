#include "CMTL/common/attributes.h"
#include <iostream>

int main()
{
    CMTL::geometry::Attributes attr;
    attr.set<int>("number") = 1;
    attr.set<std::string>("string") = "hello";
    std::cout << attr.get<int>("number") << " " << attr.get<std::string>("string") << std::endl;
    attr.set<int>("number") = 2;
    attr.set<std::string>("string") = "world";
    std::cout << attr.get<int>("number") << " " << attr.get<std::string>("string") << std::endl;
    return 0;
}