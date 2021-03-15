#include "rbt.h"


// this is the default node constructor
Node::Node(){
	key = 0;
	color = 0;
	nilness = false;
	left = NULL;
	right = NULL;
	parent = NULL;
}

Node::Node(int thekey){
	key = thekey;
	color = 0;
	nilness = false;
	left = NULL;
	right = NULL;
	parent = NULL;
}

//the basic destructor
Node::~Node(){
	if (left){
		if (left->get_nilness() == false){
			delete left;
		}
	}
	if (right){
		if (right->get_nilness() == false){
			delete right;
		}
	}
}

void Node::add_parent(Node* new_parent){
	parent = new_parent;
}

void Node::add_left(Node* new_left){
	left = new_left;
}

void Node::add_right(Node* new_right){
	right = new_right;
}

void Node::remove_parent(){
	parent = NULL;
}

void Node::remove_left(){
	left = NULL;
}

void Node::remove_right(){
	right = NULL;
}

void Node::change_key(int i){
	key = i;
}

void Node::set_color(unsigned int i){
	color = i;
}

int Node::get_key(){
	return key;
}

unsigned int Node::get_color(){
	return color;
}

Node* Node::get_parent(){
	return parent;
}

Node* Node::get_left(){
	return left;
}

Node* Node::get_right(){
	return right;
}

void Node::declare_self(ostream& to){
	to << "Key: " << key << " color: "<< (color == 0 ? "Black\n" : "Red\n");
}

void Node::disentangle(){
	parent = NULL;
	left = NULL;
	right = NULL;
}

void Node::set_nilness(bool new_nilness){
	nilness = new_nilness;
}

bool Node::get_nilness(){
	return nilness;
}

//__________________________________________________________________
//this is the end of the Node methods




//__________________________________________________________________
//this is the beinning of the RBT methods


RBT::RBT(){
	NIL = new Node();
	NIL->add_left(NIL);
	NIL->add_right(NIL);
	NIL->add_parent(NIL);
	NIL->set_nilness(true);
	root = NIL;
}

RBT::~RBT(){
	NIL->disentangle();
	if (root){
		if (root != NIL){
			delete root;
		}
	}
	delete NIL;
}


void RBT::inorder_walk(Node* current, ostream& to){
	if (current == NIL){
		return;
	} else{
		if (current->get_left() == NULL){
			cout << "There is no left child to node " << current->get_key() << endl;
		}
		if (current->get_right() == NULL){
			cout << "there is no right child to node " << current->get_key() << endl;
		}
		inorder_walk(current->get_left(), to);
		current->declare_self(to);
		inorder_walk(current->get_right(), to);
	}
}


void RBT::postorder_walk(Node* current, ostream& to){
	if (current == NIL){
		return;
	} else {
		inorder_walk(current->get_left(), to);
		inorder_walk(current->get_right(), to);
		current->declare_self(to);
	}
}


void RBT::preorder_walk(Node* current, ostream& to){
	if (current == NIL){
		return;
	} else {
		current->declare_self(to);
		inorder_walk(current->get_left(), to);
		inorder_walk(current->get_right(), to);
	}
}


Node* RBT::get_relative_min(Node* relative_root){
	Node* tmp = relative_root;

	if (relative_root == NIL){
		return NULL;
	} else {
		while ((tmp->get_left() != NIL) and (tmp->get_left() != NIL)){
			tmp = tmp->get_left();
		}
	}
	return tmp;
}


Node* RBT::get_relative_max(Node* relative_root){
	Node* tmp = relative_root;

	if (relative_root == NIL){
		return NULL;
	} else {
		while ((tmp->get_right() != NIL) and (tmp->get_right() != NIL)){
			tmp = tmp->get_right();
		}
	}
	return tmp;
}


void RBT::node_transplant(Node* u, Node* v){
	if (u->get_parent() == NIL){
		root = v;
	} else {
		if (u->get_parent()->get_left() == u){
			u->get_parent()->add_left(v);
		} else {
			u->get_parent()->add_right(v);
		}
	}
	if (v != NIL){
		v->add_parent(u->get_parent());
	}
}


void RBT::left_rotate(Node* x){
	Node* y = x->get_right();
	x->add_right(y->get_left());
	if (y->get_left() != NIL){
		y->get_left()->add_parent(x);
	}
	y->add_parent(x->get_parent());
	if (x->get_parent() == NIL){
		root = y;
	} else {
		if (x == x->get_parent()->get_left()){
			x->get_parent()->add_left(y);
		} else {
			x->get_parent()->add_right(y);
		}
	}
	y->add_left(x);
	x->add_parent(y);
}


void RBT::right_rotate(Node* x){
	Node* y = x->get_left();
	x->add_left(y->get_right());
	if (y->get_right() != NIL){
		y->get_right()->add_parent(x);
	}
	y->add_parent(x->get_parent());
	if (x->get_parent() == NIL){
		root = y;
	} else {
		if (x == x->get_parent()->get_right()){
			x->get_parent()->add_right(y);
		} else {
			x->get_parent()->add_left(y);
		}
	}
	y->add_right(x);
	x->add_parent(y);
}


