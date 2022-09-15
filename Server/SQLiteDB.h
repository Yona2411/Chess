#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <io.h>
#include <sstream>

#define DB_NAME "SQLiteDB.sqlite"

class SQLiteDB : public IDatabase
{
private:
	SQLiteDB(void);
	static IDatabase* instance;
	sqlite3* _db;

	template <typename T>
	void statement(const char* statement, T& data) const;
	void statement(const char* statement) const;

	template <typename T>
	static int callback(void* data, int argc, char** argv, char** azColName);
	template <int>
	static int callback(void* data, int argc, char** argv, char** azColName);

public:
	/* Singletons should not be cloneable or assignable. */
	///////////////////////////////////////////////
	SQLiteDB(SQLiteDB& other) = delete;
	void operator=(const SQLiteDB& other) = delete;
	///////////////////////////////////////////////

	static IDatabase* get_instance(void);
	~SQLiteDB(void);

	void signup(const string& username, const string& password) const override;
	bool is_user_exists(const string& username) const override;
	bool is_password_matches(const string& username, const string& password) const override;

};

