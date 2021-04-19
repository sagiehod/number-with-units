#include <string>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;
namespace ariel{
        class NumberWithUnits {

        private:

          double unit ;
          string str_unit;

          friend bool sameType( NumberWithUnits const & lhs, NumberWithUnits const & rhs ) ;
          double convert(const string from ,const string to , double val);
        public:
          NumberWithUnits(double _unit ,string _str_unit){
            unit=_unit;
            str_unit = _str_unit;
          }
          ~NumberWithUnits(){}
          static void read_units(ifstream& units_file);

          //operator + , =+ , + unry , - , =- , - unry
          friend NumberWithUnits operator+( NumberWithUnits const & lhs, NumberWithUnits const & rhs );

          friend NumberWithUnits operator+( NumberWithUnits & value );

          friend NumberWithUnits operator+=( NumberWithUnits& lhs, const NumberWithUnits& rhs );

          friend NumberWithUnits operator-( NumberWithUnits const & lhs, NumberWithUnits const & rhs );

          friend NumberWithUnits operator-(NumberWithUnits & value) ;

          friend NumberWithUnits operator-=( NumberWithUnits & lhs, NumberWithUnits const & rhs );

          //operator > >= < <= == !=


          friend bool operator==( NumberWithUnits const & lhs, NumberWithUnits const & rhs );

          friend bool operator!=( NumberWithUnits const & lhs, NumberWithUnits const & rhs );

          friend bool operator<( NumberWithUnits const & lhs, NumberWithUnits const & rhs );

          friend bool operator<=( NumberWithUnits const & lhs, NumberWithUnits const & rhs );

          friend bool operator>( NumberWithUnits const & lhs, NumberWithUnits const & rhs );

          friend bool operator>=( NumberWithUnits const & lhs, NumberWithUnits const & rhs );
          //operator ++ --
          friend  NumberWithUnits operator--( NumberWithUnits & value, int );
          friend  NumberWithUnits & operator--( NumberWithUnits & value );
          friend  NumberWithUnits & operator++( NumberWithUnits & value );
          friend  NumberWithUnits operator++( NumberWithUnits & value, int );
          //operator *
          friend NumberWithUnits operator*(NumberWithUnits& lhs, double value);
          friend NumberWithUnits operator*(double value, NumberWithUnits& rhs);
          //operator <<
          friend ostream& operator<<(ostream& os, const NumberWithUnits& value);
          friend istream& operator>>(istream& in, NumberWithUnits& value);


        };
}
