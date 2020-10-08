#include <iostream>
#include <vector>
using namespace std;
int main()
{
        vector<int> v = {1};
        cout << "v = {1}"<<endl;
        cout << "before the erase, v.front() : "<< v.front()<<endl;

        v.erase(v.begin());
        cout << "after the erase, v.front() : "<< v.front()<<endl;

        cout <<"this is not expected. What I expected is [v.front()="<<"'"<<"']"<<endl;

        cout <<"however, if I run function [at], then... result is below. "<<endl;

        cout << v.at(0);
        /*
           v = {1}
           before the erase, v.front() : 1
           after the erase, v.front() : 1
           this is not expected. What I expected is [v.front()='']
           however, if I run function [at], then... result is below.
           terminate called after throwing an instance of 'std::out_of_range'
           what():  vector::_M_range_check: __n (which is 0) >= this->size() (which is 0)
        */
        return 0;
}
