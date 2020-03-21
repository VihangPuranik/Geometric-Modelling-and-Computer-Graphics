#include<fstream>
#include<iostream>

using namespace std;

int main()
{
    std::fstream myfile("display.txt", std::ios_base::in);
    int a[26][26];
    for(int i =0; i<=25; i++)
    {
        for(int j=0; j<=25; j++)
        {
            myfile>>a[i][j];
            if(j<25)
            {
                if(a[i][j])
                    cout<<" * ";
                else
                    cout<<"   ";
            }
            else
            {
                if(a[i][j])
                    cout<<" * \n";
                else
                    cout<<"   \n";
            }
        }
    }
    return 0;
}
