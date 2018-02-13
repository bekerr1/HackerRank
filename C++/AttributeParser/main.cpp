//
//  main.cpp
//  cpp_file_factory
//
//  Created by Brendan Kerr on 2/13/18.
//  Copyright © 2018 Brendan Kerr. All rights reserved.
//

#include <iostream>
#include "tag_graph.hpp"

int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        std::cout << "Need to supply file!" << std::endl;
        return 0;
    } else {
        
    }
    
    TagTree t = TagTree();
    t.constructTree();
    t.analyzeTree();
    return 0;
}
