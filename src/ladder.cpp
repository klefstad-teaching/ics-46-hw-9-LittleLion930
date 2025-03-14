#include "ladder.h"
#include <algorithm>

void error(string word1, string word2, string msg) {
    cerr << "Error: " << msg << " for words '" << word1 << "' and '" << word2 << "'." << endl;
}

bool edit_distance_within(const string& str1, const string& str2, int d) {
    int m = str1.length();
    int n = str2.length();
    if (abs(m - n) > d) return false;

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i-1] == str2[j-1])
                dp[i][j] = dp[i-1][j-1];
            else 
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }

    return dp[m][n] <= d;
}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1.length() != word2.length()) return false;
    int differences = 0;
    for (size_t i = 0; i < word1.length(); ++i) {
        if (word1[i] != word2[i]) differences++;
        if (differences > 1) return false;
    }
    return differences == 1;
}

/* function generate_word_ladder(begin_word, end_word, word_list):
    ladder_queue = queue of vector of strings
    ladder_queue.push([begin_word])
    visited = set of strings
    visited.insert(begin_word)
    while ladder_queue is not empty:
        ladder = ladder_queue.pop_front()
        last_word = last element of ladder
        for word in word_list:
            if is_adjacent(last_word, word):
                if word not in visited:
                    visited.insert(word)
                    new_ladder = copy of ladder
                    new_ladder.push_back(word)
                    if word equals end_word:
                        return new_ladder
                    ladder_queue.push(new_ladder)
    return no ladder found
end function */

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();

        if (last_word == end_word) {
            return ladder;
        }

        for (const string& word : word_list) {
            if (is_adjacent(last_word, word) && visited.find(word) == visited.end()) {
                visited.insert(word);
                vector<string> new_ladder = ladder;
                new_ladder.push_back(word);
                ladder_queue.push(new_ladder);
            }
        }
    }

    return {};
} 

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << file_name << endl;
        return;
    }

    string word;
    while (file >> word) {
        word_list.insert(word);
    }

    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i];
            if (i < ladder.size() - 1) {
                cout << " ";
            }
        }
        cout << " " << endl;
    }
}

void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");

    auto test_ladder = [&word_list](const string& start, const string& end, int expected_size) {
        vector<string> ladder = generate_word_ladder(start, end, word_list);
        bool passed = ladder.size() == expected_size;
        cout << "Ladder from " << start << " to " << end 
             << (passed ? " passed" : " failed")
             << " (expected size: " << expected_size 
             << ", actual size: " << ladder.size() << ")" << endl;
        return passed;
    };
}