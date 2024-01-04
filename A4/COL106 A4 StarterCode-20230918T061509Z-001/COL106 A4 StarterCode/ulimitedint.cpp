/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
// #include <iostream>

UnlimitedInt::UnlimitedInt() {
    size = 0;
    capacity = 1;
    unlimited_int = new int[capacity];
    sign = 1;
}

UnlimitedInt::UnlimitedInt(string s) {
    capacity = 2*s.length();

    unlimited_int = new int[capacity];
    if (s[0] == '-') {
        size = s.length() - 1;
        for (int i = 1; i < s.length(); i++) {
            unlimited_int[i-1] = s[i] - '0';
        }
        sign = -1;
    }
    else {
        size = s.length();
        for (int i = 0; i < s.length(); i++) {
            unlimited_int[i] = s[i] - '0';
        }  
        if (s == "0") {
            sign = 0;
        }
        else {
            sign = 1;
        } 
    }
}

UnlimitedInt::UnlimitedInt(int i) {
    string s = std::to_string(i);
    capacity = 2*s.length();
    
    unlimited_int = new int[capacity];
    if (s[0] == '-') {
        size = s.length() - 1;
        for (int i = 1; i < s.length(); i++) {
            unlimited_int[i-1] = s[i] - '0';
        }
        sign = -1;
    }
    else {
        size = s.length();
        for (int i = 0; i < s.length(); i++) {
            unlimited_int[i] = s[i] - '0';
        }  
        if (s == "0") {
            sign = 0;
        }
        else {
            sign = 1;
        } 
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz) {
    size = sz;
    capacity = cap;
    unlimited_int = ulimited_int;
    sign = sgn;
}

UnlimitedInt::~UnlimitedInt() {
    delete[] unlimited_int;
}

int UnlimitedInt::get_size() {
    return size;
}

int* UnlimitedInt::get_array() {
    return unlimited_int;
}

int UnlimitedInt::get_sign() {
    return sign;
}

string UnlimitedInt::to_string() {
    string s = "";
    if (sign == 1 or sign == 0) {
        for (int i = 0; i < size; i++) {
            s += std::to_string(unlimited_int[i]);
        }
    }
    else {
        s += "-";
        for (int i = 0; i < size; i++) {
            s += std::to_string(unlimited_int[i]);
        }        
    }
    return s;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2) {
    int cap = i1 -> get_size() + i2 -> get_size() + 10;
    int* arr1 = i1 -> get_array();
    int* arr2 = i2 -> get_array();

    int* ans = new int[cap];

    UnlimitedInt* result = new UnlimitedInt();

    if (i1 -> get_sign() == i2 -> get_sign()) {
        if (i1 -> get_sign() == 0) {
            ans[0] = 0;
            result -> unlimited_int = ans;
            result -> sign = 0;
            result -> size = 1;
            result -> capacity = cap;
            return result;
        }
        else {
            int i = i1 -> get_size() - 1;
            int j = i2 -> get_size() - 1;
            int k = 0;
            int carry = 0;
            int sum;
            while (i >= 0 and j >= 0) {
                sum = arr1[i] + arr2[j] + carry;
                if (sum >= 10) {
                    sum = sum%10;
                    carry = 1;
                }
                else {
                    carry = 0;
                }
                ans[k] = sum;
                i--;
                j--;
                k++;
            }

            if (carry == 1 and i == j) {
                ans[k] = carry;
                carry = 0;
                k++;
            }

            while (i >= 0) {
                sum = arr1[i] + carry;
                if (sum >= 10) {
                    sum = sum%10;
                    carry = 1;
                }
                else {
                    carry = 0;
                }
                ans[k] = sum;
                k++;
                i--;
            }

            while (j >= 0) {
                sum = arr2[j] + carry;
                if (sum >= 10) {
                    sum = sum%10;
                    carry = 1;
                }
                else {
                    carry = 0;
                }
                ans[k] = sum;
                k++;
                j--;
            }       

            if (carry == 1) {
                ans[k] = carry;
                k++;
                carry = 0;
            }

            i = 0;
            j = k-1;
            int z = k;

            while (i <= j) {
                swap(ans[i], ans[j]);
                i++;
                j--;
            }
            int w = 0;
            bool flag = false;
            for (int m = 0; m < z; m++) {
                if (ans[m] == 0 and flag == false) {
                    k--;
                }
                else {
                    swap(ans[w], ans[m]);
                    w++;
                    flag = true;
                }
            }

            result -> unlimited_int = ans;
            result -> size = k;
            if (i1 -> get_sign() == 1) {
                result -> sign = 1;
            }
            else {
                result -> sign = -1;
            }
            result -> capacity = cap;

            return result;
        }   
    }
    else {
        if (i1 -> get_sign() == 1) {
            if (i2 -> get_sign() == -1) {
                i2 -> sign = 1;
                return sub(i1, i2);
            }
            else {
                return i1;
            }
        }
        else if (i1 -> get_sign() == -1) {
            if (i2 -> get_sign() == 1) {
                i1 -> sign = 1;
                return sub(i2, i1);
            }
            else {
                return i1;
            }
        }
        else {
            return i2;
        }
    }
}

string compare_magnitude(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1 -> get_size() > i2 -> get_size()) {
        return "i1";
    }
    else if (i2 -> get_size() > i1 -> get_size()) {
        return "i2";
    }
    else {
        int* arr1 = i1 -> get_array();
        int* arr2 = i2 -> get_array();
        int n = i1 -> get_size();

        for (int i = 0; i < n; i++) {
            if (arr1[i] > arr2[i]) {
                return "i1";
            }
            else if (arr1[i] < arr2[i]) {
                return "i2";
            }
            else {
                continue;
            }
        }
        return "equal";
    }
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2) {
    int cap = i1 -> get_size() + i2 -> get_size() + 10;
    int* arr1 = i1 -> get_array();
    int* arr2 = i2 -> get_array();

    int* ans = new int[cap];

    UnlimitedInt* result = new UnlimitedInt();

    if (i1 -> get_sign() == i2 -> get_sign()) {
        int i = i1 -> get_size() - 1;
        int j = i2 -> get_size() - 1;
        int k = 0;
        int borrow = 0;
        int diff = 0; 
        if (compare_magnitude(i1, i2) == "i1") {
            while (i >= 0 and  j >= 0) {
                if (arr1[i] >= arr2[j]) {
                    diff = arr1[i] - arr2[j] - borrow; 
                    if (diff < 0) {
                        diff += 10;
                        borrow = 1;
                    }
                    else {
                        borrow = 0;
                    }
                }
                else {
                    diff = arr1[i] + 10 - arr2[j] - borrow;
                    if (diff == 10) {
                        diff--;
                    }
                    borrow = 1;
                }
                ans[k] = diff;
                i--;
                j--;
                k++;
            }

            if (borrow == 1 and arr1[i] != 0) {
                arr1[i] = arr1[i] - 1;
                borrow = 0;
            }
            
            while (i >= 0) {
                if (borrow == 1) {
                    if (arr1[i] == 0) {
                        arr1[i] = arr1[i] + 10 - borrow;
                        borrow = 1;
                    }
                    else {
                        arr1[i] -= borrow;
                        borrow = 0;
                    }
                }
                ans[k] = arr1[i];
                k++;
                i--;
            }

            i = 0;
            j = k-1;
            int z = k;

            while (i <= j) {
                swap(ans[i], ans[j]);
                i++;
                j--;
            }
            int w = 0;
            bool flag = false;
            for (int m = 0; m < z; m++) {
                if (ans[m] == 0 and flag == false) {
                    k--;
                }
                else {
                    swap(ans[w], ans[m]);
                    w++;
                    flag = true;
                }
            }

            if (i1 -> get_sign() == 1) {
                result -> sign = 1;
            }
            else {
                result -> sign = -1;
            }
            result -> unlimited_int = ans;
            result -> capacity = cap;
            result -> size = k;
            return result;
        }
        else if (compare_magnitude(i1, i2) == "i2") {
            while (i >= 0 and  j >= 0) {
                if (arr2[j] >= arr1[i]) {
                    diff = arr2[j] - arr1[i] - borrow;
                    if (diff < 0) {
                        diff += 10;
                        borrow = 1;
                    }
                    else {
                        borrow = 0;
                    }                 
                }
                else {
                    diff = arr2[j] + 10 - arr1[i] - borrow;
                    if (diff == 10) {
                        diff--;
                    }
                    borrow = 1;
                }
                ans[k] = diff;
                i--;
                j--;
                k++;
            }

            if (borrow == 1 and arr2[j] != 0) {
                arr2[j] = arr2[j] - 1;
                borrow = 0;
            }

            while (j >= 0) {
                if (borrow == 1) {
                    if (arr2[j] == 0) {
                        arr2[j] = arr2[j] + 10 - borrow;
                        borrow = 1;
                    }
                    else {
                        arr2[j] -= borrow;
                        borrow = 0;
                    }
                }
                ans[k] = arr2[j];
                k++;
                j--;
            }
            i = 0;
            j = k-1;
            int z = k;

            while (i <= j) {
                swap(ans[i], ans[j]);
                i++;
                j--;
            }

            int w = 0;
            bool flag = false;
            for (int m = 0; m < z; m++) {
                if (ans[m] == 0 and flag == false) {
                    k--;
                }
                else {
                    swap(ans[w], ans[m]);
                    w++;
                    flag = true;
                }
            }

            if (i2 -> get_sign() == 1) {
                result -> sign = -1;
            }
            else {
                result -> sign = 1;
            }
            result -> unlimited_int = ans;
            result -> capacity = cap;
            result -> size = k;
            return result;
        }
        else {
            ans[0] = 0;
            result -> unlimited_int = ans;
            result -> capacity = cap;
            result -> size = 1;
            result -> sign = 0;
            return result;
        }
    }
    else {
        if (i1 -> get_sign() == 1) {
            if (i2 -> get_sign() == -1) {
                i2 -> sign = 1;
                return add(i1, i2);
            }
            else {
                return i1;
            }
        }
        else if (i1 -> get_sign() == -1) {
            if (i2 -> get_sign() == 1) {
                i2 -> sign = -1;
                return add(i1, i2);
            }
            else {
                return i1;
            }
        }
        else {
            if (i2 -> get_sign() == 1) {
                i2 -> sign = -1;
                return i2;
            }
            else {
                i2 -> sign = 1;
                return i2;
            }
        }
    }
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2) {
    int cap = i1 -> get_size() + i2 -> get_size() + 10;
    int* arr1 = i1 -> get_array();
    int* arr2 = i2 -> get_array();

    int* ans = new int[cap];

    for (int i = 0; i < cap; i++) {
        ans[i] = 0;
    }
    UnlimitedInt* result = new UnlimitedInt();
    result -> capacity = cap;

    if (i1 -> get_sign() == 0 or i2 -> get_sign() == 0) {
        result -> unlimited_int = ans;
        result -> sign = 0;
        result -> size = 1;
        return result;
    }
    else {
        int i = i1 -> get_size() - 1;
        int j = i2 -> get_size() - 1;
        int k = 0;
        int carry = 0;
        int sum;
        int pos = 0;
        while (j >= 0) {
            while (i >= 0) {
                sum = arr1[i] * arr2[j] + ans[k] + carry;
                if (sum >= 10) {
                    carry = sum/10;
                    sum = sum%10;
                }
                else {
                    carry = 0;
                }
                ans[k] = sum;
                i--;
                k++;
            }
            i = i1 -> get_size() - 1;
            j--;
            ans[k] = carry;
            carry = 0;
            pos++;
            k++;
            if ( j >= 0) {
                k = pos;
            }
        }      

        if (carry == 1) {
            ans[k] = carry;
            k++;
            carry = 0;
        }

        i = 0;
        j = k-1;
        int z = k;

        while (i <= j) {
            swap(ans[i], ans[j]);
            i++;
            j--;
        }
        int w = 0;
        bool flag = false;
        for (int m = 0; m < z; m++) {
            if (ans[m] == 0 and flag == false) {
                k--;
            }
            else {
                swap(ans[w], ans[m]);
                w++;
                flag = true;
            }
        }

            result -> unlimited_int = ans;
            result -> size = k;
            if (i1 -> get_sign() == i2 -> get_sign()) {
                result -> sign = 1;
            }
            else {
                result -> sign = -1;
            }
        return result;
    } 
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (compare_magnitude(i1, i2) == "i2") {

        int cap = i1 -> get_size() + i2 -> get_size() + 10;
        int* ans = new int[cap];
        UnlimitedInt* result = new UnlimitedInt();
        ans[0] = 0;
        result -> capacity = cap;
        result -> unlimited_int = ans;
        result -> sign = 0;
        result -> size = 1;
        return result;
    }
    else {
        UnlimitedInt* one = new UnlimitedInt("1");
        UnlimitedInt* count1 = new UnlimitedInt("1");

        while (compare_magnitude(i1, mul(i2, count1)) != "i2" ) {
            count1 = add(count1, one);
        }
        count1 = sub(count1, one);
        delete one;

        if (i1 -> get_sign() == i2 -> get_sign()) {
            count1 -> sign = 1;
        }
        else {
            count1 -> sign = -1;
        }
        return count1;
    }

}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2) {
    UnlimitedInt* copy = new UnlimitedInt(i1 -> to_string());
    if (compare_magnitude(i1, i2) == "i2") {
        if (copy -> get_sign() == i2 -> get_sign()) {
            if (copy -> get_sign() == -1) {
               copy -> sign = -1; 
            }
        }
        else {
            if (copy -> get_sign() == 1) {
                copy -> sign = -1;
            }
            else if (copy -> get_sign() == -1) {
                copy -> sign = 1;
            }
        }
        return copy;
    }
    else {
        if (i1 -> get_sign() == i2 -> get_sign()) {

            UnlimitedInt* copy = new UnlimitedInt(i1 -> to_string());

            int cap = i1 -> get_size() + i2 -> get_size() + 10;

            int* arr2 = new int[cap];
            UnlimitedInt* zero = new UnlimitedInt();
            arr2[0] = 0;
            zero -> unlimited_int = arr2;
            zero -> capacity = cap;
            zero -> size = 1;
            zero -> sign = 0;

            bool flag = false;

            while (copy -> get_sign() == 1) {
                if (compare_magnitude(copy, i2) != "i2") {
                    copy = sub(copy, i2);
                    if (copy -> get_sign() == 0) {
                        flag = true;
                        delete copy;
                        return zero;
                    } 
                }
                else {
                    delete zero;
                    return copy;
                }         
            }          
        }
        else {
            int si1 = copy -> get_sign();

            copy -> sign = 1;
            i2 -> sign = 1;

            UnlimitedInt* res = mod(copy, i2);
            if (si1 == 1) {
                res -> sign = -1;
            }
            return res;
        }
    }
}


// int main() {
//     UnlimitedInt* i1 = new UnlimitedInt("-6780");
//     UnlimitedInt* i2 = new UnlimitedInt("678");

//     UnlimitedInt* i3 = UnlimitedInt::div(i1, i2);

//     int* arr = i3 -> get_array();
//     int n = i3 -> get_size();

//     for (int i = 0; i < n; i++) {
//         std::cout << arr[i];
//     }
//     std::cout << "\n";
//     std::cout << i3 -> get_sign();

// }



