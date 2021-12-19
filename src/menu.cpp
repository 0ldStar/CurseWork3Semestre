//
// Created by 777 on 17.12.2021.
//
#include <iostream>
#include "Tree.h"
#include "menu.h"

int menu() {
    int error, menuPos, exit, newDataCount;
    bool editFlag;
    Tree tree;

    tree.open(PATH, ios::in | ios::out | ios::binary);
    error = 0;
    menuPos = -1;
    exit = 0;
    newDataCount = 0;
    editFlag = false;
    if (tree.is_open()) {
        int b_size = tree.getSize();
        tree.LoadTree();
        cout << "Was read " << tree.getSize() - b_size << " strings from data base\n";
        reopen(tree);
        while (!exit) {
            cout << "Choose the option\n";
            cout << "# 0 Exit\n";
            cout << "# 1 Read data from txt\n";
            cout << "# 2 Write data in txt\n";
            cout << "# 3 Add new data to base\n";
            cout << "# 4 Print data to Terminal\n";
            cout << "# 5 Edit data\n";
            cout << "# 6 Delete data\n";
            cout << "# 7 Clear data base\n";
            cin >> menuPos;
            if (menuPos >= 0 && menuPos <= 7) {
                switch (menuPos) {
                    case 0: {
                        exit = 1;
                        break;
                    }
                    case 1: {
                        error = inputFile(tree, newDataCount);
                        if (!error) editFlag = true;
                        break;
                    }
                    case 2: {
                        error = outputFile(tree);
                        break;
                    }
                    case 3: {
                        addNewData(tree);
                        editFlag = true;
                        newDataCount++;
                        break;
                    }
                    case 4: {
                        printData(tree);
                        break;
                    }
                    case 5: {
                        editData(tree);
                        if (!error) editFlag = true;
                        break;
                    }
                    case 6: {
                        deleteData(tree);
                        if (!error) editFlag = true;
                        break;
                    }
                    case 7: {
                        error = clearData(tree, exit);
                        if (!error) editFlag = true;
                        break;
                    }
                    default:
                        break;
                }
            }
            if (newDataCount >= AUTOSAVECOUNT) {
                tree.toBinary();
                reopen(tree);
                newDataCount = 0;
            }
        }
        askToSave(tree, editFlag);
        tree.toBinary();
        tree.close();
    } else {
        cout << "Data base read error!!!";
        error = -1;
    }

    return error;
}

int inputFile(Tree &tree, int &count) {
    int error = 0;
    string name;
    int b_size = tree.getSize();
    cout << "Enter path to file: ";
    cin >> name;
    ifstream is(name, ios::in);
    if (is.is_open()) {
        tree << is;
        cout << "Was read " << tree.getSize() - b_size << " strings\n";
        count += tree.getSize() - b_size;
    } else {
        cout << "Can`t open file!\n";
        error = 1;
    }
    is.close();
    return error;
}

int outputFile(Tree &tree) {
    if (tree.getSize() == 0) {
        cout << "Tree is empty\n";
        return 0;
    }
    int error = 0;
    string name;
    cout << "Enter path to file: ";
    cin >> name;
    ofstream os(name, ios::out | ios::app);
    if (os.is_open()) {
        os << tree;
        cout << "Was wrote " << tree.getSize() << " elements\n";
    } else {
        cout << "Can`t open file!";
        error = 1;
    }
    os.close();
    return error;
}

void addNewData(Tree &tree) {
    string str;
    cout << "Enter string:";
    cin >> str;
    tree.insert((char *) str.c_str());
}

void printData(Tree &tree) {
    if (tree.getSize() == 0) {
        cout << "Tree is empty\n";
        return;
    }
    cout << "Print all tree or element from index? (1/2)";
    int choose;
    while (true) {

        cin >> choose;
        if (choose != 1 && choose != 2) {
            cout << "Incorrect number";
            cout << "Print all tree or element from index? (1/2)";
        } else {
            if (choose == 1) {
                cout << tree << endl;
            } else if (choose == 2) {

                cout << "Current tree have " << tree.getSize() << " elements\n";
                cout << "You can choose one of them [0-" << tree.getSize() - 1 << "]\nEnter index: ";
                int index;
                while (true) {
                    cin >> index;
                    if (index >= 0 && index < tree.getSize()) {
                        Node node = tree[index];
                        for (int i = 0; i < node.strLen; ++i) {
                            cout << node.str[i];
                        }
                        cout << endl;
                        break;
                    } else {
                        cout << "Incorrect index";
                        cout << "Current tree have " << tree.getSize() << " elements\n";
                        cout << "You can choose one of them [0-" << tree.getSize() - 1
                             << "]\nEnter index: ";
                    }

                }
            }
            break;
        }

    }

}

