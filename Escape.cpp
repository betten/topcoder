// http://community.topcoder.com/stat?c=problem_statement&pm=1170&rd=4371
// Problem Name:	 Escape
// Used In:	 TCI '02 Semifinals 2
// Used As:	 Division I Level Two
// Categories:	 Graph Theory, Search
#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

struct Point {
	int x;
	int y;
	int life;
};

class ComparePoint {
	public:
	bool operator()(Point &p1, Point &p2) {
		return (p1.life > p2.life);
	}
};

class Escape {
	public:
	
	enum Type { Normal, Harmful, Deadly };
	
	static const int N = 501;
	static const int GOAL = N - 1;
	int board[N][N];
	bool visited[N][N];
	
	Escape () {
	}
	
	void setRegions(vector<string> regions, Type t) {
		int x1, y1, x2, y2, tx, ty;
		for(size_t i = 0; i < regions.size(); i++) {
			istringstream ss(regions[i]);
			ss >> x1 >> y1 >> x2 >> y2;
			if(x1 > x2) {
				tx = x1;
				x1 = x2;
				x2 = tx;
			}
			if(y1 > y2) {
				ty = y1;
				y1 = y2;
				y2 = ty;
			}
			for(int x = x1; x <= x2; x++) {
				for(int y = y1; y <= y2; y++) {
					board[x][y] = t;
				}
			}
		}
	}
	
	int lowest(vector<string> harmful, vector<string> deadly) {
		resetBoard();
		
		setRegions(harmful, Harmful);
		setRegions(deadly, Deadly);
		
		priority_queue<Point, vector<Point>, ComparePoint> q;
		
		//printBoard();
		
		q.push({ 0, 0, 0 });
		
		Point p, n;
		int i = 0;
		vector<Point> neighbors;
		
		while(!q.empty()) {
			p = q.top();
			q.pop();
			
			//cout << p.x << "," << p.y << " = " << p.life << " / " << q.size() << " / " << ++i << endl;
			
			if(p.x < 0 || p.x > GOAL || p.y < 0 || p.y > GOAL) continue;
			
			if(visited[p.x][p.y]) continue;
			visited[p.x][p.y] = true;	
			
			//printVisited();
			//cin.get();
			
			if(p.x == GOAL && p.y == GOAL) {
				return p.life;		
			}
			
			neighbors = {
				{ p.x, p.y + 1, p.life }, // up
				{ p.x, p.y - 1, p.life }, // down
				{ p.x - 1, p.y, p.life }, // left
				{ p.x + 1, p.y, p.life } // right
			};
			
			for(size_t i = 0; i < 4; i++) { // neighbors.size() = 4
				n = neighbors[i];
				if(board[n.x][n.y] == Deadly) {
					//n.life = numeric_limits<int>::max();
					continue;
				}
				if(board[n.x][n.y] == Harmful) {
					n.life = n.life + 1;
				}
				q.push(n);
			}
			
			//if(board[p.x][p.y] == Deadly) {
				//// do nothing
			//} else if(board[p.x][p.y] == Harmful) {
				//// do something
			//} else {
				//// do something else
			//}
			
			//q.push({ p.x - 1, p.y });
			//q.push({ p.x + 1, p.y });
			//q.push({ p.x, p.y - 1 });
			//q.push({ p.x, p.y + 1 });
		}
		
		return -1;
	}
	
	void resetBoard() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				board[i][j] = Normal;
				visited[i][j] = false;
			}
		}
	}
	
	void printBoard() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				cout << board[i][j] << " ";
			}
			cout << endl;
		}
	}
	
	void printVisited() {
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < N; j++) {
				cout << visited[i][j] << " ";
			}
			cout << endl;
		}
	}
};

