//
//  driver.cpp
//  project
//
//  Created by justin baron on 2017-11-15.
//  Copyright © 2017 justin baron. All rights reserved.
//
#include "document_indexer.hpp"
#include "sentence_indexer.hpp"
#include "document_indexer.hpp"
#include "movie_indexer.hpp"
#include "index_exception.hpp"

void runProgram(char i);
void indexing();
void recommender();
void googler();


// ./'program_name' i     i= 1...4 for each assignment
int main(int argc, char *argv[]){
    //runProgram(*argv[1]);
	runProgram('4');
	system("pause");
}


// Assignment 1
void indexing(){
    document_indexer di;
    di.output();
    di.removeStopwords();
    di.output();
}

// Assignment 2
void googler(){
    document_indexer di;
    std::string query = "";
    std::cout << "enter query: ";
    std::getline(std::cin, query);
    
    std::vector<query_result> results = di.query(query,3);
    for(query_result q : results){
        if(q.getScore() != 0)
            std::cout << "Document name: " << q.item->name() << "  score: " << q.getScore() << std::endl;
    }
}

// Assignment 3
void summarizer(){
    sentence_indexer si;
    
    for(std::string query : si.queries)
    {
        std::vector<query_result> results = si.query(query);
        std::cout << "query : " << query << "\n";
        for(query_result q : results){
            std::cout << q.item->content() << std::endl;
        }
        std::cout << "\n\n\n\n";
    }
}

// Assignment 4
void recommender(){
    std::cout << "Loading database...\n\n";
    movie_indexer mi;
    std::string title;
    std::string again = "y";
    std::vector<query_result> results;
    while(again == "y" || again == "Y"){
        std::cout << "Enter a movie title: ";
        std::getline(std::cin, title);
        try{
            results = mi.query(title);
            for(query_result q : results){
                movie * mpt = dynamic_cast<movie*>(q.item);
                std::cout << *mpt;
            }
        }
        catch(index_exception e){
            std::cout << e.what() << std::endl;
        }
        
        std::cout << "\n\nwould you like to search another movie: (y or n): ";
        std::getline(std::cin, again);
    }
}

void runProgram(char i){
    if(i == '1')
        indexing();
    else if(i == '2')
        googler();
    else if(i == '3')
        summarizer();
    else if(i == '4')
        recommender();
    else{
        std::cout << "this program does not exist\0";
    }
}