int clearData(Tree &tree, int &exit) {
    int error = 0;
    cout << "Warning!!!\n Are you really want to delete all data from base? (1-Yes/0-No)";
    int choose;
    while (true) {
        cin >> choose;
        if (choose != 1 && choose != 0) {
            cout << "Incorrect number!\n";
            cout << "Warning!!!\n Are you really want to delete all data from base? (1-Yes/0-No)";
        } else {
            if (choose == 1) {
                tree.free();
//                cout << "Yeap";
                tree.close();
                tree.update();
                tree.open("../data-sets/write.dat", ios::in | ios::out | ios::binary | ios::trunc);
                if (!tree.is_open()) {
                    error = -1;
                    exit = 1;
                }
                //tree.LoadTree();
            }
            break;
        }

    }
    return error;
}

void editData(Tree &tree) {
    if (tree.getSize() == 0) {
        cout << "Tree is empty\n";
        return;
    }
    cout << "Current tree have " << tree.getSize() << " elements\n";
    cout << "You can choose one of them [0-" << tree.getSize() - 1 << "] for edit\nEnter index: ";
    int index;
    while (true) {
        cin >> index;
        if (index >= 0 && index < tree.getSize()) {
            for (int i = 0; i < tree[index].strLen; ++i)
                cout << tree[index].str[i];
            cout << endl;
            string str;
            cout << "Enter string: ";
            cin >> str;
            free(tree[index].str);
            tree[index].str = new char[str.length()];
            for (int i = 0; i < str.length(); ++i) {
                tree[index].str[i] = str.c_str()[i];
            }
            tree[index].strLen = str.length();
            break;
        } else {
            cout << "Incorrect index!\n";
            cout << "Current tree have " << tree.getSize() << " elements\n";
            cout << "You can choose one of them [0-" << tree.getSize() - 1
                 << "] for edit\nEnter index: ";
        }
    }
}

void deleteData(Tree &tree) {
    cout << "Current tree have " << tree.getSize() << " elements\n";
    cout << "You can choose one of them [0-" << tree.getSize() - 1 << "] for delete\nEnter index: ";
    int index, choose;
    while (true) {
        cin >> index;
        if (index >= 0 && index < tree.getSize()) {
            for (int i = 0; i < tree[index].strLen; ++i)
                cout << tree[index].str[i];
            cout << endl;
            cout << "Are you sure delete this element? (1-Yes/0-No)";
            while (true) {
                cin >> choose;
                if (choose != 1 && choose != 0) {
                    cout << "Incorrect number!\n";
                    cout << "Are you sure delete this element? (1-Yes/0-No)";
                } else {
                    if (choose == 1) {
                        Node *node = &tree[index];
                        free(node->str);
                        node->str = nullptr;
                        node->strLen = 0;
                    }
                    break;
                }

            }
            break;
        } else {
            cout << "Incorrect index!\n";
            cout << "Current tree have " << tree.getSize() << " elements\n";
            cout << "You can choose one of them [0-" << tree.getSize() - 1
                 << "] for delete\nEnter index: ";
        }
    }
}

void reopen(Tree &tree) {
    tree.close();
    tree.open(PATH, ios::out | ios::binary);
}

void askToSave(Tree &tree, int editFlag) {
    if (editFlag) {
        cout << "Do you want to save changes to text file ? (1-Yes/0-No)";
        int choose;
        while (true) {
            cin >> choose;
            if (choose != 1 && choose != 0) {
                cout << "Incorrect number!\n";
                cout << "Do you want to save changed data to text file ? (1-Yes/0-No)";
            } else {
                if (choose == 1) {
                    outputFile(tree);
                }
                break;
            }

        }
    }
}