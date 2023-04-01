#include <iostream>
#include<string>
#include<vector>
#include <map>
#include<fstream>
#include<algorithm>
#include<random>
#include<chrono>
#include <thread>

using namespace std;

#include"UserClass.h"
#include"logInSection.h"
#include"LeaderBoard.h"
#include"quizSection.h"
#include"menuSection.h"

int main()
{
	//	admin kimi signUp yoxdur, yalniz logIn mumkundur!(admins.txt file-inda username, passworrd yazilib)
	// duzgun username, password daxil edene kimi username ve password isteyir
	// admin-in score-u yoxdur, quizleri oynaya biler, leaderBoarda baxa biler, quiz yarada biler
	// quiz yaratdiq quiz sayi sorusmuram standart 5 sual olmalidir quizde, evvelceden eyni adda quiz varsa yeni ad teleb edir
	// player kimi daxil olduqda, evvel oynadigi quizi oynaya bilmez, her duzgun cavaba gore score-a 5 elave olunur, score-na baxa biler, leaderBoarda baxa biler
	// 
	// QEYD:
	// quizlere sual tapmamisam ona gore  filedaki suallar eynidi
	menu();
}