/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

string Compare_magnitude(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1 -> get_size() > i2 -> get_size()) {
        return "i1";
    }
    else if (i1 -> get_size() > i2 -> get_size()) {
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

UnlimitedInt* GCD(UnlimitedInt* i1, UnlimitedInt* i2) {
    UnlimitedInt* copy1  = new UnlimitedInt(i1 -> to_string());
    UnlimitedInt* copy2  = new UnlimitedInt(i2 -> to_string());

    if (Compare_magnitude(copy1, copy2) != "i2") {
        UnlimitedInt* r = UnlimitedInt::mod(copy1, copy2);
        while (r -> get_sign() != 0) {
            copy1 = copy2;
            copy2 = r;
            r = UnlimitedInt::mod(copy1, copy2);
        }
        delete copy1;
        return copy2;
    }
    else {
        UnlimitedInt* r = UnlimitedInt::mod(copy2, copy1);
        while (r -> get_sign() != 0) {
            copy2 = copy1;
            copy1 = r;
            r = UnlimitedInt::mod(copy2, copy1);
        }
        delete copy2;
        return copy1;
    }
}

UnlimitedRational::UnlimitedRational() {
    p = new UnlimitedInt();
    q = new UnlimitedInt();
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den) {
    if (num -> get_sign() == 0) {
        if (den -> get_sign() != 0) {
            den = UnlimitedInt::div(den, den);
        }
    }
    else if (Compare_magnitude(num, den) != "i2") {
        if (UnlimitedInt::mod(num, den) -> get_sign() == 0) {
            num = UnlimitedInt::div(num, den);
            den = UnlimitedInt::div(den, den);
        }
        else {
            UnlimitedInt* cf = GCD(num, den);
            num = UnlimitedInt::div(num, cf);
            den = UnlimitedInt::div(den, cf);
        }
    }
    else {
        if (UnlimitedInt::mod(den, num) -> get_sign() == 0) {
            den = UnlimitedInt::div(den, num);
            num = UnlimitedInt::div(num, num);
        }
        else {
            UnlimitedInt* cf = GCD(den, num);
            num = UnlimitedInt::div(num, cf);
            den = UnlimitedInt::div(den, cf);            
        }
    }
    p = new UnlimitedInt();
    q = new UnlimitedInt();

    p = num;
    q = den;
}

UnlimitedRational::~UnlimitedRational() {
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p() {
    return p;
}

UnlimitedInt* UnlimitedRational::get_q() {
    return q;
}

string UnlimitedRational::get_p_str() {
    int* arr1 = p -> get_array();
    int n = p -> get_size();
    string s = "";
    if (p -> get_sign() == -1) {
        s += "-";
    }
    for (int i = 0; i < n; i++) {
        s += to_string(arr1[i]);
    }
    return s;
}

string UnlimitedRational::get_q_str() {
    int* arr1 = q -> get_array();
    int n = q -> get_size();
    string s = "";
    if (q -> get_sign() == -1) {
        s += "-";
    }
    for (int i = 0; i < n; i++) {
        s += to_string(arr1[i]);
    }
    return s;
}

string UnlimitedRational::get_frac_str() {
    string s1 = get_p_str();
    string s2 = get_q_str();

    return s1 + "/" + s2;
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* p1 = i1 -> get_p();
    UnlimitedInt* q1 = i1 -> get_q();

    UnlimitedInt* p2 = i2 -> get_p();
    UnlimitedInt* q2 = i2 -> get_q();

    UnlimitedInt* den = UnlimitedInt::mul(q1, q2);

    UnlimitedInt* t1 = UnlimitedInt::mul(p1, q2);
    UnlimitedInt* t2 = UnlimitedInt::mul(p2, q1);
    UnlimitedInt* num = UnlimitedInt::add(t1, t2);

    UnlimitedRational* res = new UnlimitedRational(num, den);
    return res;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* p1 = i1 -> get_p();
    UnlimitedInt* q1 = i1 -> get_q();

    UnlimitedInt* p2 = i2 -> get_p();
    UnlimitedInt* q2 = i2 -> get_q();

    UnlimitedInt* den = UnlimitedInt::mul(q1, q2);

    UnlimitedInt* t1 = UnlimitedInt::mul(p1, q2);
    UnlimitedInt* t2 = UnlimitedInt::mul(p2, q1);
    UnlimitedInt* num = UnlimitedInt::sub(t1, t2);

    UnlimitedRational* res = new UnlimitedRational(num, den);
    return res;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* p1 = i1 -> get_p();
    UnlimitedInt* q1 = i1 -> get_q();

    UnlimitedInt* p2 = i2 -> get_p();
    UnlimitedInt* q2 = i2 -> get_q();

    UnlimitedInt* den = UnlimitedInt::mul(q1, q2);
    UnlimitedInt* num = UnlimitedInt::mul(p1, p2);

    UnlimitedRational* res = new UnlimitedRational(num, den);
    return res;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2) {
    UnlimitedInt* p1 = i1 -> get_p();
    UnlimitedInt* q1 = i1 -> get_q();

    UnlimitedInt* p2 = i2 -> get_p();
    UnlimitedInt* q2 = i2 -> get_q();

    UnlimitedInt* den = UnlimitedInt::mul(p2, q1);
    UnlimitedInt* num = UnlimitedInt::mul(p1, q2);

    UnlimitedRational* res = new UnlimitedRational(num, den);
    return res;

}

// int main() {
//     UnlimitedInt* num = new UnlimitedInt("84");
//     UnlimitedInt* den = new UnlimitedInt("676746");
//     UnlimitedInt* num1 = new UnlimitedInt("2322");
//     UnlimitedInt* den1 = new UnlimitedInt("3");
//     UnlimitedRational* i = new UnlimitedRational(num, den);
//     UnlimitedRational* i1 = new UnlimitedRational(num1, den1);
//     UnlimitedRational* i2 = UnlimitedRational::mul(i1, i);
//     std::cout << i2 -> get_frac_str() << "\n";

//     delete num, den, num1, den1, i, i1, i2;
// }