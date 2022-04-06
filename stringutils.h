#pragma once

#include <vector>
#include <algorithm>

namespace String
{
    class StringUtils
    {
    public:
        static std::vector<std::string> Split(std::string s, std::string delimiter)
        {
            size_t pos_start = 0, pos_end, delim_len = delimiter.length();
            std::string token;
            std::vector<std::string> res;

            while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
                token = s.substr(pos_start, pos_end - pos_start);
                pos_start = pos_end + delim_len;
                res.push_back(token);
            }

            res.push_back(s.substr(pos_start));
            return res;
        }
        
        static std::string ToLower(std::string str)
        {
            std::for_each(str.begin(), str.end(), [](char& c) {
                c = ::tolower(c);
                });
            return str;
        }
    };
}
