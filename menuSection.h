#pragma once

void showScore(User* user) {
	ifstream file("LeaderBoard.txt");
	string username, score;
	vector <pair<string, string>> players;
	if (file.is_open()) {
		while (getline(file, username, ' ')) {
			getline(file, score);
			players.push_back({ username, score });
		}
		file.close();
	}
	for (auto& i : players){
		if (i.first == user->getUsername()) cout << "Your Score is: " << i.second << endl;
	}
}

void createQuiz() {
	string filename, question, answers, correctAnswer;
	cout << "Enter quiz name" << endl;
	cin >> filename;
	filename += ".txt";
	for (size_t i = 0; i < 5; i++)
	{
		cout << "Add your " << i + 1 << ". question: " << endl;
		getline(cin >> ws, question);
		cout << "Add four variant: " << endl;
		getline(cin >> ws, answers);
		cout << "Correct answer: " << endl;
		cin >> correctAnswer;
		ofstream file(filename, ios::app);
		if (file.is_open()) {
			file << question << " " << answers << " " << correctAnswer << "\n";
			file.close();
		}
	}
	ofstream file("quizNames.txt", ios::app);
	if (file.is_open()) {
		file << filename << "\n";
		file.close();
	}
}


void menu() {
	bool choice;
	while (true){
		try {
			choice = logOrSignChoice();
		}
		catch (const exception& ex) {
			cout << ex.what() << endl << endl;
			continue;
		}
		break;
	}
	char choice_;
	if (!choice) {
		while (true){
			try{
				signIn();
			}
			catch (const std::exception& ex){
				cout << endl << ex.what() << endl;
				continue;
			}
			break;
		}
	}

	User* user = logIn();
	if (checkAdminOrPlayer(user->getUsername(), user->getPassword())) {
		while (true){
			cin.ignore();
			cout << "1. Start Quiz" << endl;
			cout << "2. Leader Board" << endl;
			cout << "3. Create Quiz" << endl;
			cout << "4. Exit" << endl;
			cin >> choice_;
			if (choice_ == '1') startQuiz(user);
			else if (choice_ == '2') leaderBoard();
			else if (choice_ == '3') createQuiz();
			else if (choice_ == '4') exit(0);
		}
	}
	else {
		while (true){
			cin.ignore();
			cout << "1. Start Quiz" << endl;
			cout << "2. Leader Board" << endl;
			cout << "3. Show my score" << endl;
			cout << "4. Exit" << endl;
			cin >> choice_;
			if (choice_ == '1') startQuiz(user);
			else if (choice_ == '2') leaderBoard();
			else if (choice_ == '3') showScore(user);
			else if (choice_ == '4') exit(0);
		}
	}
	delete user;
}