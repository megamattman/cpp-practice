
#include <vector>
#include <iostream>
#include  <fstream>
#include <string>

#define HEREISMYNAME my_logger->write_to_stream(__PRETTY_FUNCTION__);
#define HEREISMYNUMBER my_logger->write_to_stream(__LINE__);
#define HEREIAM my_logger->write_to_stream(__FUNCTION__);

using namespace std;
class logger {
	string outfile;
	ofstream output_stream;
public:

	logger(string out_file) {
		outfile = out_file;
		output_stream.open(outfile);
		write_to_stream("log file");
	}
	~logger() {
		output_stream.close();
	}
	//template <class logType>
	void write_to_stream(string output_string) {		
		output_stream << output_string << endl;		
	}
};


class logged_class {

public:
	logger *my_logger;
	logged_class() {};
	logged_class(logger *new_logger) {
		set_logger(new_logger);
	}
	void set_logger(logger* new_logger) {
		my_logger = new_logger;
	}

};

struct tree_node {
    string email_address;
    tree_node* left_child;
    tree_node* right_child;
};


class email_tree : public logged_class{
    email_tree();


    public:    
    email_tree(logger* new_logger): logged_class(new_logger){        
        root = nullptr;
    }

    email_tree(string* first_email_address, logger* my_logger) : logged_class (my_logger){        
        root = nullptr;
        insert_email(first_email_address, root);
    }

    tree_node* create_new_node(string* email_address) {        
        tree_node* new_node = new tree_node;
        new_node->email_address = *email_address;
        new_node->right_child = nullptr;
        new_node->left_child = nullptr;
        return new_node;
    }

	int insert_email(void* email_address) {
		return 1;
	}

	int insert_email(string *email_address) {		
		if (check_for_valid_email_address(email_address)) return 1;
		cout << "inserting " << email_address << endl;
		if (root == nullptr) {
			root = create_new_node(email_address);
		}
		else {
			insert_email(email_address, root);
		}
		return 0;
	}

	string lookup_email(void* email_address) {
		return "Error in email address \n";
	}

    string lookup_email (string* email_address) {        
		if (check_for_valid_email_address(email_address)) return "Error in email address \n";
        return lookup_email (email_address, root);
    }

    private:
    tree_node* root;

	int check_for_valid_email_address(string* email_address) {
		if (email_address == nullptr) return 1;
		if (email_address->empty()) return 1;
		return 0;
	}

    void check_node( string* email_address, tree_node* child_node){        
        if (child_node == nullptr) {
            cout<< "We are null so lets assign!" << endl;
            child_node = create_new_node(email_address);
            cout << "childnodes email is now " << child_node -> email_address << endl;
        } else {
            insert_email(email_address, child_node);
        }
    }    

    void insert_email(string* email_address, tree_node* current_node) {      		
        if (current_node != nullptr){            
            if (*email_address <=  current_node->email_address){
				if (current_node->left_child == nullptr) {
					current_node->left_child = create_new_node(email_address);
				}
				else {
					insert_email(email_address, current_node->left_child);
				}                
            } else {
				if (current_node->right_child == nullptr) {
					current_node->right_child = create_new_node(email_address);
				}
				else {
					insert_email(email_address, current_node->right_child);
				}
            }
        }
        else {
            printf ("inserting email\n");            
            current_node = create_new_node(email_address);                        
        }
    }

    string lookup_email (string* email_address, tree_node* current_node) { 
        //cout << "looking up " << *email_address << endl;
        if (current_node == nullptr) return "Cannot find email address \n";
        //cout << "Current node's email address: " << current_node->email_address << endl;
        if (current_node->email_address == *email_address) {
            return *email_address;
        } else if (*email_address <=  current_node->email_address){
            return lookup_email(email_address, current_node->left_child);
        } else {
            return lookup_email(email_address, current_node->right_child);
        }
    }
};

class test_case {
public:
	string* my_email_address;
	string my_email_address_rep;
	int exp_insert_res;
	int exp_lookup_res;
	int exp_look_before_insert_res;

