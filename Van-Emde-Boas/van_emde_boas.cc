//does not have deconstructor so dont use this for anything other than learning 
//will leak memory if you use


#include <iostream>
#include <vector>
#include <cmath>

#include "van_emde_boas.h"

//u is the universe size
VEBT::VEBT(size_t u) {

	m_summary = nullptr;
	m_min = -1;
	m_max = -1;
	m_universe = u;

	//if we are not at u = 2
	if (m_universe != 2) {

		//add all the needed children to the cluster vector
		for (int i = 0; i < UpperBound(m_universe); i++) {
			m_clusters.push_back(new VEBT(LowerBound(m_universe)));
		}

		//create the summary
		m_summary = new VEBT(UpperBound(m_universe));
	}
}

int VEBT::UpperBound(int u) {
	int temp = (int)std::ceil(std::log2(u) / 2);
	return (int)std::pow(2, temp);
}



int VEBT::LowerBound(int u) {
	int temp = (int)std::floor(std::log2(u) / 2);
	return (int)std::pow(2, temp);
}



int VEBT::Low(int x) {
	return x % LowerBound(m_universe);
}



int VEBT::High(int x) {
	return (int)std::floor(x / LowerBound(m_universe));
}



int VEBT::Index(int c, int i) {
	return c * LowerBound(m_universe) + i;
}



void VEBT::Insert(int key) {

	//if we dont have min set we can simply replace min with the key
	//we dont store min so no need to recurse
	if (m_min == -1) {
		m_max = key;
		m_min = key;
		return;
	}
	
	//if key is new min we need to insert the old min because it is not stored recursively
	if (key < m_min) {
		int temp = key;
		key = m_min;
		m_min = temp;
	}

	//since we have a new max we replace our max with key
	//we still need to insert the key but do not need to insert the prev max
	//because we store max in the structure recursively
	if (key > m_max) {
		m_max = key;
	}

	//if our universe is two we dont need to recurse
	if (m_universe == 2)
		return;

	//insert into summary if node is empty
	if (m_clusters[High(key)]->m_min == -1) {
		m_summary->Insert(High(key));
	}

	//insert into the right cluster if the if statment above is met that means
	//we had no min so this recursion will be O(1) because it will get caught with first check
	m_clusters[High(key)]->Insert(Low(key));
}



int VEBT::Successor(int key) {

	if (m_universe == 2) {
		if (key == 0 && m_max == 1) {
			return 1;
		}
		else {
			//-1 is our null value for non exist value
			return -1;
		}
	}


	if (key < m_min)
		return m_min;
	

	if (m_clusters[High(key)]->m_min != -1 && Low(key) < m_clusters[High(key)]->m_min) {

		int i = m_clusters[High(key)]->Successor(Low(key));

		//reconstruct our answer from c and i
		return Index(High(key), i);
	}
	
	int c = m_summary->Successor(High(key));

	if (c == -1)
		return -1;

	//reconstruct the answer
	return Index(c, m_clusters[c]->m_min);
}


bool VEBT::ItemExist(int key) {
	if (key == m_min || key == m_max) return true;
	if (m_universe == 2) return false;
	return m_clusters[High(key)]->ItemExist(Low(key));
}
