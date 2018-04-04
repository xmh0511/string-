# string plus plus
extend standard string and easy to use
Construct:
String abc = "123"; //const char* construct;
String abc = std::string("temp"); //std::string to construct;
Output String to scree;
std::cout<<String("screen")<<std::endl;

Split by keyword;
String sp = "abc;efg"; 
auto vec = sp.split(";"); // easy to split by user declared keyword;

concat by ketword;
String jtest(vec,"&"); // easy to join with user declard keyword;

Replace keywords:
String("abc[]fg").replace("[]","&") // cout---> abc&fg;
String("abc[][]fg").replace("[]","&",RegMode::GLOBAL) //cout----->abc&&fg;

format to number;
String t1 = "10.002"; t1.to_int();
String t2 = "123456"; t2.to_double();

format from number to String:
String(10).format_number(); //cout----->10:int;

Format String by lower or upper;
String("abc").to_upper().to_lower();  //  "ABC"--->"abc";

Sort:
String("uafdag").sort(); //cout----->aadfgu;

write String to file:
String("hello,world").write_file("/tmp/test.txt");

read string from file:
String().read_file("/tmp"/test.txt");


