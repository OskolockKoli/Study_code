#include "Card.h"

int Card::get_duration()
{
	return duration;
}
Disease Card::get_disease()
{
	return disease;
}
Patient Card::get_patient()
{
	return patient;
}
string Card::get_hardness()
{
	return hardness;
}
Clinic Card::get_clinic()
{
	return clinic;
}
int Card::get_place()
{
	return place;
}
Department Card::get_department()
{
	return department;
}
void Card::set_duration(int du)
{
	duration = du;
}
void Card::set_disease(Disease d)
{
	disease = d;
}
void Card::set_patient(Patient p)
{
	patient = p;
}
void Card::set_hardness(string h)
{
	hardness = h;
}
void Card::set_clinic(Clinic c)
{
	clinic = c;
}
void Card::set_place(int p)
{
	place = p;
}
void Card::set_department(Department d)
{
	department = d;
}
