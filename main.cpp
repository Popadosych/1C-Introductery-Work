#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include "StringSimilarityCalculator.hpp"

std::string MakeFileName(std::string& file_path) {
    bool is_second_slash = false;
    int index;
    for (int i = file_path.size() - 1; i >= 0; --i) {
        if (file_path[i] == '/') {
            if (!is_second_slash) {
                is_second_slash = true;
            } else {
                index = i + 1;
                break;
            }
        }
    }
    return file_path.substr(index);
}

std::string get_string(std::ifstream& in) {
    std::string str;
    char sym;
    in.get(sym);

    while (!in.eof()) {
        str += sym;
        in.get(sym);
    }
    return str;
}


std::vector<std::string> Process(const std::string& first_dir_path, const std::string& second_dir_path, int percentage) {
    std::vector<std::string> ans;
    const std::filesystem::path first_dir{first_dir_path};
    const std::filesystem::path second_dir{second_dir_path};
    std::ifstream first_file;
    std::ifstream second_file;

    for (auto& first_iterator : std::filesystem::directory_iterator(first_dir)) {
        std::string first_path = first_iterator.path().string();
        first_file.open(first_path);
        std::string first_str = get_string(first_file);

        for (auto& second_iterator : std::filesystem::directory_iterator(second_dir)) {
            std::string second_path = second_iterator.path().string();
            second_file.open(second_path);
            std::string second_str = get_string(second_file);

            std::string review;
            size_t similarity = StringSimilarityCalculator(first_str, second_str);

            std::string first_name = MakeFileName(first_path);
            std::string second_name = MakeFileName(second_path);

           if (similarity >= percentage) {
                review += first_name;
                review += " - ";
                review += second_name;
                if (similarity != 100) {
                    review += " - ";
                    review += std::to_string(similarity);
                }
                ans.push_back(review);
            }

            second_file.close();
        }
        first_file.close();
    }
    return ans;
}

int main(int argc, char* argv[]) {
    auto ans = Process(argv[1], argv[2], atoi(argv[3]));

    for (int i = 0; i < ans.size(); ++i) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}

