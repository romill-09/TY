#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include <chrono>

using namespace std;

const int sz = 5;
const int mx = 10, mn = 1;
vector<int> v(sz);
int in = 0, out = 0;

void produce() {
    while (true) {
        int num = rand() % (mx - mn + 1) + mn;

        while ((in + 1) % sz == out) {
            cout << "Buffer Full" << endl;
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        v[in] = num;
        cout << num << " Produced" << endl;
        in = (in + 1) % sz;

        this_thread::sleep_for(chrono::milliseconds(rand() % 7000));
    }
}

void consume() {
    while (true) {
        while (in == out) {
            cout << "Buffer Empty" << endl;
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        int x = v[out];
        cout << "Consumed " << x << endl;
        out = (out + 1) % sz;

        this_thread::sleep_for(chrono::milliseconds(rand() % 7000));
    }
}

int main() {
    thread prod_thread(produce);
    thread cons_thread(consume);

    prod_thread.join();
    cons_thread.join();

}
