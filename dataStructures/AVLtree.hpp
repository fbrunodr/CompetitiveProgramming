#ifndef FBRUNODR_AVL_TREE
#define FBRUNODR_AVL_TREE

#include "../header.hpp"

template<typename Key, typename Metadata>
struct _Tree_Vertex {
    _Tree_Vertex* parent;
    _Tree_Vertex* left;
    _Tree_Vertex* right;
    Key key;
    Metadata metadata;
    int height;
    int size;

    _Tree_Vertex(const Key& k, _Tree_Vertex* p = nullptr)
        : parent(p), left(nullptr), right(nullptr), key(k), height(1), size(1) {}
};


/*
    Assert all nodes have distinct priorities otherwise this won't work !!!
    If you have multiple values with same key / priority just make a counter
    key -> {key, counter}, so all values have distinct priorities
*/
template<typename Key, typename Metadata>
struct AVL {
    using _node = _Tree_Vertex<Key, Metadata>;

    private:
    int getHeight(_node* node) {
        return (node ? node->height : 0);
    }

    int getBalance(_node* node) {
        if (!node) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Recompute node->height, then call updator(node).
    void updateNode(_node* node) {
        if (!node) return;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        node->size = size(node->left) + size(node->right) + 1;
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

    pair<_node*, _node*> _split(_node* root, const Key &k) {
        if (!root) {
            return {nullptr, nullptr};
        }
        // If root->key < k, root goes to the LEFT part
        if (comparator(root->key, k)) {
            // Split the right subtree
            auto [leftSub, rightSub] = _split(root->right, k);
            root->right = leftSub;
            if (leftSub) leftSub->parent = root;
            // Update & balance
            updateNode(root);
            root = balanceErase(root);  // or a suitable balance(...) call
            // Return the pair ( everything < k, everything >= k )
            return {root, rightSub};
        } else {
            // root->key >= k, root goes to the RIGHT part
            auto [leftSub, rightSub] = _split(root->left, k);
            root->left = rightSub;
            if (rightSub) rightSub->parent = root;
            // Update & balance
            updateNode(root);
            root = balanceErase(root);  // or a suitable balance(...) call
            return {leftSub, root};
        }
    }

    _node* _join(_node* L, _node* R) {
        if (!L) return R;
        if (!R) return L;

        // If left tree is "taller" (or equally tall - your choice),
        // attach R somewhere in L->right
        if (getHeight(L) >= getHeight(R)) {
            L->right = _join(L->right, R);
            if (L->right) L->right->parent = L;
            updateNode(L);
            L = balanceErase(L); // or some suitable balancing method
            return L;
        } else {
            // R is taller
            R->left = _join(L, R->left);
            if (R->left) R->left->parent = R;
            updateNode(R);
            R = balanceErase(R);
            return R;
        }
    }

    public:

    _node *head;

    // Used to compare two keys; returns true if lhs < rhs
    f<bool(const Key&, const Key&)> comparator;

    // Used to update node->metadata given node, children, etc.
    // Called in bottom-up fashion after we update node->height.
    f<void(_node*)> updator;

    AVL(
        f<bool(const Key&,const Key&)> _comparator,
        f<void(_Tree_Vertex<Key, Metadata>*)> _updator
    ){
        comparator = _comparator;
        updator = _updator;
        head = nullptr;
    }

    static int size(_node* node){
        return (node ? node->size : 0);
    }

    int size() {
        return AVL<Key, Metadata>::size(head);
    }

    // Insert public method
    void insert(const Key &key) {
        head = insertNode(head, key, nullptr);
    }

    static _node* getMinNode(_node* node){
        if(!node)
            return nullptr;
        while(node->left)
            node = node->left;
        return node;
    }

    static _node* getMaxNode(_node* node){
        if(!node)
            return nullptr;
        while(node->right)
            node = node->right;
        return node;
    }

    _node* getMinNode(){
        return AVL<Key, Metadata>::getMinNode(head);
    }

    _node* getMaxNode(){
        return AVL<Key, Metadata>::getMaxNode(head);
    }

    static _node* getKthNode(int k, _node* node){
        if(!node)
            return nullptr;
        if(node->size <= k)
            return nullptr;
        int prevLessThan = 0;
        while(true){
            int lessThan = prevLessThan + AVL<Key, Metadata>::size(node->left);
            if(lessThan == k)
                return node;
            else if(lessThan < k){
                prevLessThan = lessThan + 1;
                node = node->right;
            }
            else
                node = node->left;
        }
    }

    // 0 indexed
    _node* getKthNode(int k){
        return AVL<Key, Metadata>::getKthNode(k, head);
    }

    // Erase public method
    void erase(const Key &key) {
        head = eraseNode(head, key);
    }

    _node* lower_bound(const Key &key) const {
        _node* ans = nullptr;
        _node* current = head;
        while (current) {
            // Recall: comparator(a, b) == true iff a < b
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

    pair<AVL, AVL> split(const Key &k) {
        auto splitted = _split(head, k);
        AVL leftAVL(comparator, updator);
        AVL rightAVL(comparator, updator);
        leftAVL.head = splitted.first;
        rightAVL.head = splitted.second;
        return {leftAVL, rightAVL};
    }

    // you are supposed to call this after a split
    static AVL join(AVL &leftAVL, AVL &rightAVL) {
        // Ensure that all keys in leftAVL < all keys in rightAVL
        // (The user is responsible for guaranteeing this!)
        AVL newAVL(leftAVL.comparator, leftAVL.updator);
        newAVL.head = newAVL._join(leftAVL.head, rightAVL.head);
        return newAVL;
    }
};

#endif
