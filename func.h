#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

constexpr auto IndexOutOfRangeEx = "Index out of range";

template <class T>
class DynamicArray {
private:
    T* items;
    int size;
public:
    DynamicArray() {
        this->size = 0;
        this->items = nullptr;
    }

    DynamicArray(T* items, int size) {
        this->items = items;
        this->items = new T[size];
        this->size = size;
        for (int i = 0; i < this->size; i++) {
            this->items[i] = items[i];
        }
    }

    DynamicArray(int size) {
        this->items = new T[size];
        this->size = size;
    }

    DynamicArray(const DynamicArray <T>& dynamicArray) {
        this->size = dynamicArray.size;
        this->items = new T[this->size];
        for (int i = 0; i < dynamicArray.size; i++) {
            this->items[i] = dynamicArray.items[i];
        }
    }

    ~DynamicArray() {
        this->size = 0;
        delete[] this->items;
    }

    T Get(int index) {
        if (index < 0 || index >= this->size) throw out_of_range(IndexOutOfRangeEx);
        return this->items[index];
    }

    int GetSize() {
        return this->size;
    }

    void Set(int index, T value) {
        if (index < 0 || index >= this->size) throw out_of_range(IndexOutOfRangeEx);
        this->items[index] = value;
    }

    void Resize(int newSize) {
        T* items_tmp = new T[newSize];
        if (newSize > this->size) {
            for (int i = 0; i < this->size; i++) {
                items_tmp[i] = this->items[i];
            }
            this->size = newSize;
        }
        else {
            for (int i = 0; i < newSize; i++) {
                items_tmp[i] = this->items[i];
            }
            this->size = newSize;
        }
        delete[] this->items;
        this->items = items_tmp;
    }

    void delete_i(int index) {
        if (index < 0 || index >= this->size) throw out_of_range(IndexOutOfRangeEx);
        const int NewSize = this->size - 1;
        T* tmp = new T[NewSize];
        for (int i = 0; i < NewSize; i++) {
            if (i < index) {
                tmp[i] = this->items[i];
            }
            else {
                tmp[i] = this->items[i + 1];
            }
        }
        this->size--;
        delete[] this->items;
        this->items = tmp;
    }

    void print_array() {
        for (int i = 0; i < this->size; i++) {
            cout << this->items[i] << "  ";
        }
        cout << endl;
    }
};

template <class T>
class LinkedList {
private:
    int size;
    struct node {
        T items;
        node* next;
    };
    node* head = new node;
public:
    LinkedList(T* items, int count) {
        this->size = count;
        node* cur = head;
        for (int i = 0; i < this->size; i++) {
            cur->items = items[i];
            node* tmp = new node;
            cur->next = tmp;
            cur = cur->next;
        }
    }

    LinkedList() {
        node* cur = new node;
        this->head = new node;
        this->head->next = cur;
        this->size = 0;
    }

    LinkedList(const LinkedList <T>& linkedlist) {
        this->size = linkedlist.size;
        node* cur1 = this->head;
        node* cur2 = linkedlist.head;
        for (int i = 0; i < this->size; i++) {
            cur1->items = cur2->items;
            node* tmp = new node;
            cur1->next = tmp;
            cur1 = tmp;
            cur2 = cur2->next;
        }
    }

    ~LinkedList() {
        for (int i = 0; i < this->size; i++) {
            node* cur = this->head->next;
            delete this->head;
            this->head = cur;
        }
        this->size = 0;
    }

    void print_list() {
        node* cur = head;
        for (int i = 0; i < this->size; i++) {
            cout << cur->items << "  ";
            cur = cur->next;
        }
        cout << endl;
    }

    T GetFirst() {
        if (this->size <= 0) throw out_of_range(IndexOutOfRangeEx);
        return this->head->items;
    }

    T GetLast() { 
        if (this->size <= 0) throw out_of_range(IndexOutOfRangeEx);
        node* cur = new node;
        cur = this->head;
        if (this->size == 1)
            return this->head->items;
        else {
            for (int i = 0; i < this->size - 1; i++) {
                cur = cur->next;
            }
            return cur->items;
        }
    }

