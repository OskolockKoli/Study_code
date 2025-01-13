#include "Patient.h"
string Patient::get_lname()
{
	return lname;
}
string Patient::get_name()
{
	return name;
}
string Patient::get_pat()
{
	return pat;
}
string Patient::get_address()
{
	return address;
}
string Patient::get_phone()
{
	return phone;
}


void Patient::set_lname(string fio)
{
	lname = fio;
}
void Patient::set_name(string fio)
{
	name = fio;
}
void Patient::set_pat(string fio)
{
	pat = fio;
}
void Patient::set_address(string a)
{
	address = a;
}
void Patient::set_phone(string p)
{
	phone = p;
}