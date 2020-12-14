int n, m;
ll arr[1030][1030];
ll tree[4200][4200];

void build_y(int xno, int xnl, int xnr, int yno, int ynl, int ynr){
	if(ynl+1 == ynr){
		if(xnl+1 == xnr) tree[xno][yno] = arr[xnl][ynl];
		else tree[xno][yno] = tree[2*xno][yno] + tree[2*xno+1][yno];
		return;
	}
	int mid = (ynl+ynr)/2;
	build_y(xno, xnl, xnr, 2*yno, ynl, mid);
	build_y(xno, xnl, xnr, 2*yno+1, mid, ynr);
	tree[xno][yno] = tree[xno][2*yno] + tree[xno][2*yno+1];
}
void build_x(int xno, int xnl, int xnr){
	if(xnl+1 == xnr){
		build_y(xno, xnl, xnr, 1, 0, m);
		return;
	}
	int mid = (xnl+xnr)/2;
	build_x(2*xno, xnl, mid);
	build_x(2*xno+1, mid, xnr);
	build_y(xno, xnl, xnr, 1, 0, m);
}
void build(){ build_x(1, 0, n); }

// 2차원 구간 [xl, xr) [yl, yr) 쿼리
ll query_y(int yl, int yr, int xno, int yno, int ynl, int ynr){
	if(yr <= ynl || ynr <= yl) return 0;
	if(yl <= ynl && ynr <= yr) return tree[xno][yno];
	int mid = (ynl+ynr)/2;
	return query_y(yl, yr, xno, 2*yno, ynl, mid)
		+ query_y(yl, yr, xno, 2*yno+1, mid, ynr);
}
ll query_x(int xl, int xr, int yl, int yr, int xno, int xnl, int xnr){
	if(xr <= xnl || xnr <= xl) return 0;
	if(xl <= xnl && xnr <= xr) return query_y(yl, yr, xno, 1, 0, m);
	int mid = (xnl+xnr)/2;
	return query_x(xl, xr, yl, yr, 2*xno, xnl, mid)
		+ query_x(xl, xr, yl, yr, 2*xno+1, mid, xnr);
}
ll query(int xl, int xr, int yl, int yr){
	return query_x(xl, xr, yl, yr, 1, 0, n);
}

void update_y(int x, int y, ll val, int xno, int xnl, int xnr, int yno, int ynl, int ynr){
	if(y < ynl || ynr <= y) return;
	if(ynl+1 == ynr && ynl == y){
		if(xnl+1 == xnr && xnl == x) tree[xno][yno] = val;
		else tree[xno][yno] = tree[2*xno][yno] + tree[2*xno+1][yno];
		return;
	}
	int mid = (ynl+ynr)/2;
	update_y(x, y, val, xno, xnl, xnr, 2*yno, ynl, mid);
	update_y(x, y, val, xno, xnl, xnr, 2*yno+1, mid, ynr);
	tree[xno][yno] = tree[xno][2*yno] + tree[xno][2*yno+1];
}
void update_x(int x, int y, ll val, int xno, int xnl, int xnr){
	if(x < xnl || xnr <= x) return;
	if(xnl+1 == xnr && xnl == x){
		update_y(x, y, val, xno, xnl, xnr, 1, 0, m);
		return;
	}
	int mid = (xnl+xnr)/2;
	update_x(x, y, val, 2*xno, xnl, mid);
	update_x(x, y, val, 2*xno+1, mid, xnr);
	update_y(x, y, val, xno, xnl, xnr, 1, 0, m);
}
void update(int x, int y, ll val){ update_x(x, y, val, 1, 0, n); }
