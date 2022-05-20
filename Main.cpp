#include"TreeList.h"

int main() {
	TreeList* questions = new TreeList();
	while (true) {
		bool work = questions->menu();
		if (!work) break;
	}
	return 0;
}