#include "binarySearchTree.h"

Node* BinarySearchTree::insert(Data& data) {
	if(!headNode) {
		Node* newNode = new Node(data);
		headNode = newNode;
		return headNode;
	}
	Node* curNode = headNode;
	Node* parent = nullptr;
	while (true) {
		if (!curNode) {
			Node* newNode = new Node(data); 
			newNode->parent = parent; 
			newNode->rSize = 0; 
			if (parent->gamer < data)
				parent->rightN = newNode;
			else parent->leftN = newNode;
			balance(parent);
			break;
		}
		parent = curNode;
		if (curNode->gamer == data)
			break;
		if (curNode->gamer < data)
			curNode = curNode->rightN;
		else curNode = curNode->leftN;
	}
	return curNode;
}


bool BinarySearchTree::find(const Data& data) {
	return findInner(headNode, data);
}

bool BinarySearchTree::findInner(Node* curNode, const Data& data) {
	if (!curNode)
		return false;		
	if (curNode->gamer < data)
		return findInner(curNode->rightN, data);
	if (curNode->gamer > data)
		return findInner(curNode->leftN, data);
	return true;
}

void BinarySearchTree::erase(Data& data) {
	Node* found = search(headNode, data);
	//deleting element
	if (!found)	//Not founded
		return;
	if (!found->leftN && !found->rightN) {
		if (found == headNode) {
			delete headNode;
			headNode = nullptr;
			return;
		}
		if (found->parent->leftN == found) {
			found->parent->leftN = nullptr;
		}
		if (found->parent->rightN == found) {
			found->parent->rightN = nullptr;
		}
		balance(found->parent);
		delete found;
		return;
	}
	if (!found->leftN && found->rightN) {//Only right child
		if (found == headNode) {
			headNode = headNode->rightN;
		}
		if (found->parent->leftN == found) {
			found->parent->leftN = found->rightN;
		}
		else {
			found->parent->rightN = found->rightN;
		}
		found->rightN->parent = found->parent;
		balance(found->parent);
		delete found;
		return;
	}
	if (found->leftN && !found->rightN) {//Only left child
		if (found == headNode) {
			headNode = headNode->leftN;
		}
		if (found->parent->leftN == found) {	
			found->parent->leftN = found->leftN;
		}
		else {
			found->parent->rightN = found->leftN;
		}
		found->leftN->parent = found->parent;
		balance(found->parent);
		delete found;
		return;
	}
	Node* curNode = found->rightN;
	while (curNode->leftN) {//Find right min element
		curNode = curNode->leftN;
	}
	found->gamer = curNode->gamer;
	if (curNode == found->rightN) {//If min is foundNode child
		if (curNode->rightN)//If del element has child
			curNode->rightN->parent = found;
		found->rightN = curNode->rightN;
		delete curNode;
		return;
	}
	if (curNode->rightN) {//If min has right child
		Node* toDelete = curNode;
		curNode->parent->leftN = curNode->rightN;
		curNode->rightN->parent = curNode->parent;
		balance(found->parent);
		delete curNode;
		return;
	}
	//If min has not any child
	curNode->parent->leftN = nullptr;
	balance(found->parent);
	delete curNode;
	return;
}

Node* BinarySearchTree::search(Node* curNode, const Data& data) {
	if (!curNode || curNode->gamer == data)
		return curNode;
	if (curNode->gamer < data)
		return search(curNode->rightN, data);
	if (curNode->gamer > data)
		return search(curNode->leftN, data);
}

int BinarySearchTree::size() {
	return sizeInner(headNode);
}

int BinarySearchTree::sizeInner(Node* curNode) {
	if (!curNode)
		return 0;
	return 1 + sizeInner(curNode->leftN) + sizeInner(curNode->rightN);
}

void BinarySearchTree::print() {
	printInner(headNode);
}

void BinarySearchTree::printInner(Node* curNode) {
	if (!curNode)
		return;
	printInner(curNode->leftN);
	printKey(&curNode->gamer);
	printInner(curNode->rightN);
}

void BinarySearchTree::printKey(Data* data) {
	cout << data->nickname << ": rang " << data->rang << ", " << data->exp << " exp, statistic: " << data->victoryStat << endl;
}

