/*----------------------------------------------------------------------------------------
IMPLEMENTATION OF MY PROBLEM CodeForces Hockey Roadtrip
Tomas Ferreira - 202006594 - CC:FCUP on behalf of the Competitive Programming class
----------------------------------------------------------------------------------------*/
//  Used bases: Maps, Basic Sorting, DFS
//  Complexity: O(nlogn)

#include <bits/stdc++.h>
#define C 101
#define G 10001

using namespace std;

int c,r,xG;
map<int, string> clubAcr;
map<string, int> club;
map<int, int> cpidx;
map<pair<int, int>, int> road;
bool rovis[C][C];
bool hasChanged=false;

struct ROUTE{
    int pavIdx[6] = {0,0,0,0,0,0};
    bool clvis[C] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                       0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    string curpath = "UDO";
    int pG=0, dT=0, compidx=0;
};

vector<ROUTE> rdt;

bool bRDec(ROUTE a, ROUTE b){
    //cout << "Candidate A:\nRoute: " << a.curpath << "\nCompetitive Acc: " << a.compidx << "\nTotal Time: " << a.dT << endl;
    //cout << "Candidate B:\nRoute: " << b.curpath << "\nCompetitive Acc: " << b.compidx << "\nTotal Time: " << b.dT << endl;
    if(b.pG!=xG)
        return true;
    else if(a.pG!=xG)
        return false;
    else{
        if(a.compidx>b.compidx){
            if(a.dT<=b.dT)
                return true;
            else{
                double k = a.dT/5;
                int i = (a.dT-b.dT)/k;
                if(a.compidx-i>b.compidx)
                    return true;
                else if(a.compidx-i<b.compidx)
                    return false;
                else{
                    double aux = a.dT-i*k;
                    if(aux>b.dT)
                        return false;
                    else return true;
                }
            }
        }
        else if(a.compidx<b.compidx){
            if(a.dT>=b.dT)
                return false;
            if(a.dT<=b.dT)
                return true;
            else{
                double k = b.dT/5;
                int i = (b.dT-a.dT)/k;
                if(b.compidx-i>a.compidx)
                    return false;
                else if(b.compidx-i<a.compidx)
                    return true;
                else{
                    double aux = b.dT-i*k;
                    if(aux>a.dT)
                        return true;
                    else
                        return false;
                }
            }
        }
        else{
            if(a.dT<b.dT)
                return true;
            else if(a.dT>b.dT)
                return false;
            else{
                for(int i=5; i>1; i--){
                    if(a.pavIdx[i]>b.pavIdx[i])
                        return true;
                    else if(a.pavIdx[i]<b.pavIdx[i])
                        return false;
                    else continue; 
                }
                return true;
            }
        }
    }
}

void bRFS(ROUTE rt, int cur){
    if(rt.pG==xG)
        rdt.push_back(rt);
    else{
        if(rt.clvis[cur]){
            rt.pavIdx[cpidx.find(cur)->second]++;
            rt.pG++;
            rt.compidx += cpidx.find(cur)->second;
            rt.curpath += " - " + clubAcr.find(cur)->second;
            //cout << rt.curpath << endl;
            rt.clvis[cur] = false;

            if(rt.pG==xG){
                //cout << "Final Candidate: " << rt.curpath << endl;
                rdt.push_back(rt);
                return;
            }
        }

        vector<int> cands;
        for(int i=0; i<=c; i++){
            if(i!=cur){
                if(rovis[cur][i] || rovis[i][cur])
                    cands.push_back(i);
            }
        }

        if(cands.size()==1){
            rovis[cands[0]][cur] = rovis[cur][cands[0]] = false;
            rt.dT += road.find({cands[0], cur})->second;
            bRFS(rt, cands[0]);
            rovis[cands[0]][cur] = rovis[cur][cands[0]] = true;
        }

        else if(cands.size()>1){
            int sz=cands.size();

            for(int i=0; i<sz; i++){
                ROUTE aux = rt;
                rovis[cands[i]][cur] = rovis[cur][cands[i]] = false;
                aux.dT += road.find({cands[i], cur})->second;
                bRFS(aux, cands[i]);
                rovis[cands[i]][cur] = rovis[cur][cands[i]] = true;
            }
        }
        else return;
    }
}

int main(){
    ROUTE rt;
    cin >> c >> r >> xG;
    memset(rovis, false, sizeof rovis);
    clubAcr.insert({0, "UDO"});
    club.insert({"UDO", 0});
    getchar();
    for(int i=1; i<=c; i++){
        int cr;
        string cl, aux;
        getline(cin, cl);
        stringstream claux(cl);
        while(claux >> aux){
            if(aux.size()==1)
                cr = stoi(aux);
            else cl = aux;
        }
        clubAcr.insert({i, cl});
        club.insert({cl, i});
        cpidx.insert({i, cr});
        rt.clvis[i]=true;
    }
    for(int i=1; i<=r; i++){
        int dT;
        string cl, cli, clf, aux;
        getline(cin, cl);
        stringstream claux(cl);
        while(claux >> aux){
            if(cli.size()==0)
                cli = aux;
            else if(clf.size()==0)
                clf = aux;
            else dT = stoi(aux);
        }
        int idI, idF;
        if(cli=="UDO") idI=0;
        else idI = club.find(cli)->second;
        if(clf=="UDO") idF=0;
        else idF = club.find(clf)->second;
        rovis[idI][idF] = rovis[idF][idI] = true;
        road.insert({{idI, idF}, dT});
        road.insert({{idF, idI}, dT});
    }
    bRFS(rt, 0);
    sort(rdt.begin(), rdt.end(), bRDec);
    cout << rdt[0].curpath << endl << "Total Time: " << rdt[0].dT << endl;
    return 0;
}