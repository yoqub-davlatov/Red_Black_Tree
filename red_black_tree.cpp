// @author Yoqub Davlatov

#include <iostream>
#include <queue>
using namespace std;


template <typename T>
struct Node
{
    T value;
    Node *left;
    Node *right;
    Node *parent;
    bool black;
    bool leftChild;

    Node(T value)
        : value(value), left(nullptr), right(nullptr), parent(nullptr), black(false), leftChild(false)
    {
    }
};

template <typename T>
class RedBlackTree
{
private:
    Node<T> *root = nullptr;
    int size = 0;

private:
    void add(Node<T> *parent, Node<T> *node)
    {
        if (node->value > parent->value) // insert to the right subtree
        {
            if (!parent->right) // the right spot was found
            {   
                parent->right = node;
                node->parent = parent;
                node->leftChild = false;
            }
            else    // insert to the right subtree
            {
                return add(parent->right, node);
            }
        }
        else                // insert to the left subtree
        {
            if (!parent->left) // the right spot was found
            {
                parent->left = node;
                node->parent = parent;
                node->leftChild = true;
            }
            else    // insert to the left subtree
            {
                return add(parent->left, node);
            }
        }
        return checkColor(node);
    }

    void checkColor(Node<T> *node)
    {
        if (node == root)
        {
            node->black = true;
            return;
        }
        if (!node->black and !node->parent->black)
        {
            // two consecutive red nodes:
            correctTree(node);
        }
        // in case we violate some rules
        if (node->parent)
        {
            checkColor(node->parent);
        }
    }

    void correctTree(Node<T> *node)
    {
        // find node's uncle's color
        if (node->parent->leftChild)
        {
            // uncle is right child of node's grandparent
            // uncle is node.parent.parent.right (might be nullptr, that's why we check)
            if (!node->parent->parent->right or node->parent->parent->right->black)
            {
                // uncle's color is black, then rotate
                return rotate(node);
            }
            // uncle's color is red -> color flip with respect to grandparent
            // (grandparent becomes red, parent and uncle - black)
            if (node->parent->parent->right)
            {
                node->parent->parent->right->black = true;
            }
            node->parent->parent->black = false;
            node->parent->black = true;
        }
        else
        {
            // uncle is left child of node's grandparent
            // uncle is node.parent.parent.left
            if (!node->parent->parent->left or node->parent->parent->left->black)
            {
                return rotate(node);
            }
            if (node->parent->parent->left)
            {
                node->parent->parent->left->black = true;
            }
            node->parent->parent->black = false;
            node->parent->black = true;
        }
    }

    void rotate(Node<T> *node)
    {
        if (node->leftChild)
        {
            if (node->parent->leftChild)
            {
                // node is left child and parent is left child (LL case), then right rotate the grandparent
                rightRotate(node->parent->parent);
                // fix the colors: parent becomes black, node and sibling - red
                // node and parent stay in their places
                node->black = false;
                node->parent->black = true;
                // sibling is parent's right child
                if (node->parent->right)
                {
                    node->parent->right->black = false;
                }
            }
            else
            {
                // node is left child and parent is right child (LR case), then right-left rotate the grandparent
                rightLeftRotate(node->parent->parent);
                // fix colors: parent becomes black, node and sibling - red
                // node becomes parent
                node->black = true;
                node->left->black = false;
                node->right->black = false; 
            }
        }
        else
        {
            if (!node->parent->leftChild)
            {
                // node is right child and parent is right child
                leftRotate(node->parent->parent);
                // fix the colors: parent becomes black, children - red
                // node and parent stay in their places
                node->black = false;
                node->parent->black = true;
                if (node->parent->left)
                {
                    node->parent->left->black = false;
                }
            }
            else
            {
                // node is right child, and parent is left child
                leftRightRotate(node->parent->parent);
                // fix the colors: parent becomes black, children - red
                // node becomes parent
                node->black = true;
                node->left->black = false;
                node->right->black = false;
            }
        }
    }

    void leftRotate(Node<T>* node)
    {
        // make temporary pointer to right child (parent of the node that caused violation)
        Node<T>* temp = node->right;

        // set node's right child to temp's left child
        node->right = temp->left;
        
        if (node->right) // in case it is a subtree
        {
            // set its parent to current node
            node->right->parent = node;
            // since it was temp's left child, and became node's right child, mark it as right child
            node->right->leftChild = false;
        }
        // change the parent of temp
        temp->parent = node->parent;
        if (!temp->parent)
        {
            // if temp's parent is nullptr, then temp is root now
            root = temp;
            temp->black = true;
        }
        else
        {   
            if (node->leftChild) // node is left child, therefore after rotation temp becomes left child
            {
                temp->leftChild = true;
                // temp->parent is currently node->parent
                // so we set node's parent left child to temp
                temp->parent->left = temp;
            }
            else
            {
                temp->leftChild = false;
                temp->parent->right = temp;
            }
        }
        // left rotate node
        temp->left = node;
        // node becomes left child after rotation
        node->leftChild = true;
        // node's parent become temp
        node->parent = temp;
    }

    void rightRotate(Node<T>* node)
    {
        // make temporary pointer to left child (parent of the node that caused violation)
        Node<T>* temp = node->left;
        // set temp's right child to node's left child
        node->left = temp->right;
        // fix temp's child data
        if (node->left)
        {
            // temp's child's parent is now node
            node->left->parent = node;
            // temp's child was right, now it is left
            node->left->leftChild = true;
        }

        // set temp's parent to node's parent
        temp->parent = node->parent;
        if (!temp->parent)
        {
            // temp is root now;
            root = temp;
            temp->black = true;
        }
        else
        {
            if (node->leftChild)
            {
                // temp->parent is currently node->parent
                // so we set node's parent left child to temp
                temp->parent->left = temp;
                temp->leftChild = true;
            }
            else
            {
                temp->parent->right = temp;
                temp->leftChild = false;
            }
        }
        // right rotate
        temp->right = node;
        node->parent = temp;
        node->leftChild = false;
    }

    void leftRightRotate(Node<T>* node)
    {   
        leftRotate(node->left);
        rightRotate(node);
    }

    void rightLeftRotate(Node<T>* node)
    {
        rightRotate(node->right);
        leftRotate(node);
    }
public:
    void insert(const T &node)
    {
        Node<T> *newNode = new Node<T>(node);
        size++;
        if (!root)
        {
            root = newNode;
            root->black = true;
        }
        else
        {
            add(root, newNode);
        }
    }

    void print()
    {
        queue<Node<T>*> q;
        q.push(root);
        int cnt = 2;
        while (q.size())
        {
            int n = q.size();
            for (int i = 0; i < n; i++)
            {
                Node<T> *node = q.front();
                q.pop();
                cout << node->value << ' ';
                if (node->left)
                {
                    cout << cnt++ << ' ';
                    q.push(node->left);
                }
                else
                {
                    cout << -1 << ' ';
                }
                if (node->right)
                {
                    cout << cnt++ << ' ';
                    q.push(node->right);
                }
                else
                {
                    cout << -1 << ' ';
                }
                cout << endl;
            }
        }

    }
};


int main()
{
    RedBlackTree<int> rbt;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        rbt.insert(x);
    }
    cout << n << endl;
    rbt.print();
    cout << 1 << endl;
}