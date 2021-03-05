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
    first=tmp;
}

void topK::readinput(string fname)
{
    ifstream data (fname);
    string in;
    if (data.is_open())
    {
        while (getline (data,in))
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
                    dictionary.erase(first->child->ID);     // erase the min element from dictionary
                    replace_min(in);                        // replace the min hit element with new element
                    dictionary[in]=first->child;            // update dictionary for new element
                    increment_count(first->child);          // increment count
                } 
            } 
            else                                            // if element is present in dictionary
            { 
                Node* n=dictionary.at(in);                  // get node pointer
                increment_count(n);                         // increment count
                //cout<<n->parent->value<<endl;
            }
        }
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
    if(this->first->value==1)
    {
        append_child(this->first, n);
    }
    else
    {
        bucket* tmp=new bucket;
        tmp->next=first;
        first->prev=tmp;
        tmp->prev=NULL;
        tmp->value=1;
        first=tmp;
        append_child(this->first, n);
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
            int x=detach_Node(n);                           //detach node
            append_child(n->parent->next, n);               //put it in the next bucket
            if(x==1)                                        //if preveious bucket is empty, delete it
            {
                remove_bucket(n->parent->prev);
            }
            return;               
        }
    }
                                                            //if the right bucket value is not current+1 or no right bucket exist
    int x=detach_Node(n);                                   //detach node
    append_bucket(n->parent);                               //create new bucket
    append_child(n->parent->next, n);                       //put node in new bucket
    if(x==1)    
    {   
        remove_bucket(n->parent->prev);                      //if preveious bucket is empty, delete it
    }
}

int topK::detach_Node(Node* n)
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
        first=b->next;
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
    first->child->ID=data;
    first->child->e=first->value;
}

void topK::print()                                             
{
    bucket* temp1=first;
    while(temp1)
    {
        //cout<<"ID with value of "<<temp1->value<<" : ";
        Node* temp2=temp1->child;
        while(temp2)
        {
            //cout<<"ID: "<<temp2->ID<<" Value: "<<temp1->value<<" error margin: "<<temp2->e<<"\n";
            result.push_back(make_tuple(temp2->ID, temp1->value, temp2->e));
            temp2=temp2->next;
        }
        //cout<<"\n";
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
    vector<pair<int,string>> vect;
    ifstream data (fname);
    string in;
    if (data.is_open())
    {
        while (getline (data,in))
        {
            bool found=0;
            for(int i=0; i<vect.size(); i++)
            {
                if(vect[i].second==in)
                {
                    vect[i].first++;
                    found=1;
                }
            }
            if(!found)
            {
                vect.push_back(make_pair(1,in));
            }
        }
    }
    sort(vect.begin(), vect.end());
    cout<<"----------------------expected output: "<<endl;
    for(int i=vect.size()-k; i<vect.size(); i++)
    {
        //cout<<"Item: "<<vect[i].second<<" Weight: "<<vect[i].first<<endl;
        expected.push_back(vect[i]);
    }
    for(int i=k-1; i>=0; i--)
    {
        cout<<"Item: "<<expected[i].second<<" Weight: "<<expected[i].first<<endl;
    }
    tot=vect.size();
}

void topK::analysis()
{
    double total_error=0;
    int miss_count=0;
    int max_error=0;
    for(int i=0; i<k; i++)
    {
        bool found=0;
        int tmp=0;
        for(int j=0; j<k; j++)
        {
            if(get<0>(result[j])==get<1>(expected[i]))
            {
                found=1;
                //cout<<"found"<<endl;
                tmp=j;
                j=k;
            }
        }
        if(!found)
        {
            total_error+=get<0>(expected[i]);
            miss_count++;
            max_error=max(max_error, get<0>(expected[i]));
        }
        if(found)
        {
            int error=abs(get<0>(expected[i])-get<1>(result[tmp]));
            //cout<<error<<endl;
            total_error+=error;
            max_error=max(max_error, error);
        }
    }
    double avg_error=total_error/tot;
    cout<<"-----------------------analysis:"<<endl;
    cout<<"avg error: "<<avg_error<<" max error: "<<max_error<<endl;
    //cout<<miss_count<<endl;
}

int main(int argc, char* argv[])
{
    int x=0;
    string fname=argv[1];
    string temp=argv[2];
    stringstream ss(temp);
    ss>>x;
    topK space_saving{x};
    auto start = high_resolution_clock::now(); 
    space_saving.readinput(fname);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    space_saving.print();
    space_saving.brute_force(fname);
    space_saving.analysis();
    cout<<"Average time to process each item: "<< duration.count()/1000 << " nanoseconds" << endl;
}