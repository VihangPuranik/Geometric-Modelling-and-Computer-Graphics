#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<bits/stdc++.h>

using namespace std;

class vectors
{
public:
    float val[3];
    vectors()
    {

    }
    vectors(float arr[3])
    {
        int i = 0;
        while(i<3)
        {
            val[i] = arr[i];
            i++;
        }
    }
    void print()
    {
        cout<<val[0]<<"i+ "<<val[1]<<"j+ "<<val[2]<<"k."<<endl;
    }
    vectors cross(vectors const &other)
    {
        vectors ans;
        ans.val[0] = other.val[2]*this->val[1] - other.val[1]*this->val[2];
        ans.val[1] = other.val[0]*this->val[2] - other.val[2]*this->val[0];
        ans.val[2] = other.val[1]*this->val[0] - other.val[0]*this->val[1];
        ans.print();
        return ans;
    }
    int dot(vectors const &other)
    {
        int dot = 0;
        for(int i = 0; i <= 3; i++)
        {
            dot += this->val[i] * other.val[i];
        }
        return dot;
    }
    float mag()
    {
        float sum = 0;
        for(int i = 0; i < 3; i++)
        {
            sum += this->val[i] * this->val[i];
            cout<<sum<<endl;
            cout<<this->val[i]<<endl;
        }
        sum = sqrt(sum);
        return sum;
    }
    vectors operator +(vectors const &other)
    {
        float answer[3];
        for(int i = 0; i <= 3; i++)
        {
            answer[i] = this->val[i] + other.val[i];
        }
        vectors ans(answer);
        return ans;
    }
    vectors operator -(vectors const &other)
    {
        float answer[3];
        for(int i = 0; i <= 3; i++)
        {
            val[i] = this->val[i] - other.val[i];
        }
        vectors ans(answer);
        return ans;
    }
    ~vectors()
    {
        cout<<"\nThe vector has been deleted."<<endl;
    }
};
int main(int argc, char** argv)
{
    float u_vec[3] = {atof(argv[1]), atof(argv[2]), atof(argv[3])};
    float v_vec[3] = {atof(argv[4]), atof(argv[5]), atof(argv[6])};
    int command = atof(argv[7]);
    vectors u(u_vec),v(v_vec),x;
    cout<<"Vector 1 is: ";
    u.print();
    cout<<"Vector 2 is: ";
    v.print();
    switch(command)
    {
        case 1:
            {
                x = u+v;
                cout<<"Addition: ";
                x.print();
                break;
            }
        case 2:
            {
                x = u-v;
                cout<<"Subtraction: ";
                x.print();
                break;
            }
        case 3:
            {
                cout<<"The dot product is: "<<u.dot(v);
                break;
            }
        case 4:
            {
                x = u.cross(v);
                cout<<"Cross Product: ";
                x.print();
                break;
            }
        case 5:
            {
                cout<<"Magnitude of vectors are u: "<<u.mag()<<" and v: "<<v.mag();
                break;
            }
    }
    return 0;
}
