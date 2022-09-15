#pragma once
#include <iostream>

#define COULD_NOT_OPEN_DB "Failed to open DataBase"

using std::string;

class IDatabase
{
public:
	virtual void signup(const string& username, const string& password) const = 0;
	virtual bool is_user_exists(const string& username) const = 0;
	virtual bool is_password_matches(const string& username, const string& password) const = 0;

};

