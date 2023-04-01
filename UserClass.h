#pragma once
class User {
protected:
    size_t __id;
    static size_t __static_id;
    string* __username;
    string* __password;
public:
    User() {};
    User(string username, string password) {
        setUsername(username);
        setPassword(password);
    }
    void setUsername(string username) {
        for (auto& i : username){
            if ((i < 65 || i > 122) || (i > 90 &&  i < 97)) throw exception("Username cannot contain any other characters");
        }
        if (__username != nullptr) {
            delete __username;
            __username = nullptr;
        }
        __username = new string(username);
    }
    void setPassword(string password) {
        if (password.length() < 8) throw exception("Password must be more than 8 character");
        if (__password != nullptr) {
            delete __password;
            __password = nullptr;
        }
        __password = new string(password);
    }
    virtual void setScore(int score){}

    string getUsername() const{
        return *__username;
    }
    string getPassword() const{
        return *__password;
    }
    virtual int getScore() = 0;
    virtual ~User() {
        delete __username;
        delete __password;
    }
};
size_t User::__static_id = 0;

class Admin : public User {
public:
    Admin(string username, string password) : User(username, password) {}
    int getScore() { return 0; }
};

class Player : public User {
    int* _score = new int(0);
public:
    Player(){}
    Player(string username, string password) : User(username, password) {

    }
    void setScore(int score) {
        if (_score != nullptr) {
            delete _score;
            _score = nullptr;
        }
        _score = new int(score);
    }
    int getScore() { return *_score; }
    ~Player() {
        delete _score;
    }
};