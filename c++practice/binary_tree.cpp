#include "logger.cpp"


struct tree_node {
    string email_address;
    tree_node* left_child;
    tree_node* right_child;
};


class email_tree : public logged_class{
    email_tree();


    public:    
    email_tree(logger* my_logger): logged_class(my_logger){        
        root = nullptr;
    }

    email_tree(string first_email_address, logger* my_logger) : logged_class (my_logger){        
        root = nullptr;
        insert_email(first_email_address, root);
    }

    tree_node* create_new_node(string email_address) {        
        tree_node* new_node = new tree_node;
        new_node->email_address = email_address;
        new_node->right_child = nullptr;
        new_node->left_child = nullptr;
        return new_node;
    }


    void insert_email(string email_address){
        cout << "inserting " << email_address << endl;
        if (root == nullptr) {
            cout << "root it null :O!" << endl;
            root = create_new_node(email_address);
        } else {
            insert_email(email_address, root);
        }        
    }

    string lookup_email (string email_address) {        
        return lookup_email (email_address, root);
    }

    private:
    tree_node* root;

    void check_node( string email_address, tree_node* child_node){        
        if (child_node == nullptr) {
            cout<< "We are null so lets assign!" << endl;
            child_node = create_new_node(email_address);
            cout << "childnodes email is now " << child_node -> email_address << endl;
        } else {
            insert_email(email_address, child_node);
        }
    }    

    void insert_email(string email_address, tree_node* current_node) {                
        if (current_node != nullptr){            
            if (email_address <=  current_node->email_address){
                cout << "going left" << endl;
                check_node( email_address, current_node->left_child);
                cout << "Has assignment stuck?: " << current_node->left_child->email_address << endl;
            } else {
                cout << "going right" << endl;
                check_node(email_address, current_node->right_child);
            }
        }
        else {
            printf ("inserting email\n");            
            current_node = create_new_node(email_address);                        
        }
    }

    string lookup_email (string email_address, tree_node* current_node) { 
        cout << "looking up " << email_address << endl;
        if (current_node == nullptr) return "Cannot find email address \n";
        cout << "Current node's email address: " << current_node->email_address << endl;
        if (current_node->email_address == email_address) {
            return email_address;
        } else if (email_address <=  current_node->email_address){
            return lookup_email(email_address, current_node->left_child);
        } else {
            return lookup_email(email_address, current_node->right_child);
        }
    }
};

void check_for_email(string email_address, email_tree *my_email_tree){
   string ret = my_email_tree->lookup_email(email_address);
   cout<<endl;
   cout << ret; 
}

int main (void) {    
    logger* new_logger = new logger("test_outputfile");
    email_tree* my_email_tree = new email_tree(new_logger);

    printf("hello world\n");
    string email_address = "whiz60@hotmail.com";
    my_email_tree->insert_email(email_address);
    
    my_email_tree->insert_email("1.c");


    check_for_email(email_address, my_email_tree);
    check_for_email("1.c"  , my_email_tree);

     

}
