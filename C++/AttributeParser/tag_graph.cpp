//
//  tag_graph.cpp
//
//  Created by Brendan Kerr on 2/13/18.
//  Copyright © 2018 Brendan Kerr. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "tag_graph.hpp"

using namespace std;

void TagTree::constructTree() {
    int line, lines, queries;
    cin >> lines;
    cin >> queries;
    //cout << "Constructing tree with " << lines << " lines and " << queries << " queries!" << "-- starting line: " << line << endl;
    line = 0;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (line < lines) {
        TagNode *leader = new TagNode();
        cout << "Starting..." << endl;
        leader = produceLeaders(0, nullptr, line);
        if (leader) {
            leaders.push_back(leader);
        }
    }
}

// print out text representation of graph
void TagTree::analyzeTree() {
    cout << "Analyzing Tree: " << endl;
    cout << "There are " << leaders.size() << " top level leaders." << endl;
    for (vector<TagNode*>::iterator it = leaders.begin();
         it != leaders.end();
         ++it) {
        cout << "Leader: " << (*it)->info.name << ", and size: " << (*it)->children.size() << endl;
        cout << endl;
        analyzeNode(*it, nullptr);
    }
}

void TagTree::analyzeNode(TagNode *n, TagNode *p) {
    
    string parentData;
    if (p != nullptr) {
        parentData = ", parent name: " + p->info.name;
    } else {
        parentData = ", NO PARENT";
    }
    cout << "Node has name: " << n->info.name << parentData << " and attributes: " << endl;
    for (vector<Attribute>::iterator vitr = n->info.attributes.begin();
         vitr != n->info.attributes.end();
         ++vitr) {
        cout << "Attribute -- Name: " << vitr->name << ", value: " << vitr->value << endl;
    }
    cout << endl;
    for (vector<TagNode*>::iterator itr = n->children.begin();
         itr != n->children.end();
         ++itr) {
        analyzeNode(*itr, n);
        
    }
}

TagNode* TagTree::produceLeaders(int depth, TagNode* node, int &line_num) {
    cout << "Leader: depth- " << depth << ", linenum- " << line_num << endl;
    if (node == nullptr) { // new leader
        node = new TagNode();
    }
    string line;
    getline(cin, line);
    TagNode* next = p.parseLine(line);
    line_num++;
    if (next == nullptr) {
        //return produceLeaders(depth - 1, node, line_num);
        cout << "Leaf" << endl;
        return nullptr;
    } else {
        node = next;
        depth++;
        TagNode* prev;
        while ((prev = produceLeaders(depth, nullptr, line_num)) != nullptr) {
            cout << "Pushing on node at depth " << depth << endl;
            node->children.push_back(prev);
        }
        return node;
    }
}
