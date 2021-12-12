//https://contest.yandex.ru/contest/27844/problems/J/

#include "funcs.h"
#include <bits/stdc++.h>

std::vector<int>::const_iterator * getNextMergeValue(
        const std::vector<int> & line1,
        const std::vector<int> & line2,
        std::vector<int>::const_iterator & l1,
        std::vector<int>::const_iterator & l2){

    if(l1 == line1.end()) return &l2;
    if(l2 == line2.end()) return &l1;
    if(*l1 <= *l2)
        return &l1;
    else
        return &l2;
}

int leftMedian(const std::vector<int> & line1,
               const std::vector<int> & line2){
    auto l1 = line1.begin(), l2 = line2.begin();
    int len = line1.size() - 1;
    for(int i = 0; i < len; ++i){
        getNextMergeValue(line1,line2,l1,l2)->operator++();
    }
    return **getNextMergeValue(line1,line2,l1,l2);
}

void parseFile(std::istream & input, std::ostream & output){

    int n, l;
    input >> n >> l;

    std::vector<std::vector<int>> lines(n,std::vector<int>(l));
    for(auto & line : lines){
        std::copy_n(std::istream_iterator<unsigned long long >(input), l, line.begin());
    }

    std::list<int> ans;

    for(int i = 0; i<lines.size(); ++i){
        for(int j = i+1; j<lines.size(); ++j){
            ans.push_back(leftMedian(lines[i], lines[j]));
        }
    }

    std::copy(ans.begin(), ans.end(),
              std::ostream_iterator<int>(output, "\n"));
}
