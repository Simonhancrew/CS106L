#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <algorithm>
#include <vector>

using std::cout;            using std::endl;
using std::string;          using std::unordered_set;
using std::vector;

unordered_set<string> findWikiLinks(const string& page_html)
{
    unordered_set<string> ans;
    const string link_begin = "<a href=\"/wiki/";
    const int link_begin_length = link_begin.size();
    const string link_end = "\"";
    auto it_begin = page_html.begin(),it_end = page_html.end();
    while(it_begin != it_end) {
        auto tar_begin = std::search(it_begin,it_end,link_begin.begin(),link_begin.end());
        if(tar_begin == it_end) break;
        auto tar_end = std::search(tar_begin + link_begin_length,it_end,link_end.begin(),link_end.end());
        auto page_name = string(tar_begin + link_begin_length,tar_end);
        if(std::all_of(page_name.begin(),page_name.end(),[](char c){ return c != ':' && c != '#'; })) {
            ans.emplace(page_name);
        }
        // " + space
        it_begin = tar_end + 1;
    }
    return ans;
}

string get_page_html(const string& file_name) {
    string page_html,line;
    std::ifstream instrm(file_name,std::ios_base::in);
    while(getline(instrm,line)) {
        page_html.append(line);
    }
    instrm.close();
    return page_html;
}

void save_links(unordered_set<string> &wiki_links,string file_name) {
    string saved_file = "[out]" + file_name;
    std::ofstream ofstrm(saved_file,std::ios::out);
    if(!ofstrm.is_open()) {
        cout << "create file failed\n";
        return;
    }
    bool flag = false;
    for(const auto &key : wiki_links) {
        if(flag) ofstrm << '\n' << key;
        else {
            flag = true;
            ofstrm << key;
        }
//        cout << key << '\n';
    }
    ofstrm.close();
}

int main() {
	
    /* TODO: Write code here! */

    /* Note if your file reading isn't working, please go to the
     * projects tab on the panel on the left, and in the run section,
     * uncheck the "Run in terminal" box and re-check it. This
     * should fix things.
     */
    vector<string> file_names = {"ksound.txt","quokka.txt","simple.txt","simple-invalid.txt","sking.txt"};
    string file_name = "simple-invalid.txt";
//    std::ifstream instrm(file_name,std::ios_base::in);

//    if(!instrm.is_open()) {
//        cout << "fail to open file\n";
//        return 0;
//    }
//    string line,page_html;
//    while(getline(instrm,line)) {
//        page_html.append(line);
//    }

//    instrm.close();
    for(auto &file_name : file_names) {
        string page_html = get_page_html(file_name);

        auto wiki_links = findWikiLinks(page_html);
//    std::ofstream ofstrm(saved_file,std::ios::out);
//    if(!ofstrm.is_open()) {
//        cout << "create file failed\n";
//        return 0;

//    }
//    for(const auto &key : wiki_links) {
//        ofstrm << key << '\n';
//        cout << key << '\n';
//    }
//    ofstrm.close();
        save_links(wiki_links,file_name);
    }
    return 0;
}
