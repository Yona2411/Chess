#include "LoginManager.h"

void LoginManager::signup(const string& username, const string& password) const
{
	if (m_database->is_user_exists(username))
		throw (USER_ALREADY_EXISTS);
	m_database->signup(username, password);
}

void LoginManager::login(const string& username, const string& password)
{
	if (!m_database->is_user_exists(username))
		throw (USERNAME_PROBLEM);
	if (!m_database->is_password_matches(username, password))
		throw (PASSWORD_PROBLEM);
	m_logged_users.push_back(username);
}

void LoginManager::logout(const string& username)
{
	auto position = std::find(m_logged_users.begin(), m_logged_users.end(), username);
	if (position != m_logged_users.end()) // == myVector.end() means the element was not found
		m_logged_users.erase(position);
}
