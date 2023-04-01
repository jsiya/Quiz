#pragma once
bool quizCheck(User* user, string quiz_name) { // user-in quizin evvelce oynayib-oynamamasinin yoxlayir
	pair<string, string> quiz;
	quiz.first = user->getUsername();
	quiz.second = quiz_name;
	string username, quizName;
	ifstream file("playedQuizes.txt");
	if (file.is_open()) {
		while (getline(file, username, ':')) {
			while (getline(file, quizName, ',') && quizName !="#") {
				if (quiz.first == username && quiz.second == quizName) return false;
			}
		}
		file.close();
	}
	return true;
}

string quizChoice(User* user) { //quiz secmek
	system("cls");
	string choice, quizName;
	{
		ifstream quizes("quizNames.txt");
		if (quizes.is_open()) {
			while (getline(quizes, quizName, '.')){
				cout << quizName << endl;
				getline(quizes, quizName);
			}
		}
	}
	while (true){
		while (true) {
			cout << "Choose quiz: " << endl;
			cin >> choice;
			choice += ".txt";
			try {
				if (!quizCheck(user, choice)) throw exception("You already played this Game!");
			}
			catch (const exception& ex) {
				cout << ex.what() << endl;
				continue;
			}
			break;
		}
		ifstream quizes("quizNames.txt");
		if (quizes.is_open()) {
			while (getline(quizes, quizName)){
				if (choice == quizName) return choice;
			}
			quizes.close();
			cout << "Invalid Quiz Name!" << endl;
		}
	}
}

void addQuizToUser(User* user, string quiz) {//oynanan quizin userin oynadigi quizlere elave edilmesi
	//quiz bitdikden sonra elave edir
	vector<string> quizes;
	map<string, vector<string>> playedQuizes; // map<username, quizler>
	string username, quizName;
	ifstream file("playedQuizes.txt");
	if (file.is_open()) {
		while (getline(file, username, ':')) {
			quizes.clear();
			while (getline(file, quizName, ',')  && quizName != "") {
				quizes.push_back(quizName);
			}
			getline(file, quizName);//bu sondaki \n kecsin deye
			if (user->getUsername() == username) quizes.push_back(quiz);
			playedQuizes.insert({ username, quizes });
		}
		file.close();
	}
	try{
		ofstream file_("playedQuizes.txt");
		if (file_.is_open()) {
			for (auto& i : playedQuizes){
				file_ << i.first << ":";
				for (auto& j : i.second){
					file_ << j << ",";
				}file_ << ",#\n";
			}
			file_.close();
		}
	}
	catch (const exception& ex) {
		cout << ex.what() << endl;
	}
}

void fillVariants(vector<string>& variants) {
	for (size_t i = 0; i < 5; i++) {
		variants.push_back(" ");
	}
}

void startQuiz(User* user) {
	user->setScore(0); //oyuna 0 scorela basla

	string choice, quizName;
	string question, answer, correct;
	vector<string> answers;
	vector<pair<string, pair<string, vector<string>>>> questions;// vector<pair<sual, pair<duzgun_cavab,cavablar>>>
	quizName = quizChoice(user);
	char variant;
	char correctVariant;
	vector<string>variants;
	vector<string> correctVars;
	fillVariants(variants);

	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();//suallari shuffle etmek ucun
	std::default_random_engine e(seed);

	ifstream quizFile(quizName);
	if (quizFile.is_open()) {
		while (getline(quizFile, question, '?')) {
			answers.clear();
			for (int i = 0; i < 4; i++) {
				getline(quizFile, answer, ',');
				answers.push_back(answer);
			}
			getline(quizFile, correct);
			shuffle(answers.begin(), answers.end(), e);
			questions.push_back({ question,{correct, answers} });
		}
		quizFile.close();
	}
	shuffle(questions.begin(), questions.end(), e);

	int i = 0;
	int score = 0;
	while (true) {
		system("cls");
		variant = 65;
		cout << questions[i].first << "? " << endl;
		for (auto& j : questions[i].second.second) {
			if (j == questions[i].second.first) correctVariant = variant; //cavab duzgun cavabla eyni olduqda duzgun varianti saxliyir
			cout << variant++ << "." << j << "  ";
		}
		cout << endl;
		if (i == 0) cout << "                       save    " << "next" << endl;	//ilk suala gore
		else if(i == questions.size() - 1) cout << "prev" << "                  save" << endl;	//son suala gore
		else cout << "prev" << "                  save    " << "next" << endl;
		cout << "user input: ";
		cin >> choice;
		if (choice == "prev" && i != 0) i--;
		else if (choice == "save" && variants[i] !=  " ") {//save olunmasi ucun evvelceden variant secilmis olmasi
			string corVar = { correctVariant };//correctVariant char oldugu ucun
			if (variants[i] == corVar) score += 5;
			questions.erase(questions.begin() + i);
			variants.erase(variants.begin() + i);
			if (i == questions.size()) i--;//sonuncu sualda i=1 qaldigina gore indexi i = 0 olmalidi
		}
		else if (choice == "save" && variants[i] == " ") {//secilmemis save olsa
			system("cls");
			cout << "Choose variant!" << endl;
			this_thread::sleep_for(chrono::milliseconds(2000));
		}
		else if (choice == "next" && i < questions.size()) i++;
		else if (choice == "a" || choice == "b" || choice == "c" || choice == "d" || choice == "A" || choice == "B" || choice == "C" || choice == "D") {
			choice == "a" ? choice = "A" : choice;
			choice == "b" ? choice = "B" : choice;
			choice == "c" ? choice = "C" : choice;
			choice == "d" ? choice = "D" : choice;
			variants[i] = choice;
		}

		if (questions.size() == 0) {
			if (!checkAdminOrPlayer(user->getUsername(), user->getPassword())) {//ve playerdirse score artsin, adminde score yoxdur
				user->setScore(score);
				leaderBoard(user);
				addQuizToUser(user, quizName);
			}
			break;
		}
	}
}