    void delete_i(int index) {
        if (this->size <= 0) throw out_of_range(IndexOutOfRangeEx);

        if (index == 0) {
            node* tmp = new node;
            tmp = this->head;
            this->head = this->head->next;
            delete tmp;
        }

        else if (index == this->size - 1) {
            node* tmp = new node;
            tmp = this->head;
            for (int i = 0; i < this->size - 1; i++) {
                tmp = tmp->next;
            }
            delete tmp;
        }
        else {
            node* tmp = new node;
            tmp = this->head;
            for (int i = 0; i < index - 1; i++) {
                tmp = tmp->next;
            }
            node* cur = new node;
            cur = tmp;
            tmp = tmp->next;
            cur->next = tmp->next;
            delete tmp;
        }
        this->size--;

    }

    T Get(int index) {
        if (index < 0 || index >= this->size) throw out_of_range(IndexOutOfRangeEx);
        if (index == 0)
            return head->items;
        else {
            node* cur = new node;
            cur = this->head;
            for (int i = 0; i < index; i++)
                cur = cur->next;
            return cur->items;
        }
    }

    LinkedList <T>* GetSubList(int startindex, int endindex) {
        if (startindex < 0 || endindex < startindex) throw out_of_range(IndexOutOfRangeEx);
        LinkedList <T>* newLIST = new LinkedList <T>;
        newLIST->size = endindex - startindex;
        node* cur1 = new node;
        cur1 = this->head;
        node* cur2 = new node;
        cur2 = newLIST->head;
        for (int i = 0; i < endindex; i++) {
            if (i >= startindex) {
                cur2->items = cur1->items;
                node* tmp = new node;
                cur2->next = tmp;
                cur2 = tmp;
            }
            cur1 = cur1->next;
        }
        return newLIST;
    }

    int GetLength() {
        return size;
    }

    void Prepend(T item) {
        node* new_elem = new node;
        if (this->size == 0) {
            this->head->items = item;
            this->head->next = new_elem;
        }
        else {
            new_elem->next = head;
            head = new_elem;
            new_elem->items = item;
        }
        this->size++;
    }

    void Append(T item) {
        node* new_elem = new node;
        if (this->size == 0) {
            this->head->items = item;
            this->head->next = new_elem;
            this->size++;
        }
        else {
            new_elem = this->head;
            for (int i = 0; i < this->size; i++) {
                new_elem = new_elem->next;
            }
            new_elem->items = item;
            node* new_next = new node;
            new_elem->next = new_next;
            this->size++;
        }
    }

    void InsertAt(T item, int index) {
        if (index < 0 || index > this->size) throw out_of_range(IndexOutOfRangeEx);
        node* new_elem = new node;
        if (index == 0) {
            new_elem->next = head;
            head = new_elem;
        }
        else {
            node* cur = new node;
            cur = head;
            for (int i = 0; i < index - 1; i++) {
                cur = cur->next;
            }
            new_elem->next = cur->next;
            cur->next = new_elem;
        }
        new_elem->items = item;
        this->size++;
    }

    LinkedList <T>* Concat(LinkedList<T>* list) {
        LinkedList <T>* newLIST = new LinkedList<T>;
        newLIST->size = this->size + list->size;
        node* cur1 = newLIST->head;
        node* cur2 = this->head;
        if (this->size == 0)
            return list;
        else if (list->size == 0)
            return this;
        else {
            for (int i = 0; i < this->size; i++) {
                cur1->items = cur2->items;
                node* tmp = new node;
                cur1->next = tmp;
                cur1 = tmp;
                cur2 = cur2->next;
            }
            cur2 = list->head;
            for (int i = 0; i < list->size; i++) {
                cur1->items = cur2->items;
                node* tmp = new node;
                cur1->next = tmp;
                cur1 = tmp;
                cur2 = cur2->next;
            }
            return newLIST;
        }
    }
};

template <class T>
class Sequence {
public:
    Sequence() {}
    virtual ~Sequence() {}
    virtual T GetFirst() = 0;
    virtual T GetLast() = 0;
    virtual T Get(int index) = 0;
    virtual Sequence <T>* GetSubSequence(int startindex, int endindex) = 0;
    virtual int GetLength() = 0;
    virtual void delete_i(int index) = 0;

    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;
    virtual Sequence <T>* Concat(Sequence<T>* seq) = 0;
    virtual void print() = 0;
};

