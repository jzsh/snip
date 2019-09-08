#include <iostream>
#include <soci/soci.h>

using namespace soci;
using namespace std;

int main()
{
	session sql("mysql", "dbname=db1 user=dbuser password=Aa123456");
	string first_name = "Steve";
	string second_name = "Jobs";
	sql << "insert into Person(first_name, second_name)" \
    	" values(:first_name, :second_name)", \
    	use(first_name), use(second_name);
// 	long id;
// 	sql.get_last_insert_id("Person", id)
}
