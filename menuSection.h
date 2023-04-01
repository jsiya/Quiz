#pragma once
void showScore(User* user) {
	ifstream file("LeaderBoard.txt");
	string username, score;
	vector <pair<string, string>> players;    //vectorda - username, score
	if (file.is_open()) {
		while (getline(file, username, ' ')) {
			getline(file, score);
			players.push_back({ username, score });
		}
		file.close();
	}
	for (auto& i : players) {
		if (i.first == user->getUsername()) cout << "Your Score is: " << i.second << endl;
	}
}

void checkQuizName(string quizname) {
	string quizname_from_file;
	ifstream file("quizNames.txt");
	if (file.is_open()) {
		while (getline(file, quizname_from_file)) {
			if (quizname_from_file == quizname) throw exception("This quiz name already used!");
		}
	}
}

void createQuiz() {
	string filename, question, answer, correctAnswer;
	vector<string> answers;
	while (true) {
		system("cls");
		cout << "Enter quiz name" << endl;
		cin >> filename;
		try {    //quiz yaradanda adinda simvol olunmamalidi
			for (auto& i : filename) {
				if ((i < 65 || i > 122) || (i > 90 && i < 97)) throw exception("You cannot use other characters in quiz name!!!");
			}
			filename += ".txt";
			checkQuizName(filename);     //bu adda basqa quizin olub olmamasi
		}
		catch (const std::exception& ex) {
			system("cls");
			cout << ex.what() << endl;
			this_thread::sleep_for(chrono::milliseconds(2000));
			continue;
		}
		break;
	}
	for (size_t i = 0; i < 5; i++) {
		cout << "Add your " << i + 1 << ". question: " << endl;
		getline(cin >> ws, question);
		question.erase(remove(question.begin(), question.end(), '?'), question.end());    //admin suala ? qoyubsa silsin 
		cout << "Add four variant: " << endl;
		for (size_t i = 0; i < 4; i++) {
			cout << i + 1 << ". ";
			getline(cin >> ws, answer);
			answer.erase(remove(answer.begin(), answer.end(), ','), answer.end());    //cavabda , varsa silinsin
			answers.push_back(answer);
		}
		cout << "Correct answer: " << endl;
		getline(cin >> ws, correctAnswer);
		correctAnswer.erase(remove(correctAnswer.begin(), correctAnswer.end(), ','), correctAnswer.end());
		ofstream file(filename, ios::app);
		if (file.is_open()) {
			file << question << "?";
			for (auto& i : answers) {
				file << i << ", ";
			}
			file << correctAnswer << "\n";
			file.close();
		}
		answers.clear();
	}
	ofstream file_("quizNames.txt", ios::app);
	if (file_.is_open()) {
		file_ << filename << "\n";
		file_.close();
	}
}

void menu() {
	bool choice;
	while (true) {
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
		while (true) {
			try {
				signIn();
			}
			catch (const std::exception& ex) {
				cout << endl << ex.what() << endl;
				this_thread::sleep_for(chrono::milliseconds(2000));
				continue;
			}
			break;
		}
	}
	User* user = logIn();
	if (checkAdminOrPlayer(user->getUsername(), user->getPassword())) {    //admindirse
		while (true) {
			system("cls");
			cin.ignore();
			cout << "1. Start Quiz" << endl;
			cout << "2. Leader Board" << endl;
			cout << "3. Create Quiz" << endl;
			cout << "4. Exit" << endl;
			cin >> choice_;
			if (choice_ == '1') startQuiz(user);
			else if (choice_ == '2') {
				system("cls");
				leaderBoard();
				this_thread::sleep_for(chrono::milliseconds(4000));
			}
			else if (choice_ == '3') createQuiz();
			else if (choice_ == '4') exit(0);
		}
	}
	else {    //userdirse
		while (true) {
			system("cls");
			cin.ignore();
			cout << "1. Start Quiz" << endl;
			cout << "2. Leader Board" << endl;
			cout << "3. Show my score" << endl;
			cout << "4. Exit" << endl;
			cin >> choice_;
			if (choice_ == '1') startQuiz(user);
			else if (choice_ == '2') {
				system("cls");
				leaderBoard();
				this_thread::sleep_for(chrono::milliseconds(4000));
			}
			else if (choice_ == '3') {
				system("cls");
				showScore(user);
				this_thread::sleep_for(chrono::milliseconds(4000));
			}
			else if (choice_ == '4') exit(0);
		}
	}
	delete user;
}