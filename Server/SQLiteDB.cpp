#include "SQLiteDB.h"

// initialize for static member
IDatabase* SQLiteDB::instance = nullptr;

SQLiteDB::SQLiteDB(void)
{
	int file_exist = _access(DB_NAME, SQLITE_ACCESS_EXISTS);
	int res = sqlite3_open(DB_NAME, &_db);

	if (res != SQLITE_OK) {
		_db = nullptr;
		throw (COULD_NOT_OPEN_DB);
	}
	if (file_exist == SQLITE_ACCESS_EXISTS)
		return;

	statement("CREATE TABLE t_users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, username TEXT NOT NULL UNIQUE, password TEXT NOT NULL);");
}

SQLiteDB::~SQLiteDB(void)
{
	sqlite3_close(_db);
	_db = nullptr;
}

/*********************************************\
* The function create new show of this class. *
\*********************************************/
IDatabase* SQLiteDB::get_instance(void)
{
    if (instance == nullptr)
        instance = (IDatabase*)(new SQLiteDB());

    return instance;
}

/************************************************\
* The function run the statement on the database *
* and put the returned value at data.            *            
* input: statement (char*) and data (T&).		 *
\*************************************************/
template <typename T>
void SQLiteDB::statement(const char* statement, T& data) const
{
	char* error;
	int res = sqlite3_exec(_db, statement, callback<T>, &data, &error);

	if (res != SQLITE_OK)
		throw (error);
}
/*************************************************\
* The function run the statement on the database. *
* input: statement (char*).		                  *
\*************************************************/
void SQLiteDB::statement(const char* statement) const
{
	char* error;
	int res = sqlite3_exec(_db, statement, nullptr, nullptr, &error);

	if (res != SQLITE_OK)
		throw (error);
}

template<typename T>
static int SQLiteDB::callback(void* data, int argc, char** argv, char** azColName) 
{
	T var;
	std::cerr << "You monkey didn't code callback for " << typeid(var).name() << std::endl;
	return 0;
}

template<int>
static int SQLiteDB::callback(void* data, int argc, char** argv, char** azColName)
{
	int* output = reinterpret_cast<int*>(data);
	*output = atoi(argv[0]);
	return 0;
}

/*************************************************\
* The function sign up user to the database.	  *
* input: username (string) and password (string). *
\*************************************************/
void SQLiteDB::signup(const string& username, const string& password) const
{
	std::string s = "INSERT INTO t_users (username, password) VALUES(\"" + username + "\", \"" + password + "\");";
	statement(s.c_str());
}

/**********************************************************\
* The function check if username exsists in the database.  *
* input: username (string).								   *
* output: is username exsists? (bool).					   *
\**********************************************************/
bool SQLiteDB::is_user_exists(const string& username) const
{
	int count = 0;
	std::string s = "SELECT COUNT(1) FROM t_users WHERE username = \"" + username + "\";";
	statement(s.c_str(), count);
	return count > 0;
}

/********************************************************************\
* The function check if username and password match to the database. *
* input: username (string) and password (string).					 *
* output: is they match? (bool).									 *
\********************************************************************/
bool SQLiteDB::is_password_matches(const string& username, const string& password) const
{
	int count = 0;
	std::string s = "SELECT COUNT(1) FROM t_users WHERE username = \"" + username + "\" AND password = \"" + password + "\";";
	statement(s.c_str(), count);
	return count > 0;
}
