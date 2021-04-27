#include <iostream>
#include <fstream>
#include "NumberWithUnits.hpp"
#include <unordered_map>
using namespace std;

namespace ariel {

unordered_map<string,unordered_map<string,double> > u_map;

NumberWithUnits::NumberWithUnits(double _unit ,const string& _str_unit){
    if ( u_map.find(_str_unit) == u_map.end() ) {__throw_invalid_argument("type not exsist"); }
  this->unit=_unit;
  this->str_unit = _str_unit;
}
double NumberWithUnits::convert(const string &from,const string &to, double val){
        if(from == to ) {
                return val;
        }
        return u_map[to][from]*val;
}

bool sameType( NumberWithUnits const & lhs, NumberWithUnits const & rhs ) {
        if((lhs.str_unit==rhs.str_unit) && u_map.find(lhs.str_unit) != u_map.end() && u_map.find(rhs.str_unit) != u_map.end()) {return true;}
        if ( u_map.find(lhs.str_unit) != u_map.end() ) {
                if (u_map[lhs.str_unit].find(rhs.str_unit) != u_map[lhs.str_unit].end()) {
                        return true;
                }
        }
        return false;
}

void NumberWithUnits::read_units(ifstream& units_file){
        string b;
        string u;
        string u2;
        double n1=0;
        double n2=0;
        while(units_file >> n1 >> u >> b >> n2 >> u2) {
                u_map[u][u2]=n2;
                u_map[u2][u]=1/n2;

                for (auto& x : u_map[u]){
                  double conv=u_map[u2][u] * x.second;
                  u_map[u2][x.first]= conv;
                  u_map[x.first][u2]= 1/conv;
              }
                for (auto& x : u_map[u2]){
                  double conv=u_map[u][u2] * x.second;
                  u_map[u][x.first]= conv;
                  u_map[x.first][u]= 1/conv;
              }
        }
}

// // //operator + , =+ , + unry , - , =- , - unry
NumberWithUnits NumberWithUnits::operator+(NumberWithUnits const & rhs ){
        if(!sameType(*this,rhs)) {  __throw_invalid_argument("Not same type");}
        else{
                return NumberWithUnits(this->unit+NumberWithUnits::convert(this->str_unit,rhs.str_unit,rhs.unit),this->str_unit);
        }
}

NumberWithUnits NumberWithUnits::operator+( ) const{

        return NumberWithUnits(+this->unit,this->str_unit);
}

NumberWithUnits& NumberWithUnits::operator+=(const NumberWithUnits& rhs ){
        if(!sameType(*this,rhs)) {  __throw_invalid_argument("Not same type");}
        else{
                double con = NumberWithUnits::convert(this->str_unit,rhs.str_unit,rhs.unit);
                this->unit = this->unit + con;
                return *this;
        }
}

NumberWithUnits NumberWithUnits::operator-(NumberWithUnits const & rhs ){
  if(!sameType(*this,rhs)) {  __throw_invalid_argument("Not same type");}
  else{
          return NumberWithUnits(this->unit-NumberWithUnits::convert(this->str_unit,rhs.str_unit,rhs.unit),this->str_unit);
  }
}


NumberWithUnits NumberWithUnits::operator-() const {
        return NumberWithUnits((-1*this->unit),this->str_unit);
}

NumberWithUnits& NumberWithUnits::operator-=(NumberWithUnits const & rhs ){
  if(!sameType(*this,rhs)) {  __throw_invalid_argument("Not same type");}
  else{
          double con = NumberWithUnits::convert(this->str_unit,rhs.str_unit,rhs.unit);
          this->unit = this->unit - con;
          return *this;
  }
}

//operator > >= < <= == !=

bool operator==( NumberWithUnits const & lhs, NumberWithUnits const & rhs ){
        if(!sameType(lhs,rhs)) {  __throw_invalid_argument("Not same type");}
        double con=NumberWithUnits::convert(lhs.str_unit,rhs.str_unit,rhs.unit);

        const double eps=0.0001;
        if(abs(lhs.unit - con)<eps) {
                return true; return false;
        }
        return false;
}

bool operator!=( NumberWithUnits const & lhs, NumberWithUnits const & rhs ){
        if(!sameType(lhs,rhs)) {  __throw_invalid_argument("Not same type");}

        double con=NumberWithUnits::convert(lhs.str_unit,rhs.str_unit,rhs.unit);
        if(lhs.unit != con) {
                return true; return false;
        }
        return false;
}

bool operator<( NumberWithUnits const & lhs, NumberWithUnits const & rhs ){
        if(!sameType(lhs,rhs)) {  __throw_invalid_argument("Not same type");}

        double con=NumberWithUnits::convert(lhs.str_unit,rhs.str_unit,rhs.unit);
        if(lhs.unit < con) {
                return true; return false;
        }
        return false;

}

bool operator<=( NumberWithUnits const & lhs, NumberWithUnits const & rhs ){

   return lhs < rhs || lhs == rhs;
}

bool operator>( NumberWithUnits const & lhs, NumberWithUnits const & rhs ){
        if(!sameType(lhs,rhs)) {  __throw_invalid_argument("Not same type");}

        double con=NumberWithUnits::convert(lhs.str_unit,rhs.str_unit,rhs.unit);
        if(lhs.unit > con) {
                return true; return false;
        }
        return false;

}

bool operator>=( NumberWithUnits const & lhs, NumberWithUnits const & rhs ){
   return lhs > rhs || lhs == rhs;

}

NumberWithUnits operator--( NumberWithUnits & value, int ){
        return NumberWithUnits(value.unit--, value.str_unit);
}
NumberWithUnits & operator--( NumberWithUnits & value ){
        --value.unit;
        return value;
}
NumberWithUnits & operator++( NumberWithUnits & value ){
        ++value.unit;
        return value;
}
NumberWithUnits operator++( NumberWithUnits & value, int ){
        return NumberWithUnits(value.unit++, value.str_unit);
}

 NumberWithUnits operator*(const NumberWithUnits& lhs,const double &value){
        return NumberWithUnits(lhs.unit*value,lhs.str_unit);
 }
 NumberWithUnits operator*(const double &value, const NumberWithUnits& rhs){
         return NumberWithUnits(rhs.unit*value,rhs.str_unit);

 }

 //operator <<
ostream& operator<<(ostream& os, const NumberWithUnits& value){
        return os<<value.unit<<"["<<value.str_unit<<"]";
}
///operator >>
      istream &operator>>(istream &in, NumberWithUnits &value) {
        string str;
        getline(in, str, ']'); //Calls from IS to STR until he sees]

        string number;
        string un;
        unsigned int i = 0;
        while (' ' == str[i]){
            i++;
        }
        while (('0' <= str[i] && str[i] <= '9') || '+' == str[i] || '-' == str[i] || '.' == str[i]){
            number += str[i++];
        }
        while (' ' == str[i] || str[i] == '['){
            i++;
        }
        while ('A' <= str[i] && str[i] <= 'z'){
            un += str[i++];
        }
       if(u_map.find(un) == u_map.end()) {__throw_invalid_argument("Eror not same type");}

        value = NumberWithUnits(stod(number), un);
        return in;
  //  }
}

}
