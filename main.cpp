#include <iostream>
#include <string>
#include <vector>
#include "svg.h"
#include "histogram.h"
#include <curl/curl.h>
#include <sstream>
#include <string>

using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};

vector<double> input_numbers(istream& in, size_t cnt) {
    vector<double> result(cnt);
    for (size_t i = 0; i < cnt; i++)
    {
        in >> result[i];
    }
    return result;
}


Input read_input(istream& in, bool prompt) {
    Input data;
    if (prompt)
        cerr << "enter number count: ";
    size_t number_count;
    in >> number_count;
    if (prompt)
        cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    if (prompt)
        cerr << "enter bin count: ";
    in >> data.bin_count;
    return data;
}

vector<size_t> make_histogram(Input input)
{
    double min, max;
    find_minmax(input.numbers, min, max);
    double bin_size = (max - min) / input.bin_count;
    vector<size_t> bins(input.bin_count, 0);
    for (size_t i = 0; i < input.numbers.size(); i++){
        bool found = false;
        for (size_t j = 0; j < input.bin_count - 1 && !found; j++){
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;

            if (lo <= input.numbers[i] && input.numbers[i] < hi){
                bins[j]++;
                found = true;
            }
        }
        if (!found){
            bins[input.bin_count - 1]++;
        }
    }
    return bins;
}

void show_histogram_text(vector<size_t> bins) {
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

Input
download(const string& address) {
    stringstream buffer;

    CURL *curl = curl_easy_init();
        if(curl) {
            CURLcode res;
            curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
            res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                cerr << curl_easy_strerror(res) << endl;
                exit(1);
            }
            curl_easy_cleanup(curl);
        }

    return read_input(buffer, false);
}

int main(int argc, char* argv[]) {
	Input input;
    if (argc > 1) {
        input = download(argv[1]);
    } else {
        input = read_input(cin, true);
    }

	//Расчёт Гистограммы
	const auto bins = make_histogram(input);

	//Вывод данных
    show_histogram_svg(bins);
	return 0;
}
