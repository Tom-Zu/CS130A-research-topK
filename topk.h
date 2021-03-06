#ifndef topk_H
#define topk_H
#include <string>
#include <vector>
#include <unordered_map>

class topK {

    public:
        topK(int k);                                                        // constructor
        void readinput(std::string fname);                                  // read input from file and call private functions to construct data structure
        void print();                                                       // store result in vector for easy analysis
        void brute_force(std::string fname);                                // brute force algorithm to find expected output
        void analysis();                                                    // function to calculate avg_error and max_error
    private:

        struct bucket;

        struct Node {                                                       //struct for child list nodes
            std::string ID;
            int e;
            Node* next;
            Node* prev;
            bucket* parent;
        };

        struct bucket{                                                      //struct for bucket list
            int value;
            bucket* next;
            bucket* prev;
            Node* child;
        };
        std::unordered_map<std::string, int> actual;                        // container for expected result
        Node* initialize(std::string data);                                 // initialize Node when dictionary is not filled-up
        void replace_min(std::string data);                                 // replace min hit element with new element
        void increment_count(Node* n);                                      // increment count of ID
        void append_bucket(bucket* b);                                      // append value at end of bucket list
        void append_child(bucket* b, Node *n);                              // append ID at the end of child list
        bool detach_Node(Node* n);                                          // detach Node from current child list, return 1 if bucket need to be deleted
        void remove_bucket(bucket* b);                                      // remove bucket
        bucket* first_bucket;                                                      // pointer to first bucket
        std::unordered_map<std::string, Node*> dictionary;                  // hash map for elements
        int k;                                                              // max element 
        double total_element;                                                         //total number of unique elements
};

#endif