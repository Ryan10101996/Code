#include <iostream>
#include <string>
using namespace std;

class words
{
    public:
        words(){};
        words(string word)
        {
            input = word;
            string input1;
            input1= "Another word";
        }

        words operator+(words morewords)
        {
            words newword;
            newword.input = input + morewords.input;
            return(newword);
        }
        friend ostream &operator << (ostream &output, words &w)
        {
            output<<w.input;
            return output;
        }
        friend istream &operator >> (istream &input, words &w)
        {
            cout<<"Enter a word: "<<endl;
            input>>w.input;
            return input;
        }
        string input;
};

int main()
{
    words word1("Hello");
    words word2(", how are you?");
    words word3;
    words word4;


    cin>>word4;
    word3= word1+word2;
    cout<<word3.input<<endl;
    cout<<word4<<endl;

}
