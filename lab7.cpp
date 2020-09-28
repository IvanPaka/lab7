#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void taylor_method(double h, double *y, double *dy) {
    int n = (2 + h)/h;

    double x[n];
    for(int i = 0; i < n; i++)
        x[i] = i*h;

    y[0] = 1;
    dy[0] = 0;
    double d2y = -4;
    double d3y = cos(0) - 4*dy[0];
    double d4y = -sin(0) - 4*d2y;
    for(int i = 1; i < n; i++) {
        y[i] = y[i-1] + h*dy[i-1] + h*h*d2y/2. + h*h*h*d3y/6.;
        dy[i] = dy[i-1] + h*d2y + h*h*d3y/2. + h*h*h*d4y/6.;
        d2y = sin(x[i]) - 4*y[i];
        d3y = cos(x[i]) - 4*dy[i];
        d4y = -sin(x[i]) - 4*d2y;
    }
}

double find_h(double eps = 0.01) {
    double h = 1;
    bool conv = true;
    do {
        int n = 2/h;
        double y[n], dy[n];
        taylor_method(h, y, dy);
        h /= 2;
        double y1[2*n], dy1[2*n];
        taylor_method(h, y1, dy1);

        double delta_y = abs(y[0] - y1[0]);
        double delta_dy = abs(dy[0] - dy1[0]);

        for(int i = 0; i < n; i++) {
            if(delta_y < abs(y[i] - y1[2*i])){
                delta_y = abs(y[i] - y1[2*i]);
            }
            if(delta_dy < abs(dy[i] - dy1[2*i])) {
                delta_dy = abs(dy[i] - dy1[2*i]);
            }
        }
        conv = delta_y >= eps || delta_dy >= eps;
    } while(conv);
    return h;
}

int main()
{
    double h = find_h();
    int n = (2 + h)/h;
    double y[n], dy[n];
    y[0] = 1;
    dy[0] = 0;
    taylor_method(h, y, dy);

    ofstream out("data.dat", ios_base::out);

    for(int i = 0; i < n; i++){
        out << y[i] << "," << dy[i] << "," << i*h << endl;
    }
    out.close();
    return 0;
}
