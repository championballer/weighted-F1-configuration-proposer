#include<bits/stdc++.h>

using namespace std;

int knapsack(int W, int index, vector<int> & weight, vector<int> & value, vector<vector<int> > & dp)
{
	if(index == weight.size())return 0;
	if(W<=0)return 0;
	
	int val1 = 0;
	int val2 = 0;
	if(W-weight[index]>=0)val1 = value[index] + knapsack(W-weight[index], index+1, weight, value, dp);
	
	val2 = knapsack(W, index+1, weight, value, dp);

	dp[W][index] = max(val1, val2);
	return dp[W][index];
}

int main()
{
	//TODO:Print the involved items in the sack
	//TODO:Adapt to work with the game

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

	vector<vector<int> > dp(W+1, vector<int> (value.size()+1,-1));

	cout<<knapsack(W, 0, weight, value, dp)<<endl;

	// for(int i=0;i<dp.size();i++)
	// {
	// 	for(int j=0;j<dp[0].size();j++)cout<<dp[i][j]<<" ";
	// 	cout<<endl;
	// }
}