template <class T>
class ArraySequence : public Sequence <T> {
private:
    DynamicArray <T>* MyArray;
public:
    ArraySequence() {
        this->MyArray = new DynamicArray<T>();
    }

    ArraySequence(T* items, int size) {
        this->MyArray = new DynamicArray<T>(items, size);
    }

    ArraySequence(int size) {
        this->MyArray = new DynamicArray<T>(size);
    }

    ArraySequence(Sequence <T>* seq) {
        this->MyArray = new DynamicArray<T>(seq->GetLength());
        for (int i = 0; i < this->MyArray->GetSize(); i++) {
            this->MyArray->Set(i, seq->Get(i));
        }
    }

    virtual ~ArraySequence() {
        delete this->MyArray;
        this->MyArray = nullptr;
    }

    T GetFirst() override {
        return this->MyArray->Get(0);
    }

    T GetLast() override {
        return this->MyArray->Get(this->MyArray->GetSize() - 1);
    }

    T Get(int index) override {
        return this->MyArray->Get(index);
    }

    ArraySequence<T>* GetSubSequence(int startindex, int endindex) override {
        int SubSize = endindex - startindex;
        ArraySequence <T>* SubArray = new ArraySequence <T>(SubSize);
        for (int i = 0; i < SubSize; i++) {
            SubArray->MyArray->Set(i, this->MyArray->Get(i + startindex));
        }
        return SubArray;
    }

    void delete_i(int index) override {
        this->MyArray->delete_i(index);
    }

    int GetLength() override {
        return this->MyArray->GetSize();
    }

    void Set(int index, T item) {
        this->MyArray->Set(index, item);
    }

    void Append(T item) override {
        this->MyArray->Resize(this->MyArray->GetSize() + 1);
        this->MyArray->Set(this->MyArray->GetSize() - 1, item);
    }

    void Prepend(T item) override {
        this->MyArray->Resize(this->MyArray->GetSize() + 1);
        for (int i = this->MyArray->GetSize() - 1; i > 0; i--) {
            this->MyArray->Set(i, this->MyArray->Get(i - 1));
        }
        this->MyArray->Set(0, item);
    }

    void InsertAt(T item, int index) override {
        this->MyArray->Resize(this->MyArray->GetSize() + 1);
        for (int i = this->MyArray->GetSize() - 1; i > index; i--) {
            this->MyArray->Set(i, this->MyArray->Get(i - 1));
        }
        this->MyArray->Set(index, item);
    }

    ArraySequence <T>* Concat(Sequence <T>* seq) override {
        ArraySequence <T>* newconc = new ArraySequence<T>(this->MyArray->GetSize() + seq->GetLength());
        for (int i = 0; i < this->MyArray->GetSize(); i++) {
            newconc->Set(i, this->MyArray->Get(i));
        }
        for (int i = this->MyArray->GetSize(); i < seq->GetLength() + this->MyArray->GetSize(); i++) {
            newconc->Set(i, seq->Get(i - this->MyArray->GetSize()));
        }
        return newconc;
    }

    void print() override {
        this->MyArray->print_array();
    }
};

template <class T>
class ListSequence : public Sequence <T> {
private:
    LinkedList <T>* list;
public:
    ListSequence(T* items, int size) {
        this->list = new LinkedList<T>(items, size);
    }

    ListSequence() {
        this->list = new LinkedList<T>();
    }

    ListSequence(Sequence<T>* seq) {
        this->list = new LinkedList<T>();
        for (int i = 0; i < seq->GetLength(); i++)
            this->list->InsertAt(seq->Get(i), i);
    }

    virtual ~ListSequence() {
        delete this->list;
        this->list = nullptr;
    }

    T GetFirst() override {
        return this->list->GetFirst();
    }

    T GetLast() override {
        return this->list->GetLast();
    }

    T Get(int index) override {
        return this->list->Get(index);
    }

    void InsertAt(T item, int index) override {
        this->list->InsertAt(item, index);
    }

    ListSequence <T>* GetSubSequence(int startindex, int endindex) override {
        ListSequence <T>* Sublist = new ListSequence<T>();
        for (int i = startindex; i < endindex; i++) {
            Sublist->InsertAt(this->list->Get(i), i - startindex);
        }
        return Sublist;
    }

    int GetLength() override {
        return this->list->GetLength();
    }

    void Append(T item) override {
        this->list->Append(item);
    }