int BinarySearchTree::height() {
	return heightInner(headNode) - 1;
}

int BinarySearchTree::heightInner(Node* curNode) {
	if (!curNode)
		return 0;

	if (curNode->rSize<0)
		return 1 + heightInner(curNode->leftN);
	return 1 + heightInner(curNode->rightN);
}

int BinarySearchTree::findInRange(Data minObject, Data maxObject) {
	return findInnerInRange(headNode, &minObject, &maxObject);
}

int BinarySearchTree::findInnerInRange(Node* curNode, Data* minObject, Data* maxObject) {
	if (!curNode)
		return 0;
	int N = 0;
	if (curNode->gamer >= *minObject)
		N += findInnerInRange(curNode->leftN, minObject, maxObject);
	if (curNode->gamer >= *minObject && curNode->gamer <= *maxObject)
		N++;
	if (curNode->gamer <= *maxObject)
		N += findInnerInRange(curNode->rightN, minObject, maxObject);
	return N;
}

vector<Data> BinarySearchTree::findVectorInRange(Data minObject, Data maxObject) {
	return findInnerVectorInRange(headNode, &minObject, &maxObject);
}

vector<Data> BinarySearchTree::findInnerVectorInRange(Node* curNode, Data* minObject, Data* maxObject) {
	if (!curNode)
		return {};
	vector<Data> get1, get2;
	if(curNode->gamer >= *minObject)
		get1 = findInnerVectorInRange(curNode->leftN, minObject, maxObject);
	if (curNode->gamer >= *minObject && curNode->gamer <= *maxObject)
		get1.push_back(curNode->gamer);
	if (curNode->gamer <= *maxObject) {
		get2 = findInnerVectorInRange(curNode->rightN, minObject, maxObject);
		get1.insert(get1.end(), get2.begin(), get2.end());
	}
	return get1;
}

void BinarySearchTree::balance(Node* parentNode) {
	if (!parentNode)
		return;

	parentNode->rSize = heightInner(parentNode->rightN) - heightInner(parentNode->leftN);
	if (parentNode->rSize < -1) {
		if (parentNode->leftN->rSize > 0)
			bigRightRot(parentNode);
		else smallRightRot(parentNode);
		return;
	}
	if (parentNode->rSize > 1) {
		if (parentNode->rightN->rSize < 0)
			bigLeftRot(parentNode);
		else smallLeftRot(parentNode);
		return;
	}
	balance(parentNode->parent);
	return;
}

void BinarySearchTree::smallLeftRot(Node* parentNode) {
	if (!parentNode || !parentNode->rightN)
		return;

	//save data to newCentralNode
	Node* newCentralNode = parentNode->rightN;
	parentNode->rightN = newCentralNode->leftN;
	if(parentNode->rightN)
		parentNode->rightN->parent = parentNode;
	newCentralNode->leftN = parentNode;
	newCentralNode->parent = parentNode->parent;

	//Change parent child node
	if (newCentralNode->parent && newCentralNode->parent->leftN == parentNode)
		newCentralNode->parent->leftN = newCentralNode;
	if (newCentralNode->parent && newCentralNode->parent->rightN == parentNode)
		newCentralNode->parent->rightN = newCentralNode;

	parentNode->parent = newCentralNode;
	if (parentNode == headNode)
		headNode = newCentralNode;
	parentNode->rSize = heightInner(parentNode->rightN) - heightInner(parentNode->leftN);
	newCentralNode->rSize = heightInner(newCentralNode->rightN) - heightInner(newCentralNode->leftN);

}

