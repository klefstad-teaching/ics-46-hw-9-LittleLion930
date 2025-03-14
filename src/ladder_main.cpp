#include "ladder.h"

extern vector<string> g_ladder;
extern set<string> g_word_list;

int main() {
    set<string> dictionary;
    load_words(dictionary, "words.txt");

    string start_word, end_word;
    cout << "Enter start word: ";
    cin >> start_word;
    cout << "Enter end word: ";
    cin >> end_word;

    vector<string> ladder = generate_word_ladder(start_word, end_word, dictionary);
    print_word_ladder(ladder);

    g_ladder = ladder;
    g_word_list = dictionary;

    verify_word_ladder();

    return 0;
}