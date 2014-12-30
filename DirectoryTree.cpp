// http://community.topcoder.com/stat?c=problem_statement&pm=1874&rd=4645
// Problem Name:	 DirectoryTree
// Used In:	 SRM 168
// Used As:	 Division I Level Two
// Categories:	 String Manipulation, String Parsing
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

template <class T>
class CompareNode {
	public:
	bool operator()(T *n1, T *n2) {
		return (n1->name.compare(n2->name) > 0);
	}
};
class node {
	public:
	string name;
	priority_queue <node*, vector<node*>, CompareNode<node>> children;
	
	node* insert(string name) {
		node *n;
		
		auto c = this->children;
		while(!c.empty()) {
			n = c.top();
			if(n->name == name) {
				return n;
			}
			c.pop();
		}
				
		n = new node;
		n->name = name;
		this->children.push(n);
		//cout << this->children.top() << endl;
		//cout << this->children.top()->name << endl;
		return n;
	}
};

class DirectoryTree {
	public:
	//node* insert(node *root, string name) {
		//node *n = new node;
		//n->name = name;
		
		//root->children.push(n);
		//cout << root->children.top()->name << endl;
		
		//return root;
	//}
	
	void print(vector<string> result) {
		for(vector<string>::iterator it = result.begin(); it != result.end(); ++it) {
			cout << *it << endl;
		}
	}
	
	void DFS(vector<string> *result, node *n, string s, bool siblings) {
		node *N;
		
		//cout << s << "+-" << n->name << endl;
		// http://stackoverflow.com/questions/662918/how-do-i-concatenate-multiple-c-strings-on-one-line
		stringstream ss;
		ss << s << "+-" << n->name;
		result->push_back(ss.str());
		
		while(!n->children.empty()) {
			N = n->children.top();
			n->children.pop();
			DFS(result, N, s + (siblings ? "| " : "  "), !n->children.empty());
		}
	}
	
	vector<string> display(vector<string> files) {
		node root;
		root.name = "ROOT";
		
		size_t i, j;
		int m, n;
		string dir;
		
		node *N;
		
		for(i = 0; i < files.size(); i++) {
			j = 0;
			N = &root;
			
			while(j != files[i].size()) {
				m = files[i].find('/', j);
				n = files[i].find('/', j+1);
				if(n == -1) n = files[i].size();
				dir = files[i].substr(m + 1, n - m - 1);
				//cout << dir << N->name << endl;
				N = N->insert(dir);
				//cout << dir << N->name << endl;
				//cin.get();
				//cout << m << "-" << n << " = " << dir << " # ";
				j = n;
			}
		}
		
		//cout << root.name << endl;
		
		vector<string> result = {root.name};
		while(!root.children.empty()) {
			N = root.children.top();
			root.children.pop();
			DFS(&result, N, "", !root.children.empty());
		}
		
		print(result);
		
		return result;
	}
};

