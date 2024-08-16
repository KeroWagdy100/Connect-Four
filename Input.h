#pragma once
#include <iostream>
using namespace std;

namespace Input {
    void intInput(int& var, int def_val = 0, int n_trials = 3, int min_val = 0, int max_val = INT_MAX);
    void boolInput(bool& var, bool def_val = false, int n_trials = 3);
    void stringInput(string& var, string def_val = "", int n_trials = 3);
    void charInput(char& var, char def_val = 'y', int n_trials = 3, char min_val = char(32), char max_val = char(127));

};

void Input::intInput(int& var, int def_val, int n_trials, int min_val, int max_val) {
    for (int i = 0; i < n_trials; i++) {
        cin >> var;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input | Please Enter a NUMBER\n";
        } else if (var > max_val || var < min_val) {
            cout << "Invalid Input | Please Enter a NUMBER between [" << min_val << ", " << max_val << "]\n";
        }  else {
            break;
        }
        if (i == n_trials - 1)
            var = def_val;
    }
}

void Input::boolInput(bool& var, bool def_val, int n_trials){
    for (int i = 0; i < n_trials; i++) {
        cin >> var;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input | Please Enter a BOOLEAN (1 or 0)\n";
        }
        if (i == n_trials - 1)
            var = def_val;
    }
}

void Input::charInput(char& var, char def_val, int n_trials, char min_val, char max_val) {
    for (int i = 0; i < n_trials; i++) {
        cin >> var;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid Input | Please Enter a CHARACTER\n";
        } else if (var > max_val || var < min_val) {
            cout << "Invalid Input | Please Enter a CHARACTER between [" << min_val << ", " << max_val << "]\n";
        }  else {
            break;
        }
        if (i == n_trials - 1)
            var = def_val;
    }
}

void Input::stringInput(string& var, string def_val, int n_trials) {
    for (int i = 0; i < n_trials; i++) {
        cin >> var;
        if (var.empty()) {
            cout << "Invalid Input | Please Enter a non-empty string\n";
        }
        else {
            break;
        }
        if (i == n_trials - 1)
            var = def_val;
    }
}