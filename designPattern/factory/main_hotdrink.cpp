#include <iostream>
#include <vector>
#include <typeinfo>
#include <string>
#include <memory>
#include <map>
#include <functional>
 
using namespace std;

struct HotDrink
{
   public:
      virtual ~HotDrink() = default;
      virtual void prepare(int volume) = 0;
};

struct Tea : HotDrink
{
   void prepare(int volume) override
   {
      std::cout << "Take tea bag, boil water, pour " << volume << "ml, add some lemon\n";
   }
};

struct Coffee : HotDrink
{
   void prepare(int volume) override
   {
      std::cout << "Grind some beans, boil water, pour " << volume << "ml, add cream, enjoy!\n";
   }
};

#if 0
std::unique_ptr<HotDrink> make_drink(string type)
{
   std::unique_ptr<HotDrink> drink;
   if(type == "tea"){
      drink = make_unique<Tea>();
      drink->prepare(200);
   }
   else{
      drink = make_unique<Coffee>();
      drink->prepare(50);
   }
   return drink;
}
#endif

//abstract factory
class HotDrinkFactory
{
   public:
      //factory method
      virtual std::unique_ptr<HotDrink> make() const = 0;
};

struct CoffeeFactory : HotDrinkFactory
{
   std::unique_ptr<HotDrink> make() const override {
      return make_unique<Coffee>();
   }
};

struct TeaFactory : HotDrinkFactory
{
   std::unique_ptr<HotDrink> make() const override {
      return make_unique<Tea>();
   }
};

class DrinkFactory
{
   private:
      map<string, std::unique_ptr<HotDrinkFactory>> hotdrink_factories;

   public:
      DrinkFactory() {
         hotdrink_factories["coffee"] = make_unique<CoffeeFactory>();
         hotdrink_factories["tea"] = make_unique<TeaFactory>();
      }

      std::unique_ptr<HotDrink> make_drink(const string& name){
         auto drink = hotdrink_factories[name]->make();
         return drink;
      }

};

int main() {

   DrinkFactory stand;
   auto cup1 = stand.make_drink("tea");
   cup1->prepare(50);
   auto cup2 = stand.make_drink("coffee");
   cup2->prepare(200);
}


//end of file
