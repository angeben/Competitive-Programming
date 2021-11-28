class SegmentTree {
	vector<int> st;
	vector<int> lazy;
	int tam; // Numero de hojas que manejamos
public:
	// Tamano maximo que podremos guardar
	// (numero de hojas).
	// Antes de las consultas, se necesita rellenar
	// con los datos iniciales usando build().
	SegmentTree(int maxN) {
		st.assign(4 * maxN + 10, 0);
		lazy.assign(4 * maxN + 10, 0);
	}

	int query(int a, int b) {
		return query(1, 0, tam - 1, a, b);
	}
	int query(int vertex, int L, int R, int i, int j) {
		pushLazyUpdate(vertex, L, R);
		if ((j < L) || (R < i))
			return 0;
		if (i <= L && R <= j)
			return st[vertex];
		int mitad = (L + R) / 2;
		return query(2 * vertex, L, mitad, i, j) +
			query(2 * vertex + 1, mitad + 1, R, i, j);
	}

	void updateRange(int a, int b, int op) {
		updateRange(1, 0, tam - 1, a, b, op);
	}

	void updateRange(int vertex, int L, int R, int a, int b, int op) {
		// Resolvemos posibles operaciones pendientes
		pushLazyUpdate(vertex, L, R);
		if ((b < L) || (R < a)) return;
		// ¿Intervalo afectado por completo?
		if ((a <= L) && (R <= b)) {
			// Nos aplicamos la operacion y propagamos la
			// pereza a los hijos. Para evitar copiar/pegar,
			// lo hacemos aplicandonos la pereza, y luego
			// resolviendola
			setLazyUpdate(vertex, op);
			pushLazyUpdate(vertex, L, R);
			return;
		}
		// Intervalo no afectado por completo. No podemos
		// ser perezosos. Aplicamos la operacion en
		// los hijos
		int m = (L + R) / 2;
		updateRange(2 * vertex, L, m, a, b, op);
		updateRange(2 * vertex + 1, m + 1, R, a, b, op);
		// Combinamos
		st[vertex] = st[2 * vertex] + st[2 * vertex + 1];
	}

	void setLazyUpdate(int vertex, int value) {
		// Mezclamos
		// Importante +=: el nodo podria tener
		// otras operaciones pendientes anteriores
		lazy[vertex] += value;
	}

	void pushLazyUpdate(int vertex, int L, int R) {
		st[vertex] += (R - L + 1)*lazy[vertex];
		if (L != R) {
			// Tenemos hijos
			int m = (L + R) / 2;
			setLazyUpdate(2 * vertex, lazy[vertex]);
			setLazyUpdate(2 * vertex + 1, lazy[vertex]);
		}
		lazy[vertex] = 0;
	}

	void build(int* values, int n) {
		tam = n;
		build(values, 1, 0, n - 1);
	}

	void build(int* values, int p, int l, int r) {
		if (l == r) {
			st[p] = values[l];
			return;
		}
		int m = (l + r) / 2;
		build(values, 2 * p, l, m);
		build(values, 2 * p + 1, m + 1, r);
		st[p] = st[2 * p] + st[2 * p + 1];
	}
};