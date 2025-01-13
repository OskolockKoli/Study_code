#include "Disease.h"
//#include "Category.h"
Category Disease::get_category()
{
	return category;
}
string Disease::get_title()
{
	return title;
}

void Disease::set_category(string c)
{
	category = c;
}
void Disease::set_title(string t)
{
	title = t;
}