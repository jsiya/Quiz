#pragma once

map<string, string> fromFileToMap(string filename) { //txt file-dan username ve passwordu map kimi return edir
	map<string, string> users;
	string username, password;
	ifstream file(filename);
	if (file.is_open()) {
		while (getline(file, username, ' ')){
			getline(file, password);
			users.insert({ username, password });
		}
		file.close();
	}
	return users;
}

bool checkAdminOrPlayer(string username, string password) { //login zamani userin admin ve ya player olmasinin yoxlanmasi
	map<string, string> admins;
	map<string, string> players;
	admins = fromFileToMap("admins.txt");
	players = fromFileToMap("players.txt");
	for (auto& i : admins){
		if (username == i.first && password == i.second) return true;
	}
	for (auto& i : players){
		if (username == i.first && password == i.second) return false;
	}
	throw exception("Invalid User!");
}

bool logOrSignChoice() {
	string choice;
	cout << "1. LOGIN" << endl;
	cout << "2. SIGN IN" << endl;
	cin >> choice;
	if (choice != "1" && choice != "2") throw exception("Invalid choice");
	if (choice == "1") return true;
	return false;
}

User* logIn() {
	string username;
	string password;
	bool userCheck;
	while (true){
		cout << "Enter Username: ";
		cin >> username;
		cout << "Enter Password: ";
		cin >> password;
		try{// loginin yoxlanmasi
			userCheck = checkAdminOrPlayer(username, password); 
		}
		catch (const std::exception& ex){
			cout << ex.what() << endl;
			continue;
		}
		break;
	}
	if (userCheck) {//eger admindirse
		map<string, string> admins;
		admins = fromFileToMap("admins.txt");
		for (auto& i : admins){
			if (username == i.first && password == i.second) return new Admin(i.first, i.second);
		}
	}
	else {//playerdise
		map<string, string> player;
		player = fromFileToMap("players.txt");
		for (auto& i : player){
			if (username == i.first && password == i.second) return new Player(i.first, i.second);
		}
	}
}

bool signIn() { 
	string username, password;
	Player p;
	while (true){
		try{
			cout << "Enter New Username: ";
			cin >> username;
			cout << "Enter Password: ";
			cin >> password;
			p.setUsername(username);
			p.setPassword(password);
		}
		catch (const exception& ex) {
			cout << endl << ex.what() << endl;
			continue;
		}
		break;
	}

	ifstream file_("players.txt");	//yeni username-in evvelceden islendiyini yoxla!
	if (file_.is_open()) {
		string playerUsername;
		while (getline(file_, playerUsername, ' ')){
			if (username == playerUsername) throw exception("this username already used!");
			getline(file_, playerUsername);
		}
	}

	ofstream file("players.txt", ios::app); 
	if (file.is_open()) {
		file << p.getUsername() << " " << p.getPassword() << "\n";
		file.close();
		return true;
	}

	//leaderboarda 0 scorela elave

	ofstream file__("LeaderBoard.txt", ios::app); 
	if (file__.is_open()) {
		file__ << p.getUsername() << " " << 0 << "\n";
		file__.close();
	}
	return false;
}