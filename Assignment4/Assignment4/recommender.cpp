//
//  recommender.cpp
//  project
//
//  Created by justin baron on 2017-11-12.
//  Copyright © 2017 justin baron. All rights reserved.
//

#include "movie_indexer.hpp"
#include "query_result.hpp"
#include "indexer.hpp"
#include <map>
#include <iostream>

//int main(){
//    std::cout << "Loading database...\n\n";
//    movie_indexer mi;
//    std::string title;
//    std::string again = "y";
//    while(again == "y" || again == "Y"){
//        std::cout << "Enter a movie title: ";
//        std::getline(std::cin, title);
//        std::vector<query_result> results = mi.query(title);
//        for(query_result q : results){
//            movie * mpt = dynamic_cast<movie*>(q.item);
//            std::cout << *mpt;
//        }
//        std::cout << "\n\nwould you like to search another movie: (y or n): ";
//        std::getline(std::cin, again);
//    }
//    
//}