    void delete_i(int index) override {
        this->list->delete_i(index);
    }

    void Prepend(T item) override {
        this->list->Prepend(item);
    }

    ListSequence<T>* Concat(Sequence<T>* seq) override {
        ListSequence<T>* Conclist = new ListSequence<T>();
        for (int i = 0; i < this->list->GetLength(); i++) {
            Conclist->InsertAt(this->list->Get(i), i);
        }
        for (int i = 0; i < seq->GetLength(); i++) {
            Conclist->InsertAt(seq->Get(i), i);
        }
        return Conclist;
    }

    void print() override {
        this->list->print_list();
    }
};

template <class T>
class Stack {
private:
    Sequence<T>* seq;
public:
    Stack() {
        this->seq = new ArraySequence<T>();
    }

    Stack(int size) {
        this->seq = new ArraySequence <T>(size);
    }

    Stack(const T* items, int size) {
        this->seq = new ArraySequence<T>();
        for (int i = 0; i < size; i++) {
            this->seq->InsertAt(items[i], i);
        }
    }

    Stack(Sequence<T>* cur_seq) {
        this->seq = new ArraySequence<T>();
        for (int i = 0; i < this->seq->GetLength(); i++) {
            this->seq->InsertAt(cur_seq->Get(i), i);
        }
    }

    ~Stack() = default;

    T peek() { // посмотреть верхний элемент - глянуть карту с колоды
        return this->seq->Get(0);
    }


    T pop() { //достать первый и удалить его - взял карту
        if (this->seq->GetLength() <= 0) throw out_of_range(IndexOutOfRangeEx);
        T tmp_item = this->seq->GetFirst();
        this->seq->delete_i(0);
        return tmp_item;
    }

    int GetSize() {
        return this->seq->GetLength();
    }

    void push(T item) { // положить карту в колоду
        this->seq->Prepend(item);
    }
    void print() {
        this->seq->print();
    }

    void set(int index, T cur) {
        this->seq->InsertAt(cur, index);
    }

    Stack<T> map(T func(T cur)) {
        if (this->seq->GetLength() <= 0) throw out_of_range(IndexOutOfRangeEx);

        Stack<T> new_stack;
        if (this->seq->GetLength() == 1) {
            new_stack.push( func(this->seq->Get(0)) );
        }
        else {
            for (int i = 0; i < this->seq->GetLength(); i++) {
                new_stack.set(i, func(this->seq->Get(i)));
            }
        }
        return new_stack;
    }

    Stack <T> where(bool func(T cur)) {
        if (this->seq->GetLength() <= 0) throw out_of_range(IndexOutOfRangeEx);
        Stack<T> new_stack;
        for (int i = 0,j = 0; i < this->seq->GetLength(); i++) {
            if (func(this->seq->Get(i))) {
                new_stack.set(j, this->seq->Get(i));
                j++;
            }
        }
        return new_stack;
    }

    T reduce(T func(T first, T second), T const_data) {
        if (this->seq->GetLength() == 0)
            return 0; 
        T cur = func(this->seq->Get(0), const_data);
        for (int i = 1; i < this->seq->GetLength(); i++) {
            cur = func(this->seq->Get(i), cur);
        }
        return cur;

    }

    T Get(int index) {
        if (this->seq->GetLength() <= index || index < 0) throw out_of_range(IndexOutOfRangeEx);
        return this->seq->Get(index);
    }

    Stack <T> Concat(const Stack<T>* st) {
        Stack<T> concated;
        concated.seq = this->seq->Concat(st->seq);
        return concated;
    }

    Stack <T> SubStack(const int start,const int end) {
        Stack<T> SubStack;
        SubStack.seq = this->seq->GetSubSequence(start, end);
        return SubStack;
    }

    bool search(Stack<T> st) {
        if (st.GetSize() == 0)
            return 1;
        if (this->seq->GetLength() == 0)
            return 0;
        for (int i = 0; i < this->seq->GetLength(); i++) {
            if (st.Get(0) == this->seq->Get(i)) {
                int count = 0;
                for (int j = 0; j < st.GetSize(); j++) {
                    if (st.Get(j) == this->seq->Get(j + i)) {
                        count++;
                    }
                }
                if (count == st.GetSize())
                    return 1;
                count = 0;
            }
        }
        return 0;
    }

};

