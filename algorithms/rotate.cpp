/*
Learning Rotate by modifying a vector
*/

#include <algorithm>
#include <vector>
#include <iostream>





int main(){
    std::vector<int> vector1 = {1 , 2, 3, 4, 5, 6, 7, 8, 9};
    // {1,2,3,4,5,6,7,8,9}
    // begin  middle    end
    std::rotate(vector1.begin(), vector1.begin() + 2, vector1.end());

    for (auto const &i : vector1){
        std::cout << i << std::endl; 
    }
}