void BinarySearchTree::smallRightRot(Node* parentNode) {
	if (!parentNode || !parentNode->leftN)
		return;

	//save data to newCentralNode
	Node* newCentralNode = parentNode->leftN;
	parentNode->leftN = newCentralNode->rightN;
	if(parentNode->leftN)
		parentNode->leftN->parent = parentNode;
	newCentralNode->rightN = parentNode;
	newCentralNode->parent = parentNode->parent;

	//Change parent child node
	if (newCentralNode->parent && newCentralNode->parent->leftN == parentNode)
		newCentralNode->parent->leftN = newCentralNode;
	if (newCentralNode->parent && newCentralNode->parent->rightN == parentNode)
		newCentralNode->parent->rightN = newCentralNode;

	parentNode->parent = newCentralNode;
	if (parentNode == headNode)
		headNode = newCentralNode;
	parentNode->rSize = heightInner(parentNode->rightN) - heightInner(parentNode->leftN);
	newCentralNode->rSize = heightInner(newCentralNode->rightN) - heightInner(newCentralNode->leftN);
	//if (!parentNode || !parentNode->leftN)
	//	return;
	//Node* newRight = new Node();
	//Node* toDelete = parentNode->leftN;
	//newRight->gamer = parentNode->gamer;
	//newRight->rightN = parentNode->rightN;
	//newRight->parent = parentNode;
	//parentNode->rightN = newRight;
	//parentNode->gamer = toDelete->gamer;
	//parentNode->leftN = toDelete->leftN;
	//delete toDelete;
}

void BinarySearchTree::bigLeftRot(Node* parentNode) {
	if (!parentNode || !parentNode->rightN)
		return;
	if (!parentNode->rightN->leftN) {
		smallLeftRot(parentNode);
		return;
	}
	smallRightRot(parentNode->rightN);
	smallLeftRot(parentNode);
}

void BinarySearchTree::bigRightRot(Node* parentNode) {
	if (!parentNode || !parentNode->leftN)
		return;
	if (!parentNode->leftN->rightN) {
		smallRightRot(parentNode);
		return;
	}
	smallLeftRot(parentNode->leftN);
	smallRightRot(parentNode);
}

bool BinarySearchTree::isSameTree(Node* p, Node* q) {
	if (!p && !q)
		return true;
	if (!p || !q)
		return false;
	if (p->gamer != q->gamer)
		return false;
	if (!isSameTree(p->leftN, q->leftN) || !isSameTree(p->rightN, q->rightN))
		return false;
	return true;
}

//CHECK HEIGHT

//int BinarySearchTree::realH() {
//	return realInnerH(headNode);
//}
//
//int BinarySearchTree::realInnerH(Node* curNode) {
//	if (!curNode)
//		return 0;
//	int hL = realInnerH(curNode->leftN);
//	int hR = realInnerH(curNode->rightN);
//	if (hL > hR)
//		return 1 + hL;
//	return 1 + hR;
//}


//IS NOT WORKING

//Node* BinarySearchTree::insertInner(Node* curNode, const Data& data, Node* parent) {
//	if (!curNode) {
//		Node* newNode = new Node(data);
//		newNode->parent = parent;
//		newNode->rSize = 0;
//		balance(newNode->parent);
//		return newNode;
//	}
//	if (curNode->gamer < data)
//		curNode->rightN = insertInner(curNode->rightN, data, curNode);
//	else
//		curNode->leftN = insertInner(curNode->leftN, data, curNode);
//	return curNode;
//}

