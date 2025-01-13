#include "DisSympt.h"

Disease DisSympt::get_disease()
{
	return disease;
}
Symptom DisSympt::get_symptom()
{
	return symptom;
}


void DisSympt::set_disease(Disease d)
{
	disease = d;
}
void DisSympt::set_symptom(Symptom s)
{
	symptom = s;
}