#include <iostream>
#include <soci/soci.h>
#include <stdint.h>

// using namespace soci;
using namespace std;

struct Person
{
	uint32_t id;
	string first_name; 
	string second_name;
}; 

namespace soci{
template<>
struct type_conversion<Person>
{
	typedef soci::values base_type;
	static void from_base(const base_type& v, indicator ind, Person& person)
	{
		person.id = v.get<long long>("id");
		person.first_name = v.get<string>("first_name");
		person.second_name = v.get<string>("second_name");
	}
	static void to_base(const Person &person, base_type &v, indicator& ind)
	{
        v.set("id", (long long)person.id);
		v.set("first_name", person.first_name);
		v.set("second_name", person.second_name);
	}
};
}

int main()
{
	soci::session sql("mysql", "dbname=db1 user=dbuser password=Aa123456");
	string first_name = "Steve";
	string second_name = "Jobs";
	sql << "insert into Person(first_name, second_name)" \
    	" values(:first_name, :second_name)", \
    	soci::use(first_name), soci::use(second_name);
// 	long id;
// 	sql.get_last_insert_id("Person", id)
//
	int id = 1;
	sql << "SELECT first_name,second_name from PERSON where id=:id ", soci::use(id), soci::into(first_name);	
	if(!sql.got_data()) {
		cout << "no record" << endl;
	}

	cout << first_name << " " << second_name << endl;

	// 多行
	soci::rowset<soci::row> rs = (sql.prepare << "select * from person");
	for(soci::rowset<soci::row>::iterator it = rs.begin(); it != rs.end(); ++it)
	{
		const soci::row& row = *it;
		cout << "id:" << row.get<long long>(0)
			<< " first name:" << row.get<string>(1)
			<< " second name:" << row.get<string>(2) << endl;
	}


	// ORM
	Person person ; 
	person.first_name = "Tony";
	person.second_name = "Ma";
	sql << "insert into Person(first_name, second_name)"
		" values(:first_name, :second_name)", soci::use(person);
}
