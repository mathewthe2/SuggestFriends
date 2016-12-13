#include<iostream>
#include<string>
#include<vector>
#include <stdio.h>
#include <string.h>
using namespace std;
class Friend{
  string name;
  vector<string> friends;
public:
  void set_name(string a) { name = a; }
  string get_name()const { return name; }
  void add_friend(string a) {
    friends.push_back(a);
  }
  string get_friend(int i) const { return friends[i]; }
  int friend_list()const { return friends.size(); }
  bool is_friend(string a) {
    for (int i = 0; i < friends.size(); i++)
      if (friends[i] == a) { return true; }
    return false;
  }
  bool suggest(const Friend &a) {
    if (is_friend(a.get_name()))
      return false;
    for (int i = 0; i < friends.size(); i++)
      for (int j = 0; j < a.friend_list(); j++)
        if (friends[i] == a.get_friend(j))
          return true;
    return false;
  }
};

int exist_person(vector<Friend> network, string name) {
  for (int i =0; i < network.size(); i++) {
    if (network[i].get_name() == name)
      return i;
  }
  return -1;
}

vector<Friend> add_friendship(vector<Friend> network, string a_name, string b_name, bool first) {
  int exist_a = exist_person(network, a_name);
  //int exist_b = exist_person(network, b_name);
  if (exist_a < 0) {
    Friend A;
    A.set_name(a_name);
    A.add_friend(b_name);
    network.push_back(A);
  } else {
    network[exist_a].add_friend(b_name);
  }
  return first? add_friendship(network, b_name, a_name, false) : network;
}

bool know_person(vector<Friend> network, string a_name, string b_name) {
  int exist_a = exist_person(network, a_name);
  return (exist_a >= 0)? network[exist_a].is_friend(b_name) : false;
}

bool suggest_friend(vector<Friend> network, string a_name, string b_name){
  int exist_a = exist_person(network, a_name);
  int exist_b = exist_person(network, b_name);
  return (exist_a >= 0 && exist_b >= 0)? network[exist_a].suggest(network[exist_b]) : false;
}


int main(){
  char input[500];
  string a, b;
  vector<Friend> network;
  while (scanf("%s",input)!=EOF) {
    //getline(cin >> ws, input);
    //cin >> input;
    //cin.ignore();
    if (input[0] == 'F') {
        cin >> a >> b;
        network = add_friendship(network, a, b, true);
      }
    if (input[0] == 'S') {
        cin >> a >> b;
        suggest_friend(network, a, b) ? cout << "Yes\n" : cout << "No\n";
      }
    if (input[0] == 'K') {
        cin >> a >> b;
        know_person(network, a, b) ? cout << "Yes\n" : cout << "No\n";
      }
    }

  }
