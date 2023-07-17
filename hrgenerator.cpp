/*----------------------------------------------------------------------------------------
INPUT GENERATOR FOR THE PROBLEM HOCKEY ROADTRIP
Tomas Ferreira - 202006594 - CC:FCUP on behalf of the Competitive Programming class
----------------------------------------------------------------------------------------*/
#include <bits/stdc++.h>

using namespace std;

int consecNumSum(int c){
    int res=0;
    for(int i=1; i<=c; i++)
        res += i;
    return res;
}

int main(){
    int c,r,g;
    srand(time(NULL));
    c = 2+(rand()%73);
    int rec = consecNumSum(c);
    r = c+1+(rand()%(rec-c+1));
    g = 2+(rand()%(c-2));
    map<string,int> clubidx;
    map<int,string> clubacr;
    cout << c << " " << r << " " << g << endl;
    clubidx.insert({"UDO", 0}); clubacr.insert({0, "UDO"});
    for(int i=1; i<=c; i++){
        int cpr = 1+(rand()%5);
        string acr;
        do{
            acr = "";
            acr += 'A'+(rand()%26);
            acr += 'A'+(rand()%26);
            acr += 'A'+(rand()%26);
        } while(acr=="UDO" || clubidx.count(acr)>0);
        clubidx.insert({acr, i});
        clubacr.insert({i, acr});
        cout << acr << " " << cpr << endl;
    }
    bool hasVisited[c+1], setVec=true;
    int access[c+1], ndroads=2*(c+1);
    vector<int> order;
    vector<pair<int,int>> remRoad;
    memset(access, 2, sizeof access);
    bool road[c+1][c+1];
    memset(road, true, sizeof road);
    unsigned seed = 0;
    for(int i=0; i<=c; i++)
        order.push_back(i);
    
    for(int i=0; i<=c; i++)
        road[i][i]=false;

    while(true){
        int cnt=0, i=0; bool flag = true;
        memset(hasVisited, false, sizeof hasVisited);
        shuffle(order.begin(), order.end(), default_random_engine(seed));
        while(true){
            if(c==cnt)
                break;
            if(hasVisited[i]){
                flag=false;
                break;
            }
            hasVisited[i]=true;
            i = order[i];
            cnt++;
        }
        if(flag) break;
    }

    for(int i=0; i<r; i++){
        int id, rn1, rn2, dT=((5+(rand()%500))/5)*5;
        if(ndroads>0){
            rn1 = i;
            rn2 = order[i];
        }
        else{
            if(setVec){
                setVec=false;
                for(int i=0; i<=c; i++){
                    for(int j=0; j<=c; j++){
                        if(road[i][j]){
                            road[i][j] = false;
                            road[j][i] = false;
                            int chance = (rand()%1);
                            if(chance==0)
                                remRoad.push_back({i,j});
                            else
                                remRoad.push_back({j,i});
                        }
                    }
                }
                shuffle(remRoad.begin(), remRoad.end(), default_random_engine(seed));
            }
            id=(rand()%(remRoad.size()-1));
            rn1 = remRoad[id].first;
            rn2 = remRoad[id].second;
            remRoad.erase(remRoad.begin()+id);
        }
        if(access[rn1]>0) ndroads--;
        access[rn1]--;
        if(access[rn2]>0) ndroads--;
        access[rn2]--;

        road[rn1][rn2] = road[rn2][rn1] = false;
        cout << clubacr.find(rn1)->second << " " << clubacr.find(rn2)->second << " " << dT << endl;
    }
    return 0;
}