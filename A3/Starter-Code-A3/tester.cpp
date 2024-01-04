#include <bits/stdc++.h>
#include "BaseClass.h"
#include "Chaining.h"
#include "Chaining.cpp"
#include "LinearProbing.h"
#include "LinearProbing.cpp"
#include "QuadraticProbing.h"
#include "QuadraticProbing.cpp"
#include "CubicProbing.h"
#include "CubicProbing.cpp"
#include "Comp.h"
#include "Comp.cpp"

using namespace std;
BaseClass *Bank;
void test()
{
    ifstream fin("test1.txt");
    int command;
    string accName;
    int accBalance, accBalance2, transactionAmount;
    int kValue, rKValue;
    vector<int> TopKBalances;
    string s1, s2;
    int deletionResult1, deletionResult2, accExists;

    int casesTested = 0;
    while (fin >> command)
    {
        switch (command)
        {
        case 1:
            fin >> accName >> accBalance;
            Bank->createAccount(accName, accBalance);
            fin >> accBalance2;
            if (Bank->getBalance(accName) != accBalance)
            {
                cout << "FAILED on creating account " << accName << " with balance " << accBalance << endl;
                cout << "On retreving balance on " << accName << " expected " << accBalance2 << " but found " << Bank->getBalance(accName) << endl;
                throw std::runtime_error("");
            }
            casesTested++;
            break;
        case 2:
            fin >> accName >> transactionAmount;
            Bank->addTransaction(accName, transactionAmount);
            fin >> accBalance2;
            if (Bank->getBalance(accName) != accBalance2)
            {
                cout << "FAILED on adding transaction to " << accName << " an amount " << transactionAmount << endl;
                cout << "Final balance on " << accName << " expected " << accBalance2 << " but found " << Bank->getBalance(accName) << endl;
                throw std::runtime_error("");
            }
            casesTested++;
            break;
        case 4:
            fin >> kValue;
            fin >> rKValue;
            TopKBalances = Bank->getTopK(kValue);
            if (rKValue != TopKBalances.size())
            {
                cout << "FAILED on geiing top K balances" << endl;
                cout << "Expected length of vector " << rKValue << " but found " << TopKBalances.size() << endl;
                throw std::runtime_error("");
            }
            else
            {
                sort(TopKBalances.rbegin(), TopKBalances.rend());
                s1 = "";
                s2 = "";
                for (int i = 0; i < rKValue; i++)
                {
                    s1 += to_string(TopKBalances[i]) + " ";
                    fin >> accBalance;
                    s2 += to_string(accBalance) + " ";
                }
                if (s1 != s2)
                {
                    cout << "FAILED on getting top K balances" << endl;
                    cout << "Expected top K balances " << s2 << endl;
                    cout << "Found " << s1 << endl;
                    throw std::runtime_error("");
                }
            }
            casesTested++;
            break;
        case 5:
            fin >> accName;
            fin >> accBalance;
            if (accBalance != Bank->getBalance(accName))
            {
                cout << "FAILED to get acc balance of acc " << accName << endl;
                cout << "Expected balance " << accBalance << " but found " << Bank->getBalance(accName) << endl;
                throw std::runtime_error("");
            }
            casesTested++;
            break;
        case 6:
            fin >> accName;
            fin >> deletionResult1;
            deletionResult2 = Bank->deleteAccount(accName);
            if (deletionResult1 && !deletionResult2 || !deletionResult1 && deletionResult2)
            {
                cout << "FAILED in deletion of account " << accName << endl;
                cout << "Expected " << deletionResult1 << " but found " << deletionResult2 << endl;
                cout << "1 is true and 0 is false" << endl;
                throw std::runtime_error("");
            }
            casesTested++;
            break;
        case 8:
            fin >> accName;
            fin >> accBalance;
            accExists = Bank->doesExist(accName);
            if (accBalance && !accExists || !accBalance && accExists)
            {
                cout << "FAILED in doesExist " << accName << endl;
                cout << "Expected " << accBalance << " but found " << accExists << endl;
                cout << "1 is true and 0 is false" << endl;
                throw std::runtime_error("");
            }
            casesTested++;
            break;
        case 9:
            fin >> accBalance;
            if (Bank->databaseSize() != accBalance)
            {
                cout << "FAILED total database size" << endl;
                cout << "Expected " << accBalance << " but found " << Bank->databaseSize() << endl;
                throw std::runtime_error("");
            }
            casesTested++;
            break;
        }
        if (casesTested % 10000 == 0)
        {
            cout << casesTested << " OK" << endl;
        }
    }
    cout << "CasesTested " << casesTested << endl;
}

using namespace std::chrono;

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cout << "How many commands do you want to test with?: ";
    cout.flush();
    int commandCount;
    cin >> commandCount;
    string commandToGeneratedTestCase = "python3 generateTests.py " + to_string(commandCount) + " > test1.txt";
    system(&commandToGeneratedTestCase[0]);
    cout << "What part of your code do you want to test?\n1->chaining\n2->linearProbing\n4->quadraticProbing\n8->cubicProbing\n16->compPart\n";
    cout << "Enter the number as the sum of parts you want to test (e.g., 31 to test all): ";
    cout.flush();
    int toTest;
    cin >> toTest;
    cout << endl;
    cout << "CasesTested may not match the number of commands asked; it's just to know that actually some testing happened. If it's very small like 0, then something went wrong" << endl;
    cout << endl;
    cout << "If the program is not ending, it means your code might be stuck in an infinite loop" << endl;
    cout << endl;

    // Measure the runtime for each type of probing
    if (toTest & 1)
    {
        cout << "STARTING WITH CHAINING" << endl;
        Bank = new Chaining;
        auto start = high_resolution_clock::now();
        test();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken for CHAINING: " << duration.count() << " microseconds" << endl;
        cout << "DONE WITH CHAINING" << endl;
        delete Bank;
    }
    if (toTest & 2)
    {
        cout << "STARTING WITH LinearProbing" << endl;
        Bank = new LinearProbing;
        auto start = high_resolution_clock::now();
        test();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken for LinearProbing: " << duration.count() << " microseconds" << endl;
        cout << "DONE WITH LinearProbing" << endl;
        delete Bank;
    }
    if (toTest & 4)
    {
        cout << "STARTING WITH QuadraticProbing" << endl;
        Bank = new QuadraticProbing;
        auto start = high_resolution_clock::now();
        test();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken for QuadraticProbing: " << duration.count() << " microseconds" << endl;
        cout << "DONE WITH QuadraticProbing" << endl;
        delete Bank;
    }
    if (toTest & 8)
    {
        cout << "STARTING WITH CubicProbing" << endl;
        Bank = new CubicProbing;
        auto start = high_resolution_clock::now();
        test();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken for CubicProbing: " << duration.count() << " microseconds" << endl;
        cout << "DONE WITH CubicProbing" << endl;
        delete Bank;
    }
    if (toTest & 16)
    {
        cout << "STARTING WITH Comp" << endl;
        Bank = new Comp;
        auto start = high_resolution_clock::now();
        test();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        cout << "Time taken for Comp: " << duration.count() << " microseconds" << endl;
        cout << "DONE WITH Comp" << endl;
        delete Bank;
    }

    cout << "Do you want to clean up the test cases file generated? (y/n):" << endl;
    cout.flush();
    string r;
    cin >> r;
    if (r == "Y" || r == "y")
        system("rm test1.txt");

    cout << "DONE" << endl;

    return 0;
}