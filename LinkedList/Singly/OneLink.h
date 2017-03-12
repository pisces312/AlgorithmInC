#include"OneLinkNode.h"
class OneLink {
public:
    OneLinkNode *head;
    OneLink(int n);
    OneLink();
    ~OneLink();
    bool isEmpty() const {
        return head==NULL;
    }
    bool isFull() const {
        return false;
    }
    int length() const;
    OneLinkNode* index(int i) const;
    OneLinkDataType get(int i) const;
    bool set(int i,OneLinkDataType n);
    OneLinkNode* insert(OneLinkNode* p,OneLinkDataType n);
    bool remove(OneLinkNode* p);
    void output(OneLinkNode* p) const;
    void output()const;
};
