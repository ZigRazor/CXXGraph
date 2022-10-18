#include <time.h>
#include <iostream>
#include <string>
#include <deque>
#include <map>
#include <vector>

using namespace std;

const int NPREF = 2;
const char NONWORD[] = "n";  // cannot appear as real line: we remove newlines
const int MAXGEN = 10000; // maximum words generated

typedef deque<string> Prefix;

map<Prefix, vector<string> > statetab; // prefix -> suffixes

void    build(Prefix&, istream&);
void    generate(int nwords);
void    add(Prefix&, const string&);

// markov main: markov-chain random text generation
int main(void)
{
  int nwords = MAXGEN;
  Prefix prefix; // current input prefix

  srand(time(NULL));
  for (int i = 0; i < NPREF; i++)
    add(prefix, NONWORD);
  build(prefix, cin);
  add(prefix, NONWORD);
  generate(nwords);
  return 0;
}

// build: read input words, build state table
void build(Prefix& prefix, istream& in)
{
  string buf;

  while (in >> buf)
    add(prefix, buf);
}

// add: add word to suffix deque, update prefix
void add(Prefix& prefix, const string& s)
{
  if (prefix.size() == NPREF) {
    statetab[prefix].push_back(s);
    prefix.pop_front();
  }
  prefix.push_back(s);
}

// generate: produce output, one word per line
void generate(int nwords)
{
  Prefix prefix;
  int i;

  for (i = 0; i < NPREF; i++)
    add(prefix, NONWORD);
  for (i = 0; i < nwords; i++) {
    vector<string>& suf = statetab[prefix];
    const string& w = suf[rand() % suf.size()];
    if (w == NONWORD)
      break;
    cout << w << "n";
    prefix.pop_front(); // advance
    prefix.push_back(w);
  }
}
