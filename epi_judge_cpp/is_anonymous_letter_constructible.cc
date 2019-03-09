#include <string>
#include "test_framework/generic_test.h"
#include <unordered_map>

using namespace std;

bool IsLetterConstructibleFromMagazine(const string& letter_text,
                                       const string& magazine_text) {
	if (letter_text.empty()) return true;
	else if (magazine_text.empty()) return false;

	unordered_map<char, int> letter;
	for (char c : letter_text) {
		letter[tolower(c)]++;
	}
	for (char ch : magazine_text) {
		char c = tolower(ch);
		if (letter.find(c) != letter.end()){
			if(letter[c] == 1) letter.erase(c);
			else letter[c]--;
		}
		if (letter.empty()) return true;
	}
	return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"letter_text", "magazine_text"};
  return GenericTestMain(args, "is_anonymous_letter_constructible.cc",
                         "is_anonymous_letter_constructible.tsv",
                         &IsLetterConstructibleFromMagazine,
                         DefaultComparator{}, param_names);
}