//Node* BinarySearchTree::split(const Data data) {
//	return splitTree(headNode, &data);
//	//if (!headNode)
//	//	return nullptr;
//	//Node* toReturn = headNode;
//	//if (headNode->gamer == data) {//split on head
//	//	headNode = headNode->leftN;
//	//	toReturn->leftN = nullptr;
//	//	return toReturn;
//	//}
//	//if (headNode->gamer > data) {//split on left
//	//	Node* endLeftSearch = headNode;
//	//	Node* rightSearch = headNode;
//	//	while (endLeftSearch->leftN && endLeftSearch->leftN->gamer > data) {
//	//		endLeftSearch = endLeftSearch->leftN;
//	//	}
//	//	if (!endLeftSearch->leftN) {
//	//		headNode = nullptr;
//	//		return toReturn;
//	//	}
//	//	headNode = endLeftSearch->leftN;
//	//	rightSearch = headNode;
//	//	while (rightSearch->rightN && rightSearch->rightN->gamer < data) {
//	//		rightSearch = rightSearch->rightN;
//	//	}
//	//	if (!endLeftSearch) {
//	//		toReturn = rightSearch->rightN;
//	//		if (rightSearch->rightN)
//	//			rightSearch->rightN = rightSearch->rightN->leftN;
//	//		return toReturn;
//	//	}
//	//	endLeftSearch->leftN = rightSearch->rightN;
//	//	if (rightSearch->rightN)
//	//		rightSearch->rightN = rightSearch->rightN->leftN;
//	//	return toReturn;
//	//}
//	//else {//split on right
//	//	Node* current = nullptr;
//	//	Node* rightSearch = headNode;
//	//	while (rightSearch->rightN && rightSearch->rightN->gamer < data) {
//	//		rightSearch = rightSearch->rightN;
//	//	}
//	//	toReturn = rightSearch->rightN;
//	//	if (!toReturn)
//	//		return nullptr;
//	//	if (!toReturn->leftN)
//	//		return toReturn;
//	//	current = toReturn->leftN;
//	//	return nullptr;
//	//	while (current->leftN && current->leftN->gamer > data) {
//	//		current = current->leftN;
//	//	}
//	//}
//}
//
//Node* BinarySearchTree::splitTree(Node* parentNode, const Data* data) {
//	/*if (!parentNode)
//		return nullptr;
//	Node* toReturn = new Node();
//	Node* toDelete;
//	if (parentNode->gamer == *data) {
//		toReturn->gamer = parentNode->gamer;
//		toReturn->rightN = parentNode->rightN;
//		parentNode->rightN = nullptr;
//		toDelete = parentNode->leftN;
//		if (!toDelete) {
//			parentNode->gamer = Data("--Nothing--");
//			return toReturn;
//		}
//		parentNode->gamer = toDelete->gamer;
//		parentNode->leftN = toDelete->leftN;
//		delete toDelete;
//		return toReturn;
//	}
//	Node* fromRight = splitTree(parentNode->rightN, data);
//	if (parentNode->gamer < *data) {
//		return fromRight;
//	}
//	
//	if (parentNode->gamer > *data) {
//		Node* fromLeft = splitTree(parentNode->leftN, data);
//		if (fromLeft->gamer.nickname == "--Nothing--") {
//			delete fromLeft;
//			fromLeft = nullptr;
//		}
//		toReturn->gamer = parentNode->gamer;
//		toReturn->rightN = parentNode->rightN;
//		toReturn->leftN = fromLeft;
//		toDelete = parentNode->leftN;
//		if (!toDelete) {
//			parentNode->gamer = Data("--Nothing--");
//			return toReturn;
//		}
//		parentNode->gamer = parentNode->leftN->gamer;
//		parentNode->rightN = parentNode->leftN->rightN;
//		parentNode->leftN = parentNode->leftN->leftN;
//		delete toDelete;
//		return toReturn;
//	}*/
//	if (!parentNode)
//		return nullptr;
//	if (parentNode->gamer < *data) {
//		if (!parentNode->rightN)
//			return nullptr;
//		Node* fromRight = splitTree(parentNode->rightN, data);
//		if (parentNode->rightN->gamer == Data()) {
//			delete parentNode->rightN;
//			parentNode->rightN = nullptr;
//		}
//		return fromRight;
//	}
//	Node* fromLeft = splitTree(parentNode->leftN, data);
//	Node* newNode = new Node();
//	newNode->gamer = parentNode->gamer;
//	newNode->rightN = parentNode->rightN;
//	newNode->leftN = fromLeft;
//	if (!parentNode->leftN) {
//		parentNode->gamer = Data();
//		return newNode;
//	}
//	Node* toDelete = parentNode->leftN;
//	parentNode->gamer = toDelete->gamer;
//	parentNode->leftN = toDelete->leftN;
//	parentNode->rightN = nullptr;
//	delete toDelete;
//	return newNode;
//}
//
//void BinarySearchTree::merge(Node* tree1, Node* tree2) {
//	Node* curT1 = tree1;
//	Node* curT2 = tree2;
//	if (!tree1 || !tree2)
//		return;
//	if (tree1->gamer < tree2->gamer) {
//		while (curT1->rightN)
//			curT1 = curT1->rightN;
//		curT1->rightN = tree2;
//		return;
//	}
//	while (curT2->rightN)
//		curT2 = curT2->rightN;
//	curT2->rightN = tree1;	
//}
//
//void BinarySearchTree::eraseRange(Data minObject, Data maxObject) {
//	Node* rightRange = split(maxObject);
//	Node* splited = split(minObject);
//	merge(rightRange, headNode);
//}