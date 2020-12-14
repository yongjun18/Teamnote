// author : niklasb
// will maintain upper hull for maximum

const ll is_query = -(1LL<<62);

struct Line {
    ll m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};

struct HullDynamic : public multiset<Line> {
    bool bad(iterator y) {
    	if (y == begin() && next(y) == end()) return 0;
    	if (next(y) == end()) return y->m == prev(y)->m && y->b <= prev(y)->b;
    	if (y == begin()) return y->m == next(y)->m && y->b <= next(y)->b;

    	auto x = prev(y);
    	auto z = next(y);
    	if (x->m == y->m) return y->b <= x->b;
    	if (y->m == z->m) return y->b <= z->b;
    	return (x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m);
    	//return (double)(x->b - y->b)/(y->m - x->m) >= (y->b - z->b)/(z->m - y->m);
    }
    
    void insert_line(ll m, ll b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    
    ll eval(ll x) {
        auto l = *lower_bound((Line) { x, is_query });
        return l.m * x + l.b;
    }
};
