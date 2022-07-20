
#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>
#include <unordered_map>
#include "wikiscraper.h"
#include <fstream>

using std::cout;            using std::endl;
using std::string;          using std::vector;
using std::priority_queue;  using std::unordered_map;
using std::unordered_set;


/*
 * This is the function you will be implementing. It takes
 * two string representing the names of a start_page and
 * end_page and is supposed to return a ladder, represented
 * as a vector<string>, of links that can be followed from
 * start_page to get to the end_page.
 *
 * For the purposes of this algorithm, the "name" of a Wikipedia
 * page is what shows at the end of the URL when you visit that page
 * in your web browser. For ex. the name of the Stanford University
 * Wikipedia page is "Stanford_University" since the URL that shows
 * in your browser when you visit this page is:
 *
 *       https://en.wikipedia.org/wiki/Stanford_University
 */

vector<string> findWikiLadder(const string& start_page, const string& end_page) {
    // TODO: Fill in the findWikiLinks method in wikiscraper.cpp,
    //       then write this  function as per the handout.
    //
    //                Best of luck!
   WikiScraper scraper;

   unordered_set<string> visited_page{start_page};
   unordered_set<string> target_links = scraper.getLinkSet(end_page);

   auto func = [&](vector<string> &lhs,vector<string> &rhs) {
        int cnt1 = 0,cnt2 = 0;
        unordered_set<string> lhs_links = scraper.getLinkSet(lhs.back());
        unordered_set<string> rhs_links = scraper.getLinkSet(rhs.back());
        for(string const &s : target_links) {
            if(lhs_links.count(s) != 0){
                ++cnt1;
            }
            if(rhs_links.count(s) != 0) {
                ++cnt2;
            }
        }
        return cnt1 <  cnt2;
   };

   priority_queue<vector<string>,vector<vector<string>>,decltype(func)> heap(func);
   heap.push(vector<string> {start_page});

   while(!heap.empty()) {
       auto cur_ladder = heap.top();
       heap.pop();
       unordered_set<string> ne_links = scraper.getLinkSet(cur_ladder.back());
       for(auto link : cur_ladder) {
           cout << link << "->";
       }
       cout << '\n';
       if(ne_links.count(end_page) != 0) {
           cur_ladder.push_back(end_page);
           return cur_ladder;
       }
       int cnt = 0;
       for(string const &ne_link : ne_links) {
            if(visited_page.count(ne_link) != 0) {
                continue;
            }
            if(cnt > 30) break;
            ++cnt;
            cout << "add link:" << ne_link << '\n';
            visited_page.insert(ne_link);
            vector<string> new_ladder(cur_ladder);
            new_ladder.push_back(ne_link);
            heap.push(new_ladder);
       }
   }

   return vector<string> {};
}



int main() {
    auto ladder = findWikiLadder("Albert_Einstein", "Scientology");
    cout << endl;
    std::ofstream ofstrm("record.txt",std::ios::out);
    if(!ofstrm.is_open()) {
        cout << "record cant create\n";
    }
    if(ladder.empty()) {
        cout << "No ladder found!" << endl;
    } else {
        cout << "Ladder found:" << endl;
        cout << "\t";
        for(size_t i = 0;i < ladder.size() - 1;i++) {
            cout << ladder[i] << "->";
            ofstrm << ladder[i] << "->";
        }
        cout << ladder.back() << '\n';
        ofstrm << ladder.back() << '\n';
        // Print the ladder here!
    }
    return 0;
}




