#include <iostream>
#include <vector>

using namespace std;

template <typename T> void remove_dup( const vector<T>& );

int main()
{

  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(3);
  v.push_back(3);
  v.push_back(4);
  v.push_back(4);
  v.push_back(5);

  remove_dup(v);

  for(int i =0; i<v.size();i++)
    {
      cout << v[i] << endl;
    }
  
  return 0;

}


template <typename T>
void remove_dup( const vector<T>& List )
{

  unsigned count=0;

  for(unsigned i=1; i<List.size();i++)
    {
      if(List[i] == List[i-1])
	{
	  count++;
	}
      else if(List[i] != List[i-1] && count != 0)
	{
	  List[i-count] = List[i];
	}
    }
  if(count != 0)
    {
      List.erase(List.end() - count, List.end());
    }
}

      
