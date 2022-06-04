#include <iostream>
#include <string>
#include <vector>
#include "svg.h"
#include "histogram.h"

using namespace std;

vector<double>
input_numbers(size_t count) {
	vector<double> result(count);
	for (size_t i = 0; i < count; i++) {
		cin >> result[i];
	}
	return result;
}

vector<size_t>
make_histogram(const vector<double>& numbers, size_t bin_count) {
	vector<size_t> result(bin_count, 0);
	double max; double min;
	find_minmax(numbers, min, max);
	double bin_size = (max - min) / bin_count;
	for (size_t i = 0; i < numbers.size(); i++) {
		bool found = false;
		for (size_t j = 0; j < (bin_count - 1) && !found; j++) {
			auto lo = min + bin_size * j;
			auto hi = min + bin_size * (j + 1);

			if (lo <= numbers[i] && numbers[i] < hi) {
				result[j]++;
				found = true;
			}
		}
		if (!found) {
			result[bin_count - 1]++;
		}
	}
	return result;
}

void
show_histogram_text(vector<size_t> bins) {
	const size_t SCREEN_WIDTH = 80;
	const size_t MAX_ASTERISK = SCREEN_WIDTH - 4 - 1;

	size_t max_count = 0;
	for (size_t count : bins) {
		if (count > max_count) {
			max_count = count;
		}
	}
	const bool scaling_needed = max_count > MAX_ASTERISK;

	double max_height = max_count;
	if (max_count > MAX_ASTERISK) {
		max_height = MAX_ASTERISK;
	}

	for (size_t bin : bins) {
		if (bin < 100) {
			cout << ' ';
		}
		if (bin < 10) {
			cout << ' ';
		}
		cout << bin << "|";

		size_t height = bin;
		if (scaling_needed) {
			const double scaling_factor = (double)MAX_ASTERISK / max_count;
			height = (size_t)(bin * scaling_factor);
		}

		for (size_t i = 0; i < height; i++) {
			cout << '*';
		}
		cout << '\n';
	}

	for (size_t bin : bins) {
		double height = bin;

		if (scaling_needed) {
			const double scaling_factor = (double)MAX_ASTERISK / max_count;
			height = (size_t)(bin * scaling_factor);
		}
		for (size_t i = 0; i < max_height - height - 1; i++) {
			cout << ' ';
		}
		for (size_t i = 0; i < height; i++) {
			cout << '*';
		}

		cout << '|';

		if (bin < 100) {
			cout << ' ';
		}
		if (bin < 10) {
			cout << ' ';
		}
		cout << bin;
		cout << endl;
	}
}

vector<string> input_colours(size_t bin_count) {
    vector<string> colours(bin_count);
    for (int i = 0; i < bin_count; i++) {
        cerr << "Enter bin " << i + 1 << " colour: ";
        cin >> colours[i];
        while (!check_color(colours[i])) {
            cin >> colours[i];
        }
    }
    return colours;
}

int main()
{
	//Ввод данных
	size_t number_count;
    cerr << "enter number count: ";
    cin >> number_count;

	const auto numbers = input_numbers(number_count);

	size_t bin_count;
    cerr << "enter bin count: ";
    cin >> bin_count;

	//Расчёт Гистограммы
	const auto bins = make_histogram(numbers, bin_count);
    const auto colours = input_colours(bin_count);

	//Вывод данных
    show_histogram_svg(bins, colours);
	return 0;
}
