#include <cstdio>
#include<string>
#include<vector>
#include<unordered_set>>
using namespace std;
class solution
{
public:
	solution();
	~solution();
	vector<string> get_same_string(vector<string> s1,vector<string> s2) {
		vector<string> answer;
		unordered_set<string> storage;
		for (int i = 0; i < s1.size(); i++) {
			if (storage.find(s1[i]) == storage.end()) {
				storage.insert(s1[i]);
			}
		}
		for (int i = 0; i < s2.size(); i++) {
			if (storage.find(s2[i]) != storage.end()) {
				answer.push_back(s2[i]);
			}
		}
	}
		
private:

};

solution::solution()
{
}

solution::~solution()
{
}

int main()
{
    printf("hello from helloworld!\n");
    return 0;
}