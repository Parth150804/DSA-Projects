#include <iostream>
#include <vector>

using namespace std;

class SET {
    private:
    vector<int> v = {};

    int binary_search(int n, int key) {
            int low = 0;
            int high = n - 1;
            int mid;
            while (low <= high) {
                mid = (low+high)/2;

                if (v[mid] == key) {
                    return mid;
                }
                else if (v[mid] > key) {
                    high = mid - 1;
                }
                else {
                    low = mid + 1;
                }
            }
            return mid;
        }

    public:
    
    SET() {

    }
    
    int Insert(int data) {
        int n = v.size();
        if (n == 0) {
            v.push_back(data);
            return v.size();
        }

        int val = binary_search(n, data);
        
        if (v[val] == data) {
            return v.size();
        }
        if (v[val] > data) {
            v.insert(v.begin() + val, data);
            return v.size();
        }

        v.insert(v.begin() + val + 1, data);
            return v.size(); 
        }

    int Delete(int data) {
        int n = v.size();

        if (n == 0) {
            return n;
        }
    
        int val = binary_search(n, data);

        if (v[val] == data) {
            v.erase(v.begin() + val);
            return v.size();
        }

        return v.size();

    }

    int Belongs_To(int data) {
        if (v.size() == 0) {
            return 0;
        }
        else {
            int val = binary_search(v.size(), data);

            if(v[val] == data) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }

    int Union(SET &s1) {               
        for (int i = 0; i < v.size(); i++) {
            s1.Insert(v[i]);
        }
        return s1.Size();
    }

    int Intersection(SET s1) {
        vector<int> ans = {};
        for (int i = 0; i < v.size(); i++) {
            if (s1.Belongs_To(v[i]) == 1) {
                ans.push_back(v[i]);
            }
            else {
                continue;
            }
        }
        v = ans;
        return v.size();
    }

    int Size() {
        return v.size();
    }

    int Difference(SET s1) {
        vector<int> ans = {};
        
        for (int i = 0; i < v.size(); i++) {
            if (s1.Belongs_To(v[i]) == 0) {
                ans.push_back(v[i]);
            }
            else {
                continue;
            }
        }
        v = ans;
        return v.size();
    }
    

    int Symmetric_Difference(SET &s1) {
        SET ans = s1;
        for (int i = 0; i < v.size(); i++) {
            ans.Insert(v[i]);
        }
        for (int i = 0; i < v.size(); i++) {
            if (s1.Belongs_To(v[i]) == 1) {
                ans.Delete(v[i]);
            }
            else {
                continue;
            }
        }
        s1 = ans;
        return s1.Size();
    }

    void Print() {
        if (v.size() == 0) {
            std::cout << "\n";
            return;
        }
        for (int i = 0; i < v.size() - 1; i++) {
            std::cout << v[i] << ",";
        }
        std::cout << v[v.size() - 1] << "\n";
    } 
};




int main() {

vector<SET> inputs;

int i1;
// std::cin >> i1;

while(std::cin >> i1) {
    if (i1 == 1) {
        int m1, m2;
        std::cin >> m1 >> m2;
        if (m1 < inputs.size()) {
            std::cout << inputs[m1].Insert(m2) << "\n";
        }
        else {
            SET s1;
            s1.Insert(m2);
            inputs.push_back(s1);
            std::cout << inputs[m1].Insert(m2) << "\n";
        }
    }

    else if (i1 == 2) {
        int m1, m2;
        std::cin >> m1 >> m2;
        if (m1 < inputs.size()) {
            std::cout << inputs[m1].Delete(m2) << "\n";
        }
        else {
            std::cout << -1 << "\n";
        }
    }

    else if (i1 == 3) {
        int m1, m2;
        std::cin >> m1 >> m2;
        if (m1 < inputs.size()) {
            std::cout << inputs[m1].Belongs_To(m2) << "\n";
        }
        else {
            std::cout << -1 << "\n";
        }
    }

    else if (i1 == 4) {
        int m1, m2;
        std::cin >> m1 >> m2;
        if (m1 < inputs.size() and m2 < inputs.size()) {
            std::cout << inputs[m2].Union(inputs[m1]) << "\n";
        }
        else if ((m1 < inputs.size() and m2 >= inputs.size()) or (m2 < inputs.size() and m1 >= inputs.size())) {
            SET s1;
            inputs.push_back(s1);
            std::cout << inputs[m2].Union(inputs[m1]) << "\n";
        }
        else {
            SET s1, s2;
            inputs.push_back(s1);
            inputs.push_back(s2);
            std::cout << inputs[m2].Union(inputs[m1]) << "\n"; 
        }
    }

    else if (i1 == 5) {
        int m1, m2;
        std::cin >> m1 >> m2;
        if (m1 < inputs.size() and m2 < inputs.size()) {
            std::cout << inputs[m1].Intersection(inputs[m2]) << "\n";
        }
        else if ((m1 < inputs.size() and m2 >= inputs.size()) or (m2 < inputs.size() and m1 >= inputs.size())) {
            SET s1;
            inputs.push_back(s1);
            std::cout << inputs[m1].Intersection(inputs[m2]) << "\n";
        }
        else {
            SET s1, s2;
            inputs.push_back(s1);
            inputs.push_back(s2);
            std::cout << inputs[m1].Intersection(inputs[m2]) << "\n"; 
        }
    }

    else if (i1 == 6) {
        int m1;
        std::cin >> m1;
        if (m1 < inputs.size()) {
            std::cout << inputs[m1].Size() << "\n";
        }
        else {
            SET s1;
            inputs.push_back(s1);
            std::cout << inputs[m1].Size() << "\n";
        }
    }

    else if (i1 == 7) {
        int m1, m2;
        std::cin >> m1 >> m2;
        if (m1 < inputs.size() and m2 < inputs.size()) {
            std::cout << inputs[m1].Difference(inputs[m2]) << "\n";
        }
        else if ((m1 < inputs.size() and m2 >= inputs.size()) or (m2 < inputs.size() and m1 >= inputs.size())) {
            SET s1;
            inputs.push_back(s1);
            std::cout << inputs[m1].Difference(inputs[m2]) << "\n";
        }
        else {
            SET s1, s2;
            inputs.push_back(s1);
            inputs.push_back(s2);
            std::cout << inputs[m1].Difference(inputs[m2]) << "\n"; 
        }
    }

    else if (i1 == 8) {
        int m1, m2;
        std::cin >> m1 >> m2;
        if (m1 < inputs.size() and m2 < inputs.size()) {
            std::cout << inputs[m2].Symmetric_Difference(inputs[m1]) << "\n";
        }
        else if ((m1 < inputs.size() and m2 >= inputs.size()) or (m2 < inputs.size() and m1 >= inputs.size())) {
            SET s1;
            inputs.push_back(s1);
            std::cout << inputs[m2].Symmetric_Difference(inputs[m1]) << "\n";
        }
        else {
            SET s1, s2;
            inputs.push_back(s1);
            inputs.push_back(s2);
            std::cout << inputs[m2].Symmetric_Difference(inputs[m1]) << "\n"; 
        }
    }

    else if (i1 == 9) {
        int m1;
        std::cin >> m1;
        if (m1 < inputs.size()) {
            inputs[m1].Print();
        }
        else {
            std::cout << "\n";
        }
    }
}

if(std::cin.eof()) {
    return 0;
}


}
