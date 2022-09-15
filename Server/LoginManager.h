#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "IDatabase.h"

using std::string;
using std::vector;

#define USER_ALREADY_EXISTS "Can't sign up, User with this username already exists"
#define USERNAME_PROBLEM "User with this username is not exists"
#define PASSWORD_PROBLEM "Password didn't match with your username"


class LoginManager
{
private:
	IDatabase* m_database;
	vector<string> m_logged_users;

public:
	void signup(const string& username, const string& password) const;
	void login(const string& username, const string& password);
	void logout(const string& username);
};

