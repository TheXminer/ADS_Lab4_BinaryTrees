#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

struct Data {
	string nickname;
	int rang;
	int exp;
	int victoryStat;
	Data() {
		nickname = "-";
		rang = rand()%10;
		exp = 0;
		victoryStat = 0;
	}
	Data(string nickname) {
		this->nickname = nickname;
		rang = 0;
		exp = 0;
		victoryStat = 0;
	}
	Data(int exp) {
		nickname = "-";
		rang = 0;
		this->exp = exp;
		victoryStat = 0;
	}
	Data(string nickname, int rang, int exp, int victoryStat) :
		nickname(nickname),
		rang(rang),
		exp(exp),
		victoryStat(victoryStat) {}

	bool operator<(const Data& second) const {
		if (this->nickname != second.nickname)
			return this->nickname < second.nickname;
		if (this->rang != second.rang)
			return this->rang < second.rang;
		if (this->exp != second.exp)
			return this->exp < second.exp;
		if (this->victoryStat != second.victoryStat)
			return this->victoryStat < second.victoryStat;
		return false;
	}
	bool operator>(const Data& second) const {
		if (this->nickname != second.nickname)
			return this->nickname > second.nickname;
		if (this->rang != second.rang)
			return this->rang > second.rang;
		if (this->exp != second.exp)
			return this->exp > second.exp;
		if (this->victoryStat != second.victoryStat)
			return this->victoryStat > second.victoryStat;
		return false;
	}
	bool operator==(const Data& second) const {
		if (this->nickname == second.nickname && this->rang == second.rang && this->exp == second.exp && this->victoryStat == second.victoryStat)
			return true;
		return false;
	}
	bool operator>=(const Data& second) const {
		return !(*this<(second));
	}
	bool operator<=(const Data& second) const {
		return !(*this>(second));
	}
	bool operator!=(const Data& second) const {
		if (*this == second)
			return false;
		return true;
	}
};

struct Node {
	int rSize;
	Data gamer;
	Node* leftN;
	Node* rightN;
	Node* parent;

	Node() {
		gamer = Data();
		leftN = nullptr;
		rightN = nullptr;
		parent = nullptr;
	}

	Node(Data gamer) {
		this->gamer = gamer;
		rSize = 0;
		leftN = nullptr;
		rightN = nullptr;
		parent = nullptr;
	}
};

struct BinarySearchTree {
	Node* insert(Data& data);
	bool find(const Data& data);
	void erase(Data& data);
	int size();
	void print();
	int height();
	vector<Data> findVectorInRange(Data minObject, Data maxObject);
	int findInRange(Data minObject, Data maxObject);
	bool isSameTree(Node* curNode1, Node* curNode2);
	//Node* split(const Data data);
	//void merge(Node* tree1, Node* tree2);
	//void eraseRange(Data minObject, Data maxObject);
private:
	Node* headNode = nullptr;
	Node* search(Node* curNode, const Data& data);
	bool findInner(Node* curNode, const Data& data);
	void printInner(Node* curNode);
	void printKey(Data* data);
	int sizeInner(Node* curNode);
	int heightInner(Node* curNode);
	int findInnerInRange(Node* curNode, Data* minObject, Data* maxObject);
	vector<Data> findInnerVectorInRange(Node* curNode, Data* minObject, Data* maxObject);

	void balance(Node* parentNode);
	void bigLeftRot(Node* parentNode);
	void bigRightRot(Node* parentNode);
	void smallLeftRot(Node* parentNode);
	void smallRightRot(Node* parentNode);

	//Node* insertInner(Node* curNode, const Data& data, Node* parent);
	//Node* splitTree(Node* parentNode,const Data* data);
};