#include<bits/stdc++.h>

using namespace std;

struct node{
	int value{0};
	vector<int> items;
};

node knapsack(int W, int S, int index, vector<int> & weight, vector<int> & value, vector<vector<vector<int> > > & dp, vector<vector<vector<vector<int> > > > & items)
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
	
	int val1 = 0;
	int val2 = 0;
	node ans1 = knapsack(W-weight[index],S-1,index+1, weight, value, dp, items);
	node ans2 = knapsack(W, S, index+1, weight, value, dp, items);
	if(W-weight[index]>=0 && S-1>=0)
	{
			val1 = value[index] + ans1.value;
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

	int n;
	cout<<"Please input the number of items:";
	cin>>n;

	vector<int> weight(n,0);
	vector<int> value(n,0);

	cout<<"Please enter the weights of the items:";
	for(int i=0;i<n;i++)cin>>weight[i];
	cout<<"Please enter the corresponding values of the items:";
	for(int i=0;i<n;i++)cin>>value[i];
	
	int W;
	cout<<"Please enter the capacity of the sack:";
	cin>>W;

	int S;
	cout<<"Please enter the no. of slots available:";
	cin>>S;

	vector<vector<vector<int> > > dp(W+1, vector<vector<int> > (S+1,vector<int> (value.size()+1,-1)));
	vector<vector<vector<vector<int> > > > items(W+1, vector<vector<vector<int> > > (S+1, vector<vector<int> > (value.size()+1,{})));
	node ans = knapsack(W, S, 0, weight, value, dp,items);
	cout<<ans.value<<endl;

	for(int i=0;i<ans.items.size();i++)cout<<ans.items[i]<<" ";
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
