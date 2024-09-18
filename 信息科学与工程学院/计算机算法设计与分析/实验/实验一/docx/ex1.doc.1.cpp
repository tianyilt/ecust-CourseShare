#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdio>

using namespace std;

class Point {
private:
public:
    double x;
    double y;
    Point() {}
    Point(double x_, double y_) : x(x_), y(y_) {}
    
    void setPoint(double x1, double y1) {
        x = x1;
        y = y1;
    }
    /*
    // 引入iostream头文件的编译时间较久，加起来acm提交超时
    double getX() const {
        return x;
    }
    
    double getY() const {
        return y;
    }
    
    friend istream& operator >> (istream& in, Point& p) {
        double x1;
        double y1;
        in >> x1;
        in >> y1;
        p.setPoint(x1, y1);
        
        return in;
    }
    
    friend ostream& operator << (ostream& out, Point p) {
        out << "(" << p.getX() << "," << p.getY() << ")" << endl;
        
        return out; 
    }
	*/
};



class Solution {
private:
    int n;
    vector<Point> pointsX;
    vector<Point> pointsY;
    
    static bool compx(const Point &a, const Point &b) {
	    return a.x < b.x;
	}
	    
	static bool compy(const Point &a, const Point &b) {
	    return a.y < b.y;
	}
    
    inline double fPow(double x) {
		return x * x;
	}
    
    inline double getDistance(const Point & a, const Point & b) {
        return sqrt(fPow(a.x - b.x) + fPow(a.y - b.y));
    }
public:
    Solution () {
        pointsY.resize(100001);
        pointsX.resize(100001);
    }
    void inputPoints() {
        for (int i = 0; i < n; i ++ ) {
            scanf("%lf%lf", &pointsX[i].x, &pointsX[i].y);
        }
    }
    double solve(int l, int r) {
        if (l + 1 == r) {
            return getDistance(pointsX[l], pointsX[r]);
        }
        
        if (l + 2 == r) {
            double d1 = getDistance(pointsX[l], pointsX[r]);
            double d2 = getDistance(pointsX[l], pointsX[l + 1]);
            double d3 = getDistance(pointsX[l + 1], pointsX[r]);
            
            return min(min(d1, d2), d3);
        }
        
        int mid = (l + r) >> 1;
        int cnt = 0;
        
        double ans = min(solve(l, mid), solve(mid + 1, r));
        for (int i = l; i <= r; i ++ ) {
            if (abs(pointsX[i].x - pointsX[mid].x) <= ans) {
                pointsY[cnt ++ ] = pointsX[i];
            }
        }
        sort(pointsY.begin(), pointsY.begin() + cnt, compy);
        for (int i = 0; i < cnt; i ++ ) {
            for (int j = i + 1; j < cnt; j ++ ) {
                if (pointsY[j].y - pointsY[i].y >= ans) {
                    break;
                }
                ans = min(ans, getDistance(pointsY[i], pointsY[j]));
            }
        }
        
        return ans;
    }
    
    void work(int& n) { //, vector<double>& ans
        this->n = n;
        inputPoints();
        
        // 如果compx不是静态的需要使用一下方式创建函数指针
//         std::sort(pointsX.begin(), pointsX.end(), mem_fn(&Solution::compx));
        
        sort(pointsX.begin(), pointsX.begin() + n, compx); // Solution::compx
        
        printf("%.2lf\n", solve(0, n - 1) / 2);
    }
};

int main() {
    int n;
    Solution solution;
    
    while (scanf("%d", &n) == 1 && n) {
        solution.work(n);
    }
    
    return 0;
}
