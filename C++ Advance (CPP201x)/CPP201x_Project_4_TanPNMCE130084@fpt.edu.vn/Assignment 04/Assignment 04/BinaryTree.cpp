#include "BinaryTree.h"

// Contructor to init Tree
BinaryTree::BinaryTree() {
	root = NULL;
	BinaryTree::resultSearchName = NULL;
}

BinaryTree::~BinaryTree() {
	destroy_tree();
}

/*
* Function to detroy tree
*/
void BinaryTree::destroy_tree(Node* leaf) {
	if (leaf != NULL) {
		destroy_tree(leaf->left);
		destroy_tree(leaf->right);
		delete leaf;
	}
}

/*
* Function to detroy tree
*/
void BinaryTree::destroy_tree() {
	destroy_tree(root);
}

/*
* The function to insert new node into binary tree
*/
void BinaryTree::insert(Setting* data) {
	
	// If root is NULL, then create data for root
	if (root == NULL) {
		root = new Node;
		root->data = data;
		root->left = NULL;
		root->right = NULL;
	}
	else {	// Create data for child
		insert(root, data);
	}
}

/*
* The function to insert new node into binary tree
*/
void BinaryTree::insert(Node* node, Setting* data) {

	// If personal key of data is smaller than personal key of node
	// Go to left node
	if (data->getPersonalKey() < node->data->getPersonalKey()) {
		
		// If node left is NULL then create data
		if (node->left == NULL) {
			node->left = new Node;
			node->left->data = data;
			node->left->left = NULL;
			node->left->right = NULL;
		}
		else {	// If not, go to next left node
			insert(node->left, data);
		}
	}
	else {	// If personal key of data is greater than personal key of node => Go to right node
		
		// If node right is NULL then create data
		if (node->right == NULL) {
			node->right = new Node;
			node->right->data = data;
			node->right->left = NULL;
			node->right->right = NULL;
		}
		else {	// If not, go to next right node
			insert(node->right, data);
		}
	}
}




/*
* The function to search node by personal key
*/
Node* BinaryTree::searchByPersonalKey(Node* node, string personalKey) {
	// If node is not NULL
	if (node != NULL) {
		// If personal key is equal with personal key of node
		if (personalKey == node->data->getPersonalKey()) {
			return node;
		}
		// If personal key is smaller than personal key of node => go to next left node
		if (personalKey < node->data->getPersonalKey()) {
			return searchByPersonalKey(node->left, personalKey);
		}
		// If personal key is greater than or equal with personal key of node => go to next right node
		else {
			return searchByPersonalKey(node->right, personalKey);
		}
	}
	else {	// If tree is NULL then return NULL
		return NULL;
	}
}

/*
* The function to search node by personal key
*/
Node* BinaryTree::searchByPersonalKey(string personalKey) {
	return searchByPersonalKey(root, personalKey);
}

/*
* The function to search node by owner name
*/
Node* BinaryTree::searchByName(string name) {
	
	// Init resultSearchName is NULL
	resultSearchName = NULL;
	// Call function searchByName(name, root) to get result
	Node* result = searchByName(name, root);
	return result;
}

/*
* The function to search node by owner name
*/
Node* BinaryTree::searchByName(string name, Node* node) {
	// if node not NULL
	if (node != NULL) {
		// Go to left node to search data
		searchByName(name, node->left);

		// Compare owner name with owner name of node
		int res = name.compare(node->data->getCarName());

		// If both is equal then assign this node to resultSearchName
		if (res == 0) {
			resultSearchName = node;
		}

		// Go to right node to search data
		searchByName(name, node->right);
	}
	else { // If tree is NULL then return NULL
		return NULL;
	}

	// If is found, return node resultSearchName
	if (resultSearchName != NULL)
	{
		return resultSearchName;
	}
	else { // If is not found, return NULL
		return NULL;
	}
}



/*
* The function use inorder traversal to print data out
*/
void BinaryTree::printTree(Node* node, int type) {
	// check if node is not NULL
	if (node != NULL) {
		// go to left node
		printTree(node->left, type);

		// Check type to print the corect type out
		// if type is display
		switch (type)
		{
		case 1:		// The case type is Display
			// print value
			if (dynamic_cast<Display*>(node->data) != NULL)
			{
				//leaf->value->Setting::xuatThongTin();
				dynamic_cast<Display*>(node->data)->xuatThongTin();
			}
			break;

		case 2:		// The case type is Display
			// print value
			if (dynamic_cast<Sound*>(node->data) != NULL)
			{
				//leaf->value->Setting::xuatThongTin();
				dynamic_cast<Sound*>(node->data)->xuatThongTin();
			}
			break;

		case 3:		// The case type is Display
			// print value
			if (dynamic_cast<General*>(node->data) != NULL)
			{
				//leaf->value->Setting::xuatThongTin();
				dynamic_cast<General*>(node->data)->xuatThongTin();
			}
			break;
		}

		// go to right node
		printTree(node->right, type);
	}
}

/*
* The function print data in tree
*/
void BinaryTree::printTree(int type) {
	printTree(root, type);
}



/*
* The function to get all data of Display and return to vector
*/
void BinaryTree::getAllDisplay(Node* node, vector<Display*>* v_display) {
	// if node is not NULL
	if (node != NULL) {
		// go to left node
		getAllDisplay(node->left, v_display);
		// push to vector
		v_display->push_back(dynamic_cast<Display*>(node->data));
		// go to right node
		getAllDisplay(node->right, v_display);
	}
}

/*
* The function to get all data of Display and return to vector
*/
vector<Display*>* BinaryTree::getAllDisplay(vector<Display*>* v_display) {
	getAllDisplay(root, v_display);
	return v_display;
}

/*
* The function to get all data of Sound and return to vector
*/
void BinaryTree::getAllSound(Node* node, vector<Sound*>* v_sound) {
	// if node is not NULL
	if (node != NULL) {
		// go to left node
		getAllSound(node->left, v_sound);
		// push to vector
		v_sound->push_back(dynamic_cast<Sound*>(node->data));
		// go to right node
		getAllSound(node->right, v_sound);
	}
}

/*
* The function to get all data of Sound and return to vector
*/
vector<Sound*>* BinaryTree::getAllSound(vector<Sound*>* v_sound) {
	getAllSound(root, v_sound);
	return v_sound;
}

/*
* The function to get all data of General and return to vector
*/
void BinaryTree::getAllGeneral(Node* node, vector<General*>* v_general) {
	// if node is not NULL
	if (node != NULL) {
		// go to left node
		getAllGeneral(node->left, v_general);
		// push to vector
		v_general->push_back(dynamic_cast<General*>(node->data));
		// go to right node
		getAllGeneral(node->right, v_general);
	}
}

/*
* The function to get all data of General and return to vector
*/
vector<General*>* BinaryTree::getAllGeneral(vector<General*>* v_general) {
	getAllGeneral(root, v_general);
	return v_general;
}