namespace LinearList {
int test();
class LinearList {
private:
    int* table;
    int capacity;
    int actualLen;
public:
    //at least 1 here
    LinearList(int n=1);
    //[EFFC++]
    LinearList(const LinearList&);
    ~LinearList();
        //[EFFC++]
    const LinearList& operator=(const LinearList&);
    //
    //
    bool isEmpty() const;
    bool isFull() const;
    int length() const;
    int get(int i) const;
    bool set(int i,int k);
    bool insert(int i,int k);
    bool insert(int k);
    int search(int k);
    bool remove(int k);

    void output();
    static LinearList* create(int n);
};

}
