#pragma once
#include<exception>
#include<iostream>
template<class T>
struct Node
{
    T value;
    Node<T>* left;
    Node<T>* right;
    int height;
    int size;
    Node(const T& _val, Node<T>* _left = nullptr, Node<T>* _right = nullptr,int _heihgt = 0, int _size = 1): value(_val), left(_left), right(_right),height(_heihgt), size(_size){};
};

template <class T>
class BTrees
{
private:
    Node<T>* root;
    const int MAX_INBALANCE = 1;

    Node<T>* copy(Node<T>* root){
        //ako nqma element
        if(!root){
            return nullptr;
        }
        //inache vrushtame
        return new Node(root->value, copy(root->left),copy(root->right),root->height,root->size);
    }

    void free(Node<T>* root)
    {
        if(!root){
            return;
        }
        //inache imame element
        free(root->left);
        free(root->right);
        delete root;
    }

    void rightRotation(Node<T>*& root){
        //vsqkash go vzimame s rukata
        //kogato lqvata chast e po-tejka
        Node<T>* originalLeft = root->left;
        root->left = originalLeft->right;
        originalLeft->right = root;

        // da updeitnem samite visochini
        root->height = std::max(getNodeHeight(root->left), getNodeHeight(root->right)) +1;
        originalLeft->height = std::max(getNodeHeight(originalLeft->left), getNodeHeight(originalLeft->right))+1;

        // trqbva da updeitnem i size
        root->size = (getNodeSize(root->left) + getNodeSize(root->right)) + 1;
        originalLeft->size = (getNodeSize(originalLeft->left) + getNodeSize(originalLeft->right)) +1;

        //da updeitnem korena
        root = originalLeft;
    }

    void leftRotation(Node<T>*& root){
        // kogato dqsnata chast e po-tejka
        Node<T>* originalRight = root->right;
        root->right =  originalRight->left;
        originalRight->left = root;

        root->height = std::max(getNodeHeight(root->left), getNodeHeight(root->right)) +1;
        originalRight->height = std::max(getNodeHeight(originalRight->left), getNodeHeight(originalRight->right))+1;

        root = originalRight;
    }

    void leftRightRotation(Node<T>*& root){
        leftRotation(root->left);
        rightRotation(root);
    }

    void rightLeftRotation(Node<T>*& root){
        rightRotation(root->right);
        leftRotation(root);
    }

    void balance(Node<T>*&root){
        if(!root){
            return;
        }
        //inache koe ot dvete e po-tejko
        if(getNodeHeight(root->left) - getNodeHeight(root->right) > MAX_INBALANCE){
            //da vidim na lqvoto poddurvo koe ot poddurvata e po-tejkoto
            if(getNodeHeight(root->left->left) >= getNodeHeight(root->left->right)){
                rightRotation(root);
            }
            else{
                leftRightRotation(root);
            }
        }
        else if(getNodeHeight(root->right) - getNodeHeight(root->left) > MAX_INBALANCE){
            //koe e po-tejko ot decata
            if(getNodeHeight(root->right->right) >= getNodeHeight(root->right->left)){
                leftRotation(root);
            }
            else{
                rightLeftRotation(root);
            }
        }

        //za vseki sluchai da se podsigurim 
        root->height = std::max(getNodeHeight(root->right),getNodeHeight(root->left)) + 1;
    }

    bool _contains(Node<T>* node, const T& data)const{
        if(!node){
            return false;
        }
        if(node->value == data){
            return true;
        } 
        if(node->value > data){
            return _contains(node->left,data);
        }
        if(node->value < data){
            return _contains(node->right, data);
        }
    }

    void _add(Node<T>*& root,const T& data){
        if(!root){
            //ako nqmame nishto v durvoto ni go suzdavame tozi element
            root = new Node(data);
        }
        //inache tursim kude da go dobavim
        if(root->value > data){
            _add(root->left,data);
        }
        if(root->value < data){
            _add(root->right, data);
        }
        root->size = getNodeSize(root->left) + getNodeSize(root->right) + 1;
    }

