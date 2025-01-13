#include "Clinic.h"

District Clinic::get_district()
{
	return district;
}
int Clinic::get_places()
{
	return places;
}
string Clinic::get_title()
{
	return title;
}


void Clinic::set_district(District d)
{
	district = d;
}
void Clinic::set_places(int p)
{
	places = p;
}
void Clinic::set_title(string t)
{
	title = t;
}