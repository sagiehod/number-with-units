#include <iostream>
#include <fstream>
#include "NumberWithUnits.hpp"
#include <unordered_map>
using namespace std;

namespace ariel {



unordered_map<string,unordered_map<string,double> > u_map;


double convert(const string &from,const string &to, double val){
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
        }
}


// // //operator + , =+ , + unry , - , =- , - unry
NumberWithUnits operator+( NumberWithUnits const & lhs, NumberWithUnits const & rhs ){
        if(!sameType(lhs,rhs)) {  __throw_invalid_argument("Not same type");}
        else{
                return NumberWithUnits(lhs.unit+convert(lhs.str_unit,rhs.str_unit,rhs.unit),lhs.str_unit);
        }
}

NumberWithUnits operator+( NumberWithUnits & value ){
        if(value.unit<0) {
                return NumberWithUnits((-1*value.unit),value.str_unit);
        }
        return NumberWithUnits(value.unit,value.str_unit);
}


NumberWithUnits operator+=( NumberWithUnits& lhs,const NumberWithUnits& rhs ){
        if(!sameType(lhs,rhs)) {  __throw_invalid_argument("Not same type");}
        else{
                double con = convert(lhs.str_unit,rhs.str_unit,rhs.unit);
                lhs.unit = lhs.unit + con;
                return lhs;
        }
}

NumberWithUnits operator-( NumberWithUnits const & lhs, NumberWithUnits const & rhs ){
        if(!sameType(lhs,rhs)) {  __throw_invalid_argument("Not same type");}
        else{
                return NumberWithUnits(lhs.unit-convert(lhs.str_unit,rhs.str_unit,rhs.unit),lhs.str_unit);
        }
}


NumberWithUnits operator-(NumberWithUnits & value) {
        return NumberWithUnits((-1*value.unit),value.str_unit);
}


NumberWithUnits operator-=( NumberWithUnits & lhs, NumberWithUnits const & rhs ){
        if(!sameType(lhs,rhs)) {  __throw_invalid_argument("Not same type");}
        else{
                double con = convert(lhs.str_unit,rhs.str_unit,rhs.unit);
                lhs.unit = lhs.unit - con;
                return lhs;
        }
}

//operator > >= < <= == !=


bool operator==( NumberWithUnits const & lhs, NumberWithUnits const & rhs ){
        if(!sameType(lhs,rhs)) {  __throw_invalid_argument("Not same type");}
        double con=convert(lhs.str_unit,rhs.str_unit,rhs.unit);

        const double eps=0.0001;
        if(abs(lhs.unit - con)<eps) {
                return true; return false;
        }
        return false;
}

bool operator!=( NumberWithUnits const & lhs, NumberWithUnits const & rhs ){
        if(!sameType(lhs,rhs)) {  __throw_invalid_argument("Not same type");}

        double con=convert(lhs.str_unit,rhs.str_unit,rhs.unit);
        if(lhs.unit != con) {
                return true; return false;
        }
        return false;
}

bool operator<( NumberWithUnits const & lhs, NumberWithUnits const & rhs ){
        if(!sameType(lhs,rhs)) {  __throw_invalid_argument("Not same type");}

        double con=convert(lhs.str_unit,rhs.str_unit,rhs.unit);
        if(lhs.unit < con) {
                return true; return false;
        }
        return false;

}

bool operator<=( NumberWithUnits const & lhs, NumberWithUnits const & rhs ){
        if(!sameType(lhs,rhs)) {  __throw_invalid_argument("Not same type");}

        double con=convert(lhs.str_unit,rhs.str_unit,rhs.unit);
        if(lhs.unit <= con) {
                return true; return false;
        }
        return false;

}

bool operator>( NumberWithUnits const & lhs, NumberWithUnits const & rhs ){
        if(!sameType(lhs,rhs)) {  __throw_invalid_argument("Not same type");}

        double con=convert(lhs.str_unit,rhs.str_unit,rhs.unit);
        if(lhs.unit > con) {
                return true; return false;
        }
        return false;

}

bool operator>=( NumberWithUnits const & lhs, NumberWithUnits const & rhs ){
        if(!sameType(lhs,rhs)) {  __throw_invalid_argument("Not same type");}

        double con=convert(lhs.str_unit,rhs.str_unit,rhs.unit);
        if(lhs.unit >= con) {
                return true; return false;
        }
        return false;
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


NumberWithUnits operator*(NumberWithUnits& lhs, double value){
        return NumberWithUnits(lhs.unit*value, lhs.str_unit);
}
NumberWithUnits operator*(double value, NumberWithUnits& rhs){
        return NumberWithUnits(rhs.unit*value, rhs.str_unit);
}
// //operator <<
ostream& operator<<(ostream& os, const NumberWithUnits& value){
        return os<<value.unit<<"["<<value.str_unit<<"]";
}
istream& operator>>(istream& in, NumberWithUnits& value){
        string temp;
        in >> value.unit>> temp >> value.str_unit;
        return in;
}
}
