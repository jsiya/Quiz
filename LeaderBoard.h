#pragma once

void addUserScore(User* user) {
	vector<pair<string, int>> players;
	string username, score;
	ifstream file("LeaderBoard.txt");
	if (file.is_open()) {
		while (getline(file, username, ' ')){
			getline(file, score);
			players.push_back({ username, stoi(score) });
		}
		file.close();
	}
	for (auto& i : players){
		if (i.first == user->getUsername()) i.second = i.second + user->getScore();
	}
	ofstream file_("LeaderBoard.txt");
	if (file_.is_open()) {
		for (auto& i : players){
			file_ << i.first << " " << i.second << "\n";
		}
		file_.close();
	}
}

void leaderBoard(User* user = nullptr) {
	string username, score;
	if (user == nullptr) { //nullptrdirse ekrana cixardir
		ifstream file("LeaderBoard.txt");
		int i = 0;
		cout << "________Leader Board________" << endl;
		if (file.is_open()) {
			while (getline(file, username, ' ')) {
				getline(file, score);
				cout << username << " " << score << endl;
				i++;
				if (i == 10) break;
			}
			file.close();
		}
	}
	else {//nizamliyir 
		addUserScore(user);

		vector<pair<string, string>> players;
		ifstream file("LeaderBoard.txt");
		if (file.is_open()) {
			while (getline(file, username, ' ')){
				getline(file, score);
				players.push_back({ username, score });
			}
			file.close();
		}

		sort(players.begin(), players.end(),
			[](const pair<string, string>& u1, const pair<string, string>& u2) {
				return stoi(u1.second) > stoi(u2.second);
			});

		ofstream file_("LeaderBoard.txt");
		if (file_.is_open()) {
			for (auto& i : players){
				file_ << i.first << " " << i.second << "\n";
			}
			file_.close();
		}
	}
}