#include<bits/stdc++.h>
#include<fstream>
#include<sstream>

#define A 1
#define B 1
#define P 1
#define H 1
#define L 1

using namespace std;

struct node{
	int value{0};
	vector<int> items;
};

int calculate_value(int index,vector<int>& aero, vector<int> & brakes, vector<int> & power, vector<int> & handling, vector<int> & lightweight, int a = A, int b = B, int p = P, int h = H, int l = L)
{
	return a*aero[index]+b*brakes[index]+p*power[index]+h*handling[index]+l*lightweight[index];
}

node knapsack(int W, int S, int index, vector<int> & weight, vector<int> & value, vector<int> & aero, vector<int> & brakes, vector<int> & power, vector<int> & handling, vector<int> & lightweight, vector<vector<vector<int> > > & dp, vector<vector<vector<vector<int> > > > & items)
{
	if(index == weight.size())
	{
		node ans;
		return ans;
	}
		
	if(W<=0)
	{
		node ans;
		return ans;
	}

	if(S<=0)
	{
		node ans;
		return ans;
	}

	if(dp[W][S][index]!=-1)
	{
		node ans;
		ans.value = dp[W][S][index];
		ans.items = items[W][S][index];
		return ans;
	}
	
	int val1 = 0;
	int val2 = 0;
	node ans1 = knapsack(W-weight[index],S-1,index+1, weight, value, aero, brakes, power, handling, lightweight, dp, items);
	node ans2 = knapsack(W, S, index+1, weight, value,aero, brakes, power, handling, lightweight, dp, items);
	if(W-weight[index]>=0 && S-1>=0)
	{
			val1 = calculate_value(index,aero,brakes,power,handling, lightweight) + ans1.value;
	}
	val2 = ans2.value;

	dp[W][S][index] = max(val1, val2);
	if(val1>val2)
	{
		items[W][S][index].push_back(index);
		for(int i=0;i<ans1.items.size();i++)items[W][S][index].push_back(ans1.items[i]);
		
	}

	else
	{
		for(int i=0;i<ans2.items.size();i++)items[W][S][index].push_back(ans2.items[i]);
	}
	node ans;
	ans.value = dp[W][S][index];
	ans.items = items[W][S][index];
	return ans;
}

int main()
{
	//TODO: Adapt to work with the game
	//TODO: Optimise by removing memoization in favour of dp
	//TODO: Optimise for space in case of item printing
	//TODO: Maximising parameters, initially for complete value, and then individual features of the car


	int W;
	cout<<"Please enter the capacity of the sack:";
	cin>>W;

	int S;
	cout<<"Please enter the no. of slots available:";
	cin>>S;

	vector<int> weight;
	vector<int> value;
	vector<int> aero;
	vector<int> brakes;
	vector<int> power;
	vector<int> handling;
	vector<int> lightweight;
	vector<string> names;
	ifstream myfile;
	myfile.open("./parts.txt");

	if(!myfile)
	{
		return -1;
	}

	else
	{
		string line;
		while(getline(myfile, line))
		{
			string name_of_part;
			int total_value;
			int aero_;
			int brakes_;
			int power_;
			int handling_;
			int lightweight_;
			int weight_of_part;
			istringstream mystream(line);
			while(mystream>>name_of_part>>total_value>>aero_>>brakes_>>power_>>handling_>>lightweight_>>weight_of_part)
			{
				cout<<name_of_part<<" "<<total_value<<" "<<aero_<<" "<<brakes_<<" "<<power_<<" "<<handling_<<" "<<lightweight_<<" "<<weight_of_part<<endl;
				names.push_back(name_of_part);
				value.push_back(total_value);
				weight.push_back(weight_of_part);
				aero.push_back(aero_);
				brakes.push_back(brakes_);
				power.push_back(power_);
				handling.push_back(handling_);
				lightweight.push_back(lightweight_);
			}
		}
	}

	vector<vector<vector<int> > > dp(W+1, vector<vector<int> > (S+1,vector<int> (value.size()+1,-1)));
	vector<vector<vector<vector<int> > > > items(W+1, vector<vector<vector<int> > > (S+1, vector<vector<int> > (value.size()+1,{})));
	node ans = knapsack(W, S, 0, weight, value,aero, brakes, power, handling, lightweight, dp,items);
	cout<<ans.value<<endl;

	for(int i=0;i<ans.items.size();i++)cout<<names[ans.items[i]]<<" ";
	cout<<endl;
	// for(int i=0;i<dp.size();i++)
	// {
	// 	for(int j=0;j<dp[0].size();j++)
	// 	{
	// 		for(int k=0;k<dp[0][0].size();k++)cout<<dp[i][j][k]<<" ";
	// 			cout<<endl;
	// 	}
	// 	cout<<endl;
	// }
}
