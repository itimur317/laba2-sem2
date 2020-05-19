#include "func.h"
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

string func_map(string cur) {
    return cur + cur;
}

string func_reduce(string cur1, string cur2) {
    return cur1 + cur2 + cur2;
}

bool func_where(string cur) {
    if (cur == "a" || cur == "b")
        return 1;
    return 0;
}

void interface() {
    cout << "STACK" << endl;
    cout << "Welcome to card game MEPHI!" << endl;
    cout << "how many cards you want put to deck?" << endl;
    int size;
    cin >> size;
    string* str = new string[size];
    Stack <string> stack_str;
    for (int i = 0; i < size; i++) {
        cout << "enter " << i;
        if (i == 1)
            cout << "st";
        else if (i == 2)
            cout << "nd";
        else if (i == 3)
            cout << "rd";
        else
            cout << "th";
        cout << " card name" << endl;
        string cin_str;
        cin >> cin_str;
        stack_str.push(cin_str);
        cout << "your card put into deck" << endl << endl;
    }
    int check = 1;
    while (check) {
        cout << "1. to check deck`s size" << endl;
        cout << "2. to check upper card" << endl;
        cout << "3. to take upper card" << endl;
        cout << "4. to put card into deck" << endl;
        cout << "5. to concatenate second deck" << endl;
        cout << "6. to take small deck from main deck" << endl;
        cout << "7. to find out about including small deck" << endl;
        cout << "8. to learn all deck" << endl;
        cout << "0. to exit card game MEPHI" << endl;
        cin >> check;
        switch (check) {
        case 1: {
            if (stack_str.GetSize() == 1)
                cout << stack_str.GetSize() << " card1" << endl;
            else
                cout << stack_str.GetSize() << " cards" << endl;
        }
              break;

        case 2: {
            cout << "the upper card is - " << stack_str.peek() << endl;
        }
              break;

        case 3: {
            cout << "you took " << stack_str.peek() << " from the deck" << endl;
            stack_str.pop();
        }
              break;
        case 4: {
            string tmp;
            cout << "enter name of card: ";
            cin >> tmp;
            stack_str.push(tmp);
            cout << "you put card" << endl;
        }
              break;
        case 5: {
            Stack<string> tmp;
            cout << "to create second deck enter size: ";
            int size_deck;
            cin >> size_deck;
            for (int i = 0; i < size_deck; i++) {
                string cur;
                cout << "enter " << i;
                if (i == 1)
                    cout << "st";
                else if (i == 2)
                    cout << "nd";
                else if (i == 3)
                    cout << "rd";
                else
                    cout << "th";
                cout << " card" << endl;
                cin >> cur;
                tmp.push(cur);

            }
            cout << "you got new deck:" << endl;
            stack_str.Concat(&tmp).print();
        }
              break;
        case 6: {
            cout << "enter the start number: ";
            int first, second;
            cin >> first;
            cout << endl << "enter the end number: ";
            cin >> second;
            if (first >= second || first < 0 || second + 1 > stack_str.GetSize()) throw out_of_range(IndexOutOfRangeEx);
            cout << endl;
            stack_str.SubStack(first, second).print();
        }
              break;
        case 7: {
            Stack<string> tmp;
            cout << "to create second deck enter size: ";
            int size_deck;
            cin >> size_deck;
            if (size_deck > stack_str.GetSize()) throw out_of_range(IndexOutOfRangeEx);
            for (int i = 0; i < size_deck; i++) {
                string cur;
                cout << "enter " << i;
                if (i == 1)
                    cout << "st";
                else if (i == 2)
                    cout << "nd";
                else if (i == 3)
                    cout << "rd";
                else
                    cout << "th";
                cout << " card" << endl;
                cin >> cur;
                tmp.push(cur);
            }
            if (stack_str.search(tmp))
                cout << "deck found!" << endl;
            else
                cout << "we coulnd`t find deck" << endl;
        }
              break;
        case 8: {
            stack_str.print();
        }
              break;
        case 0: {
            cout << "are you sure?" << endl;
            cout << "press 0 to quit -- press 1 to cancel" << endl;
            int sure;
            cin >> sure;
            if (sure != 0 && sure != 1) throw out_of_range(IndexOutOfRangeEx);
            if (sure == 1)
                check = 1;
            else if (sure == 0) {
                check = 0;
                cout << "We're so excited about your comeback!" << endl;
            }
        }
        }
    }
}

