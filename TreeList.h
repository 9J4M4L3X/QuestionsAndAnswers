#ifndef TREE_LIST_H_
#define TREE_LIST_H_

#include"Node.h"

class TreeList {
public:
	TreeList();

	bool menu();
	Node* searchQuestion(string text);
	Node* searchMostLikedAnswer(unsigned question_number);
private:
	void printQuestions();

	Node* current = nullptr;
	vector<Node*> questions_;//array of questions with all their answers and comments
};
#endif // !TREE_LIST_H_