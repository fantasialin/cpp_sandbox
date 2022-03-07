#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

class PersonBuilder;
class Person
{
    string m_name, m_street_address, m_post_code, m_city;  // Personal Detail
    string m_company_name, m_position, m_annual_income;    // Employment Detail
    Person(string name) : m_name(name) {}
  public:
    friend class PersonBuilder;
    friend ostream& operator<<(ostream&  os, const Person& obj);
    static PersonBuilder create(string name);
};

class PersonBuilder
{
    Person person;
  public:
    PersonBuilder(string name) : person(name) {}
    operator Person() const { return move(person); }
    PersonBuilder&  lives();
    PersonBuilder&  at(string street_address);
    PersonBuilder&  with_postcode(string post_code);
    PersonBuilder&  in(string city);
    PersonBuilder&  works();
    PersonBuilder&  with(string company_name);
    PersonBuilder&  as_a(string position);
    PersonBuilder&  earning(string annual_income);
};

PersonBuilder Person::create(string name) { return PersonBuilder{name}; }

ostream& operator<<(ostream& os, const Person& obj)
{
    return os << obj.m_name
              << endl
              << "lives : " << endl
              << "at " << obj.m_street_address
              << " with postcode " << obj.m_post_code
              << " in " << obj.m_city
              << endl
              << "works : " << endl
              << "with " << obj.m_company_name
              << " as a " << obj.m_position
              << " earning " << obj.m_annual_income;
}

PersonBuilder&  PersonBuilder::lives() { return *this; }
PersonBuilder&  PersonBuilder::works() { return *this; }
PersonBuilder&  PersonBuilder::with(string company_name) 
{
    person.m_company_name = company_name; 
    return *this;
}

PersonBuilder&  PersonBuilder::as_a(string position) 
{
    person.m_position = position; 
    return *this;
}

PersonBuilder&  PersonBuilder::earning(string annual_income) 
{
    person.m_annual_income = annual_income; 
    return *this;
}

PersonBuilder&  PersonBuilder::at(string street_address) 
{
    person.m_street_address = street_address; 
    return *this;
}

PersonBuilder&  PersonBuilder::with_postcode(string post_code) 
{
    person.m_post_code = post_code; 
    return *this;
}

PersonBuilder&  PersonBuilder::in(string city) 
{
    person.m_city = city; 
    return *this;
}

int main(int argc, char **argv){
    cout << "Builder - person test" << endl;
    Person p = Person::create("John")
                                .lives()
                                .at("123 London Road")
                                .with_postcode("SW1 1GB")
                                .in("London")
                                .works()
                                .with("PragmaSoft")
                                .as_a("Consultant")
                                .earning("10e6");
    cout << p << endl;
    return 0;
};
