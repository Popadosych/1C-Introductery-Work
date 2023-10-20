#include "StringSimilarityCalculator.hpp"
#include <cmath>
#include <unordered_map>

void MakeMap(const std::string& str, std::unordered_map<std::string, int>& cnt_substr, int substr_length) {
    for (int i = 0; i + substr_length - 1 < str.size(); ++i) {
        std::string substring = str.substr(i, substr_length);
        ++cnt_substr[substring];
    }
}

size_t StringSimilarityCalculator(const std::string& first_str, const std::string& second_str) {
    if (first_str.empty() || second_str.empty()) {
        return 0; //can't calculate this scenary
    }
    if (first_str == second_str) {
        return 100; //100 percentage
    }
    int substr_length = log(std::min(first_str.size(), second_str.size())) / 2 + 1;
    std::unordered_map<std::string, int> first_cnt_substr;
    std::unordered_map<std::string, int> second_cnt_substr;
    MakeMap(first_str, first_cnt_substr, substr_length);
    MakeMap(second_str, second_cnt_substr, substr_length);

    size_t cnt = 0;
    for (auto [key, value]: first_cnt_substr) {
        if (second_cnt_substr.find(key) != second_cnt_substr.end()) {
            cnt += std::min(value, second_cnt_substr[key]);
        }
    }

    size_t res = (cnt * 100) / (std::max(first_str.size(), second_str.size()) - substr_length + 1) ;
    return res;
}
