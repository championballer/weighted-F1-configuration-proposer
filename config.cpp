#include<bits/stdc++.h>
#include<fstream>
#include<sstream>

#define A 33
#define B 12
#define P 33
#define H 12
#define L 21
#define W_ 34
#define S_ 10
#define INPUT_FILE "./parts.txt"
#define OUTPUT_FILE "./possible_configurations.txt"
using namespace std;

struct node{
	int value{0};
	vector<int> items;
};

int diff(int a = A, int b = B, int p = P, int h = H, int l = L)
{
	int v1 = abs(a-b);
	int v2 = abs(a-p);
	int v3 = abs(a-h);
	int v4 = abs(a-l);
	int v5 = abs(b-p);
	int v6 = abs(b-h);
	int v7 = abs(b-l);
	int v8 = abs(p-h);
	int v9 = abs(p-l);
	int v10 = abs(h-l);
	return v1+v2+v3+v4+v5+v6+v7+v8+v9+v10; 
}

int calculate_value(int index,vector<int>& aero, vector<int> & brakes, vector<int> & power, vector<int> & handling, vector<int> & lightweight, int a = A, int b = B, int p = P, int h = H, int l = L)
{
	return a*aero[index]+b*brakes[index]+p*power[index]+h*handling[index]+l*lightweight[index]-diff();
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
	//TODO: Optimise by removing memoization in favour of dp
	//TODO: Optimise for space in case of item printing
	//TODO: Work on the balancing factor and the weighting mechanism

	int W = W_; 
	int S = S_;
	vector<int> weight;
	vector<int> value;
	vector<int> aero;
	vector<int> brakes;
	vector<int> power;
	vector<int> handling;
	vector<int> lightweight;
	vector<string> names;
	

	ifstream inputfile;
	inputfile.open(INPUT_FILE);

	if(!inputfile)
	{
		cout<<"Input file not available, please check for availability"<<endl;
		return -1;
	}

	else
	{
		string line;
		while(getline(inputfile, line))
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

	inputfile.close();

	vector<vector<vector<int> > > dp(W+1, vector<vector<int> > (S+1,vector<int> (value.size()+1,-1)));
	vector<vector<vector<vector<int> > > > items(W+1, vector<vector<vector<int> > > (S+1, vector<vector<int> > (value.size()+1,{})));
	
	node ans = knapsack(W, S, 0, weight, value,aero, brakes, power, handling, lightweight, dp,items);
	
	int final_value = 0;
	int final_aero = 0;
	int final_brakes = 0;
	int final_power = 0;
	int final_handling = 0;
	int final_lightweight = 0;
	for(int i=0;i<ans.items.size();i++)
	{
		cout<<names[ans.items[i]]<<" ";
		final_value+=value[ans.items[i]];
		final_aero+=aero[ans.items[i]];
		final_brakes+=brakes[ans.items[i]];
		final_power+=power[ans.items[i]];
		final_handling+=handling[ans.items[i]];
		final_lightweight+=lightweight[ans.items[i]];
	}
	cout<<endl;
	
	cout<<"Total:"<<final_value<<endl;
	cout<<"Aero:"<<final_aero<<endl;
	cout<<"Brakes:"<<final_brakes<<endl;
	cout<<"Power:"<<final_power<<endl;
	cout<<"Handling:"<<final_handling<<endl;
	cout<<"Lightweight:"<<final_lightweight<<endl;
	
	ofstream outputfile;
	outputfile.open(OUTPUT_FILE, ios::app);

	if(!outputfile.is_open())
	{
		cout<<"Output file could not be successfully opened, please check for possible issues:"<<endl;
		return -1;
	}

	outputfile<<"W:"<<W_<<" S:"<<S_<<" A:"<<A<<" B:"<<B<<" P:"<<P<<" H:"<<H<<" L:"<<L<<endl;
	outputfile<<"Total:"<<final_value<<endl;
	outputfile<<"Aero:"<<final_aero<<endl;
	outputfile<<"Brakes:"<<final_brakes<<endl;
	outputfile<<"Power:"<<final_power<<endl;
	outputfile<<"Handling:"<<final_handling<<endl;
	outputfile<<"Lightweight:"<<final_lightweight<<endl;
	outputfile<<"Parts to include : ";
	for(int i=0;i<ans.items.size();i++)
	{
		outputfile<<names[ans.items[i]]<<" ";
	}
	outputfile<<endl;
	outputfile<<"------------------------------------------------------------------------"<<endl;
	outputfile.close();


}
