#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>

using namespace std;

struct Cmp {
    bool operator ()(const pair<int,set<string>> &a, const pair<int,set<string>> &b)
    {
        return a.first > b.first || (a.first == b.first && a.second < b.second);
    }
};


vector<set<string>> DBInput(){
    string line;
    vector<set<string>> db;
    
    while (getline(cin, line))
    {
        string s;
        set<string> result;
        istringstream iss(line);
        
        while(iss >> s)
            result.insert(s);
        
        db.push_back(result);
    }
    return db;
}

void DBPrint(const vector<set<string>> db){
    for(int i = 0; i < db.size(); i++){
        for(auto it = db[i].begin(); it != db[i].end(); it++)
            cout << *it << ",";
        cout << endl;
    }
}


int main() {
    string str;
    getline(cin, str);
    int minSup = stoi(str);
    
    vector<set<string>> db = DBInput();
    
    map<set<string>, int> supportMap;
    set<set<string>> candidateItemSets;
    vector<set<set<string>>> frequentItemSets;
    
    for(int i = 0; i < db.size(); i++){
        for(auto it = db[i].begin(); it != db[i].end(); it++){
            set<string> currItemSet;
            currItemSet.insert(*it);
            
            supportMap[currItemSet]++;
            candidateItemSets.insert(currItemSet);
        }
    }
    
    for (auto it = candidateItemSets.begin(); it != candidateItemSets.end(); it++) {
        if(supportMap[*it] < minSup)
            candidateItemSets.erase(*it);
    }
    
    frequentItemSets.push_back(candidateItemSets);
    
    while(!candidateItemSets.empty()){
        set<set<string>> tempItemSets;
        
        for(auto it = candidateItemSets.begin(); it != candidateItemSets.end(); it++){
            auto it2 = it;
            advance(it2, 1);
            for(it2; it2 != candidateItemSets.end(); it2++){
                set<string> temp1 = *it;
                set<string> temp2 = *it2;
                temp1.insert(temp2.begin(), temp2.end());
                
                if(temp1.size() == temp2.size() + 1)
                    tempItemSets.insert(temp1);
            }
        }
        
        for(int i = 0; i < db.size(); i++){
            for(auto it = tempItemSets.begin(); it != tempItemSets.end(); it++){
                set<string> temp = *it;
                if(includes(db[i].begin(), db[i].end(), temp.begin(), temp.end()))
                    supportMap[*it]++;
            }
        }
        
        for (auto it = tempItemSets.begin(); it != tempItemSets.end(); it++) {
            if(supportMap[*it] < minSup)
                tempItemSets.erase(*it);
        }
        
        candidateItemSets = tempItemSets;
        frequentItemSets.push_back(candidateItemSets);
    }
    
    set<pair<int,set<string>>, Cmp> outputSet;
    
    for(int i = 0; i < frequentItemSets.size(); i++){
        for(auto it = frequentItemSets[i].begin(); it != frequentItemSets[i].end(); it++){
            pair<int, set<string>> temp(supportMap[*it],*it);
            outputSet.insert(temp);
        }
    }
    
    for(auto it = outputSet.begin(); it != outputSet.end(); it++){
        pair<int, set<string>> temp = *it;
        cout << temp.first << " [";
        auto sit = temp.second.begin();
        auto end = temp.second.end();
        advance(end, -1);
        for(sit; sit != end; sit++)
            cout << *sit << " ";
        cout << *sit << "]" << endl;
    }
    
    cout << endl;
    
    set<pair<int,set<string>>, Cmp> closedOutputSet, maxOutputSet;
    
    closedOutputSet = outputSet;
    maxOutputSet = outputSet;
    for(auto it = closedOutputSet.begin(); it != closedOutputSet.end(); it++){
        for(auto it2 = closedOutputSet.begin(); it2 != closedOutputSet.end(); it2++){
            if(it != it2){
                pair<int,set<string>> temp1 = *it;
                pair<int,set<string>> temp2 = *it2;
                if(includes(temp1.second.begin(), temp1.second.end(), temp2.second.begin(), temp2.second.end())){
                    maxOutputSet.erase(*it2);
                    if(supportMap[temp1.second] == supportMap[temp2.second])
                        closedOutputSet.erase(*it2);
                }
            }
        }
    }
    
    for(auto it = closedOutputSet.begin(); it != closedOutputSet.end(); it++){
        pair<int, set<string>> temp = *it;
        cout << temp.first << " [";
        auto sit = temp.second.begin();
        auto end = temp.second.end();
        advance(end, -1);
        for(sit; sit != end; sit++)
            cout << *sit << " ";
        cout << *sit << "]" << endl;
    }
    
    cout << endl;
    
    for(auto it = maxOutputSet.begin(); it != maxOutputSet.end(); it++){
        pair<int, set<string>> temp = *it;
        cout << temp.first << " [";
        auto sit = temp.second.begin();
        auto end = temp.second.end();
        advance(end, -1);
        for(sit; sit != end; sit++)
            cout << *sit << " ";
        cout << *sit << "]" << endl;
    }
    
    return 420;
}