    int  getNodeHeight(Node<T>* node)const{
        if(node){
            //imame si pole za nego
            return node->height;
        }
        // nevaliden indeks inache
        return -1;
    }
    /* po startiqt, no ne dobur nachin v koito vzimame samo stoinostta, bez swapovete
    T getMin(Node<T>* node) const
    {
        if(!node){
            throw std::logic_error("Empty !");
        }
        while(node){
            node = node->left;
        }
        return node->value;
    }

    void _remove(Node<T>*& root, const T& data){
        if(!root){return;}
        //inache tursim v durvoto
        if(root->value < data){
            _remove(root->right,data);
        }
        else if(root->value < data){
            _remove(root->left,data);
        }
        
        //tuk sme go namerili kolko naslednika ima? 0,1 ili 2?
        if(!root->left && !root->right){
            //nqma naslednici, prosto go triem togava
            delete root;
            //vajno uslovie e da se zanuli    
            root = nullptr;
        }

        else if(!root->left){
            //ako ima desen naslednik,to:
            Node<T>* toDel = root;
            root = root->right;
            delete toDel;
            return;
        }
        else if(!root->right){
            //treim inache i go zamenqme s lqvoto dete
            Node<T>* toDel= root;
            root = root->left;
            delete toDel;
            return;
        } 
        else{
            //imame dvva naslednika, namirame minimumut v dqsnoto poddurvo i povtarqme procedurata za nego
            T minRight = getMin(root->right);
            root->value = minRight;
            _remove(root->right, minRight);
        }   
        balance(root);
    }
    
    */

    //sega po noviq nachin

    Node<T>*& getMin(Node<T>*& root)const{
        if(!root->left){
            return root;
        }        
        return getMin(root->left);
    }

    void _remove(Node<T>*& root, const T& data){
        if(!root){
            return;
        }
        else if(root->value > data){
            _remove(root->left,data);
        }
        else if(root->value < data){
            _remove(root->right,data);
        }
        else{
            //inache sme go namerili 
            if(!root->left && !root->right){
                delete root;
                root = nullptr; // ako ne e reference nqmame dostup da pravim tova
                return;
            }

            else if(!root->left){
                //imame dqsno dete
                Node<T>* toDel = root;
                root = root->right;
                delete toDel;
                //tuk kazaxme che ne problem da ne go napravim nullptr tui kato e pointur kum tozi vrux, a ne reference
                return;
            }
            else if(!root->right){
                //ima lqvo dete
                Node<T>* toDel = root;
                root = root->left;
                delete toDel;
                return;
            }
            else{
                //inache imame dva naslednika
                Node<T>*& minNode = getMin(root->right);
                
                //tuk imaxme osben sluchai ako sa susedi root i minNode;
                if(minNode == root->right){
                    // iskame da maxnem root, no znaem che toi ima dva naslednika, toest ne trqbva da gubim lqvoto dete
                    minNode->left = root->left; // tuk tochno tova pravim kato go svurzvame pravilno s lqvoto dete na root;
           		    Node<T>* toDelete = root; 
            		root = minNode;
            		delete toDelete;
                    return;
                }
                else{
                    //inache ne sa susedi i trqbva da gi swapnem pravilno
                    Node<T>* oldRootLeft = root->left; // ima lqvo i
                    Node<T>* oldRootRight = root->right; // dqsno dete koito ni trqbvat, inache gi gubim sled swap-a
                    Node<T>* oldMinNodeRight = minNode->right; // znaem che moje da ima takova ili nullptr, no nqma kak da ima lqvo, inache tozi nqmaseh da e min

                    swapNodePointers(root,minNode);
                    //sega na mqstoto na root stoi minNode, a na mqstoto na minNode - stoi root;
                    root->left = oldRootLeft;
                    root->right = oldRootRight;
                    minNode->right = oldMinNodeRight;
                    _remove(minNode, minNode->value);
                }
            }
        }
        if(root){
            root->size = getNodeSize(root->left) + getNodeSize(root->right) + 1; // updeitvame size za tekushtiq vrux
        }
    }

