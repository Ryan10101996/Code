#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include <cctype>
#include "ArgumentManager.h"
using namespace std;

struct AVLNode
{
string info;
int bfactor; //balance factor
AVLNode *llink;
AVLNode *rlink;
};

class tree
{
public:
    string input="";
    string output="";
    string bigword="";
    int rotatecounter=0;
    AVLNode *root = NULL;

    void insertIntoAVL(AVLNode* &root,AVLNode *newNode, bool& isTaller)
    {
        if (root == NULL)
        {
            root = newNode;
            isTaller = true;
        }
        else if (root->info == newNode->info)
            cout << "No duplicates are allowed." << endl;
        else if (root->info > newNode->info) //newItem goes in //the left subtree
        {
            insertIntoAVL(root->llink, newNode, isTaller);
            if (isTaller) //after insertion, the subtree grew in height
                switch (root->bfactor)
                {

                    case -1:
                        balanceFromLeft(root);
                        isTaller = false;
                        break;
                    case 0:
                        root->bfactor = -1;
                        isTaller = true;
                        break;
                    case 1:
                        root->bfactor = 0;
                        isTaller = false;
                }//end switch
        }//end if
        else
        {
            insertIntoAVL(root->rlink, newNode, isTaller);
            if (isTaller) //after insertion, the subtree grew in height
                switch (root->bfactor)
                {
                    case -1:
                        root->bfactor = 0;
                        isTaller = false;
                        break;
                    case 0:
                        root->bfactor = 1;
                        isTaller = true;
                        break;
                    case 1:
                        balanceFromRight(root);
                        isTaller = false;
                }//end switch
        }//end else
    }//insertIntoAVL

    void balanceFromRight(AVLNode* &root)
    {
        AVLNode *p;
        AVLNode *w;
        p = root->rlink; //p points to the left subtree of root
        switch (p->bfactor)
        {
            case -1:
            w = p->llink;

            switch (w->bfactor) //adjust the balance factors
            {
                case -1:
                    root->bfactor = 0;
                    p->bfactor = 1;
                    break;
                case 0:
                    root->bfactor = 0;
                    p->bfactor = 0;
                    break;
                case 1:
                    root->bfactor = -1;
                    p->bfactor = 0;
            }//end switch

            w->bfactor = 0;
            rotateToRight(p);
            root->rlink = p;
            rotateToLeft(root);
            break;

            case 0:
                cerr << "Error: Cannot balance from the left." << endl;
                break;
            case 1:
                root->bfactor = 0;
                p->bfactor = 0;
                rotateToLeft(root);
        }//end switch;
    }//end balanceFromRight

    void balanceFromLeft(AVLNode* &root)
    {
        AVLNode *p;
        AVLNode *w;
        p = root->llink; //p points to the left subtree of root
        switch (p->bfactor)
        {
            case -1:
            root->bfactor = 0;
            p->bfactor = 0;
            rotateToRight(root);
            break;
            case 0:
            cerr << "Error: Cannot balance from the left." << endl;
            break;
            case 1:
            w = p->rlink;
            switch (w->bfactor) //adjust the balance factors
            {
                case -1:
                root->bfactor = 1;
                p->bfactor = 0;
                break;
                case 0:
                root->bfactor = 0;
                p->bfactor = 0;
                break;
                case 1:
                root->bfactor = 0;
                p->bfactor = -1;
            }//end switch
        w->bfactor = 0;
        rotateToLeft(p);
        root->llink = p;
        rotateToRight(root);
        }//end switch;
    }//end balanceFromLeft


    void rotateToLeft(AVLNode* &root)
    {
        AVLNode *p; //pointer to the root of the
        //right subtree of root
        if (root == NULL)
            cerr << "Error in the tree" << endl;
        else if (root->rlink == NULL)
            cerr << "Error in the tree: No right subtree to rotate." << endl;
        else
        {
            p = root->rlink;
            root->rlink = p->llink; //the left subtree of p becomes
            //the right subtree of root
            p->llink = root;
            root = p; //make p the new root node
        }
        rotatecounter++; //add +1 to total number of rotations
    }//rotateLeft


