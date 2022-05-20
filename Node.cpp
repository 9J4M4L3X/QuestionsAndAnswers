#include"Node.h"

Node::Node(string text) {
	text_ = text;
}

Node::~Node()
{
	//level order traversal, deletes this node and all children after this node
	Node* root = this;
	if (!root) return;

	queue<Node*> q;
	q.push(root);

	while (q.empty() == false) {
		Node* node = q.front();
		q.pop();

		unsigned cnt = 0;
		while (cnt < node->getChildNum()) {
			q.push(node->getChild(cnt++));
		}
		node = nullptr;
	}

}

void Node::removeChild(unsigned pos) {
	children_.at(pos)->~Node();
}

void Node::printTree()
{
	//level order traversal for the right output format
	Node* root = this;
	if (!root) return;

	queue<Node*> q;
	q.push(root);

	while (q.empty() == false) {
		Node* node = q.front();
		cout << node->getContent() << '\n';
		q.pop();
		
		unsigned cnt = 0;
		while (cnt < node->getChildNum()) {
			q.push(node->getChild(cnt++));
		}
	}
}

void Node::sortTree()
{
	//sorts all answers based on their number of likes
	Node* root = this;
	if (!root) return;

	queue<Node*> q;
	q.push(root);

	while (q.empty() == false) {
		Node* node = q.front();
		q.pop();

		unsigned number_of_children = node->getChildNum();
		if(number_of_children > 1)//if there is more than one child then do sort
			selectionSort(node->getChildren(), node->getLikes(), number_of_children);	
		
		unsigned cnt = 0;
		while (cnt < number_of_children) {
			q.push(node->getChild(cnt++));
		}
	}
}

void Node::selectionSort(vector<Node*> children, vector<unsigned> likes, unsigned ch_num)
{
	unsigned i, j, max_idx;

	//one by one move boundary of unsorted subarray
	for (i = 0; i < ch_num - 1; i++)
	{
		//find the minimum element in unsorted array
		max_idx = i;
		for (j = i + 1; j < ch_num; j++)
			if (likes[j] > likes[max_idx])
				max_idx = j;

		//swap the found maximum element(element with maximum likes) with the first element
		swap(children[max_idx], children[i]);
		swap(likes[max_idx], likes[i]);
	}
}

void Node::swap(Node* node1, Node* node2)
{
	Node temp = *node1;
	*node1 = *node2;
	*node2 = temp;
}

void Node::swap(unsigned likes1, unsigned likes2)
{
	unsigned temp = likes1;
	likes1 = likes2;
	likes2 = temp;
}

Node* Node::searchAnswer(string text)
{
	Node* root = this;
	if (!root) return nullptr;

	queue<Node*> q;
	q.push(root);

	while (q.empty() == false) {
		Node* node = q.front();
		//compares input and the text of an answer and if they are the same then returns node
		if (node->getContent().compare(text) == 0) return node;
		q.pop();

		unsigned cnt = 0;
		while (cnt < node->getChildNum()) {
			q.push(node->getChild(cnt++));
		}
	}
	return nullptr;
}

void Node::printChildren()
{
	vector<Node*>::iterator it = this->children_.begin();
	while (it < children_.end()) {
		cout << (*it)->getContent() << '\n';
		it++;
	}
}
