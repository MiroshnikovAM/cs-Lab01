#include <iostream>
#include <vector>
#include <cmath>

const size_t SCREEN_WIDTH = 80;
const size_t MAX_ASTERISK = SCREEN_WIDTH - 4;

using namespace std;

void find_min_max(vector<double> & numbers, double& min, double& max) {
    min = numbers[0];
    max = numbers[0];
    for (double x : numbers) {
        if (x < min) {
            min = x;
        }
        else
            if (x > max) {
                max = x;
            }
    }
}

void sort_nums_to_bins(vector<double> & numbers, vector<size_t> & bins, double& min, double& max, size_t& bin_count, size_t& max_count) {
    size_t bin_index;
    max_count = 0;
    for (double number : numbers) {
        bin_index = (size_t)( (number - min) * bin_count / (max - min) );
        if (number == max) {
            bin_index--;
        }
        // abs for negatives ??
        bins[bin_index]++;
    }
}

void print_bins( vector<size_t> & bins) {
    for (size_t bin: bins) {
        cout << bin << "| ";
        for (size_t i = 0; i < bin; i++) {
            cout << "*";
        }
        cout << "\n";
    }
}

size_t find_max_count( vector<size_t> & bins) {
    size_t max = bins[0];
    for (size_t bin: bins) {
        if (bin > max) {
            max = bin;
        }
    }
    return max;
}

void print_bins_scaled( vector<size_t> & bins, size_t & max_count) {

    // bool fl;
    /*
    if (max_count > MAX_ASTERISK) {
        fl = true;
    } else {
        fl = false;
    }
    */
    max_count = find_max_count(bins);
    size_t height;
    double k = static_cast<double>(MAX_ASTERISK) / max_count;
    for (size_t bin: bins) {
        if ((bin) < 100) {
            cout << " ";
        }
        if ((bin) < 10) {
            cout << " ";
        }
        cout << bin << "|";
        height = k * bin;
        for (size_t i = 0; i < height; i++) {
            cout << "*";
        }
        cout << "\n";
    }
}

void print_bins_vertical(vector<size_t> & bins) {

    size_t max_count = 0;
    for (size_t count : bins) {
        if (count > max_count) {
            max_count = count;
        }
    }
    size_t max_height;
    const bool scaling_needed = max_count > MAX_ASTERISK;
    double scaling_factor = 1;
    if (scaling_needed) {
            scaling_factor = (double)MAX_ASTERISK / max_count;
            max_height = (size_t)(max_count * scaling_factor);
        } else {
            max_height = max_count;
        }

    for (size_t i = 0; i < max_height; i++) {
        for (size_t bin : bins) {
            size_t height = bin;
            if (scaling_needed) {
                height = (size_t)(bin * scaling_factor);
            }
            if (height > i) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }
    return;
}

int main()
{
    // Input
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    vector<double> numbers(number_count);
    cerr << "Enter numbers:\n";
    for (size_t i = 0; i < number_count; i++) {
        cin >> numbers[i];
    }
    cerr << "Enter bin count: ";
    size_t bin_count;
    cin >> bin_count;
    // End of Input
    vector<size_t> bins(bin_count, 0);
    double min, max;
    size_t max_count;
    find_min_max(numbers, min, max);
    sort_nums_to_bins(numbers, bins, min, max, bin_count, max_count);
    // print_bins_scaled(bins, max_count);
    print_bins_vertical(bins);
    return 0;
}
