// #include <fstream>
//#include <stdexcept>
//#include <unistd.h>
//#include <algorithm>
//using namespace doctest;

#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
using namespace ariel;

ifstream units_file{"units.txt"};
const std::string test_file = "./units.txt";

TEST_CASE("m and km)"){
    NumberWithUnits::read_units(units_file);
    NumberWithUnits x{2650 , "cm"};
    NumberWithUnits a{2650, "m"};
    NumberWithUnits b{2.6, "km"};
    CHECK_EQ(a , NumberWithUnits{2650, "m"});
    CHECK_EQ(b, NumberWithUnits{2.6, "km"});
    CHECK_EQ(x , NumberWithUnits{2650, "cm"});
    CHECK_NE(x,a);
    CHECK_NE(a,b);
    CHECK_EQ(a , NumberWithUnits{2.65, "km"});
    CHECK_EQ(b , NumberWithUnits{2600, "m"});
//************* + , =+ , + unry , - , =- , - unry  ,* left, right * ****************}
// + unry,- unry
    CHECK_EQ(+a , NumberWithUnits{2650, "m"});
    CHECK_EQ(+b , NumberWithUnits{2.6, "km"});
    CHECK_EQ(-b , NumberWithUnits{-2.6, "km"});
    CHECK_EQ((-a) , NumberWithUnits{-2650, "m"});
//+,-
    CHECK_EQ(a+b , NumberWithUnits{5.25, "km"});
    CHECK_EQ(b+a , NumberWithUnits{5250, "m"});
  //  CHECK((b-a) == NumberWithUnits( -0.05, "km"));
    CHECK_EQ(a-b , NumberWithUnits{0.05, "km"});


//=+,=-
    CHECK_EQ(a+=b , NumberWithUnits{5.25, "km"});
    CHECK_EQ(b+=a , NumberWithUnits{7850, "m"});
    CHECK_EQ(a-=b , NumberWithUnits{-2.6, "km"});
    CHECK_EQ(b-=a , NumberWithUnits{10450, "m"});

//* left, right *
    CHECK_EQ(a*2 , NumberWithUnits{-5200, "m"});
    CHECK_EQ(2*a , NumberWithUnits{-5200, "m"});
    CHECK_EQ(b*2 , NumberWithUnits{20.9, "km"});
    CHECK_EQ(2*b , NumberWithUnits{20.9, "km"});
      //***************** > >= < <= == !=  ***************************
//< ,<=,>=,>
    CHECK(a<x);
    CHECK(a<b);
    CHECK(a <  NumberWithUnits{-2599, "m"});
    CHECK(a <= NumberWithUnits{-2600, "m"});
    CHECK(b <  NumberWithUnits{10.46, "km"});
    CHECK(b <= NumberWithUnits{10.45, "km"});
    CHECK(a >  NumberWithUnits{-2601, "m"});
    CHECK(a >= NumberWithUnits{-2600, "m"});
    CHECK(b >  NumberWithUnits{2.59, "km"});
    CHECK(b >= NumberWithUnits{2.6, "km"});
//==,!=
    CHECK(a == NumberWithUnits{-2600, "m"});
    CHECK(b == NumberWithUnits{10.45, "km"});
    CHECK(a != NumberWithUnits{2599, "m"});
    CHECK(b != NumberWithUnits{6.2, "km"});
        //********************** ++ -- *******************************
 //str --  , str++
      CHECK(a-- == NumberWithUnits{-2600, "m"});
      CHECK(b-- == NumberWithUnits{10.45, "km"});
      CHECK(a++ == NumberWithUnits{-2601, "m"});
      CHECK(b++ == NumberWithUnits{9.45, "km"});
 //--str  , ++ str
      CHECK(--a == NumberWithUnits{-2601, "m"});
      CHECK(--b == NumberWithUnits{9.45, "km"});
      CHECK(++a == NumberWithUnits{-2600, "m"});
      CHECK(++b == NumberWithUnits{10.45, "km"});
      // ****************** << >> ***************************
//<<
    stringstream str;
    str << b<< endl;
    //CHECK(nospaces(str.str())==nospaces("10.45[km]"));
//>>
    istringstream str2{"5000[m]"};
    str2 >> a;
   
    CHECK(a == NumberWithUnits{5000, "m"});


}

