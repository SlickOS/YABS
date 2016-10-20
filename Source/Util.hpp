#pragma once

#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

namespace Util {
    std::vector<std::string> FindFiles(const std::string &dir, const std::string &ext);
    bool NeedToRebuild(const std::string &obj, const std::string &src);
    bool CheckDirFromFile(const std::string &name);
    bool CheckDir(const std::string &name);
    std::string GetDirFromFile(const std::string &name);
    void CreateDirFromFile(const std::string &file);
    void CreateDir(const std::string &dir);
    void CleanDir(const std::string &dir);
    std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
    void PrintError(const std::string &message, const YAML::Node &node);
    std::vector<std::string> Split(const std::string &str, char delim);
    std::string &LStrip(std::string &s);
    std::string &RStrip(std::string &s);
    std::string &Strip(std::string &s);
    std::map<std::string, std::string> AppendVariables(const std::map<std::string, std::string> &lhs, const std::map<std::string, std::string> &rhs);
}


// #include <map>
// #include <iostream>
// #include <iterator>
// #include <algorithm>

// #include <iostream>
// #include <map>
// #include <numeric>

// int main() 
// {
//     std::map<int, int> m1 = { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 } }; 
//     std::map<int, int> m2 = { { 2, 5 }, { 3, 1 }, { 5, 5 } };

//     for ( const auto &p : m1 ) 
//     {
//         std::cout << "{ " << p.first << ", " << p.second << " } ";
//     }

//     std::cout << std::endl;

//     for ( const auto &p : m2 ) 
//     {
//         std::cout << "{ " << p.first << ", " << p.second << " } ";
//     }

//     std::cout << std::endl;

//     std::map<int, int> m3 = std::accumulate( m1.begin(), m1.end(), std::map<int, int>(),
//         []( std::map<int, int> &m, const std::pair<const int, int> &p )
//         {
//             return ( m[p.first] +=p.second, m );
//         } );

//     m3 = std::accumulate( m2.begin(), m2.end(), m3,
//         []( std::map<int, int> &m, const std::pair<const int, int> &p )
//         {
//             return ( m[p.first] +=p.second, m );
//         } );

//     for ( const auto &p : m3 ) 
//     {
//         std::cout << "{ " << p.first << ", " << p.second << " } ";
//     }

//     std::cout << std::endl;

//     return 0;
// }