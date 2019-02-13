Part 1: OOP general quetions 6,7,8
    Chapt 10: T/F
        10 blanks

Part 2:
    Operator Overloading WRITING
        +,-, <<, >>, member and non-member
        member - argument
        non-member - 2 arguments

        << and >> returns reference to ostream and istream
        friend functions

        reading - pass by reference
        writing - pass by value

        EX1:

        class Doors
        friend ostream& operator<<(ostream &jeff, door x) {

        jeff << x.screw << endl;
    //    - the x will be passed by value
    //    - &jeff passed by reference


        return jeff;
    }

  //////////////////////////////////////////////////////
    EX2:
            friend ostream& operator<<(ostream &jeff, door &x) {

        jeff << x.screw << endl;
    //    - the x will be passed by value
    //    - &jeff passed by reference

    jeff >> x.mat //reading the door

        return jeff;
    }



Part 3:

Inheritance and Polymorphism ... 30pts

What is the output? 6x5 pts

Inh base - derived

How the const and all functions can be called

Which destructor called first

Polymorphism virtual w/ pointers

Difference between static and dynamic object allocation
    -variable of type point and var of type circle
    - call the var and you have to see output
    - whenever we use dynamic you must virtual
    java equivalent of virtual is "abstract"


Son inheritance from mother class and father class
 - if there is a comma, then son inherits from both classes


Part 4:

    Exception Handling:

    2 what is the output of 5 each
    we're gonna be given, and then we throw whatever(given by instruct)
    and figure out catch and output



Part 5:
    Files : 20 pts

    Read and Write into a file;
    - Very similar to the one on the midterm


Part 6:
    Recursion - 10 pts WRITING


    Write a recursive function

    Find Rep
    Cond to stop
    what we are repeating

    if(cond) {
        return a specific value
    }else {
        return operation to be repeated; and call function by changing at least one argument
    }


    // if the function is void, cout

    int fact(n) {
        if (n==1 || n == 0) {
            return 1;
        } else {
            return n*fact(n-1);
        }
    }

    Write a function to compute a^b recursively

    return a(b-1)


    a*a*a*a <-- see reptition
