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
    return edit_distance_within(word1, word2, 1);
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

/* vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
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
} */

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

        // Generate all possible next words
        for (int i = 0; i <= last_word.length(); ++i) {
            string new_word = last_word;
            for (char c = 'a'; c <= 'z'; ++c) {
                // Try inserting a character
                new_word.insert(i, 1, c);
                if ((word_list.count(new_word) || new_word == end_word) && visited.count(new_word) == 0) {
                    visited.insert(new_word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(new_word);
                    ladder_queue.push(new_ladder);
                    if (new_word == end_word) return new_ladder;
                }
                new_word.erase(i, 1);

                // Try replacing a character
                if (i < last_word.length()) {
                    char original = new_word[i];
                    new_word[i] = c;
                    if ((word_list.count(new_word) || new_word == end_word) && visited.count(new_word) == 0) {
                        visited.insert(new_word);
                        vector<string> new_ladder = ladder;
                        new_ladder.push_back(new_word);
                        ladder_queue.push(new_ladder);
                        if (new_word == end_word) return new_ladder;
                    }
                    new_word[i] = original;
                }
            }
            // Try deleting a character
            if (i < last_word.length()) {
                new_word.erase(i, 1);
                if ((word_list.count(new_word) || new_word == end_word) && visited.count(new_word) == 0) {
                    visited.insert(new_word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(new_word);
                    ladder_queue.push(new_ladder);
                    if (new_word == end_word) return new_ladder;
                }
            }
        }
    }

    return {};  // No ladder found
}

void load_words(set<string>& word_list, const string& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i];
            if (i < ladder.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
    } else {
        for (size_t i = 0; i < ladder.size(); ++i) {
            cout << ladder[i];
            if (i < ladder.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }
}

vector<string> g_ladder;
set<string> g_word_list;

void verify_word_ladder() {
    if (g_ladder.size() < 2) {
        cout << "Invalid ladder: too short" << endl;
        return;
    }

    for (size_t i = 1; i < g_ladder.size(); ++i) {
        if (!is_adjacent(g_ladder[i - 1], g_ladder[i])) {
            cout << "Invalid ladder: non-adjacent words " << g_ladder[i - 1] << " and " << g_ladder[i] << endl;
            return;
        }
        if (i > 0 && g_word_list.find(g_ladder[i]) == g_word_list.end()) {
            cout << "Invalid ladder: word not in dictionary: " << g_ladder[i] << endl;
            return;
        }
    }

    cout << "Valid word ladder" << endl;
}