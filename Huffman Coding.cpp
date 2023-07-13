#include <iostream>
#include <queue>
#include <string>
#include <map>
#include <iterator>
using namespace std;

map<char, int> freq;
map<char, string> patt;

struct node {
    char data;
    int freq;
    node* left, * right;
    node(char d = ' ', int f = 0) {
        data = d;
        freq = f;
        left = right = NULL;
    }
};

struct compare {
    bool operator()(node* left, node* right) {
        return (left->freq > right->freq);
    }
};

void frequency(string str) {
    for (int i = 0; i < str.length(); i++) {
        freq[str[i]]++;
    }
}

string encodedString(string txt) {
    string str = "";
    for (int i = 0; i < txt.length(); i++) {
        str += patt[txt[i]];
    }
    return str;
}

void bitPattern(node* n, string str) {
    if (n == NULL) {
        return;
    }
    else if (n->data != '*') {
        patt[n->data] = str;
    }
    bitPattern(n->left, str + "0");
    bitPattern(n->right, str + "1");
}

void encode(priority_queue<node*, vector<node*>, compare> &q) {
    while (q.size()>1) {
        node* left, * right, * parent;
        left = q.top();
        q.pop();
        right = q.top();
        q.pop();
        parent = new node('*', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        q.push(parent);
    }
    bitPattern(q.top(), "");
}

string decode(node*& root, string coded) {
    string text = "";
    node* n = root;
    for (int i = 0; i <= coded.length(); i++) {
        if (n->data != '*') {
            text += n->data;
            n = root;
        }
        if (coded[i] == '0') {
           n = n->left;
        }
        else if (coded[i] == '1') {
           n = n->right;
        }
    }
    return text;
}

//DRIVER
int main() {
    string text = "A quick brown fox jumps over the lazy dog";
    cout << "Original text: " << text << endl;

    priority_queue<node*, vector<node*>, compare> q;
    frequency(text);
    cout << "\nFrequency:\n";
    map<char, int>::iterator it;
    for (it = freq.begin(); it != freq.end(); it++) {
        cout << it->first << " : " << it->second << endl;
        q.push(new node(it->first, it->second));
    }

    encode(q);
    cout << "\nBit Pattern:\n";
    map<char, string>::iterator it_;
    for (it_ = patt.begin(); it_ != patt.end(); it_++) {
        cout << it_->first << " : " << it_->second << endl;
    }

    string coded = encodedString(text);
    cout << "\nEncoded text: " << coded << endl;

    node* n=q.top();
    string decoded = decode(n, coded);
    cout << "\nDecoded text: " << decoded << endl;
    
    return 0;
}
