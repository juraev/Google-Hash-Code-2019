#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
class slide{
public:
    int x, y;
    vector<int>tags;
    slide(){
        x=y=-1;
        tags.clear();
    }
};
slide connect(slide a, slide b){
    slide c;
    c.x = a.x;
    c.y = b.x;
    int lst = -1, l = 0, r = 0, q;
    for(int i = a.tags.size() + b.tags.size(); i > 0; i --){
        if(l == a.tags.size())
            q = b.tags[r++];
        else if(r == b.tags.size())
            q = a.tags[l++];
        else if(a.tags[l] < b.tags[r])
            q = a.tags[l++];
        else
            q = b.tags[r++];
        if(q != lst) c.tags.push_back(q);
        lst = q;
    }
    return c;
}
vector<slide>h, v;
int n, m;
map<string, int> mymap;

slide result[300000];
bool used[300000];
int L = 100000, R = 100000;
int getk(slide a, slide b){
    int m=0;
    int u=0,v=0;
    while(u < a.tags.size() && v < b.tags.size()){
        if(a.tags[u] < b.tags[v]){
            u ++;
            continue;
        }
        if(a.tags[u] > b.tags[v]){
            v ++;
            continue;
        }
        m ++;
        u ++;
        v ++;
    }
    return min(
               min(m,(int)a.tags.size() - m),
               (int)b.tags.size() - m);
}
pair<int,int>getmax(slide a){
    int r = 0, x, y, ind;
    x = getk(a, h[r]);

    for(int i = 0; i < 1000; i ++){
        ind = rand() % h.size();
        y=getk(a, h[ind]);
        if(x < y){
            x = y;
            r = ind;
        }
    }
    return make_pair(x, r);
}
void getresult(){
    L = R = 1e5;
    used[0] = true;
    result[L] = h[0];
    pair<int,int>ll, rr;
    long long res = 0;
    int hs = h.size();
    swap(h[0], h[hs-1]);
    h.pop_back();
    for(int i = 1; i < hs; i ++){
        ll = getmax(result[L]);
        rr = getmax(result[R]);
        res += max(ll.first, rr.first);
        if(ll.first > rr.first){
            result[--L] = h[ll.second];
            swap(h[ll.second], h[h.size() - 1]);
            ///used[ll.second] = true;
        }else{
            result[++R] = h[rr.second];
            swap(h[rr.second], h[h.size() - 1]);
            ///used[rr.second] = true;
        }
        h.pop_back();
        if(i % 100 == 0)
            clog << i << endl;
    }
    cout << res << endl;
}
bool tags(slide a, slide b){
    return a.tags.size() < b.tags.size();
}
bool tags1(slide a, slide b){
    return a.tags.size() > b.tags.size();
}
int main(int argc, char *argv[]){
    srand(time(0));
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);
    cin >> n;
    char c;
    slide sl;
    string tag;
    int x, y, tagc = 0;
    for(int i = 0; i < n; i ++){
        cin >> c;
        cin >> x;
        sl.x = i;
        for(int i = 0; i < x; i ++){
            cin >> tag;
            if(mymap[tag]) y = mymap[tag];
            else y = mymap[tag] = ++tagc;
            sl.tags.push_back(y);
        }
        sort(sl.tags.begin(), sl.tags.end());
        if(c == 'H')
            h.push_back(sl);
        else
            v.push_back(sl);
        sl.tags.clear();
    }
    ///random_shuffle(v.begin(), v.end());
    sort(v.begin(),v.end(), tags);
    for(int i = v.size() % 2, j = v.size() - 1; i < j; i ++, j --){
        h.push_back(connect(v[i], v[j]));
    }
    int collll = h.size();
    clog << "Shuffle tugadi" << endl;
    sort(h.begin(), h.end(), tags1);
    getresult();
    clog << "tugadi";
    cout << collll << endl;
    for(int i = L; i <= R; i ++){
        cout << result[i].x;
        if(result[i].y != -1)
            cout << " " << result[i].y;
        cout << endl;
    }

}
