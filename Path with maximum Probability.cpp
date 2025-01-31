#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;

class Node {
public:
	int from;
	int to;
	float weight;
	Node() :from(0), to(0), weight(0) {}
	Node(int _from, int _to, float _weight) :from(_from), to(_to), weight(_weight) {}
};
class GraphMST {
private:
	vector<Node> qu;
	vector<int> F;
	vector<int> setStatus;
	float count = 1;
	bool exist(const vector<int>& F, int key) {
		for (int i = 0; i < F.size(); ++i) {
			if (F[i] == key) return true;
		}
		return false;
	}
	int getIndex(int key) {
		for (int i = 0; i < F.size(); ++i) {
			if (F[i] == key) {
				if (setStatus[i] >= 0) {
					key = setStatus[i];
					i = -1;
				}
				else {
					return i;
				}
			}
		}
	}
	void rearrange(int key, int replace) {
		for (int i = 0; i < setStatus.size(); ++i) {
			if (setStatus[i] == key) {
				setStatus[i] = replace;
			}
		}
	}
public:
	GraphMST() {}
	void addEdge(int _from, int _to, float _weight) {
		Node temp;
		temp.from = _from;
		temp.to = _to;
		temp.weight = _weight;
		qu.push_back(temp);
		if (!exist(F, _from)) {
			F.push_back(_from);
			setStatus.push_back(-1);
		}
		if (!exist(F, _to)) {
			F.push_back(_to);
			setStatus.push_back(-1);
		}
	}
	void sortEdge() {
		sort(qu.begin(), qu.end(), [](Node& a, Node& b) { return a.weight > b.weight; });
	}
	void KruskalMST() {
		int a = 0;
		for (int i = 0; i < qu.size(); ++i) {
			int f = getIndex(qu[i].from);
			int t = getIndex(qu[i].to);
			if (a == F.size()) break;
			if (F[f] != F[t]) {
				a++;
				setStatus[f] += setStatus[t];
				setStatus[t] = F[f];
				rearrange(F[t], F[f]);
				count *= qu[i].weight;
			}
		}	
	}
	void print() {
		if (count < 0.05 || count == 1) printf("%d", 0);
		else {
			cout << setprecision(4) << round(count * 10000) / 10000;
		}
	}
};
int main(void) {
	int n = 0;
	cin >> n;
	GraphMST MST;
	string str;
	int from, to;
	float weight;
	for (int i = 0; i < n; ++i) {
		cin >> from >> to >> weight;
		MST.addEdge(from, to, weight);
	}
	MST.sortEdge();
	MST.KruskalMST();
	MST.print();
	return 0;
}
