#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <unordered_map>

namespace TestConstants {
  const std::string kFirstPath =  "/home/popados/CLionProjects/1C-Introductery-Work/test/first_dir";
  const std::string kSecondPath = "/home/popados/CLionProjects/1C-Introductery-Work/test/second_dir";
};

static const size_t kSubstrLength = 8;


void MakeMap(const std::string& str, std::unordered_map<std::string, int> cnt_substr) {
    for (int i = 0; i + kSubstrLength < str.size(); ++i) {
        std::string substring = str.substr(i, i + kSubstrLength);
        ++cnt_substr[substring];
    }
}

size_t Similirary(const std::string& first_str, const std::string& second_str) {
    std::unordered_map<std::string, int> first_cnt_substr;
    std::unordered_map<std::string, int> second_cnt_substr;
    MakeMap(first_str, first_cnt_substr);
    MakeMap(second_str, second_cnt_substr);

    size_t cnt = 0;
    for (auto [key, value]: first_cnt_substr) {
        if (second_cnt_substr.find(key) != second_cnt_substr.end()) {
            cnt += std::min(value, second_cnt_substr[key]);
        }
    }

    size_t res = (std::max(first_str.size(), second_str.size()) * kSubstrLength * 100) / cnt;
    return res;
}



std::vector<std::string> Process(const std::string& first_dir_path, const std::string& second_dir_path) {
    std::vector<std::string> ans;
    const std::filesystem::path first_dir{first_dir_path};
    const std::filesystem::path second_dir{second_dir_path};
    std::ifstream first_file;
    std::ifstream second_file;

    for (auto& first_iterator : std::filesystem::directory_iterator(first_dir)) {
        first_file.open(first_iterator.path().string());
        size_t last_slash = first_iterator.path().string().rfind("/");
        std::string first_name = first_iterator.path().string().substr(last_slash + 1);
        std::string first_str;
        char sym;
        first_file.get(sym);

        while (!first_file.eof()) {
            first_str += sym;
            first_file.get(sym);
        }

        for (auto& second_iterator : std::filesystem::directory_iterator(second_dir)) {
            last_slash = second_iterator.path().string().rfind("/");
            std::string second_name = second_iterator.path().string().substr(last_slash + 1);
            second_file.open(second_iterator.path().string());
            std::string second_str;

            char ch;
            second_file.get(ch);

            while (!second_file.eof()) {
                second_str += ch;
                second_file.get(ch);
            }
            std::string review;
            if (first_str == second_str) {
                review = first_name + " is identical with " + second_name;
                ans.push_back(review);
                std::cout << review << '\n';
            }
        }
    }
    return ans;
}

int main() {
    Process(TestConstants::kFirstPath, TestConstants::kSecondPath);
    return 0;
}

