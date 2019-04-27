/* Пученков Дмитрий
 * АПО-13
 * Дано число N < 106 и последовательность пар целых чисел из [-231, 231] длиной N.
 * Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi).
 * Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве.
 * Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
 * При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте найденное поддерево по ключу x так,
 * чтобы в первом поддереве все ключи меньше x, а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y).
 * Новый узел вставьте на место узла P. Построить также наивное дерево поиска по ключам Xi.
 * Равные ключи добавляйте в правое поддерево.
 * Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска.
 * Вывести их разницу. Разница может быть отрицательна.
 */
#include <iostream>
#include <queue>
#include <iostream>

template<typename Key>
struct Node {
    Node(const Key &key, int priority = 0) : key(key), height(1), left(nullptr), right(nullptr), priority(priority) {}

    Key key;
    int priority;
    size_t height;
    Node *left;
    Node *right;
};

template<typename Key>
class AvlTree {


public:
    AvlTree() : root(nullptr) {}

    ~AvlTree() {
        destroyTree(root);
    }

    bool Has(const Key &key) const {
        Node<Key> *tmp = root;
        while (tmp) {
            if (tmp->key == key) {
                return true;
            } else if (tmp->key < key) {
                tmp = tmp->right;
            } else {
                tmp = tmp->left;
            }
        }
        return false;
    }

    void Add(const Key &key) {
        root = addInternal(root, key);
    }

    void Remove(const Key &key) {
        root = removeInternal(root, key);
    }

private:

    Node<Key> *root;

    void destroyTree(Node<Key> *node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    Node<Key> *addInternal(Node<Key> *node, const Key &key) {
        if (!node)
            return new Node<Key>(key);
        if (node->key <= key)
            node->right = addInternal(node->right, key);
        else
            node->left = addInternal(node->left, key);

        return doBalance(node);
    }

    Node<Key> *removeInternal(Node<Key> *node, const Key &key) {
        if (!node)
            return nullptr;
        if (node->key < key)
            node->right = removeInternal(node->right, key);
        else if (node->key > key)
            node->left = removeInternal(node->left, key);
        else {
            Node<Key> *left = node->left;
            Node<Key> *right = node->right;

            delete node;

            if (!right)
                return left;

            Node<Key> *min = findMin(right);
            min->right = removeMin(right);
            min->left = left;

            return doBalance(min);
        }

        return doBalance(node);
    }

    Node<Key> *findMin(Node<Key> *node) {
        while (node->left)
            node = node->left;
        return node;
    }

    Node<Key> *removeMin(Node<Key> *node) {
        if (!node->left)
            return node->right;
        node->left = removeMin(node->left);
        return doBalance(node);
    }

    Node<Key> *doBalance(Node<Key> *node) {
        fixHeight(node);

        switch (getBalance(node)) {
            case 2: {
                if (getBalance(node->right) < 0)
                    node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
            case -2: {
                if (getBalance(node->left) > 0)
                    node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
            default:
                return node;
        }
    }

    size_t getHeight(Node<Key> *node) {
        return node ? node->height : 0;
    }

    void fixHeight(Node<Key> *node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    int getBalance(Node<Key> *node) {
        return getHeight(node->right) - getHeight(node->left);
    }

    Node<Key> *rotateLeft(Node<Key> *node) {
        Node<Key> *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        fixHeight(node);
        fixHeight(tmp);
        return tmp;
    }

    Node<Key> *rotateRight(Node<Key> *node) {
        Node<Key> *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fixHeight(node);
        fixHeight(tmp);
        return tmp;
    }

    void split(Node<Key> *curNode, const Key &key, Node<Key> *&left, Node<Key> *&right) {
        if (curNode == NULL) {
            left = NULL;
            right = NULL;
        } else if (curNode->key <= key) {
            split(curNode->right, key, curNode->right, right);
            left = curNode;
        } else {
            split(curNode->left, key, left, curNode->left);
            right = curNode;
        }
    }
    void setRoot(Node<Key> *rootMain) {
        root = rootMain;
    }
public:
    void SecondAdd(const Key &key, int priority) {
        Node<Key> *node = new Node<Key>(key, priority),
                *curNode = root,
                *prevNode = root;

        if (curNode == NULL) {
            setRoot(node);
            return;
        }
        while (curNode != NULL && priority <= curNode->priority) {
            prevNode = curNode;
            if (key <= curNode->key) {
                curNode = curNode->left;
            } else {
                curNode = curNode->right;
            }
        }
        split(curNode, key, node->left, node->right);
        if (curNode == root) {
            root = node;
        } else if (key <= prevNode->key) {
            prevNode->left = node;
        } else {
            prevNode->right = node;
        }
    }

    int getMaxWidth() {
        int maxWidth = 0,
                curWidth = 0;

        std::queue<Node<Key> *> Sheets;
        Node<Key> *curNode = NULL;
        Sheets.push(root);
        while (!Sheets.empty()) {
            if ((curWidth = Sheets.size()) > maxWidth) {
                maxWidth = curWidth;
            }

            for (size_t i = 0; i < curWidth; i++) {
                curNode = Sheets.front();
                if (curNode->left != NULL) {
                    Sheets.push(curNode->left);
                }
                if (curNode->right != NULL) {
                    Sheets.push(curNode->right);
                }
                Sheets.pop();
            }
        }

        return maxWidth;
    }
};

template<class Key>
class Tree {
private:
    Node<Key> *root;
public:
    Tree() : root(NULL) {
    }

    ~Tree() {}

    void setRoot(Node<Key> *_root) {
        root = _root;
    }

    void add(const Key &data) {
        Node<Key> *node = new Node<Key>(data),
                *curNode = root;

        if (curNode == NULL) {
            setRoot(node);
            return;
        }
        while (true) {
            if (data < curNode->key) {
                if (curNode->left != NULL) {
                    curNode = curNode->left;
                } else {
                    curNode->left = node;
                    return;
                }
            } else {
                if (curNode->right != NULL) {
                    curNode = curNode->right;
                } else {
                    curNode->right = node;
                    return;
                }
            }
        }
    }

    int getMaxWidth() {
        int maxWidth = 0,
                curWidth = 0;

        std::queue<Node<Key> *> Sheets;
        Node<Key> *cur = NULL;
        Sheets.push(root);

        while (!Sheets.empty()) {
            if ((curWidth = Sheets.size()) > maxWidth) {
                maxWidth = curWidth;
            }

            for (size_t i = 0; i < curWidth; i++) {
                cur = Sheets.front();
                if (cur->left != NULL) {
                    Sheets.push(cur->left);
                }
                if (cur->right != NULL) {
                    Sheets.push(cur->right);
                }
                Sheets.pop();
            }
        }

        return maxWidth;
    }
};

int main(int argc, const char *argv[]) {
    Tree<int> firstTree;
    AvlTree<int> secondTree;
    int key;
    int priority;
    int N = 0;
    std::cin >> N;
    for (int i =0 ; i < N; i++) {
        std::cin >> key >> priority;
        secondTree.SecondAdd(key, priority);
        firstTree.add(key);
    }
    std::cout << secondTree.getMaxWidth() - firstTree.getMaxWidth();
    return 0;
}
    