int main() {
	Escape e;
	// cout << "lowest: " << e.lowest({}, {}) << endl; // 0
	//cout << "lowest: " << e.lowest({"500 0 0 500"}, {"0 0 0 0"}) << endl; // 1000
	//cout << "lowest: " << e.lowest({"0 0 250 250", "250 250 500 500"}, {"0 251 249 500", "251 0 500 249"}) << endl; // 1000
	//cout << "lowest: " << e.lowest({"0 0 250 250", "250 250 500 500"}, {"0 250 250 500", "250 0 500 250"}) << endl; // -1
	//cout << "lowest: " << e.lowest({}, {"500 500 500 500"}) << endl; // -1
	cout << "lowest: " << e.lowest({"468 209 456 32", "71 260 306 427", "420 90 424 492", "374 253 54 253", "319 334 152 431", "38 93 204 84", "246 0 434 263", "12 18 118 461", "215 462 44 317", "447 214 28 475", "3 89 38 125", "157 108 138 264", "363 17 333 387", "457 362 396 324", "95 27 374 175", "381 196 265 302", "105 255 253 134", "0 308 453 55", "169 28 313 498", "103 247 165 376", "264 287 363 407", "185 255 110 415", "475 126 293 112", "285 200 66 484", "60 178 461 301", "347 352 470 479", "433 130 383 370", "405 378 117 377", "403 324 369 133", "12 63 174 309", "181 0 356 56", "473 380 315 378"}, {"250 384 355 234", "28 155 470 4", "333 405 12 456", "329 221 239 215", "334 20 429 338", "85 42 188 388", "219 187 12 111", "467 453 358 133", "472 172 257 288", "412 246 431 86", "335 22 448 47", "150 14 149 11", "224 136 466 328", "369 209 184 262", "274 488 425 195", "55 82 279 253", "153 201 65 228", "208 230 132 223", "369 305 397 267", "200 145 98 198", "422 67 252 479", "231 252 401 190", "312 20 0 350", "406 72 207 294", "488 329 338 326", "117 264 497 447", "491 341 139 438", "40 413 329 290", "148 245 53 386", "147 70 186 131", "300 407 71 183", "300 186 251 198", "178 67 487 77", "98 158 55 433", "167 231 253 90", "268 406 81 271", "312 161 387 153", "33 442 25 412", "56 69 177 428", "5 92 61 247"}) << endl; // 254
	cout << "lowest: " << e.lowest({"31 68 123 131", "118 204 258 389", "379 163 452 149", "472 60 488 187", "494 319 383 271", "111 119 372 321", "360 36 448 388", "90 108 38 487", "152 178 374 134", "369 73 211 41", "245 307 354 312", "112 198 284 100", "81 46 285 109", "194 149 99 470", "141 267 490 470", "210 337 29 317", "359 37 70 71", "428 82 42 115", "488 416 159 30", "222 322 107 21", "24 256 459 23", "161 98 373 467", "411 353 79 195", "50 222 213 374", "400 370 343 320", "362 97 338 27", "53 95 289 299", "80 343 301 262", "491 239 295 227", "161 459 366 242", "124 69 328 377", "385 421 294 261", "242 336 458 53"}, {"37 197 284 62", "421 34 412 435", "464 316 364 374", "388 220 61 112", "171 244 219 411", "63 164 353 167", "270 435 17 279", "141 308 325 272", "200 77 441 287", "208 68 494 393", "258 136 257 352", "491 194 474 331", "135 471 388 259", "485 477 382 434", "229 380 45 199", "329 269 140 466", "186 98 146 106", "390 355 460 206", "197 356 342 464", "192 388 395 24", "239 257 102 350", "416 185 488 261", "47 359 452 147", "331 337 142 388", "253 446 46 429", "145 182 492 41", "225 134 437 199", "388 348 162 163", "302 53 459 263", "60 169 442 75", "202 478 344 125", "412 414 4 466", "37 420 242 469", "334 395 447 395"}) << endl; // 0
	cout << "lowest: " << e.lowest({"0 300 0 200", "500 200 400 0", "400 300 300 200", "100 200 200 100", "0 0 300 100", "200 100 200 200", "400 500 0 200", "200 400 300 500", "400 400 500 0", "100 100 300 500", "500 400 400 100", "300 400 200 300", "500 200 200 0", "300 500 400 300", "300 200 400 0", "100 100 300 200", "500 300 500 100", "200 0 100 200", "100 100 300 0", "400 0 100 0", "500 0 500 0", "200 300 400 400", "100 400 200 200"}, {"40 20 215 280", "300 215 390 325"}) << endl; // 663
}
