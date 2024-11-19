#include"Bank.h"
#include"lib.h"

int minimumFinder(bank* net, int numBanks){
    int minAmount = INT_MAX,minInd = -1;
    for(int i = 0 ; i < numBanks; i ++){
        if(net[i].netAmount == 0) continue;
        if(net[i].netAmount < minAmount){
            minAmount = net[i].netAmount;
            minInd=i;
        }
    }
    return minInd;
}

int Simple_Max_Index(bank* net, int numBanks){
    int mamoumt = INT_MIN;
    int maxInd = -1;
    for(int i = 0; i < numBanks; i++){
        if(net[i].netAmount == 0)continue;
        if(net[i].netAmount > mamoumt){
            mamoumt = net[i].netAmount;
            maxInd = i;
        }
    }
    return maxInd;
}

pair<string, int> maximumFinder(bank* net, int numBanks, int minIndex, bank* banks, int maxNumtypes){
    int maximumIndex = -1;
    int maxAmount = INT_MIN;
    string str;
    for(int i = 0 ; i < numBanks;i++){
        if(net[i].netAmount == 0)continue;
        if(net[i].netAmount<0)continue;
        vector<string> v(maxNumtypes);
        std::set_intersection(net[minIndex].distinct.begin(), net[minIndex].distinct.end(), net[i].distinct.begin(), net[i].distinct.end(), v.begin());
        if(!v.empty() && maxAmount < net[i].netAmount){
            maxAmount = net[i].netAmount;
            maximumIndex = i;
            str = v[0];
        }
    }
    return make_pair(str, maximumIndex);
}

void Display(vector<vector<pair<int, string>>> ansGraph, int numBanks, unordered_map<string, int> bankIndex, bank* banks, int numTransactions){
    cout<<"The transactions are as follows"<<endl;
    for(int i = 0; i < numBanks;i++){
        for(int j = 0; j < numBanks; j++){
            if(i == j)continue;
            if(ansGraph[i][j].first != 0 && ansGraph[j][i].first!= 0){
                if(ansGraph[i][j].first == ansGraph[j][i].first){
                    ansGraph[i][j].first = 0;
                    ansGraph[j][i].first=0;
                }
                else if(ansGraph[i][j].first>ansGraph[j][i].first){
                    ansGraph[i][j].first -= ansGraph[j][i].first;
                    ansGraph[j][i].first = 0;
                    cout << banks[i].names << " pays " << ansGraph[i][j].first << " to " << banks[j].names << "via" << ansGraph[i][j].second << endl;
                }
                else{
                    ansGraph[j][i].first -= ansGraph[i][j].first;
                    ansGraph[i][j].first = 0;
                    cout << banks[j].names << " pays " << ansGraph[j][i].first << " to " << banks[i].names << "via" << ansGraph[j][i].second << endl;
                }
            }
            else if(ansGraph[i][j].first != 0){
                cout << banks[i].names << " pays " << ansGraph[i][j].first << " to " << banks[j].names << "via" << ansGraph[i][j].second << endl;
            }
            else if(ansGraph[j][i].first != 0){
                cout << banks[j].names << " pays " << ansGraph[j][i].first << " to " << banks[i].names << "via" << ansGraph[j][i].second << endl;
            }
            ansGraph[i][j].first = 0;
            ansGraph[j][i].first = 0;
        }
    }
    cout << "\n";
}

void minimize_cash_flower(vector<vector<int> > graph, int numBanks, bank* banks, int maxNumtypes, unordered_map<string,int> bankIndex, int numTransactions){
    bank* net=new bank[numBanks];
    for(int i=0;i<numBanks;i++){
        net[i].names=banks[i].names;
        net[i].distinct = banks[i].distinct;
    }
    vector<vector<pair<int, string>>> ansGraph(numBanks, vector<pair<int, string>>(numBanks, make_pair(0, " ")));
    int ZeroNetamount = 0;
    while(ZeroNetamount != numBanks){
        int minIndex = minimumFinder(net, numBanks);
        pair<string, int> maximum_Answers = maximumFinder(net, numBanks, minIndex, banks, maxNumtypes);
        int maxIndex = maximum_Answers.second;
        if(maxIndex == -1){
            (ansGraph[minIndex][0].first) += abs(net[minIndex].netAmount);
            ansGraph[minIndex][0].second = *(banks[minIndex].distinct.begin());
            int simMaxInd = Simple_Max_Index(net, numBanks);
            (ansGraph[0][simMaxInd].first) += abs(net[minIndex].netAmount);
            (ansGraph[0][simMaxInd].second) = *(banks[simMaxInd].distinct.begin());
            net[simMaxInd].netAmount += net[minIndex].netAmount;
            net[minIndex].netAmount = 0;
            if(net[simMaxInd].netAmount == 0){
                ZeroNetamount++;
            }
            if(net[simMaxInd].netAmount == 0){
                ZeroNetamount++;
            }
        }
        else{
            int transactionAmount = min(abs(net[minIndex].netAmount), net[maxIndex].netAmount);
            (ansGraph[minIndex][maxIndex].first) += (transactionAmount);
            (ansGraph[minIndex][maxIndex].second) = maximum_Answers.second;
            net[minIndex].netAmount += transactionAmount;
            net[maxIndex].netAmount -= transactionAmount;
            if(net[minIndex].netAmount == 0){
                ZeroNetamount++;
            }
            if(net[maxIndex].netAmount == 0){
                ZeroNetamount++;
            }
        }
    }
    Display(ansGraph, numBanks, bankIndex, banks, numTransactions);
}

int main(){
    int numBanks;
    cin>>numBanks;
    bank* banks=new bank[numBanks];
    unordered_map<string,int> bankIndex;
    cout<<"Enter the names of the banks"<<endl;
    int maxNumtypes;
    for(int i=0;i<numBanks;i++){
        if(i == 0)cout << "world Bank : ";
        else cout << "Bank " << i << " : ";
        cin>>banks[i].names;
        bankIndex[banks[i].names]=i;
        int numtypes;
        cout<<"Enter the number of types of transactions"<<endl;
        cin>>numtypes;
        if(i == 0)maxNumtypes=numtypes;
        cout<<"Enter the types of transactions"<<endl;
        while(numtypes--){
            string temp;
            cin>>temp;
            banks[i].distinct.insert(temp);
        }
    }
    cout<<"Enter the number of transactions"<<endl;
    int numTransactions;
    cin>>numTransactions;
    cout<<"Enter the transactions"<<endl;
    vector<vector<int> > graph(numBanks, vector<int>(numBanks, 0));
    for(int i = 0; i < numTransactions; i++){
        cout<<"Enter the name of the bank and the transaction"<<endl;
        string fromName;
        string toName;
        int amount;
        cin>>fromName>>toName>>amount;
        int fromIndex = bankIndex[fromName];
        int toIndex = bankIndex[toName];
        graph[fromIndex][toIndex] = amount;
    }
    minimize_cash_flower(graph, numBanks, banks, maxNumtypes, bankIndex, numTransactions);
}