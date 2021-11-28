class FenwickTree {
	vector<int> ft;
public:
	FenwickTree(int n) { ft.assign(n+1, 0); }

	int getSum(int b) {
		int ret = 0;
		while (b) {
			ret += ft[b]; b -= (b & -b);
		}
		return ret;
	}

	void add(int pos, int val) {
		while (pos < ft.size()) {
			ft[pos] += val; pos += (pos & -pos);
		}
	}

	int getSum(int a, int b) {
		return getSum(b) - getSum(a - 1);
	}
	int getValue(int pos) {
		return getSum(pos) - getSum(pos - 1);
	}
	void setValue(int pos, int val) {
		add(pos, val - getValue(pos));
	}
};