    // da implementirame i funckiite za koito spomenaxme rank i operator[]
    //ideqta za rank e che pokazva ot kolko elementa tekushtiqt e po-golqm v sortiranta redica ot elementi na durvoto
    int _rank(Node<T>*parent, const T& key)const
    {
        if(!parent){
            return 0; // nqmame takuv element
        }
        else if(parent->value > key){
            return _rank(parent->left,key); //tursim lqvo, zashtoto zasega ne sme namerili nqkoi po-maluk ot tekushtiq
        }
        else if(parent->value < key){
            //sus sigurnost e po-golqm ot vsichki vlqvo na parent, kakto i ot samiq parent, toest
            return getNodeSize(parent->left) + 1 + _rank(parent->right, key); // produljavame da tursim vdqsno
        }
        else {
            //nameren e 
            return getNodeSize(parent->left); // dava tochno kolko elementa po-malki ima ot nego, moje  i da e 0
        }
    }

    //koi element sedi na tazi poziciq v sortiraniq masiv ot stoinosti ot vurxovete na durvoto
    Node<T>* select(Node<T>* root,int index) const
    {
        //ne bi trqbvalo da vlizame v nego, no za vseki sluchai moje da go proverim, no s operator[] nqma da proverqvame, ne ochakvame da se sluchi da vurne nullptr
        if(!root){
            return nullptr;
        }
        int leftSize = getNodeSize(root->left);
        if(leftSize > index){
            // tova znachi che index e v lqvoto poddurvo i produljavame da go tursim
            select(root->left, index);
        }
        else if(leftSize == index){
            return root; // nameren e elementut
        }
        else{
            // znachi tursim v dqsno, toest znachi che tozi element e po-golqm ot vsichko v lqvo i trqbva da maxnem size na lqvata chast kakto - 1,
            //kato taka s tova -1 otchitame i samiq root;
            return select(root->right,index - leftSize - 1);
        }

    }

    int getNodeSize(Npde<T>* node) const {
        return node ? node->size : 0;
    }

    void _printDot(Node<T>* root) const {
        if(!root){
            return;
        }
        //inache imame stoinost tekushta
        std::cout << root->value << " ";
        _printDot(root->left);
        _printDot(root->right);
    }

public:
    //ctor with args
    BTrees(Node<T>* _root = nullptr) : root(_root){};
    //copy ctor
    BTrees(const BTrees<T>& other){
        this->root = copy(other.root);
    }
    //operator=
    BTrees<T>& operator=(const BTrees<T>& other)
    {
        if(this != &other)
        {
            Node<T>* newRoot = nullptr;
            try
            {
                newRoot = copy(other.root);
            }
            catch(const std::exception& e)
            {
                free(this->root);
            }
            //inache newRoot e srabotil i imame kopie na drugiq obekt
            //sega trqbva da prenasochim nashiqt, no purvo iztrivame ako ima neshto v nego
            free(this->root);
            this->root = newRoot;
        }
        return *this;
    }
    //dtor
    ~BTrees(){
        free(this->root);
    }

    //methods
    void add(const T& data){
        _add(this->root,data);
        balance(this->root); // ne zabravqme da go ostavim vuv validno balansirano sustoqnie
    }

    void remove(const T& data){
        _remove(this->root,data);
        balance(this->root); // analogichno i tuk 
    }

    bool contains(const T& data)const{
        return _contains(this->root, data);
    }

    int rank(const T& key)const{
        return _rank(this->root, key);
    }

    T& operator[](int index)
    {
        if(index < 0 || index > getNodeSize(this->root)){
            throw std::invalid_argument("Out of range!");
        }
        //inache e validen index
        return select(root,index)->value;
    }

    void printDot() const
    {
        std::cout << "Diagraph G:" << std::endl;
        _printDot(this->root);
        std::cout << std::endl;
    }
    
};

template<class T>
void swapNodePointers(Node<T>*& a, Node<T>*& b){
    Node<T>* temp = a;
    a = b;
    b = temp;
}