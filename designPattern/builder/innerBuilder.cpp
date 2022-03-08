
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

class Automobile {
private:
    int numberOfTires;
    std::string bodyType;
    std::string engineType;
    int fuelTankSizeInGallons;
    bool airConditioned;
    int odometerMiles;

public:

    class Builder {
    public:        
        int numTires = 0;
        std::string body = "";
        std::string engine = "";
        int fuelTankSize = 0;
        bool airCondition = false;
        int odometer = 0;

        Builder* numberOfTires(int numberOfTires) {
            this->numTires = numberOfTires;
            return this;
        }

        Builder* bodyType(std::string bodyType) {
            this->body = bodyType;
            return this;
        }

        Builder* engineType(std::string engineType) {
            this->engine = engineType;
            return this;
        }

        Builder* fuelTankSizeInGallons(int fuelTankSizeInGallons) {
            this->fuelTankSize = fuelTankSizeInGallons;
            return this;
        }

        Builder* airConditioned(bool airConditioned) {
            this->airCondition = airConditioned;
            return this;
        }

        Builder* odometerMiles(int odometerMiles) {
            this->odometer = odometerMiles;
            return this;
        }

        Automobile build() {
            return Automobile(*this);
        }
    };

    Automobile(Builder builder)
            : numberOfTires(builder.numTires), bodyType(builder.body), engineType(builder.engine),
            fuelTankSizeInGallons(builder.fuelTankSize), airConditioned(builder.airCondition),
            odometerMiles(builder.odometer) {}

    friend ostream& operator<<(ostream&  os, const Automobile& obj);
};

ostream& operator<<(ostream& os, const Automobile& obj)
{
    return os << obj.numberOfTires << " tires, "
              << obj.bodyType << " body type, "
              << obj.engineType << " engine, "
              << obj.fuelTankSizeInGallons << " fuel tank size, "
              << obj.airConditioned << " air condition, "
              << obj.odometerMiles << " odo meter miles\n";
}

int main(int argc, char **argv){
    cout << "Builder - inner test" << endl;
    Automobile automobile = Automobile::Builder().numberOfTires(4)
        ->bodyType("coupe")
        ->engineType("V8")
        ->fuelTankSizeInGallons(16)
        ->airConditioned(true)
        ->odometerMiles(20000)->build();

    cout << automobile;
    return 0;
};
