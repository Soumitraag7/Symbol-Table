#include <iostream>
#include <list>

#define SIZE 15

using namespace std;

class SymbolInfo // class for storing a symbol and its type with a next pointer
{
public:
    string symbol;
    string symbol_type;
    SymbolInfo(string &name, string &type);
};

SymbolInfo::SymbolInfo(string &name, string &type)
{
    symbol = name;
    symbol_type = type;
}

class SymbolTable // class creating hashtable , functions to insert, search, dump, delete symbols
{
public:
    list<SymbolInfo *> table[SIZE];
    SymbolInfo *si;

    // hash function
    int hash(string id)
    {
        int asciiSum = 0;
        for (int i = 0; i < id.length(); i++)
        {
            asciiSum += id[i];
        }
        return (asciiSum % SIZE);
    }

    // function to insert new symbols in hash table
    int insert(SymbolInfo *si)
    {
        if (this->lookup(si->symbol) != 0)
            return 0;

        int h = hash(si->symbol);
        table[h].push_back(si);
        return 1;
    }

    // function to search desired symbol
    SymbolInfo *lookup(const string &symbol)
    {
        int h = hash(symbol);
        list<SymbolInfo *>::iterator i;
        for (i = table[h].begin(); i != table[h].end(); i++)
        {
            if ((*i)->symbol == symbol)
                return *i;
        }
        return 0;
    }

    // function to print the whole hashtable
    void dump()
    {
        list<SymbolInfo *>::iterator j;

        for (int i = 0; i < SIZE; ++i)
        {
            cout << i << ": ";
            for (j = table[i].begin(); j != table[i].end(); ++j)
            {
                cout << "->[Symbol: " << (*j)->symbol << ", Type: " << (*j)->symbol_type << "] ";
            }
            cout << endl;
        }
    }

    // function to delete a certain input symbol
    void erase(const string &symbol)
    {
        list<SymbolInfo *>::iterator j;

        for (int i = 0; i < SIZE; i++)
        {
            for (j = table[i].begin(); j != table[i].end(); j++)
            {
                if ((*j)->symbol == symbol)
                {
                    cout << "\nDeleted ->[Symbol: " << (*j)->symbol << ", Type: " << (*j)->symbol_type << "]" << endl;
                    table[i].erase(j);
                    break;
                }
            }
        }
    }
};

void menu()
{
    cout << "\n* Press 1 to insert a new symbol along with its type into the symbol-table";
    cout << "\n* Press 2 to lookup whether a given symbol already exists in the symbol-table or not";
    cout << "\n* Press 3 to dump the contents of the symbol-table to the console";
    cout << "\n* Press 4 to delete a given symbol if it already exists in the symbol-table";
    cout << "\n* Press 0 to exit\n";
}

int main()
{
    int choice;
    string name, type;
    SymbolTable st;
    SymbolInfo *si;

    menu();
    cout << "\nEnter your choice: ";
    cin >> choice;

    while (choice != 0)
    {
        switch (choice)
        {
        // insert
        case 1:
            cout << "\nEnter a symbol and it's type: " << endl;
            cin >> name >> type;
            si = new SymbolInfo(name, type);
            if (!st.insert(si))
                cout << "[WARNING] Symbol already exists.\n";
            break;

        // lookup
        case 2:
            cout << "\nEnter a symbol for lookup: ";
            cin >> name;
            si = st.lookup(name);
            if (si == 0)
                cout << "\n[INFO] Symbol not found.\n";
            else
                cout << "\n[INFO] Symbol found:\n"
                     << "\nSymbol: " << si->symbol << ", Type: "
                     << si->symbol_type << ", Symbol is present in position: " << st.hash(name) << endl;
            break;

        // dump
        case 3:
            cout << "\nSymbol Table:\n";
            st.dump();
            cout << endl;
            break;

            // delete
        case 4:
            cout << "\nEnter a symbol to delete: ";
            cin >> name;

            si = st.lookup(name);
            if (si == 0)
                cout << "[WARNING] Symbol do not exisist.\n";
            else
                st.erase(name);
            break;

        default:
            cout << "\n# Choose a number form the menu.\n";
        }

        menu();
        cout << "\nEnter your choice: ";
        cin >> choice;
    }

    return 0;
}
