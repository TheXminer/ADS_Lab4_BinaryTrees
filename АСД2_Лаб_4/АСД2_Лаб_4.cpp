#include <iostream>
#include "binarySearchTree.h"

#include <set>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

long long generateRandLong() {
	long long number = 0;
	int lengthNumber = rand() % 5 + 11;
	for (int i = 0; i < lengthNumber; i++) {
		number = number * 10 + rand() % 10;
	}
	return number;
}

bool testBinarySearchTree()
{
	srand(time(NULL));
	const int iters = 30000;
	const int keysAmount = iters * 2;
	const int itersToRangeQueries = 1000;
	vector<Data> data(keysAmount);
	vector<Data> dataToInsert(iters);
	vector<Data> dataToErase(iters);
	vector<Data> dataToFind(iters);
	vector<pair<Data, Data>> dataToRangeQueries;
	for (int i = 0; i < iters; i++)
	{
		dataToInsert[i] = Data(generateRandLong() % keysAmount);
		dataToErase[i] = Data(generateRandLong() % keysAmount);
		dataToFind[i] = Data(generateRandLong() % keysAmount);
	}
	for (int i = 0; i < itersToRangeQueries; i++)
	{
		Data minData = Data();
		Data maxData = Data();
		if (maxData < minData)
		{
			swap(minData, maxData);
		}
		dataToRangeQueries.push_back({ minData, maxData });
	}
	BinarySearchTree myTree;
	clock_t myStart = clock();
	for (int i = 0; i < iters; i++)
	{
		myTree.insert(dataToInsert[i]);
	}
	int myInsertSize = myTree.size();
	int myTreeHeight = myTree.height();
	int optimalTreeHeight = log2(myInsertSize) + 1;
	for (int i = 0; i < iters; i++)
	{
		myTree.erase(dataToErase[i]);
	}
	int myEraseSize = myInsertSize - myTree.size();
	int myFoundAmount = 0;
	for (int i = 0; i < iters; i++)
	{
		if (myTree.find(dataToFind[i]))
		{
			myFoundAmount++;
		}
	}
	clock_t myEnd = clock();
	float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;

	set<Data> stlTree;
	clock_t stlStart = clock();
	for (int i = 0; i < iters; i++)
	{
		stlTree.insert(dataToInsert[i]);
	}
	int stlInsertSize = stlTree.size();
	for (int i = 0; i < iters; i++)
	{
		stlTree.erase(dataToErase[i]);
	}
	int stlEraseSize = stlInsertSize - stlTree.size();
	int stlFoundAmount = 0;
	for (int i = 0; i < iters; i++)
	{
		if (stlTree.find(dataToFind[i]) != stlTree.end())
		{
			stlFoundAmount++;
		}
	}
	clock_t stlEnd = clock();
	float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
	clock_t myRangeStart = clock();
	int myRangeFoundAmount = 0;
	for (int i = 0; i < itersToRangeQueries; i++)
	{
		myRangeFoundAmount += myTree.findInRange(dataToRangeQueries[i].first, dataToRangeQueries[i].second);
	}
	clock_t myRangeEnd = clock();
	float myRangeTime = (float(myRangeEnd - myRangeStart)) / CLOCKS_PER_SEC;
	clock_t stlRangeStart = clock();
	int stlRangeFoundAmount = 0;
	for (int i = 0; i < itersToRangeQueries; i++)
	{
		const auto& low = stlTree.lower_bound(dataToRangeQueries[i].first);
		const auto& up = stlTree.upper_bound(dataToRangeQueries[i].second);
		stlRangeFoundAmount += distance(low, up);
	}
	clock_t stlRangeEnd = clock();
	float stlRangeTime = (float(stlRangeEnd - stlRangeStart)) / CLOCKS_PER_SEC;
	cout << "My BinaryTree: height = " << myTreeHeight << ", optimal height = " <<  optimalTreeHeight << endl;
	cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ", found amount : " << myFoundAmount << endl;
	cout << "Range time: " << myRangeTime << ", range found amount: " << myRangeFoundAmount	<< endl << endl;
	cout << "STL Tree:" << endl;
	cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize << ", found amount: " << stlFoundAmount << endl;
	cout << "Range time: " << stlRangeTime << ", range found amount: " << stlRangeFoundAmount << endl << endl;
	if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount == stlFoundAmount && myRangeFoundAmount == stlRangeFoundAmount)
	{
		cout << "The lab is completed" << endl;
		return true;
	}
	cerr << ":(" << endl;
	return false;
}

using namespace std;

int main()
{
	testBinarySearchTree();
	

	//srand(time(NULL));
	//cout << endl << endl << endl;
	//Data a = { "a", 0, 0, 0 };
	//Data b = { "b", 0, 0, 0 };
	//Data c = { "c", 0, 0, 0 };
	//Data d = { "d", 0, 0, 0 };
	//Data e = { "e", 0, 0, 0 };
	//Data f = { "f", 0, 0, 0 };
	//Data g = { "g", 0, 0, 0 };
	//Data h = { "h", 0, 0, 0 };
	//Data i = { "i", 0, 0, 0 };
	//Data j = { "j", 0, 0, 0 };
	//BinarySearchTree tree;
	//tree.insert(a);
	//tree.insert(b);
	//tree.insert(c);
	//tree.print();
	//cout << endl << "H: " << tree.height() << " S: " << tree.size() << " optimal H: " << log2(tree.size()) + 1 << endl;

	/*tree.insert(d);
	tree.insert(f);
	tree.insert(e);
	tree.insert(g);
	tree.insert(h);
	tree.insert(i);
	tree.insert(j);
	for (int i = 0; i < 20000; i++) {
		int exp = generateRandLong() % 160000;
		Data dt = Data(exp);
		tree.insert(dt);
	}*/
	
	////for (int i = 0; i < 1000; i++) {
	//	int exp = rand() % 10000;
	//	Data dt = Data(exp);
	//	tree.erase(f);
	//	//tree.print();
	//	cout << endl << "H: " << tree.height() << " S: " << tree.size();

	//}
	//tree.insert(j);
	//tree.insert(i);
	//tree.insert(h);
	//tree.insert(g);
	//tree.insert(f);
	//tree.insert(e);
	//tree.insert(d);
	//tree.insert(c);
	//tree.insert(b);
	//tree.insert(a);
	//tree.print();
	//cout << endl << tree.height() << " h";
	//cout << endl << endl << endl;
	//tree.merge(tree.split(d), tree.headNode);
	//tree.split(j);
	//tree.print();
}