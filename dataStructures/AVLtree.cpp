#include<bits/stdc++.h>
using namespace std;

template<typename Key, typename Metadata>
struct _Tree_Vertex {
    _Tree_Vertex* parent;
    _Tree_Vertex* left;
    _Tree_Vertex* right;
    Key key;
    Metadata metadata;
    int height;

    _Tree_Vertex(const Key& k, _Tree_Vertex* p = nullptr)
        : parent(p), left(nullptr), right(nullptr), key(k), height(1) {}
};

template<typename Key, typename Metadata>
struct AVL {
    using _node = _Tree_Vertex<Key, Metadata>;

    _node *head;

    // Used to compare two keys; returns true if lhs < rhs
    function<bool(const Key&, const Key&)> comparator;

    // Used to update node->metadata given node, children, etc.
    // Called in bottom-up fashion after we update node->height.
    function<void(_node*)> updator;

    // Constructor
    AVL(function<bool(const Key&,const Key&)> _comparator,
        function<void(_node*)> _updator)
    {
        comparator = _comparator;
        updator = _updator;
        head = nullptr;
    }

    // Helper: get the height of a node
    int getHeight(_node* node) {
        return (node ? node->height : 0);
    }

    // Helper: compute balance factor = height(left) - height(right)
    int getBalance(_node* node) {
        if (!node) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Recompute node->height, then call updator(node).
    void updateNode(_node* node) {
        if (!node) return;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        // Call the user’s updator so the metadata can be updated
        updator(node);
    }

    // Right rotate the subtree rooted at y
    _node* rotateRight(_node* y) {
        _node* x = y->left;
        _node* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update parent pointers (if you need them in your logic)
        if(T2) T2->parent = y;
        x->parent = y->parent;
        y->parent = x;

        // Update heights & metadata in bottom-up order
        updateNode(y);
        updateNode(x);
        return x;  // x becomes the new root of this subtree
    }

    // Left rotate the subtree rooted at x
    _node* rotateLeft(_node* x) {
        _node* y = x->right;
        _node* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update parent pointers (if you need them in your logic)
        if(T2) T2->parent = x;
        y->parent = x->parent;
        x->parent = y;

        // Update heights & metadata in bottom-up order
        updateNode(x);
        updateNode(y);
        return y;  // y becomes the new root of this subtree
    }

    // Balance a node if needed
    _node* balance(_node* node, const Key &key) {
        if (!node) return node;

        int balanceFactor = getBalance(node);

        // Left Heavy
        if (balanceFactor > 1) {
            // If key is smaller than node->left->key => Left-Left
            // else => Left-Right
            if (comparator(key, node->left->key)) {
                // Left-Left
                return rotateRight(node);
            } else {
                // Left-Right
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }
        // Right Heavy
        else if (balanceFactor < -1) {
            // If key is greater than node->right->key => Right-Right
            // else => Right-Left
            if (comparator(node->right->key, key)) {
                // Right-Right
                return rotateLeft(node);
            } else {
                // Right-Left
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        // Already balanced
        return node;
    }

    // Balance a node after erase (we might not know which direction
    // to rotate just from the erased key, so a simpler check).
    _node* balanceErase(_node* node) {
        if (!node) return node;

        int balanceFactor = getBalance(node);

        // Left heavy
        if (balanceFactor > 1) {
            // Check child balance
            if (getBalance(node->left) >= 0) {
                // Left-Left
                return rotateRight(node);
            } else {
                // Left-Right
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }
        // Right heavy
        else if (balanceFactor < -1) {
            // Check child balance
            if (getBalance(node->right) <= 0) {
                // Right-Right
                return rotateLeft(node);
            } else {
                // Right-Left
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }
        return node;
    }

    // Recursive helper to insert a new key in subtree rooted at 'node'
    // 'parent' is to set node->parent if you want to maintain parent pointers
    _node* insertNode(_node* node, const Key &key, _node* parent = nullptr) {
        // 1. Standard BST insertion
        if (!node) {
            _node* newNode = new _Tree_Vertex<Key, Metadata>(key, parent);
            // If you want to call updateNode on newNode (some folks do),
            // but typically you do it after children are set, so it's fine here too:
            updator(newNode);
            return newNode;
        }

        if (comparator(key, node->key)) {
            node->left = insertNode(node->left, key, node);
        }
        else if (comparator(node->key, key)) {
            node->right = insertNode(node->right, key, node);
        }
        else {
            // Equal keys case: you can decide to do nothing or always go right or left
            // For example, let's choose to always go right if equal
            node->right = insertNode(node->right, key, node);
        }

        // 2. Balance the node
        node = balance(node, key);

        // 3. Update this node's height & metadata
        updateNode(node);

        return node;
    }

    // Insert public method
    void insert(const Key &key) {
        head = insertNode(head, key, nullptr);
    }

    // Find the node with min key in subtree
    _node* getMinNode(_node* node) {
        while (node && node->left) {
            node = node->left;
        }
        return node;
    }

    // Recursive helper to erase 'key' from subtree
    _node* eraseNode(_node* node, const Key &key) {
        if (!node) return nullptr;

        if (comparator(key, node->key)) {
            // key < node->key
            node->left = eraseNode(node->left, key);
        }
        else if (comparator(node->key, key)) {
            // key > node->key
            node->right = eraseNode(node->right, key);
        }
        else {
            // This is the node to be deleted
            if (!node->left || !node->right) {
                // One child or no child
                _node* temp = (node->left) ? node->left : node->right;

                // No child case
                if (!temp) {
                    // free node
                    delete node;
                    node = nullptr;
                }
                else {
                    // One child
                    // Copy the contents of the child
                    temp->parent = node->parent;  // keep parent pointer updated
                    *node = *temp;                 // tricky: copies all fields
                    delete temp;                   // free the "duplicate" node
                }
            } else {
                // Node with two children:
                // Get the inorder successor (smallest in the right subtree)
                _node* successor = getMinNode(node->right);
                // Copy the successor's key & metadata to this node
                node->key = successor->key;
                node->metadata = successor->metadata;
                // Erase the successor
                node->right = eraseNode(node->right, successor->key);
            }
        }

        // If the tree had only one node, then return
        if (!node) return node;

        // Balance the node after deletion
        node = balanceErase(node);

        // Update height & metadata
        updateNode(node);
        return node;
    }

    // Erase public method
    void erase(const Key &key) {
        head = eraseNode(head, key);
    }

    _node* lower_bound(const Key &key) const {
        _node* ans = nullptr;
        _node* current = head;
        while (current) {
            // Recall: comparator(a, b) == true if a < b
            // We want the first key that is NOT less than `key`.
            // If current->key is NOT less than 'key', we move left 
            // and record current as a potential answer.
            if (!comparator(current->key, key)) {
                // This means current->key >= key
                ans = current;
                current = current->left;
            } else {
                // current->key < key
                current = current->right;
            }
        }
        return ans;
    }
};