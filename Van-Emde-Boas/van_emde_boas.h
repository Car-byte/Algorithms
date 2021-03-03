
#ifndef VAN_EMDE_BOAS_H
#define VAN_EMDE_BOAS_H

#include <iostream>
#include <vector>

class VEBT {
public:

	VEBT(size_t u);
	void Insert(int key);
	int Successor(int key);
	bool ItemExist(int key);

private:

	int m_min;
	int m_max;
	int m_universe;
	std::vector<VEBT*> m_clusters;
	VEBT* m_summary;

	int Index(int c, int i);
	int Low(int x);
	int High(int x);
	int UpperBound(int u);
	int LowerBound(int u);
};


#endif // !VAN_EMDE_BOAS_H