#include<iostream>
#include<vector>

// return true if word1 > word2, and false otherwise
bool compare(const std::vector<char> chars, std::vector<char> & word1, const std::vector<char> & word2) {
    int l = (word1.size() > word2.size()) ? word2.size() : word1.size();

    for (int i = 0; i < l; i++) {
        int order1, order2;
        for (int j = 0; j < chars.size(); j++) {
            if (word1[i] == chars[j]) {
                order1 = j;
                break;
            }
        }

        for (int j = 0; j < chars.size(); j++) {
            if (word2[i] == chars[j]) {
                order2 = j;
                break;
            }
        }

        if (order1 > order2) {
            return true;
        } else if (order1 < order2) {
            return false;
        }
    }

    if (word1.size() > word2.size()) {
        return true;
    }

    return false;
}

void print(std::vector<std::vector<char>> words) {
    for (int i = words.size() - 1; i >= 0; i--) {
        for (int j = 0; j < words[i].size(); j++) {
            std::cout << words[i][j];
        }
        std::cout << std::endl;
    }
}

void quickSort(std::vector<std::vector<char>> & words,std::vector<char> chars, int start, int end) {
    int i = start;
    int j = end;
    int hole = start;
    std::vector<char> tmp = words[start];

    if (end <= start) {
        return;
    }

    while (i < j) {
        while (i < j && compare(chars, tmp, words[j])) {
            j--;
        }
        if (i == j) {
            break;
        }

        words[hole] = words[j];
        hole = j;

        while (i < j && compare(chars, words[i], tmp)) {
            i++;
        }
        if (i == j) {
            break;
        }
        words[hole] = words[i];
        hole = i;
    }
    words[hole] = tmp;

    quickSort(words, chars, start, hole - 1);
    quickSort(words, chars, hole + 1, end);
}

int main() {
    int n, m;
    char c;
    std::vector<char> chars, word;
    std::vector<std::vector<char>> words;

    std::cin >> n >> m;
    std::cin.ignore();

    for (int i = 0; i < n; i++) {
        std::cin >> c;
        chars.push_back(c);
    }
    std::cin.ignore();

    for (int i = 0; i < m; i++) {
        word.clear();

        while (std::cin.get(c) && c != '\n') {
            word.push_back(c);
        }
        
        words.push_back(word);
    }

    quickSort(words, chars, 0, words.size() - 1);

    print(words);

    return 0;
}