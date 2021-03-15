#ifndef RBT_H_
#define RBT_H_

#include <iostream>

using namespace std;

class Node {
private:
	int key;
	//0 will be used to signify black, 1 to signify red
	unsigned int color;
	bool nilness;
	Node* parent;
	Node* left;
	Node* right;

public:
	// this is the default constructor
	Node();
	// this is the manual constructor
	Node(int i);

	// the class destructor
	~Node();

	void add_parent(Node* new_parent);

	void add_left(Node* new_left);

	void add_right(Node* new_right);

	void remove_parent();
	void remove_left();
	void remove_right();
	void change_key(int i);
	void set_color(unsigned int i);

	int get_key();
	unsigned int get_color();
	Node* get_parent();
	Node* get_left();
	Node* get_right();
	
	void declare_self(ostream& to);
	void disentangle();

	void set_nilness(bool new_nilness);
	bool get_nilness();
};

class RBT {
private:
	Node* root;
	Node* NIL;

	void inorder_walk(Node* current, ostream& to);
	void postorder_walk(Node* current, ostream& to);
	void preorder_walk(Node* current, ostream& to);

	Node* get_relative_min(Node* relative_root);

	Node* get_relative_max(Node* relative_root);

	void node_transplant(Node* u, Node* v);

	// this family of functions is for insertion and deletion fixups
	void left_rotate(Node* x);
	void right_rotate(Node* x);
	void rb_insert_fixup(Node* in);
	void rb_delete_fixup(Node* in);


public:

	RBT();
	RBT(Node* start_root);
	~RBT();

	void delete_node(Node* z);
	void insert_node(Node* z);
	void insert_scratch_node(int node_value);

	//values from the tree

	Node* get_min_node();
	Node* get_max_node();
	Node* get_successor(Node* in);
	Node* get_successor_by_val(int val);
	Node* get_pred(Node* in);
	Node* get_pred_by_val(int val);
	void inorder_traversal(ostream& to);
	void postorder_traversal(ostream& to);
	void preorder_traversal(ostream& to);
	Node* search(int search_key);
};

#endif