    void rotateToRight(AVLNode* &root)
    {
        AVLNode *p; //pointer to the root of
        //the left subtree of root
        if (root == NULL)
            cerr << "Error in the tree" << endl;
        else if (root->llink == NULL)
            cerr << "Error in the tree: No left subtree to rotate." << endl;
        else
        {
            p = root->llink;
            root->llink = p->rlink; //the right subtree of p becomes
            //the left subtree of root
            p->rlink = root;
            root = p; //make p the new root node
        }

        rotatecounter++; //add +1 to total number of rotations
    }//end rotateRight

    void inorder(AVLNode *p)
    {
        if (p != NULL)
        {
            inorder(p->llink);
            bigword= bigword + '\n' + p->info; //store info in a string
            inorder(p->rlink);
        }
    }

    void insert(const string &newItem) //calls on insertintoAVL to add to tree
    {
        bool isTaller = false;
        AVLNode *newNode;
        newNode = new AVLNode;
        newNode->info = newItem;
        newNode->bfactor = 0;
        newNode->llink = NULL;
        newNode->rlink = NULL;
        insertIntoAVL(root, newNode, isTaller);
    }

    void readfile() //reads the file
    {
        fstream file;
        file.open(input);
        while(!file.eof())
        {
            string word;
            file >> word;   //store each word in string

            if(reject(word))    //checks to see if valid
            {
                string formattedword = removepunctuation(word); //removes punctuation and stores word
                insert(formattedword);

            }
        }
    }

    bool reject(string current)
    {

        int currentwordsize;                //Checks to see if word needs to be rejected by searching through the string for illegal characters
        currentwordsize=current.length();

        int found = current.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ(),.;:?!'");

        if(found!=-1)
            if(current[found]!='"')
                return false;

        for(int i=1;i<currentwordsize-1;i++)
            if(current[i]=='!'||current[i]=='.'||current[i]=='?'||current[i]=='!'||current[i]=='"'||current[i]=='('||current[i]==')'||current[i]==':'||current[i]==';'||current[i]==',')
            {
                return false;       //Searches for puncuation in the middle of the word and returns false if it finds it
            }
        if(current[0]=='!'||current[0]=='.'||current[0]=='?'||current[0]=='!'||current[0]==')'||current[0]==':'||current[0]==';'||current[currentwordsize-1]==
        '('||current[0]==',')   //Searches for the wrong type of punctuation at the start
            return false;
        if(current=="")
            return false;   //deletes blank spaces
        return true;        //If none of the above conditions are met it is safe to insert
    }

    string removepunctuation(string aword)
    {
        int currentwordsize = aword.length();   //Removes punctuation by searching through the word in the same way as above
        if(aword[currentwordsize-1]=='!'||aword[currentwordsize-1]=='?'||aword[currentwordsize-1]==')'||aword[currentwordsize-1]=='"'||aword[currentwordsize-1]==';'
        ||aword[currentwordsize-1]==':'||aword[currentwordsize-1]==','||aword[currentwordsize-1]=='.')
        {
            aword.erase(currentwordsize-1,currentwordsize-1);   //If it comes across puncuation it uses the erase command to delete it
        }
        else
        {

        }
        if(aword[0]=='('||aword[0]=='"')
        {
            aword.erase(0,1);
        }

       aword[0]=toupper(aword[0]);  //sets first letter to capital

       for(int i=1;i<currentwordsize;i++) //sets rest to lowercase
            aword[i]=tolower(aword[i]);

        return aword;   //returns the formatted word
    }

    void fileoutput()
    {
        bigword.erase(0,1); //erase first character which is a blank space
        ofstream out;
        out.open(output,std::ios::app);
        out<<bigword<<endl;     //open file and output
        out<<rotatecounter;
        out.close();
    }



};

//int main()
int main(int argc, char* argv[])
{
    tree thing;

   // thing.input="hw4input.txt";
    //thing.output=("hw5output.txt");

    if (argc < 2)
    {
        cout << "Usage: densemult \"A=<file>;C=<file>\"" <<endl;        //For reading the file names
        return -1;
    }

    ArgumentManager am(argc, argv);

    thing.input = am.get("A");
    thing.output = am.get("C");

    thing.readfile();
    thing.inorder(thing.root);
    thing.fileoutput();

    cout<<"Big word: " + thing.bigword;
}