int main() {
	DirectoryTree d;
	//d.display({"/usr/lib/libc", "/usr/bin/find", "/home/schveiguy/bashrc", "/usr/bin/bash", "/usr/local/bin/ssh"});
	//d.display({"/dir/dir/file", "/dir/file", "/file", "/dir/sharedname/dir", "/dir/dir/sharedname"});
	//d.display({"/a/a/a/a/a/a/a","/a/b/a/a/a/a/a","/a/a/a/a/b/a/a"});
	
	vector<string> answer = {"ROOT", "+-bbdwepuqzecr", "+-byxyixqsdqjouvtjocdhkzjwpjgjkmaskrmfbtfxde", "+-djxumvuygpblkqrtoamgzcbhsibenqwvznxoqtquzbbi", "+-ea", "+-gcpw", "+-itbhmrajgabcsdyg", "+-kbpuwkam", "+-ln", "+-lupymnkslo", "+-plbfuhs", "+-qkqtoculjue", "+-r", "| +-bwintwribcugoosyddr", "| +-cxisylotfxjocojkelthquwfatwqjwcjmywlvhemjnaweew", "| +-db", "| +-dfpdtxamejlryhfjvaxd", "| +-dkhwpseicietopffhzmj", "| +-ezlbejukvqwwbhwtyghfckbpnbqfotkmlj", "| +-geoggchbyggwwrpdrltpcnwdcdqn", "| +-iubsqjgotjgaftpvxasnbgahjxqdattkamdjdnxyss", "| +-iwppyekevgarqtptejsdgpkfvugwznxyffolatqbpkksd", "| +-jimfn", "| +-kyipvyuessvexcmjdgmlhdiloehklrgaoncjxexgtoe", "| +-lumquymokdudljuzgwcuvuffrmmwsv", "| +-lxfavmntqtbgoytxpcxmhbwx", "| +-m", "| +-mpb", "| +-nsrjrgguomuawlug", "| +-oilagmvhmz", "| +-pcyumevaanumnusdxjinoqzkksqqynsmzunrbgkpwiff", "| +-qoh", "| +-sclovvqlcigxiysudcdkjljdftrl", "| +-srciknreegqrbverzswu", "| +-stzrvozudnybtogmo", "| +-tatkptkvbqqcujsqahpvbvbtjknjawlimwtgi", "| +-u", "| +-wbmgoifcfipuqazpqszknztzfksqr", "| +-yxvdqvfzwdevorakhwqqocflzokeyowl", "+-teaaczqrzgaeqgufohyfwockhzfncgwhzqztpoyfzmafvzq", "+-uzqeobuvizabojq", "+-vemduazgugcsnchnhkrail", "+-w", "+-wflsrabq", "+-woahxqucgmanzjhjlrfkgqvwhfljwggdbbzjh", "+-wtbiecz", "+-xfcawcwioucvjtdkmgufxptf", "+-xtemvrku"};
	cout << (d.display({"/bbdwepuqzecr", "/byxyixqsdqjouvtjocdhkzjwpjgjkmaskrmfbtfxde", "/djxumvuygpblkqrtoamgzcbhsibenqwvznxoqtquzbbi", "/ea", "/gcpw", "/itbhmrajgabcsdyg", "/kbpuwkam", "/ln", "/lupymnkslo", "/plbfuhs", "/qkqtoculjue", "/r/bwintwribcugoosyddr", "/r/cxisylotfxjocojkelthquwfatwqjwcjmywlvhemjnaweew", "/r/db", "/r/dfpdtxamejlryhfjvaxd", "/r/dkhwpseicietopffhzmj", "/r/ezlbejukvqwwbhwtyghfckbpnbqfotkmlj", "/r/geoggchbyggwwrpdrltpcnwdcdqn", "/r/iubsqjgotjgaftpvxasnbgahjxqdattkamdjdnxyss", "/r/iwppyekevgarqtptejsdgpkfvugwznxyffolatqbpkksd", "/r/jimfn", "/r/kyipvyuessvexcmjdgmlhdiloehklrgaoncjxexgtoe", "/r/lumquymokdudljuzgwcuvuffrmmwsv", "/r/lxfavmntqtbgoytxpcxmhbwx", "/r/m", "/r/mpb", "/r/nsrjrgguomuawlug", "/r/oilagmvhmz", "/r/pcyumevaanumnusdxjinoqzkksqqynsmzunrbgkpwiff", "/r/qoh", "/r/sclovvqlcigxiysudcdkjljdftrl", "/r/srciknreegqrbverzswu", "/r/stzrvozudnybtogmo", "/r/tatkptkvbqqcujsqahpvbvbtjknjawlimwtgi", "/r/u", "/r/wbmgoifcfipuqazpqszknztzfksqr", "/r/yxvdqvfzwdevorakhwqqocflzokeyowl", "/teaaczqrzgaeqgufohyfwockhzfncgwhzqztpoyfzmafvzq", "/uzqeobuvizabojq", "/vemduazgugcsnchnhkrail", "/w", "/wflsrabq", "/woahxqucgmanzjhjlrfkgqvwhfljwggdbbzjh", "/wtbiecz", "/xfcawcwioucvjtdkmgufxptf", "/xtemvrku"}) == answer) << endl;
}
