


#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <unordered_map>

class Trie {
public:

	Trie() : m_is_word{ false } 
	{
	}


	bool Empty() {
		return m_children.empty();
	}



	void Insert(std::string str) {

		if (str.empty())
			return;

		//lowercase the string by reference to reduce memory usage and make not case-sensative
		ToLower(str);

		//edge case of new first character
		if (m_children.find(str[0]) == m_children.end())
			m_children.insert(std::make_pair(str[0], new Trie));

		//will not be unintilized memory because of prev checks
		Trie* cur = m_children.at(str[0]);

		//loop through all the str letters
		for (int i = 1; i < str.size(); i++) {

			//get itterator at beging and then check that itterator to reduce number of hashes for select cases
			auto it = cur->m_children.find(str[i]);

			//if there is no letter in the hashtable add it 
			if (it == cur->m_children.end()) {
				cur->m_children.insert(std::make_pair(str[i], new Trie));
				it = cur->m_children.find(str[i]);
			}
			
			cur = it->second;
		}

		//mark as end of word
		cur->m_is_word = true;
	}


	~Trie() {

		for (auto it = m_children.begin(); it != m_children.end(); it++)
			delete it->second;
	}


	bool Search(std::string str) {

		if (str.empty())
			return false;

		//since str is not empty this will not be unitlilized memory
		auto it = m_children.find(str[0]);

		//if the character is not in the trie node
		if (it == m_children.end())
			return false;

		for (int i = 1; i < str.size(); i++) {

			//if the character is not in the trie we return false
			if (it->second->m_children.find(str[i]) == it->second->m_children.end())
				return false;

			//follow the nodes of the trie
			it = it->second->m_children.find(str[i]);
		}

		//if the series of letters is marked as a word it will be true otherwise false
		return it->second->m_is_word;
	}



	std::unordered_map<char, Trie*> m_children;
	bool m_is_word;

private:


	void ToLower(std::string& str) {
		for (int i = 0; i < str.size(); i++) {
			str[i] = std::tolower(str[i]);
		}
	}
};


#endif // !TRIE_H