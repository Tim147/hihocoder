#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef struct trie_node {
	int count;
	trie_node *next[26];
};

trie_node* create_trie_node() {
	trie_node *node = new trie_node;
	node->count = 1;
	for (int i = 0; i < 26; ++i) node->next[i] = NULL;
	return node;
}

int search_trie(trie_node* head, const string& word) {
	trie_node* ptr = head;
	int i = 0;
	while (i < word.size()) {
		if (ptr->next[word[i] - 'a'] != NULL) {
			ptr = ptr->next[word[i] - 'a'];
			++i;
		}
		else {
			return 0;
		}
	}
	int count = ptr->count; 
	return count;
}

void build_trie(trie_node* ptr, const string& word) {
	if (ptr == NULL) return ;
	int i = 0;
	for (; i < word.size(); ++i) {
		if (ptr->next[word[i] - 'a'] != NULL) {
			ptr = ptr->next[word[i] - 'a'];
			ptr->count++;
		}
		else {
			ptr->next[word[i] - 'a'] = create_trie_node();
			ptr = ptr->next[word[i] - 'a'];
		}
	}
}

void delete_trie(trie_node* ptr) {
	for (int i = 0; i < 26; ++i) {
		if (ptr->next[i] != NULL) {
			delete_trie(ptr->next[i]);
		}
	}
	delete ptr;
}

int main() {
	int dict_num, word_num;
	trie_node *head = create_trie_node();
	cin >> dict_num;
	for (int i = 0; i < dict_num; ++i) {
		string dict_word;
		cin >> dict_word;
		build_trie(head, dict_word);
	}
	cin >> word_num;
	vector<int> nums(word_num, 0);
	for (int i = 0; i < word_num; ++i) {
		string word;
		cin >> word;
		nums[i] = search_trie(head, word);
	}
	for (int i = 0; i < word_num; ++i)
		cout << nums[i] << endl;
	delete_trie(head);
	return 0;
}