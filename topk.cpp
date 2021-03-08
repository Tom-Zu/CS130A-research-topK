#include "topk.h"
#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <algorithm> 
#include <stdlib.h>
#include <chrono> 

using namespace std;
using namespace std::chrono; 

topK::topK(int x)
{
    k=x;
    bucket* tmp=new bucket;
    tmp->value=1;
    tmp->next=NULL;
    tmp->prev=NULL;
    tmp->child=NULL;
    first_bucket=tmp;
}

double topK::readinput(string fname)
{
    vector<string> input;
    ifstream data (fname);
    string in;
    if (data.is_open())
    {
        while (getline (data,in))
        {
            input.push_back(in);
        }
    }
    auto start = high_resolution_clock::now();
    for (int i=0; i<input.size(); i++)
    {
        space_saving(input[i]);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    return 1.0*duration.count()/input.size();
}

void topK::space_saving(string in)
{
    if(dictionary.find(in)==dictionary.end())       // element not present in dictionary
    { 
        if(dictionary.size()<k)                     // if dictionary is not filled-up
        { 
            Node *n=initialize(in);                 // create new Nodes and insert into bucket 1
            dictionary[in]= n;                      // update dictionary
        } 
        else                                        //if dictionary is filled-up
        { 
            dictionary.erase(first_bucket->child->ID);     // erase the min element from dictionary
            replace_min(in);                        // replace the min hit element with new element
            dictionary[in]=first_bucket->child;            // update dictionary for new element
            increment_count(first_bucket->child);          // increment count
        } 
    } 
    else                                            // if element is present in dictionary
    { 
        Node* n=dictionary.at(in);                  // get node pointer
        increment_count(n);                         // increment count
        //cout<<n->parent->value<<endl;
    }
}

topK::Node* topK::initialize(string data)
{
    Node *n=new Node;
    n->ID=data;
    n->e=0;
    n->next=NULL;
    n->prev=NULL;
    n->parent=NULL;
    if(this->first_bucket->value==1)
    {
        append_child(this->first_bucket, n);
    }
    else
    {
        bucket* tmp=new bucket;
        tmp->next=first_bucket;
        first_bucket->prev=tmp;
        tmp->prev=NULL;
        tmp->value=1;
        first_bucket=tmp;
        append_child(this->first_bucket, n);
    }
    return n;
}

void topK::append_child(bucket* b, Node *n)
{
    if(b->child==NULL)
    {
        b->child=n;
        n->prev=NULL;
        n->next=NULL;
        n->parent=b;
        return;
    }
    else
    {
        Node* temp=b->child;
        while(temp->next)
        {
            temp=temp->next;
        }
        temp->next=n;
        n->prev=temp;
        n->next=NULL;
        n->parent=b;
    }
}

void topK::increment_count(Node* n)
{
    if(n->parent->next)                                     //if the bucket has a right bucket
    {
        if(n->parent->next->value==n->parent->value+1)      //if the right bucket's value is current +1
        {
            bool x=detach_Node(n);                          //detach node
            append_child(n->parent->next, n);               //put it in the next bucket
            if(x==1)                                        //if preveious bucket is empty, delete it
            {
                remove_bucket(n->parent->prev);
            }
            return;               
        }
    }
                                                            //if the right bucket value is not current+1 or no right bucket exist
    bool x=detach_Node(n);                                  //detach node
    append_bucket(n->parent);                               //create new bucket
    append_child(n->parent->next, n);                       //put node in new bucket
    if(x==1)    
    {   
        remove_bucket(n->parent->prev);                      //if preveious bucket is empty, delete it
    }
}

bool topK::detach_Node(Node* n)
{
    if(n->next&&n->prev)
    {
        n->prev->next=n->next;
        n->next->prev=n->prev;
    }
    else if(n->next)
    {
        n->next->prev=NULL;
        n->parent->child=n->next;
    }
    else if(n->prev)
    {
        n->prev->next=NULL;
    }
    else
    {
        return 1;
    }
    return 0;
}

void topK::remove_bucket(bucket* b)
{
    if(b->next&&b->prev)
    {
        b->prev->next=b->next;
        b->next->prev=b->prev;
        b->child=NULL;
        delete b;
    }
    else if(b->next)
    {
        b->next->prev=NULL;
        first_bucket=b->next;
        b->child=NULL;
        delete b;
    }
    else
    {
        cout<<"something is not right"<<endl;
    }
}

void topK::append_bucket(bucket* b)
{
    if(b->next)                                             // if the current bucket has a next bucket
    {
        bucket* temp1=b->next;                              // insert a bucket in between
        bucket* temp2=new bucket;
        temp2->value=b->value+1;
        b->next=temp2;
        temp2->next=temp1;
        temp2->prev=b;
        temp1->prev=temp2;
        temp2->child=NULL;
    }
    else                                                    // if the current bucket does not have a next bucket
    {
        bucket* tmp=new bucket;                             //append bucket at the end
        tmp->value=b->value+1;
        b->next=tmp;
        tmp->prev=b;
        tmp->next=NULL;
        tmp->child=NULL;
    }
}

void topK::replace_min(string data)
{
    first_bucket->child->ID=data;
    first_bucket->child->e=first_bucket->value;
}

void topK::print()                                             
{
    bucket* temp1=first_bucket;
    vector<tuple<string, int, int>> result;
    while(temp1)
    {
        Node* temp2=temp1->child;
        while(temp2)
        {
            result.push_back(make_tuple(temp2->ID, temp1->value, temp2->e));
            temp2=temp2->next;
        }
        temp1=temp1->next;
    }
    cout<<"----------------------actual output:"<<endl;
    for(int i=k-1; i>=0; i--)
    {
        cout<<"Item: "<<get<0>(result[i])<<" Weight: "<<get<1>(result[i])<<" error margin: "<<get<2>(result[i])<<"\n";
    }
}

void topK::brute_force(string fname)
{
    vector<pair<int, string>> expected;
    ifstream data (fname);
    string in;
    total_element=0;
    if (data.is_open())
    {
        while (getline (data,in))
        {
            total_element++;
            if(actual.find(in)==actual.end())
            {
                actual[in]=1;
            }
            else
            {
                int temp=actual.at(in);
                temp++;
                actual.erase(in);
                actual[in]=temp;
            }
        }
    }
    for (auto& it : actual) 
    { 
        expected.push_back(make_pair(it.second, it.first)); 
    } 
    sort(expected.begin(), expected.end());
    cout<<"----------------------expected output: "<<endl;
    for(int i=expected.size()-1; i>=expected.size()-k; i--)
    {
        cout<<"Item: "<<expected[i].second<<" Weight: "<<expected[i].first<<endl;
    }
    unique_element=expected.size();
}

void topK::analysis()
{
    double total_error=0;
    int miss_count=0;
    int max_error=0;

    for(auto& it : actual)
    {
        if(dictionary.find(it.first)==dictionary.end())
        {
            max_error=max(max_error, it.second);
            total_error+=it.second;
        }
        else
        {
            int error=abs(it.second-dictionary.at(it.first)->parent->value);
            total_error+=error;
            max_error=max(max_error, error);
        }
    }
    double avg_error=total_error/unique_element;
    cout<<"-----------------------analysis:"<<endl;
    cout<<"avg error: "<<avg_error<<" max error: "<<max_error<<endl;
}

int main(int argc, char* argv[])
{
    int x=0;
    string fname=argv[1];
    string temp=argv[2];
    stringstream ss(temp);
    ss>>x;
    topK space_saving{x};
    double avg_time=space_saving.readinput(fname);
    space_saving.print();
    space_saving.brute_force(fname);
    space_saving.analysis();
    cout<<"Average time to process each item is: "<<avg_time<<" nanoseconds."<<endl;
}