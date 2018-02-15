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

TagNode* TagGraph::produceLeaders(int depth, TagNode* node, int &line_num, istream &source) {
    if (node == nullptr) { // new leader
        node = new TagNode();
    }
    string line;
    getline(source, line);
    TagNode* next = p.parseLine(line);
    line_num++;
    if (next == nullptr) {
        return nullptr;
    } else {
        node = next;
        depth++;
        TagNode* prev;
        while ((prev = produceLeaders(depth, nullptr, line_num, source)) != nullptr) {
            node->children[prev->info.name] = prev;
        }
        return node;
    }
}

void TagGraph::constructGraph(istream &source) {
    int line, lines, queries;
    source >> lines;
    source >> queries;
    line = 0;
    source.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (line < lines) {
        TagNode *leader = new TagNode();
        leader = produceLeaders(0, nullptr, line, source);
        if (leader) {
            leaders[leader->info.name] = leader;
        }
    }
    string query;
    for (int i = 0; i < queries; i++) {
        getline(cin, query);
        cout << p.parseQuery(leaders, query) << endl;
    }
}

// print out text representation of graph
void TagGraph::analyzeGraph() {
    cout << "Analyzing Graph: " << endl;
    cout << "There are " << leaders.size() << " top level leaders." << endl;
    for (map<string, TagNode*>::iterator it = leaders.begin();
         it != leaders.end();
         ++it) {
        cout << "Leader: " << it->first << ", and size: " << it->second->children.size() << endl;
        cout << endl;
        analyzeNode(it->second, nullptr);
    }
}

void TagGraph::analyzeNode(TagNode *n, TagNode *p) {
    string parentData;
    if (p != nullptr) {
        parentData = ", parent name: " + p->info.name;
    } else {
        parentData = ", NO PARENT";
    }
    cout << "Node has name: " << n->info.name << parentData << " and attributes: " << endl;
    for (map<string, string>::iterator mitr = n->info.attributes.begin();
         mitr != n->info.attributes.end();
         ++mitr) {
        cout << "Attribute -- Name: " << mitr->first << ", value: " << mitr->second << endl;
    }
    cout << endl;
    for (map<string, TagNode *>::iterator itr = n->children.begin();
         itr != n->children.end();
         ++itr) {
        analyzeNode(itr->second, n);
    }
}
