#include <iostream>
using namespace std;

// a class declaration part
// the base class....
class MyFather
{
  protected:
       char* EyeColor;
       char* HairType;
       double FamSaving;
       int FamCar;

  public:
       MyFather(){}
       ~MyFather(){}
       char* ShowEyeColor();
       char* ShowHairType();
       long double FamilySaving();
       int FamilyCar();
};

// another base class...
class MyMother
{
  // notice the same member variables names
  // as in MyFather class...
  protected:
       char* EyeColor;
       char* HairType;
       int FamHouse;

  public:
       MyMother(){}
       ~MyMother(){}
       char* ShowMotherEye();
       char* ShowMotherHair();
       int FamilyHouse();
};

// single inheritance derived class...
// aaahhh!!! my class :-) finally!!!
class MySelf:public MyFather
{
  // another member variables with same names...
  char* HairType;
  char* Education;

  public:
       MySelf(){ }
       ~MySelf(){ }
       char* ShowMyHair();
       char* ShowMyEducation();
};

// multiple inheritance derived class...
// notice the keyword public must follow every
// parent class list as needed...
class MySister:public MyFather,public MyMother
{
  char* SisEye;
  float MonAllowance;

  public:
       MySister(){}
       ~MySister(){}
       char* ShowSisEye();
       float ShowSisAllownace();
};

// a class implementation part
char* MyFather::ShowEyeColor()
{return EyeColor = "Brown";}

char* MyFather::ShowHairType()
{return HairType = "Bald";}

long double MyFather::FamilySaving()
{return FamSaving = 100000L;}

int MyFather::FamilyCar()
{return  FamCar = 4;}

char* MyMother::ShowMotherEye()
{return EyeColor = "Blue";}

char* MyMother::ShowMotherHair()
{return HairType = "Curly Blonde";}

int MyMother::FamilyHouse()
{return FamHouse = 3;}

char* MySelf::ShowMyHair()
{return HairType = "Straight Black";}

char* MySelf::ShowMyEducation()
{return Education = "Post Graduate";}

char* MySister::ShowSisEye()
{return SisEye = "Black";}

float MySister::ShowSisAllownace()
{return MonAllowance = 1000.00;}

// the main program
int main()
{
      // instantiate the objects...
      MyFather ObjFat;
      MyMother ObjMot;
      MySelf ObjSelf;
      MySister ObjSis;

      cout<<"--My father's data--"<<endl;
      cout<<"His eye:           "<<ObjFat.ShowEyeColor()<<"\n"
           <<"His hair:          "<<ObjFat.ShowHairType()<<"\n"
           <<"Family Saving: USD"<<ObjFat.FamilySaving()<<"\n"
           <<"Family Car:    "<<ObjFat.FamilyCar()<<" cars.\n";

      cout<<"\n--My mother's data--"<<endl;
      cout<<"Her eye: "<<ObjMot.ShowMotherEye()<<endl;
      cout<<"Her hair: "<<ObjMot.ShowMotherHair()<<endl;
      cout<<"Our family house: "<<ObjMot.FamilyHouse()<<" houses."<<endl;

      // notice how to access the base/parent class member functions
      // through the child or derived objects...
      cout<<"\n--My data--"<<endl;
      cout<<"My Hair: "<<ObjSelf. ShowMyHair()<<endl;
      cout<<"My family saving: USD"<<ObjSelf.MySelf::FamilySaving()<<endl;
      cout<<"My family car: "<<ObjSelf.MySelf::FamilyCar()<<" cars."<<endl;
      cout<<"My education: "<<ObjSelf.ShowMyEducation()<<endl;

      cout<<"\n--My sister's data--"<<endl;
      cout<<"Her eye: "<<ObjSis. ShowSisEye()<<endl;
      cout<<"Our family saving: USD"<<ObjSis.MySister::FamilySaving()<<endl;
      cout<<"Our family car: "<<ObjSis.MySister::FamilyCar()<<" cars."<<endl;
      cout<<"Our family house: "<<ObjSis.MySister::FamilyHouse()<<" houses."<<endl;
      cout<<"Her monthly allowances: USD"<<ObjSis.ShowSisAllownace()<<endl;

      return 0;
}