	// constructor used to test nullptr as email address
	test_case(email_tree* email_tree_ut, string* email_address, int exp_insert_res_ut = 0, int exp_lookup_res_ut = 0, int exp_look_before_insert_res_ut =1) {
		my_email_address = email_address;
		exp_insert_res = exp_insert_res_ut;
		exp_lookup_res = exp_lookup_res_ut;
		exp_look_before_insert_res = exp_look_before_insert_res_ut;
		my_email_address_rep = "nullptr";
	}

	test_case(email_tree* email_tree_ut, string email_address, int exp_insert_res_ut =0, int exp_lookup_res_ut =0, int exp_look_before_insert_res_ut = 1) {
		my_email_address = new string (email_address);
		exp_insert_res = exp_insert_res_ut;
		exp_lookup_res = exp_lookup_res_ut;
		my_email_address_rep = (email_address.empty()) ? "empty string" : email_address;
		exp_look_before_insert_res = exp_look_before_insert_res_ut;
	}
};


class email_tree_tester {
public:
	
	email_tree* my_email_tree;

	email_tree_tester(email_tree* email_tree_ut) {
		my_email_tree = email_tree_ut;
	}

	void test_case(test_case* case_ut) {
		
		string* email_address_ut;
		string email_address_rep;
		
		email_address_ut  = case_ut->my_email_address;
		email_address_rep = case_ut->my_email_address_rep;

		int ret = test_lookup(case_ut->exp_look_before_insert_res, email_address_ut);
		if (ret) cout << "PASS: test lookup before insert " << email_address_rep << endl;
		else cout << "FAIL: test lookup before insert returned " << ret << " email address: " << email_address_rep << endl;


		ret = test_insert(case_ut->exp_insert_res, email_address_ut);
		if (ret) cout << "PASS: expected result when inserting" << email_address_rep << endl;
		else cout << "FAIL: test insert returned " << ret << " email address: " << email_address_rep << endl;


		ret = test_lookup(case_ut->exp_lookup_res, email_address_ut);
		if (ret) cout << "PASS: expected result when lookingup: " << email_address_rep << endl;
		else cout << "FAIL: test lookup after insert returned " << test_lookup(case_ut->exp_lookup_res, email_address_ut) << " email address: " << email_address_rep << endl;

	}


private:


	int test_lookup(int exp_ret, string* email_address_ut) {
		string ret = my_email_tree->lookup_email(email_address_ut);
		string error_message = "Error in email address \n";
		string missing_message = "Cannot find email address \n";

		// email has error
		if (ret == error_message) return exp_ret == 2;
		// email not found
		if (ret == missing_message) return exp_ret == 1;
		// email found		
		if (ret == *email_address_ut) return exp_ret == 0;
		//Something has gone wrong
		return 3;
	}

	int test_insert(int exp_result, string* email_address_ut) {
		int ret = my_email_tree->insert_email(email_address_ut);
		return ret == exp_result;
	}
};


int main (void) {    
	vector<test_case*> test_cases;
    logger* new_logger = new logger("test_outputfile");
    email_tree* my_email_tree = new email_tree(new_logger);
	email_tree_tester* my_email_tree_tester = new email_tree_tester(my_email_tree);

	test_cases.push_back(new test_case(my_email_tree, "", 1,2,2));
	test_cases.push_back(new test_case(my_email_tree, "1.c"));
	test_cases.push_back(new test_case(my_email_tree, "2.c"));
	test_cases.push_back(new test_case(my_email_tree, "aa.c"));
	test_cases.push_back(new test_case(my_email_tree, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	test_cases.push_back(new test_case(my_email_tree, "22222211231212312"));
	test_cases.push_back(new test_case(my_email_tree, nullptr,1,2,2));
		
	for (auto const& test_case_ut : test_cases) {
		string email_address = test_case_ut->my_email_address_rep;
		cout << email_address << " " <<  endl;
		my_email_tree_tester->test_case(test_case_ut);
	}

	cin.ignore(2);

}