void RBT::rb_insert_fixup(Node* in){
	Node* z = in;
	Node* y;
	while (z->get_parent()->get_color() == 1){
		if (z->get_parent() == z->get_parent()->get_parent()->get_left()){
			y = z->get_parent()->get_parent()->get_right();
			if (y->get_color() == 1){
				z->get_parent()->set_color(0);
				y->set_color(0);
				z->get_parent()->get_parent()->set_color(1);
				z = z->get_parent()->get_parent();
			} else {
				if (z == z->get_parent()->get_right()){
					z = z->get_parent();
					left_rotate(z);
				}
				z->get_parent()->set_color(0);
				z->get_parent()->get_parent()->set_color(1);
				right_rotate(z->get_parent()->get_parent());
			}
		} else {
			y = z->get_parent()->get_parent()->get_left();
			if (y->get_color() == 1){
				z->get_parent()->set_color(0);
				y->set_color(0);
				z->get_parent()->get_parent()->set_color(1);
				z = z->get_parent()->get_parent();
			} else {
				if (z == z->get_parent()->get_left()){
					z = z->get_parent();
					right_rotate(z);
				}
				z->get_parent()->set_color(0);
				z->get_parent()->get_parent()->set_color(1);
				left_rotate(z->get_parent()->get_parent());
			}
		}
	}
	root->set_color(0);
}


void RBT::insert_node(Node* z){
	Node* y = NIL;
	Node* x = root;
	while (x != NIL){
		y = x;
		if (z->get_key() < x->get_key()){
			x = x->get_left();
		} else {
			x = x->get_right();
		}
	}
	z->add_parent(y);
	if (y == NIL){
		root = z;
	} else {
		if (z->get_key() < y->get_key()){
			y->add_left(z);
		} else {
			y->add_right(z);
		}
	}
	z->add_left(NIL);
	z->add_right(NIL);
	z->set_color(1);
	rb_insert_fixup(z);
}


void RBT::rb_delete_fixup(Node* in){
	Node* x = in;
	Node* w;
	while ((x != root) and (x->get_color() == 0)){
		if (x->get_parent() == NULL){
		} else {
			if (x->get_parent()->get_left() == NULL){
				cout << x->get_key() << endl;
				cout << x->get_parent()->get_key() << endl;
			}
		}
		if (x == x->get_parent()->get_left()){
			w = x->get_parent()->get_right();
			if (w->get_color() == 1){
				w->set_color(0);
				x->get_parent()->set_color(1);
				left_rotate(x->get_parent());
				w = x->get_parent()->get_right();
			}
			if ((w->get_left()->get_color() == 0) and (w->get_right()->get_color() == 0)){
				w->set_color(1);
				x = x->get_parent();
			} else {
				if (w->get_right()->get_color() == 0){
					w->get_left()->set_color(0);
					w->set_color(1);
					right_rotate(w);
					w = x->get_parent()->get_right();
				}
				w->set_color(x->get_parent()->get_color());
				x->get_parent()->set_color(0);
				w->get_right()->set_color(0);
				left_rotate(x->get_parent());
				x = root;
			}
		} else {
			w = x->get_parent()->get_left();
			if (w->get_color() == 1){
				w->set_color(0);
				x->get_parent()->set_color(1);
				right_rotate(x->get_parent());
				w = x->get_parent()->get_left();
			}
			if ((w->get_right()->get_color() == 0) and (w->get_left()->get_color() == 0)){
				w->set_color(1);
				x = x->get_parent();
			} else {
				if (w->get_left()->get_color() == 0){
					w->get_right()->set_color(0);
					w->set_color(1);
					left_rotate(w);
					w = x->get_parent()->get_left();
				}
				w->set_color(x->get_parent()->get_color());
				x->get_parent()->set_color(0);
				right_rotate(x->get_parent());
				x = root;
			}
		}
	}
	x->set_color(0);
}

void RBT::delete_node(Node* z){
	if ((z == NIL) or (z == NULL)){
		return;
	}
	Node* x;
	Node* y = z;
	unsigned int ycol = y->get_color();
	if (z->get_left() == NIL){
		x = z->get_left();
		node_transplant(z, z->get_right());
	} else if (z->get_right() == NIL){
		x = z->get_left();
		node_transplant(z, z->get_left());
	} else {
		y = get_relative_min(z->get_right());
		ycol = y->get_color();
		x = y->get_right();
		if (y->get_parent() == z){
			x->add_parent(y);
		} else {
			node_transplant(y, y->get_right());
			y->add_right(z->get_right());
			y->get_right()->add_parent(y);
		}
		node_transplant(z, y);
		y->add_left(z->get_left());
		y->get_left()->add_parent(y);
		y->set_color(z->get_color());
	}
	if (ycol == 0){
		rb_delete_fixup(x);
	}
	z->add_left(NULL);
	z->add_right(NULL);
	z->add_right(NULL);
	delete z;
}


Node* RBT::get_min_node(){
	return get_relative_min(root);
}

Node* RBT::get_max_node(){
	return get_relative_max(root);
}

Node* RBT::search(int search_key){
	Node* x = root;
	while ((x != NIL) and (x->get_key() != search_key)){
		if (search_key < x->get_key()){
			x = x->get_left();
		} else {
			x = x->get_right();
		}
	}
	if (x == NIL){
		return NULL;
	} else {
		return x;
	}
}


void RBT::inorder_traversal(ostream& to){
	inorder_walk(root, to);
}


void RBT::preorder_traversal(ostream& to){
	preorder_walk(root, to);
}

void RBT::postorder_traversal(ostream& to){
	postorder_walk(root, to);
}

Node* RBT::get_successor(Node* in){
	Node* y;
	if (in->get_right() != NIL){
		return get_relative_min(in->get_right());
	}
	y = in->get_parent();
	while ((y != NIL) and (in == y->get_right())){
		in = y;
		y = y->get_parent();
	}
	if (y == NIL){
		return NULL;
	} else {
		return y;
	}
}


Node* RBT::get_pred(Node* in){
	Node* y;
	if (in->get_left() != NIL){
		return get_relative_max(in->get_left());
	}
	y = in->get_parent();
	while ((y != NIL) and (in == y->get_left())){
		in = y;
		y = y->get_parent();
	}
	if (y == NIL){
		return NULL;
	} else {
		return y;
	}
}