TEST_CASE("-- ++ (++) (--))"){
	// str --  , str++
	NumberWithUnits::read_units(units_file);
	 NumberWithUnits e{2000, "min"};
	 NumberWithUnits f{2.5, "hour"};
 			CHECK(e-- == NumberWithUnits{2000, "min"});
			CHECK(e == NumberWithUnits{1999, "min"});
			CHECK(f-- == NumberWithUnits{2.5, "hour"});
 			CHECK(e++ == NumberWithUnits{1999, "min"});
			CHECK(e == NumberWithUnits{2000, "min"});
 			CHECK(f++ == NumberWithUnits{1.5, "hour"});
 // // //  --str  , ++ str
 			CHECK(--e == NumberWithUnits{1999, "min"});
 			CHECK(--f == NumberWithUnits{1.5, "hour"});
 			CHECK(++e == NumberWithUnits{2000, "min"});
 			CHECK(++f == NumberWithUnits{2.5, "hour"});
}
TEST_CASE("kg and ton)"){
    NumberWithUnits::read_units(units_file);
     NumberWithUnits c{2000, "kg"};
     NumberWithUnits d{2.5, "ton"};
    CHECK_EQ(c , NumberWithUnits{2000, "kg"});
    CHECK_EQ(d, NumberWithUnits{2.5, "ton"});
    CHECK_EQ(c , NumberWithUnits{2, "ton"});
    CHECK_EQ(d , NumberWithUnits{2500, "kg"});
//************* + , =+ , + unry , - , =- , - unry  ,* left, right * ****************}
// + unry,- unry
    CHECK_EQ(+c , NumberWithUnits{2000, "kg"});
    CHECK_EQ(+d , NumberWithUnits{2.5, "ton"});
    CHECK_EQ((-d) , NumberWithUnits{-2.5, "ton"});
    CHECK_EQ((-c) , NumberWithUnits{-2000, "kg"});
//+,-
    CHECK_EQ(c+d , NumberWithUnits{4.5, "ton"});
    CHECK_EQ(d+c , NumberWithUnits{4500, "kg"});
    CHECK_EQ(c-d , NumberWithUnits{-500, "kg"});
    CHECK_EQ(d-c , NumberWithUnits{0.5, "ton"});

//=+,=-
    CHECK_EQ(c+=d , NumberWithUnits{4500, "kg"});
    CHECK_EQ(d+=c , NumberWithUnits{7, "ton"});
    CHECK_EQ(c-=d , NumberWithUnits{-2500, "kg"});
    CHECK_EQ(d-=c , NumberWithUnits{9.5, "ton"});
//* left, right *
    CHECK_EQ(c*2 , NumberWithUnits{-5000, "kg"});
    CHECK_EQ(2*c , NumberWithUnits{-5000, "kg"});
    CHECK_EQ(d*2 , NumberWithUnits{19, "ton"});
    CHECK_EQ(2*d , NumberWithUnits{19, "ton"});
//       //***************** > >= < <= == !=  ***************************
//< ,<=,>=,>
    CHECK(c <  NumberWithUnits{-2499, "kg"});
    CHECK(c <= NumberWithUnits{-2500, "kg"});
    CHECK(d <  NumberWithUnits{9.56, "ton"});
    CHECK(d <= NumberWithUnits{9.5, "ton"});
    CHECK(c >  NumberWithUnits{-2599, "kg"});
    CHECK(c >= NumberWithUnits{-2500, "kg"});
    CHECK(d >  NumberWithUnits{2.49, "ton"});
    CHECK(d >= NumberWithUnits{2.5, "ton"});
//==,!=
    CHECK(c == NumberWithUnits{-2500, "kg"});
    CHECK(d == NumberWithUnits{9.5, "ton"});
    CHECK(d != NumberWithUnits{1234, "kg"});
    CHECK(c != NumberWithUnits{3.2, "ton"});
   //********************** ++ -- *******************************
 // str --  , str++
      CHECK(c-- == NumberWithUnits{-2500, "kg"});
      CHECK(d-- == NumberWithUnits{9.5, "ton"});
      CHECK(c++ == NumberWithUnits{-2501, "kg"});
      CHECK(d++ == NumberWithUnits{8.5, "ton"});
// --str  , ++ str
      CHECK(--c == NumberWithUnits{-2501, "kg"});
      CHECK(--d == NumberWithUnits{8.5, "ton"});
      CHECK(++c == NumberWithUnits{-2500, "kg"});
      CHECK(++d == NumberWithUnits{9.5, "ton"});
  // ****************** << >> ***************************
//<<
    stringstream str;
    str << d<< endl;
     // CHECK(nospaces(str.str())==("9.5[ton]"));

//>>
    istringstream str2{"1500[kg]"};
    str2 >> c;
    CHECK(c == NumberWithUnits{1500, "kg"});
}
TEST_CASE("min and hour)"){
     NumberWithUnits::read_units(units_file);
     NumberWithUnits e{360, "min"};
     NumberWithUnits f{6.5, "hour"};

    CHECK_EQ(e , NumberWithUnits{360, "min"});
    CHECK_EQ(f, NumberWithUnits{6.5, "hour"});
    CHECK_EQ(e , NumberWithUnits{6, "hour"});
    CHECK_EQ(f , NumberWithUnits{390, "min"});

//************* + , =+ , + unry , - , =- , - unry  ,* left, right * ****************}
// + unry,- unry
    CHECK_EQ(+e , NumberWithUnits{360, "min"});
    CHECK_EQ(+f , NumberWithUnits{6.5, "hour"});
    CHECK_EQ((-f) , NumberWithUnits{-6.5, "hour"});
    CHECK_EQ((-e) , NumberWithUnits{-360, "min"});
//+,-
    CHECK_EQ(e+f , NumberWithUnits{750,"min"});
    CHECK_EQ(f+e , NumberWithUnits{12.5, "hour"});
    CHECK_EQ(e-f , NumberWithUnits{-30, "min"});
    CHECK_EQ(f-e , NumberWithUnits{0.5, "hour"});

//=+,=-
    CHECK_EQ(e+=f , NumberWithUnits{750, "min"});
    CHECK_EQ(f+=e , NumberWithUnits{19, "hour"});
    CHECK_EQ(e-=f , NumberWithUnits{-390, "min"});
    CHECK_EQ(f-=e , NumberWithUnits{25.5, "hour"});
//* left, right *
    CHECK_EQ(e*2 , NumberWithUnits{-780, "min"});
    CHECK_EQ(2*e , NumberWithUnits{-780, "min"});
    CHECK_EQ(f*2 , NumberWithUnits{51, "hour"});
    CHECK_EQ(2*f , NumberWithUnits{51, "hour"});
//       //***************** > >= < <= == !=  ***************************
//< ,<=,>=,>
    CHECK(e <  NumberWithUnits{-389, "min"});
    CHECK(e <= NumberWithUnits{-390, "min"});
    CHECK(f <  NumberWithUnits{25.6, "hour"});
    CHECK(f <= NumberWithUnits{25.6, "hour"});
    CHECK(e >  NumberWithUnits{-391, "min"});
    CHECK(e >= NumberWithUnits{-390, "min"});
    CHECK(f >  NumberWithUnits{25.4, "hour"});
    CHECK(f >= NumberWithUnits{25.5, "hour"});
//==,!=
    CHECK(e == NumberWithUnits{-390, "min"});
    CHECK(f == NumberWithUnits{25.5, "hour"});
    CHECK(f != NumberWithUnits{4321, "min"});
    CHECK(e != NumberWithUnits{390, "hour"});
		//********************** ++ -- *******************************
 // str --  , str++
			CHECK(e-- == NumberWithUnits{-390, "min"});
			CHECK(f-- == NumberWithUnits{25.5, "hour"});
			CHECK(e++ == NumberWithUnits{-391, "min"});
			CHECK(f++ == NumberWithUnits{24.5, "hour"});
//  --str  , ++ str
			CHECK(--e == NumberWithUnits{-391, "min"});
			CHECK(--f == NumberWithUnits{24.5, "hour"});
			CHECK(++e == NumberWithUnits{-390, "min"});
			CHECK(++f == NumberWithUnits{25.5, "hour"});
    // ****************** << >> ***************************
//<<
    stringstream str;
    str << f<< endl;
   // CHECK(nospaces(str.str())==("25.5[hour]"));
//>>
    istringstream str2{"500[min]"};
    str2 >> e;
    CHECK(e == NumberWithUnits{500, "min"});



}
