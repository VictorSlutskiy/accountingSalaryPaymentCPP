#pragma once
#include"libraries.h"
#include"struct.h"
struct User
{
	string username;
	string password;
	bool isAdmin;
	bool isBanned;
};
struct Employee
{
		string name;
		string surname;
		string patronymic;
		string department;
		string post;
		float salary;
};
extern vector <User> UserArr;