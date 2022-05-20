#include<vector>
#include<string>
#include<iostream>
#include<stack>
#include<queue>
#include<istream>

using namespace std;

const unsigned COM_MAX = 10;

class Node {
public:
	Node(string text);
	Node() { text_ = ""; }
	~Node();

	void addChild(Node* child) { if(children_.size() <= COM_MAX) children_.push_back(child); }
	void setChild(unsigned pos, Node* n) { if (pos < children_.size()) children_.at(pos) = n; }
	void removeChild(unsigned pos);//removes a child from the node and all its children 
	void editText(string txt) { text_ = txt; }
	void createLike() { likes_.push_back(0); }
	void addLike(unsigned pos) { likes_.at(pos)++; }
	
	void printTree();//prints the question and all the answers
	void sortTree();//if this node is root(question) then it sorts all answers according to number of likes 
	Node* searchAnswer(string text);//searches answer based on its text
	void printChildren();//prints only the answers to this node(answer) without further answers/comments

	void selectionSort(vector<Node*>, vector<unsigned>, unsigned);
	void swap(Node*, Node*);
	void swap(unsigned, unsigned);

	unsigned getChildNum() { return children_.size(); }
	Node* getChild(unsigned pos) { return children_.at(pos); }
	vector<Node*> getChildren() { return children_; }
	string getContent() { return text_; }
	vector<unsigned> getLikes() { return likes_; }
private:
	vector<Node*> children_;//answers to the question, or comments of answers/comments
	vector<unsigned> likes_;
	string text_;
};