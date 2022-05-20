#include"TreeList.h"

TreeList::TreeList()
{
	current = nullptr;
	 
}

bool TreeList::menu(){
	if (!this->current){

		cout << "Izaberi redni broj opcije:\n"
			<< "\t1 Ispis svih postojecih pitanja\n"//done
			<< "\t2 Ispis jednog pitanja sa svim odgovorima\n"//done
			<< "\t3 Uredjivanje odgovora po oceni za odabrano pitanje\n"//done
			<< "\t4 Uredjivanje odgovora po oceni za sva pitanja\n"//done
			<< "\t5 Odabir postojeceg pitanja\n"//done
			<< "\t6 Postavi pitanje\n"//done
			<< "\t7 Pretraga pitanja\n"//done
			<< "\t8 Obrisi pitanje\n"
			<< "\t9 Pretraga najbolje ocenjenog odgovora na zadato pitanje\n"//done
			<< "\t10 Izlaz\n";
	
		Node* question, * root, *ans;
		unsigned option, q, temp;
		string opt, text;
		while (opt.size() == 0) {
			getline(cin, opt);
		}
		option = stoi(opt);
		
		switch (option)
		{
		case 1:
			printQuestions();
			break;
		case 2:
			cout << "Upisi redni broj pitanja:\n";
			cin >> q;
			if (q - 1 < questions_.size())
				questions_[q-1]->printTree();
			else
				cout << "Nevalidan ulaz...";
			break;
		case 3:
			cout << "Upisi redni broj pitanja:\n";
			cin >> q;
			if (q - 1 < questions_.size())
				questions_[q - 1]->sortTree();
			else
				cout << "Nevalidan ulaz...";
			break;
		case 4:
			for (unsigned i = 0; i < questions_.size(); i++) {
				questions_[i]->sortTree();
			}
			break;
		case 5:
			cout << "Upisi redni broj pitanja:\n";
			cin >> q;
			if ((q <= questions_.size()) && (q > 0)) {
				current = questions_[q - 1];
				cout << "\nSelektovano pitanje\n" << current->getContent() << '\n';
			}
			break;
		case 6:
			cout << "Unesi pitanje:\n";
			getline(cin, text);
			question = new Node(text);
			this->questions_.push_back(question);
			break;		
		case 7:
			cout << "Unesi pitanje:\n";
			getline(cin, text);
			
			root = searchQuestion(text);
			if (!root) {
				cout << "Ne postoji ovakvo pitanje";
			}
			else {
				cout << "Pronadjeno pitanje:\n"
					<< root->getContent()
					<< "\n1. Selektuj pitanje\n2. Nazad na glavni meni\n";
				cin >> temp;	
				if (temp == 1)
					current = root;
			}
			break;
		case 8:
			cout << "Upisi redni broj pitanja:\n";
			cin >> q;
			if (q - 1 < questions_.size()) {
				delete questions_[q - 1];//implicitly calls the destructor function of class Node 
				questions_.erase(questions_.begin() + q - 1);//pops the question from the vector
			}
			break;
		case 9:
			cout << "\nUnesi redni broj pitanja za koje se radi pretraga\n";
			cin >> q;

			ans = searchMostLikedAnswer(q);

			if (!ans) {
				cout << "Ne postoji ovakav odgovor";
			}
			else {
				cout << "Pronadjeni odgovor:\n"
					<< ans->getContent()
					<< "\n1. Selektuj odgovor\n2. Nazad\n";
				cin >> temp;
				if (temp == 1) current = ans;
			}
			break;

		case 10:
			return false;
		default: 
			cout << "Izabrana opcija nije validna! Izabrati ponovo...\n";
			break;
		}
	}
	else {
		cout << "Izaberi redni broj opcije:\n"
			<< "\t1. Ispisi odgovore\n"
			<< "\t2. Izaberi odgovor\n"
			<< "\t3. Dodaj odgovor\n"
			<< "\t4. Pretraga odgovora\n"
			<< "\t5. Povecaj ocenu odgovora\n"
			<< "\t6. Obrisi odgovor\n"
			<< "\t7. Vrati se na glavni meni\n"
			<< "\t8. Izadji\n";
		
		Node* ans;
		unsigned option, q, temp;
		string opt, text;
		while (opt.size() == 0) {
			getline(cin, opt);
		}
		option = stoi(opt);

		switch (option)
		{
			case 1:
				//writes only answers to the current answer, without comments
				current->printChildren();
				break;
			case 2:
				cout << "Upisi redni broj odgovora:\n";
				cin >> temp;
				if (temp - 1 < current->getChildNum()) {
					current = current->getChild(temp - 1);
				}
				break;
			case 3:
				cout << "Unesi tekst odgovora koji se dodaje:\n";
				getline(cin, text);
				ans = new Node(text);
				current->addChild(ans);
				current->createLike();//adds a new like 'button'(set to 0)
				break;
			case 4:
				cout << "Unesi tekst odgovora koji treba naci:\n";
				getline(cin, text);
				ans = current->searchAnswer(text);

				if (!ans) {
					cout << "Ne postoji ovakav odgovor";
				}
				else {
					cout << "Pronadjeni odgovor:\n"
						<< ans->getContent()
						<< "\n1. Selektuj odgovor\n2. Nazad\n";
					cin >> temp;
					if (temp == 1) current = ans;
				}
				break;
			case 5:
				cout << "Upisi redni broj odgovora:\n";
				cin >> temp;

				if ((temp <= current->getChildNum()) && (temp > 0))
					current->addLike(temp - 1);//adds like for an answer, position given by input

				break;
			case 6:
				cout << "Upisi redni broj odgovora koji zelis da obrises:\n";
				cin >> q;
				if (q - 1 < current->getChildNum()) {
					current->removeChild(q - 1);
				}
				break;
			case 7:
				current = nullptr;
				break;
			case 8:
				return false;

			default:
				cout << "Izabrana opcija nije validna! Izabrati ponovo...\n";
				break;
		}

	}
	return true;
}

Node* TreeList::searchQuestion(string text)
{
	vector<Node*>::iterator it = questions_.begin();
	while (it < questions_.end()) {
		if ((*it)->getContent().compare(text) == 0) 
			return (*it);
	}
	return nullptr;
}

void TreeList::printQuestions()
{
	vector<Node*>::iterator it = questions_.begin();
	while (it < questions_.end()) {
		cout << (*it++)->getContent() << '\n';
	}
}

Node* TreeList::searchMostLikedAnswer(unsigned question_number)
{
	Node* root = questions_.at(question_number - 1);
	if (!root) return nullptr;

	queue<Node*> q;
	q.push(root);
	
	unsigned max_likes = 0;
	Node* ans_with_max_likes = nullptr;
	while (q.empty() == false) {
		Node* node = q.front(); 
		q.pop();
		
		vector<unsigned> likes = node->getLikes();
		vector<unsigned>::iterator it = likes.begin();
		unsigned cnt = 0;
		while (cnt < node->getChildNum()) {
			if (*it >= max_likes) {
				max_likes = *it;
				ans_with_max_likes = node->getChild(cnt);
			}
			it++;
			q.push(node->getChild(cnt++));
		}
	}
	return ans_with_max_likes;
}
