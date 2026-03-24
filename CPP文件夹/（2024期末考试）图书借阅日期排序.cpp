#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
using namespace std;
struct book {
	string name;
	string day;
	string month;
	string year;
	int daynum;
	int monthnum;
	int yearnum;
};
int main() {
	vector<string>days = { "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "19th", "20th", "21st", "22nd", "23rd", "24th", "25th", "26th", "27th", "28th", "29th", "30th", "31st" };
	vector<string> months = { "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	int n;
	cin >> n;
	cin.ignore();
	vector<book>a(n);
	for (int i = 0; i < n; i++) {
		string input;
		char ch;
		getline(cin, input);
		stringstream ss(input);
		ss >> a[i].name;
		string date;
		ss >> date;
		stringstream ss1(date);
		getline(ss1, a[i].day, '-');
		getline(ss1, a[i].month, '-');
		getline(ss1, a[i].year);
		for (int j = 0; j < 31; j++) {
			if (a[i].day == days[j])a[i].daynum = j;
		}
		for (int j = 0; j < 12; j++) {
			if (a[i].month == months[j])a[i].monthnum = j;
		}
		a[i].yearnum = stoi(a[i].year);
	}
	sort(a.begin(), a.end(),
		[](const auto& b1, const auto& b2) {
			if (b1.yearnum != b2.yearnum) {
				return b1.yearnum > b2.yearnum;
			}
			if (b1.monthnum != b2.monthnum) {
				return b1.monthnum > b2.monthnum;
			}
			if (b1.daynum != b2.daynum) {
				return b1.daynum > b2.daynum;
			}
			return b1.daynum > b2.daynum;
		}
	);
	for (int i = n - 1; i >= 0; i--) {
		cout << a[i].name << endl;
	}
	return 0;
}