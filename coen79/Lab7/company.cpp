// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)
// Benjamin Banh <bbanh@scu.edu>

#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    //constructor 
    company::company(const std::string& company_name) : company_name(company_name), head_ptr(NULL), tail_ptr(NULL) {}

    //copy constructor
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);

        list_copy(src.head_ptr, head_ptr, tail_ptr);
    }

    //asignment operator
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);

        if (this != &src){
            list_clear(head_ptr);
            company_name = src.company_name;
            list_copy(src.head_ptr, head_ptr, tail_ptr);
        }
        return *this;
    }
    
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    //inserts a product into a company's linked list of products
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)){
            return false;
        }
        
        if (head_ptr == NULL){
            list_init(head_ptr, tail_ptr, product_name, price);
        }
        else {
            list_tail_insert(tail_ptr, product_name, price);
        }
        
        return true;
    }

    //erases a product from a company's linked list of products
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);

        node* target = list_search(head_ptr, product_name);
        if (target != NULL){
            if (target == head_ptr){
                list_head_remove(head_ptr);
            } 
            else {
                node* prev = head_ptr;
                while (prev->getLink() != target){
                    prev = prev->getLink();
                }
                prev->setLink(target->getLink());
                if (target == tail_ptr){
                    tail_ptr = prev;
                }
                delete target;
            }
            return true;
        }
        return false;

    }
    
    
}