void test_string() {
    string* source_string = new string[3];
    source_string[0] = "a";
    source_string[1] = "b";
    source_string[2] = "c";
    Stack<string> cur(source_string,3);
    // test peek
    if (cur.peek() != "a")
        cout << "peek test failed" << endl;
    else
        cout << "peek test done" << endl;
    // test push
    cur.push("k");
    if (cur.peek() == "k")
        cout << "push test done" << endl;
    else
        cout << "push test failed" << endl;
    //test pop 
    cur.pop();
    if (cur.peek() == "a")
        cout << "test pop done";
    else 
        cout << "test pop failed";
    cout << endl;
    //test map
    Stack<string> mapped_cur = cur.map(func_map);
    if (mapped_cur.Get(0) == "aa" && mapped_cur.Get(1) == "bb" && mapped_cur.Get(2) == "cc")
        cout << "test map done";
    else
        cout << "test map failed";
    cout << endl;
    // test reduce
    if ("cbakkakkbakkakk" == cur.reduce(func_reduce, "k"))
        cout << "test reduce done";
    else
        cout << "test reduce failed";
    cout << endl;
    // test where
    if (cur.where(func_where).Get(0) == "a" && cur.where(func_where).Get(1) == "b")
        cout << "test where done";
    else
        cout << "test where failed";
    cout << endl;
    // test izvlechenie
    if (cur.SubStack(0, 2).Get(0) == "a" && cur.SubStack(0, 2).Get(1) == "b")
        cout << "test izvlechenie done";
    else
        cout << "test izvlechenie failed";
    cout << endl;
    // test search
    string* search_tmp = new string[2];
    search_tmp[0] = "a";
    search_tmp[1] = "b";
    Stack<string> search_string(search_tmp, 2);
    if (cur.search(search_string))
        cout << "search test done";
    else
        cout << "search test failed";
    cout << endl;
    // test getsize
    if (cur.GetSize() == 3)
        cout << "GetSize test done";
    else
        cout << "GetSize test failed";
    cout << endl;
    // test concat
    if (cur.Concat(&search_string).Get(0) == "a" &&
        cur.Concat(&search_string).Get(1) == "b" &&
        cur.Concat(&search_string).Get(2) == "c" &&
        cur.Concat(&search_string).Get(3) == "a" &&
        cur.Concat(&search_string).Get(4) == "b")
        cout << "test concat done";
    else cout << "test concat failed";
    cout << endl;
}

int inc0(int cur) {
    return cur;
}
int inc1(int cur) {
    return cur + 1;
}
int inc2(int cur) {
    return cur + 2;
}
int inc3(int cur) {
    return cur + 3;
}

int map_funcs(int cur) {
    return cur * cur;
}

int reduce_funcs(int cur1, int cur2) {
    return cur1 * cur2 + cur1;
}

bool where_funcs(int cur) {
    if (cur >= 1)
        return 1;
    return 0;
}

void test_functions() {
    const int leng = 4;
    int (*funcs[leng])(int);
    funcs[0] = &inc0;
    funcs[1] = &inc1;
    funcs[2] = &inc2;
    funcs[3] = &inc3;

    Stack <int> cur;
    cur.push(funcs[3](0));
    cur.push(funcs[2](0));
    cur.push(funcs[1](0));
    cur.push(funcs[0](0));

    //test peek
    if (cur.peek() == 0)
        cout << "test peek done";
    else
        cout << "test peek failed";
    cout << endl;
    // test push
    cur.push(7);
    if (cur.peek() == 7)
        cout << "test push done";
    else
        cout << "test push failed";
    cout << endl;
    // test pop
    cur.pop();
    if (cur.peek() == 0)
        cout << "test pop done";
    else
        cout << "test pop failed";
    cout << endl;
    // test map
    if (cur.map(map_funcs).Get(0) == 0 &&
        cur.map(map_funcs).Get(1) == 1 &&
        cur.map(map_funcs).Get(2) == 4 &&
        cur.map(map_funcs).Get(3) == 9)

        cout << "test map done";
    else
        cout << "test map failed";
    cout << endl;
    // test reduce
    if (cur.reduce(reduce_funcs, 8) == 15)
        cout << "test reduce done";
    else
        cout << "test reduce failed";
    cout << endl;
    // test where
    if (cur.where(where_funcs).Get(0) == 1 &&
        cur.where(where_funcs).Get(1) == 2)
        cout << "test where done";
    else
        cout << "test where failed";
    cout << endl;
    // test izvlechenie
    if (cur.SubStack(0, 1).Get(0) == 0)
        cout << "test izvlechenie done";
    else
        cout << "test izvlechenie failed";
    cout << endl;
    // test search
    Stack<int> tmp_search;
    tmp_search.push(2);
    tmp_search.push(1);
    tmp_search.push(0); // 0 1 2
    if (cur.search(tmp_search))
        cout << "test search done";
    else
        cout << "test search failed";
    cout << endl;
    //test getsize
    if (cur.GetSize() == 4)
        cout << "GetSize test done";
    else
        cout << "GetSize test failed";
    cout << endl;
    //test concat
    if (cur.Concat(&tmp_search).Get(0) == 0 &&
        cur.Concat(&tmp_search).Get(1) == 1 &&
        cur.Concat(&tmp_search).Get(2) == 2 &&
        cur.Concat(&tmp_search).Get(3) == 3 &&
        cur.Concat(&tmp_search).Get(4) == 0 &&
        cur.Concat(&tmp_search).Get(5) == 1 &&
        cur.Concat(&tmp_search).Get(6) == 2)
        cout << "test concat done";
    else
        cout << "test concat failed";
    cout << endl;
}

int main() {
    int indik = 1;
    while (indik) {
        cout << "to test press 1" << endl;
        cout << "to use interface press 2" << endl;
        cout << "to exit press 0" << endl;
        cin >> indik;
        if (indik == 1) {
            int indik_test;
            cout << "to test string press 1" << endl;
            cout << "to test functions press 0" << endl;
            cin >> indik_test;
            if (indik_test == 1) {
                test_functions();
                cout << endl;
            }
            else if (indik_test == 0) {
                test_functions();
                cout << endl;
            }
        }
        else if (indik == 2) {
            interface();
        }
        else if (indik == 0) {
            continue;
        }
        else {
            cout << "enter 0 or 1 or 2!";
            indik = 0;
        }
    }

    
	return 0;
}